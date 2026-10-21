cmake_minimum_required(VERSION 3.25)

project(N1KA-VISU
    VERSION 0.1.0
    DESCRIPTION "Visualisierung von Algorithmen"
    LANGUAGES C CXX
)

# C++20 – reiner Standard ohne Compiler-Erweiterungen
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Schreibt build/<preset>/compile_commands.json (für clangd / clang-tidy)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/Dependencies.cmake)

# Warnungen als INTERFACE-Target: Wer es linkt, bekommt die Optionen
add_library(visu_warnings INTERFACE)
target_compile_options(visu_warnings INTERFACE -Wall -Wextra -Wpedantic)

# Logik ohne GUI (eigene Library, siehe src/core/CMakeLists.txt)
add_subdirectory(src/core)

# Das Programm mit Fenster
add_executable(visu src/main.cpp)
target_link_libraries(visu PRIVATE imgui visu_warnings)

# Unit-Tests
enable_testing()
add_subdirectory(tests)