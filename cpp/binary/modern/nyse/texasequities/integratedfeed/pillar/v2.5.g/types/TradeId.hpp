#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::texasequities::integratedfeed::pillar::v2_5_g {

// Unique ID assigned by the matching engine to this execution.
struct TradeId {

    static constexpr const char* name = "Trade Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TradeId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeId(const std::uint32_t value)
     : value{ value } {}

    // get value of TradeId field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
