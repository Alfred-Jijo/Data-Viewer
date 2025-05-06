#include <iostream>
#include <fstream>

#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

// Returns an ifstream if it can find a fucking file
std::ifstream openFile(const std::string filePath);

#endif