#include "core/TracedArray.hpp"
#include "core/algorithms/sorting/BubbleSort.hpp"

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <utility>
#include <variant>
#include <vector>

using namespace visu;

namespace
{

const std::vector<std::vector<int>> kInputs = {
    {},              // leer
    {42},            // ein Element
    {1, 2, 3, 4},    // schon sortiert
    {4, 3, 2, 1},    // umgekehrt sortiert
    {5, 1, 4, 2, 8}, // gemischt
    {3, 3, 1, 3},    // Duplikate
};

// Wendet nur die Swap-Steps auf die Startwerte an – so wie es später der Player tut
std::vector<int> replay(std::vector<int> values, const std::vector<Step>& trace)
{
    for (const Step& step : trace)
    {
        if (const auto* swap = std::get_if<Swap>(&step))
            std::swap(values[swap->i], values[swap->j]);
    }
    return values;
}

} // namespace

TEST_CASE("Bubble Sort sortiert verschiedene Eingaben")
{
    for (const auto& input : kInputs)
    {
        TracedArray array(input);
        BubbleSort{}.run(array);

        auto expected = input;
        std::ranges::sort(expected);
        CHECK(array.values() == expected);
    }
}

TEST_CASE("Den Trace nachzuspielen ergibt dasselbe Ergebnis")
{
    for (const auto& input : kInputs)
    {
        TracedArray array(input);
        BubbleSort{}.run(array);

        CHECK(replay(input, array.trace()) == array.values());
    }
}

TEST_CASE("Jedes Element wird genau einmal als sortiert markiert")
{
    for (const auto& input : kInputs)
    {
        TracedArray array(input);
        BubbleSort{}.run(array);

        std::vector<int> markCount(input.size(), 0);
        for (const Step& step : array.trace())
        {
            if (const auto* mark = std::get_if<MarkSorted>(&step))
                ++markCount[mark->index];
        }
        CHECK(std::ranges::all_of(markCount, [](int count) { return count == 1; }));
    }
}

TEST_CASE("Bei sortierter Eingabe bricht Bubble Sort nach einem Durchlauf ab")
{
    TracedArray array({1, 2, 3, 4, 5});
    BubbleSort{}.run(array);

    const auto compares = std::ranges::count_if(array.trace(), [](const Step& step) {
        return std::holds_alternative<Compare>(step);
    });
    const auto swaps = std::ranges::count_if(array.trace(), [](const Step& step) {
        return std::holds_alternative<Swap>(step);
    });

    CHECK(compares == 4); // n - 1 Vergleiche
    CHECK(swaps == 0);
}