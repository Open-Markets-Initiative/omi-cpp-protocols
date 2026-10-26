#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Represents an approximation of what the low end Bid price of a security's trading range may be, or the lower price band value for a security. Has implied 6 decimal places
struct LowIndicationPriceLowerLimitPriceBand {

    static constexpr const char* name = "Low Indication Price Lower Limit Price Band";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr LowIndicationPriceLowerLimitPriceBand()
     : value{ 0 } {}

    // constructor for LowIndicationPriceLowerLimitPriceBand field
    constexpr explicit LowIndicationPriceLowerLimitPriceBand(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of LowIndicationPriceLowerLimitPriceBand field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of LowIndicationPriceLowerLimitPriceBand field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
