cmake_minimum_required(VERSION 3.5)
project(task2)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Include directories for OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Create executables
add_executable(task2 task2.cpp)

# Link OpenCV libraries
target_link_libraries(task2 ${OpenCV_LIBS})

# Include ImageFilters library
add_library(ImageFilters ImageFilters.cpp)

# Link ImageFilters library
target_link_libraries(task2 ImageFilters)
