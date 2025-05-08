#include "viewer.hpp"
#include "typedef.h"
#include <iostream>

int main() {
    std::string filename;
    std::cout << "Enter CSV file name: ";
    std::cin >> filename;

    std::vector<std::vector<std::string>> data = DataVwr::readCSV(filename);
    if (data.empty()) return 1;

    std::string choice;
    while (true) {
	std::cout << "\nOptions:\n"
		  << "1. Filter by column\n"
		  << "2. Sort by column\n"
		  << "3. Display full data\n"
		  << "4. Exit\n"
		  << "Enter choice: ";
	std::cin >> choice;

	if (choice == "1") {
	    std::string col, val;
	    char ci;
	    std::cout << "Column name: ";
	    std::cin >> col;
	    std::cout << "Value to match: ";
	    std::cin >> val;
	    std::cout << "Case-insensitive? (y/n): ";
	    std::cin >> ci;
	    std::vector<std::vector<std::string>> filtered =
		DataVwr::filterByColumn(data, col, val, (ci == 'y' || ci == 'Y'));
	    DataVwr::displayTable(filtered);
	} else if (choice == "2") {
	    std::string col, dir;
	    std::cout << "Column name: ";
	    std::cin >> col;
	    std::cout << "Direction (asc/desc): ";
	    std::cin >> dir;
	    bool ascending = (dir == "asc");
	    DataVwr::sortByColumn(data, col, ascending);
	    DataVwr::displayTable(data);
	} else if (choice == "3") {
	    DataVwr::displayTable(data);
	} else if (choice == "4") {
	    break;
	} else {
	    std::cout << "Invalid option.\n";
	}
    }

    return 0;
}
