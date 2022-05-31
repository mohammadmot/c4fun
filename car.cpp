class CCar
{
private:
    int nWheels = 0;

public:
    CCar();

    // pure virtual
    virtual bool CreateEngine() = 0;
    virtual bool CreateEngine() = 0;

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
    CBenz()
    {
        int nNumWheels = SetWheel(4);
    }

    // ...
};

int main()
{
    CBenz ocBenz = new CBenz();

    return 0;
}