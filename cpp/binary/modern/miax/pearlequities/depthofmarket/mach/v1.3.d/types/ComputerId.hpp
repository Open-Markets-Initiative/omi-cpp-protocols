#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {


// issued by MIAX Futures Exchange during initial setup
struct ComputerId {

    static constexpr auto name = "Computer Id";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr ComputerId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ComputerId(const type &value)
     : value{ value } {}

    // get value of ComputerId field
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
