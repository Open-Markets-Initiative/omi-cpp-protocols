#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v2_10_a {

// Offer Price represents the lowest price acceptable to a prospective seller at a particular time for a security; Upper Limit Price Band represents the upper price band value when Security Status Indicator is Limit Up-Limit Down Price Band
struct OfferPriceUpperLimitPriceBand {

    static constexpr const char* name = "Offer Price Upper Limit Price Band";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr OfferPriceUpperLimitPriceBand()
     : value{ 0 } {}

    // constructor for OfferPriceUpperLimitPriceBand field
    constexpr explicit OfferPriceUpperLimitPriceBand(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of OfferPriceUpperLimitPriceBand field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of OfferPriceUpperLimitPriceBand field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
