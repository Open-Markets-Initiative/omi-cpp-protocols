#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// Corrected short sale restriction indicator
struct CorrectedShortSaleRestrictionIndicator {

    static constexpr auto name = "Corrected Short Sale Restriction Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr CorrectedShortSaleRestrictionIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CorrectedShortSaleRestrictionIndicator(const char &value)
     : value{ value } {}

    // get value of CorrectedShortSaleRestrictionIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
