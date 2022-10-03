#include <memory>
#include <iostream>

class Bar
{
public:
    Bar()
    {
        std::cout << "making a Bar" << std::endl;
    }
    ~Bar()
    {
        std::cout << "destroying a Bar" << std::endl;
    }
};

class Foo
{
private:
    std::unique_ptr<Bar> m_bar;

public:
    Foo()
    {
        m_bar = std::make_unique<Bar>();
    }
};

int main()
{
    Foo foo;
}

/*
output:

making a Bar
destroying a Bar
*/