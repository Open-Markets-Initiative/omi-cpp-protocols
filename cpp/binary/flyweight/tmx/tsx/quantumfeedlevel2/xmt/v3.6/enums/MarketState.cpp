// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: enums/MarketState.cpp
#include "MarketState.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

std::string_view to_string(MarketState value) {
    switch (value) {
        case MarketState::PreOpen: return "Pre Open";
        case MarketState::Opening: return "Opening";
        case MarketState::Open: return "Open";
        case MarketState::MocImbalance: return "Moc Imbalance";
        case MarketState::MocFreeze: return "Moc Freeze";
        case MarketState::CcpDetermination: return "Ccp Determination";
        case MarketState::PriceMovementExtension: return "Price Movement Extension";
        case MarketState::Closing: return "Closing";
        case MarketState::ExtendedHoursCxls: return "Extended Hours Cxls";
        case MarketState::ExtendedHoursOpen: return "Extended Hours Open";
        case MarketState::ExtendedHoursClose: return "Extended Hours Close";
        case MarketState::Closed: return "Closed";
        case MarketState::NavExClosed: return "Nav Ex Closed";
        case MarketState::NavExOrderEntry: return "Nav Ex Order Entry";
        case MarketState::NavExOrderEntryClose: return "Nav Ex Order Entry Close";
        case MarketState::NavExAmExecution: return "Nav Ex Am Execution";
        case MarketState::NavExPmExecution: return "Nav Ex Pm Execution";
        case MarketState::NavExClose: return "Nav Ex Close";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MarketState value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
