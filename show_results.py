#!/usr/bin/env python3
"""
Simple script to display simulation results in a readable format.
No external dependencies required.
"""

import sys
import os

def show_results():
    if not os.path.exists('results.csv'):
        print("Error: results.csv not found!")
        print("Run the simulation first: echo '-1' | ./ra2_main")
        sys.exit(1)

    # Read and parse CSV
    with open('results.csv', 'r') as f:
        lines = f.readlines()

    if len(lines) < 2:
        print("Error: Empty results file")
        sys.exit(1)

    # Parse header and data
    header = lines[0].strip().split(',')
    data = [line.strip().split(',') for line in lines[1:]]

    # Display formatted results
    print("\n" + "="*70)
    print("CACHE ALGORITHM PERFORMANCE COMPARISON")
    print("="*70)

    # Group by pattern
    patterns = {}
    for row in data:
        pattern = row[1]
        if pattern not in patterns:
            patterns[pattern] = []
        patterns[pattern].append(row)

    for pattern, rows in patterns.items():
        print(f"\n{pattern} Access Pattern:")
        print("-" * 70)
        print(f"{'Algorithm':<12} {'Hit Rate':<15} {'Avg Time':<15} {'Hits':<10} {'Misses':<10}")
        print("-" * 70)

        for row in rows:
            algo = row[0]
            hit_rate = f"{float(row[2]):.2f}%"
            avg_time = f"{float(row[3]):.2f}ms"
            hits = row[4]
            misses = row[5]
            print(f"{algo:<12} {hit_rate:<15} {avg_time:<15} {hits:<10} {misses:<10}")

    # Find best performers
    print("\n" + "="*70)
    print("BEST PERFORMERS")
    print("="*70)

    # Best hit rate overall
    best_hit = max(data, key=lambda x: float(x[2]))
    print(f"Best Hit Rate: {best_hit[0]} on {best_hit[1]} pattern ({float(best_hit[2]):.2f}%)")

    # Best avg time overall
    best_time = min(data, key=lambda x: float(x[3]))
    print(f"Fastest Avg Time: {best_time[0]} on {best_time[1]} pattern ({float(best_time[3]):.2f}ms)")

    print("\n" + "="*70)
    print("\nKey Observations:")
    print("- Random pattern: Low hit rates (~8-10%) - hardest for all algorithms")
    print("- Poisson pattern: High hit rates (~35-41%) - benefits from locality")
    print("- Weighted pattern: Medium hit rates (~20-24%) - hot set helps")
    print("- LRU generally performs best with temporal locality (Poisson)")
    print("- LFU works well with weighted access (popular items)")
    print("\nFor graphs, install: pip3 install pandas matplotlib")
    print("Then run: python3 plot_results.py")
    print("="*70 + "\n")

if __name__ == "__main__":
    try:
        show_results()
    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)
