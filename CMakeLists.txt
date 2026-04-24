cmake_minimum_required(VERSION 3.10)

project(WebServer)

set(CMAKE_CXX_STANDARD 17)

add_executable(server
    Main.cpp
    Request.cpp
    Response.cpp
    Route.cpp
    RouteEngine.cpp
    RouteEngineHelpers.cpp
    WebServer.cpp
)
