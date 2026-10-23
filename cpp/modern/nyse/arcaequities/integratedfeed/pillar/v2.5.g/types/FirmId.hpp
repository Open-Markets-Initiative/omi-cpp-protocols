#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g {


// The market participant's firm ID.
struct FirmId {

    static constexpr auto name = "Firm Id";
    static constexpr std::size_t size = 5;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr FirmId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FirmId(const type &value)
     : value{ value } {}

    // get value of FirmId field
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
