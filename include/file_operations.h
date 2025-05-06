#pragma once

#include <iostream>
#include <fstream>

// Returns an ifstream if it can find a fucking file
std::ifstream openFile(const std::string filePath);