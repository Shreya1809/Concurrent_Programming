#ifndef BARRIERS_H_
#define BARRIERS_H_

#include <mutex>
#include <memory>
#include <pthread.h>
#include <atomic>

namespace CP
{
    enum class BarType
    {
        PTHREAD = 0,
        SENSE,
        NONE
    };

    class IBarrier
    {
        public:
        virtual void wait() = 0;
        virtual BarType GetBarType() const = 0;
        virtual ~IBarrier() = 0;
    };

    using IBarSharedPtr = std::shared_ptr<IBarrier>;

    class BarFactory
    {
        public:
        static IBarSharedPtr GetBarObject(BarType type, int numofthreads);
    };

    class Pthread_Bar : public IBarrier
    {
        public:
        Pthread_Bar() = delete;
        Pthread_Bar(int numofthread);
        __always_inline void wait() override;
        BarType GetBarType() const override
        { 
            return this->TypeOfBarrier; 
        }
        ~Pthread_Bar();
        private:
        int numOfThreads = 0;
        pthread_barrier_t bar = {0};
        const BarType TypeOfBarrier = BarType::PTHREAD; 

    };

    class Sense_Bar : public IBarrier
    {
        public:
        Sense_Bar() = delete;
        Sense_Bar(int numofthreads):numberOfThreads(numofthreads){};
        __always_inline void wait() override;
        BarType GetBarType() const override
        { 
            return this->TypeOfBarrier; 
        }
        ~Sense_Bar();
        private:
        std::atomic<int> count = 1;
        std::atomic<int> senseFlag = 0;
        int numberOfThreads = 0;
        const BarType TypeOfBarrier = BarType::SENSE; 

    };
};

#endif
