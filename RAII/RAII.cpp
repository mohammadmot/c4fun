#include <stdio.h>
#include <iostream>
#include <memory>

using namespace std;

// ===============================================
class Collection
{
private:
    int *data;

public:
    Collection()
    {
        data = new int[10];
        // fopen(); or ...

        try
        {
            throw 11;
        }
        catch (int ex)
        {
            cout << "Error Message: " << ex << endl;
        }
    }

    virtual ~Collection() // free the resources inside destructor
    {
        cout << "destructor is still called !" << endl;
        delete[] data;
    }

    // operator
    int &operator[](std::size_t index)
    {
        return data[index];
    }

    const int &operator[](std::size_t index) const
    {
        return data[index];
    }
};

// ===============================================
// ok resource management done by a handle
void Function(int i)
{
    auto ptr = make_unique<int[]>(12);
    // ...
    if (i < 17)
    {
        cout << "exception in Function" << endl;
        throw "exception in Function";
    }
    // ...
}

// ===============================================
int main()
{
    Function(20);

    Collection myCollection;
    myCollection[0] = 1;
    myCollection[1] = 2;
    myCollection[2] = 3;

    cout << myCollection[0] << endl;
}