cmake_minimum_required(VERSION 2.8)
project (MrfDenoising)
include_directories("${PROJECT_SOURCE_DIR}/include")
add_subdirectory(src)
add_executable(FunctionTest main.cxx)
target_link_libraries(FunctionTest MrfImageDenoising)