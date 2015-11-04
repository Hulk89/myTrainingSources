#ifndef SCOPED_LOCK_HPP_
#define SCOPED_LOCK_HPP_

#include <pthread.h>

class scoped_lock 
{
  public:

    scoped_lock(pthread_mutex_t* mutex) 
    {
        mutex_ = mutex;
        pthread_mutex_lock(mutex_);
    }

    ~scoped_lock() 
    {
        pthread_mutex_unlock(mutex_);
    }

  private:
    pthread_mutex_t* mutex_;

    //block wrong usage...
    scoped_lock(const scoped_lock& copy);
    scoped_lock& operator=(const scoped_lock& rhs);
};
#endif
