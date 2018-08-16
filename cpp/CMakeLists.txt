cmake_minimum_required(VERSION 2.8)
project(chenlin_programmingTasks)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
include(cmake/PICMake.cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/libs)
IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Release)
ENDIF()
message("-- Build type: " ${CMAKE_BUILD_TYPE})

list(APPEND CMAKE_CXX_FLAGS "-std=c++11")


#INCLUDE_DIRECTORIES(libs)


# utils libs
pi_add_target(utils STATIC libs REQUIRED System)

###############################################################################
# C++ 
###############################################################################
add_subdirectory(basic)

pi_report_targets()

