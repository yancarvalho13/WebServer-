#include "headers/Response.h"
#include <iostream>
#include <ostream>
#include <string>

Response::Response()
{

}

void Response::logResponse()
{
  std::cout <<  "Responded sucessesfully" << std::endl;
}

void Response::setData(std::string data)
{
  _responseData = data;
}

std::string Response::getData()
{
  return _responseData;
}
