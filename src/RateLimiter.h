#pragma once

#include <chrono>
#include <mutex>
#include <string>
#include <unordered_map>

class RateLimiter {
public:
    RateLimiter(std::size_t capacity, double refillRatePerSecond);
    bool allow(const std::string& clientId);

private:
    struct Bucket {
        double tokens;
        std::chrono::steady_clock::time_point lastRefill;
    };

    std::size_t capacity;
    double refillRatePerSecond;
    std::unordered_map<std::string, Bucket> buckets;
    std::mutex mtx;

    void refill(Bucket& bucket, std::chrono::steady_clock::time_point now);
};