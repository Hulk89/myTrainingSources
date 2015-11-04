//original c version author: Tomer Heber (heber.tomer@gmail.com).
//http://sourceforge.net/projects/cthreadpool/

#include "thread_pool.hpp"
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

#define THREAD_POOL_DEBUG

#ifdef THREAD_POOL_DEBUG
#define REPORT_ERROR(...) fprintf (stderr,"line %d - ",__LINE__); fprintf (stderr, __VA_ARGS__); fprintf (stderr,"\n")
#else
#define REPORT_ERROR(...)
#endif /* THREAD_POOL_DEBUG */

using namespace threadpool ;

ThreadPool* pThisInstance;

///////////////////////////////////////////////////////////////////////////////

ThreadPool::ThreadPool(int num_threads)
{
    pThisInstance = this;
    num_of_threads = num_threads ;
    InitThreadPool();
}

///////////////////////////////////////////////////////////////////////////////
ThreadPool::~ThreadPool()
{
    Terminate();
}

///////////////////////////////////////////////////////////////////////////////
void ThreadPool::InitQueue(TaskQueue *queue)
{
    int i;

    for (i = 0; i < THREAD_POOL_QUEUE_SIZE; i++)
    {
        queue->cells[i] = NULL;
    }

    queue->head = 0;
    queue->tail = 0;
    queue->num_of_cells = 0;
}

