#include "data_struct.hpp"
#include "iofmtguard.hpp"
#include <iomanip>

namespace kabishev {

struct DelimiterIO {
    char exp;
};

struct RatLspIO {
    std::pair<long long, unsigned long long>& ref;
};

struct UllHexIO {
    unsigned long long& ref;
};

struct StringIO {
    std::string& ref;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
    std::istream::sentry guard(in);
    if (!guard) return in;
    char c = 0;
    in >> c;
    if (c != dest.exp) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, RatLspIO&& dest) {
    std::istream::sentry guard(in);
    if (!guard) return in;

    char c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0;
    long long num = 0;
    unsigned long long den = 0;

    in >> c1 >> c2 >> c3; // Ожидаем '(', ':', 'N'/'D'
    if (c1 != '(' || c2 != ':') {
        in.setstate(std::ios::failbit);
        return in;
    }

    if (c3 == 'N' || c3 == 'n') {
        in >> num >> c4 >> c5 >> den >> c6;
        if (c4 != ':' || (c5 != 'D' && c5 != 'd') || c6 != ':') {
            in.setstate(std::ios::failbit);
        }
    } else if (c3 == 'D' || c3 == 'd') {
        in >> den >> c4 >> c5 >> num >> c6;
        if (c4 != ':' || (c5 != 'N' && c5 != 'n') || c6 != ':') {
            in.setstate(std::ios::failbit);
        }
    } else {
        in.setstate(std::ios::failbit);
    }

    char c_close = 0;
    in >> c_close; // Ожидаем ')'
    if (c_close != ')') {
        in.setstate(std::ios::failbit);
    }

    if (in) {
        dest.ref = {num, den};
    }
    return in;
}

std::istream& operator>>(std::istream& in, UllHexIO&& dest) {
    std::istream::sentry guard(in);
    if (!guard) return in;
    iofmtguard fmtguard(in);

    char c1 = 0, c2 = 0;
    in >> c1 >> c2;
    if (c1 == '0' && (c2 == 'x' || c2 == 'X')) {
        in >> std::hex >> dest.ref;
    } else {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, StringIO&& dest) {
    std::istream::sentry guard(in);
    if (!guard) return in;
    return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
}

std::istream& operator>>(std::istream& in, DataStruct& input) {
    std::istream::sentry guard(in);
    if (!guard) return in;
    iofmtguard fmtguard(in);

    DataStruct temp;
    char c1 = 0, c2 = 0;
    in >> c1 >> c2;
    if (c1 != '(' || c2 != ':') {
        in.setstate(std::ios::failbit);
        return in;
    }

    for (int i = 0; i < 3; ++i) {
        std::string label;
        char c = 0;
        while (in >> c && c != ':') {
            label += c;
        }

        if (label == "key1") {
            in >> RatLspIO{temp.key1};
        } else if (label == "key2") {
            in >> UllHexIO{temp.key2};
        } else if (label == "key3") {
            in >> StringIO{temp.key3};
        } else {
            in.setstate(std::ios::failbit);
        }

        in >> DelimiterIO{':'};
    }

    in >> DelimiterIO{')'};
    if (in) {
        input = temp;
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
    std::ostream::sentry guard(out);
    if (!guard) return out;
    iofmtguard fmtguard(out);

    out << "(:key1 (:N " << src.key1.first << ":D " << src.key1.second << ":)"
        << ":key2 0x" << std::hex << std::uppercase << src.key2
        << ":key3 \"" << src.key3 << "\":)";
    return out;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b) {
    double valA = static_cast<double>(a.key1.first) / a.key1.second;
    double valB = static_cast<double>(b.key1.first) / b.key1.second;
    if (valA != valB) {
        return valA < valB;
    }
    if (a.key2 != b.key2) {
        return a.key2 < b.key2;
    }
    return a.key3 < b.key3;
}

}
