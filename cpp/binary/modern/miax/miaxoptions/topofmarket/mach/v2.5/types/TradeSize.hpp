#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Number of contracts executed in this trade
struct TradeSize {

    static constexpr const char* name = "Trade Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TradeSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeSize(const std::uint32_t value)
     : value{ value } {}

    // get value of TradeSize field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
