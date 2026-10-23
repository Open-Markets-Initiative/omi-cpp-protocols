#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {


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
