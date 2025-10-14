#ifndef FIFO_H
#define FIFO_H

#include "../core/cache.h"
#include <queue>

// FIFO - First In First Out cache
class FIFOCache : public Cache {
private:
    std::queue<int> order;

public:
    bool get(int id, std::string& content) {
        if (data.find(id) != data.end()) {
            content = data[id];
            hits++;
            return true;
        }
        misses++;
        return false;
    }

    void put(int id, const std::string& content) {
        // If already in cache, don't add to queue again
        if (data.find(id) != data.end()) {
            data[id] = content;
            return;
        }

        // Check if cache is full
        if (data.size() >= CACHE_SIZE) {
            evict();
        }

        data[id] = content;
        order.push(id);
    }

    void evict() {
        if (!order.empty()) {
            int oldest = order.front();
            order.pop();
            data.erase(oldest);
        }
    }
};

#endif
