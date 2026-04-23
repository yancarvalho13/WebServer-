#pragma once
#include "Route.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include "Request.h"
#include "Response.h"
class RouteHandler{
  public:
    RouteHandler();
    void mapRoute(Route route);
    Response handleRequest(Request request);
    Route getRoute(std::string path);
  private:
    std::vector<Route> _routes;
};
