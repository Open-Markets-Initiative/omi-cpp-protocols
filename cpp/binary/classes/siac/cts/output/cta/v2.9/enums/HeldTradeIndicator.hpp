#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_9 {

// The Held Trade Indicator reflects whether this trade qualifies for the Participant or
// Consolidated Last Price at the time it is disseminated
enum class HeldTradeIndicator : char {
    NotApplicable = ' ',                                                 // Not Applicable
    CannotBeUsedAsALastSaleForBothParticipantAndConsolidatedBasis = 'A', // Cannot Be Used As A Last Sale For Both Participant And Consolidated Basis
    CanBeUsedAsALastSaleForParticipantButNotConsolidatedBasis = 'B',     // Can Be Used As A Last Sale For Participant But Not Consolidated Basis
    CanBeUsedAsALastSaleForParticipantAndConsolidatedBasis = 'C',        // Can Be Used As A Last Sale For Participant And Consolidated Basis
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(HeldTradeIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, HeldTradeIndicator value);

} // namespace siac::cts::output::cta::v2_9
