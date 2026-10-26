#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// Original short sale restriction indicator
struct OriginalShortSaleRestrictionIndicator {

    static constexpr auto name = "Original Short Sale Restriction Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OriginalShortSaleRestrictionIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OriginalShortSaleRestrictionIndicator(const char &value)
     : value{ value } {}

    // get value of OriginalShortSaleRestrictionIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
