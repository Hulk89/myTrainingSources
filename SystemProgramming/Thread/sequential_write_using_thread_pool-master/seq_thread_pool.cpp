#include "seq_thread_pool.hpp"

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

#include <string.h> //memcpy

#ifdef _ASSERT_
int nAssertPreOut = -1; //for assertion
#endif

SeqentialWorkManager* pgThisInstance = NULL;
const int BUFFER_CNT = 1000;

int nLastWriteIndex    = -1;
int nWorkAssignIndex = 0;

#define EMPTY         'E'
#define COMPLETED     'C'
#define NOT_COMPLETED 'N'

void ThreadProc(void* arg) ;

bool gbRun = true;
//pthread_cond_t cb_invoked_cond ;
pthread_mutex_t gMutexMonitor = PTHREAD_MUTEX_INITIALIZER;
//pthread_mutex_t cb_invoked_mutex ;
char completed_index_array     [BUFFER_CNT];
ST_PER_WORK_INFO*  workDoneDataArray [ BUFFER_CNT ];

void* ThreadWriteProc(void* arg) ;
void pre_complete_cb ( void * p_work_data  ) ;
///////////////////////////////////////////////////////////////////////////////

SeqentialWorkManager::SeqentialWorkManager()
{
    ptb = NULL;
    pgThisInstance = this;
    failed_count = 0;
}

