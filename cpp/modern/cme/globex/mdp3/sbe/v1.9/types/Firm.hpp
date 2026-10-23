#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cme::mdp3::v9 {


// Firm ID
struct Firm {

    static constexpr auto name = "Firm";
    static constexpr std::size_t size = 5;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr Firm()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Firm(const type &value)
     : value{ value } {}

    // get value of Firm field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field
    [[nodiscard]] std::size_t length() const {
        std::size_t index = 0;
        for (; index < size; ++index) {
            if (value[index] == '\0') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
