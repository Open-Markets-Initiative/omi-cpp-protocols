#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace bse::bseindia::eobi::fbe::v1_4 {

// Indicates whether a synthetic match is occured.
enum class TradeCondition : std::uint8_t {
    ImpliedTrade = 1, // Implied Trade
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradeCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradeCondition value);

} // namespace bse::bseindia::eobi::fbe::v1_4
