# File Tree

    eniac_os/
      CMakeLists.txt
      README.md
      .gitignore
      include/eniac_os/
        accumulator.hpp
        instruction.hpp
        machine.hpp
        monitor.hpp
        program.hpp
      src/
        accumulator.cpp
        main.cpp
        machine.cpp
        monitor.cpp
        program.cpp
      tests/
        test_main.cpp
      examples/
        addition.epr
        multiply.epr
      config/
        default_machine.json
      scripts/
        build.sh
      docs/
        API_REFERENCE.md
        ARCHITECTURE.md
        DESIGN_SPEC.md
        FILE_TREE.md
        HISTORICAL_SCOPE.md
        OPERATOR_MANUAL.md
        OPERATOR_UI.md
        PROGRAM_FORMAT.md
        ROADMAP.md

This subproject is independently configured by eniac_os/CMakeLists.txt and does not need the parent project's CMake targets.
