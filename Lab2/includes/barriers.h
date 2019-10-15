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
        SENSE
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
        static IBarSharedPtr GetBarObject(BarType type);
    };

    class Pthread_Bar : public IBarrier
    {
        public:
        __always_inline void wait() override;
        BarType GetBarType() const override
        { 
            return this->TypeOfBarrier; 
        }
        ~Pthread_Bar();
        private:
        pthread_barrier_t bar;
        const BarType TypeOfBarrier = BarType::PTHREAD; 

    };

    class Sense_Bar : public IBarrier
    {
        public:
        __always_inline void wait() override;
        BarType GetBarType() const override
        { 
            return this->TypeOfBarrier; 
        }
        ~Sense_Bar();
        private:
        std::atomic<int> count = 0;
        std::atomic<int> senseFlag = 0;
        size_t numberOfThreads;
        const BarType TypeOfBarrier = BarType::SENSE; 

    };
}

#endif
