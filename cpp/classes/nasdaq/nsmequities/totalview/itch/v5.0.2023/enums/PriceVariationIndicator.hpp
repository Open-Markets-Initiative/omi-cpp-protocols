#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Indicates the absolute value of the percentage of deviation of the Near Indicative Clearing
// Price to the nearest Current Reference Price
enum class PriceVariationIndicator : char {
    LessThan1Percent = 'L',  // Less Than 1 Percent
    LessThan2Percent = '1',  // Less Than 2 Percent
    LessThan3Percent = '2',  // Less Than 3 Percent
    LessThan4Percent = '3',  // Less Than 4 Percent
    LessThan5Percent = '4',  // Less Than 5 Percent
    LessThan6Percent = '5',  // Less Than 6 Percent
    LessThan7Percent = '6',  // Less Than 7 Percent
    LessThan8Percent = '7',  // Less Than 8 Percent
    LessThan9Percent = '8',  // Less Than 9 Percent
    LessThan10Percent = '9', // Less Than 10 Percent
    LessThan20Percent = 'A', // Less Than 20 Percent
    LessThan30Percent = 'B', // Less Than 30 Percent
    MoreThan30Percent = 'C', // More Than 30 Percent
    NotAvailable = ' ',      // Not Available
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PriceVariationIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PriceVariationIndicator value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
