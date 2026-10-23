#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace asx::asxderivatives::ntp::itch::v1_05 {


// Additional instrument series information.
struct LongName {

    static constexpr auto name = "Long Name";
    static constexpr std::size_t size = 60;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr LongName()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LongName(const type &value)
     : value{ value } {}

    // get value of LongName field
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
