#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {


// Ticker symbol for the security in NASDAQ Integrated Platform format.
struct TickerSymbol {

    static constexpr auto name = "Ticker Symbol";
    static constexpr std::size_t size = 11;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr TickerSymbol()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TickerSymbol(const type &value)
     : value{ value } {}

    // get value of TickerSymbol field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field
    [[nodiscard]] std::size_t length() const {
        std::size_t index = 0;
        for (; index < size; ++index) {
            if (value[index] == ' ') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
