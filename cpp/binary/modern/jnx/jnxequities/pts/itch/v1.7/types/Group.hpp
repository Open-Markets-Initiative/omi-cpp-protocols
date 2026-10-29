#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace jnx::jnxequities::pts::itch::v1_7 {


// Orderbook group identifier.
struct Group {

    static constexpr auto name = "Group";
    static constexpr std::size_t size = 4;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr Group()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Group(const type &value)
     : value{ value } {}

    // get value of Group field
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
