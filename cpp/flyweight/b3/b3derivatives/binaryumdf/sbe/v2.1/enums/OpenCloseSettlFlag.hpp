#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

// openCloseSettlFlag
enum class OpenCloseSettlFlag : std::uint8_t {
    Daily = 0,                        // Daily
    Session = 1,                      // Session
    ExpectedEntry = 3,                // Expected Entry
    EntryFromPreviousBusinessDay = 4, // Entry From Previous Business Day
    TheoreticalPrice = 5,             // Theoretical Price
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OpenCloseSettlFlag value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OpenCloseSettlFlag value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_1
