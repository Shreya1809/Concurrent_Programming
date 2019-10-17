#include <set>
#include <algorithm>
#include <vector>
#include <pthread.h>
#include <algorithm>
#include <math.h>
#include <stdio.h>
#include "locks.h"
#include "parse.h"
#include <iostream>
using namespace CP;

using namespace std;

struct timespec start_time1, end_time1;
class Bucket
{
    private:
        std::multiset<int> _bucket;
        ILockSharedPtr _bucketLock = nullptr;
        std::shared_ptr<CP::McsLock> _mcsLock = nullptr;

    public:
        Bucket(LockType typeoflock)
        {
            if(typeoflock == CP::LockType::MCS_LOCK)
                _mcsLock = std::make_shared<CP::McsLock>();
            
            _bucketLock = LockFactory::GetLockObject(typeoflock);
            // cout << "*****SHREYA**" <<std::string(__FUNCTION__) << "Lock type:" << (int)(_bucketLock->GetLockType()) << endl;
        }
        ~Bucket()
        {
            // cout << __FUNCTION__ << endl;
        }
        void insert(int num, McsLock::QNode &node)
        {
            if(_bucketLock->GetLockType() != LockType::MCS_LOCK)
            {
                _bucketLock->Lock();
                _bucket.insert(num);
                _bucketLock->Unlock();
            }
            else 
            {
                // static McsLock::QNode node;
                _mcsLock->Lock(node);
                _bucket.insert(num);
                _mcsLock->Unlock(node);
            }
            
        }
        vector<int> getBucket()
        {
            return std::vector<int>(_bucket.begin(),_bucket.end());
        }

};

class BucketManager
{
    private:
        // Bucket *_bucketHolder;
        std::vector<Bucket> _bucketHolder;
        size_t _numBucket;
        int _min;
        int _max;
        
    public:
    BucketManager(size_t numBuckets, int minVal, int maxVal, LockType typeofLock): _numBucket(numBuckets),_min(minVal),_max(maxVal)
    {
        // _bucketHolder = new Bucket[_numBucket](typeofLock);
        _bucketHolder.resize(numBuckets, Bucket(typeofLock));
    }
    ~BucketManager()
    {
        // delete []_bucketHolder;
    }

    void insert(int num, McsLock::QNode &node)
    {
        //printf("\rinserting number %d ",num);
        int index = floor ((_numBucket-1) * num / _max);
        //int index = floor (_numBucket * num / _max);
        //int index1 = (num - _min) % _numBucket;
        _bucketHolder[index].insert(num, node);
    }

    vector<int> getSortedList()
    {
        vector<int> sortedList;
        for(size_t i = 0; i < _numBucket; i++)
        {
            vector<int> temp = _bucketHolder[i].getBucket();
            sortedList.insert(sortedList.end(), temp.begin(), temp.end());
        }
        return sortedList;
    }
};

struct _distributeArg
{
    vector<int> *inArray;
    size_t low;
    size_t high;
    BucketManager *buckMan;
};

void *distribute(void *args)
{
    struct _distributeArg *arg = (struct _distributeArg*)args;
    McsLock::QNode node;
    //printf("in distribute thread %d\n",arg->inArray);
    for(size_t i = arg->low; i <= arg->high; i++)
    {
        arg->buckMan->insert((*(arg->inArray))[i], node);
    }
    return 0;
}

void bucketsortMethod(vector<int> *inputArray, size_t numOfThreads)
{
    //printf("In bucket sort method....\n");
    int min = *min_element(inputArray->begin(),inputArray->end());
    int max = *max_element(inputArray->begin(),inputArray->end());
    BucketManager buckMan(sqrt(inputArray->size()), min, max, lockType);
    //BucketManager buckMan(10, min, max);
    const size_t MAX_ELEMENTS = inputArray->size();
    pthread_t threads[numOfThreads];
    struct _distributeArg threadArg[numOfThreads];
    size_t i = 0;
    for (i = 0; i < numOfThreads; i++)
    {
        threadArg[i].inArray = inputArray;
        threadArg[i].buckMan = &buckMan;
        threadArg[i].low = i * (MAX_ELEMENTS /numOfThreads ); 
        threadArg[i].high = (i + 1) * (MAX_ELEMENTS / numOfThreads) - 1; 
    }
    threadArg[i-1].high = MAX_ELEMENTS -1;
    clock_gettime(CLOCK_MONOTONIC,&start_time1);
    for(i = 0; i < numOfThreads; i++)
    {
        pthread_create(&threads[i], NULL, distribute, 
                                        (void*)&threadArg[i]); 
    }
    //printf("%ld threads created\n",numOfThreads);
    for (i = 0; i < numOfThreads; i++)
    { 
        pthread_join(threads[i], NULL);
        //printf("joined thread number %zu\n",i+1); 
    }
    clock_gettime(CLOCK_MONOTONIC,&end_time1);

    vector<int> sorted = buckMan.getSortedList();
    copy(sorted.begin(), sorted.end(), inputArray->begin());
    unsigned long long elapsed_ns;
	elapsed_ns = (end_time1.tv_sec-start_time1.tv_sec)*1000000000 + (end_time1.tv_nsec-start_time1.tv_nsec);
	printf("Elapsed (ns): %llu\n",elapsed_ns);
	double elapsed_s = ((double)elapsed_ns)/1000000000.0;
	printf("Elapsed (s): %lf\n",elapsed_s);
}