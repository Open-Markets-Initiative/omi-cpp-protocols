#pragma once

#include <cstddef>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {


// Closing Only Indicator
struct ClosingOnlyIndicator {

    static constexpr auto name = "Closing Only Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ClosingOnlyIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ClosingOnlyIndicator(const char &value)
     : value{ value } {}

    // get value of ClosingOnlyIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
