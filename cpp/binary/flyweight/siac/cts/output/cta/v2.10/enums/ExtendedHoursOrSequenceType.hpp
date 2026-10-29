#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_10 {

// Category 3: Extended Hours Or Sequence Type
enum class ExtendedHoursOrSequenceType : char {
    NotExtendedHoursOrSoldOutOfSequence = ' ', // Not Extended Hours Or Sold Out Of Sequence
    SoldLast = 'L',                            // Sold Last
    ExtendedHoursTrade = 'T',                  // Extended Hours Trade
    ExtendedHoursSold = 'U',                   // Extended Hours Sold
    SoldOutOfSequence = 'Z',                   // Sold Out Of Sequence
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ExtendedHoursOrSequenceType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ExtendedHoursOrSequenceType value);

} // namespace siac::cts::output::cta::v2_10
