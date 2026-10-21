#pragma once

#include <string_view>

namespace visu
{

class TracedArray;

class Algorithm
{
public:
    virtual ~Algorithm() = default;

    virtual std::string_view name() const = 0;
    virtual void run(TracedArray& array) const = 0;
};

}