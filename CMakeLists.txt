cmake_minimum_required(VERSION 3.14)
project(TP3)

set(CMAKE_CXX_STANDARD 11)

set(OLD_SOURCE_FILES
        old/main.cpp
        old/MemoryManager.cpp
        old/MemoryManager.h
        old/MemorySegment.h
        old/Program.h)

set(SOURCE_FILES
        main.cpp
        MemoryManager.cpp
        MemoryManager.h
        MemorySegment.cpp
        MemorySegment.h
        Program.cpp
        Program.h
        )

add_executable(TP3_OLD old/main.cpp ${OLD_SOURCE_FILES})
add_executable(TP3 main.cpp ${SOURCE_FILES})
