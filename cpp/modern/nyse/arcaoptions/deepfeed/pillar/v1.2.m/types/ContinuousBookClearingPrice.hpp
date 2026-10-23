#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// The price at which all interest on the book can trade, including auction and imbalance offset interest, and disregarding auction collars.
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
