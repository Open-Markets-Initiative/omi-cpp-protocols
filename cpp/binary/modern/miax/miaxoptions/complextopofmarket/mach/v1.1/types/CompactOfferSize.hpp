#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Aggregate size at MIAX Best Bid Net Price
struct CompactOfferSize {

    static constexpr const char* name = "Compact Offer Size";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr CompactOfferSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CompactOfferSize(const std::uint16_t value)
     : value{ value } {}

    // get value of CompactOfferSize field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
