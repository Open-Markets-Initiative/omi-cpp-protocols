#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::millennium::level2::mitch::v11_9 {

// Best offer price. Will contain zero if there are no visible limit orders on the sell side
struct SellLimitPrice {

    static constexpr const char* name = "Sell Limit Price";
    static constexpr std::size_t size =  8;
    using type = std::int64_t;

    // default constructor
    constexpr SellLimitPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SellLimitPrice(const std::int64_t value)
     : value{ value } {}

    // get value of SellLimitPrice field
    [[nodiscard]] std::int64_t get() const {
        return value;
    }

  protected:
    std::int64_t value;
};
}
