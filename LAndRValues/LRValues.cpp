/*
L-Value: locator values, some kind of location as well as
*/

#include <iostream>

// GetValue function return an R-Value or Temporary value,
// because just return value 10
// it has no location, no storage
// just returning the value 10
int GetValue()
{
    return 10;
}

// in this case pretending an L-Value reference
int &GetValue2()
{
    static int value = 10;
    return value;
}

//
void SetValue(int value)
{
}

//
void SetValue2(int &value)
{
}

// accept both type of data L-Value and R-Value
void SetValue3(const int &value)
{
}

// accept just L-Value
void PrintName(std::string &name)
{
    std::cout << name << std::endl;
}

// accept R-Value with [const &]
void PrintName2(const std::string &name)
{
    std::cout << name << std::endl;
}

// accept R-Value with [&&] , that only accept temporary objects
void PrintName3(std::string &&name)
{
    std::cout << name << std::endl;
}

// accept 2 type of L-Value and R-Value with function overloading function
// PrintName4(&) and PrintName4(&&)
void PrintName4(std::string &name)
{
    std::cout << name << std::endl;
}
void PrintName4(std::string &&name)
{
    std::cout << name << std::endl;
}

int main()
{
    // [1].
    // L-Value = R-Value
    // L-Value actual variable with a location in memory
    // R-Value simply a value just a numeric literal it's just 10,
    //   with no storage it has no location until it is assigned to L-Value i
    //   you can't assign something to R-Value and I can't say (10 = i)
    //   because 10 has no location to store data
    int i = 10;

    // [2].
    // L-Value = L-Value
    int a = i;

    // [3].
    // GetValue function return temporary value, just 10, without location
    // L-Value = R-Value
    int j = GetValue();

    // [4].
    // R-Value could not assign a value
    // this expression must be a modifiable L-Value
    // L-Value: modifiable meaning has to be non const
    // !!! R-Value = R-Value
    // !!! GetValue() = 5;

    // [5].
    // L-Value = R-Value
    GetValue2() = 5;

    // [6].
    // call function with L-Value and R-Value
    int aa = 10;
    SetValue(aa);
    SetValue(5);

    // [7].
    // call function with L-Value , not R-Value
    int aaa = 10;
    SetValue2(aaa);
    // !!! SetValue2(5); // initial value of reference to non-const be an L-Value

    // [8].
    // it's ok: const L-Value reference
    const int &iA = 10;
    // because compiler create temp variable to assigned this
    // like:
    // int temp = 10;
    // const int& iA = temp;

    // [9].
    // accept both type of data L-Value and R-Value
    // because a const L-Value reference, can accept both
    int bb = 5;
    SetValue3(bb);
    SetValue3(10);

    // [10].
    // L-Value = R-Value
    // R-Values: temporary object or temporary string
    //  "mohammad"
    //  "motieian"
    //  firstName + lastName
    std::string firstName = "mohammad";
    std::string lastName = "motieian";
    std::string fullName = firstName + lastName;

    // [11].
    // could not assign R-Value to function with [&]
    PrintName(firstName);
    PrintName(lastName);
    // not work because it is R-Value: firstName + lastName
    // error: cannot bind non-const lvalue reference of type to an rvalue of type
    // !!! PrintName(firstName + lastName);

    // [12].
    // could assign R-Value to function with [const &]
    PrintName2(firstName + lastName);

    // [13].
    // L-Value?
    // writing an L-Value reference that's non const an L-Value reference
    // can only accept L-Value, this will not compile because of course
    // it's an R-Value.
    //
    // Do we have a way to write a function that only accepts temporary objects?
    // Yes. for that we need to create R-Value reference and it's looks the same
    // as L-Value reference only with two & [&&] , instead of one & [&]
    PrintName3(firstName + lastName);
    // !!! PrintName3(firstName); // error : cannot bind rvalue reference of type to lvalue of type

    // [14].
    // accept L-Value with PrintName4(&)
    // accept R-Value with PrintName4(&&)
    PrintName4(firstName + lastName);
    PrintName4(firstName);

    // Finally:
    //   you can't take an L-Value reference from an R-Value
    //   you can only have a L-Value reference of an L-Value
    //
    //   R-Value is temporary
    //   L-Value is variable and have storage in them
    //
    //   L-Value references accept L-Value unless const
    //   R-Value references can only take temporary R-Values
    //
    //   You can take/steal from temporary R-Values
    //   but you can't take/steal from L-Values

    return 0;
}
