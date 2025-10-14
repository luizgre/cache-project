#ifndef CACHE_H
#define CACHE_H

#include <unordered_map>
#include <string>

#define CACHE_SIZE 10
#define NUM_TEXTS 100

// Abstract base class for cache implementations
class Cache {
protected:
    std::unordered_map<int, std::string> data;
    int hits;
    int misses;

public:
    Cache() : hits(0), misses(0) {}
    virtual ~Cache() {}

    // Pure virtual functions that child classes must implement
    virtual bool get(int id, std::string& content) = 0;
    virtual void put(int id, const std::string& content) = 0;
    virtual void evict() = 0;

    // Statistics functions
    int getHits() { return hits; }
    int getMisses() { return misses; }
    double getHitRate() {
        int total = hits + misses;
        return total > 0 ? (double)hits / total : 0;
    }

    void resetStats() {
        hits = 0;
        misses = 0;
    }

    int getSize() {
        return data.size();
    }
};

#endif
