#!/usr/bin/env python3
"""
Simple script to generate performance graphs from simulation results.
Creates bar charts comparing cache algorithms across different access patterns.
"""

import pandas as pd
import matplotlib.pyplot as plt
import sys
import os

def plot_results():
    # Check if results file exists
    if not os.path.exists('results.csv'):
        print("Error: results.csv not found!")
        print("Run the simulation first: ./ra2_main and choose -1")
        sys.exit(1)

    # Read results
    df = pd.read_csv('results.csv')

    # Create output directory
    os.makedirs('docs/graphs', exist_ok=True)

    # Plot 1: Hit Rate comparison
    plt.figure(figsize=(10, 6))

    patterns = df['Pattern'].unique()
    x = range(len(patterns))
    width = 0.25

    fifo_data = df[df['Algorithm'] == 'FIFO']['HitRate'].values
    lru_data = df[df['Algorithm'] == 'LRU']['HitRate'].values
    lfu_data = df[df['Algorithm'] == 'LFU']['HitRate'].values

    plt.bar([i - width for i in x], fifo_data, width, label='FIFO', color='skyblue')
    plt.bar([i for i in x], lru_data, width, label='LRU', color='orange')
    plt.bar([i + width for i in x], lfu_data, width, label='LFU', color='green')

    plt.xlabel('Access Pattern')
    plt.ylabel('Hit Rate (%)')
    plt.title('Cache Hit Rate Comparison')
    plt.xticks(x, patterns)
    plt.legend()
    plt.grid(axis='y', alpha=0.3)
    plt.tight_layout()
    plt.savefig('docs/graphs/hit_rate.png', dpi=100)
    print("Generated: docs/graphs/hit_rate.png")

    # Plot 2: Average response time comparison
    plt.figure(figsize=(10, 6))

    fifo_time = df[df['Algorithm'] == 'FIFO']['AvgTime(ms)'].values
    lru_time = df[df['Algorithm'] == 'LRU']['AvgTime(ms)'].values
    lfu_time = df[df['Algorithm'] == 'LFU']['AvgTime(ms)'].values

    plt.bar([i - width for i in x], fifo_time, width, label='FIFO', color='skyblue')
    plt.bar([i for i in x], lru_time, width, label='LRU', color='orange')
    plt.bar([i + width for i in x], lfu_time, width, label='LFU', color='green')

    plt.xlabel('Access Pattern')
    plt.ylabel('Average Response Time (ms)')
    plt.title('Average Response Time Comparison')
    plt.xticks(x, patterns)
    plt.legend()
    plt.grid(axis='y', alpha=0.3)
    plt.tight_layout()
    plt.savefig('docs/graphs/response_time.png', dpi=100)
    print("Generated: docs/graphs/response_time.png")

    # Plot 3: Summary table
    fig, ax = plt.subplots(figsize=(12, 4))
    ax.axis('tight')
    ax.axis('off')

    table_data = []
    for _, row in df.iterrows():
        table_data.append([
            row['Algorithm'],
            row['Pattern'],
            f"{row['HitRate']:.1f}%",
            f"{row['AvgTime(ms)']:.2f}ms",
            row['TotalHits'],
            row['TotalMisses']
        ])

    table = ax.table(cellText=table_data,
                    colLabels=['Algorithm', 'Pattern', 'Hit Rate', 'Avg Time', 'Hits', 'Misses'],
                    cellLoc='center',
                    loc='center')
    table.auto_set_font_size(False)
    table.set_fontsize(9)
    table.scale(1, 1.5)

    plt.title('Complete Results Summary', pad=20, fontsize=14, fontweight='bold')
    plt.savefig('docs/graphs/summary_table.png', dpi=100, bbox_inches='tight')
    print("Generated: docs/graphs/summary_table.png")

    print("\nAll graphs generated successfully!")
    print("Check docs/graphs/ directory")

if __name__ == "__main__":
    try:
        plot_results()
    except Exception as e:
        print(f"Error generating graphs: {e}")
        sys.exit(1)
