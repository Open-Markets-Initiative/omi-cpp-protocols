#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {


// Reserved
struct Reserved3 {

    static constexpr auto name = "Reserved 3";
    static constexpr std::size_t size = 3;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr Reserved3()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Reserved3(const type &value)
     : value{ value } {}

    // get value of Reserved3 field
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
