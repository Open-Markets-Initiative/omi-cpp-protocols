#pragma once

#include <cstddef>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {


// The Currency in which the Product settles
struct SettlementCurrency {

    static constexpr auto name = "Settlement Currency";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SettlementCurrency()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SettlementCurrency(const char &value)
     : value{ value } {}

    // get value of SettlementCurrency field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
