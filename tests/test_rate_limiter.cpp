#include "../src/RateLimiter.h"
#include <cassert>
#include <chrono>
#include <thread>

int main() {
    RateLimiter limiter(2, 2.0);
    assert(limiter.allow("user-1"));
    assert(limiter.allow("user-1"));
    assert(!limiter.allow("user-1"));
    assert(limiter.allow("user-2"));
    std::this_thread::sleep_for(std::chrono::milliseconds(600));
    assert(limiter.allow("user-1"));
}
