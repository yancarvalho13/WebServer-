#pragma once
#include "Request.h"
#include "Route.h"
#include "RouteEngine.h"
#include <queue>
#include <thread>
class WebServer
{
  public:
    WebServer(int serverPort,int connectionQueueSize);
    void start();
    void stop();
    void mapRoute(Route route);

  private:
    int _serverFD, _serverPort, _connectionQueueSize;
    bool _running;
    std::thread _serverThread;
    std::queue<Request> _requestQueue;
    RouteHandler _routeEngine;
    void initializeSockets();
    void processRequests();
};
