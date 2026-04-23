#include "headers/Request.h"
#include "headers/RouteEngineEnums.h"
#include "headers/RouteEngineHelpers.h"
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <Web>
Request::Request(Methods metodo, std::string path, std::string url)
{ 
  _metodo = metodo;
  _path = path;
  _url = url;
}

Request Request::fromHttpRequest(char buffer[], int size)
{

  std::vector<std::string>lines;
  std::string msg = "";
  for(int i = 0; i < size; i++)
  {
    if(buffer[i] != '\n' && buffer[i] != '\r')
    {
      msg += buffer[i];
    }
    else {
      if(!msg.empty())
      {
        lines.push_back(msg);
        msg.clear();
      }
    }
  }
  std::string firstLine = lines.at(0);
  Methods metodo;
  std::string path;
  std::string url;
  std::vector<std::string> firstLineWords = extractWords(lines.at(0));
  std::vector<std::string> secondLineWords = extractWords(lines.at(1));
  
  metodo = getMethodEnumFromString(firstLineWords.at(0));
  path = firstLineWords.at(1);
  url = secondLineWords.at(1);

  Request parsedRequest(metodo, path, url);
  parsedRequest.to_string();
  for(std::string line : lines)
  {
    std::cout << "LogRequestParseer: " << line << std::endl;
  }
  return  parsedRequest;
}

std::string Request::getPath()
{
  return _path; 
}

Methods Request::getMethod()
{
  return _metodo;
}
