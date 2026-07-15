# CMakeLists.txt
# This file configures the Noise project build using CMake.

cmake_minimum_required(VERSION 3.10)

project(Noise CXX)

# Set standard C++ requirements (C++17 is commonly used for modern projects)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# NOTE: Removed non-MSVC compiler flags (-Wall, -Wextra) to resolve D8021 error.
# CMake will now manage standard warnings appropriate for the target compiler (MSVC).

# --- Source Files Definition ---
# List all primary source files. CMake will handle the compilation unit linking.
set(SOURCE_FILES
    PerlinNoise/src/main.cpp
    PerlinNoise/src/Image.cpp
    PerlinNoise/src/PerlinNoise.cpp
)

# --- Executable Target Definition ---
# Create the main executable target and link all sources into it.
add_executable(PerlinNoise ${SOURCE_FILES})