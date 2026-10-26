#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace iex::iexequities::deep::snap::v1_6 {


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
