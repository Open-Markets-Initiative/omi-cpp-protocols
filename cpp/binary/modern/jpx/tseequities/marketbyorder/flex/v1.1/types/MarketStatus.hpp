#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {


// Indicates market status
struct MarketStatus {

    static constexpr auto name = "Market Status";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr MarketStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketStatus(const std::uint8_t &value)
     : value{ value } {}

    // get value of MarketStatus field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
