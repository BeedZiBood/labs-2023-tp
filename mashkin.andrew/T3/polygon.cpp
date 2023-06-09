#include "polygon.h"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <inputStructs.h>

namespace mashkin
{
  std::istream& operator>>(std::istream& inp, Point& point)
  {
    std::istream::sentry sentry(inp);
    if (!sentry)
    {
      return inp;
    }
    inp >> DelimiterIO{'('} >> point.x >> DelimiterIO{';'};
    inp >> point.y >> DelimiterIO{')'};
    return inp;
  }

  std::istream& operator>>(std::istream& inp, Polygon& dest)
  {
    std::istream::sentry sentry(inp);
    if (!sentry)
    {
      return inp;
    }
    Polygon input;
    size_t numOfPoints;
    inp >> numOfPoints;
    using inpIter = std::istream_iterator< mashkin::Point >;
    std::copy_n(inpIter(inp), numOfPoints, std::back_inserter(input.points));
    if (inp)
    {
      dest = input;
    }
    return inp;
  }
}