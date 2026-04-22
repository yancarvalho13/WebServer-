#include <cstring>
#include <iostream>
#include <ostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
using namespace std;


class request {
  public:
    request(string metodo, string path)
    {
      _metodo = metodo;
      _path = path;
    }

  private:
    std::string _metodo, _path;
};

std::string formatHttpHtmlResponse(){
  
  std::string html = "<html><body><h1>Ola usuario</h1></body></html>";

  std::string response = 
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Content-Length: " + std::to_string(html.length()) + "\r\n"
    "Connection: close\r\n"
    "\r\n"
    + html;

  return response;
}

int main()
{
  int serverSocketFileDescriptor = socket(AF_INET,SOCK_STREAM,0);
  sockaddr_in serverAddress;
  /*AF_INET representa a familia do endereço, no caso IPV4*/
  serverAddress.sin_family = AF_INET;
  /*Usamos htons para converter um inteiro nao assinado de 16bits para ordem de bytes de rede
   * isso garante que o ddo enviado esteja formatado em Big-Endian que e o padrao tcp/ip */
  serverAddress.sin_port = htons(8080);
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  bind(serverSocketFileDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

  listen(serverSocketFileDescriptor, 5);
  
  char buffer[1024] = {0};

  while (true)
  {
  int clientSocketFileDescriptor = accept(serverSocketFileDescriptor, nullptr, nullptr);
  recv(clientSocketFileDescriptor, buffer, sizeof(buffer), 0);

  std::string msg = "";
  for(int i = 0; i < sizeof(buffer); i++)
  {
    if(buffer[i] != '\n' && buffer[i] != '\r')
    {
      msg += buffer[i];
    }
    else {
      if(!msg.empty())
      {
        std::cout << "Menssagem do cliente: " << msg << std::endl;
        msg.clear();
      }
    }
  }
   msg = formatHttpHtmlResponse();
  const char* msgBuffer = msg.data();
  write(clientSocketFileDescriptor, msgBuffer, strlen(msgBuffer));
  close(clientSocketFileDescriptor);
  }

  close(serverSocketFileDescriptor);
}
