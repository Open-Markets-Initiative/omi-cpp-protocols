#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

// Code identifying this message type
enum class MessageType : char {
    SystemEventMessage = 'S',            // System Event Message
    StockDirectoryMessage = 'R',         // Stock Directory Message
    StockTradingActionMessage = 'H',     // Stock Trading Action Message
    RegShoRestrictionMessage = 'Y',      // Reg Sho Restriction Message
    MwcbDeclineLevelMessage = 'V',       // Mwcb Decline Level Message
    MwcbBreachMessage = 'W',             // Mwcb Breach Message
    OperationalHaltMessage = 'h',        // Operational Halt Message
    BboQuotationMessage = 'Q',           // Bbo Quotation Message
    PriceImprovementMessage = 'N',       // Price Improvement Message
    IpoQuotingPeriodUpdateMessage = 'K', // Ipo Quoting Period Update Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
