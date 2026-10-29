#pragma once

#include <cstddef>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {


// Top of Strategy Market Quote Conditions
struct OfferCondition {

    static constexpr auto name = "Offer Condition";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OfferCondition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OfferCondition(const char &value)
     : value{ value } {}

    // get value of OfferCondition field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
