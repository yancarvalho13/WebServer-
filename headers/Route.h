#pragma once      
#include "RouteEngineEnums.h"
#include <string>

class Route {
  public:
    Route(Methods metodo ,std::string path); 
    void setHtmlResponse(std::string ); 
    std::string getRouteResponse();
    Methods getMethod();
    std::string getPath();
  private:
  Methods _metodo;
  std::string _path, _response;
};


