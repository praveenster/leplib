cmake_minimum_required (VERSION 2.6)

project (leplib)

add_definitions(-D__ENABLE_LOGGER__)
add_subdirectory (src)
add_subdirectory (test)
