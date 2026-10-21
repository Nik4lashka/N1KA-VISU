#pragma once

#include <cstddef>
#include <variant>

namespace visu
{

// Step ist die Operation die auf dem Array ausgeführt wird (vom Algo)
// Die Liste aller Steps (Trace) ist alle Schritte die der Algo ausgeführt hat
 
// Zwei Elemente wurden verglichen (ändert nichts am Array)
struct Compare
{
    std::size_t i;
    std::size_t j;
};

// Zwei Elemente wurden vertauscht
struct Swap
{
    std::size_t i;
    std::size_t j;
};

// Ein Element steht an seiner endgültigen Position
struct MarkSorted
{
    std::size_t index;
};

// Ein Step ist GENAU EINE dieser Operationen
using Step = std::variant<Compare, Swap, MarkSorted>;

} // namespace visu