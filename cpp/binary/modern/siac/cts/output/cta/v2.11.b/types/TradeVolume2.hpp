#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Contains the total number of shares traded in a single transaction for an individual security (short form)
struct TradeVolume2 {

    static constexpr const char* name = "Trade Volume 2";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr TradeVolume2()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeVolume2(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of TradeVolume2 field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
