#pragma once

#include <cstddef>

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {


// "N" = Normal
struct SymbolCondition {

    static constexpr auto name = "Symbol Condition";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SymbolCondition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SymbolCondition(const char &value)
     : value{ value } {}

    // get value of SymbolCondition field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
