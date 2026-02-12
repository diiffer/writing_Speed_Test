cmake_minimum_required(VERSION 3.10)
project(writingSpeedTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(writingSpeedTest
        WST/main.cpp
        WST/TerminalManager.cpp
        WST/WordGenerator.cpp
        WST/TypingTest.cpp
)

target_include_directories(writingSpeedTest PRIVATE WST)