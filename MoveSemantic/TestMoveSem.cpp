using namespace std;
#include <iostream>
#include <memory.h>
class CStringEx
{
public:
    CStringEx() = default;
    CStringEx(const char *data)
    {
        printf("Created!\n");
        m_nSize = strlen(data);
        m_pData = new char[m_nSize];
        memcpy(m_pData, data, m_nSize);
    }
    CStringEx(const CStringEx &other)
    {
        printf("Copied\n");
        m_nSize = other.m_nSize;
        m_pData = new char[m_nSize];
        memcpy(m_pData, other.m_pData, m_nSize);
    }
    CStringEx(CStringEx &&other)
    {
        printf("Moved!\n");
        m_nSize = other.m_nSize;
        m_pData = other.m_pData;
        other.m_nSize = 0;
        other.m_pData = nullptr;
    }
    ~CStringEx()
    {
        printf("Destroyed!\n");
        delete m_pData;
    }
    void Print()
    {
        cout << "Printed Value: ";

        for (int nI = 0; nI < m_nSize; nI++)
            printf("%c", m_pData[nI]);
        printf("\n");
    }

private:
    int m_nSize;
    char *m_pData;
};

class CLogger
{
public:
    CLogger(const CStringEx &log)
        : m_strLog(log)
    {
    }
    CLogger(CStringEx &&log)
        : m_strLog(std::move(log))
    {
    }
    void Print()
    {
        m_strLog.Print();
    }

private:
    CStringEx m_strLog;
};

int main()
{
    CLogger logger(CStringEx("MoveSemantic"));
    logger.Print();
    return 0;
}