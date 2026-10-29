#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_9 {

// Contains the total number of trade transactions executed from a Market Center
struct TotalTrades {

    static constexpr const char* name = "Total Trades";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TotalTrades()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TotalTrades(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of TotalTrades field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
