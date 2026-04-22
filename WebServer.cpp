#include <iostream>
#include <ostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

int main()
{
  int serverSocketFileDescriptor = socket(AF_INET,SOCK_STREAM,0);
  sockaddr_in serverAddress;
  /*AF_INET representa a familia do endereço, no caso IPV4*/
  serverAddress.sin_family = AF_INET;
  /*Usamos htons para converter um inteiro nao assinado de 16bits para ordem de bytes de rede
   * isso garante que o ddo enviado esteja formatado em Big-Endian que e o padrao tcp/ip */
  serverAddress.sin_port = htons(8080);
  serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
  bind(serverSocketFileDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

  listen(serverSocketFileDescriptor, 5);
  int clientSocket = accept(serverSocketFileDescriptor, nullptr, nullptr);

  char buffer[1024] = {0};
  recv(clientSocket, buffer, sizeof(buffer), 0);
  std::cout << "Menssagem do cliente: " << buffer << std::endl;
  close(serverSocketFileDescriptor);
}
