# Rate Limiter

A thread-safe Token Bucket Rate Limiter implemented in C++17.

## What does it do?
A rate limiter controls how many requests a client can make over time.

Example: capacity 5 and refill rate 1 token/second means a client can make 5 requests immediately, then receives about 1 new token per second.

## Token Bucket
Each client has a bucket of tokens. An accepted request consumes one token. Tokens are refilled according to elapsed time and the bucket cannot exceed its capacity. Requests with no available token are rejected.

## Design
Client -> RateLimiter -> Token Bucket per client -> Allowed / Rejected

The implementation uses an unordered_map for client buckets and std::mutex for thread safety.

## Usage
RateLimiter limiter(5, 1.0);
if (limiter.allow("user-123")) {
    // process request
} else {
    // return HTTP 429 Too Many Requests
}

## Complexity
- Request: O(1) average
- Bucket lookup: O(1) average
- Memory: O(N), where N is the number of tracked clients

## Build
cmake -S . -B build
cmake --build build

Run demo: ./build/rate_limiter_demo
Run tests: ctest --test-dir build --output-on-failure

## Why rate limiting?
- Protect APIs from excessive traffic
- Prevent brute-force attempts
- Avoid accidental request storms
- Protect backend resources
- Enforce API usage limits

## Production Extension
This implementation is in-memory and single-process. A distributed version can store bucket state in Redis and use atomic operations so multiple backend servers share the same limits.

## Interview Topics
Token Bucket, OOP, encapsulation, mutex, concurrency, hash maps, time-based state, API rate limiting, and distributed-system trade-offs.
