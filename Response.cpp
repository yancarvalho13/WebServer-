#include "headers/Response.h"
#include <string>

Response::Response()
{

}

void Response::setData(std::string data)
{
  _responseData = data;
}

std::string Response::getData()
{
  return _responseData;
}
