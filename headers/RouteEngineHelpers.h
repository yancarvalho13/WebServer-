#pragma once
#include "RouteEngineEnums.h"
#include <string>
#include <vector>
Methods getMethodEnumFromString(std::string& method);
std::string methodToString(Methods method);
std::vector<std::string> extractWords(std::string line);
std::string parseHtmlToString(std::string htmlPath);

