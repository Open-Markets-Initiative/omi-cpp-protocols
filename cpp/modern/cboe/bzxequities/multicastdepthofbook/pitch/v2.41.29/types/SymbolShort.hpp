#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29 {


// Symbol
struct SymbolShort {

    static constexpr auto name = "Symbol Short";
    static constexpr std::size_t size = 6;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr SymbolShort()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SymbolShort(const type &value)
     : value{ value } {}

    // get value of SymbolShort field
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
