#include <iostream>
#include <queue>

using namespace std;
class T {
    public:
	int a;

    T()
    {
	a = 10;
    }
   ~T()
    {
	a = 0;
    }
};


int main()
{
    std::queue<T> q;
    T *a = new T;

    a->a = 10;

    printf("%p\n",a);
    q.push(*a);

    free(a);
    a = &(q.front());
    
    printf("%p\n",a);
    std::cout << a->a << endl;

    q.pop();
    std::cout << a->a << endl;;
    return 0;
}    
