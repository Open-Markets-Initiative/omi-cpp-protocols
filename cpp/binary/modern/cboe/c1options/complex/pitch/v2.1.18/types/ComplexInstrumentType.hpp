#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cboe::c1options::complex::pitch::v2_1_18 {


// 4 character field; each field describes a characteristic.
struct ComplexInstrumentType {

    static constexpr auto name = "Complex Instrument Type";
    static constexpr std::size_t size = 4;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr ComplexInstrumentType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ComplexInstrumentType(const type &value)
     : value{ value } {}

    // get value of ComplexInstrumentType field
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
