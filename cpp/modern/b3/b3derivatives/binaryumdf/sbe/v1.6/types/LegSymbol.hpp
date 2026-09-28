#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {


// Leg symbol.
struct LegSymbol {

    static constexpr auto name = "Leg Symbol";
    static constexpr std::size_t size = 20;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr LegSymbol()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegSymbol(const type &value)
     : value{ value } {}

    // get value of LegSymbol field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field
    [[nodiscard]] std::size_t length() const {
        std::size_t index = 0;
        for (; index < size; ++index) {
            if (value[index] == '\0') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
