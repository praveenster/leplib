include_directories (${lep_SOURCE_DIR}/lep)

link_directories (${lep_BINARY_DIR})

add_executable (lep_tests
                TestCsvFile.cpp
                TestConfigFile.cpp
                TestHttpClient.cpp
                TestJson.cpp
                TestMain.cpp
                TestSmartPointer.cpp
                TestSocket.cpp
                TestSocketAddress.cpp
                TestString.cpp
                TestStringBuilder.cpp
                TestThread.cpp)

target_link_libraries (lep_tests lep)

