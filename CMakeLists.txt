cmake_minimum_required(VERSION 3.25.0)
project(EasySQL VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)  # Set to OFF to avoid compiler-specific extensions


include_directories(include)

# Glob for .cpp and .hpp files
file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/*.hpp)

# Add nanodbc to the project
add_subdirectory(vendor/nanodbc)

# Our Project
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link nanodbc to your project
target_link_libraries(${PROJECT_NAME} PRIVATE nanodbc)
