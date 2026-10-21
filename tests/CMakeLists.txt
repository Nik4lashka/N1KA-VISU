add_executable(visu_tests
    TracedArrayTests.cpp
    BubbleSortTests.cpp
)

target_link_libraries(visu_tests PRIVATE visu_core visu_warnings Catch2::Catch2WithMain)

# Jeden TEST_CASE einzeln bei CTest anmelden (für "ctest" und den Test-Explorer in VS Code)
include(Catch)
catch_discover_tests(visu_tests)