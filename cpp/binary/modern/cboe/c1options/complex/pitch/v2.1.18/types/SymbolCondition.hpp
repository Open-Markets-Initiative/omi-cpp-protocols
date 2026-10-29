#pragma once

#include <cstddef>

namespace cboe::c1options::complex::pitch::v2_1_18 {


// N = Normal C = Closing Only
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
