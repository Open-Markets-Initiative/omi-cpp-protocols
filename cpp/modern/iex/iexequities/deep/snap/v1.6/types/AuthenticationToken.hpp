#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace iex::iexequities::deep::snap::v1_6 {


// Token supplied by Iex Market Ops, left justified and space padded on the right
struct AuthenticationToken {

    static constexpr auto name = "Authentication Token";
    static constexpr std::size_t size = 40;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr AuthenticationToken()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AuthenticationToken(const type &value)
     : value{ value } {}

    // get value of AuthenticationToken field
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
