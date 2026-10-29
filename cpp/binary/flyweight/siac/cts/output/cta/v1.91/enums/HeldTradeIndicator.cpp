#include "HeldTradeIndicator.hpp"

namespace siac::cts::output::cta::v1_91 {

std::string_view to_string(HeldTradeIndicator value) {
    switch (value) {
        case HeldTradeIndicator::NotApplicable: return "Not Applicable";
        case HeldTradeIndicator::CannotBeUsedAsALastSaleForBothParticipantAndConsolidatedBasis: return "Cannot Be Used As A Last Sale For Both Participant And Consolidated Basis";
        case HeldTradeIndicator::CanBeUsedAsALastSaleForParticipantButNotConsolidatedBasis: return "Can Be Used As A Last Sale For Participant But Not Consolidated Basis";
        case HeldTradeIndicator::CanBeUsedAsALastSaleForParticipantAndConsolidatedBasis: return "Can Be Used As A Last Sale For Participant And Consolidated Basis";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, HeldTradeIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v1_91
