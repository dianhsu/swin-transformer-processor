cmake_minimum_required(VERSION 3.16)

project(swin-transformer-compiler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_PREFIX_PATH "libtorch")

find_package(Torch REQUIRED)
include_directories(include)

file(GLOB SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(main main.cpp ${SRC})

target_link_libraries(main ${TORCH_LIBRARIES})