#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// ISE’s Strategy ID assigned daily, valid while there are any open complex orders for the day
struct StrategyId {

    static constexpr const char* name = "Strategy Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr StrategyId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StrategyId(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of StrategyId field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
