#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cme::mdp3::v9 {


// Currency in which the StrikePrice is denominated
struct StrikeCurrency {

    static constexpr auto name = "Strike Currency";
    static constexpr std::size_t size = 3;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr StrikeCurrency()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StrikeCurrency(const type &value)
     : value{ value } {}

    // get value of StrikeCurrency field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field: its characters up to the fill after the last of them, so a space
    // or a null inside the text is kept
    [[nodiscard]] std::size_t length() const {
        std::size_t index = size;
        for (; index > 0; --index) {
            if (value[index - 1] != '\0') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
