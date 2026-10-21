#include "core/algorithms/sorting/BubbleSort.hpp"

#include "core/TracedArray.hpp"

namespace visu
{

void BubbleSort::run(TracedArray& array) const
{
    std::size_t end = array.size(); // alles an end ist fertig sortiert

    while (end > 1)
    {
        bool swapped = false;
        for (std::size_t i = 0; i + 1 < end; i++)
        {
            if (array.less(i + 1, i))
            {
                array.swap(i, i + 1);
                swapped = true;
            }
        }

        --end;
        array.markSorted(end);

        if (!swapped)
        {
            break;
        }
    }

    for (std::size_t i = 0; i < end; ++i)
    {
        array.markSorted(i);
    }
}

} // namespace visu