#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Indicates the price of the upper auction collar threshold
struct UpperAuctionCollarPrice {

    static constexpr const char* name = "Upper Auction Collar Price";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr UpperAuctionCollarPrice()
     : value{ 0 } {}

    // constructor for UpperAuctionCollarPrice field
    constexpr explicit UpperAuctionCollarPrice(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of UpperAuctionCollarPrice field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of UpperAuctionCollarPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
