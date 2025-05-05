#include <typedef.h>
#include <stb_ds.h>

#include <iostream>
#include <fstream>
#include <vector>

int main(void) {
	std::cout << "Hello, World!" << std::endl;
	std::string line, value;
	std::vector<std::vector<std::string>> table;
	std::ifstream file("data.csv");

	file.close();
	return 0;
}