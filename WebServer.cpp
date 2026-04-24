#include "headers/WebServer.h"
#include "headers/Request.h"
#include "headers/Route.h"
#include <asm-generic/socket.h>
#include <cstdio>
#include <cstring>
#include <exception>
#include <netinet/in.h>
#include <ostream>
#include <string>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

WebServer::WebServer(int serverPort, int connectionQueueSize)
{
   _serverPort = serverPort;
   _connectionQueueSize = connectionQueueSize;
}
void WebServer::processRequests()
{
  while (!_requestQueue.empty())
  {
    Request request = _requestQueue.front();
    _requestQueue.pop();
    Response response = _routeEngine.handleRequest(request);

    std::string responseData = response.getData();
    const char* responseBufffer  = responseData.data();
    
    write(request.getClientFD(), responseBufffer, responseData.size());
    response.logResponse(); 
    close(request.getClientFD());
  }
}
void WebServer::initializeSockets()
{
  std::cout << "Starting WebServer on port: " << _serverPort << std::endl;
  int serverFD = socket(AF_INET, SOCK_STREAM, 0);
  int option = 1;
  setsockopt(serverFD, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
  
  sockaddr_in serverAddress;

  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(_serverPort);
  serverAddress.sin_addr.s_addr = htons(INADDR_ANY);

  if(bind(serverFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)))
  {
    perror("Fail to bind server socket");
    throw std::exception();
  }
  
  if(listen(serverFD, _connectionQueueSize))
  {
    perror("Fail to listen on server socket");
    throw std::exception();
  }
  _serverFD = serverFD;
  _running = true;
  while(_running)
  { 
  char buffer[4086] = {0};
  Request request;
  int clientFD = accept(serverFD, nullptr, nullptr);
  if(clientFD <= 0 )
    {
      perror("Failed to accept client request on the server.");
      continue;
    }
  int requestBytes = recv(clientFD,buffer,sizeof(buffer),0);
  if(requestBytes <= 0)
    {
      close(clientFD);
      continue;
    }
  request = request.fromHttpRequest(buffer, requestBytes); 
  request.setClientFD(clientFD);
  _requestQueue.push(request);
  processRequests();
  }
  close(_serverFD);
}

void WebServer::start()
{
  _serverThread = std::thread(&WebServer::initializeSockets,this);
  _serverThread.detach();
}

void WebServer::stop()
{
 _running = false;
 _serverThread.join();

}

void WebServer::mapRoute(Route route)
{
  _routeEngine.mapRoute(route);
}
