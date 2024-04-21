cmake_minimum_required(VERSION  3.22.1)
project( Lab5 )
find_package(OpenCV REQUIRED)
set(CMAKE_CXX_STANDARD 14)
include_directories(${OpenCV_INCLUDE_DIRS})



add_executable(task2 task2.cpp)



target_link_libraries(task2 ${OpenCV_LIBS})

