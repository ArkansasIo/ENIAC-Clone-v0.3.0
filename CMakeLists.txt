cmake_minimum_required(VERSION 3.25)
project(ENIACClone VERSION 0.3.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---------------------------------------------------------------------------
# ENIAC-Clone v0.3.0
# ---------------------------------------------------------------------------
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

# ---------------------------------------------------------------------------
# FLOPPY 5.2 - Modular Disk Development Kit
# ---------------------------------------------------------------------------
add_library(floppy52_core src/core/ModuleRegistry.cpp src/core/MemoryTable.cpp src/core/Config.cpp)
target_include_directories(floppy52_core PUBLIC include)
target_compile_features(floppy52_core PUBLIC cxx_std_23)

add_executable(floppy52 src/main.cpp)
target_link_libraries(floppy52 PRIVATE floppy52_core)

include(CTest)
if(BUILD_TESTING)
  add_executable(floppy52_tests tests/test_core.cpp)
  target_link_libraries(floppy52_tests PRIVATE floppy52_core)
  add_test(NAME floppy52_tests COMMAND floppy52_tests)
endif()
