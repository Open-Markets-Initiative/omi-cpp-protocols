#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// TradeId
struct TradeId {

    static constexpr const char* name = "Trade Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr TradeId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeId(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of TradeId field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
