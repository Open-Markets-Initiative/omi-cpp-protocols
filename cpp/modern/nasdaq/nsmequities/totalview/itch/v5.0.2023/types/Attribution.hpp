#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Nasdaq market participant identifier associated with the entered order
struct Attribution {

    static constexpr auto name = "Attribution";
    static constexpr std::size_t size = 4;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr Attribution()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Attribution(const type &value)
     : value{ value } {}

    // get value of Attribution field
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
