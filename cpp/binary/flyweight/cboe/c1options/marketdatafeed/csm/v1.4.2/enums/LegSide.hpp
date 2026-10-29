#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

enum class LegSide : char {
    BuyBid = 'B',  // Buy Bid
    SellAsk = 'S', // Sell Ask
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LegSide value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LegSide value);

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
