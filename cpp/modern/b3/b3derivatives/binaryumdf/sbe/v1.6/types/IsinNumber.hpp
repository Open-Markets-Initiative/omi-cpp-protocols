#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {


// isinNumber
struct IsinNumber {

    static constexpr auto name = "Isin Number";
    static constexpr std::size_t size = 12;

    // underlying type
    using type = std::array<char, size>;

    // whether the optional IsinNumber field is present
    [[nodiscard]] bool has_value() const {
        return value[0] != '\0';
    }

    // default constructor
    constexpr IsinNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IsinNumber(const type &value)
     : value{ value } {}

    // get value of IsinNumber field
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
