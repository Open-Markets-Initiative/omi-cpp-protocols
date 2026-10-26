#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Indicates method of pricing or status of quote display after the tag is delivered
enum class PricingMethod : std::uint8_t {
    ItayoseMethod = 1,                     // Itayose Method
    ZarabaMethod = 2,                      // Zaraba Method
    SellSpecialQuoteDisplayed = 3,         // Sell Special Quote Displayed
    BuySpecialQuoteDisplayed = 4,          // Buy Special Quote Displayed
    SellSequentialTradeQuoteDisplayed = 5, // Sell Sequential Trade Quote Displayed
    BuySequentialTradeQuoteDisplayed = 6,  // Buy Sequential Trade Quote Displayed
    OtherThanTheAbove = 0,                 // Other Than The Above
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PricingMethod value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PricingMethod value);

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
