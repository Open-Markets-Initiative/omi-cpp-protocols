#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace databento::marketdata::normalized::dbn::v2 {

// The type of status change
enum class StatusAction : std::uint16_t {
    None = 0,                    // None
    PreOpen = 1,                 // Pre Open
    PreCross = 2,                // Pre Cross
    Quoting = 3,                 // Quoting
    Cross = 4,                   // Cross
    Rotation = 5,                // Rotation
    NewPriceIndication = 6,      // New Price Indication
    Trading = 7,                 // Trading
    Halt = 8,                    // Halt
    Pause = 9,                   // Pause
    Suspend = 10,                // Suspend
    PreClose = 11,               // Pre Close
    Close = 12,                  // Close
    PostClose = 13,              // Post Close
    SsrChange = 14,              // Ssr Change
    NotAvailableForTrading = 15, // Not Available For Trading
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(StatusAction value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, StatusAction value);

} // namespace databento::marketdata::normalized::dbn::v2
