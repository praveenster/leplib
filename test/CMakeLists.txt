include_directories (${leplib_SOURCE_DIR}/leplib)

link_directories (${leplib_BINARY_DIR})

add_executable (leplibTests
                TestCsvFile.cpp
                TestConfigFile.cpp
                TestHttpClient.cpp
                TestJson.cpp
                TestMain.cpp
                TestSmartPointer.cpp
                TestSocketAddress.cpp
                TestString.cpp
                TestStringBuilder.cpp
                TestThread.cpp)

target_link_libraries (leplibTests leplib)
