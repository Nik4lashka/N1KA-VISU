add_library(visu_core STATIC
    TracedArray.cpp
    algorithms/sorting/BubbleSort.cpp
)

# Includes immer ab src/ schreiben: #include "core/Step.hpp"
target_include_directories(visu_core PUBLIC ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(visu_core PRIVATE visu_warnings)