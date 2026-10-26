#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// 0 (zero) if new trade. Trade ID of the original trade if this trade originated as a correction of the original trade.
struct ReferenceTradeId {

    static constexpr const char* name = "Reference Trade Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ReferenceTradeId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ReferenceTradeId(const std::uint32_t value)
     : value{ value } {}

    // get value of ReferenceTradeId field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
