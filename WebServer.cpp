#include "headers/Request.h"
#include "headers/Route.h"
#include "headers/RouteEngine.h"
#include "headers/RouteEngineEnums.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
using namespace std;


int main()
{
  int serverSocketFileDescriptor = socket(AF_INET,SOCK_STREAM,0);
  sockaddr_in serverAddress;
  /*AF_INET representa a familia do endereço, no caso IPV4*/
  serverAddress.sin_family = AF_INET;
  /*Usamos htons para converter um inteiro nao assinado de 16bits para ordem de bytes de rede
   * isso garante que o ddo enviado esteja formatado em Big-Endian que e o padrao tcp/ip */
  serverAddress.sin_port = htons(8080);
  serverAddress.sin_addr.s_addr = htons(INADDR_ANY);
  if(bind(serverSocketFileDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress)))
  {
    perror("Falha no bind do socket");
    return 1;
  };

  if(listen(serverSocketFileDescriptor, 5))
  {
    perror("Falha no listen do socket");
    return 1;
  };
  Route* home = new Route(Methods::GET,"/");
  home->setHtmlResponse("html/home.html");
  Route* about = new Route(Methods::GET, "/about");
  about->setHtmlResponse("html/about.html");
  RouteHandler routeHandler;

  routeHandler.mapRoute(*home);
  routeHandler.mapRoute(*about);
  
  char buffer[1024] = {0};

  while (true)
  {
  Request request;
 
  int clientSocketFileDescriptor = accept(serverSocketFileDescriptor, nullptr, nullptr);
  int bytes = recv(clientSocketFileDescriptor, buffer, sizeof(buffer), 0);
  
  request = request.fromHttpRequest(buffer, bytes); 
  
  Response response = routeHandler.handleRequest(request); 

  std::string responseDta = response.getData();

  const char* msgBuffer = responseDta.data(); 
  
  write(clientSocketFileDescriptor, msgBuffer, responseDta.size()); 
  
  close(clientSocketFileDescriptor);
  }

  close(serverSocketFileDescriptor);
}
