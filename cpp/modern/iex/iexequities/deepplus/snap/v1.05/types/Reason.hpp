#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace iex::iexequities::deepplus::snap::v1_05 {


// Reason for the trading status change
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
