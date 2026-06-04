#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>
#include "geometry.hpp"

std::vector<Polygon> readPolygons(const std::string& filename);

struct PolygonEqual
{
    bool operator()(const Polygon& a, const Polygon& b) const { return a == b; }
};

#endif
