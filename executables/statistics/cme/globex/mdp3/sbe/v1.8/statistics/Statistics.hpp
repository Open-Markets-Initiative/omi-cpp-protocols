#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/advanced/cme/globex/mdp3/sbe/v1.8/messages/session.hpp"

namespace statistics {

// Cme Sbe C++ statistics
struct Statistics {

    packet::Parser& parser;
    const statistics::Options& options;

    // counters
    uint64_t total_packets = 0;
    uint64_t unknown_packets = 0;
    uint64_t total_messages = 0;
    uint64_t unknown_messages = 0;
    uint64_t heartbeats = 0;
    // messages dispatch recognised; the rest of total_messages is unknown
    uint64_t matched_messages = 0;

    // message counters
    uint64_t mktdata_message = 0;
    uint64_t channel_reset = 0;
    uint64_t admin_heartbeat = 0;
    uint64_t admin_login = 0;
    uint64_t admin_logout = 0;
    uint64_t md_instrument_definition_future = 0;
    uint64_t md_instrument_definition_spread = 0;
    uint64_t security_status = 0;
    uint64_t md_incremental_refresh_book = 0;
    uint64_t md_incremental_refresh_daily_statistics = 0;
    uint64_t md_incremental_refresh_limits_banding = 0;
    uint64_t md_incremental_refresh_session_statistics = 0;
    uint64_t md_incremental_refresh_trade = 0;
    uint64_t md_incremental_refresh_volume = 0;
    uint64_t snapshot_full_refresh = 0;
    uint64_t quote_request = 0;
    uint64_t md_instrument_definition_option = 0;
    uint64_t md_incremental_refresh_trade_summary = 0;
    uint64_t md_incremental_refresh_order_book = 0;
    uint64_t snapshot_full_refresh_order_book = 0;
    uint64_t mdpsessionmgmt_message = 0;
    uint64_t negotiate = 0;
    uint64_t negotiation_reject = 0;
    uint64_t negotiation_response = 0;
    uint64_t terminate = 0;
    uint64_t market_data_request = 0;
    uint64_t request_ack = 0;
    uint64_t request_reject = 0;
    uint64_t security_list_request = 0;
    uint64_t security_status_request = 0;
    uint64_t subscriber_heartbeat = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process udp packet: the session layer walks the segment and dispatches
    // each message back to this handler
    void udp() {
        const auto& frame = parser.frame();

        cme::mdp3::v8::process_segment(*this, frame.payload, frame.payload_len, parser.source.timestamp_ns(), frame);

        // whatever dispatch did not recognise is unknown
        unknown_messages = total_messages - matched_messages;
    }

    // called once per segment, before any message is dispatched
    cme::mdp3::v8::seq_action on_transport_header(const cme::mdp3::v8::binary_packet_header&, const packet::Frame&) {
        // how many messages this segment holds is however many the walk finds; each is counted as it arrives

        return cme::mdp3::v8::seq_action::process;
    }

    // one overload per dispatched message
    void on_message(const cme::mdp3::v8::mktdata_message&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++mktdata_message; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::channel_reset&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++channel_reset; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::admin_heartbeat&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++admin_heartbeat; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::admin_login&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++admin_login; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::admin_logout&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++admin_logout; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::md_instrument_definition_future&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++md_instrument_definition_future; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::md_instrument_definition_spread&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++md_instrument_definition_spread; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::security_status&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++security_status; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::md_incremental_refresh_book&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++md_incremental_refresh_book; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::md_incremental_refresh_daily_statistics&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++md_incremental_refresh_daily_statistics; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::md_incremental_refresh_limits_banding&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++md_incremental_refresh_limits_banding; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::md_incremental_refresh_session_statistics&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++md_incremental_refresh_session_statistics; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::md_incremental_refresh_trade&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++md_incremental_refresh_trade; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::md_incremental_refresh_volume&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++md_incremental_refresh_volume; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::snapshot_full_refresh&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++snapshot_full_refresh; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::quote_request&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++quote_request; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::md_instrument_definition_option&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++md_instrument_definition_option; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::md_incremental_refresh_trade_summary&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++md_incremental_refresh_trade_summary; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::md_incremental_refresh_order_book&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++md_incremental_refresh_order_book; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::snapshot_full_refresh_order_book&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++snapshot_full_refresh_order_book; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::mdpsessionmgmt_message&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++mdpsessionmgmt_message; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::negotiate&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++negotiate; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::negotiation_reject&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++negotiation_reject; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::negotiation_response&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++negotiation_response; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::terminate&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++terminate; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::market_data_request&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++market_data_request; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::request_ack&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++request_ack; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::request_reject&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++request_reject; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::security_list_request&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++security_list_request; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::security_status_request&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++security_status_request; ++matched_messages; ++total_messages; }
    void on_message(const cme::mdp3::v8::subscriber_heartbeat&, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++subscriber_heartbeat; ++matched_messages; ++total_messages; }

