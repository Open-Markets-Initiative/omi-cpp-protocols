#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// Unique code for feed
enum class FeedIdentifier : char {
    Aspen = 'A',        // Aspen
    AspenVert = 'V',    // Aspen Vert
    Midpoint = 'M',     // Midpoint
    AspenUat = 'B',     // Aspen Uat
    AspenVertUat = 'W', // Aspen Vert Uat
    MidpointUat = 'N',  // Midpoint Uat
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(FeedIdentifier value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, FeedIdentifier value);

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
