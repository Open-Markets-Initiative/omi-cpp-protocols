#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::millennium::level2::mitch::v11_9 {

// Best bid price. Will contain zero if there are no visible limit orders on the buy side
struct BuyLimitPrice {

    static constexpr const char* name = "Buy Limit Price";
    static constexpr std::size_t size =  8;
    using type = std::int64_t;

    // default constructor
    constexpr BuyLimitPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BuyLimitPrice(const std::int64_t value)
     : value{ value } {}

    // get value of BuyLimitPrice field
    [[nodiscard]] std::int64_t get() const {
        return value;
    }

  protected:
    std::int64_t value;
};
}
