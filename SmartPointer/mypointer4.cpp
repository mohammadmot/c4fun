/*
C++: shared_ptr and how to write your own

Share Pointer:
- they are better than normal pointers
- managing dynamically allocated memory
- SharePtr is a reference-counted smart pointer
- it can share ownership of a dynamically allocated object with other SharePtr instances
- to put it in another way, several SharePtr objects can own (point to)
  the same memory(object) on the heap

- SharePtr maintains a reference count as to how many
  SharePtr objects own the same underlying pointer.
  And the memory pointed by the underlying pointer is deleted when:
    *The reference count becomes zero. the last remaining SharePtr object is destroyed.
    *The last remaining SharePtr object owning the pointer is assigned with some other pointer.


- it's a smart pointer which is stack allocate object that wrap raw pointer
- when last reference of the object in memory is destructed,
  wrapped pointer will also be deleted
- circular references!
- performance bottleneck: create/copy/destroy need to be atomic operation
  in multi-threading performance
*/

// chain assignment: (a = b) = c
// avoid extra copy constructor, destruct cost

#include <iostream>
#include <string>

// -----------------------------------------------------
typedef unsigned int uint;

template <typename T>
class SharePtr
{
private:
    T *m_data = nullptr;     // normal pointer, data container to pointer of data
    uint *m_count = nullptr; // count reference counter
                             // variable is declared as a pointer. We cannot make it an integer variable because it won’t be possible to maintain its same value between different SharePtr objects.

    void clean_up()
    {
        if (m_count != nullptr)
            (*m_count)--;

        // last share pointer, release pointer
        if (*m_count == 0)
        {
            if (m_data != nullptr)
                delete m_data;
            delete m_count;
        }
    }

public:
    ~SharePtr() // destructor
    {
        clean_up();
    }

    // ----------------------------
    // default constructor
    SharePtr() : m_data(nullptr), m_count(new uint(0))
    {
    }

    SharePtr(T *ptr) : m_data(ptr), m_count(new uint(1)) // constructor
    {
    }

    // ----------------------------
    /*** Copy Semantics ***/

    // copy constructor
    SharePtr(const SharePtr &another_ptr)
    {
        this->m_data = another_ptr.m_data;   // share the underlying pointer
        this->m_count = another_ptr.m_count; // share count
        if (nullptr != another_ptr.m_data)
        {
            // if the pointer is not null, increment the count
            (*this->m_count)++;
        }
    }

    // copy assignment
    SharePtr &operator=(const SharePtr &another_ptr)
    {
        // cleanup any existing data
        clean_up();

        // Assign incoming object's data to this object
        this->m_data = another_ptr.m_data;   // share the underlying pointer
        this->m_count = another_ptr.m_count; // share count
        if (nullptr != another_ptr.m_data)
        {
            // if the pointer is not null, increment the refCount
            (*this->m_count)++;
        }
    }

    // ----------------------------
    /*** Move Semantics ***/

    // move constructor
    SharePtr(SharePtr &&dyingObj)
    {
        this->m_data = dyingObj.m_data;               // share the underlying pointer
        this->m_count = dyingObj.m_count;             // share count
        dyingObj.m_data = dyingObj.m_count = nullptr; // clean up dyingObj
    }

    // move assignment
    SharePtr &operator=(SharePtr &&dyingObj)
    {
        // cleanup any existing data
        clean_up();

        this->m_data = dyingObj.m_data;               // share the underlying pointer
        this->m_count = dyingObj.m_count;             // share count
        dyingObj.m_data = dyingObj.m_count = nullptr; // clean up dyingObj
    }

    // ----------------------------
    // [const] in a function signature makes it a constant member function which ensures that this function will not make any changes to the object. It’s a good practice to make getter functions of a class as const member functions.
    T *operator->() const
    {
        return this->ptr;
    }

    T &operator*() const
    {
        return this->ptr;
    }

    // ----------------------------
    uint get_count() const
    {
        return *m_count; // *this->m_count
    }

    T *get() const
    {
        return this->m_data;
    }
};

// -----------------------------------------------------

class Box
{
public:
    int length, width, height;
    Box() : length(0), width(0), height(0)
    {
    }
};

using namespace std;

int main()
{
    SharePtr<Box> obj;
    cout << obj.get_count() << endl; // prints 0

    SharePtr<Box> box1(new Box());
    cout << box1.get_count() << endl; // prints 1

    SharePtr<Box> box2(box1); // calls copy constructor

    cout << box1.get_count() << endl; // prints 2
    cout << box2.get_count() << endl; // also prints 2

    return 0;
}
