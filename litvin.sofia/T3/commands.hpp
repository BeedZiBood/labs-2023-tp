#ifndef T3_COMMANDS_HPP
#define T3_COMMANDS_HPP
#include <map>
#include "polygon.hpp"
namespace litvin
{
  void printInvalidCommand(std::ostream & out);
  using signature_type_1 = void (*)(const std::vector< Polygon > & data, std::ostream & out);
  using signature_type_2 = void (*)(const std::vector< Polygon > & data, const Polygon & pol, std::ostream & out);
  using signature_type_3 = void (*)(const std::vector< Polygon > & data, size_t num, std::ostream & out);
  struct command_dicts
  {
    command_dicts();
    std::map< std::string, signature_type_1 > dict1;
    std::map< std::string, signature_type_2 > dict2;
    std::map< std::string, signature_type_3 > dict3;
    void executeCommand(const std::string & cmd, const std::vector< Polygon > & data, std::ostream & out) const;
    void executeCommand(const std::string & cmd, const std::vector< Polygon > & data, const Polygon & pol,
                        std::ostream & out) const;
    void executeCommand(const std::string & cmd, const std::vector< Polygon > & data, size_t num,
                        std::ostream & out) const;
  };
  using v_pol = std::vector< Polygon >;
  using cmd_d = command_dicts;
  std::string inputCommand(std::istream & in);
  void runCommand(const v_pol & data, const cmd_d & dicts, std::string & cmd, std::ostream & out, std::istream & in);
}
#endif
