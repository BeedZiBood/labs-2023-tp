#ifndef T3_POLYGON_H
#define T3_POLYGON_H
#include <vector>
#include <iostream>

namespace mashkin
{
  struct Point
  {
    int x, y;
    bool operator==(const Point& rhs) const;
    bool operator<(const Point& rhs);
  };

  struct Polygon
  {
    std::vector< Point > points;
    bool operator<(const Polygon& rhs);
  };

  std::istream& operator>>(std::istream& inp, Point& point);
  std::istream& operator>>(std::istream& inp, Polygon& dest);
}
#endif