#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v1_91 {

// Denotes the Sequence Type sale condition
enum class Category3 : char {
    NotExtendedHoursOrSoldOutOfSequence = ' ', // Not Extended Hours Or Sold Out Of Sequence
    SoldLast = 'L',                            // Sold Last
    ExtendedHoursTrade = 'T',                  // Extended Hours Trade
    ExtendedHoursSold = 'U',                   // Extended Hours Sold
    SoldOutOfSequence = 'Z',                   // Sold Out Of Sequence
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Category3 value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Category3 value);

} // namespace siac::cts::output::cta::v1_91
