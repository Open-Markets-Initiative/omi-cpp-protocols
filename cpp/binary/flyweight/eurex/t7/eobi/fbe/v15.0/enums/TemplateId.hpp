#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v15_0 {

// SBE template identifier of the packet header (e.g., 13004 RefreshHeader / 13005
// BeaconMessage)
enum class TemplateId : std::uint16_t {
    AddComplexInstrument = 13400,      // Add Complex Instrument
    AddFlexibleInstrument = 13401,     // Add Flexible Instrument
    AddScaledSimpleInstrument = 13402, // Add Scaled Simple Instrument
    AuctionBbo = 13500,                // Auction Bbo
    AuctionClearingPrice = 13501,      // Auction Clearing Price
    CrossRequest = 13502,              // Cross Request
    ExecutionSummary = 13202,          // Execution Summary
    FullOrderExecution = 13104,        // Full Order Execution
    Heartbeat = 13001,                 // Heartbeat
    InstrumentStateChange = 13301,     // Instrument State Change
    InstrumentSummary = 13601,         // Instrument Summary
    MassInstrumentStateChange = 13302, // Mass Instrument State Change
    OrderAdd = 13100,                  // Order Add
    OrderDelete = 13102,               // Order Delete
    OrderMassDelete = 13103,           // Order Mass Delete
    OrderModify = 13101,               // Order Modify
    OrderModifySamePrio = 13106,       // Order Modify Same Prio
    PacketHeader = 13002,              // Packet Header
    PartialOrderExecution = 13105,     // Partial Order Execution
    ProductStateChange = 13300,        // Product State Change
    ProductSummary = 13600,            // Product Summary
    QuoteRequest = 13503,              // Quote Request
    SnapshotOrder = 13602,             // Snapshot Order
    TesTradeReport = 13203,            // Tes Trade Report
    TopOfBook = 13504,                 // Top Of Book
    TradeReport = 13201,               // Trade Report
    TradeReversal = 13200,             // Trade Reversal
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TemplateId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TemplateId value);

} // namespace eurex::t7::eobi::fbe::v15_0
