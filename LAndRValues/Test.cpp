#include <iostream>
using namespace std;

// In this code, we want to explain what the
// LValue and RValue are

// In most cases, the expressions in the left side of
// '=' operation called LValue and the right side called
// RValue. But there is some cases that this rule dose not hold.

// Go to main function first...

int GetValue_0()
{
    return 10;
}
int &GetValue_1()
{
    static int var = 10;
    return var;
}

void SetValue_0(int &var)
{
    // do something...
}
void SetValue_1(const int &var)
{
    // do something...
}
void PrintValue_0(std::string &name)
{
    cout << name << endl;
}
void PrintValue_1(const std::string &name)
{
    cout << name << endl;
}
void PrintValue_2(std::string &&name)
{
    cout << name << endl;
}

int main()
{
    // 1- Most of the times, RValues also called Temporary expresion.
    {
        int a = 10; // 'a' is lvalue and '10' is rvalue.
                    // 'a' has location address and can reference
                    // to another variables. '10' is a temporary value
                    // and dose not have any location address.

        // 10 = a;     // This line of code produces a compile error because
        // '10' is not a lvalue.

        int b = a; // In this line, both 'b' and 'a' are lvalues
                   // and compiles fine.
    }
    // 2- rvalues are not always temporarily expressions.
    // It can be also functions.
    {
        int a = GetValue_0(); // In this line, GetValue_0() returns rvalue
                              // because it returns a temporary value 10;

        // This line of code produces a compile error because its a rvalue and can not be used as lvalue.
        // GetValue_0() = 20;

        // But if we change GetValue_0() in order to use as lvalue expresion,
        // we have to return lvalue_reference just like GetValue_1() function

        GetValue_1() = 20; // This line works fine, because GetValue_1() returns
                           // lvalue expresion and its like (var = 20);
    }
    // 3- Lvalue Reference:
    // How can be used lvalue and rvalue expressions in a function
    {
        int a = 10;
        SetValue_0(a); // SetValue_0(var) function takes only lvalue parameter.
        // SetValue_0(10); // This line produces a compile error because '10' is rvalue
        // and can not be used as lvalue expression.

        // In order to fix SetValue_0(10) compile error, the function must be changed
        // in a way that takes both lvalue and rvalue.
        // SetValue_1(var) changes by adding 'const' keyword before int& var.
        // SO, WITH MAKING LVALUE REFERENCE (e.g int& var) FROM AN EXPRESSION,
        // WE CAN DETERMINE IF THE EXPRESSION IS LVALUE OR RVALUE.

        // So the main rule is: WE 'CAN NOT' TAKE LVALUE REFERENCE FROM RVALUE.

        // But there is an exception:
        // By adding 'const' keyword before 'lvalue reference expression', we can
        // make a rvalue (like '10' as below) work fine.

        SetValue_1(a); //  lvalue call which works fine.

        SetValue_1(10); // This line works fine. Thats why functions are mainly
                        // written with const lvalue reference (e.g const int& var)
                        // as input parameter.
    }
    {
        // String example
        // In the example below, fname, lname and fullname are lvalue variables.
        // And the right side all are rvalue expressions.
        std::string fname = "name";
        std::string lname = "lastname";
        std::string fullname = fname + lname;

        // Works fine because its lvalue.
        PrintValue_0(fullname);

        // PrintValue_0(fname + lname);
        // Produces a compile error because 'fname + lname' is a rvalue or temporary expression.

        // To fix the above compile error, need to add const keyword before lvalue reference.
        PrintValue_1(fname + lname);

        // RValue Reference:
        // Is there any way that only can be used for rvalue or temporary expressions?
        // Yes. Rvalue Reference is the answer.

        // Produces a compile error because fullname is lvalue and con not be used
        // in PrintValue_2(...) which takes only rvalues or temporaries.

        // PrintValue_2(fullname);

        // Works fine because 'fname + lname' is temporary or rvalue.
        // This is called 'rvalue reference' which is used only for
        // temporary expressions. This usage only 'Moves' the temporary
        // values instead of 'copying' which is very useful in MoveSemantics, Move Constructors and
        // Move Assignments.
        PrintValue_2(fname + lname);
    }
}