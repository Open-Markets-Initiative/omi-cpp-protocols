#pragma once

#include <cstddef>

namespace lseg::lse::level2mbo::gtp::v26_2 {


// The value in this field is only relevant when Trade Type is 1.
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
