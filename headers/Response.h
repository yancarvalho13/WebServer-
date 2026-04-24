#pragma once
#include <string>
class Response {
  public:
    Response();
    void setData(std::string);
    std::string getData();
    void logResponse();
  private:
    std::string _responseData;
};
