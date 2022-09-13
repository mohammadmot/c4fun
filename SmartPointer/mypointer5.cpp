/*
Typical implementation of unique_ptr

unique_ptr:
 The unique_ptr is also a smart pointer but takes care of the exclusive ownership
 of internal resource. In most of the use-case,
 its behavior is same as the [auto_ptr].
 However, unique pointer ensures that any transfer of ownership
 happens by moving the pointer.

=> unique_ptr<int> uptr1 = new int(2);
=> unique_ptr<int> uptr2 = std::move(uptr1);  // move the ownership

Copy:
Any attempt to copy shall fail during compiler only.
In following code, snippet, the ownership is not moved but copied.
=> std::unique_ptr<int> up1 = new int;
=> std::unique_ptr<int> up2 = up1;  // this is wrong

Delete copy operations:
The implementation specifically [deletes]
both the [copy constructor] as well as [assignment operator].
=> the_unique_ptr(const the_unique_ptr& up_rhs) = delete;
=> the_unique_ptr& operator=(const the_unique_ptr& up_rhs) = delete;

Introduction of Move member functions:
 The unique_ptr internally uses move member functions (constructor and assignment).
 Since, these members accepts only an [R-value] parameter,
 therefore unique_ptr will not accept any [L-value] unique_ptr.
 The reason behind this design is that a user must do
 an explicit move and pass an R-value.
 Therefore, there shall be no chance of unintended copy.
 Finally, the [move] shall transfer ownership of resource by
 explicit move of internal resource.
the_unique_ptr(the_unique_ptr&& up_rhs) // move constructor
{
    up_data = std::move(up_rhs.up_data);
    up_rhs.up_data = NULL;
}

*/
#include <iostream>  //main header
using namespace std; // namespace

template <typename T>
class the_unique_ptr // smart pointers implementation
{
    T *up_data;

public:
    the_unique_ptr() : up_data(nullptr) // default constructor
    {
    }

    the_unique_ptr(T *p)
    {
        up_data = p;
    }

    // remove copy semantics
    // copy constructor is deleted
    the_unique_ptr(const the_unique_ptr &up_rhs) = delete;

    // move constructor
    the_unique_ptr(the_unique_ptr &&up_rhs)
    {
        // Transfer ownership of memory pointed by up_rhs
        up_data = std::move(up_rhs.up_data);
        up_rhs.up_data = NULL;
    }

    // remove copy semantics
    // copy assignment is deleted
    the_unique_ptr &operator=(const the_unique_ptr &up_rhs) = delete;

    // move assignment
    the_unique_ptr &operator=(the_unique_ptr &&up_rhs)
    {
        // Transfer ownership of memory pointed
        up_data = std::move(up_rhs.up_data);

        // cleanup any existing data
        up_rhs.up_data = NULL;
        return (*this);
    }

    // dereferencing underlying pointer
    T &operator*()
    {
        return (*up_data);
    }
    
    // obtaining pointer using arrow operator
    T *operator->()
    {
        return up_data;
    }

    ~the_unique_ptr()
    {
        cout << "Automatic clean-up"
             << endl;
        if (up_data)
            delete up_data;
        up_data = NULL;
    }
};

int main()
{
    the_unique_ptr<int> up1 = new int(2);
    the_unique_ptr<int> up2 = std::move(up1);
    *up2 = 4;
    cout << *up2 << endl;

    the_unique_ptr<std::string> up3 = new std::string("mainfunda");
    the_unique_ptr<std::string> up4 = std::move(up3);

    cout << *up4 << endl;
    cout << up4->size() << endl;

    return 0;
}
