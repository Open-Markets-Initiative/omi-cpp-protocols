#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace siac::cqs::output::cta::v1_91 {


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