///////////////////////////////////////////////////////////////////////////////
int ThreadPool::EnqueueTask(TaskQueue *queue, void *data)
{
    if (queue->num_of_cells == THREAD_POOL_QUEUE_SIZE) 
    {
        REPORT_ERROR("The queue is full, unable to add data to it.");
        return -1;
    }

	if (queue->cells[queue->tail] != NULL) 
	{
		REPORT_ERROR("A problem was detected in the queue (expected NULL, but found a different value).");
		return -1;
	}

	queue->cells[queue->tail] = data;

	queue->num_of_cells++;
	queue->tail++;

	if (queue->tail == THREAD_POOL_QUEUE_SIZE) 
	{
		queue->tail = 0;
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
void* ThreadPool::DequeueTask( TaskQueue *queue)
{
	void *data;

	if (queue->num_of_cells == 0) 
	{
		REPORT_ERROR("Tried to dequeue from an empty queue.");
		return NULL;
	}

	data = queue->cells[queue->head];

	queue->cells[queue->head] = NULL;
	queue->num_of_cells--;

	if (queue->num_of_cells == 0) 
	{
		queue->head = 0;
		queue->tail = 0;
	}
	else 
	{
		queue->head++;
		if (queue->head == THREAD_POOL_QUEUE_SIZE) 
		{
			queue->head = 0;
		}
	}

	return data;
}

///////////////////////////////////////////////////////////////////////////////
int ThreadPool::DoesQueueEmpty( TaskQueue *queue)
{
    if (queue->num_of_cells == 0) 
    {
        return 1;
    }

    return 0;
}

///////////////////////////////////////////////////////////////////////////////
int ThreadPool::GetQueueSize( TaskQueue *queue)
{
    return queue->num_of_cells;
}

///////////////////////////////////////////////////////////////////////////////
void ThreadPool::InitTask(Task *task)
{
	task->data = NULL;
	task->user_work = NULL;
}

///////////////////////////////////////////////////////////////////////////////
Task* ThreadPool::GetTask()
{
	Task* task;

	if (stop_flag) 
	{
		/* The pool should shut down return NULL. */
		return NULL;
	}

	/* Obtain a task */
	if (pthread_mutex_lock(&mutex)) 
	{
		perror("pthread_mutex_lock: ");
		return NULL;
	}

	while ( DoesQueueEmpty(& tasks_queue ) && !stop_flag) 
	{
		// wait until a new task arrives. 
		if (pthread_cond_wait(&cond,&mutex)) 
		{
			perror("pthread_cond_wait: ");
			if (pthread_mutex_unlock(&mutex)) 
			{
				perror("pthread_mutex_unlock: ");
			}

			return NULL;
		}
	}

	if (stop_flag) 
	{
		// The pool should shut down return NULL. 
		if (pthread_mutex_unlock(&mutex)) 
		{
			perror("pthread_mutex_unlock: ");
		}
		return NULL;
	}

	if ((task = (Task*)DequeueTask(&tasks_queue)) == NULL) 
	{
		REPORT_ERROR("Failed to obtain a task from the jobs queue.");
	}

	if (pthread_mutex_unlock(&mutex)) 
	{
		perror("pthread_mutex_unlock: ");
		return NULL;
	}

	return task;
}

///////////////////////////////////////////////////////////////////////////////
void* WorkerThreadRoutine(void *data)
{
	Task *task;

	while (1) 
	{
		task = pThisInstance->GetTask();

		if (task == NULL) 
		{
			if ( pThisInstance->stop_flag) 
			{
				// OK.Worker thr needs to exit (thread pool was shutdown). 
				break;
			}
			else 
			{
				// An error has occurred. 
				REPORT_ERROR("Warning an error has occurred when trying to obtain a worker task.");
				REPORT_ERROR("The worker thread has exited.");
				break;
			}
		}

		// Execute routine (if any). 
		if (task->user_work) 
		{
			task->user_work(task->data);
            //
            if (task->user_cb) 
            {
                task->user_cb ( task->callback_data );
            }

			// Release the task by returning it to the free_task_queue. 
			pThisInstance->InitTask(task);

			if (pthread_mutex_lock(&( pThisInstance-> free_tasks_mutex))) 
			{
				perror("pthread_mutex_lock: ");
				REPORT_ERROR("The worker thread has exited.");
				break;
			}

            //enqueue to free_tasks_queue
			if (pThisInstance->EnqueueTask(&( pThisInstance->free_tasks_queue),task)) 
			{
				REPORT_ERROR("Failed to enqueue a task to free tasks queue.");
				if (pthread_mutex_unlock(&(pThisInstance->free_tasks_mutex))) 
				{
					perror("pthread_mutex_unlock: ");
				}

				REPORT_ERROR("The worker thread has exited.");
				break;
			}

			if (pThisInstance->GetQueueSize(&(pThisInstance->free_tasks_queue)) == 1) 
			{
				// Notify all waiting threads that new tasks can added. 
				if ( pthread_cond_broadcast(&(pThisInstance->free_tasks_cond))) // free_tasks_cond 
				{
					perror("pthread_cond_broadcast: ");
					if (pthread_mutex_unlock(&(pThisInstance->free_tasks_mutex))) 
					{
						perror("pthread_mutex_unlock: ");
					}

					break;
				}
			}

			if (pthread_mutex_unlock(&(pThisInstance->free_tasks_mutex))) 
			{
				perror("pthread_mutex_unlock: ");
				REPORT_ERROR("The worker thread has exited.");
				break;
			}
		}


	}

	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
bool ThreadPool::Terminate()
{
	int i;
	stop_flag = 1;

	if (pthread_mutex_lock(&mutex)) 
	{
		perror("pthread_mutex_lock: ");
		REPORT_ERROR("Warning: Memory was not released.");
		REPORT_ERROR("Warning: Some of the worker threads may have failed to exit.");
		return false;
	}

	if (pthread_cond_broadcast(&cond)) 
	{
		perror("pthread_cond_broadcast: ");
		REPORT_ERROR("Warning: Memory was not released.");
		REPORT_ERROR("Warning: Some of the worker threads may have failed to exit.");
		return false;
	}

	if (pthread_mutex_unlock(&mutex)) 
	{
		perror("pthread_mutex_unlock: ");
		REPORT_ERROR("Warning: Memory was not released.");
		REPORT_ERROR("Warning: Some of the worker threads may have failed to exit.");
		return false;
	}

	for (i = 0; i < num_of_threads; i++) 
	{
		if (pthread_join(thr_arr[i],NULL)) 
		{
			perror("pthread_join: ");
		}
	}

	free(thr_arr);

	return false;
}

///////////////////////////////////////////////////////////////////////////////
bool ThreadPool::InitThreadPool()
{
	int i;
	stop_flag = 0;

	if (pthread_mutex_init(&free_tasks_mutex,NULL)) 
	{
		perror("pthread_mutex_init: ");
		return false;
	}
	
    if (pthread_mutex_init(&mutex,NULL)) 
	{
		perror("pthread_mutex_init: ");
		return false;
	}

	if (pthread_cond_init(&free_tasks_cond,NULL)) 
	{
		perror("pthread_mutex_init: ");
		return false;
	}
	
	if (pthread_cond_init(&cond,NULL)) 
	{
		perror("pthread_mutex_init: ");
		return false;
	}

	// Init the jobs queue. 
	InitQueue(&tasks_queue);

	// Init the free tasks queue. 
	InitQueue(&free_tasks_queue);

	// Add all the free tasks to the free tasks queue. 
	for (i = 0; i < THREAD_POOL_QUEUE_SIZE; i++) 
	{
		InitTask(tasks + i);

		if (EnqueueTask(&free_tasks_queue,tasks + i)) 
		{
			REPORT_ERROR("Failed to a task to the free tasks queue during initialization.");
			return false;
		}
	}

	// Create the thr_arr. 
	if ((thr_arr = (pthread_t*) malloc(sizeof(pthread_t) * num_of_threads)) == NULL) 
	{
		perror("malloc: ");
		return false;
	}

	// Start the worker threads. 
	for ( int i= 0; i < num_of_threads; i++) 
    {
		if (pthread_create(&(thr_arr[i]), NULL, WorkerThreadRoutine, NULL ) ) 
		{
			perror("pthread_create:");

			Terminate();

			return false;
		}
	}
    
    //cout << "all worker thread created..." << "\n";

	return true;
}

///////////////////////////////////////////////////////////////////////////////
int ThreadPool::AddTaskWithCallBack (
							WORK_FOR_WORKER_THREAD work_to_do, 
							void *data, 
							T_ADD_TASK blocking,
                            COMPLETED_CALLBACK cb ,
							void* callback_data
					    )
{
	Task *task;

	if (pthread_mutex_lock(&free_tasks_mutex)) 
	{
		perror("pthread_mutex_lock: ");
		return -1;
	}

	/* Check if the free task queue is empty. */
	while ( DoesQueueEmpty(&free_tasks_queue) ) 
	{
        //empty
		if (!blocking) 
		{
			// Return immediately 
			if (pthread_mutex_unlock(&free_tasks_mutex)) 
			{
				perror("pthread_mutex_unlock: ");
				return -1;
			}

			return -2;
		}

		// wait until free_tasks queue has a task to obtain. 
		if (pthread_cond_wait(&(free_tasks_cond),&(free_tasks_mutex))) 
		{
			perror("pthread_cond_wait: ");
			if (pthread_mutex_unlock(&(free_tasks_mutex))) 
			{
				perror("pthread_mutex_unlock: ");
			}

			return -1;
		}
	}

	// Obtain an empty task. 
	if ((task = (Task*)DequeueTask(&free_tasks_queue)) == NULL) 
	{
		REPORT_ERROR("Failed to obtain an empty task from the free tasks queue.");
		if (pthread_mutex_unlock(&free_tasks_mutex)) 
		{
			perror("pthread_mutex_unlock: ");
		}

		return -1;
	}

	if (pthread_mutex_unlock(&free_tasks_mutex)) 
	{
		perror("pthread_mutex_unlock: ");
		return -1;
	}

	task->data = data;
	task->user_work = work_to_do;
    task->user_cb = cb;
    task->callback_data = callback_data;

	// Add the task, to the tasks queue. 
	if (pthread_mutex_lock(&(mutex))) 
	{
		perror("pthread_mutex_lock: ");
		return -1;
	}

	if (EnqueueTask(&tasks_queue,task)) 
	{
		REPORT_ERROR("Failed to add a new task to the tasks queue.");
		if (pthread_mutex_unlock(&mutex)) 
		{
			perror("pthread_mutex_unlock: ");
		}
		return -1;
	}

	if ( GetQueueSize( & tasks_queue  ) == 1 ) 
	{
		// Notify all worker threads that there are new jobs. 
		if (pthread_cond_broadcast(&cond)) 
		{
			perror("pthread_cond_broadcast: ");
			if (pthread_mutex_unlock(&mutex)) 
			{
				perror("pthread_mutex_unlock: ");
			}

			return -1;
		}
	}

	if (pthread_mutex_unlock(&mutex)) 
	{
		perror("pthread_mutex_unlock: ");
		return -1;
	}

	return 0;
}


///////////////////////////////////////////////////////////////////////////////
/*
int ThreadPool::AddTask ( 
							WORK_FOR_WORKER_THREAD work_to_do, 
							void *data, 
							T_ADD_TASK blocking
					    )
{
	Task *task;

	if (pthread_mutex_lock(&free_tasks_mutex)) 
	{
		perror("pthread_mutex_lock: ");
		return -1;
	}

	while ( DoesQueueEmpty(&free_tasks_queue) ) 
	{
        //empty
		if (!blocking) 
		{
			// Return immediately 
			if (pthread_mutex_unlock(&free_tasks_mutex)) 
			{
				perror("pthread_mutex_unlock: ");
				return -1;
			}

			return -2;
		}

		// wait until free_tasks queue has a task to obtain. 
		if (pthread_cond_wait(&(free_tasks_cond),&(free_tasks_mutex))) 
		{
			perror("pthread_cond_wait: ");
			if (pthread_mutex_unlock(&(free_tasks_mutex))) 
			{
				perror("pthread_mutex_unlock: ");
			}

			return -1;
		}
	}

	// Obtain an empty task. 
	if ((task = (Task*)DequeueTask(&free_tasks_queue)) == NULL) 
	{
		REPORT_ERROR("Failed to obtain an empty task from the free tasks queue.");
		if (pthread_mutex_unlock(&free_tasks_mutex)) 
		{
			perror("pthread_mutex_unlock: ");
		}

		return -1;
	}

	if (pthread_mutex_unlock(&free_tasks_mutex)) 
	{
		perror("pthread_mutex_unlock: ");
		return -1;
	}

	task->data = data;
	task->user_work = work_to_do;

	// Add the task, to the tasks queue. 
	if (pthread_mutex_lock(&(mutex))) 
	{
		perror("pthread_mutex_lock: ");
		return -1;
	}

	if (EnqueueTask(&tasks_queue,task)) 
	{
		REPORT_ERROR("Failed to add a new task to the tasks queue.");
		if (pthread_mutex_unlock(&mutex)) 
		{
			perror("pthread_mutex_unlock: ");
		}
		return -1;
	}

	if ( GetQueueSize( & tasks_queue  ) == 1 ) 
	{
		// Notify all worker threads that there are new jobs. 
		if (pthread_cond_broadcast(&cond)) 
		{
			perror("pthread_cond_broadcast: ");
			if (pthread_mutex_unlock(&mutex)) 
			{
				perror("pthread_mutex_unlock: ");
			}

			return -1;
		}
	}

	if (pthread_mutex_unlock(&mutex)) 
	{
		perror("pthread_mutex_unlock: ");
		return -1;
	}

	return 0;
}
*/


