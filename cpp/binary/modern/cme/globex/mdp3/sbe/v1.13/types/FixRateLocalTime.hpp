#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cme::mdp3::v13 {


// Fixing Rate Local Time, denoted in HH:MM:SS format
struct FixRateLocalTime {

    static constexpr auto name = "Fix Rate Local Time";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr FixRateLocalTime()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FixRateLocalTime(const type &value)
     : value{ value } {}

    // get value of FixRateLocalTime field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field: its characters up to the fill after the last of them, so a space
    // or a null inside the text is kept
    [[nodiscard]] std::size_t length() const {
        std::size_t index = size;
        for (; index > 0; --index) {
            if (value[index - 1] != '\0') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
