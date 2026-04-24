#include "headers/Route.h"
#include "headers/RouteEngineEnums.h"
#include "headers/WebServer.h"
#include <asm-generic/socket.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <iostream>
#include <ostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>


int main()
{
 try{ 
  Route* portfolio = new Route(Methods::GET, "/");
  portfolio->setHtmlResponse("assets/portfolio.html");
  
  WebServer* webServer = new WebServer(8080,10);
  webServer->start();
  
  webServer->mapRoute(*portfolio);

  std::cout << "Type anything to stop" << std::endl;
  std::string exit; 
  std::cin >> exit;
  if(!exit.empty())
  {
    webServer->stop();
  }
  }catch(std::exception)
  {
   
  }
}
