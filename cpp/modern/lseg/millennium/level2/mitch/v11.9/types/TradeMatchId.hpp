#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::millennium::level2::mitch::v11_9 {

// Unique identifier of the trade.
struct TradeMatchId {

    static constexpr const char* name = "Trade Match Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr TradeMatchId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeMatchId(const std::uint64_t value)
     : value{ value } {}

    // get value of TradeMatchId field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
