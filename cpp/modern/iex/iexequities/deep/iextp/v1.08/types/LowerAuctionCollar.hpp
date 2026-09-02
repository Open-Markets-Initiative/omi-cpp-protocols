#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::deep::iextp::v1_08 {

// Lower threshold price of the auction collar, if any
struct LowerAuctionCollar {

    static constexpr const char* name = "Lower Auction Collar";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;

    // default constructor
    constexpr LowerAuctionCollar()
     : value{ 0 } {}

    // constructor for LowerAuctionCollar field
    constexpr explicit LowerAuctionCollar(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of LowerAuctionCollar field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of LowerAuctionCollar field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
