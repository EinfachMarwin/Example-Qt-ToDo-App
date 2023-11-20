cmake_minimum_required(VERSION 3.9)
project(ToDo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/forms")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

qt_standard_project_setup()

# Include the header files from the include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(ToDo
        src/main.cpp
        src/mainwindow.cpp
)

target_link_libraries(ToDo
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)