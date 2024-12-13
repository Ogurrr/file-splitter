cmake_minimum_required(VERSION 3.10)

# Project name
project(FileSplitter LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable target
add_executable(FileSplitter splitter.cpp)

cmake_minimum_required(VERSION 3.10)

# Project name
project(FileMerger LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable target
add_executable(FileMerger merger.cpp)