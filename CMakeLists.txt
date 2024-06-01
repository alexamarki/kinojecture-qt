cmake_minimum_required(VERSION 3.8)
project(kinojecture VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Sql)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(GLOB UI_FILES qt/*.ui)
file(GLOB HEADER_FILES qt/*.h game_logic/*.h db_code/*.h controller/*.h)
file(GLOB SOURCE_FILES qt/*.cpp game_logic/*.cpp db_code/*.cpp controller/*.cpp)

qt6_wrap_ui(UI_HEADERS ${UI_FILES})

add_executable(myApp
    #${HEADER_FILES}
    ${SOURCE_FILES}
    ${UI_HEADERS}
)

set_target_properties(myApp PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    OUTPUT_NAME "base_window"
)

target_include_directories(myApp PRIVATE 
    ${CMAKE_SOURCE_DIR}/qt 
    ${CMAKE_SOURCE_DIR}/game_logic
    ${CMAKE_SOURCE_DIR}/db_code 
    ${CMAKE_SOURCE_DIR}/controller
)

target_link_libraries(myApp Qt6::Widgets Qt6::Core Qt6::Sql)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
