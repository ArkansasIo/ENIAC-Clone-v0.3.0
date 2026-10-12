cmake_minimum_required(VERSION 3.20)
project(ENIACClone VERSION 0.3.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENIAC_BUILD_TESTS "Build the test executable" ON)
option(ENIAC_ENABLE_WARNINGS "Enable strict compiler warnings" ON)

add_library(eniac_core
    src/arithmetic/decimal_alu.cpp
    src/config/function_table.cpp
    src/config/wiring.cpp
    src/control/execution_engine.cpp
    src/control/master_programmer.cpp
    src/control/program.cpp
    src/core/accumulator.cpp
    src/core/accumulator_bank.cpp
    src/core/machine.cpp
    src/core/machine_clock.cpp
    src/core/machine_config.cpp
    src/diagnostics/diagnostics.cpp
    src/io/console_reporter.cpp
    src/io/event_log.cpp
)

target_include_directories(eniac_core PUBLIC include)

if(ENIAC_ENABLE_WARNINGS)
    if(MSVC)
        target_compile_options(eniac_core PRIVATE /W4 /permissive-)
    else()
        target_compile_options(eniac_core PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
    endif()
endif()

add_executable(eniac src/app/main.cpp)
target_link_libraries(eniac PRIVATE eniac_core)

if(ENIAC_BUILD_TESTS)
    enable_testing()
    add_executable(eniac_tests tests/test_main.cpp)
    target_link_libraries(eniac_tests PRIVATE eniac_core)
    add_test(NAME eniac_tests COMMAND eniac_tests)
endif()
