#include <viewer.hpp>

namespace DataVwr {

    std::string toLower(const std::string& str) {
        std::string out = str;
        usize len = out.size();
        for (usize i = 0; i < len; ++i) {
            out[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(out[i])));
        }
        return out;
    }

    bool equalsIgnoreCase(const std::string& a, const std::string& b) {
        return toLower(a) == toLower(b);
    }

    std::vector<std::string> splitCSVLine(const std::string& line) {
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

    std::vector<std::vector<std::string>> readCSV(const std::string& filename) {
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

    void displayTable(const std::vector<std::vector<std::string>>& data) {
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
                std::cout << std::left << std::setw(static_cast<int>(colWidths[c] + 2)) << data[r][c];
            }
            std::cout << '\n';
        }
    }

    std::vector<std::vector<std::string>> filterByColumn(
        const std::vector<std::vector<std::string>>& data,
        const std::string& columnName,
        const std::string& matchValue,
        bool caseInsensitive
    ) {
        std::vector<std::vector<std::string>> filtered;
        if (data.empty()) return filtered;

        filtered.push_back(data[0]); // header

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
                bool match = caseInsensitive ? equalsIgnoreCase(val, matchValue) : val == matchValue;
                if (match) {
                    filtered.push_back(data[i]);
                }
            }
        }

        return filtered;
    }

    void sortByColumn(
        std::vector<std::vector<std::string>>& data,
        const std::string& columnName,
        bool ascending
    ) {
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

        std::sort(data.begin() + 1, data.end(),
            [colIndex, ascending](const std::vector<std::string>& a, const std::vector<std::string>& b) -> bool {
                if (colIndex >= a.size() || colIndex >= b.size()) return false;
                return ascending ? (a[colIndex] < b[colIndex]) : (a[colIndex] > b[colIndex]);
            });
    }

}
