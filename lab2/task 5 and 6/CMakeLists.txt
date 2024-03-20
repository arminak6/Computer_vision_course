cmake_minimum_required(VERSION 3.5)
project(task3)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Include directories for OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Create executables
add_executable(task3 task3.cpp)

# Link OpenCV libraries
target_link_libraries(task3 ${OpenCV_LIBS})
