#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v1_91 {


// Identifies whether or not a Short Sale Restriction is in effect for a security
struct ShortSaleRestrictionIndicator {

    static constexpr auto name = "Short Sale Restriction Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ShortSaleRestrictionIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ShortSaleRestrictionIndicator(const char &value)
     : value{ value } {}

    // get value of ShortSaleRestrictionIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
