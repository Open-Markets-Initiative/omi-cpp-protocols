#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace lseg::millennium::level2::mitch::v11_9 {


// Reason for the manual session change or the trading halt.
struct Reason {

    static constexpr auto name = "Reason";
    static constexpr std::size_t size = 4;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr Reason()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Reason(const type &value)
     : value{ value } {}

    // get value of Reason field
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
