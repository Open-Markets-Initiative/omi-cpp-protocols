#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cme::globex::mdp3::sbe::v1_13 {

enum class TemplateId : std::uint16_t {
    ChannelReset = 4,                                  // Channel Reset
    AdminHeartbeat = 12,                               // Admin Heartbeat
    AdminLogin = 15,                                   // Admin Login
    AdminLogout = 16,                                  // Admin Logout
    SecurityStatus = 30,                               // Security Status
    MdIncrementalRefreshVolume = 37,                   // Md Incremental Refresh Volume
    QuoteRequest = 39,                                 // Quote Request
    MdIncrementalRefreshBook = 46,                     // Md Incremental Refresh Book
    MdIncrementalRefreshOrderBook = 47,                // Md Incremental Refresh Order Book
    MdIncrementalRefreshTradeSummary = 48,             // Md Incremental Refresh Trade Summary
    MdIncrementalRefreshDailyStatistics = 49,          // Md Incremental Refresh Daily Statistics
    MdIncrementalRefreshLimitsBanding = 50,            // Md Incremental Refresh Limits Banding
    MdIncrementalRefreshSessionStatistics = 51,        // Md Incremental Refresh Session Statistics
    SnapshotFullRefresh = 52,                          // Snapshot Full Refresh
    SnapshotFullRefreshOrderBook = 53,                 // Snapshot Full Refresh Order Book
    MdInstrumentDefinitionFuture = 54,                 // Md Instrument Definition Future
    MdInstrumentDefinitionOption = 55,                 // Md Instrument Definition Option
    MdInstrumentDefinitionSpread = 56,                 // Md Instrument Definition Spread
    MdInstrumentDefinitionFixedIncome = 57,            // Md Instrument Definition Fixed Income
    MdInstrumentDefinitionRepo = 58,                   // Md Instrument Definition Repo
    SnapshotRefreshTopOrders = 59,                     // Snapshot Refresh Top Orders
    SecurityStatusWorkup = 60,                         // Security Status Workup
    SnapshotFullRefreshTcp = 61,                       // Snapshot Full Refresh Tcp
    CollateralMarketValue = 62,                        // Collateral Market Value
    MdInstrumentDefinitionFx = 63,                     // Md Instrument Definition Fx
    MdIncrementalRefreshBookLongQty = 64,              // Md Incremental Refresh Book Long Qty
    MdIncrementalRefreshTradeSummaryLongQty = 65,      // Md Incremental Refresh Trade Summary Long Qty
    MdIncrementalRefreshVolumeLongQty = 66,            // Md Incremental Refresh Volume Long Qty
    MdIncrementalRefreshSessionStatisticsLongQty = 67, // Md Incremental Refresh Session Statistics Long Qty
    SnapshotFullRefreshTcpLongQty = 68,                // Snapshot Full Refresh Tcp Long Qty
    SnapshotFullRefreshLongQty = 69,                   // Snapshot Full Refresh Long Qty
    Negotiate = 200,                                   // Negotiate
    NegotiationReject = 201,                           // Negotiation Reject
    NegotiationResponse = 202,                         // Negotiation Response
    Terminate = 203,                                   // Terminate
    MarketDataRequest = 205,                           // Market Data Request
    RequestAck = 206,                                  // Request Ack
    RequestReject = 207,                               // Request Reject
    SecurityListRequest = 208,                         // Security List Request
    SecurityStatusRequest = 209,                       // Security Status Request
    SubscriberHeartbeat = 210,                         // Subscriber Heartbeat
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TemplateId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TemplateId value);

} // namespace cme::globex::mdp3::sbe::v1_13
