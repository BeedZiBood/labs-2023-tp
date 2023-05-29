// IN FRAME   SAME
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include "Commands.h"
#include "Geometry.h"

constexpr size_t MAX_STREAM_SIZE =
  std::numeric_limits< std::streamsize >::max();

int main(int argc, char* argv[])
{
  if (argc != 2) {
    std::cerr << "Not enough arguments" << '\n';
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open()) {
    std::cerr << "Couldn't open a file" << '\n';
    return 1;
  }
  std::vector< ganiullin::Polygon > polygons;
  while (!file.eof()) {
    using inputPolyIt = std::istream_iterator< ganiullin::Polygon >;
    std::copy(inputPolyIt(file), inputPolyIt(), std::back_inserter(polygons));
    if (!file) {
      file.clear();
      file.ignore(MAX_STREAM_SIZE, '\n');
    }
  }

  auto commands = ganiullin::createCommandDicts();
  auto readCommand =
    std::bind(ganiullin::readCommand, std::ref(std::cin), commands);
  auto execCommand = std::bind(ganiullin::executeCommand, readCommand, polygons,
    commands, std::ref(std::cin), std::ref(std::cout));

  while (!std::cin.eof()) {
    try {
      execCommand();
      std::cout << '\n';
    } catch (const std::logic_error& e) {
      ganiullin::printErrorMessage(std::cout);
      std::cout << '\n';
      std::cin.ignore(MAX_STREAM_SIZE, '\n');
    } catch (const std::runtime_error& e) {
      break;
    }
  }
  return 0;
}
