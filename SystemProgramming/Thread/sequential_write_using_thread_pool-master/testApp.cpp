#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <iostream>
#include <string>
#include <sstream>

#include "ElapsedTimer.hpp"
#include "seq_thread_pool.hpp"

using namespace std; 

double pool_elapsed =  0;
double nothread_elapsed =  0;
const int WORK_TIME_SHORT = 10;
const int WORK_TIME_LONG  = 300;
const int CNT_TEST         = 1000;

typedef void (*COMPLETED_CALLBACK)( void* ) ; 

typedef struct _ST_USER_WORK_DATA
{
    int n_work_load;
    string work_data;
} ST_USER_WORK_DATA ;


SeqentialWorkManager* pSeqManager ;
////////////////////////////////////////////////////////////////////////
void no_thread_test()
{
    ElapsedTimer et ;
    et.start();
    int nToggle = 1;
    int nTestCnt = 0;
    char szTemp[10];
    for ( int i = 0; i < CNT_TEST; i++ )
    {
        int nSleep = ( nToggle > 0) ? WORK_TIME_SHORT: WORK_TIME_LONG ;
        usleep(nSleep); 
        snprintf( szTemp, sizeof(szTemp), "%d", i );

        cout << "/" << szTemp ; 
        nToggle = nToggle * -1;

        nTestCnt++;
    }
    cout << "\nTest done: " << nTestCnt << "\n";
    nothread_elapsed =  et.stop();
    cout << "no thrad elapsed: " << nothread_elapsed << "\n";
}


////////////////////////////////////////////////////////////////////////
// thread work
void MyThreadProc(void* arg) 
{
    ST_USER_WORK_DATA* pUserData = (ST_USER_WORK_DATA*)arg;

    //------------------------------------------------
    //some work..
    //cout << "usleep : " << pUserData->n_work_load << "\n";
    usleep( pUserData->n_work_load ); 
    //do whatever with your data
    //pUserData->work_data = pUserData->work_data + "-Done!" ;
    //------------------------------------------------ 
}

///////////////////////////////////////////////////////////////////////////////
// invoked sequentially after works done.
void WorkDoneCallBack (int nSeq, void* data)
{
    ST_USER_WORK_DATA* pData = (ST_USER_WORK_DATA*)data;
    cout << "/" << pData->work_data ;

    delete pData; //XXX
    pData = NULL;
}


///////////////////////////////////////////////////////////////////////////////
void thread_pool_test()
{
    pSeqManager = new SeqentialWorkManager ();
    if( ! pSeqManager->Init() )
    {
        cout << "Error : Init" << "\n";
        return;
    }

    int nTotalWorkAssigned = 0;
    int nToggle = 1;

    ElapsedTimer et ;
    et.start();

    while(1)
	{
        int nSleep = ( nToggle > 0) ? WORK_TIME_SHORT: WORK_TIME_LONG ;
        nToggle = nToggle * -1;
        ostringstream variable;
        variable << nTotalWorkAssigned ; 

        ST_USER_WORK_DATA* pData = new ST_USER_WORK_DATA;

        pData->work_data = variable.str(); //set data
        pData->n_work_load = nSleep ;
        pSeqManager->AssignWork( MyThreadProc, pData, sizeof(ST_USER_WORK_DATA),  WorkDoneCallBack );

        nTotalWorkAssigned++;

        if( nTotalWorkAssigned == CNT_TEST ) //for loop exit
        {
            pSeqManager->Terminate();

            cout << "\nTest done: " << nTotalWorkAssigned << "  nTotalOut: "<< pSeqManager->nTotalOut <<"\n";
            break;
        }

    } //while

    pool_elapsed =  et.stop();
    cout << "pool :" << pool_elapsed << ": " <<  ": failed: "  << pSeqManager->failed_count << "\n";

    delete pSeqManager;
}

////////////////////////////////////////////////////////////////////////

int main()
{
    //no thread
    no_thread_test();

    //thread pool
    thread_pool_test();

    cout << "\n\n";
    cout << "--------------------------------------------------------------------\n";
    cout << "WORK_TIME_SHORT :" << WORK_TIME_SHORT << "\n";
    cout << "WORK_TIME_LONG  :" << WORK_TIME_LONG  << "\n";
    cout << "loop cnt : " << CNT_TEST << "\n";
    cout << "<elapsed sec.> using no thread   : " << nothread_elapsed  << "\n";
    cout << "<elapsed sec.> using thread pool : " << pool_elapsed << "\n";
    cout << "--------------------------------------------------------------------\n";
    cout << "performance ratio (nothread_elapsed / pool_elapsed): " << nothread_elapsed / pool_elapsed << "\n\n\n";
    
    return 0;
}
