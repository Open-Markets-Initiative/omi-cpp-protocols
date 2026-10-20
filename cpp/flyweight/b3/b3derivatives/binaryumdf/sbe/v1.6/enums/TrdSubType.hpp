#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// trdSubType
enum class TrdSubType : std::uint8_t {
    MultiAssetTrade = 101, // Multi Asset Trade
    LegTrade = 102,        // Leg Trade
    MidpointTrade = 103,   // Midpoint Trade
    BlockBookTrade = 104,  // Block Book Trade
    RfqTrade = 105,        // Rfq Trade
    RlpTrade = 106,        // Rlp Trade
    TacTrade = 107,        // Tac Trade
    TaaTrade = 108,        // Taa Trade
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TrdSubType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TrdSubType value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
