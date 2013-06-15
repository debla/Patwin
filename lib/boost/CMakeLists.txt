set(Boost_USE_STATIC_LIBS    ON )
set(Boost_USE_MULTITHREADED  ON )
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.53 COMPONENTS unit_test_framework regex chrono date_time program_options system thread filesystem REQUIRED)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found! Download and install Boost from http://www.boost.org/")
endif()

mark_as_advanced(Boost_LIB_DIAGNOSTIC_DEFINITIONS)
