#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jnx::jnxequities::pts::itch::v1_7 {

// Price tick size table identifier.
struct PriceTickSizeTableId {

    static constexpr const char* name = "Price Tick Size Table Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr PriceTickSizeTableId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PriceTickSizeTableId(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of PriceTickSizeTableId field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
