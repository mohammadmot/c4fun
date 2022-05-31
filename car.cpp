#include <iostream>
using namespace std;
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
    virtual bool CreateEngine(){}; // Error if this declaration was not here.
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

int main()
{
    // Static and Dynamic Memory Allocation
    {
        CBenz ocBenz("Static");
        ocBenz.func();
    }
    {
        CBenz *pBenz = new CBenz("Dynamic");
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