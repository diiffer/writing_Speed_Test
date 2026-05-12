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

# Копируем директорию со словарями в папку со сборкой
add_custom_command(TARGET writingSpeedTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/WST/dictionaries"
    "$<TARGET_FILE_DIR:writingSpeedTest>/dictionaries"
)