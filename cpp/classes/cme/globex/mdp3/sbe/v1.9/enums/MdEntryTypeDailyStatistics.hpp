#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cme::globex::mdp3::sbe::v1_9 {

// Market Data entry type
enum class MdEntryTypeDailyStatistics : char {
    SettlementPrice = '6', // Settlement Price
    ClearedVolume = 'B',   // Cleared Volume
    OpenInterest = 'C',    // Open Interest
    FixingPrice = 'W',     // Fixing Price
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MdEntryTypeDailyStatistics value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MdEntryTypeDailyStatistics value);

} // namespace cme::globex::mdp3::sbe::v1_9
