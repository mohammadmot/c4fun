/*
Virtual Destructors
Why to make base class destructor virtual, Modern Cpp Series
ref: https://www.youtube.com/watch?v=XvzgC5WoBCE
*/

#include <iostream>

using namespace std;

class Base
{
public:
    Base()
    {
        cout << "Base::ctor" << endl;
    }

    // with virtual, make call [Derived::dtor] :
    //      look further down our inheritance hierarchy call destructor
    // without virtual, don't call [Derived::dtor]
    virtual ~Base()
    {
        cout << "Base::dtor" << endl;
    }

    virtual void MemeberFunc()
    {
        cout << "Base::MemeberFunc" << endl;
    }
};

class Derived : public Base
{
public:
    Derived()
    {
        cout << "Derived::ctor" << endl;
    }

    ~Derived()
    {
        cout << "Derived::dtor" << endl;
    }

    void MemeberFunc() override
    {
        cout << "Derived::MemeberFunc" << endl;
    }
};

int main()
{
    cout << "--------------------" << endl;
    {
        // vTable create for this instance of the object
        Base *instance = new Derived();

        // when we call a member function, the vTable points us to the correct member function
        instance->MemeberFunc();
        instance->Base::MemeberFunc();

        delete instance;
        // delete[] instance; // nok!
    }
    cout << "--------------------" << endl;
    {
        Base *instance = new Base();
        instance->MemeberFunc();
        delete instance;
    }
    cout << "--------------------" << endl;
    /*
        cout << "--------------------" << endl;
        Derived ocObj;
        ocObj.MemeberFunc();
        cout << "--------------------" << endl;
    */

    return 0;
}