#pragma once
#include "RouteEngineEnums.h"
#include <string>
class Request {
  public:
    Request(Methods metodo,std::string path, std::string url);
    Request fromHttpRequest(char buffer[] ,int size);
    std::string getPath();
    Methods getMethod();
    void to_string();
    // {
    //   std::cout << _metodo  << " From: " << _url << " Requesting: " << _path << std::endl;
    // }

  private:
   Methods _metodo;
   std::string _path, _url;
};
