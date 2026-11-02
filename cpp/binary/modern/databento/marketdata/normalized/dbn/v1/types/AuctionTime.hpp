#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {


// Reserved for future use
struct AuctionTime {

    static constexpr auto name = "Auction Time";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;
static const type no_value = 18446744073709551615ULL;

    // default constructor
    constexpr AuctionTime()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AuctionTime(const std::uint64_t &value)
     : value{ value } {}

    // get value of AuctionTime field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
