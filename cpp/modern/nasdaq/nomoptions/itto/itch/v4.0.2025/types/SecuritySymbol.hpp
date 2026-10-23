#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {


// Denotes the security symbol.
struct SecuritySymbol {

    static constexpr auto name = "Security Symbol";
    static constexpr std::size_t size = 6;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr SecuritySymbol()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecuritySymbol(const type &value)
     : value{ value } {}

    // get value of SecuritySymbol field
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
