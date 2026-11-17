// Databento.MarketData.Normalized.Dbn.v2: enums/Action.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace databento::marketdata::normalized::dbn::v2 {

// The event action
enum class Action : char {
    Add = 'A',    // Add
    Cancel = 'C', // Cancel
    Fill = 'F',   // Fill
    Modify = 'M', // Modify
    None = 'N',   // None
    Clear = 'R',  // Clear
    Trade = 'T',  // Trade
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Action value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Action value);

} // namespace databento::marketdata::normalized::dbn::v2
