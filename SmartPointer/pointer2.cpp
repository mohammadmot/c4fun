#include <iostream>
#include <string>

#include <memory> // unique,share,weak pointer

class Entity
{
    std::shared_ptr<Entity> Adjacent;
    // !!! std::weak_ptr<Entity> Adjacent; // to solve cycling reference problem

    public:
    Entity()
    {
        std::cout << "a Ctor" << std::endl;
    }

    ~Entity()
    {
        std::cout << "a Dtor" << std::endl;
    }

    void Print()
    {
        std::cout << "a Entity class" << std::endl;
    }

    void SetAdjacent(std::shared_ptr<Entity> ptr)
    {
        Adjacent = ptr;
    }
};

int main()
{
    std::shared_ptr<Entity> sp1(new Entity);
    std::shared_ptr<Entity> sp2(new Entity);

    // weak pointer access
    std::weak_ptr<Entity> wp1 = sp1;
    wp1.lock()->Print(); // weak pointer can access the class with lock() only

    // !!! Cycling dependency => to solve the problem:
    // !!! change Entity parameter Adjacent to weak_pointer
    sp1->SetAdjacent(sp2);
    sp2->SetAdjacent(sp1);

    std::cout << "use_count: " << sp1.use_count() << std::endl;
    std::cout << "use_count: " << sp2.use_count() << std::endl;

    return 0;
}