#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {


// Symbol right padded with spaces.
struct ExpandedSymbol {

    static constexpr auto name = "Expanded Symbol";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr ExpandedSymbol()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExpandedSymbol(const type &value)
     : value{ value } {}

    // get value of ExpandedSymbol field
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
