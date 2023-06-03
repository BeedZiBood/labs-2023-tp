#include "commands.hpp"
#include <iostream>

namespace malaya
{
  void info(std::ostream & out)
  {
    out << "INFO - shows all commands and short info about them\n";
    out << "MAN <command> - shows full information about command\n";
    out << "MERGE <dict1> <dict2> <dest> - merges two dictionaries and writes result ";
    out << "to dest dictionary\n";
    out << "GET_INTERSECTION <dict1> <dict2> <dest> - puts same elements of two dictionaries to dest\n";
    out << "SEARCH <dict> <key> - searches the element in dictionary and shows the value\n";
    out << "INSERTS <dict> <key> - inserts key to dictionary\n";
    out << "DELETE_KEY <dict> <key> - deletes key from dictionary\n";
    out << "DELETE_DICT <dict> <key> - deletes dictionary\n";
    out << "PRINT <dict> - prints all keys from dictionaries with their values\n";
    out << "ARE_SAME <dict1> <dict2> - checks if two dictionaries are identical\n";
    out << "DO_SYMMETRIC_DIFFERENCE <dict1> <dict2> <dest> - fills new dest dictionary ";
    out << "with symmetric difference of two dictionaries\n";
    out << "SUBTRACT <dict1> <dict2> <dest> - fills new dest dictionary with subtraction ";
    out << "of two dictionaries\n";
    out << "FIND_MOST_FREQUENT <dict1> - shows the most frequent word in the dict\n";
    out << "IS_SUBSET <dict1> <dict2> - checks if one dictionary is subset of another\n";
  }

}