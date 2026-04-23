#include "headers/RouteEngine.h"
#include <cstdio>
#include <stdexcept>
#include <string>

RouteHandler::RouteHandler()
{

}

void RouteHandler::mapRoute(Route route)
{
  _routes.push_back(route);
}

Route RouteHandler::getRoute(std::string path)
{
  for(Route route : _routes)
  {
    if(route.getPath() == path)
    {
      return route;
    }
  }
  throw std::invalid_argument("Essa rota não existe ou nao foi cadastrada");
}

Response RouteHandler::handleRequest(Request request)
{
    Route* route; 
    for(Route& routeItem : _routes)
    {
      if(routeItem.getPath() == request.getPath() && routeItem.getMethod() == request.getMethod())
      {
          route = &routeItem; 
      }
    }
    if(route == nullptr)
    {
      throw std::invalid_argument("Rota não encontada para o caminho: " + request.getPath());
    }
    Response response;
    response.setData(route->getRouteResponse());
    return response;
}
