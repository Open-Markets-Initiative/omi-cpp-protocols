// Databento.MarketData.Normalized.Dbn.v1: enums/SecurityUpdateAction.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace databento::marketdata::normalized::dbn::v1 {

// Indicates if the instrument definition has been added, modified, or deleted
enum class SecurityUpdateAction : char {
    Add = 'A',     // Add
    Delete = 'D',  // Delete
    Modify = 'M',  // Modify
    Invalid = '~', // Invalid
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityUpdateAction value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityUpdateAction value);

} // namespace databento::marketdata::normalized::dbn::v1
