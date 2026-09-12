#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace iex::iexequities::deepplus::snap::v1_05 {

// Detail of the Reg. SHO short sale price test restriction status
enum class Detail : char {
    NoPriceTestInPlace = ' ',                                                         // No Price Test In Place
    ShortSalePriceTestRestrictionInEffectDueToAnIntradayPriceDropInTheSecurity = 'A', // Short Sale Price Test Restriction In Effect Due To An Intraday Price Drop In The Security
    ShortSalePriceTestRestrictionRemainsInEffectFromPriorDay = 'C',                   // Short Sale Price Test Restriction Remains In Effect From Prior Day
    ShortSalePriceTestRestrictionDeactivated = 'D',                                   // Short Sale Price Test Restriction Deactivated
    NotAvailable = 'N',                                                               // Not Available
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Detail value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Detail value);

} // namespace iex::iexequities::deepplus::snap::v1_05
