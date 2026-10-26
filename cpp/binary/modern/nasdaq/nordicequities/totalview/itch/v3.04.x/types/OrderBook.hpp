#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Order book id
struct OrderBook {

    static constexpr const char* name = "Order Book";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr OrderBook()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OrderBook(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of OrderBook field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
