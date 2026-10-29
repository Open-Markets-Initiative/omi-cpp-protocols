#include "TradeCond4.hpp"

namespace nyse::amexequities::integratedfeed::pillar::v2_5_g {

std::string_view to_string(TradeCond4 value) {
    switch (value) {
        case TradeCond4::Na: return "Na";
        case TradeCond4::OddLotTrade: return "Odd Lot Trade";
        case TradeCond4::ContingentTradeTexasOnly: return "Contingent Trade Texas Only";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeCond4 value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::amexequities::integratedfeed::pillar::v2_5_g
