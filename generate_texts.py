#!/usr/bin/env python3
"""
Simple script to generate 100 text files with 1000+ words each.
Uses sample text content repeated to meet word count requirement.
"""

import os

# Sample paragraphs to use for text generation
paragraphs = [
    "In the field of computer science, caching is a fundamental technique used to improve system performance. "
    "A cache stores frequently accessed data in a faster storage layer, reducing the need to retrieve data from slower storage. "
    "This mechanism is crucial in modern computing systems, from web browsers to database management systems.",

    "Cache replacement algorithms determine which items to remove when the cache is full and new data needs to be stored. "
    "Different algorithms have different performance characteristics depending on the access patterns. "
    "The choice of algorithm can significantly impact the overall system performance and efficiency.",

    "FIFO, or First In First Out, is the simplest cache replacement algorithm. "
    "It removes the oldest entry in the cache when space is needed. "
    "While easy to implement, FIFO does not consider how frequently or recently an item was accessed.",

    "LRU, or Least Recently Used, removes the item that has not been accessed for the longest time. "
    "This algorithm assumes that recently accessed items are more likely to be accessed again soon. "
    "LRU generally provides better performance than FIFO for many workloads.",

    "LFU, or Least Frequently Used, tracks how many times each item has been accessed. "
    "When eviction is needed, it removes the item with the lowest access count. "
    "This algorithm works well when some items are consistently more popular than others.",

    "Understanding cache behavior requires analyzing hit rates and miss rates. "
    "A cache hit occurs when requested data is found in the cache. "
    "A cache miss happens when the data must be retrieved from slower storage.",

    "The temporal locality principle states that recently accessed data is likely to be accessed again soon. "
    "The spatial locality principle suggests that data near recently accessed data will likely be accessed next. "
    "These principles guide the design of effective caching strategies.",

    "Memory hierarchies in computer systems include registers, cache, main memory, and disk storage. "
    "Each level offers different trade-offs between speed, cost, and capacity. "
    "Effective caching helps bridge the performance gap between these levels.",
]

def generate_text_file(file_num, target_words=1200):
    """Generate a single text file with at least target_words words."""
    words = []
    para_idx = 0

    # Keep adding paragraphs until we reach target word count
    while len(words) < target_words:
        # Add paragraph
        para_words = paragraphs[para_idx % len(paragraphs)].split()
        words.extend(para_words)

        # Add some variation
        words.append(f"Section {len(words) // 100}.")
        words.append(f"Document {file_num}.")

        para_idx += 1

    # Join words into text with proper formatting
    text = ""
    for i, word in enumerate(words):
        text += word + " "
        # Add newlines every 15 words for readability
        if (i + 1) % 15 == 0:
            text += "\n"

    return text

def main():
    print("Generating 100 text files...")

    texts_dir = "texts"
    if not os.path.exists(texts_dir):
        os.makedirs(texts_dir)

    for i in range(1, 101):
        filename = os.path.join(texts_dir, f"{i}.txt")
        content = generate_text_file(i)

        with open(filename, 'w') as f:
            f.write(content)

        # Count actual words
        word_count = len(content.split())

        if i % 10 == 0:
            print(f"Generated {i}/100 files...")

    print("Done! All 100 text files created.")
    print(f"Each file has ~1200 words.")

if __name__ == "__main__":
    main()
