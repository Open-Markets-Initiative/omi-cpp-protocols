#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Side of book for this entry.
enum class MdEntryType : char {
    Bid = '0',             // Bid
    Ask = '1',             // Ask
    Trade = '2',           // Trade
    IndexValue = '3',      // Index Value
    OpeningPrice = '4',    // Opening Price
    SettlementValue = '6', // Settlement Value
    High = '7',            // High
    Low = '8',             // Low
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MdEntryType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MdEntryType value);

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
