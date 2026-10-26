#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {


// Current trading status of the security.
struct TradingStatus {

    static constexpr auto name = "Trading Status";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr TradingStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradingStatus(const std::uint8_t &value)
     : value{ value } {}

    // get value of TradingStatus field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
