#include <iostream>
#include <string>

#include <memory> // unique,share,weak pointer

// when single ownership of resource is required use std::unique_ptr
/*
std::unique_ptr<A> ptr1(new A);
std::unique_ptr<A> ptr2 = ptr1; // !!! Error, can't copy unique_ptr
std::unique_ptr<A> ptr2 = std::move(ptr1); // change the owner ship to other
*/

class Entity
{
    public:
    Entity()
    {
        // std::cout << "a Ctor" << std::endl;
    }

    ~Entity()
    {
        // std::cout << "a Dtor" << std::endl;
    }

    void Print()
    {
        std::cout << "a Entity class" << std::endl;
    }
};

int main()
{
    std::unique_ptr<Entity> uPtr1(new Entity);
    uPtr1->Print();
    std::cout << "unique pointer 1 get(): " << uPtr1.get() << std::endl;

    std::unique_ptr<Entity> uPtr2 = std::move(uPtr1);
    uPtr2->Print();
    std::cout << "unique pointer 1 get(): " << uPtr1.get() << std::endl;
    std::cout << "unique pointer 2 get(): " << uPtr2.get() << std::endl;

    return 0;
}