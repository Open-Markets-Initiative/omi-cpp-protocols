#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cme::globex::mdp3::sbe::v1_13 {

// Identifies the trading status applicable to the instrument or Security Group
enum class SecurityTradingStatus : std::uint8_t {
    TradingHalt = 2,             // Trading Halt
    Close = 4,                   // Close
    NewPriceIndication = 15,     // New Price Indication
    ReadyToTrade = 17,           // Ready To Trade
    NotAvailableForTrading = 18, // Not Available For Trading
    UnknownorInvalid = 20,       // Unknownor Invalid
    PreOpen = 21,                // Pre Open
    PreCross = 24,               // Pre Cross
    Cross = 25,                  // Cross
    PostClose = 26,              // Post Close
    NoChange = 103,              // No Change
    PrivateWorkup = 201,         // Private Workup
    PublicWorkup = 202,          // Public Workup
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityTradingStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityTradingStatus value);

} // namespace cme::globex::mdp3::sbe::v1_13
