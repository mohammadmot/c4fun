// C++: Smart Pointers and how to write your own
/*
One of the peculiar things of C++ language is dynamic memory management.
Unlike Java or C#, C++ doesn’t have an inbuilt Garbage Collector.
[Bjarne Stroustrup], the creator of C++, was asked, 
“Why doesn’t C++ have garbage collection?”. 
His answer is, “I don’t like garbage. I don’t like littering.
My ideal is to eliminate the need for a garbage collector by not producing any garbage”. This is true in the sense that C++ itself doesn’t create any garbage, it’s the developer who creates garbage. So it is their responsibility to manage (deallocate) the dynamically allocated memory. Pointers are a way to access heap memory. But the problem with pointers is that they are prone to cause memory leakage in a program.
*/

#include <iostream>  //main header
using namespace std; // namespace

template <class T>
class my_unique_ptr
{
private:
    T *ptr = nullptr;

public:
    my_unique_ptr() : ptr(nullptr) // default constructor
    {
    }

    my_unique_ptr(T *ptr) : ptr(ptr)
    {
    }

    my_unique_ptr(const my_unique_ptr &obj) = delete;            // copy constructor is deleted
    my_unique_ptr &operator=(const my_unique_ptr &obj) = delete; // copy assignment is deleted

    my_unique_ptr(my_unique_ptr &&dyingObj) // move constructor
    {
        // Transfer ownership of the memory pointed by dyingObj to this object
        this->ptr = dyingObj.ptr;
        dyingObj.ptr = nullptr;
    }

    void operator=(my_unique_ptr &&dyingObj) // move assignment
    {
        __cleanup__(); // cleanup any existing data

        // Transfer ownership of the memory pointed by dyingObj to this object
        this->ptr = dyingObj.ptr;
        dyingObj.ptr = nullptr;
    }

    T *operator->() // dereferencing arrow operator
    {
        return this->ptr;
    }

    T &operator*()
    {
        return *(this->ptr);
    }

    ~my_unique_ptr() // destructor
    {
        __cleanup__();
    }

private:
    void __cleanup__()
    {
        if (ptr != nullptr)
            delete ptr;
    }
};

template <class T>
class my_unique_ptr<T[]>
{
private:
    T *ptr = nullptr;

public:
    my_unique_ptr() : ptr(nullptr) // default constructor
    {
    }

    my_unique_ptr(T *ptr) : ptr(ptr)
    {
    }

    my_unique_ptr(const my_unique_ptr &obj) = delete;            // copy constructor is deleted
    my_unique_ptr &operator=(const my_unique_ptr &obj) = delete; // copy assignment is deleted

    my_unique_ptr(my_unique_ptr &&dyingObj) // move constructor
    {
        __cleanup__(); // cleanup any existing data

        // Transfer ownership of the memory pointed by dyingObj to this object
        this->ptr = dyingObj.ptr;
        dyingObj.ptr = nullptr;
    }

    void operator=(my_unique_ptr &&dyingObj) // move assignment
    {
        __cleanup__(); // cleanup any existing data

        // Transfer ownership of the memory pointed by dyingObj to this object
        this->ptr = dyingObj.ptr;
        dyingObj.ptr = nullptr;
    }

    T *operator->() // deferencing arrow operator
    {
        return this->ptr;
    }

    T &operator*()
    {
        return *(this->ptr);
    }

    T &operator[](int index)
    {
        if (index < 0)
        {
            // Throw negative index exception
            throw(new std::exception("Negative index exception"));
        }
        return this->ptr[index]; // doesn't check out of bounds
    }

    ~my_unique_ptr() // destructor
    {
        __cleanup__();
    }

private:
    void __cleanup__()
    {
        if (ptr != nullptr)
            delete[] ptr;
    }
};

class Box
{
private:
    int length, width, height;
};

int main()
{
    // creates a my_unique_ptr object holding a 'Box' object
    my_unique_ptr<Box> box1(new Box);

    // creates a my_unique_ptr object holding an array of 'Box' objects
    my_unique_ptr<Box[]> boxArr(new Box[5]);
    Box b1 = boxArr[0]; // index based access

    // Every new must have a corresponding delete but here as the Box object(s) is being encapsulated in a smart pointer object, we don’t need to call delete as the destructor of my_unique_ptr will be called when its scope completes and the destructor will take care of the deallocation of the dynamically allocated memory.
    return 0;
}