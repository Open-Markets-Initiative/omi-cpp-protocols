#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Time priority of this order within the order book.
struct OrderBookPriority {

    static constexpr const char* name = "Order Book Priority";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr OrderBookPriority()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OrderBookPriority(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of OrderBookPriority field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
