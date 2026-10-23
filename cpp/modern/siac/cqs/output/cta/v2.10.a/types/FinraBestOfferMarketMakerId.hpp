#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace siac::cqs::output::cta::v2_10_a {


// Contains the FINRA ADF provided FINRA Best Offer Market Maker identifier of the Market Maker that had the FINRA Best Offer
struct FinraBestOfferMarketMakerId {

    static constexpr auto name = "Finra Best Offer Market Maker Id";
    static constexpr std::size_t size = 4;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr FinraBestOfferMarketMakerId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FinraBestOfferMarketMakerId(const type &value)
     : value{ value } {}

    // get value of FinraBestOfferMarketMakerId field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field
    [[nodiscard]] std::size_t length() const {
        std::size_t index = 0;
        for (; index < size; ++index) {
            if (value[index] == ' ') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
