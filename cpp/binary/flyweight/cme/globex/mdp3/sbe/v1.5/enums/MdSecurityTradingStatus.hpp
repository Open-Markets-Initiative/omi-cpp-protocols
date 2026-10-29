#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cme::globex::mdp3::sbe::v1_5 {

// Identifies the current state of the instrument. In Security Definition message this tag is
// available in the Instrument Replay feed only
enum class MdSecurityTradingStatus : std::uint8_t {
    TradingHalt = 2,             // Trading Halt
    Close = 4,                   // Close
    NewPriceIndication = 15,     // New Price Indication
    ReadyToTrade = 17,           // Ready To Trade
    NotAvailableForTrading = 18, // Not Available For Trading
    UnknownOrInvalid = 20,       // Unknown Or Invalid
    PreOpen = 21,                // Pre Open
    PreCross = 24,               // Pre Cross
    Cross = 25,                  // Cross
    PostClose = 26,              // Post Close
    NoChange = 103,              // No Change
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MdSecurityTradingStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MdSecurityTradingStatus value);

} // namespace cme::globex::mdp3::sbe::v1_5
