SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_extensions/)

FIND_PACKAGE(Boost COMPONENTS python REQUIRED)
FIND_PACKAGE(PythonLibs REQUIRED)
IF(Boost_FOUND)
    MESSAGE("boost found!")
    INCLUDE_DIRECTORIES(${BOOST_INCLUDE_DIR})
    LINK_DIRECTORIES(${BOOST_LIBRARY_DIR})
endif()

IF (PythonLibs_FOUND OR PYTHON_LIBRARIES)
    message("python found!")
    INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_DIR})
    LINK_DIRECTORIES(${PYTHON_LIBRARY_DIRS})
endif()


message (${Boost_LIBRARIES})
message (${PYTHON_LIBRARIES})
set(PYBROT_SRCS pycomplex.cxx pymandelbrot.cxx pybrot.cxx)
add_library(pybrot SHARED ${PYBROT_SRCS})
target_link_libraries(pybrot mandelbrot complex ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
set_target_properties(pybrot PROPERTIES PREFIX "" OUTPUT_NAME "mandelbrot")
