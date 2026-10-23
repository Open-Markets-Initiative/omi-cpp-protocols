#pragma once

#include <cstddef>

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {


// Denotes which System Event is used to determine when trading ceases in this symbol.
struct OptionClosingType {

    static constexpr auto name = "Option Closing Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OptionClosingType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OptionClosingType(const char &value)
     : value{ value } {}

    // get value of OptionClosingType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
