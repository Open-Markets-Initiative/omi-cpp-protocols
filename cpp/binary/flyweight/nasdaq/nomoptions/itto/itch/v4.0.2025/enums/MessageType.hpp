#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// Code identifying this message type
enum class MessageType : char {
    SystemEventMessage = 'S',                 // System Event Message
    OptionsDirectoryMessage = 'R',            // Options Directory Message
    TradingActionMessage = 'H',               // Trading Action Message
    SecurityOpenMessage = 'O',                // Security Open Message
    AddOrderMessageShortMessageForm = 'a',    // Add Order Message Short Message Form
    AddOrderMessageLongFormMessage = 'A',     // Add Order Message Long Form Message
    AddQuoteMessageShortFormMessage = 'j',    // Add Quote Message Short Form Message
    AddQuoteMessageLongFormMessage = 'J',     // Add Quote Message Long Form Message
    SingleSideExecutedMessage = 'E',          // Single Side Executed Message
    SingleSideExecutedWithPriceMessage = 'C', // Single Side Executed With Price Message
    OrderCancelMessage = 'X',                 // Order Cancel Message
    SingleSideReplaceMessageShortForm = 'u',  // Single Side Replace Message Short Form
    SingleSideReplaceMessageLongForm = 'U',   // Single Side Replace Message Long Form
    SingleSideDeleteMessage = 'D',            // Single Side Delete Message
    SingleSideChangeMessage = 'G',            // Single Side Change Message
    QuoteReplaceMessageShortForm = 'k',       // Quote Replace Message Short Form
    QuoteReplaceMessageLongForm = 'K',        // Quote Replace Message Long Form
    QuoteDeleteMessage = 'Y',                 // Quote Delete Message
    OptionsTradeMessagesNonAuction = 'P',     // Options Trade Messages Non Auction
    OptionsCrossTradeMessage = 'Q',           // Options Cross Trade Message
    BrokenTradeOrderExecutedMessage = 'B',    // Broken Trade Order Executed Message
    NoiiMessage = 'I',                        // Noii Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
