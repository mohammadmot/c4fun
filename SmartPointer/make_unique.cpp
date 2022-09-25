// std::make_unique, std::make_unique_for_overwrite
/*
std::make_unique<int>(1); <=== [vs] ===> std::unique_ptr<int>(new int(1));

The motivation behind make_unique is primarily:
    1. make_unique is safe for creating temporaries,
    whereas with explicit use of new you have to remember the rule
    about not using unnamed temporaries.
    >>> foo(make_unique<T>(), make_unique<U>()); // exception safe
    >>> foo(unique_ptr<T>(new T()), unique_ptr<U>(new U())); // unsafe*

    2. The addition of make_unique finally means we can tell people to 'never'
    use [new] rather than the previous rule to
    "'never' use new except when you make a unique_ptr".

    3. make_unique does not require redundant type usage. unique_ptr<T>(new T()) -> make_unique<T>()




What are the advantages of using std::make_unique over the new operator
 for initializing a std::unique_ptr?

 >>> std::unique_ptr<SomeObject> a = std::make_unique(SomeObject(...))
 better than doing:
 >>> std::unique_ptr<SomeObject> a = new SomeObject(...)

 - Does it prevent any kind of memory leaks that might happen?
 - Is it faster to do a std::make_unique than to use new?

Advantages:
    make_unique teaches users "never say new/delete and new[]/delete[]"
        without disclaimers.
    make_unique shares two advantages with make_shared
        (excluding the third advantage, increased efficiency).
        First, unique_ptr<LongTypeName> up(new LongTypeName(args))
        must mention LongTypeName twice, while
        auto up = make_unique<LongTypeName>(args) mentions it once.
    make_unique prevents the unspecified-evaluation-order leak triggered by
        expressions like foo(unique_ptr<X>(new X), unique_ptr<Y>(new Y)).
        (Following the advice "never say new" is simpler than
        "never say new, unless you immediately give it to a named unique_ptr".)
    make_unique is carefully implemented for exception safety and is recommended
        over directly calling unique_ptr constructors.

When not to use make_unique:
    Don't use make_unique if you need a custom deleter or are adopting a raw pointer from elsewhere.
*/
#include <iostream>
#include <iomanip>
#include <memory> // make_unique

struct Vec3
{
    int x, y, z;

    // following constructor is no longer needed since C++20
    Vec3(int x = 0, int y = 0, int z = 0) noexcept : x(x), y(y), z(z) {}

    friend std::ostream &operator<<(std::ostream &os, const Vec3 &v)
    {
        return os << "{ x=" << v.x << ", y=" << v.y << ", z=" << v.z << " }";
    }
};

int main()
{
    /*
    ref: https://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique

    unique_ptr<T>(new std::remove_extent_t<T>[size])

    Parameters:
    args - list of arguments with which an instance of T will be constructed.
    size - the length of the array to construct
    */

    // Use the default constructor.
    std::unique_ptr<Vec3> v1 = std::make_unique<Vec3>();
    // Use the constructor that matches these arguments
    std::unique_ptr<Vec3> v2 = std::make_unique<Vec3>(0, 1, 2);
    // Create a unique_ptr to an array of 5 elements
    std::unique_ptr<Vec3[]> v3 = std::make_unique<Vec3[]>(5);

    std::cout << "make_unique<Vec3>():      " << *v1 << '\n'
              << "make_unique<Vec3>(0,1,2): " << *v2 << '\n'
              << "make_unique<Vec3[]>(5):   ";

    for (int i = 0; i < 5; i++)
    {
        std::cout << std::setw(i ? 30 : 0) << v3[i] << '\n';
    }
}