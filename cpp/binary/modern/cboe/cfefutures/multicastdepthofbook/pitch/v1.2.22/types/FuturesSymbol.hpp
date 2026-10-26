#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {


// Twelve character textual definition of the symbol where the first six characters contain the product symbol, left justified, and padded on the right with spaces, and the right most six characters are the expiration date in YYMMDD format.
struct FuturesSymbol {

    static constexpr auto name = "Futures Symbol";
    static constexpr std::size_t size = 12;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr FuturesSymbol()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FuturesSymbol(const type &value)
     : value{ value } {}

    // get value of FuturesSymbol field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field: its characters up to the fill after the last of them, so a space
    // or a null inside the text is kept
    [[nodiscard]] std::size_t length() const {
        std::size_t index = size;
        for (; index > 0; --index) {
            if (value[index - 1] != ' ') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
