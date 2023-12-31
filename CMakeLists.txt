cmake_minimum_required(VERSION 3.0.0)
set (CMAKE_CXX_STANDARD 17)
project(Chip8Emulator VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_subdirectory(include/SDL2)

add_executable(Chip8Emulator main.cpp)

add_library(memory include/memory.h src/memory.cpp)
add_library(display include/display.h src/display.cpp)
add_library(cpu include/cpu.h src/cpu.cpp)
add_library(keyboard include/keyboard.h src/keyboard.cpp)
add_library(window include/window.h src/window.cpp)

target_link_libraries(cpu memory display keyboard)
target_link_libraries(display SDL2 cpu)
target_link_libraries(window SDL2)
target_link_libraries(${PROJECT_NAME} cpu memory display keyboard window)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
