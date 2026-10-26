#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cme::globex::mdp3::sbe::v1_8 {

enum class TemplateId : std::uint16_t {
    ChannelReset = 4,                           // Channel Reset
    AdminHeartbeat = 12,                        // Admin Heartbeat
    AdminLogin = 15,                            // Admin Login
    AdminLogout = 16,                           // Admin Logout
    MdInstrumentDefinitionFuture = 27,          // Md Instrument Definition Future
    MdInstrumentDefinitionSpread = 29,          // Md Instrument Definition Spread
    SecurityStatus = 30,                        // Security Status
    MdIncrementalRefreshBook = 32,              // Md Incremental Refresh Book
    MdIncrementalRefreshDailyStatistics = 33,   // Md Incremental Refresh Daily Statistics
    MdIncrementalRefreshLimitsBanding = 34,     // Md Incremental Refresh Limits Banding
    MdIncrementalRefreshSessionStatistics = 35, // Md Incremental Refresh Session Statistics
    MdIncrementalRefreshTrade = 36,             // Md Incremental Refresh Trade
    MdIncrementalRefreshVolume = 37,            // Md Incremental Refresh Volume
    SnapshotFullRefresh = 38,                   // Snapshot Full Refresh
    QuoteRequest = 39,                          // Quote Request
    MdInstrumentDefinitionOption = 41,          // Md Instrument Definition Option
    MdIncrementalRefreshTradeSummary = 42,      // Md Incremental Refresh Trade Summary
    MdIncrementalRefreshOrderBook = 43,         // Md Incremental Refresh Order Book
    SnapshotFullRefreshOrderBook = 44,          // Snapshot Full Refresh Order Book
    Negotiate = 200,                            // Negotiate
    NegotiationReject = 201,                    // Negotiation Reject
    NegotiationResponse = 202,                  // Negotiation Response
    Terminate = 203,                            // Terminate
    MarketDataRequest = 205,                    // Market Data Request
    RequestAck = 206,                           // Request Ack
    RequestReject = 207,                        // Request Reject
    SecurityListRequest = 208,                  // Security List Request
    SecurityStatusRequest = 209,                // Security Status Request
    SubscriberHeartbeat = 210,                  // Subscriber Heartbeat
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TemplateId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TemplateId value);

} // namespace cme::globex::mdp3::sbe::v1_8
