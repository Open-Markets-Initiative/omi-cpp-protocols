#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::integratedfeed::pillar::v2_5_g {

// The price closest to the reference price where the imbalance is 0.
struct ContinuousBookClearingPrice {

    static constexpr const char* name = "Continuous Book Clearing Price";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr ContinuousBookClearingPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ContinuousBookClearingPrice(const std::int32_t value)
     : value{ value } {}

    // get value of ContinuousBookClearingPrice field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
