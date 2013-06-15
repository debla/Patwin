message(STATUS "Setting up Unix enviroment")

# Support for c++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_definitions(-D_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES)
