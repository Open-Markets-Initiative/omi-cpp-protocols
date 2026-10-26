#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Derivative strike price
struct StrikePrice {

    static constexpr const char* name = "Strike Price";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr StrikePrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StrikePrice(const std::int32_t value)
     : value{ std::byteswap(value) } {}

    // get value of StrikePrice field
    [[nodiscard]] std::int32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::int32_t value;
};
}
