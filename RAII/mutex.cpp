/*
RAII:
ref: https://en.cppreference.com/w/cpp/language/raii

Resource Acquisition Is Initialization or RAII, is a C++ programming technique
which binds the life cycle of a resource that must be acquired before use
 allocated heap memory
 thread of execution
 open socket
 open file
 locked mutex
 disk space
 database connection
 anything that exists in limited supply
to the lifetime of an object.

- Notes:
  RAII [does not apply] to the management of the resources that are not acquired
   before use: CPU time, cores, and cache capacity, entropy pool capacity,
   network bandwidth, electric power consumption, stack memory.

- RAII guarantees that the resource is available to any function that may access
  the object
- guarantees that all resources are released when the lifetime of their
  controlling object ends, in reverse order of acquisition.
- Likewise, if resource acquisition fails (the constructor exits with an exception),
  all resources acquired by every fully-constructed member and base sub-object
  are released in reverse order of initialization
- This leverages the core language features
   object lifetime
   scope exit
   order of initialization
   and stack unwinding
  to eliminate resource leaks and guarantee exception safety.
- Another name for this technique is Scope-Bound Resource Management (SBRM),
  after the basic use case where the lifetime of an RAII object ends due to scope exit.

RAII can be summarized as follows:
    1. encapsulate each resource into a class, where
        the constructor acquires the resource and establishes all class invariants or throws an exception if that cannot be done,
        the destructor releases the resource and never throws exceptions;

    2. always use the resource via an instance of a RAII-class that either
        has automatic storage duration or temporary lifetime itself, or
        has lifetime that is bounded by the lifetime of an automatic or temporary object

- [Move semantics] make it possible to [safely transfer resource ownership]
   between objects,
   across scopes,
   and in and out of threads,
  while maintaining resource safety.

- Classes with:
   open()/close(),
   lock()/unlock(),
   or init()/copyFrom()/destroy() member functions
  are typical examples of non-RAII classes.

- The standard library
  The C++ library classes that manage their own resources follow RAII:
   std::string,
   std::vector,
   std::jthread (since C++20),
  and many others acquire their resources in constructors
  (which throw exceptions on errors), release them in their destructors
  (which never throw), and don't require explicit cleanup.

- In addition, the standard library offers several RAII wrappers to manage
  user-provided resources:
    std::unique_ptr and std::shared_ptr to manage dynamically-allocated memory or,
     with a user-provided deleter, any resource represented by a plain pointer;

    std::lock_guard, std::unique_lock, std::shared_lock to manage mutexes.
*/

#include <stdio.h>
#include <iostream>

//===================================================
#include <mutex>
std::mutex m;

void f()
{
    // ...
}

bool everything_ok()
{
    // ...
    return false;
}

void bad()
{
    m.lock(); // acquire the mutex
    f();      // if f() throws an exception, the mutex is never released
    if (!everything_ok())
        return; // early return, the mutex is never released
    m.unlock(); // if bad() reaches this statement, the mutex is released
}

void good()
{
    std::lock_guard<std::mutex> lk(m); // RAII class: mutex acquisition is initialization
    f();                               // if f() throws an exception, the mutex is released
    if (!everything_ok())
        return; // early return, the mutex is released
}

//===================================================
/* What is an auto_ptr and why isn't there an auto_array?

   An auto_ptr is an example of very simple handle class, defined in<memory>,
   supporting exception safety using the resource acquisition is initialization technique.
   An auto_ptr holds a pointer, can be used as a pointer,
   and deletes the object pointed to at the end of its scope.

   example:
   If an exception is thrown in the... part,
   the object held by p is correctly deleted by auto_ptr's destructor
   while the X pointed to by q is [leaked].
*/

#include <memory>
using namespace std;

struct X
{
    int m;
    // ..
};

void ff()
{
    std::unique_ptr<X> p(new X);
    X *q = new X;

    p->m++; // do not [leaked], use p just like a pointer
    q->m++; // may be [leaked]

    // ... [if exception occurs]

    delete q;
}

//===================================================
int main()
{
    unique_ptr<X> p(new X);
    unique_ptr<X> q = move(p);
    cout << "p: " << p.get() << " q: " << q.get() << "\n";

    printf("std::mutex [lock,unlock] or [lock_guard]");

    good();

    bad();

    // ...

    return 0;
}
