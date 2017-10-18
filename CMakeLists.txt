project(HypePubSub)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Define the directory of the source code and of the headers 
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/inc")

FILE(GLOB_RECURSE MY_C_SOURCES "${SRC_DIR}/*.c")
FILE(GLOB_RECURSE MY_C_INCLUDES "${INC_DIR}/*.h")

include_directories( ${INC_DIR})

add_executable(${PROJECT_NAME} ${MY_C_SOURCES}
                               ${MY_C_INCLUDES})


target_link_libraries(${PROJECT_NAME})
