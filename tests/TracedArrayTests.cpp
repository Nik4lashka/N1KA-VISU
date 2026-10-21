#include "core/TracedArray.hpp"

#include <catch2/catch_test_macros.hpp>

#include <stdexcept>
#include <variant>
#include <vector>

using namespace visu;

TEST_CASE("less() vergleicht und zeichnet einen Compare-Step auf")
{
    TracedArray array({3, 1, 2});

    CHECK(array.less(1, 0));       // 1 < 3
    CHECK_FALSE(array.less(0, 2)); // 3 < 2 ist falsch

    REQUIRE(array.trace().size() == 2);
    const auto* compare = std::get_if<Compare>(&array.trace()[0]);
    REQUIRE(compare != nullptr);
    CHECK(compare->i == 1);
    CHECK(compare->j == 0);

    CHECK(array.values() == std::vector<int>{3, 1, 2}); // Vergleichen ändert nichts
}

TEST_CASE("swap() vertauscht und zeichnet einen Swap-Step auf")
{
    TracedArray array({3, 1, 2});

    array.swap(0, 2);

    CHECK(array.values() == std::vector<int>{2, 1, 3});
    REQUIRE(array.trace().size() == 1);
    CHECK(std::holds_alternative<Swap>(array.trace()[0]));
}

TEST_CASE("Falscher Index wirft eine Exception und zeichnet nichts auf")
{
    TracedArray array({1, 2});

    CHECK_THROWS_AS(array.swap(0, 5), std::out_of_range);
    CHECK_THROWS_AS(array.less(7, 0), std::out_of_range);
    CHECK(array.trace().empty());
}