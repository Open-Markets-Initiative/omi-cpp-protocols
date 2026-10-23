#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g {

// For NYSE non-Significant imbalances, if a Sell Short Restriction is in effect, the price at which Sell Short interest will be filed.
struct SsrFilingPrice {

    static constexpr const char* name = "Ssr Filing Price";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr SsrFilingPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SsrFilingPrice(const std::int32_t value)
     : value{ value } {}

    // get value of SsrFilingPrice field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
