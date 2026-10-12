cmake_minimum_required(VERSION 3.20)
project(ENIACProgramOS VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENIAC_OS_BUILD_TESTS "Build ENIAC OS tests" ON)
option(ENIAC_OS_WARNINGS "Enable compiler warnings" ON)

add_library(eniac_os_core
    src/accumulator.cpp
    src/program.cpp
    src/machine.cpp
    src/monitor.cpp
)
target_include_directories(eniac_os_core PUBLIC include)

if(ENIAC_OS_WARNINGS)
    if(MSVC)
        target_compile_options(eniac_os_core PRIVATE /W4 /permissive-)
    else()
        target_compile_options(eniac_os_core PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
    endif()
endif()

add_executable(eniac_os src/main.cpp)
target_link_libraries(eniac_os PRIVATE eniac_os_core)

if(ENIAC_OS_BUILD_TESTS)
    enable_testing()
    add_executable(eniac_os_tests tests/test_main.cpp)
    target_link_libraries(eniac_os_tests PRIVATE eniac_os_core)
    add_test(NAME eniac_os_tests COMMAND eniac_os_tests)
endif()
