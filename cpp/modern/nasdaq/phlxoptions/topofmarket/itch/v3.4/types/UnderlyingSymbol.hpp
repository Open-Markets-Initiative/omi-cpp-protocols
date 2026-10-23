#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {


// Denotes the unique symbol assigned to the underlying security within the Exchange System.
struct UnderlyingSymbol {

    static constexpr auto name = "Underlying Symbol";
    static constexpr std::size_t size = 13;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr UnderlyingSymbol()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UnderlyingSymbol(const type &value)
     : value{ value } {}

    // get value of UnderlyingSymbol field
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
