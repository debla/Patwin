project(Patwin C CXX)
cmake_minimum_required(VERSION 2.8)
message("Patwin (c) 2013 Denis Blank")

include(CheckCXXSourceRuns)
include(CheckIncludeFiles)

if(CMAKE_COMPILER_IS_GNUCXX)
    # SET(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
endif()

add_subdirectory(cmake)
include(lib/boost/CMakeLists.txt)

add_subdirectory(lib)

include_directories (
  ${CMAKE_SOURCE_DIR}/lib/cpp-netlib
  ${CMAKE_SOURCE_DIR}/lib/tinyxml
  ${CMAKE_SOURCE_DIR}/src
  ${Boost_INCLUDE_DIR}
)

file(GLOB_RECURSE sources src/*.cpp src/*.h src/*.hpp install/*.xml)
source_group(Source FILES ${sources})

if( WIN32 )
    SET(sources 
        ${sources}
        ${CMAKE_SOURCE_DIR}/src/Patwin.rc
    )

    add_custom_command(TARGET Patwin POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/install" "${CMAKE_BINARY_DIR}/bin/$(ConfigurationName)")
endif()

add_executable(Patwin
    ${sources}
)

target_link_libraries(Patwin
    ${Boost_LIBRARIES}
    TinyXML
)

