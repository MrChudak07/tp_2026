#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include "data_struct.hpp"

int main() {
    std::vector<kabishev::DataStruct> data;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            continue;
        }
        std::stringstream ss(line);
        kabishev::DataStruct temp;
        if (ss >> temp) {
            data.push_back(temp);
        }
    }

    std::sort(data.begin(), data.end(), kabishev::compareDataStruct);

    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<kabishev::DataStruct>(std::cout, "\n")
    );

    return 0;
}
