#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {


// OSI Symbol.
struct OsiSymbol {

    static constexpr auto name = "Osi Symbol";
    static constexpr std::size_t size = 21;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr OsiSymbol()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OsiSymbol(const type &value)
     : value{ value } {}

    // get value of OsiSymbol field
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
