#ifndef LFU_H
#define LFU_H

#include "../core/cache.h"
#include <unordered_map>

// LFU - Least Frequently Used cache
class LFUCache : public Cache {
private:
    std::unordered_map<int, int> freq;  // Track access frequency

public:
    bool get(int id, std::string& content) {
        if (data.find(id) != data.end()) {
            freq[id]++;  // Increment frequency
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
            freq[id]++;
            return;
        }

        // Check if cache is full
        if (data.size() >= CACHE_SIZE) {
            evict();
        }

        // Add new item with frequency 1
        data[id] = content;
        freq[id] = 1;
    }

    void evict() {
        if (data.empty()) return;

        // Find item with lowest frequency
        int min_freq = -1;
        int lfu_id = -1;

        for (auto& p : freq) {
            if (min_freq == -1 || p.second < min_freq) {
                min_freq = p.second;
                lfu_id = p.first;
            }
        }

        // Remove least frequently used
        if (lfu_id != -1) {
            data.erase(lfu_id);
            freq.erase(lfu_id);
        }
    }
};

#endif
