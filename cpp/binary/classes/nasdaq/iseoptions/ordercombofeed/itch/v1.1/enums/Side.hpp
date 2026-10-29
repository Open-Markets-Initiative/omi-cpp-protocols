#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// ‘B’ = Bid ‘A’ = Offer (Ask) ‘ ’ (blank) = not set (hidden)
enum class Side : char {
    Bid = 'B',      // Bid
    OfferAsk = 'A', // Offer Ask
    Hidden = ' ',   // Hidden
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Side value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Side value);

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
