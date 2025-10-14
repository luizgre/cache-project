# Development Notes

## Oct 10 - Project Setup
- Created folder structure for cache project
- Made directories: core, algorithms, simulation, texts
- Added .gitignore and README

## Oct 10 - Text Files
- Wrote generate_texts.py to create test files
- Generated 100 text files, about 1200 words each
- Used content about caching and CS concepts
- Verified with wc -w, all have 1000+ words

## Oct 11 - Cache Base Class
- Created cache.h with base Cache class
- Used unordered_map for O(1) lookup
- Tracks hits and misses
- Made get(), put(), evict() as virtual methods
- Added text_loader.cpp with 10ms delay to simulate disk

## Oct 11 - FIFO Implementation
- Made fifo.h, inherits from Cache
- Uses std::queue to track order
- Evicts oldest when full
- Pretty straightforward, all O(1)

## Oct 12 - LRU Implementation
- Created lru.h
- Uses list + unordered_map for positions
- Move accessed items to front
- Evict from back (least recent)
- A bit more complex than FIFO but still O(1)

## Oct 12 - LFU Implementation
- Made lfu.h
- Tracks frequency count for each item
- Evict item with lowest count
- Used simple linear search to find minimum
- Could optimize but works fine for 10 items

## Oct 13 - Request Simulator
- Added simulator.h with pattern generators
- Random: uniform distribution
- Poisson: centered around 50
- Weighted: 43% for items 30-40
- All return vector of request IDs

## Oct 13 - Main Program
- Wrote ra2_main.cpp
- Interactive mode: enter text ID, shows hit/miss and time
- Simulation mode: runs all combos (3 algs x 3 patterns)
- 3 users, 200 requests each = 600 per test
- Saves to results.csv

## Oct 13 - Makefile
- Simple makefile with g++ -std=c++11
- Compiles ra2_main.cpp and text_loader.cpp
- make, make clean, make run
- Compiled with no warnings

## Oct 14 - Graph Scripts
- plot_results.py reads CSV and makes graphs
- Uses pandas and matplotlib
- 3 graphs: hit rate, response time, summary table
- show_results.py for terminal output without libraries

## Oct 14 - Testing
Ran some tests:
- Interactive mode works, text 5 MISS then HIT
- Simulation runs all 9 combinations
- LFU got best results on Poisson pattern (43.8%)
- Random pattern hardest for all algorithms (8-10%)
- Results look reasonable

## Notes
- All code in English
- Simple implementations, nothing fancy
- Focus on correctness over optimization
- Cache size hardcoded to 10
- Text files in texts/ folder numbered 1-100
