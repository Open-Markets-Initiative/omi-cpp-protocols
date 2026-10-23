#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// Uniquely identifies the Auction for the trading day.
struct AuctionId {

    static constexpr const char* name = "Auction Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr AuctionId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AuctionId(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of AuctionId field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
