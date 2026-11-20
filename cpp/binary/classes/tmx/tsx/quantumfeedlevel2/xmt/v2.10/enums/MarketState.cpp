// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: enums/MarketState.cpp
#include "MarketState.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

std::string_view to_string(MarketState value) {
    switch (value) {
        case MarketState::PreOpen: return "Pre Open";
        case MarketState::Opening: return "Opening";
        case MarketState::Open: return "Open";
        case MarketState::MocImbalance: return "Moc Imbalance";
        case MarketState::CcpDetermination: return "Ccp Determination";
        case MarketState::PriceMovementExtension: return "Price Movement Extension";
        case MarketState::Closing: return "Closing";
        case MarketState::ExtendedHoursCxls: return "Extended Hours Cxls";
        case MarketState::ExtendedHoursOpen: return "Extended Hours Open";
        case MarketState::ExtendedHoursClose: return "Extended Hours Close";
        case MarketState::Closed: return "Closed";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MarketState value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
