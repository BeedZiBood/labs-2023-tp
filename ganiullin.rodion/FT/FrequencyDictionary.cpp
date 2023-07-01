#include "FrequencyDictionary.h"

#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include "TypesIO.h"

namespace {
  bool compareNodes(const ganiullin::NodeType& lhs,
      const ganiullin::NodeType& rhs)
  {
    if (lhs.second == rhs.second) {
      return lhs.first < rhs.first;
    }
    return lhs.second > rhs.second;
  }
}
using InS = std::istream;
using OutS = std::ostream;
using Dict = ganiullin::Dict;

Dict ganiullin::getIntersect(const Dict& lhs, const Dict& rhs,
    const SubComm func)
{
  Dict res;

  for (const NodeType& elem : lhs) {
    if (rhs.find(elem.first) != rhs.end()) {
      size_t valueToInsert = func(elem.second, rhs.find(elem.first)->second);
      res[elem.first] = valueToInsert;
    }
  }
  return res;
}

Dict ganiullin::merge(const Dict& lhs, const Dict& rhs, const SubComm func)
{
  Dict res;
  res.reserve(std::max(lhs.size(), rhs.size()));

  for (const NodeType& elem : lhs) {
    size_t valueToInsert = 0;
    if (rhs.find(elem.first) != rhs.end()) {
      valueToInsert = func(elem.second, rhs.find(elem.first)->second);
    } else {
      valueToInsert = elem.second;
    }
    res[elem.first] = valueToInsert;
  }
  for (const NodeType& elem : rhs) {
    if (res.find(elem.first) == res.end()) {
      res[elem.first] = elem.second;
    }
  }
  return res;
}

Dict ganiullin::getDifference(const Dict& lhs, const Dict& rhs)
{
  Dict res;

  for (const NodeType& elem : lhs) {
    if (rhs.find(elem.first) == rhs.end()) {
      res[elem.first] = elem.second;
    }
  }
  for (const NodeType& elem : rhs) {
    if (lhs.find(elem.first) == lhs.end()) {
      res[elem.first] = elem.second;
    }
  }
  return res;
}
template < class T >
ganiullin::VectorDict ganiullin::getSorted(const Dict& src, const T& predicate)
{
  VectorDict res;
  res.reserve(src.size());
  auto dictBeginIt = std::begin(src);
  auto dictEndIt = std::end(src);
  auto resInsertIt = std::back_inserter(res);
  std::copy(dictBeginIt, dictEndIt, resInsertIt);
  auto resBeginIt = std::begin(res);
  auto resEndIt = std::end(res);

  std::sort(resBeginIt, resEndIt, predicate);
  return res;
}
OutS& ganiullin::print(OutS& out, const Dict& src)
{
  VectorDict res = getSorted(src, compareNodes);
  printSomeElems(out, res, res.size());

  return out;
}
OutS& ganiullin::printRareElems(OutS& out, const Dict& src, size_t num)
{
  using namespace std::placeholders;
  auto compareNodesObj = std::bind(compareNodes, _1, _2);
  auto compareNodesRev = std::bind(std::logical_not< bool >{}, compareNodesObj);

  VectorDict res = getSorted(src, compareNodesRev);

  printSomeElems(out, res, num);
  return out;
}
OutS& ganiullin::printCommonElems(OutS& out, const Dict& src, size_t num)
{
  using namespace std::placeholders;
  auto compareNodesObj = std::bind(compareNodes, _1, _2);
  VectorDict res = getSorted(src, compareNodesObj);

  printSomeElems(out, res, num);
  return out;
}
OutS& ganiullin::printSomeElems(OutS& out, const VectorDict& src, size_t num)
{
  for (size_t i = 0; i < num && i < src.size(); i++) {
    NodeType elem = src[i];
    out << EntryO{elem};
    if (i != num - 1 && i != src.size() - 1) {
      out << '\n';
    }
  }
  return out;
}
InS& ganiullin::readText(InS& in, Dict& src)
{
  while (!in.eof()) {
    std::string word = "";
    in >> WordIO{word};
    if (word.size() != 0) {
      src[word] += 1;
    }
  }
  return in;
}
std::ifstream& ganiullin::loadDict(std::ifstream& in, Dict& src)
{
  if (!in.is_open()) {
    throw std::runtime_error("Could not open file");
  }
  while (in.peek() != '\n' && in) {
    std::string word = "";
    size_t val = 0;

    in >> EntryI{word, val};
    src[word] = val;
  }
  return in;
}
std::ofstream& ganiullin::saveDict(std::ofstream& out, const Dict& src)
{
  if (!out.is_open()) {
    throw std::runtime_error("Could not open file");
  }
  size_t i = 0;
  for (const NodeType& elem : src) {
    i++;
    out << elem.first << ' ' << elem.second;
    if (i < src.size()) {
      out << ' ';
    }
  }
  return out;
}
