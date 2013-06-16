set(TinyXML_STAT_SRCS
  tinystr.cpp
  tinystr.h
  tinyxml.cpp
  tinyxml.h
  tinyxmlerror.cpp
  tinyxmlparser.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(TinyXML STATIC ${TinyXML_STAT_SRCS})
