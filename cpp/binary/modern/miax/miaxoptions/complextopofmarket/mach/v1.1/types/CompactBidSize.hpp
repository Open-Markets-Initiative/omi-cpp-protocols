#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Aggregate size at MIAX Best Bid Net Price
struct CompactBidSize {

    static constexpr const char* name = "Compact Bid Size";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr CompactBidSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CompactBidSize(const std::uint16_t value)
     : value{ value } {}

    // get value of CompactBidSize field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
