include_directories (${lepcpplib_SOURCE_DIR}/lepcpplib)

link_directories (${lepcpplib_BINARY_DIR})

add_executable (lepcpplibTests TestMain.cpp TestString.cpp TestConfigFile.cpp)

target_link_libraries (lepcpplibTests lepcpplib)
