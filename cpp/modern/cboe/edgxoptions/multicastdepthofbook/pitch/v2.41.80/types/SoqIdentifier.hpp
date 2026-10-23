#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {


// Dissemination symbol of the final SOQ right padded with spaces.
struct SoqIdentifier {

    static constexpr auto name = "Soq Identifier";
    static constexpr std::size_t size = 20;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr SoqIdentifier()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SoqIdentifier(const type &value)
     : value{ value } {}

    // get value of SoqIdentifier field
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
