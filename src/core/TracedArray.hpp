#pragma once

#include "core/Step.hpp"

#include <cstddef>
#include <vector>

namespace visu
{

// Algorithmus greift über diese Klasse auf Daten zu
// Dann wird der Trace automatisch mit erstellt
class TracedArray
{
public:
    explicit TracedArray(std::vector<int> values);

    std::size_t size() const { return m_values.size(); }

    bool less(std::size_t i, std::size_t j);   // vergleich ( i < j)
    void swap(std::size_t i, std::size_t j);   // tausch ( i <-> j)
    void markSorted(std::size_t index);        // fertig sortiert an index

    const std::vector<int>& values() const { return m_values; }
    const std::vector<Step>& trace() const { return m_trace; }

private:
    std::vector<int> m_values;
    std::vector<Step> m_trace;
};

} // namespace visu