#
# The library
#
set(SIMULATION_LIB_SOURCES
        Vector3D.h Vector3D.cpp
        Simulation.cpp Simulation.h
        DebugStream.h
        DebugStream.cpp )
add_library(simulib STATIC ${SIMULATION_LIB_SOURCES})

#
# A quick demo
#
set(3ddemo_SOURCES 3ddemo.cpp)
add_executable(3ddemo ${3ddemo_SOURCES})
target_link_libraries(3ddemo simulib)

#
# The REPL
#
set(RobotWorld_SOURCES robotworld.cpp sim_commands.cpp sim_commands.h repl_tools.cpp repl_tools.h)
add_executable(RobotWorld ${RobotWorld_SOURCES})
target_link_libraries(RobotWorld simulib)

if(CLANGFORMAT)
    include(ClangFormat)

    set(clangformat_srcs
            ${SIMULATION_LIB_SOURCES}
            ${3ddemo_SOURCES}
            ${RobotWorld_SOURCES})

    clangformat_setup("${clangformat_srcs}")
endif()