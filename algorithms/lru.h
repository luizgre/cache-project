#ifndef LRU_H
#define LRU_H

#include "../core/cache.h"
#include <list>
#include <unordered_map>

// LRU - Least Recently Used cache
class LRUCache : public Cache {
private:
    std::list<int> order;  // Most recent at front
    std::unordered_map<int, std::list<int>::iterator> positions;

public:
    bool get(int id, std::string& content) {
        if (data.find(id) != data.end()) {
            // Move to front (most recently used)
            order.erase(positions[id]);
            order.push_front(id);
            positions[id] = order.begin();

            content = data[id];
            hits++;
            return true;
        }
        misses++;
        return false;
    }

    void put(int id, const std::string& content) {
        // If already exists, update it
        if (data.find(id) != data.end()) {
            data[id] = content;
            order.erase(positions[id]);
            order.push_front(id);
            positions[id] = order.begin();
            return;
        }

        // Check if cache is full
        if (data.size() >= CACHE_SIZE) {
            evict();
        }

        // Add new item
        data[id] = content;
        order.push_front(id);
        positions[id] = order.begin();
    }

    void evict() {
        if (!order.empty()) {
            int lru = order.back();
            order.pop_back();
            positions.erase(lru);
            data.erase(lru);
        }
    }
};

#endif
