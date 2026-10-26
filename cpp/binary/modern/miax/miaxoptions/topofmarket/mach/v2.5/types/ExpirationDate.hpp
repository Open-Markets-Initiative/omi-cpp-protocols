#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {


// Expiration date of the option in YYYYMMDD format
struct ExpirationDate {

    static constexpr auto name = "Expiration Date";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr ExpirationDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExpirationDate(const type &value)
     : value{ value } {}

    // get value of ExpirationDate field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field: its characters up to the fill after the last of them, so a space
    // or a null inside the text is kept
    [[nodiscard]] std::size_t length() const {
        std::size_t index = size;
        for (; index > 0; --index) {
            if (value[index - 1] != ' ') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
