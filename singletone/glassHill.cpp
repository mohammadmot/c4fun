#include <iostream>
#include <thread>
#include <mutex>

struct Princess {};

Princess getPrincess(int id) {
    if (std::random_device()() % 10)
    {
        printf("Knight ", id, " has slid back down the hill!\n");
        throw std::runtime_error("failed");
    }
    return Princess{};
}

void goQuesting(int id, std::once_flag& hill) {
    std::optional<Princess> wife;
    print("Knight ", id, " has arrived at the foot of the hill.\n");
try_again:
    try {
        std::call_once(hill, [&]() {
            print("Knight ", id, " is riding up the hill.\n");
            wife = getPrincess(id);
            print("Knight ", id, " has won the princess!\n");
        });
    } catch (...) {
        print("Knight ", id, " is ready to try again.\n");
        goto try_again;
    }
    print("Knight ", id, " has gone home ", (wife ? "with" : "without"), " a wife.\n");
}

int main() {
    std::vector<std::thread> knights;
    std::once_flag hill;
    for (int id=0; id < 4; ++id) {
        knights.emplace_back([id, &hill]() {
            goQuesting(id, hill);
        });
    }
    for (auto&& t : knights) t.join();
}