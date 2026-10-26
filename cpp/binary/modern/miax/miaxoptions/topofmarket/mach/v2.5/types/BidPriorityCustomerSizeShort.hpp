#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Aggregate size of Priority Customer contracts at the MIAX Best Bid Price
struct BidPriorityCustomerSizeShort {

    static constexpr const char* name = "Bid Priority Customer Size Short";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr BidPriorityCustomerSizeShort()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BidPriorityCustomerSizeShort(const std::uint16_t value)
     : value{ value } {}

    // get value of BidPriorityCustomerSizeShort field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
