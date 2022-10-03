// The simplest strategy is to have a single non - static mutex member,
// and have every member function acquire the mutex at the beginning of its body,
// and release it at the end.
// A thread - safe integer wrapper type might look like this:

// Note that std::lock_guard’s destructor releases the mutex automatically.
// Note that the mutex is mutable so it can be locked by get(), which is const.

// Finer-grained locking may be desirable in some cases,
// and when performance is critical, lock-free algorithms may be preferred.

#include <memory>
#include <string>
#include <thread>
#include <mutex>

class AtomicInt
{
    int get() const
    {
        std::lock_guard<std::mutex> l(m);
        return value;
    }

    int set(int newval)
    {
        std::lock_guard<std::mutex> l(m);
        return std::exchange(value, newval);
    }

private:
    mutable std::mutex m;
    int value;
};