// Databento.MarketData.Normalized.Dbn.v2: types/StrikePriceCurrency.hpp
#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace databento::marketdata::normalized::dbn::v2 {


// The strike price currency
struct StrikePriceCurrency {

    static constexpr auto name = "Strike Price Currency";
    static constexpr std::size_t size = 4;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr StrikePriceCurrency()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StrikePriceCurrency(const type &value)
     : value{ value } {}

    // get value of StrikePriceCurrency field
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
