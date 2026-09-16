#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Denotes the security symbol for the issue in the NASDAQ execution system.
struct Stock {

    static constexpr auto name = "Stock";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr Stock()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Stock(const type &value)
     : value{ value } {}

    // get value of Stock field
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
