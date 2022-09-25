#include <iostream>
#include <future>

using namespace std;

// ref: https://github.com/chriskohlhoff/executors
// ref: https://www.youtube.com/watch?v=y7YfnllLftY

/*
void Print()
{
    std::cout << "Hello ..." << std::endl;
}

...
dispatch(ex, Print);

    execution context: thread, pool thread, any executable object
    run a callable =>
    function, function object or lambda function
        Where: internal or external process, result is read back
        When: immediately or scheduled
        How: CPU or GPU context
*/

// active object pattern
class BankAccount
{
    int _balance = 0;
    std::experimental::thread_pool pool_{1}; // thread pool

public:
    void deposit(int amount)
    {
        post(pool_, [=]
             { _balance += amount; });
    }

    void withdraw(int amount)
    {
        post(pool_, [=]
             { if (_balance += amount)
                _balance -= amount; });
    }

    void withdraw(int amount)
    {
        std::future<void> futu = std::experimental::post(
            pool_, [=]
            { 
                if (_balance >= amount)
                _balance -= amount; },
            std::experimental::use_future);
        futu.get();
    }

    // waiting for function completion
    template <class CompletionToken>
    auto withdraw(int amount, CompletionToken &&token)
    {
        return std::experimental::post(
            pool_, [=]
            { 
                if (_balance >= amount)
                _balance -= amount; },
            std::forward<CompletionToken>(token));
    }

    // completion tokens
    std::future<std::string> futu = std::experimental::dispatch(
        ex,
        []
        { return 1; },
        [](int i)
        { return i + 1; },
        [](int i)
        { return i * 2; },
        [](int i)
        { return std::to_string(i); },
        [](std::string s)
        { return "value is " + s; },
        std::experimental::use_future);

    std::cout << futu.get() << std::endl;
};