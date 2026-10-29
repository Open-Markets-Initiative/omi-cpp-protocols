#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// The original TradeID of the Trade being cancelled.
struct OriginalTradeId {

    static constexpr const char* name = "Original Trade Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr OriginalTradeId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OriginalTradeId(const std::uint32_t value)
     : value{ value } {}

    // get value of OriginalTradeId field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
