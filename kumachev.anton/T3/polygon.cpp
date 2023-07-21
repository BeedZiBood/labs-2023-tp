#include "polygon.h"
#include <iterator>
#include <algorithm>
#include <functional>
#include <numeric>

namespace kumachev {
  static double getTriangleArea(const Point &p1, const Point &p2)
  {
    return p1.x * p2.y - p1.y * p2.x;
  }

  size_t vertex(const Polygon &polygon)
  {
    return polygon.points.size();
  }

  double getArea(const Polygon &polygon)
  {
    using namespace std::placeholders;
    auto areaOperator = std::bind(getTriangleArea, _2, _1);

    std::vector< double > values;
    auto backInserter = std::back_inserter(values);

    auto first = polygon.points.begin();
    auto second = first;
    ++second;
    auto end = polygon.points.end();

    std::transform(second, end, first, backInserter, areaOperator);
    double area = std::accumulate(values.begin(), values.end(), .0);
    area += areaOperator(polygon.points.front(), polygon.points.back());
    area = std::abs(area) / 2;

    return area;
  }

  bool PointComparator::operator()(const Point &lhs, const Point &rhs)
  {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }

  bool PolygonComparator::operator()(const Polygon &lhs, const Polygon &rhs)
  {
    if (lhs.points.size() != rhs.points.size()) {
      return false;
    }

    auto leftBegin = lhs.points.begin();
    auto leftEnd = lhs.points.begin();
    auto rightBegin = lhs.points.begin();
    PointComparator comp;

    return std::equal(leftBegin, leftEnd, rightBegin, comp);
  }
}
