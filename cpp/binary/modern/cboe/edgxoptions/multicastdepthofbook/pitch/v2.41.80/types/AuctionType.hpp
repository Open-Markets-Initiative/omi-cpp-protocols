#pragma once

#include <cstddef>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {


// G = GTH Opening (C1 Only), O = RTH Opening (C1 Only), H = Halt Re-Opening, V = Volatility Opening.
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
