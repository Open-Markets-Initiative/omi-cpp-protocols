#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {


// Expressed in HH:MM:SS format. Eg: 04:00:00.
struct OpeningTime {

    static constexpr auto name = "Opening Time";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr OpeningTime()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OpeningTime(const type &value)
     : value{ value } {}

    // get value of OpeningTime field
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
