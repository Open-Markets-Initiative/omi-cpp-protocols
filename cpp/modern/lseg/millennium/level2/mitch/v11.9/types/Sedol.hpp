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
