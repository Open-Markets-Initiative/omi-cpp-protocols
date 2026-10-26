#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::deep::iextp::v1_06 {

// Projected time of the auction match
struct ScheduledAuctionTime {

    static constexpr const char* name = "Scheduled Auction Time";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ScheduledAuctionTime()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ScheduledAuctionTime(const std::uint32_t value)
     : value{ value } {}

    // get value of ScheduledAuctionTime field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
