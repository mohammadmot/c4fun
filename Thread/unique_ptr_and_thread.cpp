/*
unique_ptr is thread safe when used correctly.
You broke the unwritten rule: never pass unique_ptr between threads by reference.
*/

#include <memory>
#include <string>
#include <thread>
#include <cstdio>

using namespace std;

int main()
{
    unique_ptr<int> work;

    thread t1([&]
              {
        while (true) {
            const unique_ptr<int> localWork = move(work);
            if (localWork)
                printf("thread1: %d\n", *localWork);
            this_thread::yield();
        } });

    thread t2([&]
              {
        while (true) {
            const unique_ptr<int> localWork = move(work);
            if (localWork)
                printf("thread2: %d\n", *localWork);
            this_thread::yield();
        } });

    for (int i = 0;; i++)
    {
        work.reset(new int(i));

        while (work)
            this_thread::yield();
    }

    return 0;
}