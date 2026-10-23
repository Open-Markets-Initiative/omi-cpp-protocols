#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cme::mdp3::v13 {


// Local (counter) currency
struct PriceQuoteCurrency {

    static constexpr auto name = "Price Quote Currency";
    static constexpr std::size_t size = 3;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr PriceQuoteCurrency()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PriceQuoteCurrency(const type &value)
     : value{ value } {}

    // get value of PriceQuoteCurrency field
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
