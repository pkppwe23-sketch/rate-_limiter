#include "RateLimiter.h"
#include <chrono>
#include <iostream>
#include <thread>

int main() {
    RateLimiter limiter(5, 1.0);
    for (int i = 1; i <= 7; ++i) {
        std::cout << "Request " << i << ": "
                  << (limiter.allow("user-1") ? "Allowed" : "Rejected") << '\n';
    }
    std::cout << "Waiting for 1 second...\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Request after refill: "
              << (limiter.allow("user-1") ? "Allowed" : "Rejected") << '\n';
}
