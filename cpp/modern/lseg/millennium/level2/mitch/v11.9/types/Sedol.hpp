#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace lseg::millennium::level2::mitch::v11_9 {


// Instrument identification number
struct Sedol {

    static constexpr auto name = "Sedol";
    static constexpr std::size_t size = 12;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr Sedol()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Sedol(const type &value)
     : value{ value } {}

    // get value of Sedol field
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
