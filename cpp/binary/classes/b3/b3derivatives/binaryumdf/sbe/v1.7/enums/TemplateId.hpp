#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// Template ID used to encode the message
enum class TemplateId : std::uint16_t {
    SequenceReset1Message = 1,                  // Sequence Reset 1 Message
    Sequence2Message = 2,                       // Sequence 2 Message
    EmptyBook9Message = 9,                      // Empty Book 9 Message
    ChannelReset11Message = 11,                 // Channel Reset 11 Message
    SecurityStatus3Message = 3,                 // Security Status 3 Message
    SecurityGroupPhase10Message = 10,           // Security Group Phase 10 Message
    DeprecatedsecurityDefinitionMessage = 4,    // DeprecatedSecurity Definition Message
    SecurityDefinitionMessage = 12,             // Security Definition Message
    News5Message = 5,                           // News 5 Message
    OpeningPrice15Message = 15,                 // Opening Price 15 Message
    TheoreticalOpeningPrice16Message = 16,      // Theoretical Opening Price 16 Message
    ClosingPrice17Message = 17,                 // Closing Price 17 Message
    AuctionImbalance19Message = 19,             // Auction Imbalance 19 Message
    PriceBand20Message = 20,                    // Price Band 20 Message
    QuantityBand21Message = 21,                 // Quantity Band 21 Message
    PriceBand22Message = 22,                    // Price Band 22 Message
    HighPrice24Message = 24,                    // High Price 24 Message
    LowPrice25Message = 25,                     // Low Price 25 Message
    LastTradePrice27Message = 27,               // Last Trade Price 27 Message
    SnapshotFullRefreshHeader30Message = 30,    // Snapshot Full Refresh Header 30 Message
    OrderMbO50Message = 50,                     // Order Mb O 50 Message
    DeleteOrderMbO51Message = 51,               // Delete Order Mb O 51 Message
    MassDeleteOrdersMbO52Message = 52,          // Mass Delete Orders Mb O 52 Message
    Trade53Message = 53,                        // Trade 53 Message
    ForwardTrade54Message = 54,                 // Forward Trade 54 Message
    ExecutionSummary55Message = 55,             // Execution Summary 55 Message
    ExecutionStatistics56Message = 56,          // Execution Statistics 56 Message
    TradeBust57Message = 57,                    // Trade Bust 57 Message
    SnapshotFullRefreshOrdersMbO71Message = 71, // Snapshot Full Refresh Orders Mb O 71 Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TemplateId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TemplateId value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
