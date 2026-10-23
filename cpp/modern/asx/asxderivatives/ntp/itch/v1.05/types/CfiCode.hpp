#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace asx::asxderivatives::ntp::itch::v1_05 {


// Indicates the type of security using ISO 10962 standard, CFI code values.
struct CfiCode {

    static constexpr auto name = "Cfi Code";
    static constexpr std::size_t size = 6;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr CfiCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CfiCode(const type &value)
     : value{ value } {}

    // get value of CfiCode field
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
