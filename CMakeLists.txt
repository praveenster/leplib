cmake_minimum_required (VERSION 2.6)

project (leplib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__LEPFILE__='\"$(subst ${CMAKE_SOURCE_DIR}/,,$(abspath $<))\"'")

add_definitions(-D__ENABLE_LOGGER__)
add_subdirectory (src)
add_subdirectory (test)

