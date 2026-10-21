#pragma once

#include "../../Algorithm.hpp"

namespace visu
{

class BubbleSort final : public Algorithm
{
public:
    std::string_view name() const override { return "Bubble Sort"; }
    void run(TracedArray& array) const override;
};

} // namespace visu