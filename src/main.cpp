#include <typedef.h>
#include <stb_ds.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <file_operations.h>

int main(void) {
	std::cout << "Hello, World!" << std::endl;
	std::string line, value;
	std::vector<std::vector<std::string>> table;
	std::ifstream file = openFile("hi.csv");
	
#ifdef DEBUG
std::cout << "Debug mode is enabled." << std::endl;
#endif

#ifdef _DEBUG
std::cout << "Not debug" << std::endl;
#endif

	file.close();
	return 0;
}