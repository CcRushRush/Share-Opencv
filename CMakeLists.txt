cmake_minimum_required(VERSION 3.12)
project(chapter01)

set(CMAKE_CXX_STANDARD 14)

#add_executable(chapter01 main.cpp)
add_executable(chapter01 openCVDemo1/main.cpp)

#查找Qt的库
find_package(Qt5Widgets)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(chapter01 ${OpenCV_LIBS}  Qt5::Widgets)

#打开Qt的MOC功能和UI文件处理功能
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)