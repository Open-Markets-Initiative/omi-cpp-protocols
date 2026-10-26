#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::tops::iextp::v1_66 {

// Upper threshold price of the auction collar, if any
struct UpperAuctionCollar {

    static constexpr const char* name = "Upper Auction Collar";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;

    // default constructor
    constexpr UpperAuctionCollar()
     : value{ 0 } {}

    // constructor for UpperAuctionCollar field
    constexpr explicit UpperAuctionCollar(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of UpperAuctionCollar field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of UpperAuctionCollar field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
