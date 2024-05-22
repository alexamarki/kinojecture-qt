cmake_minimum_required(VERSION 3.8)
project(kinojecture VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Sql)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# qt6_wrap_ui(UI_HEADERS ${CMAKE_SOURCE_DIR}/qt/base_window.ui)

add_executable(myApp 
    qt/base_window.h 
    qt/base_window.cpp 
    qt/base_window.ui
    #build/ui_base_window.hx
)
# add_executable(controller 
#     controller/controller.h 
#     controller/controller.cpp 
# )
# add_executable(gameModel 
#     game_logic/game_model.h 
#     game_logic/game_model.cpp 
# )
add_executable(leaderboard 
    db_code/leaderboard.h 
    db_code/leaderboard.cpp)

target_link_libraries(myApp Qt6::Widgets Qt6::Core)
# target_link_libraries(controller Qt6::Core Qt6::Sql)
# target_link_libraries(gameModel Qt6::Core Qt6::Sql)
target_link_libraries(leaderboard Qt6::Core Qt6::Sql)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
