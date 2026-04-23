#include "headers/RouteEngineEnums.h"
#include <fstream>
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

std::string parseHtmlToString(std::string htmlPath)
{
  std::ifstream file(htmlPath);
  if(!file.is_open())
  {
    perror("Falha ao abrir o html ou caminho incorreto");
    return "";
  }
  std::stringstream buffer;

  buffer << file.rdbuf();
  
  std::string html = buffer.str();
    
  std::string response = 
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Content-Length: " + std::to_string(html.size()) + "\r\n"
    "Connection: close\r\n"
    "\r\n"
    + html; return response;
}
