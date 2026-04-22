#include <algorithm>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>
#include <sstream>
using namespace std;


class Request {
  public:
    Request(string metodo, string path, string url)
    {
      _metodo = metodo;
      _path = path;
      _url = url;
    }

    void to_string()
    {
      cout << _metodo  << " From: " << _url << " Requesting: " << _path << endl;
    }

  private:
    std::string _metodo, _path, _url;
};

vector<string> getWords(string line)
{
  istringstream _stringStream(line);
  vector<string> words;
  string word;

  while(_stringStream >> word)
  {
    words.push_back(word);
  }

  return words;
}

Request HttpRequestParseer(char buffer[], int size)
{

  vector<string> lines;
  

  std::string msg = "";
  for(int i = 0; i < size; i++)
  {
    if(buffer[i] != '\n' && buffer[i] != '\r')
    {
      msg += buffer[i];
    }
    else {
      if(!msg.empty())
      {
        lines.push_back(msg);
        msg.clear();
      }
    }
  }
  string firstLine = lines.at(0);
  string metodo;
  string path;
  string url;
  
  vector<string> firstLineWords = getWords(lines.at(0));
  vector<string> secondLineWords = getWords(lines.at(1));

  Request parsedRequest(firstLineWords.at(0),firstLineWords.at(1),secondLineWords.at(1));
  parsedRequest.to_string();
  for(string line : lines)
  {
    cout << "LogRequestParseer: " << line << endl;
  }
  return  parsedRequest;

}

string HtmlToString(const string& path)
{
  ifstream file(path);
  if(!file.is_open())
  {
    perror("Falha ao abrir o html ou caminho incorreto");
    return "";
  }
  stringstream buffer;

  buffer << file.rdbuf();
  
  string html = buffer.str();
    
  string response = 
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Content-Length: " + to_string(html.size()) + "\r\n"
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
  char buffer[1024] = {0};

  while (true)
  {
  
  int clientSocketFileDescriptor = accept(serverSocketFileDescriptor, nullptr, nullptr);
  int bytes = recv(clientSocketFileDescriptor, buffer, sizeof(buffer), 0);
  
  HttpRequestParseer(buffer, bytes);
  string msg = HtmlToString("html/home.html");
  const char* msgBuffer = msg.data();
  write(clientSocketFileDescriptor, msgBuffer, strlen(msgBuffer));
  close(clientSocketFileDescriptor);
  }

  close(serverSocketFileDescriptor);
}
