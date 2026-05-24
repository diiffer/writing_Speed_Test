cmake_minimum_required(VERSION 3.10)
project(writingSpeedTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(writingSpeedTest
        WST/main.cpp
        WST/GuiManager.cpp
        WST/WordGenerator.cpp
        WST/TypingTest.cpp
        WST/imgui/imgui.cpp
        WST/imgui/imgui_draw.cpp
        WST/imgui/imgui_widgets.cpp
        WST/imgui/imgui_tables.cpp
        WST/imgui/imgui_demo.cpp
        WST/imgui/backends/imgui_impl_glfw.cpp
        WST/imgui/backends/imgui_impl_opengl3.cpp
        WST/imgui/misc/cpp/imgui_stdlib.cpp
)

target_link_libraries(writingSpeedTest PRIVATE glfw OpenGL::GL)

target_include_directories(writingSpeedTest PRIVATE
    WST
    WST/imgui
    WST/imgui/backends
)

# Копируем директорию со словарями в папку со сборкой
add_custom_command(TARGET writingSpeedTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/WST/dictionaries"
    "$<TARGET_FILE_DIR:writingSpeedTest>/dictionaries"
)