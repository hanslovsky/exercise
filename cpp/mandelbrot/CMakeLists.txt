CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(mandelbrot)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_extensions/)
message(${CMAKE_MODULE_PATH})
FIND_PACKAGE(VIGRA REQUIRED)
if (VIGRA_FOUND)
    MESSAGE("vigra found!")
    INCLUDE_DIRECTORIES(${VIGRA_INCLUDE_DIR})
    LINK_DIRECTORIES( ${VIGRA_IMPEX_LIBRARY_DIR})
endif()



SET(CMAKE_CXX_FLAGS "-Wall -Wextra -Wfatal-errors -std=c++98 -pedantic -pthread")
SET(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -Werror")	



INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include/")


ADD_LIBRARY(complex SHARED src/complex.cpp)
ADD_LIBRARY(mandelbrot SHARED src/mandelbrot.cpp)
ADD_EXECUTABLE(brot main.cxx)
TARGET_LINK_LIBRARIES(mandelbrot complex vigraimpex)
TARGET_LINK_LIBRARIES(brot mandelbrot)

SET(WITH_PYTHON true CACHE BOOL "build with python wrapper")
if(WITH_PYTHON)
  add_subdirectory(python/)
endif()
