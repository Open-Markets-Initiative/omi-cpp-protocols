#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_10 {

// Contains the total number of shares traded in a single transaction for an individual security
struct TradeVolumeShort {

    static constexpr const char* name = "Trade Volume Short";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr TradeVolumeShort()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeVolumeShort(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of TradeVolumeShort field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
