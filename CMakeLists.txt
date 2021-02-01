cmake_minimum_required(VERSION 3.17)

project(CPP_HokusBlokus)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -Wall -O3 -march=native -flto -mpopcnt")

find_package(Boost COMPONENTS system thread program_options)

file(STRINGS "cmakeListings/includeDirsAbs.cmake" includes)
file(STRINGS "cmakeListings/sourceFilesAbs.cmake" sources)

add_executable(CPP_HokusBlokus ${sources})

include_directories(${includes})

if(Boost_FOUND)
    target_link_libraries(CPP_HokusBlokus ${Boost_LIBRARIES})
endif(Boost_FOUND)