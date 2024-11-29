cmake_minimum_required(VERSION 3.5)

project(desktop VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
link_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(DEFINED ENV{QTDIR})
    set(CMAKE_PREFIX_PATH "$ENV{QTDIR}")
endif()

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror  -fPIC -std=c++17")

include_directories(brick_game/snake)
include_directories(brick_game/tetris)
include_directories(brick_game/common)
include_directories(brick_game)
include_directories(gui/cli)
include_directories(gui/desktop)

set(SOURCE_FILES
    gui/desktop/View.cpp
    gui/desktop/View.h
    gui/desktop/View.ui
    common/bg_objects.h
    brick_game/brick_game_qt.cpp
)

if(TETRIS)
    add_executable(tetris_desktop ${SOURCE_FILES})
    target_link_libraries(tetris_desktop
        Qt::Core
        Qt::Gui
        Qt::Widgets
        -l:tetris.a
    )
else()
    add_executable(snake_desktop ${SOURCE_FILES})
    target_link_libraries(snake_desktop 
        Qt::Core
        Qt::Gui
        Qt::Widgets
        -l:snake.a
    )
endif()

message(STATUS "PROJECT_SOURCES: ${PROJECT_SOURCES}")