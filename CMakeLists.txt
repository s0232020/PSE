cmake_minimum_required(VERSION 3.6)
project(ProjectTitle)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 17)
# Remove the "-O2" flag if you have problems with the debugger.
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Werror -O0") # -O0 is for debugging, used to be -02
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(gtest/include InputTests)

# Set Library dir
link_directories(gtest/lib InputTests)

# Set source files for RELEASE target
# Only add cpp files, no h files!
# Only add files with functionality here, no test files!
set(RELEASE_SOURCE_FILES src/main.cpp
        TinyXML/tinystr.cpp
        TinyXML/tinyxmlerror.cpp
        TinyXML/tinyxml.cpp
        TinyXML/tinyxmlparser.cpp
        src/PrintingSystem.cpp
        src/main.cpp
)

# Set source files for DEBUG target
# Only add cpp files, no h files!
set(DEBUG_SOURCE_FILES TinyXML/tinystr.cpp
        TinyXML/tinyxmlerror.cpp
        TinyXML/tinyxml.cpp
        TinyXML/tinyxmlparser.cpp
        src/PrintingSystemTests.cpp
        src/tests.cpp
        src/PrintingSystem.cpp)

# Create RELEASE target
add_executable(release_target ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(debug_target ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(debug_target gtest)
