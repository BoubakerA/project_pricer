# Minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(OptionPricer)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add include directory
include_directories(include)

# Define the source files
set(SOURCES
    main.cpp
    src/black_and_scholes_pricer.cpp
    src/monte_carlo_pricer.cpp
)

# Add executable
add_executable(option_pricer ${SOURCES})
