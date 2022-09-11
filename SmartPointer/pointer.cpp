#include <iostream>
#include <string>

#include <memory> // unique,share,weak pointer

class Entity
{
    public:
    Entity()
    {
        std::cout << "constructor of Entity class invoked." << std::endl;
    }

    ~Entity()
    {
        std::cout << "destructor of Entity class invoked." << std::endl;
    }

    void Print()
    {
        std::cout << "Print ..." << std::endl;
    }
};

int main()
{
    // unique pointer

    std::cout << "Start scope #1 ..." << std::endl;
    {
        std::unique_ptr<Entity> ptrEntity2 = std::make_unique<Entity>();
    }
    std::cout << "Exit from scope #1 ..." << std::endl;

    std::cout << "-------------------------------------------------------" << std::endl;
    
    {   
        // not safe, may be throw exception 
        std::unique_ptr<Entity> ptrEntity1(new Entity());
        ptrEntity1->Print();

        // all references delete
        // !!! std::unique_ptr<Entity> ptrCopyEntity = ptrEntity1;

        // -------------------
        // -------------------
        std::unique_ptr<int> unPtr1 = std::make_unique<int>(25);
        std::cout << *unPtr1 << std::endl;
        // std::cout << (unPtr1) << std::endl;

        // !!! std::unique_ptr<int> unPtr2 = unPtr1; // you can't share unique pointer
        std::unique_ptr<int> unPtr2 = std::move(unPtr1); // move the owner ship the pointer, the original owner make null pointer
        std::cout << *unPtr2 << std::endl;
        try
        {
            // !!! throw "forced exception !!!"; // exception goto handler: catch(const char* e)
            if (unPtr1)
                std::cout << *unPtr1 << std::endl; // !!! null pointer exception
        }
        catch(const char* e)
        {
            std::cerr << e << '\n';
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        catch (...) // default handler in last
        {
            std::cerr << "Exception Happened !!!" << '\n';
        }

        std::cout << "Continue after exception ..." << std::endl;

        // -------------------
        // -------------------
    }

    {   // safe, don't make the memory leak
        std::unique_ptr<Entity> ptrEntity2 = std::make_unique<Entity>();
        ptrEntity2->Print();
    }

    {   // raw pointer
        Entity* pocEntity3 = new Entity();
        // ...
        delete pocEntity3;
    }

    std::cout << "-------------------------------------------------------" << std::endl;
    // shared pointer: store reference counting
    // share pointer increase reference count but weak pointer not increase
    {
        std::shared_ptr<Entity> ptrEntity = std::make_shared<Entity>();
        // the numbers of owners this shared pointer
        std::cout << "shared_ptr.use_count = " << ptrEntity.use_count() << std::endl;
        {
            std::shared_ptr<Entity> ptrShareEntity = std::make_shared<Entity>();
            ptrShareEntity = ptrEntity;
            std::cout << "shared_ptr.use_count = " << ptrEntity.use_count() << std::endl;
        }   
        
        std::cout << "shared_ptr.use_count = " << ptrEntity.use_count() << std::endl;

        std::shared_ptr<Entity> ptrShareEntity2 = ptrEntity;
        std::cout << "shared_ptr.use_count = " << ptrEntity.use_count() << std::endl;
    }

    std::cout << "-------------------------------------------------------" << std::endl;
    // weak pointer: not count as a reference
    {
        std::weak_ptr<Entity> ptrEntity;
        {
            std::shared_ptr<Entity> ptrShareEntity = std::make_shared<Entity>();
            ptrEntity = ptrShareEntity;
        }   
        
        if (!ptrEntity.expired())
        {
            ptrEntity.lock()->Print();
        }

    }

    // ...

    std::cin.get();
}