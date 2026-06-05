#include "polygon.hpp"
#include <algorithm>

bool operator==(const Point &a, const Point &b)
{
  return a.x == b.x && a.y == b.y;
}

bool operator==(const Polygon &a, const Polygon &b)
{
  if (a.points.size() != b.points.size())
    return false;
  return std::equal(a.points.begin(), a.points.end(), b.points.begin());
}

std::istream &operator>>(std::istream &in, Point &p)
{
  char c1, c2, c3;
  if (in >> c1 >> p.x >> c2 >> p.y >> c3)
  {
    if (c1 != '(' || c2 != ';' || c3 != ')')
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}

std::istream &operator>>(std::istream &in, Polygon &poly)
{
  size_t num;
  if (!(in >> num))
    return in;
  poly.points.resize(num);
  for (size_t i = 0; i < num; ++i)
  {
    if (!(in >> poly.points[i]))
    {
      in.setstate(std::ios::failbit);
      return in;
    }
  }
  return in;
}
