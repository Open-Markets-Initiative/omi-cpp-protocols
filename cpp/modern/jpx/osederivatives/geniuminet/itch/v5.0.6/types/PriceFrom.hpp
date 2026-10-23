#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Start of price range
struct PriceFrom {

    static constexpr const char* name = "Price From";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr PriceFrom()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PriceFrom(const std::int32_t value)
     : value{ std::byteswap(value) } {}

    // get value of PriceFrom field
    [[nodiscard]] std::int32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::int32_t value;
};
}
