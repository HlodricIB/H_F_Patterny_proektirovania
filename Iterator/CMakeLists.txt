cmake_minimum_required(VERSION 3.5)

project(Iterator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC_FILES ./src/*.cpp)
file(GLOB INC_FILES ./include/*.h)

add_executable(${PROJECT_NAME}
    ${SRC_FILES}
    ${INC_FILES}
)

target_compile_options(${PROJECT_NAME} PUBLIC -g -O0 -Wall -Wextra)
target_link_options(${PROJECT_NAME} PUBLIC -dynamic)

target_include_directories(${PROJECT_NAME} PUBLIC ./include/)
