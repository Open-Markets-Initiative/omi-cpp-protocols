// Databento.MarketData.Normalized.Dbn.v1: types/Err.hpp
#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace databento::marketdata::normalized::dbn::v1 {


// The error message
struct Err {

    static constexpr auto name = "Err";
    static constexpr std::size_t size = 64;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr Err()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Err(const type &value)
     : value{ value } {}

    // get value of Err field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field: its characters up to the fill after the last of them, so a space
    // or a null inside the text is kept
    [[nodiscard]] std::size_t length() const {
        std::size_t index = size;
        for (; index > 0; --index) {
            if (value[index - 1] != '\0') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
