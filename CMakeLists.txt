project(HypePubSub)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_C_FLAGS "-std=c99")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

# Define the directory for the SHA
set(SHA1_LIB "sha1")
set(SHA1_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/src")
set(SHA1_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/include")
file(GLOB_RECURSE SHA1_C_SOURCES "${SHA1_SRC_DIR}/*.c")
file(GLOB_RECURSE SHA1_C_INCLUDES "${SHA1_INC_DIR}/*.h")
add_library(${SHA1_LIB} ${SHA1_C_SOURCES} ${SHA1_C_INCLUDES})

# Define the directory of the source code and of the headers 
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
file(GLOB_RECURSE MY_C_SOURCES "${SRC_DIR}/*.c")
file(GLOB_RECURSE MY_C_INCLUDES "${INC_DIR}/*.h")

# Define the directory of the shared source code
set(SHARED_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shared/src")
set(SHARED_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shared/include")
file(GLOB_RECURSE MY_SHARED_C_SOURCES "${SHARED_SRC_DIR}/*.c")
file(GLOB_RECURSE MY_SHARED_C_INCLUDES "${SHARED_INC_DIR}/*.h")

include_directories( ${INC_DIR})
include_directories( ${SHARED_INC_DIR})
include_directories( ${SHA1_INC_DIR})

add_executable(${PROJECT_NAME} ${MY_C_SOURCES}
                                ${MY_C_INCLUDES}
                                ${MY_SHARED_C_SOURCES}
                                ${MY_SHARED_C_INCLUDES}
                                ${SHA1_C_SOURCES}
                                ${SHA1_C_INCLUDES})

target_link_libraries(${PROJECT_NAME}
                        ${SHA1_LIB})

if(HYPE_PUB_SUB_COMPILE_TESTS) # Compile for testing

    # Setup CUnit framework
    find_library(C_UNIT cunit)
    if(NOT C_UNIT)
        message(FATAL_ERROR "CUnit library not found (libcunit.dylib)")
    endif()

    find_path(CUNIT_INCLUDE_DIRS "CUnit")
    if(NOT CUNIT_INCLUDE_DIRS)
        message(FATAL_ERROR "CUnit header files not found")
    endif()
    include_directories(${CUNIT_INCLUDE_DIRS})

    # Define the directory of the testing source code and of the headers
    set(TEST_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test/src/hype_pub_sub")
    set(TEST_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test/include/hype_pub_sub")
    file(GLOB_RECURSE MY_TEST_C_SOURCES "${TEST_SRC_DIR}/*.c")
    file(GLOB_RECURSE MY_TEST_C_INCLUDES "${TEST_INC_DIR}/*.h")
    include_directories( ${TEST_INC_DIR})

    # Define the directory of the shared testing source code
    set(SHARED_TEST_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test/shared/src")
    set(SHARED_TEST_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test/shared/include")
    file(GLOB_RECURSE MY_SHARED_TEST_C_SOURCES "${SHARED_TEST_SRC_DIR}/*.c")
    file(GLOB_RECURSE MY_SHARED_TEST_C_INCLUDES "${SHARED_TEST_INC_DIR}/*.h")
    include_directories( ${SHARED_TEST_INC_DIR})

    enable_testing()
    list(REMOVE_ITEM MY_C_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/hype_pub_sub/hpb_main.c")
    add_executable(TestHypePubSub ${MY_C_SOURCES}
                                    ${MY_C_INCLUDES}
                                    ${MY_SHARED_C_SOURCES}
                                    ${MY_SHARED_C_INCLUDES}
                                    ${SHA1_C_SOURCES}
                                    ${SHA1_C_INCLUDES}
                                    ${MY_SHARED_TEST_C_SOURCES}
                                    ${MY_SHARED_TEST_C_INCLUDES}
                                    ${MY_TEST_C_SOURCES}
                                    ${MY_TEST_C_INCLUDES})


    add_test(TestHypePubSub ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/TestHypePubSub)
    target_link_libraries(TestHypePubSub ${C_UNIT})

endif()




