#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {


// Market identifier code
struct Mic {

    static constexpr auto name = "Mic";
    static constexpr std::size_t size = 4;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr Mic()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Mic(const type &value)
     : value{ value } {}

    // get value of Mic field
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
