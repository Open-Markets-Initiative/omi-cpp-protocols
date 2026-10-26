#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Reference price used to set the auction collars
struct AuctionCollarReferencePrice {

    static constexpr const char* name = "Auction Collar Reference Price";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr AuctionCollarReferencePrice()
     : value{ 0 } {}

    // constructor for AuctionCollarReferencePrice field
    constexpr explicit AuctionCollarReferencePrice(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of AuctionCollarReferencePrice field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of AuctionCollarReferencePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
