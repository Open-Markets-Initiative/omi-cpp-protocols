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
