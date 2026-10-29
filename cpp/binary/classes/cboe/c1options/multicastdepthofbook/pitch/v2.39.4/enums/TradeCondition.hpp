#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// Options Only (byte not sent in Equities) (Space): Normal Trade S: Spread trade
enum class TradeCondition : char {
    NormalTrade = ' ', // Normal Trade
    SpreadTrade = 'S', // Spread Trade
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradeCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradeCondition value);

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
