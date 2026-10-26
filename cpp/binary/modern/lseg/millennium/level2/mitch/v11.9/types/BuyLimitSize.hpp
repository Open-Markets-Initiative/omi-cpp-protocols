#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::millennium::level2::mitch::v11_9 {

// Cumulative visible size at best bid price. Will contain zero if there are no visible limit orders on the buy side
struct BuyLimitSize {

    static constexpr const char* name = "Buy Limit Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr BuyLimitSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BuyLimitSize(const std::uint32_t value)
     : value{ value } {}

    // get value of BuyLimitSize field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
