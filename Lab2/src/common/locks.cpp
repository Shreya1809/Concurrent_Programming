#include <atomic>
#include <mutex>

#include "locks.h"

using namespace CP;

#ifdef DEBUG
#include <iostream>
#define PRINT_DESTRUCTOR_MSG() std::cout << __FUNCTION__ << std::endl
#else
#define PRINT_DESTRUCTOR_MSG()
#endif

ILockSharedPtr LockFactory::GetLockObject(LockType type)
{
    switch (type)
    {
    case LockType::MUTEX_LOCK:
        return std::make_shared<Mutex>();
    case LockType::TAS_LOCK:
        return std::make_shared<TASLock>();
    case LockType::TTAS_LOCK:
        return std::make_shared<TTASLock>();
    case LockType::TICKET_LOCK:
        return std::make_shared<TicketLock>();
    default:
        return nullptr;
    }
}

ILock::~ILock(){ };

__always_inline void Mutex::Lock() 
{
    Mtx.lock();
}

__always_inline void Mutex::Unlock() 
{
    Mtx.unlock();
}

Mutex::~Mutex()
{
    Unlock();
    PRINT_DESTRUCTOR_MSG();
}

__always_inline void TASLock::Lock()
{
    while (Locked.exchange(true, std::memory_order_acquire) == true);
}

__always_inline void TASLock::Unlock()
{
    Locked.store(false, std::memory_order_release);
}

TASLock::~TASLock()
{
    Unlock();
    PRINT_DESTRUCTOR_MSG();
}

__always_inline void TTASLock::Lock() 
{
    do
    {
        TTASLock::WaitUntilLockIsFree();
    } while (Locked.exchange(true, std::memory_order_acquire) == true);
}

__always_inline void TTASLock::WaitUntilLockIsFree() const
{
    while (Locked.load(std::memory_order_relaxed) == true)
        ;
}

__always_inline void TTASLock::Unlock() 
{
    Locked.store(false, std::memory_order_release);
}

TTASLock::~TTASLock()
{
    Unlock();
    PRINT_DESTRUCTOR_MSG();
}

__always_inline void TicketLock::Lock()
{
    const auto myTicketNo = NextTicketNo.fetch_add(1, std::memory_order_relaxed);

    while (ServingTicketNo.load(std::memory_order_acquire) != myTicketNo)
        //CpuRelax();
        asm("pause");
}

__always_inline void TicketLock::Unlock()
{
    // We can get around a more expensive read-modify-write operation
    // (std::atomic_size_t::fetch_add()), because noone can modify
    // ServingTicketNo while we're in the critical section.
    const auto newNo = ServingTicketNo.load(std::memory_order_relaxed) + 1;
    ServingTicketNo.store(newNo, std::memory_order_release);
}

TicketLock::~TicketLock()
{
    Unlock();
    PRINT_DESTRUCTOR_MSG();
}

// class McsLock : public ILock
// {
// public:
//     struct QNode
//     {
//         std::atomic<QNode *> Next = {nullptr};
//         std::atomic_bool     Locked = {false};
//     };

// public:
//     __always_inline void Lock(QNode &node)
//     {
//         node.Next = nullptr;
//         node.Locked = true;

//         QNode *oldTail = Tail.exchange(&node);

//         if (oldTail != nullptr)
//         {
//             oldTail->Next = &node;

//             while (node.Locked == true)
//                 //CpuRelax();
//                 asm("pause");
//         }
//     }

//     __always_inline void Unlock(QNode &node)
//     {
//         if (node.Next.load() == nullptr)
//         {
//             QNode *tailWasMe = &node;
//             if (Tail.compare_exchange_strong(tailWasMe, nullptr))
//                 return;

//             while (node.Next.load() == nullptr)
//                 //CpuRelax();
//                 asm("pause");
//         }

//         node.Next.load()->Locked = false;
//     }

//     private:
//         std::atomic<QNode *> Tail = {nullptr};
//     };

//#define SELF_TEST_LOCK
#ifdef SELF_TEST_LOCK
#include <cassert>
#include <iostream>



using namespace CP;
using namespace std;
int main()
{
    static_assert(alignof(TASLock) == CACHELINE_SIZE, "TAS LOCK is not aligned on CACHELINE_SIZE");
    static_assert(alignof(TTASLock) == CACHELINE_SIZE, "TTAS LOCK is not aligned on CACHELINE_SIZE");
    static_assert(alignof(TicketLock) == CACHELINE_SIZE, "Ticket LOCK is not aligned on CACHELINE_SIZE");


    ILockSharedPtr lock = LockFactory::GetLockObject(LockType::MUTEX_LOCK);
    lock->Lock();
    lock->Unlock();
    assert(lock.get() != nullptr);
    assert(lock.use_count() == 1);
    ILockSharedPtr newLock = lock;
    assert(lock.use_count() == 2);
    assert(newLock.use_count() == 2);
    lock = LockFactory::GetLockObject(LockType::TAS_LOCK);
    assert(lock.get() != nullptr);
    assert(lock.use_count() == 1);
    lock = LockFactory::GetLockObject(LockType::TICKET_LOCK);
    assert(lock.get() != nullptr);
    assert(lock.use_count() == 1);

    return 0;
}
#endif
