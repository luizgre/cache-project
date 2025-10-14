#include "text_loader.h"
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>

std::string loadTextFromDisk(int id) {
    // Simulate slow disk access
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    std::string filename = "texts/" + std::to_string(id) + ".txt";
    std::ifstream file(filename);

    if (!file.is_open()) {
        return "Error: Text not found";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}