    // a code none of the messages answer to: counted, so what the walk found adds up
    void on_unknown(const std::byte*, std::size_t, std::uint64_t, const cme::mdp3::v8::binary_packet_header&)
        { ++total_messages; }

    // report statistics
    void report() {
        std::cout << std::endl;
        std::cout << "Statistics Report" << std::endl;
        std::cout << "=================" << std::endl;
        std::cout << "Total packets:   " << total_packets << std::endl;
        std::cout << "Unknown packets: " << unknown_packets << std::endl;
        std::cout << "Total messages:  " << total_messages << std::endl;
        std::cout << "Unknown types:   " << unknown_messages << std::endl;
        std::cout << "Heartbeats:      " << heartbeats << std::endl;

        std::cout << std::endl;
        std::cout << "Message Counts:" << std::endl;
        std::cout << "--------------" << std::endl;
        std::cout << "  MktdataMessage                              " << mktdata_message << std::endl;
        std::cout << "  ChannelReset (4)                            " << channel_reset << std::endl;
        std::cout << "  AdminHeartbeat (12)                         " << admin_heartbeat << std::endl;
        std::cout << "  AdminLogin (15)                             " << admin_login << std::endl;
        std::cout << "  AdminLogout (16)                            " << admin_logout << std::endl;
        std::cout << "  MdInstrumentDefinitionFuture (27)           " << md_instrument_definition_future << std::endl;
        std::cout << "  MdInstrumentDefinitionSpread (29)           " << md_instrument_definition_spread << std::endl;
        std::cout << "  SecurityStatus (30)                         " << security_status << std::endl;
        std::cout << "  MdIncrementalRefreshBook (32)               " << md_incremental_refresh_book << std::endl;
        std::cout << "  MdIncrementalRefreshDailyStatistics (33)    " << md_incremental_refresh_daily_statistics << std::endl;
        std::cout << "  MdIncrementalRefreshLimitsBanding (34)      " << md_incremental_refresh_limits_banding << std::endl;
        std::cout << "  MdIncrementalRefreshSessionStatistics (35)  " << md_incremental_refresh_session_statistics << std::endl;
        std::cout << "  MdIncrementalRefreshTrade (36)              " << md_incremental_refresh_trade << std::endl;
        std::cout << "  MdIncrementalRefreshVolume (37)             " << md_incremental_refresh_volume << std::endl;
        std::cout << "  SnapshotFullRefresh (38)                    " << snapshot_full_refresh << std::endl;
        std::cout << "  QuoteRequest (39)                           " << quote_request << std::endl;
        std::cout << "  MdInstrumentDefinitionOption (41)           " << md_instrument_definition_option << std::endl;
        std::cout << "  MdIncrementalRefreshTradeSummary (42)       " << md_incremental_refresh_trade_summary << std::endl;
        std::cout << "  MdIncrementalRefreshOrderBook (43)          " << md_incremental_refresh_order_book << std::endl;
        std::cout << "  SnapshotFullRefreshOrderBook (44)           " << snapshot_full_refresh_order_book << std::endl;
        std::cout << "  MdpsessionmgmtMessage                       " << mdpsessionmgmt_message << std::endl;
        std::cout << "  Negotiate (200)                             " << negotiate << std::endl;
        std::cout << "  NegotiationReject (201)                     " << negotiation_reject << std::endl;
        std::cout << "  NegotiationResponse (202)                   " << negotiation_response << std::endl;
        std::cout << "  Terminate (203)                             " << terminate << std::endl;
        std::cout << "  MarketDataRequest (205)                     " << market_data_request << std::endl;
        std::cout << "  RequestAck (206)                            " << request_ack << std::endl;
        std::cout << "  RequestReject (207)                         " << request_reject << std::endl;
        std::cout << "  SecurityListRequest (208)                   " << security_list_request << std::endl;
        std::cout << "  SecurityStatusRequest (209)                 " << security_status_request << std::endl;
        std::cout << "  SubscriberHeartbeat (210)                   " << subscriber_heartbeat << std::endl;
    }
};
}
