# Text Cache System

A cache system implementation in C++ comparing different cache replacement algorithms (FIFO, LRU, LFU) for text file access.

## Project Overview

This project simulates a text caching system with:
- 100 text files (1000+ words each) stored on disk
- Cache limited to 10 texts in memory
- Three cache replacement algorithms
- Simulation of multiple users with different access patterns

## Requirements

- g++ with C++11 support
- Python 3 with pandas and matplotlib (for graphs)
- Make

## Building

```bash
make
```

This will compile the project and create the `ra2_main` executable.

## Running

### Interactive Mode

```bash
./ra2_main
```

Enter text numbers (1-100) to load texts. The system will show:
- Cache HIT or MISS
- Loading time
- First 100 characters of the text
- Current cache statistics

Commands:
- `1-100`: Load specific text
- `-1`: Run simulation mode
- `0`: Exit

### Simulation Mode

From interactive mode, enter `-1` to run the full simulation.

Or run directly:
```bash
echo "-1" | ./ra2_main
```

This will:
1. Test all 3 algorithms (FIFO, LRU, LFU)
2. With 3 access patterns (Random, Poisson, Weighted)
3. Simulate 3 users x 200 requests each
4. Save results to `results.csv`

### Generate Graphs

After running simulation:
```bash
python3 plot_results.py
```

This creates graphs in `docs/graphs/`:
- `hit_rate.png` - Hit rate comparison
- `response_time.png` - Response time comparison
- `summary_table.png` - Complete results table

## Cache Algorithms

### FIFO (First In First Out)
- Removes oldest entry when cache is full
- Simple but doesn't consider access patterns
- Time complexity: O(1)

### LRU (Least Recently Used)
- Removes least recently accessed item
- Better for temporal locality
- Time complexity: O(1)

### LFU (Least Frequently Used)
- Removes item with lowest access count
- Good for workloads with popular items
- Time complexity: O(n) for eviction

## Access Patterns

1. **Random**: Uniform distribution across all texts
2. **Poisson**: Centered around text 50 (λ=50)
3. **Weighted**: 43% probability for texts 30-40 (hot set)

## Project Structure

```
cache_project/
├── core/
│   ├── cache.h           # Abstract cache base class
│   ├── text_loader.h     # Text file loader
│   └── text_loader.cpp
├── algorithms/
│   ├── fifo.h           # FIFO implementation
│   ├── lru.h            # LRU implementation
│   └── lfu.h            # LFU implementation
├── simulation/
│   └── simulator.h       # Request pattern generator
├── texts/               # 100 text files
├── ra2_main.cpp         # Main program
├── Makefile
└── plot_results.py      # Graph generation
```

## Cleaning

```bash
make clean
```

Removes compiled objects and executable.

## Author

Luiz Felipe Greboge - 2025
