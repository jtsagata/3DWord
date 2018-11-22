cmake_minimum_required(VERSION 3.12)
project(3DWord)

# Configure CMake
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)
option(CLANGFORMAT "Setup clangformat target" ON)


# For use with tooling like clang-modernize
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 14)
set( CMAKE_CXX_FLAGS "-Wall -Werror" )

add_subdirectory(src)

execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/scripts
        ${CMAKE_BINARY_DIR}/scripts)