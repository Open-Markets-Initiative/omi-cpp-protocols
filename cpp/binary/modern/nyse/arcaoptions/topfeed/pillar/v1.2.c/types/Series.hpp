#pragma once

#include <cstddef>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {


// Settlement related conditions. Valid values:
struct Series {

    static constexpr auto name = "Series";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Series()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Series(const char &value)
     : value{ value } {}

    // get value of Series field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
