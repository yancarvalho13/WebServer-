#include "headers/RouteEngineEnums.h"
#include <sstream>
#include <map>
#include <vector>
#include "headers/RouteEngineHelpers.h"
Methods getMethodEnumFromString(std::string& method)
{
  std::map<std::string, Methods> methodMap =
  {
    {"GET", Methods::GET},
    {"POST", Methods::POST},
    {"PATCH", Methods::PATCH},
    {"PUT", Methods::PUT},
    {"DELETE", Methods::DELETE}
  };

  auto iterator = methodMap.find(method);
  if(iterator != methodMap.end())
  {
    return iterator->second;
  }
  return Methods::UNKNOWN;  
}

std::vector<std::string> extractWords(std::string line)
{
  std::istringstream _stringStream(line);
  std::vector<std::string> words;
  std::string word;

  while(_stringStream >> word)
  {
    words.push_back(word);
  }

  return words;
}
