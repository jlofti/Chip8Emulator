cmake_minimum_required(VERSION 3.0.0)
set (CMAKE_CXX_STANDARD 17)
project(Chip8Emulator VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()




include_directories(include
                    include/**
                    include/SDL2/include
                    include/SDL2/include/**
                    src)


file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/include/*.hpp"
        "${PROJECT_SOURCE_DIR}/include/**/*.h"
        "${PROJECT_SOURCE_DIR}/include/**/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/*.c"
        "${PROJECT_SOURCE_DIR}/include/SDL2/include.*.h}",
        "${PROJECT_SOURCE_DIR}/include/SDL2/include.*.hpp}",
        "${PROJECT_SOURCE_DIR}/include/SDL2/include.*.c}",
        "${PROJECT_SOURCE_DIR}/include/SDL2/include.*.cpp}"
        )

        
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Chip8Emulator main.cpp ${all_SRCS})

target_link_libraries(Chip8Emulator ${SDL2_LIBRARIES})




set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