SeqentialWorkManager::~SeqentialWorkManager()
{
    if(gbRun)
    {
        gbRun = false;

        if (pthread_join( write_thread, NULL)) 
        {
            perror("pthread_join: ");
        }
        delete ptb;

        for (int i=  0; i < BUFFER_CNT; i++)
        {    
            delete workDoneDataArray[i];
            workDoneDataArray[i]= NULL;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
void SeqentialWorkManager::Terminate()
{
    gbRun = false;

    /*
	if (pthread_mutex_lock(&cb_invoked_mutex))
	{
		perror("pthread_mutex_lock: ");
		return ;
	}
    
	if ( pthread_cond_signal(&cb_invoked_cond) )
	{
		perror("pthread_cond_signal: ");
	}

	if (pthread_mutex_unlock(&cb_invoked_mutex))
	{
		perror("pthread_mutex_unlock: ");
	}
    */
    if (pthread_join( write_thread, NULL)) 
    {
        perror("pthread_join: ");
	}
    delete ptb;

    for (int i=  0; i < BUFFER_CNT; i++)
    {    
        delete workDoneDataArray[i];
        workDoneDataArray[i]= NULL;
    }
}

///////////////////////////////////////////////////////////////////////////////
int SeqentialWorkManager::GetNumberOfCpu ()
{
    int numCPU = sysconf( _SC_NPROCESSORS_ONLN );
    //cout << "\ncpu count: " << numCPU << "\n";
    return numCPU;
}

///////////////////////////////////////////////////////////////////////////////
bool SeqentialWorkManager::Init ( int nTotalCpu )
{
    if( nTotalCpu == 0 )
    {
        int numCPU = sysconf( _SC_NPROCESSORS_ONLN );
		if( numCPU > 24 )
		{
			cout << "set cpu count 24 " <<  "\n";
		    numCPU = 24 ; // Not to make too many thread context
		}
        ptb = new ThreadPool ( numCPU );
        cout << "cpu count: " << numCPU  <<  "\n";
    }
    else
    {
        ptb = new ThreadPool ( nTotalCpu );
    }

	/*
    if (pthread_mutex_init(& cb_invoked_mutex,NULL)) 
    {
        perror("pthread_mutex_init: ");
        return false;
    }
    if (pthread_cond_init(&cb_invoked_cond,NULL)) 
    {
        perror("pthread_mutex_init: ");
		return false;
    }
	*/
    for (int i = 0; i < BUFFER_CNT; i++)
    {    
        completed_index_array [i] = EMPTY;
    }

    for (int i = 0; i < BUFFER_CNT; i++)
    {    
        workDoneDataArray [i] = new ST_PER_WORK_INFO;
    }

    if (pthread_create( &write_thread, NULL, ThreadWriteProc, NULL ) ) 
    {
        perror("pthread_create:");
        return false;
    }
    failed_count = 0;

    return true;
}
///////////////////////////////////////////////////////////////////////////////

void* ThreadWriteProc(void* arg) 
{
    pgThisInstance->nTotalOut = 0;

    while(1)
    {
        if( false == gbRun )
        {
		    //exit check
            bool nNotCompletedFound = 0;
            for(int i = 0; i < BUFFER_CNT; i ++ )
            {
                scoped_lock guard (&gMutexMonitor); 
                if ( NOT_COMPLETED == completed_index_array [i] )
                {
				    nNotCompletedFound = true;
				    break;
                }
            }

            if( nNotCompletedFound == false )
            {
                //cout << "ThreadWriteProc Exit!" << "\n";
                int nFromIndex = nLastWriteIndex + 1;
                char cStatus;

                for (int k = 0; k < 2; k ++ ) //loop 2 times will cover all arrary
                {
                    for(int i = nFromIndex; i < BUFFER_CNT; i ++ )
                    {
                        { //20130915
                        scoped_lock guard (&gMutexMonitor); 
                        cStatus = completed_index_array [i] ;
                        }

                        if ( COMPLETED == cStatus )
                        {
                            pgThisInstance->nTotalOut++;
                            workDoneDataArray[i]->final_completed_cb( workDoneDataArray[i]->n_seq,  
                                                                      workDoneDataArray[i]->data );

                            { //20130915
                            scoped_lock guard (&gMutexMonitor); 
                            completed_index_array [i] = EMPTY; //reset
                            }

                            if( i == BUFFER_CNT -1 )
                            {
                                nLastWriteIndex = -1 ;
                                break;
                            }
                            else
                            {
                                nLastWriteIndex = i ;
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                break;
            } //if( nNotCompletedFound == false )
            usleep(10);
        }
        else
        {
            /////////////////////////////////////////////
			/*
            if (pthread_mutex_lock(&cb_invoked_mutex)) 
            {
                perror("pthread_mutex_lock: ");
				return NULL ;
            }

            if ( pthread_cond_wait( &cb_invoked_cond, &cb_invoked_mutex) ) 
            {
                perror("pthread_cond_wait: ");
                if (pthread_mutex_unlock(&(cb_invoked_mutex))) 
                {
                    perror("pthread_mutex_unlock: ");
                }

                return NULL;
            }

            if (pthread_mutex_unlock(&(cb_invoked_mutex))) 
            {
				perror("pthread_mutex_unlock: ");
            }
            */
            /////////////////////////////////////////////
            int nFromIndex = nLastWriteIndex + 1;
            char cStatus;

            for(int i = nFromIndex; i < BUFFER_CNT; i ++ )
            {
                { //20130915
                scoped_lock guard (&gMutexMonitor); 
                cStatus = completed_index_array [i];
                }

                if ( COMPLETED == cStatus )
                {
                    pgThisInstance->nTotalOut++;

                    workDoneDataArray[i]->final_completed_cb(workDoneDataArray[i]->n_seq,  
                                                             workDoneDataArray[i]->data );

                    { //20130915
                    scoped_lock guard (&gMutexMonitor); 
                    completed_index_array [i] = EMPTY; //reset
                    }

                    #ifdef _ASSERT_
                    if( nAssertPreOut >= i )
                    {
                        cout << " !!!!!! Write Data ERROR !!! " << "\n";
                        return NULL;
                    }
                    nAssertPreOut = i;
                    #endif

                    if( i == BUFFER_CNT -1 )
                    {
                        nLastWriteIndex = -1 ;

                        #ifdef _ASSERT_
                        nAssertPreOut = -1; 
                        #endif
                        break;
                    }
                    else
                    {
                        nLastWriteIndex = i ;
                    }
                }
                else
                {
                    break;
                }
            }

            usleep (1);
         }
    }

    return NULL;
}
           


/////////////////////////////////////////////////////////////////
void pre_complete_cb ( void * p_work_data  ) 
{
    ST_PER_WORK_INFO* pData = (ST_PER_WORK_INFO*) p_work_data;

    workDoneDataArray [pData->n_seq] =  pData;

    {
        scoped_lock guard (&gMutexMonitor); 
        completed_index_array[pData->n_seq] = COMPLETED; //mark as completed
    }

    /*
	if (pthread_mutex_lock(&cb_invoked_mutex)) 
    {
        perror("pthread_mutex_lock: ");
        return ;
    }

    if ( pthread_cond_signal(&cb_invoked_cond) ) 
    {
        perror("pthread_cond_signal: ");
    }

    if (pthread_mutex_unlock(&cb_invoked_mutex)) 
    {
        perror("pthread_mutex_unlock: ");
    }
	*/
}

///////////////////////////////////////////////////////////////////////////////
void SeqentialWorkManager::AssignWork( WORK_PROCESS work_process, 
                                       void* work_data, 
                                       int nLen, 
                                       WORK_COMPLETED_CALLBACK call_back )
{
    char status ='U';

    while(1)
	{

        { //make lock local scope
            scoped_lock guard (&gMutexMonitor); 
            status = completed_index_array [ nWorkAssignIndex ] ;
        } //make lock local scope

        if( status != EMPTY )
        {
            //cout << "completed_index_array is FULL...: " << "\n" ; //debug
            usleep(1);
        }
        else
        {
            break;
        }
    }
	
    workDoneDataArray [nWorkAssignIndex]->n_seq =  nWorkAssignIndex ;
    workDoneDataArray [nWorkAssignIndex]->data  =  work_data ; //data
    workDoneDataArray [nWorkAssignIndex]->final_completed_cb = call_back;

    {
        scoped_lock guard (&gMutexMonitor); 
        completed_index_array [nWorkAssignIndex] = NOT_COMPLETED; 
    }

    int ret = ptb->AddTaskWithCallBack( work_process, 
                            workDoneDataArray [nWorkAssignIndex]->data ,
                            BLOCKING , 
                            pre_complete_cb,
                            workDoneDataArray [nWorkAssignIndex]  ); //20130819

    if (ret == -1) 
    {
        printf("An error had occurred while adding a task.");
        exit(EXIT_FAILURE);
    }
    if (ret == -2) 
    {
        cout << "Add task failed!" << "\n";
        failed_count++;
    }

    nWorkAssignIndex ++;


    if(nWorkAssignIndex == BUFFER_CNT )
    {
        nWorkAssignIndex = 0;
    }
}
