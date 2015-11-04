#include <iostream>
#include <string>
#include <sstream>

#include "seq_thread_pool.hpp"

//스레드 풀에서 수행되는 작업에 필요한 사용자 데이터 정의
typedef struct _ST_USER_WORK_DATA
{
    int n_work_time;
    string work_data;
} ST_USER_WORK_DATA ;


//스레드풀에서 처리될 스레드 함수를 정의한다. 즉, 사용자가 수행할 작업을 의미.
void MyThreadProc(void* arg) 
{
    ST_USER_WORK_DATA* pUserData = (ST_USER_WORK_DATA*)arg;

    //전달된 데이터를 가지고 작업을 수행한다.
    //여기서는 작업부하를 usleep 호출로 시뮬레이트한다.
    usleep( pUserData->n_work_time ); 
    pUserData->work_data = pUserData->work_data + " : done! ";
}

//스레드 풀에서 처리된 최종 결과가 전달되는 함수를 정의한다.
//이함수는 스레드풀 순차적 처리 관리자에게 요청한 순서대로 순차적으로 호출된다.
void WorkDoneCallBack (int nSeq, void* data)
{
    ST_USER_WORK_DATA* pData = (ST_USER_WORK_DATA*)data;
    cout << "/" << pData->work_data << "\n";

    delete pData; //최종적으로 사용이 끝난 작업 데이터를 삭제.
    pData = NULL;
}

//사용자의 호출 부분
int main()
{
    //스레드풀 순차적 처리 관리자 객체를 선언.
    SeqentialWorkManager* pSeqManager = new SeqentialWorkManager ();

    if( ! pSeqManager->Init() ) //초기화
    {
        cout << "Error : Init" << "\n";
        return -1;
    }

    ostringstream variable;
    variable << 1 ; 

    //전달할 작업 데이터를 준비한다
    ST_USER_WORK_DATA* pData1 = new ST_USER_WORK_DATA;
    pData1->work_data = variable.str(); //data
    pData1->n_work_time = 1000; 
    
    pSeqManager->AssignWork( MyThreadProc, pData1, sizeof(ST_USER_WORK_DATA),  WorkDoneCallBack );

    variable.seekp(0);
    variable << 2 ; 
    ST_USER_WORK_DATA* pData2 = new ST_USER_WORK_DATA;
    pData2->work_data = variable.str(); //data
    pData2->n_work_time = 100; 
    
    pSeqManager->AssignWork( MyThreadProc, pData2, sizeof(ST_USER_WORK_DATA),  WorkDoneCallBack );

    variable.seekp(0);
    variable << 3 ; 
    ST_USER_WORK_DATA* pData3 = new ST_USER_WORK_DATA;
    pData3->work_data = variable.str(); //data
    pData3->n_work_time = 10; 
    
    pSeqManager->AssignWork( MyThreadProc, pData3, sizeof(ST_USER_WORK_DATA),  WorkDoneCallBack );

    pSeqManager->Terminate();
    delete pSeqManager;
    return 0;
}
