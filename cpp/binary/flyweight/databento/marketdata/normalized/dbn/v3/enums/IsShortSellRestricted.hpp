// Databento.MarketData.Normalized.Dbn.v3: enums/IsShortSellRestricted.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace databento::marketdata::normalized::dbn::v3 {

// The state of short sell restrictions for the instrument
enum class IsShortSellRestricted : char {
    NotAvailable = '~', // Not Available
    No = 'N',           // No
    Yes = 'Y',          // Yes
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(IsShortSellRestricted value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, IsShortSellRestricted value);

} // namespace databento::marketdata::normalized::dbn::v3
