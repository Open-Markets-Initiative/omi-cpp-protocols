#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_11_b {

// Reflects whether a held trade qualifies for the Participant or Consolidated Last Price at
// the time it is disseminated
enum class HeldTradeIndicator : char {
    HeldTradeIndicatorNotApplicable = ' ',                   // Held Trade Indicator Not Applicable
    HeldTradeNotALastSaleForParticipantOrConsolidated = 'A', // Held Trade Not A Last Sale For Participant Or Consolidated
    HeldTradeLastSaleForParticipantButNotConsolidated = 'B', // Held Trade Last Sale For Participant But Not Consolidated
    HeldTradeLastSaleForParticipantAndConsolidated = 'C',    // Held Trade Last Sale For Participant And Consolidated
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(HeldTradeIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, HeldTradeIndicator value);

} // namespace siac::cts::output::cta::v2_11_b
