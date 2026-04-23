#include "headers/RouteEngine.h"
#include "headers/RouteEngineHelpers.h"
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
    Route* route = nullptr; 
    for(Route& routeItem : _routes)
    {
      if(routeItem.getPath() == request.getPath() && routeItem.getMethod() == request.getMethod())
      {
          route = &routeItem; 
      }
    }

    Response response;

    if(route == nullptr)
    {
      std::string routeResponse = parseHtmlToString("assets/notfound.html");
      response.setData(routeResponse);
      return response;
    }
    response.setData(route->getRouteResponse());
    return response;
}
