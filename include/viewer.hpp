#pragma once

#include <typedef.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>

namespace DataVwr {

    std::vector<std::string> splitCSVLine(const std::string& line);

    std::vector<std::vector<std::string>> readCSV(const std::string& filename);

    void displayTable(const std::vector<std::vector<std::string>>& data);

    std::vector<std::vector<std::string>> filterByColumn(
        const std::vector<std::vector<std::string>>& data,
        const std::string& columnName,
        const std::string& matchValue,
        bool caseInsensitive = false
    );

    void sortByColumn(
        std::vector<std::vector<std::string>>& data,
        const std::string& columnName,
        bool ascending = true
    );

}