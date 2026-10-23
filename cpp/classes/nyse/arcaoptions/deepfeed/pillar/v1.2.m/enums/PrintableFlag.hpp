#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// Indicates whether trade is included in total volume.
enum class PrintableFlag : std::uint8_t {
    TradeNotIncludedInTotalVolume = 0, // Trade Not Included In Total Volume
    TradeIncludedInTotalVolume = 1,    // Trade Included In Total Volume
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PrintableFlag value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PrintableFlag value);

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
