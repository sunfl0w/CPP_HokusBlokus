cmake_minimum_required(VERSION 3.1)

project(CPP_HokusBlokus)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g -fno-omit-frame-pointer -DENABLE_OPENGL_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -Wall -O3 -fopenmp -march=native -flto -mpopcnt -fwhole-program")

find_package(Boost COMPONENTS system thread program_options)

file(STRINGS "includelist.cmake" includes)
file(STRINGS "sourcelist.cmake" sources)

include_directories(${includes})

add_executable(CPP_HokusBlokus_Starter ${sources})

if(Boost_FOUND)
    target_link_libraries(CPP_HokusBlokus_Starter ${Boost_LIBRARIES})
endif(Boost_FOUND)