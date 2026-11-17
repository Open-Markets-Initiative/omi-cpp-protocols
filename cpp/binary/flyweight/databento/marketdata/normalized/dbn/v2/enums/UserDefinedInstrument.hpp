// Databento.MarketData.Normalized.Dbn.v2: enums/UserDefinedInstrument.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace databento::marketdata::normalized::dbn::v2 {

// Indicates if the instrument is user defined
enum class UserDefinedInstrument : char {
    No = 'N',  // No
    Yes = 'Y', // Yes
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(UserDefinedInstrument value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, UserDefinedInstrument value);

} // namespace databento::marketdata::normalized::dbn::v2
