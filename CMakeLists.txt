cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(MyProject VERSION 1.0 LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files and create a library
add_library(MyLibrary STATIC
        src/cpu.cpp
        src/instructions.cpp
        src/register.cpp
        src/timer.cpp
        src/mmu.cpp
        src/mmu.h
)

# Add the main executable
add_executable(Gb
        src/unittest.cpp
)

# Link the executable with the library
target_link_libraries(Gb PRIVATE MyLibrary)

# Include directories
target_include_directories(MyLibrary PUBLIC
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/nlohmann  # Directory for json.hpp
)

target_include_directories(Gb PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/nlohmann
)

# Ensure v1 and roms directories are copied to the output directory
add_custom_command(TARGET Gb POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/v1 $<TARGET_FILE_DIR:Gb>/v1
)

add_custom_command(TARGET Gb POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/roms $<TARGET_FILE_DIR:Gb>/roms
)

add_custom_command(TARGET Gb POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/tests $<TARGET_FILE_DIR:Gb>/tests
)

# Installation rules
install(TARGETS Gb
        RUNTIME DESTINATION bin
)
