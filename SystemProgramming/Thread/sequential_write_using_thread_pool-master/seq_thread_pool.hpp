#ifndef SEQUENTIAL_THREAD_POOL
#define SEQUENTIAL_THREAD_POOL

#include "scoped_lock.hpp"
#include "thread_pool.hpp"

using namespace threadpool ;

typedef void (*WORK_PROCESS)( void* ) ; 
typedef void (*WORK_COMPLETED_CALLBACK)( int,void* ) ; //seq, result 

typedef struct _ST_PER_PER_WORK_INFO
{
    int n_seq;
    void* data;
    WORK_COMPLETED_CALLBACK  final_completed_cb;
} ST_PER_WORK_INFO ;

class SeqentialWorkManager
{
  public:

    SeqentialWorkManager() ;
    ~SeqentialWorkManager() ;
    void AssignWork( WORK_PROCESS work_process, 
                     void* work_data,
                     int nDataLen,  
                     WORK_COMPLETED_CALLBACK call_back );
    bool Init( int nTotalCpu=0 );
    void Terminate();
    int failed_count ;
    int nTotalOut ;
    int GetNumberOfCpu ();

  private:
    ThreadPool* ptb ;
    pthread_t   write_thread ;
};
#endif
