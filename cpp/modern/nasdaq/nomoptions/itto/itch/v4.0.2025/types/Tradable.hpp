#pragma once

#include <cstddef>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {


// Denotes whether or not this option is tradable at the exchange. The allowable values are:
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
