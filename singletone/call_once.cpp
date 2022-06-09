#include <iostream>
#include <thread>
#include <mutex>

void do_once_ex(int index, std::once_flag& onceFlag)
{
    std::call_once(
        onceFlag, [&]()
        { std::cout << "Only once by index:" << index << std::endl; });
}

/*std::once_flag onceFlag;

void do_once()
{
    std::call_once(onceFlag, []() { std::cout << "Only once." << std::endl; });
}
*/

int main()
{
    std::cout << std::endl;

    
    for (size_t i = 0; i < 100; i++)
    {
        std::once_flag onceFlag;

        std::thread t1(do_once_ex, 1, &onceFlag);
        std::thread t2(do_once_ex, 2, &onceFlag);
        std::thread t3(do_once_ex, 3, &onceFlag);
        std::thread t4(do_once_ex, 4, &onceFlag);

        t1.join();
        t2.join();
        t3.join();
        t4.join();
    }

    std::cout << "end." << std::endl;
}