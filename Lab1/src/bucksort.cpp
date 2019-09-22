#include <set>
#include <algorithm>
#include <vector>
#include <pthread.h>
#include <algorithm>
using namespace std;

struct timespec start_time1, end_time1;

class Bucket
{
    private:
        std::multiset<int> _bucket;
        pthread_mutex_t _bucketLock;

    public:
        Bucket()
        {
            pthread_mutex_init(&_bucketLock, NULL);
            
        }
        void insert(int num)
        {
            pthread_mutex_lock(&_bucketLock);
            _bucket.insert(num);
            pthread_mutex_unlock(&_bucketLock);
        }
        vector<int> getBucket()
        {
            return std::vector<int>(_bucket.begin(),_bucket.end());
        }

};

class BucketManager
{
    private:
        Bucket *_bucketHolder;
        size_t _numBucket;
        int _min;
        int _max;
        
    public:
    BucketManager(size_t numBuckets, int minVal, int maxVal): _numBucket(numBuckets),_min(minVal),_max(maxVal)
    {
        _bucketHolder = new Bucket[_numBucket];
    }
    ~BucketManager()
    {
        delete []_bucketHolder;
    }

    void insert(int num)
    {
        int index = floor (_numBucket * num / _max);
        int index1 = (num - _min) / _numBucket;
        _bucketHolder[index1].insert(num);
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
    clock_gettime(CLOCK_MONOTONIC,&start_time1);
    for(size_t i = arg->low; i <= arg->high; i++)
    {
        arg->buckMan->insert((*(arg->inArray))[i]);
    }
    clock_gettime(CLOCK_MONOTONIC,&end_time1);
    return 0;
}

void bucketsortMethod(vector<int> *inputArray, size_t numOfThreads)
{
    int min = *min_element(inputArray->begin(),inputArray->end());
    int max = *max_element(inputArray->begin(),inputArray->end());
    BucketManager buckMan(inputArray->size(), min, max);
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

    for(i = 0; i < numOfThreads; i++)
    {
        pthread_create(&threads[i], NULL, distribute, 
                                        (void*)&threadArg[i]); 
    }
  
    // joining all 4 threads 
    for (i = 0; i < numOfThreads; i++)
    { 
        pthread_join(threads[i], NULL);
        printf("joined thread number %zu\n",i+1); 
    }

    vector<int> sorted = buckMan.getSortedList();
    copy(sorted.begin(), sorted.end(), inputArray->begin());
    unsigned long long elapsed_ns;
	elapsed_ns = (end_time1.tv_sec-start_time1.tv_sec)*1000000000 + (end_time1.tv_nsec-start_time1.tv_nsec);
	printf("Elapsed (ns): %llu\n",elapsed_ns);
	double elapsed_s = ((double)elapsed_ns)/1000000000.0;
	printf("Elapsed (s): %lf\n",elapsed_s);
}