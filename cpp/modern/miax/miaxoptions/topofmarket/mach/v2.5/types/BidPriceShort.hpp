#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// MIAX best bid price at the time stated in Timestamp and side specified in Message Type
struct BidPriceShort {

    static constexpr const char* name = "Bid Price Short";
    static constexpr std::size_t size =  2;
    static constexpr std::size_t precision = 2;
    static constexpr double denominator = 100;
    using type = std::uint16_t;

    // default constructor
    constexpr BidPriceShort()
     : value{ 0 } {}

    // constructor for BidPriceShort field
    constexpr explicit BidPriceShort(const std::uint16_t value)
     : value{ value } {}

    // get underlying integer of BidPriceShort field
    [[nodiscard]] std::uint16_t integer() const {
        return value;
    }

    // decimal value of BidPriceShort field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint16_t value;
};
}
