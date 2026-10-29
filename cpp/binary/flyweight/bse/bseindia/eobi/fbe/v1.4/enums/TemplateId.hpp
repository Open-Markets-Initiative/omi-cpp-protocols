#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace bse::bseindia::eobi::fbe::v1_4 {

// Unique identifier for a Bse Eobi message layout
enum class TemplateId : std::uint16_t {
    HeartbeatMessage = 13001,               // Heartbeat Message
    ProductSummaryMessage = 13600,          // Product Summary Message
    SnapshotOrderMessage = 13602,           // Snapshot Order Message
    InstrumentSummaryMessage = 13601,       // Instrument Summary Message
    AuctionBestBidOfferMessage = 13500,     // Auction Best Bid Offer Message
    AuctionClearingPriceMessage = 13501,    // Auction Clearing Price Message
    TopOfBookMessage = 13504,               // Top Of Book Message
    OrderAddMessage = 13100,                // Order Add Message
    OrderModifyMessage = 13101,             // Order Modify Message
    OrderModifySamePriorityMessage = 13106, // Order Modify Same Priority Message
    OrderDeleteMessage = 13102,             // Order Delete Message
    OrderMassDeleteMessage = 13103,         // Order Mass Delete Message
    PartialOrderExecutionMessage = 13105,   // Partial Order Execution Message
    FullOrderExecutionMessage = 13104,      // Full Order Execution Message
    TradeReversalMessage = 13200,           // Trade Reversal Message
    ExecutionSummaryMessage = 13202,        // Execution Summary Message
    InstrumentInfoMessage = 13203,          // Instrument Info Message
    LppRangeMessage = 13204,                // Lpp Range Message
    ProductStateChangeMessage = 13300,      // Product State Change Message
    InstrumentStateChangeMessage = 13301,   // Instrument State Change Message
    AddComplexInstrumentMessage = 13400,    // Add Complex Instrument Message
    PacketHeader = 13002,                   // Packet Header
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TemplateId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TemplateId value);

} // namespace bse::bseindia::eobi::fbe::v1_4
