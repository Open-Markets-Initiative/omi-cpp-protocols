#pragma once

#include <cstddef>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {


// Actual or Theoretical Settlement Price Indicator
struct SettlementPriceTypeCalcMethod {

    static constexpr auto name = "Settlement Price Type Calc Method";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SettlementPriceTypeCalcMethod()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SettlementPriceTypeCalcMethod(const char &value)
     : value{ value } {}

    // get value of SettlementPriceTypeCalcMethod field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
