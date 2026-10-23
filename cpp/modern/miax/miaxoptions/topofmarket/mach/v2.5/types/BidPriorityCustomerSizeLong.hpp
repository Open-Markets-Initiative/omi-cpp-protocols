#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Aggregate size of Priority Customer contracts at the MIAX Best Bid Price
struct BidPriorityCustomerSizeLong {

    static constexpr const char* name = "Bid Priority Customer Size Long";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr BidPriorityCustomerSizeLong()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BidPriorityCustomerSizeLong(const std::uint32_t value)
     : value{ value } {}

    // get value of BidPriorityCustomerSizeLong field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
