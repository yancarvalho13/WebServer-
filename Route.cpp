#include "headers/Route.h"
Route::Route(Methods metodo, std::string path) 
{
 _metodo = metodo;
 _path = path;
};

std::string Route::getPath()
{
  return _path;
}

Methods Route::getMethod()
{
  return _metodo;
}

void Route::setHtmlResponse(std::string path)
{

};

std::string Route::getRouteResponse()
{
  return _response;
}


