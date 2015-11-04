#include <iostream>
#include <vector>

using namespace std;
void printVector( vector<double> ret );

int main()
{
    int i;
    int j;
    //double template
    vector<double> ret;

    i = j = 0;

    cout << "insertion test" << endl;
    for ( i = 0 ; i < 10 ; i++ )
    {
        ret.push_back((double)(i)/10.0);
    }
    printVector( ret );

    cout << "popBack" << endl;
    for ( i = 0 ; i < 10 ; i++ )
    {
        ret.pop_back();
    }
    printVector( ret );

    cout << "isEmpty? : " << ret.empty() << endl;
    
    return 0;
}


void printVector( vector<double> ret )
{
    int i;
    for ( i = 0 ; i < ret.size() ; i++ )
    {
        cout << "return : " << ret.at(i) << endl;
    }
}
