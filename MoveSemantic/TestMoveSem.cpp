// Move Semantics in C++
// ref: https://www.youtube.com/watch?v=ehMg6zvXuMY
// ref: https://www.youtube.com/watch?v=OWNeCTd7yQE

using namespace std;

#include <iostream>
#include <memory.h>
#include <cstring>

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

    // copy constructor = [Depp copy] = allocating new memory
    CStringEx(const CStringEx &other)
    {
        printf("Copied\n");
        m_nSize = other.m_nSize;
        m_pData = new char[m_nSize];
        memcpy(m_pData, other.m_pData, m_nSize);
    }

    // move constructor, [Shallow copy] = optimize = just kind [rewired the pointers]
    CStringEx(CStringEx &&other) // [&&] R-Value reference, is that temporary
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

    // assignment operator, transfer the ownership the array of characters
    // without any copy or allocate memory, [just switched]
    CStringEx &operator=(CStringEx &&other) noexcept
    {
        cout << "Move! with[=]operator" << endl;
        if (this != &other)
        {
            delete[] m_pData;

            m_nSize = other.m_nSize;
            m_pData = other.m_pData;

            other.m_nSize = 0;
            other.m_pData = nullptr;
        }

        return *this;
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
    CLogger(CStringEx &&log) // R-Value call this, take string as a temporary here
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
    std::cout << "------------------ copy string" << std::endl;
    {
        CStringEx str_1 = "mohammd";
        CStringEx str_2 = str_1;
    }
    std::cout << "------------------ copy string" << std::endl;
    {
        CStringEx str_1 = "mohammd";
        CStringEx str_2(str_1);

        std::cout << "str_1: ";
        str_1.Print();
        std::cout << "str_2: ";
        str_2.Print();
        std::cout << std::endl;
    }
    std::cout << "------------------ moving with &&" << std::endl;
    {
        CStringEx str_1 = "mohammd";
        CStringEx str_2((CStringEx &&) str_1); // [moving] string into another string

        std::cout << "str_1: ";
        str_1.Print();
        std::cout << "str_2: ";
        str_2.Print();
        std::cout << std::endl;
    }
    std::cout << "------------------ moving with std::move" << std::endl;
    {
        CStringEx str_1 = "mohammd";
        CStringEx str_2(std::move(str_1)); // [moving] string into another string

        std::cout << "str_1: ";
        str_1.Print();
        std::cout << "str_2: ";
        str_2.Print();
        std::cout << std::endl;
    }
    std::cout << "------------------ use operator[=]" << std::endl;
    {
        // transfer the ownership the array of characters
        CStringEx strApple = "Apple";
        CStringEx strDest;
        strDest = std::move(strApple);
    }

    std::cout << "------------------" << std::endl;
    // [2].
    // we want only allocated memory once = single allocation
    // and move the string into class
    {
        CLogger logger0("TEST-Main");
    }
    std::cout << "------------------" << std::endl;
    {
        CLogger logger(CStringEx("MoveSemantic")); // R-Value reference, is that temporary
        logger.Print();
    }

    return 0;
}