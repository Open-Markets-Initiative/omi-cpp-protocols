#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Contains the total number of shares traded in a single transaction for an individual security
struct TradeVolume {

    static constexpr const char* name = "Trade Volume";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TradeVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeVolume(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of TradeVolume field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
