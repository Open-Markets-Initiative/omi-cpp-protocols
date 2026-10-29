#include "TradeCond4.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

std::string_view to_string(TradeCond4 value) {
    switch (value) {
        case TradeCond4::Na: return "Na";
        case TradeCond4::OddLotTrade: return "Odd Lot Trade";
        case TradeCond4::OfficialClosingPrice: return "Official Closing Price";
        case TradeCond4::OfficialOpenPrice: return "Official Open Price";
        case TradeCond4::ContingentTradeTrfOrTexasOnly: return "Contingent Trade Trf Or Texas Only";
        case TradeCond4::PriorReferencePriceTrfOnly: return "Prior Reference Price Trf Only";
        case TradeCond4::WeightedAveragePriceTrfOnly: return "Weighted Average Price Trf Only";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeCond4 value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::nationalequities::trades::pillar::v2_6
