#include <iostream>
using namespace std;
int setvalue(const int &n)
{
    cout << "the value is " << n;
}
int main()
{
    const int a1 = 10;
    const int &a = a1;
    int n = 10;
    setvalue(n);
    setvalue(10);

    return 0;
}