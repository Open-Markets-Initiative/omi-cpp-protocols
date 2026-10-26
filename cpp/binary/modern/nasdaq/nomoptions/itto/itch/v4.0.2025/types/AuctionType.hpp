#pragma once

#include <cstddef>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {


// Type of Auction:
struct AuctionType {

    static constexpr auto name = "Auction Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr AuctionType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AuctionType(const char &value)
     : value{ value } {}

    // get value of AuctionType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
