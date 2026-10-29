#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cboe::c1options::complex::pitch::v2_1_18 {


// Complex Instrument Id right padded with spaces.
struct ComplexInstrumentId8 {

    static constexpr auto name = "Complex Instrument Id 8";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr ComplexInstrumentId8()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ComplexInstrumentId8(const type &value)
     : value{ value } {}

    // get value of ComplexInstrumentId8 field
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
