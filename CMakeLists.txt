cmake_minimum_required(VERSION 3.8)
project(kinojecture VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDAR xD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lsqlite3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -fexperimental-library -stdlib=libc++")
include (FetchContent)
FetchContent_Declare(sqlite3 URL https://www.sqlite.org/2024/sqlite-amalgamation-3450300.zip)
FetchContent_MakeAvailable(sqlite3)

set(SQLITE "${CMAKE_SOURCE_DIR}/build/_deps/sqlite3-src")
add_library(sqlite3 STATIC ${SQLITE}/sqlite3.c)
target_include_directories(sqlite3 PUBLIC ${SQLITE})

add_executable(main main.cpp)
add_executable(helper helper_src/code/helper.cpp helper_src/code/helper.h)

target_link_libraries(helper PRIVATE sqlite3)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
