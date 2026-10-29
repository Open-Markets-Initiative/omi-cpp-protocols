#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::ntxequities::totalview::itch::v5_0 {

// Indicates which Limit Up / Limit Down price band calculation parameter is to be used for the
// instrument.
enum class LuldReferencePriceTier : char {
    Tier1NmsStocksAndSelectEtPs = '1', // Tier 1 Nms Stocks And Select Et Ps
    Tier2NmsStocks = '2',              // Tier 2 Nms Stocks
    NotAvailable = ' ',                // Not Available
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LuldReferencePriceTier value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LuldReferencePriceTier value);

} // namespace nasdaq::ntxequities::totalview::itch::v5_0
