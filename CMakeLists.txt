cmake_minimum_required(VERSION 3.14)
project(libdd)

SET(CMAKE_C_STANDARD 99)
SET(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
SET(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR})

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O2 -fPIC -std=c++17 -Wall -Wno-deprecated -Werror")
set(CMAKE_BUILD_TYPE Debug)

include_directories(
        ${PROJECT_SOURCE_DIR}/src/base
        ${PROJECT_SOURCE_DIR}/src/net
        ${PROJECT_SOURCE_DIR}/src/net/poller
        ${PROJECT_SOURCE_DIR}/src/net/http
        ${PROJECT_SOURCE_DIR}/src/timer
        ${PROJECT_SOURCE_DIR}/src/logger
        ${PROJECT_SOURCE_DIR}/src/memory
        ${PROJECT_SOURCE_DIR}/src/mysql
)

aux_source_directory(${PROJECT_SOURCE_DIR}/src/base SRC_BASE)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/net SRC_NET)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/net/poller SRC_POLLER)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/http SRC_HTTP)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/timer SRC_TIMER)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/logger SRC_LOG)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/memory SRC_MEMORY)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/mysql SRC_MYSQL)

add_library(LIBDD SHARED ${SRC_BASE}
        ${SRC_NET}
        ${SRC_POLLER}
        ${SRC_TIMER}
        ${SRC_LOG}
        ${SRC_HTTP}
        ${SRC_MEMORY}
        ${SRC_MYSQL})

set(LIBS
        LIBDD
        pthread
        mysqlclient
        )

set(TEST_BASE_LIST
        tests/base/thread_test1.cc
        tests/base/timestamp_test1.cc
        )

foreach (source ${TEST_BASE_LIST})
    set(module base)
    string(REPLACE ".cc" "" test_name ${source})
    string(REPLACE "tests/${module}/" "${module}_" testName ${test_name})
    add_executable(${testName} ${source})
    target_link_libraries(${testName} ${LIBS})
    set_target_properties(${testName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/${module})
endforeach ()