#pragma once

#include <cstddef>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {


// ‘S’ = Start ‘U’ = Auction Update ‘E’ = End of Auction
struct AuctionEvent {

    static constexpr auto name = "Auction Event";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr AuctionEvent()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AuctionEvent(const char &value)
     : value{ value } {}

    // get value of AuctionEvent field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
