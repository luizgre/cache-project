#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include "core/cache.h"
#include "core/text_loader.h"
#include "algorithms/fifo.h"
#include "algorithms/lru.h"
#include "algorithms/lfu.h"
#include "simulation/simulator.h"

using namespace std;

void runSimulation() {
    cout << "\n=== SIMULATION MODE ===\n" << endl;
    cout << "Running 3 users x 200 requests each\n";
    cout << "Testing 3 algorithms x 3 patterns\n\n";

    // Open results file
    ofstream results("results.csv");
    results << "Algorithm,Pattern,HitRate,AvgTime(ms),TotalHits,TotalMisses\n";

    string algorithms[] = {"FIFO", "LRU", "LFU"};
    string patterns[] = {"Random", "Poisson", "Weighted"};

    // For each algorithm
    for (int alg = 0; alg < 3; alg++) {
        // For each pattern
        for (int pat = 0; pat < 3; pat++) {
            Cache* cache;

            // Create cache instance
            if (alg == 0) cache = new FIFOCache();
            else if (alg == 1) cache = new LRUCache();
            else cache = new LFUCache();

            // Generate requests for 3 users
            vector<int> all_requests;
            for (int user = 0; user < 3; user++) {
                vector<int> user_requests;

                if (pat == 0) {
                    user_requests = Simulator::generateRandom(200);
                } else if (pat == 1) {
                    user_requests = Simulator::generatePoisson(200);
                } else {
                    user_requests = Simulator::generateWeighted(200);
                }

                all_requests.insert(all_requests.end(),
                                  user_requests.begin(),
                                  user_requests.end());
            }

            // Process all requests
            auto start_time = chrono::high_resolution_clock::now();

            for (int req : all_requests) {
                string content;
                bool hit = cache->get(req, content);

                if (!hit) {
                    content = loadTextFromDisk(req);
                    cache->put(req, content);
                }
            }

            auto end_time = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);

            // Calculate stats
            double hit_rate = cache->getHitRate() * 100;
            double avg_time = (double)duration.count() / all_requests.size();

            // Save results
            results << algorithms[alg] << ","
                   << patterns[pat] << ","
                   << fixed << setprecision(2) << hit_rate << ","
                   << fixed << setprecision(2) << avg_time << ","
                   << cache->getHits() << ","
                   << cache->getMisses() << "\n";

            // Print progress
            cout << algorithms[alg] << " + " << patterns[pat]
                 << ": Hit Rate = " << hit_rate << "%"
                 << ", Avg Time = " << avg_time << "ms" << endl;

            delete cache;
        }
    }

    results.close();

    cout << "\nSimulation complete!" << endl;
    cout << "Results saved to results.csv" << endl;
    cout << "Generate graphs with: python3 plot_results.py\n" << endl;
}

int main() {
    cout << "Text Cache System" << endl;
    cout << "-----------------" << endl;
    cout << "Enter text number (1-100)" << endl;
    cout << "0 to exit, -1 for simulation\n" << endl;

    // Default to FIFO for interactive mode
    Cache* cache = new FIFOCache();

    int choice;
    while (true) {
        cout << "Text: ";
        cin >> choice;

        if (choice == 0) {
            cout << "Exiting..." << endl;
            break;
        }
        else if (choice == -1) {
            delete cache;
            runSimulation();
            cout << "\nReturning to interactive mode..." << endl;
            cache = new FIFOCache();
        }
        else if (choice >= 1 && choice <= NUM_TEXTS) {
            auto start = chrono::high_resolution_clock::now();

            string content;
            bool hit = cache->get(choice, content);

            if (!hit) {
                content = loadTextFromDisk(choice);
                cache->put(choice, content);
            }

            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

            string status = hit ? "HIT" : "MISS";
            cout << "[" << status << "] Text " << choice
                 << " loaded in " << duration.count() << "ms" << endl;
            cout << "First 100 chars: "
                 << content.substr(0, 100) << "..." << endl;

            // Show current cache stats
            cout << "Cache stats: " << cache->getHits() << " hits, "
                 << cache->getMisses() << " misses, "
                 << "hit rate = " << fixed << setprecision(1)
                 << (cache->getHitRate() * 100) << "%" << endl << endl;
        }
        else {
            cout << "Invalid number! Use 1-100" << endl;
        }
    }

    delete cache;
    return 0;
}
