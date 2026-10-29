#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_1_f {

// Continuous book clearing price
struct ContinuousBookClearingPrice {

    static constexpr const char* name = "Continuous Book Clearing Price";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ContinuousBookClearingPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ContinuousBookClearingPrice(const std::uint32_t value)
     : value{ value } {}

    // get value of ContinuousBookClearingPrice field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
