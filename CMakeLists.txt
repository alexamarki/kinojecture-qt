cmake_minimum_required(VERSION 3.8)
project(kinojecture VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lsqlite3")
include (FetchContent)
FetchContent_Declare(sqlite3 URL https://www.sqlite.org/2024/sqlite-amalgamation-3450300.zip)
FetchContent_MakeAvailable(sqlite3)
add_executable(kinojecture main.cpp)

target_link_libraries(kinojecture PRIVATE sqlite3)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
