#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Indicates which Limit Up / Limit Down price band calculation parameter is to be used for the
// instrument
enum class LuldReferencePriceTier : char {
    Tier1 = '1',        // Tier 1
    Tier2 = '2',        // Tier 2
    NotAvailable = ' ', // Not Available
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LuldReferencePriceTier value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LuldReferencePriceTier value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
