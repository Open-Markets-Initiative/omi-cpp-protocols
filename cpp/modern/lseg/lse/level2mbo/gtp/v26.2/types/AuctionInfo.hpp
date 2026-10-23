#pragma once

#include <cstddef>

namespace lseg::lse::level2mbo::gtp::v26_2 {


// Populated if the Statistic Type is 1.
struct AuctionInfo {

    static constexpr auto name = "Auction Info";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr AuctionInfo()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AuctionInfo(const char &value)
     : value{ value } {}

    // get value of AuctionInfo field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
