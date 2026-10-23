#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29 {


// Symbol
struct SymbolLong {

    static constexpr auto name = "Symbol Long";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr SymbolLong()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SymbolLong(const type &value)
     : value{ value } {}

    // get value of SymbolLong field
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
