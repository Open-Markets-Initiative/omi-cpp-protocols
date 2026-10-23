#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// A non-zero value indicates that this trade is part of an execution cycle for a combination trade from the E or P message.
struct BuyerCombinationTradeId {

    static constexpr const char* name = "Buyer Combination Trade Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr BuyerCombinationTradeId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BuyerCombinationTradeId(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of BuyerCombinationTradeId field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
