leplib
=========
A library for c++ with (hopes) of achieving the following goals:

    * lightweight - design on demand. implement api's on a necessity basis not for 
      completeness (for example, overloaded functions for all the possible datatypes 
      that can potentially be passed in)
    * embeddable - compact enough to be used in an embedded device project
    * portable - work across different OSs. initial goal is win32 and linux
    * modern - provide libraries that have more modern api's and utilities 
      (like an http client) found in newer languages like c# or java.
    * configurable - provide an easy way of configuring implementation aspects
    * customizable - be able to take only parts of the library that are needed. 

The default std libraries that ship with win32, glibc, uclibc or yourfavouritelibc seem to be 
insufficient in a couple of ways and there seems to be a need to write c++ wrappers for a lot 
of functionality (threads, synchronization objects, datatype converters, sockets etc.). 
Additionally, some of the c library calls are not exactly portable across windows and linux. 
There are a couple of good opensource alternatives like boost or poco but they did not seem to 
fit the needs of being lightweight and portable.

Build Instructions
=====================
To build, install cmake. Then go to build and type cmake ../
Then type make
The unit tests get built under tests, lepcpplibTests.
Logging can be disabled by commenting out -D__ENABLE_LOGGER_ from the top level
CMakeLists.txt

