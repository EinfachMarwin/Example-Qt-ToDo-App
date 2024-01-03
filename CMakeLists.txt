cmake_minimum_required(VERSION 3.9)
project(ToDo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTOMOC_PATH_PREFIX ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Sql
        LinguistTools
        REQUIRED)

find_package(TinyOrm 0.36.5 CONFIG REQUIRED)
find_package(SQLite3 REQUIRED)

qt_standard_project_setup()

include(cmake/Deploy.cmake)

# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/widgets)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/windows)

add_executable(ToDo
        src/main.cpp
        src/dbmanager.cpp

        src/windows/mainwindow.cpp
        src/windows/settingswindow.cpp

        src/widgets/taskwidget.cpp
        src/widgets/listwidget.cpp
)
target_include_directories(ToDo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(ToDo
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Sql

        TinyOrm::TinyOrm

        SQLite::SQLite3
)

qt_add_resources(
        ToDo "resources"
        PREFIX "/"
        FILES
            res/images/HelpIcon.png
            res/images/LogoToDoAppTransparent.png
            res/images/SettingsIcon.png
            res/images/TasksListIcon.png
            res/images/ImportantIcon.png
            res/images/TodayIcon.png
            res/images/InboxIcon.png
)

target_qt_deploy(ToDo)

if (MINGW)
    target_link_libraries(ToDo -static-libgcc)
endif ()