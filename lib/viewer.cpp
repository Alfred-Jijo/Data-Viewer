#include <viewer.hpp>

/**
 * @author Alfred Jijo
 * @brief Converts a string to lowercase.
 * @param str The input string.
 * @return The lowercase version of the input string.
 */
std::string DataVwr::toLower(const std::string& str) {
        std::string out = str;
        usize len = out.size();
        for (usize i = 0; i < len; ++i) {
                out[i] = static_cast<char>(
                    std::tolower(static_cast<unsigned char>(out[i])));
        }
        return out;
}

/**
 * @author Alfred Jijo
 * @brief Compares two strings for equality, ignoring case.
 * @param a The first string.
 * @param b The second string.
 * @return True if the strings are equal (ignoring case), false otherwise.
 */
bool DataVwr::equalsIgnoreCase(const std::string& a, const std::string& b) {
        return toLower(a) == toLower(b);
}

/**
 * @author Alfred Jijo
 * @brief Splits a CSV line into fields, handling quoted strings.
 * @param line The input CSV line.
 * @return A vector of strings representing the fields in the line.
 */
std::vector<std::string> DataVwr::splitCSVLine(const std::string& line) {
        std::vector<std::string> result;
        std::string field;
        bool inQuotes = false;
        usize len = line.length();

        for (usize i = 0; i < len; ++i) {
                char c = line[i];
                if (c == '"') {
                        if (inQuotes && (i + 1 < len) && line[i + 1] == '"') {
                                field += '"';
                                ++i;
                        } else {
                                inQuotes = !inQuotes;
                        }
                } else if (c == ',' && !inQuotes) {
                        result.push_back(field);
                        field.clear();
                } else {
                        field += c;
                }
        }
        result.push_back(field);
        return result;
}

/**
 * @author Alfred Jijo
 * @brief Reads a CSV file and returns its contents as a vector of vectors of
 * strings.
 * @param filename The name of the CSV file.
 * @return A vector of vectors of strings representing the CSV data.
 */
std::vector<std::vector<std::string>> DataVwr::readCSV(
    const std::string& filename) {
        std::ifstream file(filename);
        std::vector<std::vector<std::string>> data;
        std::string line;

        if (!file.is_open()) {
                std::cerr << "Error: Could not open file " << filename << '\n';
                return data;
        }

        while (std::getline(file, line)) {
                if (!line.empty()) {
                        std::vector<std::string> row = splitCSVLine(line);
                        data.push_back(row);
                }
        }

        file.close();
        return data;
}

/**
 * @author Alfred Jijo
 * @brief Displays a table of data in the console.
 * @param data The data to display, represented as a vector of vectors of
 * strings.
 * @note The first row is treated as the header.
 */
void DataVwr::displayTable(const std::vector<std::vector<std::string>>& data) {
        if (data.empty()) return;

        usize cols = data[0].size();
        std::vector<usize> colWidths(cols, 0);

        for (usize r = 0; r < data.size(); ++r) {
                for (usize c = 0; c < data[r].size(); ++c) {
                        usize cellLen = data[r][c].size();
                        if (cellLen > colWidths[c]) {
                                colWidths[c] = cellLen;
                        }
                }
        }

        for (usize r = 0; r < data.size(); ++r) {
                for (usize c = 0; c < data[r].size(); ++c) {
                        std::cout
                            << std::left
                            << std::setw(static_cast<int>(colWidths[c] + 2))
                            << data[r][c];
                }
                std::cout << '\n';
        }
}

/**
 * @author Alfred Jijo
 * @brief Filters the data by a specific column and value.
 * @param data The data to filter, represented as a vector of vectors of
 * strings.
 * @param columnName The name of the column to filter by.
 * @param matchValue The value to match in the specified column.
 * @param caseInsensitive Whether to perform a case-insensitive match.
 * @return A vector of vectors of strings representing the filtered data.
 */
std::vector<std::vector<std::string>> DataVwr::filterByColumn(
    const std::vector<std::vector<std::string>>& data,
    const std::string& columnName, const std::string& matchValue,
    bool caseInsensitive) {
        std::vector<std::vector<std::string>> filtered;
        if (data.empty()) return filtered;

        filtered.push_back(data[0]);  // header

        const std::vector<std::string>& header = data[0];
        usize colIndex = 0;
        bool found = false;
        for (usize i = 0; i < header.size(); ++i) {
                if (header[i] == columnName) {
                        colIndex = i;
                        found = true;
                        break;
                }
        }

        if (!found) {
                std::cerr << "Column '" << columnName << "' not found.\n";
                return data;
        }

        for (usize i = 1; i < data.size(); ++i) {
                if (colIndex < data[i].size()) {
                        const std::string& val = data[i][colIndex];
                        bool match = caseInsensitive
                                         ? equalsIgnoreCase(val, matchValue)
                                         : val == matchValue;
                        if (match) {
                                filtered.push_back(data[i]);
                        }
                }
        }

        return filtered;
}

/**
 * @author Alfred Jijo
 * @brief Sorts the data by a specific column.
 * @param data The data to sort, represented as a vector of vectors of strings.
 * @param columnName The name of the column to sort by.
 * @param ascending Whether to sort in ascending order (true) or descending
 * order (false).
 */
void DataVwr::sortByColumn(std::vector<std::vector<std::string>>& data,
                           const std::string& columnName, bool ascending) {
        if (data.size() <= 1) return;

        const std::vector<std::string>& header = data[0];
        usize colIndex = 0;
        bool found = false;
        for (usize i = 0; i < header.size(); ++i) {
                if (header[i] == columnName) {
                        colIndex = i;
                        found = true;
                        break;
                }
        }

        if (!found) {
                std::cerr << "Column '" << columnName << "' not found.\n";
                return;
        }

        std::sort(
            data.begin() + 1, data.end(),
            [colIndex, ascending](const std::vector<std::string>& a,
                                  const std::vector<std::string>& b) -> bool {
                    if (colIndex >= a.size() || colIndex >= b.size())
                            return false;
                    return ascending ? (a[colIndex] < b[colIndex])
                                     : (a[colIndex] > b[colIndex]);
            });
}
