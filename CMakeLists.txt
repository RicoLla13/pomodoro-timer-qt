# Set export compile commands (optional)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Minimum CMake version required
cmake_minimum_required(VERSION 3.16)

# Set the project name and version
set(PROJECT_NAME pomodoro-qt)

# Enable Qt resource handling
set(CMAKE_AUTORCC ON)

# Define the project
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the Qt6 Widgets package
find_package(Qt6 REQUIRED COMPONENTS Widgets Multimedia Svg)

# Standard Qt project setup
qt_standard_project_setup()

# Add the executable, including the resource file
qt_add_executable(${PROJECT_NAME}
    main.cpp
    main_window.hpp
    main_window.cpp
    timer.hpp
    timer.cpp
    settings.hpp
    settings.cpp
    pomodoro.cpp
    pomodoro.cpp
    nordic_clock.hpp
    nordic_clock.cpp
    resources.qrc
    utils.hpp
)

# Link the Qt6::Widgets library to the target
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Multimedia Qt6::Svg)

# Set executable properties for Windows (optional)
set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE ON
)
