#include "solvingCommands.h"
#include <algorithm>
#include <cmath>
#include <numeric>
#include <outputStructs.h>

namespace mashkin
{
  using iter = std::vector< Polygon >::iterator;

  std::vector< FullArea > getFullArea(const iter& begin, const iter& end)
  {
    std::vector< mashkin::PositiveArea > halfPA;
    std::vector< mashkin::NegativeArea > halfNA;
    std::vector< mashkin::FullArea > area;
    std::transform(begin, end, std::back_inserter(halfPA), calcPositiveArea);
    std::transform(begin, end, std::back_inserter(halfNA), calcNegativeArea);
    std::transform(halfPA.begin(), halfPA.end(), halfNA.begin(), std::back_inserter(area), solveArea);
    return area;
  }

  bool isOdd(const Polygon& data)
  {
    return data.points.size() % 2;
  }

  bool isEven(const Polygon& data)
  {
    return !(isOdd(data));
  }

  XMultiY::XMultiY(const Point& first, const Point& second):
    res(first.x * second.y)
  {
  }

  XMultiY::XMultiY(int&& rhs):
    res(rhs)
  {
  }

  XMultiY::XMultiY():
    res(0)
  {
  }

  XMultiY XMultiY::operator+(const XMultiY& rhs)
  {
    return XMultiY{this->res + rhs.res};
  }

  XMultiY solveXY(const Point& lhs, const Point& rhs)
  {
    return XMultiY(lhs, rhs);
  }

  PositiveArea::PositiveArea(const Polygon& lhs)
  {
    std::transform(lhs.points.begin(), --lhs.points.end(), ++lhs.points.begin(), std::back_inserter(this->halfArea),
                   solveXY);
    std::transform(--lhs.points.end(), lhs.points.end(), lhs.points.begin(), std::back_inserter(this->halfArea),
                   solveXY);
  }

  PositiveArea calcPositiveArea(const Polygon& lhs)
  {
    return PositiveArea(lhs);
  }

  NegativeArea::NegativeArea(const Polygon& lhs, const Polygon& rhs)
  {
    std::transform(++lhs.points.begin(), lhs.points.end(), rhs.points.begin(), std::back_inserter(this->halfArea),
                   solveXY);
    std::transform(lhs.points.begin(), ++lhs.points.begin(), --rhs.points.end(), std::back_inserter(this->halfArea),
                   solveXY);
  }

  NegativeArea calcNegativeArea(const Polygon& lhs)
  {
    auto rhs = lhs;
    return NegativeArea(lhs, rhs);
  }

  FullArea::FullArea(const PositiveArea& first, const NegativeArea& second)
  {
    XMultiY positive = std::accumulate(first.halfArea.begin(), first.halfArea.end(), XMultiY());
    XMultiY negative = std::accumulate(second.halfArea.begin(), second.halfArea.end(), XMultiY());
    int almostRes = std::abs(positive.res - negative.res);
    res = static_cast< double >(almostRes) * 0.5;
  }

  FullArea solveArea(const PositiveArea& first, const NegativeArea& second)
  {
    return FullArea(first, second);
  }

  std::ostream& operator<<(std::ostream& out, const FullArea& data)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << data.res;
  }
}