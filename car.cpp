#include <iostream>
using namespace std;

// abstract class = have to at least one pure virtual function
// concret class = has no pure virtual function

class CCar
{
private:
    int nWheels = 0;
    string strObjectType = "";

public:
    CCar(string strobjtype)
    {
        strObjectType = strobjtype;
        cout << strObjectType << " Object Created!\r\n";
    }
    ~CCar()
    {
        cout << strObjectType << " Object Destroyed!\r\n";
    }

    // pure virtual
    virtual bool CreateEngine() = 0;

    virtual void func()
    {
        cout << "Base Class Called!\r\n";
    }

    virtual int SetWheel(int nNum)
    {
        nWheels = nNum;
    }
    virtual int GetWheel()
    {
        return nWheels;
    }
};

class CBenz : public CCar
{
public:
    CBenz(string str) : CCar(str)
    {
        SetWheel(4);
    }

    // Error if this declaration was not here.
    bool CreateEngine() {};
    
    virtual void func()
    {
        cout << "Benz Func Called!\r\n";
    }
};

class CFord : public CCar
{
public:
    CFord(string str) : CCar(str)
    {
        SetWheel(4);
    }
    ~CFord()
    {
    }
    virtual bool CreateEngine(){};

    virtual void func()
    {
        cout << "Ford Func Called!\r\n";
    }
};

// vtable = virtual table map
// function_virtual | refrence have to body {...}

int main()
{
    // Static and Dynamic Memory Allocation
    {
        CBenz ocBenz("Static-Memory = Stack");
        ocBenz.func();
    }
    {
        CBenz *pBenz = new CBenz("Dynamic-Memory = Heap");
        if (pBenz)
            pBenz->func();
    }

    // Polymorphism
    CCar *pCars[2];
    pCars[0] = new CBenz("Dynamic");
    pCars[1] = new CFord("Dynamic");

    for (size_t i = 0; i < 2; i++)
    {
        if (pCars[i])
            pCars[i]->func();
    }

    return 0;
}