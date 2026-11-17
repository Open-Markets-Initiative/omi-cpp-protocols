// Databento.MarketData.Normalized.Dbn.v2: types/StypeInSymbol.hpp
#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace databento::marketdata::normalized::dbn::v2 {


// The input symbol
struct StypeInSymbol {

    static constexpr auto name = "Stype In Symbol";
    static constexpr std::size_t size = 71;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr StypeInSymbol()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StypeInSymbol(const type &value)
     : value{ value } {}

    // get value of StypeInSymbol field
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
