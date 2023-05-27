#ifndef COMMANDS_H
#define COMMANDS_H
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <functional>
#include "polygon.h"
using namespace std::placeholders;
namespace romanovich
{
  class CommandProcessor
  {
  public:
    CommandProcessor()
    {
      commands["MAX VERTEXES"] = std::bind(&CommandProcessor::calcPointsMax, this, _1);
      commands["MIN VERTEXES"] = std::bind(&CommandProcessor::calcPointsMin, this, _1);
      commands["AREA MEAN"] = std::bind(&CommandProcessor::calcAreaMean, this, _1);
      commands["AREA EVEN"] = std::bind(&CommandProcessor::calcAreaOdd, this, _1);
      commands["AREA ODD"] = std::bind(&CommandProcessor::calcAreaEven, this, _1);
      commands["COUNT EVEN"] = std::bind(&CommandProcessor::countEven, this, _1);
      commands["MAX AREA"] = std::bind(&CommandProcessor::calcAreaMax, this, _1);
      commands["MIN AREA"] = std::bind(&CommandProcessor::calcAreaMin, this, _1);
      commands["COUNT ODD"] = std::bind(&CommandProcessor::countOdd, this, _1);
      commands["RIGHTSHAPES"] = std::bind(&CommandProcessor::countShapesWithRightAngle, this, _1);
      commands["AREA"] = std::bind(&CommandProcessor::calcAreaWithNumber, this, _1, _2);
      commands["COUNT"] = std::bind(&CommandProcessor::countWithNumber, this, _1, _2);
      commands["MAXSEQ"] = std::bind(&CommandProcessor::countMaxSeq, this, _1, _2);
    }
    void operator()(const std::string &command, const std::vector< romanovich::Polygon > &polygons);
    void calcPointsMax(const std::vector< Polygon > &);
    void calcPointsMin(const std::vector< Polygon > &);
    void calcAreaMean(const std::vector< Polygon > &);
    void calcAreaEven(const std::vector< Polygon > &);
    void calcAreaOdd(const std::vector< Polygon > &);
    void calcAreaMin(const std::vector< Polygon > &);
    void calcAreaMax(const std::vector< Polygon > &);
    void countEven(const std::vector< Polygon > &);
    void countOdd(const std::vector< Polygon > &);
    void calcAreaWithNumber(const std::vector< Polygon > &, const std::string &);
    void countWithNumber(const std::vector< Polygon > &, const std::string &);
    void countMaxSeq(const std::vector< Polygon > &, const std::string &);
    void countShapesWithRightAngle(const std::vector< Polygon > &);
    void printError();
  private:
    std::unordered_map< std::string, std::function< void(const std::vector< Polygon > &, std::string)>> commands;
  };
}
#endif
