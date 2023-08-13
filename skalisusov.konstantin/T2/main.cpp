#include <vector>
#include <iterator>
#include <algorithm>
#include "DataStruct.h"

int main()
{
  using skalisusov::DataStruct;
  std::vector< DataStruct > vector;
  while(!std::cin.eof())
  {
    std::copy(std::istream_iterator< DataStruct >(std::cin),
              std::istream_iterator< DataStruct >(),
              std::back_inserter(vector));
    if(!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::sort(std::begin(vector), std::end(vector),skalisusov::comparate);
  std::copy(std::begin(vector),
            std::end(vector),
            std::ostream_iterator< DataStruct >(std::cout, "\n"));
  return 0;
}
