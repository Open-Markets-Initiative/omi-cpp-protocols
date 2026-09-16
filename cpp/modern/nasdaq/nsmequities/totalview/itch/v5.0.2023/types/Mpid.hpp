#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Denotes the market participant identifier for which the position message is being generated
struct Mpid {

    static constexpr auto name = "Mpid";
    static constexpr std::size_t size = 4;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr Mpid()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Mpid(const type &value)
     : value{ value } {}

    // get value of Mpid field
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
