include_directories (${lepcpplib_SOURCE_DIR}/lepcpplib)

link_directories (${lepcpplib_BINARY_DIR})

add_executable (lepcpplibTests
                TestCsvFile.cpp
                TestConfigFile.cpp
                TestMain.cpp
                TestString.cpp
                TestThread.cpp)

target_link_libraries (lepcpplibTests lepcpplib)
