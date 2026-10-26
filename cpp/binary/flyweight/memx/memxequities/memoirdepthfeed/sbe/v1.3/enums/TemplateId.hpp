#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// T8 Identifier of the message template
enum class TemplateId : std::uint8_t {
    InstrumentDirectoryMessage = 1,   // Instrument Directory Message
    RegShoRestrictionMessage = 2,     // Reg Sho Restriction Message
    SecurityTradingStatusMessage = 3, // Security Trading Status Message
    TradingSessionStatusMessage = 5,  // Trading Session Status Message
    OrderAddedMessage = 10,           // Order Added Message
    OrderDeletedMessage = 11,         // Order Deleted Message
    OrderReducedMessage = 12,         // Order Reduced Message
    OrderExecutedMessage = 13,        // Order Executed Message
    TradeMessage = 14,                // Trade Message
    BrokenTradeMessage = 15,          // Broken Trade Message
    CorrectedTradeMessage = 16,       // Corrected Trade Message
    ClearBookMessage = 18,            // Clear Book Message
    SnapshotCompleteMessage = 100,    // Snapshot Complete Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TemplateId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TemplateId value);

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
