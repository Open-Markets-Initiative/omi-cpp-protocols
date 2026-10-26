#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cme::mdp3::v13 {


// Long Name of the Underlying Instrument. For the instruments listed on Globex this value will be the same as of that contained in Security Definition Tag 2714-FinancialInstrumentFullName
struct UnderlyingFinancialInstrumentFullName {

    static constexpr auto name = "Underlying Financial Instrument Full Name";
    static constexpr std::size_t size = 35;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr UnderlyingFinancialInstrumentFullName()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UnderlyingFinancialInstrumentFullName(const type &value)
     : value{ value } {}

    // get value of UnderlyingFinancialInstrumentFullName field
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
