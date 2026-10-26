#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cme::globex::mdp3::sbe::v1_9 {

// Flag describing IOP and Open Price entries
enum class OpenCloseSettlFlag : std::uint8_t {
    DailyOpenPrice = 0,         // Daily Open Price
    IndicativeOpeningPrice = 5, // Indicative Opening Price
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OpenCloseSettlFlag value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OpenCloseSettlFlag value);

} // namespace cme::globex::mdp3::sbe::v1_9
