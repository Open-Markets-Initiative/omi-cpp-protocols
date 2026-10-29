#pragma once

#include <cstddef>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {


// <space> = regular quote/autox eligible “X” = Pre-Open/Halted
struct QuoteCondition {

    static constexpr auto name = "Quote Condition";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr QuoteCondition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit QuoteCondition(const char &value)
     : value{ value } {}

    // get value of QuoteCondition field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
