// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: enums/MarketState.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

// Indicates The Current Market State
enum class MarketState : char {
    PreOpen = 'P',                // Pre Open
    Opening = 'O',                // Opening
    Open = 'S',                   // Open
    MocImbalance = 'M',           // Moc Imbalance
    MocFreeze = 'T',              // Moc Freeze
    CcpDetermination = 'A',       // Ccp Determination
    PriceMovementExtension = 'E', // Price Movement Extension
    Closing = 'L',                // Closing
    ExtendedHoursCxls = 'N',      // Extended Hours Cxls
    ExtendedHoursOpen = 'R',      // Extended Hours Open
    ExtendedHoursClose = 'F',     // Extended Hours Close
    Closed = 'C',                 // Closed
    NavExClosed = 'J',            // Nav Ex Closed
    NavExOrderEntry = 'G',        // Nav Ex Order Entry
    NavExOrderEntryClose = 'H',   // Nav Ex Order Entry Close
    NavExAmExecution = 'K',       // Nav Ex Am Execution
    NavExPmExecution = 'X',       // Nav Ex Pm Execution
    NavExClose = 'Y',             // Nav Ex Close
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MarketState value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MarketState value);

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
