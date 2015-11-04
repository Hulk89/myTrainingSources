//original c version author: Tomer Heber (heber.tomer@gmail.com).
//http://sourceforge.net/projects/cthreadpool/

#ifndef _THREAD_POOL_HPP_
#define _THREAD_POOL_HPP_

#include <iostream>
#include <pthread.h>
using namespace std;

namespace threadpool
{
    typedef void (*WORK_FOR_WORKER_THREAD)(void*) ; 
    typedef void (*COMPLETED_CALLBACK)( void* ) ; 

	#define THREAD_POOL_QUEUE_SIZE 10000
    
    typedef enum _T_ADD_TASK
    {
        NON_BLOCKING = 0,
        BLOCKING = 1
    } T_ADD_TASK;

	class Task
	{
		public:
			void (*user_work)(void*);
			void* data;
            COMPLETED_CALLBACK user_cb;
            void* callback_data; //20130819
	};

	class TaskQueue 
	{
		public:
			unsigned int head;
			unsigned int tail;
			unsigned int num_of_cells;
			void *cells[THREAD_POOL_QUEUE_SIZE];
	};


	class ThreadPool 
	{
		private:
			TaskQueue tasks_queue;
			Task tasks[THREAD_POOL_QUEUE_SIZE];
			void InitQueue ( TaskQueue *queue);
			void* DequeueTask ( TaskQueue *queue);

		public:
			ThreadPool(int num_of_threads= 4);
			~ThreadPool();
			volatile unsigned short stop_flag; //XXX need a lock.?
			pthread_mutex_t free_tasks_mutex;
			pthread_mutex_t mutex;
			pthread_cond_t free_tasks_cond;
			pthread_cond_t cond;
			TaskQueue free_tasks_queue;
			unsigned short num_of_threads;
			pthread_t *thr_arr;

			Task* GetTask (void);
			void InitTask (struct Task *task);
			bool InitThreadPool ();
			int  EnqueueTask (TaskQueue *queue, void *data) ;
			int DoesQueueEmpty( TaskQueue *queue);
			int GetQueueSize ( TaskQueue *queue);

			bool Terminate();

			int AddTask (
					WORK_FOR_WORKER_THREAD work_to_do,  
					void *data, 
					T_ADD_TASK blocking
					)
           {
                return AddTaskWithCallBack ( work_to_do, data, blocking, NULL, NULL );
           }

			int AddTaskWithCallBack (
					WORK_FOR_WORKER_THREAD work_to_do,  
					void *data, 
					T_ADD_TASK blocking,
                    COMPLETED_CALLBACK cb ,
                    void* callback_data
					) ;
	};
}

#endif
