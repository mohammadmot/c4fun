#include <iostream>
#include <string>

#include <vector>
#include <memory>

using namespace std;

struct X
{
    int m;
    // ..
};

int main()
{
    int n = 10;
    unique_ptr<X> p1(new X[n]); //
    unique_ptr<X> p2(new X[n]); //
    vector<X> v(n);

    // ref: https://stackoverflow.com/questions/22757412/stdunique-ptr-with-array-pointer
    // You have to correctly specify the type the unique_ptr will be holding
    // for it to work correctly:
    std::unique_ptr<X[]> ptr(new X[100]);
    // This will default to a deleter that uses delete[] instead of delete.

    // ptr.reset();
    cout << ptr.get() << endl;

    // ...

    return 0;
}
