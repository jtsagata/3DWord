cmake_minimum_required(VERSION 3.12)
project(3DWorld VERSION 0.0.1 LANGUAGES CXX)



# Configure CMake
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)
option(CLANGFORMAT "Setup clangformat target" ON)


# For use with tooling like clang-modernize
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 14)
set( CMAKE_CXX_FLAGS "-Wall -Werror" )

add_subdirectory(src)

# Symlink scripts to build folder
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/scripts
        ${CMAKE_BINARY_DIR}/scripts)

# Make distribution for the email. No CPACK
# http://agateau.com/2009/cmake-and-make-dist-the-simple-version/
set(ARCHIVE_NAME ${CMAKE_PROJECT_NAME}-${PROJECT_VERSION})
add_custom_target(dist
        COMMAND git archive --prefix=${ARCHIVE_NAME}/ HEAD
        | bzip2 > ${CMAKE_SOURCE_DIR}/${ARCHIVE_NAME}.tar.bz2
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

# Count Lines of code
add_custom_target(code_stats
        COMMAND cloc --report-file=${CMAKE_PROJECT_NAME}_stats.txt src
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
