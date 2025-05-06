#include <iostream>
#include <fstream>

std::ifstream openFile(const std::string filePath) {
    std::ifstream file;
    // Pray to the gods of C++ that this will work
    try {
        file = std::ifstream(filePath);
        if (!file.is_open()) {
            throw std::errc::io_error;
        }
    } catch (std::errc e) {
        std::cerr << "Error opening file" << std::endl;
        return std::ifstream(nullptr);
    }
    return file;
}