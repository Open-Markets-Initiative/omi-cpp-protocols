#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// O = Would open, Q = Need quote to open, B = Need more buyers (C1 Only), S = Need more
// sellers (C1 Only), C = Crossed Composite Market.
enum class OpeningCondition : char {
    WouldOpen = 'O',              // Would Open
    NeedQuoteToOpen = 'Q',        // Need Quote To Open
    NeedMoreBuyers = 'B',         // Need More Buyers
    NeedMoreSellers = 'S',        // Need More Sellers
    CrossedCompositeMarket = 'C', // Crossed Composite Market
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OpeningCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OpeningCondition value);

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
