#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

// The TradeID of the original Trade or Execution message to be cancelled.
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
