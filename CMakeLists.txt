cmake_minimum_required(VERSION 3.17)

project(CPP_HokusBlokus)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -Wall -O3 -march=native -flto -mpopcnt")

find_package(Boost COMPONENTS system thread program_options)
find_package(PythonLibs REQUIRED)

file(STRINGS "includelist.cmake" includes)
file(STRINGS "sourcelist.cmake" sources)

include_directories(${includes})
include_directories(${PYTHON_INCLUDE_DIRS})

add_executable(CPP_HokusBlokus_Exe ${sources})
set_target_properties(CPP_HokusBlokus_Exe PROPERTIES OUTPUT_NAME "Hive_Executable")
add_library(CPP_HokusBlokus_Lib SHARED ${sources})
set_target_properties(CPP_HokusBlokus_Lib PROPERTIES PREFIX "")
set_target_properties(CPP_HokusBlokus_Lib PROPERTIES OUTPUT_NAME "_Hive")

target_link_libraries(CPP_HokusBlokus_Exe ${PYTHON_LIBRARIES})
target_link_libraries(CPP_HokusBlokus_Lib ${PYTHON_LIBRARIES})

set_property(TARGET CPP_HokusBlokus_Exe PROPERTY SWIG_USE_TARGET_INCLUDE_DIRECTORIES TRUE)
set_property(TARGET CPP_HokusBlokus_Lib PROPERTY SWIG_USE_TARGET_INCLUDE_DIRECTORIES TRUE)

if(Boost_FOUND)
    target_link_libraries(CPP_HokusBlokus_Exe ${Boost_LIBRARIES})
    target_link_libraries(CPP_HokusBlokus_Lib ${Boost_LIBRARIES})
endif(Boost_FOUND)