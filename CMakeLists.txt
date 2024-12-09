cmake_minimum_required(VERSION 3.14)
project(TP3)

set(CMAKE_CXX_STANDARD 11)

set(OLD_SOURCE_FILES
        old/main.cpp
        old/MemoryManager.cpp
        old/MemoryManager.h
        old/MemorySegment.h
        old/Program.h)

set(TEAM_SOURCE_FILES
        team/main-team.cpp)

set(SOURCE_FILES
        main.cpp
        MemoryManager.h
        MemoryManager.cpp
        MemorySegment.h
        MemorySegment.cpp
        Program.h
        Program.cpp
        )

add_executable(TP3_OLD old/main.cpp ${OLD_SOURCE_FILES})
add_executable(TP3_TEAM team/main-team.cpp ${TEAM_SOURCE_FILES})
add_executable(TP3 main.cpp ${SOURCE_FILES})
