#ifndef LOCKS_H_
#define LOCKS_H_

#include <atomic>
#include <mutex>
#include <memory>

namespace CP
{
    constexpr size_t CACHELINE_SIZE = 64;

    enum class LockType
    {
        MUTEX_LOCK = 0,
        TAS_LOCK,
        TTAS_LOCK,
        TICKET_LOCK,
        MCS_LOCK
    };

    //interface for Lock type
    class ILock
    {
        public:
        virtual void Lock() = 0;
        virtual void Unlock() = 0;
        virtual ~ILock() = 0;
    };

    using ILockSharedPtr = std::shared_ptr<ILock>;

    class LockFactory
    {
        public:
        static ILockSharedPtr GetLockObject(LockType type);
    };

    class Mutex : public ILock
    {

    public:
        __always_inline void Lock() override;
        __always_inline void Unlock() override;
        ~Mutex();

    private:
        std::mutex Mtx;
        
    };

    class TASLock : public ILock
    {

    public:
        __always_inline void Lock() override;
        __always_inline void Unlock() override;
        ~TASLock();

    private:
        alignas(CACHELINE_SIZE) std::atomic_bool Locked = {false};
        static_assert(alignof(Locked) == CACHELINE_SIZE, "Locked is not aligned on CACHELINE_SIZE");
    };

    class TTASLock : public ILock
    {

    public:
        __always_inline void Lock() override;
        __always_inline void Unlock() override;
        ~TTASLock();

    private:
        __always_inline void WaitUntilLockIsFree() const;
        alignas(CACHELINE_SIZE) std::atomic_bool Locked = {false};
        static_assert(alignof(Locked) == CACHELINE_SIZE, "Locked is not aligned on CACHELINE_SIZE");
    };


    class TicketLock : public ILock
    {
    public:
        __always_inline void Lock() override;
        __always_inline void Unlock() override;
        ~TicketLock();

    private:
        alignas(CACHELINE_SIZE) std::atomic_size_t ServingTicketNo = {0};
        alignas(CACHELINE_SIZE) std::atomic_size_t NextTicketNo = {0};
        static_assert(alignof(ServingTicketNo) == CACHELINE_SIZE, "ServingTicketNo is not aligned on CACHELINE_SIZE ");
        static_assert(alignof(NextTicketNo) == CACHELINE_SIZE, "NextTicketNo is not aligned on CACHELINE_SIZE");
    };

};



#endif