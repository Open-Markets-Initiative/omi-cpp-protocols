#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Indicates the number of extensions to the Reopening Auction
struct AuctionCollarExtension {

    static constexpr const char* name = "Auction Collar Extension";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr AuctionCollarExtension()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AuctionCollarExtension(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of AuctionCollarExtension field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
