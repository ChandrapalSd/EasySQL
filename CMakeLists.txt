cmake_minimum_required(VERSION 3.25.0)
project(EasySQL VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)


include_directories(include)
	
file(GLOB SOURCES src/*.cpp src/api/*.cpp)
file(GLOB HEADERS include/*.hpp include/api/*.hpp)

set(BUILD_SHARED_LIBS OFF)
add_subdirectory(vendor/nanodbc)
add_subdirectory(vendor/glog)
add_subdirectory(vendor/drogon)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE nanodbc glog drogon)

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
