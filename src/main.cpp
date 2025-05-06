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

	file.close();
	return 0;
}