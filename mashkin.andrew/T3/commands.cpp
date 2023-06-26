#include "commands.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
#include <iostream>
#include <iterator>
#include "polygon.h"
#include "solvingCommands.h"

using namespace std::placeholders;

/*void runRightshapes(std::istream& inp, std::string& command);
void runPerms(std::istream& inp, std::string& command);
void runCount(std::istream& inp, std::string& command);
void runMin(std::istream& inp, std::string& command);
void runMax(std::istream& inp, std::string& command);*/
void runArea(std::istream& inp, std::string& command, const std::vector< mashkin::Polygon >& res);

void runEven(const std::vector< mashkin::Polygon >& res)
{
  using pol = mashkin::Polygon;
  using outIter = std::ostream_iterator< mashkin::FullArea >;
  std::vector< pol > data = res;
  std::vector< pol >::iterator it = std::partition(data.begin(), data.end(), mashkin::isEven);
  std::vector< mashkin::FullArea > areas = mashkin::getFullArea(data.begin(), it);
  std::copy(areas.begin(), areas.end(), outIter(std::cout, "\n"));
}

void runOdd(const std::vector< mashkin::Polygon >& res)
{
  using pol = mashkin::Polygon;
  using outIter = std::ostream_iterator< mashkin::FullArea >;
  std::vector< pol > data = res;
  std::vector< pol >::iterator it = std::partition(data.begin(), data.end(), mashkin::isOdd);
  std::vector< mashkin::FullArea > areas = mashkin::getFullArea(data.begin(), it);
  std::copy(areas.begin(), areas.end(), outIter(std::cout, "\n"));
}

/*void runMean();
void runAreaNumOfVertexes(std::string& command);*/

void runArea(std::istream& inp, std::string& command, const std::vector< mashkin::Polygon >& res)
{
  inp >> command;
  if (command == "EVEN")
  {
    runEven(res);
  }
  else if (command == "ODD")
  {
    runOdd(res);
  }
  /*else if (command == "MEAN")
  {
    runMean();
  }
  else if (command.find_first_not_of("0123456789") == std::string::npos)
  {
    runAreaNumOfVertexes(command);
  }*/
  else
  {
    std::cout << " <INVALID COMMAND>";
  }
}

namespace mashkin
{
  void runCommand(std::istream& inp, std::string& command, const std::vector< Polygon >& res)
  {
    inp >> command;
    if (command == "AREA")
    {
      runArea(inp, command, res);
    }
    /*else if (command == "MAX")
    {
      runMax(inp, command);
    }
    else if (command == "MIN")
    {
      runMin(inp, command);
    }
    else if (command == "COUNT")
    {
      runCount(inp, command);
    }
    else if (command == "PERMS")
    {
      runPerms(inp, command);
    }
    else if (command == "RIGHTSHAPES")
    {
      runRightshapes(inp, command);
    }*/
    else
    {
      std::cout << " <INVALID COMMAND>";
    }
  }
}
