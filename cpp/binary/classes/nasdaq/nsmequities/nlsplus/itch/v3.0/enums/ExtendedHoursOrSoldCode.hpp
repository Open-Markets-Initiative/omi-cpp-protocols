#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Used for Extended Hours or Sold codes
enum class ExtendedHoursOrSoldCode : char {
    ExtendedHoursTrade = 'T',             // Extended Hours Trade
    ExtendedHoursTradeReportedLate = 'U', // Extended Hours Trade Reported Late
    SoldLast = 'L',                       // Sold Last
    SoldOutOfSequence = 'Z',              // Sold Out Of Sequence
    NotApplicable = ' ',                  // Not Applicable
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ExtendedHoursOrSoldCode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ExtendedHoursOrSoldCode value);

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
