cmake_minimum_required (VERSION 2.8.12)
project (http_app)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_FLAGS "-g -std=c++14 -L../http_lib/build/")

include_directories (${HttpServer_INCLUDE_DIR})

add_executable (${PROJECT_NAME} main.cpp)
target_link_libraries (${PROJECT_NAME} HttpServer)

file (GLOB PAGES "pages/*")
foreach (FILE ${PAGES})
    file (COPY ${FILE} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endforeach (FILE)
