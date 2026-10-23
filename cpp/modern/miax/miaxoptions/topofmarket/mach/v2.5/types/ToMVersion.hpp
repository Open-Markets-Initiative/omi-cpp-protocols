#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {


// Eg: TOM2.1
struct ToMVersion {

    static constexpr auto name = "To M Version";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr ToMVersion()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ToMVersion(const type &value)
     : value{ value } {}

    // get value of ToMVersion field
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
