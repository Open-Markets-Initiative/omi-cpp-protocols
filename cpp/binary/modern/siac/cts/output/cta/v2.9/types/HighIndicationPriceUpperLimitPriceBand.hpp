#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_9 {

// Represents an approximation of what the high end Offer price of a security's trading range may be, or the upper price band value for a security. Has implied 6 decimal places
struct HighIndicationPriceUpperLimitPriceBand {

    static constexpr const char* name = "High Indication Price Upper Limit Price Band";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr HighIndicationPriceUpperLimitPriceBand()
     : value{ 0 } {}

    // constructor for HighIndicationPriceUpperLimitPriceBand field
    constexpr explicit HighIndicationPriceUpperLimitPriceBand(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of HighIndicationPriceUpperLimitPriceBand field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of HighIndicationPriceUpperLimitPriceBand field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
