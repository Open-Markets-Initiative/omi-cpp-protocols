#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Aggregate size at MIAX best bid Price at the time stated in Timestamp and side specified in Message Type
struct BidSizeShort {

    static constexpr const char* name = "Bid Size Short";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr BidSizeShort()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BidSizeShort(const std::uint16_t value)
     : value{ value } {}

    // get value of BidSizeShort field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
