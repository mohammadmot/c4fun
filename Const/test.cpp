#include <iostream>
using namespace std;

// In this example we are going to exercise some codes about CONST keyword
int main()
{
    // Very normal way to use CONST is:
    {
        const int MAX = 100; // this means that we can change the value of MAX.
        // MAX = 10;        // if we do uncomment this, we get error say CONST content can not be changed.
    }
    // When we want to use CONST int pointers
    {
        // Normal pointer using
        int *p = new int;

        // it says you can change the content of p and works fine.
        *p = 2;

        // Or you can change the Address of p with &a. works fine.
        int a = 10;
        p = &a;

        // Now lets say you have pointer and we want to see how CONST keyword can affect on it.
        {
            // 1- put CONST keyword before int
            const int *p1 = new int;

            // You can not change the content of a pointer when its const int*.
            // *p1 = 10;
            // but you can change the Address of p1 as below:
            p1 = &a;
        }
        {
            // 2- put CONST keyword after int
            int const *p2 = new int;

            // still you can not change the CONTENT of p2 just like part 1
            // *p2 = 10; // compile error

            // but you can change the ADDRESS of p2
            p2 = &a;
        }
        {
            // 3- Put CONST keyword after * sign and before the name of variable
            int *const p3 = new int;

            // Now you can change the CONTENT of p3
            *p3 = 10;

            // but you can not change the ADDRESS of p3.
            // p3 = &a; // compile error

            // So, the result is: part 1 and 2 are the same and part 3 is the opposit.
            // It means tha putting CONST keyword before and after the '*' sign is the difference.
        }

        //
    }
    return 0;
}

// 4- Using const keyword in function defines and signatures
class CTest
{
public:
    CTest() = default;

    // putting const here makes sure that any class member variables can not be change in this function
    // Typically, we use const keyword as below in Get functions which basically makes it READONLY function
    int GetX() const
    {
        // m_y = 10; // compile error
        // m_x = 10;  // compile error
        return m_x;
    }

    // The return value format means: the CONTENT and the ADDRESS of m_z can not be modified in GetZ() function.
    const int *const GetZ() const
    {
        // m_y = 10; // compile error because function was made readonly by const keyword.
        // m_x = 10;  // compile error because function was made readonly by const keyword.
        return m_z;
    }

private:
    int m_x, m_y, *m_z;
};

void PrintTest(const CTest &t)
{
    // if GetX function was not const, the next line of code would produce compile error.
    cout << "the value of x: " << t.GetX();

    int a = 10;                        // normal variable
    const int *const pTemp = t.GetZ(); // use a temp pointer as m_z;

    // the following two lines of codes produce compile error because we can not change the CONTENT and the ADDRESS of pTemp
    // *pTemp = 2;
    // pTemp = &a;
    cout << "the value of z: " << t.GetZ();
}
