cmake_minimum_required(VERSION 3.10)

# Set project name
project(RobotVacuumFSM)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect all source files
set(SOURCES
    main.cpp
    RobotVacuum.cpp
    IdleState.cpp
    CleaningState.cpp
    ChargingState.cpp
    ReturningToBaseState.cpp
)

# Add executable
add_executable(RobotVacuumFSM ${SOURCES})

# Include current directory for header files
target_include_directories(RobotVacuumFSM PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

