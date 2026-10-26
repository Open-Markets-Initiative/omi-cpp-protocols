#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Indicates the pricing method in place when the execution occurred
enum class AdoptedPricingMethod : std::uint8_t {
    ItayoseMethod = 1,  // Itayose Method
    QuoteDisplayed = 2, // Quote Displayed
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AdoptedPricingMethod value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AdoptedPricingMethod value);

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
