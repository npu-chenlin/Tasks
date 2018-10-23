cmake_minimum_required( VERSION 2.8 )
project( imageBasics )

# 添加c++ 11标准支持
set( CMAKE_CXX_FLAGS "-std=c++11" )
set(CUDA_USE_STATIC_CUDA_RUNTIME OFF)
# 寻找OpenCV库
find_package( OpenCV REQUIRED )
# 添加头文件
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( imageBasics contrastandbright.cpp )
# 链接OpenCV库
target_link_libraries( imageBasics ${OpenCV_LIBS} )
