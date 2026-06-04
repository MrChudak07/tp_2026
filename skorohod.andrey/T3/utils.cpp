#include "utils.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

std::vector<Polygon> readPolygons(const std::string& filename)
{
    std::vector<Polygon> polygons;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open file");
    }
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        int vertexCount;
        if (!(iss >> vertexCount)) continue;
        Polygon poly;
        bool ok = true;
        for (int i = 0; i < vertexCount; ++i)
        {
            char open, semi, close;
            int x, y;
            if (!(iss >> open >> x >> semi >> y >> close) || open != '(' || semi != ';' || close != ')')
            {
                ok = false;
                break;
            }
            poly.points.push_back({x, y});
        }
        if (ok && poly.points.size() == static_cast<size_t>(vertexCount))
        {
            polygons.push_back(std::move(poly));
        }
    }
    return polygons;
}