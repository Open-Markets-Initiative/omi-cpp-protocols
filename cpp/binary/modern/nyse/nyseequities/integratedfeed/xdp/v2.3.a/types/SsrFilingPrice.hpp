#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

// For Pillar-powered markets, not supported and defaulted to 0. For NYSE, the price at which Sell Short interest in the opening auction will be filed if a Sell Short Restriction is in effect for the security.
struct SsrFilingPrice {

    static constexpr const char* name = "Ssr Filing Price";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr SsrFilingPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SsrFilingPrice(const std::uint32_t value)
     : value{ value } {}

    // get value of SsrFilingPrice field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
