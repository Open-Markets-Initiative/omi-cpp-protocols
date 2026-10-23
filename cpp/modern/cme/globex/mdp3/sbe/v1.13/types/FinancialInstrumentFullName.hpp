#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cme::mdp3::v13 {


// Long name of the instrument
struct FinancialInstrumentFullName {

    static constexpr auto name = "Financial Instrument Full Name";
    static constexpr std::size_t size = 35;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr FinancialInstrumentFullName()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FinancialInstrumentFullName(const type &value)
     : value{ value } {}

    // get value of FinancialInstrumentFullName field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field
    [[nodiscard]] std::size_t length() const {
        std::size_t index = 0;
        for (; index < size; ++index) {
            if (value[index] == '\0') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
