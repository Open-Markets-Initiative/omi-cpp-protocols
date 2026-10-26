#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::tops::iextp::v1_66 {

// Clearing price using orders on the Auction Book
struct AuctionBookClearingPrice {

    static constexpr const char* name = "Auction Book Clearing Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;

    // default constructor
    constexpr AuctionBookClearingPrice()
     : value{ 0 } {}

    // constructor for AuctionBookClearingPrice field
    constexpr explicit AuctionBookClearingPrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of AuctionBookClearingPrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of AuctionBookClearingPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
