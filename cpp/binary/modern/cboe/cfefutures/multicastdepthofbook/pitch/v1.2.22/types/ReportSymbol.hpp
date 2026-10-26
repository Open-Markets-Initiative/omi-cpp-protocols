#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {


// Symbol for product or underlying security.
struct ReportSymbol {

    static constexpr auto name = "Report Symbol";
    static constexpr std::size_t size = 6;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr ReportSymbol()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ReportSymbol(const type &value)
     : value{ value } {}

    // get value of ReportSymbol field
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
