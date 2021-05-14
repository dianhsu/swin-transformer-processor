cmake_minimum_required(VERSION 3.16)

project(swin-transformer-compiler)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PREFIX_PATH "libtorch")

find_package(Torch REQUIRED)

add_executable(parser parser.cpp)

target_link_libraries(parser ${TORCH_LIBRARIES})