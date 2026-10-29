#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Aggregate size at MIAX Best Bid Net Price
struct WideOfferSize {

    static constexpr const char* name = "Wide Offer Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr WideOfferSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit WideOfferSize(const std::uint32_t value)
     : value{ value } {}

    // get value of WideOfferSize field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
