cmake_minimum_required(VERSION 3.8)
project(kinojecture VERSION 0.5.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Sql)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(GLOB UI_FILES qt/*.ui)
file(GLOB HEADER_FILES qt/*.h game_logic/*.h db_code/*.h controller/*.h)
file(GLOB SOURCE_FILES qt/*.cpp game_logic/*.cpp db_code/*.cpp controller/*.cpp)
set(cinema_db_path "${CMAKE_CURRENT_SOURCE_DIR}/resources/game.db")
set(lead_db_path "${CMAKE_CURRENT_SOURCE_DIR}/resources/leaderboard.db")
set(player_data_path "${CMAKE_CURRENT_SOURCE_DIR}/resources/player_data.json")

list(APPEND SOURCE_FILES ${cinema_db_path} ${lead_db_path} ${player_data_path})

set_source_files_properties(${cinema_db_path} ${lead_db_path} ${player_data_path}
    PROPERTIES
    MACOSX_PACKAGE_LOCATION "Resources"
)

set(MACOSX_BUNDLE_ICON_FILE kj_icon_test.ico)
set(IDI_ICON1 ICON kj_icon_test.ico)

set(app_icon_macos "${CMAKE_CURRENT_SOURCE_DIR}/resources/kj_icon_test.ico")
set_source_files_properties(${app_icon_macos} PROPERTIES
            MACOSX_PACKAGE_LOCATION "Resources")

if(WIN32)
    set(app_icon_windows "${CMAKE_CURRENT_SOURCE_DIR}/resources/kj_icon_test.rc")
    list(APPEND SOURCE_FILES ${app_icon_windows})
endif()

qt6_wrap_ui(UI_HEADERS ${UI_FILES})

add_executable(myApp
    ${HEADER_FILES}
    ${SOURCE_FILES}
    ${UI_HEADERS}
    ${app_icon_macos}
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

set_target_properties(myApp PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS myApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(icon)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
find_package(Doxygen)
if(Doxygen_FOUND)
    add_subdirectory(docs)
else()
    message(STATUS "Doxygen not found")
endif()
