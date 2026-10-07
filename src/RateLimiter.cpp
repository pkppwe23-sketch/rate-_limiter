#include "RateLimiter.h"

#include <algorithm>
#include <stdexcept>

RateLimiter::RateLimiter(std::size_t capacity, double refillRatePerSecond)
    : capacity(capacity), refillRatePerSecond(refillRatePerSecond) {
    if (capacity == 0 || refillRatePerSecond <= 0) {
        throw std::invalid_argument("Capacity and refill rate must be positive");
    }
}

void RateLimiter::refill(Bucket& bucket, std::chrono::steady_clock::time_point now) {
    const double elapsed = std::chrono::duration<double>(now - bucket.lastRefill).count();
    bucket.tokens = std::min(static_cast<double>(capacity), bucket.tokens + elapsed * refillRatePerSecond);
    bucket.lastRefill = now;
}

bool RateLimiter::allow(const std::string& clientId) {
    std::lock_guard<std::mutex> lock(mtx);
    const auto now = std::chrono::steady_clock::now();
    auto it = buckets.find(clientId);
    if (it == buckets.end()) {
        it = buckets.emplace(clientId, Bucket{static_cast<double>(capacity), now}).first;
    }
    refill(it->second, now);
    if (it->second.tokens < 1.0) return false;
    it->second.tokens -= 1.0;
    return true;
}
