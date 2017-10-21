project(HypePubSub)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Define the directory for the SHA
set(SHA1_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/src")
set(SHA1_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/include")
file(GLOB_RECURSE SHA1_C_SOURCES "${SHA1_SRC_DIR}/*.c")
file(GLOB_RECURSE SHA1_C_INCLUDES "${SHA1_INC_DIR}/*.h")
add_library(SHA1_LIB ${SHA1_C_SOURCES} ${SHA1_C_INCLUDES} )

# Define the directory of the source code and of the headers 
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
file(GLOB_RECURSE MY_C_SOURCES "${SRC_DIR}/*.c")
file(GLOB_RECURSE MY_C_INCLUDES "${INC_DIR}/*.h")

include_directories( ${INC_DIR})
include_directories( ${SHA1_INC_DIR})

add_executable(${PROJECT_NAME} ${MY_C_SOURCES}
                                ${MY_C_INCLUDES}
                                ${SHA1_C_SOURCES}
                                ${SHA1_C_INCLUDES})


target_link_libraries(${PROJECT_NAME}
                        SHA1_LIB)


