#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cme::mdp3::v13 {


// Base/Local. Denotes the currency pair in CCY1/CCY2 convention
struct FxCurrencySymbol {

    static constexpr auto name = "Fx Currency Symbol";
    static constexpr std::size_t size = 7;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr FxCurrencySymbol()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FxCurrencySymbol(const type &value)
     : value{ value } {}

    // get value of FxCurrencySymbol field
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
