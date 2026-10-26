#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// End of price range
struct PriceTo {

    static constexpr const char* name = "Price To";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr PriceTo()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PriceTo(const std::int32_t value)
     : value{ std::byteswap(value) } {}

    // get value of PriceTo field
    [[nodiscard]] std::int32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::int32_t value;
};
}
