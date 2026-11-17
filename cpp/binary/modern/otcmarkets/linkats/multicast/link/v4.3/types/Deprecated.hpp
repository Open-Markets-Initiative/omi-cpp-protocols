// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/Deprecated.hpp
#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace otcmarkets::linkats::multicast::link::v4_3 {


// Deprecated field. Spaces will be sent in the message.
struct Deprecated {

    static constexpr auto name = "Deprecated";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr Deprecated()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Deprecated(const type &value)
     : value{ value } {}

    // get value of Deprecated field
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
