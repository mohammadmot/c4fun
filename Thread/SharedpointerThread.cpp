// compile: g++ -std=c++14 .\SharedpointerThread.cpp -lpthread
 
#include <memory>
#include <thread>
#include <iostream>

using namespace std;

class Foo
{
    int x;

public:
    Foo(int x) : x{x} {}
    int getX() { return x; }
    ~Foo() { cout << "~Foo" << endl; }
};

void Func(std::shared_ptr<Foo> sp)
{
    cout << "func: " << sp.use_count() << endl;
}

int main()
{
    std::shared_ptr<Foo> sp(new Foo(100));

    thread t1(Func, sp), t2(Func, sp), t3(Func, sp);
    cout << "main: " << sp.use_count() << endl;

    return 0;
}