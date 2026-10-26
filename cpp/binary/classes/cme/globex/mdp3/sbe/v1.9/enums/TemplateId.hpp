#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cme::globex::mdp3::sbe::v1_9 {

enum class TemplateId : std::uint16_t {
    ChannelReset = 4,                                 // Channel Reset
    AdminHeartbeat = 12,                              // Admin Heartbeat
    AdminLogin = 15,                                  // Admin Login
    AdminLogout = 16,                                 // Admin Logout
    MdInstrumentDefinitionFutureLegacy = 27,          // Md Instrument Definition Future Legacy
    MdInstrumentDefinitionSpreadLegacy = 29,          // Md Instrument Definition Spread Legacy
    SecurityStatus = 30,                              // Security Status
    MdIncrementalRefreshBookLegacy = 32,              // Md Incremental Refresh Book Legacy
    MdIncrementalRefreshDailyStatisticsLegacy = 33,   // Md Incremental Refresh Daily Statistics Legacy
    MdIncrementalRefreshLimitsBandingLegacy = 34,     // Md Incremental Refresh Limits Banding Legacy
    MdIncrementalRefreshSessionStatisticsLegacy = 35, // Md Incremental Refresh Session Statistics Legacy
    MdIncrementalRefreshVolume = 37,                  // Md Incremental Refresh Volume
    SnapshotFullRefreshLegacy = 38,                   // Snapshot Full Refresh Legacy
    QuoteRequest = 39,                                // Quote Request
    MdInstrumentDefinitionOptionLegacy = 41,          // Md Instrument Definition Option Legacy
    MdIncrementalRefreshTradeSummaryLegacy = 42,      // Md Incremental Refresh Trade Summary Legacy
    MdIncrementalRefreshOrderBookLegacy = 43,         // Md Incremental Refresh Order Book Legacy
    SnapshotFullRefreshOrderBookLegacy = 44,          // Snapshot Full Refresh Order Book Legacy
    MdIncrementalRefreshBook = 46,                    // Md Incremental Refresh Book
    MdIncrementalRefreshOrderBook = 47,               // Md Incremental Refresh Order Book
    MdIncrementalRefreshTradeSummary = 48,            // Md Incremental Refresh Trade Summary
    MdIncrementalRefreshDailyStatistics = 49,         // Md Incremental Refresh Daily Statistics
    MdIncrementalRefreshLimitsBanding = 50,           // Md Incremental Refresh Limits Banding
    MdIncrementalRefreshSessionStatistics = 51,       // Md Incremental Refresh Session Statistics
    SnapshotFullRefresh = 52,                         // Snapshot Full Refresh
    SnapshotFullRefreshOrderBook = 53,                // Snapshot Full Refresh Order Book
    MdInstrumentDefinitionFuture = 54,                // Md Instrument Definition Future
    MdInstrumentDefinitionOption = 55,                // Md Instrument Definition Option
    MdInstrumentDefinitionSpread = 56,                // Md Instrument Definition Spread
    Negotiate = 200,                                  // Negotiate
    NegotiationReject = 201,                          // Negotiation Reject
    NegotiationResponse = 202,                        // Negotiation Response
    Terminate = 203,                                  // Terminate
    MarketDataRequest = 205,                          // Market Data Request
    RequestAck = 206,                                 // Request Ack
    RequestReject = 207,                              // Request Reject
    SecurityListRequest = 208,                        // Security List Request
    SecurityStatusRequest = 209,                      // Security Status Request
    SubscriberHeartbeat = 210,                        // Subscriber Heartbeat
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TemplateId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TemplateId value);

} // namespace cme::globex::mdp3::sbe::v1_9
