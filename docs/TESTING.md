# Testing

Build and run the test suite:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

Recommended future cases:
- accumulator boundaries and sign transitions;
- overflow and normalization;
- invalid accumulator indices;
- invalid wiring endpoints;
- empty programs and bounded execution;
- machine lifecycle transitions;
- event log ordering;
- configuration validation.
