// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.1: types/PaddingChar2.hpp
#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {


// padding
struct PaddingChar2 {

    static constexpr auto name = "Padding char 2";
    static constexpr std::size_t size = 2;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr PaddingChar2()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PaddingChar2(const type &value)
     : value{ value } {}

    // get value of PaddingChar2 field
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
