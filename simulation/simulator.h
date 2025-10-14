#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include <random>
#include <algorithm>

class Simulator {
public:
    // Generate random uniform requests
    static std::vector<int> generateRandom(int count) {
        std::vector<int> requests;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, NUM_TEXTS);

        for (int i = 0; i < count; i++) {
            requests.push_back(dis(gen));
        }
        return requests;
    }

    // Generate Poisson distribution requests
    static std::vector<int> generatePoisson(int count) {
        std::vector<int> requests;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::poisson_distribution<> dis(50);  // lambda = 50

        for (int i = 0; i < count; i++) {
            int val = dis(gen);
            // Clamp to valid range
            val = std::max(1, std::min(NUM_TEXTS, val));
            requests.push_back(val);
        }
        return requests;
    }

    // Generate weighted requests (43% chance for texts 30-40)
    static std::vector<int> generateWeighted(int count) {
        std::vector<int> requests;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> prob(0, 1);
        std::uniform_int_distribution<> hot_range(30, 40);
        std::uniform_int_distribution<> cold_range(1, NUM_TEXTS);

        for (int i = 0; i < count; i++) {
            if (prob(gen) < 0.43) {
                // 43% chance to access hot range
                requests.push_back(hot_range(gen));
            } else {
                // 57% chance to access any text
                requests.push_back(cold_range(gen));
            }
        }
        return requests;
    }
};

#endif
