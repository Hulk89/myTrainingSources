#include <iostream>
#include <list>

using namespace std;

/*
지원하는 함수들
    pop_back
    push_back
    push_front
    rbigin
    rend
    bigin
    end

    front
    back
    clear
    empty
    size
    insert
    erase
    remove
    remove_if
    sort
*/
int main()
{
    list<int> integerList;
    list<int>* intPtrList = new list<int>;

    integerList.push_front(1);
    integerList.push_front(2);
    integerList.push_front(3);
    integerList.push_front(4);
    integerList.push_front(5);
    integerList.push_front(4);
    integerList.push_front(3);
    integerList.push_front(2);
    integerList.push_front(1);
    
    cout << " front of integerList : " << (int)integerList.front() << endl; 
   
    list<int>::iterator iterEnd = integerList.end();
    for ( list<int>::iterator iterPos = integerList.begin() ; 
          iterPos != iterEnd ;
          iterPos++ )
    {
        cout << " integer : " << *iterPos << endl;
    }
    integerList.pop_front();
    

    cout << " front of integerList : " << (int)integerList.front() << endl; 
    return 0;
}

