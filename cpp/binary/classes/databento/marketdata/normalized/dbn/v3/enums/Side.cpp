// Databento.MarketData.Normalized.Dbn.v3: enums/Side.cpp
#include "Side.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

std::string_view to_string(Side value) {
    switch (value) {
        case Side::Ask: return "Ask";
        case Side::Bid: return "Bid";
        case Side::None: return "None";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Side value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace databento::marketdata::normalized::dbn::v3
