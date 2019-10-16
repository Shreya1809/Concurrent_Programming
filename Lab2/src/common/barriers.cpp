#include <mutex>
#include "barriers.h"

using namespace CP;

IBarSharedPtr BarFactory::GetBarObject(BarType type, int numofthreads)
{
    switch (type)
    {
    case BarType::PTHREAD:
        return std::make_shared<Pthread_Bar>(numofthreads);
    case BarType::SENSE:
        return std::make_shared<Sense_Bar>(numofthreads);
    default:
        return nullptr;
    }
}

IBarrier::~IBarrier() {};

__always_inline void Pthread_Bar::wait() 
{
    pthread_barrier_wait(&(this->bar));
}
Pthread_Bar::Pthread_Bar(int numofthreads)
{
    this->numOfThreads = numofthreads;
    pthread_barrier_init(&(this->bar), NULL, numofthreads );
}
Pthread_Bar::~Pthread_Bar()
{
    pthread_barrier_destroy(&(this->bar));
}

__always_inline void Sense_Bar::wait()
{
    thread_local bool my_sense = 0;
    std::atomic <int> count_copy;
    if(my_sense == 0)
    {
        my_sense =1; //flip sense
    } 
    else
    {
        my_sense = 0;
    }
    count_copy = std::atomic_fetch_add(&count, 1);
    if(count_copy == this->numberOfThreads){ //last to arrive
        count.store(1,std::memory_order_relaxed); 
        senseFlag.store(my_sense);
    }
    else
    { 
        //not last
        while(senseFlag.load() != my_sense){}
    }
  
}

Sense_Bar::~Sense_Bar()
{
    //nothing to do
}