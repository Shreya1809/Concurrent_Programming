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
        MCS_LOCK,
        NONE
    };

    //interface for Lock type
    class ILock
    {
        public:
        virtual void Lock() = 0;
        virtual void Unlock() = 0;
        virtual LockType GetLockType() const = 0;
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
        LockType GetLockType() const override
        { 
            return this->TypeOfLock; 
        }
        ~Mutex();

    private:
        std::mutex Mtx;
        const LockType TypeOfLock = LockType::MUTEX_LOCK; 
    };

    class TASLock : public ILock
    {

    public:
        __always_inline void Lock() override;
        __always_inline void Unlock() override;
        LockType GetLockType() const override
        { 
            return this->TypeOfLock; 
        }
        ~TASLock();

    private:
        alignas(CACHELINE_SIZE) std::atomic_bool Locked = {false};
        static_assert(alignof(Locked) == CACHELINE_SIZE, "Locked is not aligned on CACHELINE_SIZE");
        const LockType TypeOfLock = LockType::TAS_LOCK;
    };

    class TTASLock : public ILock
    {

    public:
        __always_inline void Lock() override;
        __always_inline void Unlock() override;
        LockType GetLockType()const override
        { 
            return this->TypeOfLock; 
        }
        ~TTASLock();

    private:
        __always_inline void WaitUntilLockIsFree() const;
        alignas(CACHELINE_SIZE) std::atomic_bool Locked = {false};
        static_assert(alignof(Locked) == CACHELINE_SIZE, "Locked is not aligned on CACHELINE_SIZE");
        const LockType TypeOfLock = LockType::TTAS_LOCK;
    };


    class TicketLock : public ILock
    {
    public:
        __always_inline void Lock() override;
        __always_inline void Unlock() override;
        LockType GetLockType() const override
        { 
            return this->TypeOfLock; 
        }
        ~TicketLock();

    private:
        const LockType TypeOfLock = LockType::TICKET_LOCK;
        alignas(CACHELINE_SIZE) std::atomic_size_t ServingTicketNo = {0};
        alignas(CACHELINE_SIZE) std::atomic_size_t NextTicketNo = {0};
        static_assert(alignof(ServingTicketNo) == CACHELINE_SIZE, "ServingTicketNo is not aligned on CACHELINE_SIZE ");
        static_assert(alignof(NextTicketNo) == CACHELINE_SIZE, "NextTicketNo is not aligned on CACHELINE_SIZE");
    };

    class McsLock : public ILock
    {
    public:
    struct QNode
    {
        std::atomic<QNode *> Next = {nullptr};
        std::atomic_bool     Locked = {false};
    };
    public:
        [[deprecated("not implemented - use Lock(QNode)")]] __always_inline void Lock() override {};//{ static_assert(false, "Never Call this Lock function"); };
        [[deprecated("not implemented - use Unlock(QNode)")]] __always_inline void Unlock() override {};//{ static_assert(false, "Never Call this Lock function"); };
        void Lock(QNode &node);
        void Unlock(QNode &node);
        LockType GetLockType() const override
        { 
            return this->TypeOfLock; 
        }
        ~McsLock();  
    private:
        //alignas(CACHELINE_SIZE) 
        std::atomic<QNode *> Tail = {nullptr};
        const LockType TypeOfLock = LockType::MCS_LOCK;
    };

};



#endif