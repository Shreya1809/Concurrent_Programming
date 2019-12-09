#ifndef LOCK_H_
#define LOCK_H_

#include <pthread.h>
//#define USE_RWLOCK

#ifdef USE_RWLOCK
#define LOCK_T              pthread_rwlock_t
#define LOCK_INIT(lock)     pthread_rwlock_init(&lock , NULL) 
#define LOCK_RDLOCK(lock)   pthread_rwlock_rdlock(&lock)
#define LOCK_WRLOCK(lock)   pthread_rwlock_wrlock(&lock)
#define LOCK_UNLOCK(lock)   pthread_rwlock_unlock(&lock)
#else
#define LOCK_T              pthread_mutex_t
#define LOCK_INIT(lock)     pthread_mutex_init(&lock , NULL) 
#define LOCK_RDLOCK(lock)   pthread_mutex_lock(&lock)
#define LOCK_WRLOCK(lock)   pthread_mutex_lock(&lock)
#define LOCK_UNLOCK(lock)   pthread_mutex_unlock(&lock)
#endif


#endif