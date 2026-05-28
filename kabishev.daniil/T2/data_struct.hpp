#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iostream>
#include <string>
#include <utility>

namespace kabishev {

    struct DataStruct {
        std::pair<long long, unsigned long long> key1; // RAT LSP (:N 1:D 2:)
        unsigned long long key2;                       // ULL HEX 0xFA
        std::string key3;                              // String "Data"
    };

    std::istream& operator>>(std::istream& in, DataStruct& input);
    std::ostream& operator<<(std::ostream& out, const DataStruct& src);

    bool compareDataStruct(const DataStruct& a, const DataStruct& b);

}

#endif
