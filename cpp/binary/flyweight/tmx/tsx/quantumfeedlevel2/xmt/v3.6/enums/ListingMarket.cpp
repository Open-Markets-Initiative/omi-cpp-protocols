// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: enums/ListingMarket.cpp
#include "ListingMarket.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

std::string_view to_string(ListingMarket value) {
    switch (value) {
        case ListingMarket::Tsx: return "Tsx";
        case ListingMarket::TsxVenture: return "Tsx Venture";
        case ListingMarket::TsxNaVex: return "Tsx Na Vex";
        case ListingMarket::Nasdaq: return "Nasdaq";
        case ListingMarket::Nyse: return "Nyse";
        case ListingMarket::NyseMkt: return "Nyse Mkt";
        case ListingMarket::NoMarket: return "No Market";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ListingMarket value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
