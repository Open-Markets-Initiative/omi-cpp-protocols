// Databento.MarketData.Normalized.Dbn.v1: enums/UpdateAction.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace databento::marketdata::normalized::dbn::v1 {

// Indicates if the statistic is newly added or deleted
enum class UpdateAction : std::uint8_t {
    New = 1,    // New
    Delete = 2, // Delete
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(UpdateAction value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, UpdateAction value);

} // namespace databento::marketdata::normalized::dbn::v1
