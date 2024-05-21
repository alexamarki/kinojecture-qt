cmake_minimum_required(VERSION 3.8)
project(kinojecture VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(sqlite3 URL https://www.sqlite.org/2024/sqlite-amalgamation-3450300.zip)
FetchContent_MakeAvailable(sqlite3)

set(SQLITE "${CMAKE_SOURCE_DIR}/build/_deps/sqlite3-src")
add_library(sqlite3 STATIC ${SQLITE}/sqlite3.c)
target_include_directories(sqlite3 PUBLIC ${SQLITE})

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#qt6_wrap_ui(UI_HEADERS ${CMAKE_SOURCE_DIR}/qt/base_window.ui)

add_executable(myApp 
    qt/base_window.h 
    qt/base_window.cpp 
    qt/base_window.ui
    #build/ui_base_window.h
)
add_executable(controller 
    controller/controller.h 
    controller/controller.cpp 
)
add_executable(model 
    game_logic/model.h 
    game_logic/model.cpp 
)

target_link_libraries(myApp Qt6::Widgets Qt6::Core)
target_link_libraries(controller Qt6::Core)
target_link_libraries(model Qt6::Core)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
