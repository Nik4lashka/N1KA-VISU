#include "core/TracedArray.hpp"

#include <utility>

namespace visu
{

TracedArray::TracedArray(std::vector<int> values)
    : m_values(std::move(values))
{
}

bool TracedArray::less(std::size_t i, std::size_t j)
{
    // .at() prüft den Index und wirft std::out_of_range bei einem Fehler
    const bool result = m_values.at(i) < m_values.at(j);
    m_trace.push_back(Compare{i, j});
    return result;
}

void TracedArray::swap(std::size_t i, std::size_t j)
{
    std::swap(m_values.at(i), m_values.at(j));
    m_trace.push_back(Swap{i, j});
}

void TracedArray::markSorted(std::size_t index)
{
    (void)m_values.at(index); // nur Index prüfen
    m_trace.push_back(MarkSorted{index});
}

} // namespace visu