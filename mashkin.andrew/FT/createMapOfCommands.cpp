#include "createMapOfCommands.h"
#include <iostream>
#include <map>
#include "commands.h"

namespace mashkin
{
  void createMapOfCommands(MapOfCommands& mapOfCommands)
  {
    mapOfCommands["add"] = addExpr;
    mapOfCommands["simplify"] = simplifyExpr;
    mapOfCommands["parameters"] = getParameters;
    mapOfCommands["set"] = setNewExpr;
    mapOfCommands["show"] = showExpr;
  }
}
