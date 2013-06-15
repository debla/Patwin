project(Patwin C CXX)
cmake_minimum_required(VERSION 2.8)
message("Patwin (c) 2013 Denis Blank")

include(CheckCXXSourceRuns)
include(CheckIncludeFiles)

add_subdirectory(cmake)
include(lib/boost/CMakeLists.txt)

include_directories (
  ${CMAKE_SOURCE_DIR}/lib/cpp-netlib
  ${CMAKE_SOURCE_DIR}/src
  ${Boost_INCLUDE_DIR}
)

file(GLOB_RECURSE sources src/*.cpp src/*.h src/*.hpp install/*.xml)
source_group(Source FILES ${sources})

add_executable(Patwin
    ${sources}
)

target_link_libraries(Patwin
    ${Boost_LIBRARIES}
)

if( WIN32 )
    add_custom_command(TARGET Patwin POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/install" "${CMAKE_BINARY_DIR}/bin/$(ConfigurationName)")
endif()
