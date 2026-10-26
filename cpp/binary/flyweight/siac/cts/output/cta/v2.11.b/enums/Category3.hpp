#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_11_b {

// Extended Hours / Sequence Type
enum class Category3 : char {
    NotExtendedHoursOrSoldOutOfSequence = ' ', // Not Extended Hours Or Sold Out Of Sequence
    SoldLastLateReporting = 'L',               // Sold Last Late Reporting
    MarketCenterOpeningTrade = 'O',            // Market Center Opening Trade
    ExtendedHoursTrade = 'T',                  // Extended Hours Trade
    ExtendedHoursSoldOutOfSequence = 'U',      // Extended Hours Sold Out Of Sequence
    SoldOutOfSequence = 'Z',                   // Sold Out Of Sequence
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Category3 value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Category3 value);

} // namespace siac::cts::output::cta::v2_11_b
