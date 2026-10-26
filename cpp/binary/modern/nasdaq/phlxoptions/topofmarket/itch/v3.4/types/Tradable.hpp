#pragma once

#include <cstddef>

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {


// Denotes whether or not this option is tradable at the exchange:
struct Tradable {

    static constexpr auto name = "Tradable";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Tradable()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Tradable(const char &value)
     : value{ value } {}

    // get value of Tradable field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
