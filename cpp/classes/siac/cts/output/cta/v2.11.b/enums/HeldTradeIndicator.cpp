#include "HeldTradeIndicator.hpp"

namespace siac::cts::output::cta::v2_11_b {

std::string_view to_string(HeldTradeIndicator value) {
    switch (value) {
        case HeldTradeIndicator::HeldTradeIndicatorNotApplicable: return "Held Trade Indicator Not Applicable";
        case HeldTradeIndicator::HeldTradeNotALastSaleForParticipantOrConsolidated: return "Held Trade Not A Last Sale For Participant Or Consolidated";
        case HeldTradeIndicator::HeldTradeLastSaleForParticipantButNotConsolidated: return "Held Trade Last Sale For Participant But Not Consolidated";
        case HeldTradeIndicator::HeldTradeLastSaleForParticipantAndConsolidated: return "Held Trade Last Sale For Participant And Consolidated";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, HeldTradeIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_11_b
