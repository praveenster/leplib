add_library (leplib
             ConfigFile.cpp
             CsvFile.cpp
             HttpClient.cpp
             JsonArray.cpp
             JsonBool.cpp
             JsonNull.cpp
             JsonNumber.cpp
             JsonObject.cpp
             JsonString.cpp
             JsonValue.cpp
             Logger.cpp
             Socket.cpp
             SocketAddress.cpp
             String.cpp
             StringBuilder.cpp
             TestCase.cpp
             TestModule.cpp
             TestSet.cpp
             Thread.cpp
             )

if(CMAKE_HOST_WIN32)
    target_link_libraries(leplib ${target_link_libraries} ws2_32)
endif(CMAKE_HOST_WIN32)

if(CMAKE_HOST_UNIX)
    target_link_libraries(leplib ${target_link_libraries} pthread)
endif(CMAKE_HOST_UNIX)
