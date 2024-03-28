cmake_minimum_required(VERSION 3.0)
project(task3)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Include directories for OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})



# Create executable
add_executable(${PROJECT_NAME} task3.cpp)

# Link OpenCV libraries
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
