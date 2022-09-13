/*
Concurrency support library
std::mutex

The mutex class is a synchronization primitive that can be used to protect
shared data from being simultaneously accessed by multiple threads.

mutex offers exclusive, non-recursive ownership semantics:
    - A calling thread owns a mutex from the time that it successfully calls
      either lock or try_lock until it calls unlock.
    - When a thread owns a mutex, all other threads will block
      (for calls to lock) or receive a false return value (for try_lock)
      if they attempt to claim ownership of the mutex.
    - A calling thread must not own the mutex prior to calling lock or try_lock.

The behavior of a program is undefined if a mutex is destroyed while
still owned by any threads, or a thread terminates while owning a mutex.
The mutex class satisfies all requirements of Mutex and StandardLayoutType.

std::mutex is neither copyable nor movable.

Notes:
std::mutex is usually not accessed directly:
 std::unique_lock,
 std::lock_guard,
 or std::scoped_lock (since C++17)
manage locking in a more exception-safe manner.

*/
#include <iostream>
#include <map>
#include <string>

#include <chrono>
#include <thread>
#include <mutex>

// This example shows how a mutex can be used to protect an
// std::map shared between two threads.

// std::map containers are not inherently atomic and therefore not thread-safe
std::map<std::string, std::string> g_pages;

std::mutex g_pages_mutex;

void save_page(const std::string &url)
{
    // simulate a long page fetch
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::string result = "fake content";

    // *** very important to sync threads
    std::lock_guard<std::mutex> guard(g_pages_mutex);
    g_pages[url] = result;
}

int main()
{
    std::thread t1(save_page, "http://www1");
    std::thread t2(save_page, "http://www2");
    std::thread t3(save_page, "http://www3");
    t1.join();
    t2.join();
    t3.join();

    // safe to access g_pages without lock now, as the threads are joined
    for (const auto &pair : g_pages)
    {
        std::cout << pair.first << " => " << pair.second << '\n';
    }
}