#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/advanced/miax/pearlequities/depthofmarket/mach/v1.3.d/messages/session.hpp"

namespace statistics {

// Miax Mach C++ statistics
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
    uint64_t system_time_message = 0;
    uint64_t symbol_update_message = 0;
    uint64_t system_state_message = 0;
    uint64_t security_trading_status_notification_message = 0;
    uint64_t symbol_clear_message = 0;
    uint64_t add_order_message = 0;
    uint64_t modify_order_message = 0;
    uint64_t delete_order_message = 0;
    uint64_t order_execution_message = 0;
    uint64_t trade_message = 0;
    uint64_t trade_cancel_message = 0;
    uint64_t refresh_request_message = 0;
    uint64_t refresh_response_message = 0;
    uint64_t end_of_refresh_notification_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process udp packet: the session layer walks the segment and dispatches
    // each message back to this handler
    void udp() {
        const auto& frame = parser.frame();

        miax::pearlequities::depthofmarket::mach::v1_3_d::process_segment(*this, frame.payload, frame.payload_len, parser.source.timestamp_ns(), frame);

        // whatever dispatch did not recognise is unknown
        unknown_messages = total_messages - matched_messages;
    }

    // called once per segment, before any message is dispatched
    miax::pearlequities::depthofmarket::mach::v1_3_d::seq_action on_transport_header(const miax::pearlequities::depthofmarket::mach::v1_3_d::mach_message& transport, const packet::Frame&) {
        if (transport.mach_packet_type.get().value() == miax::pearlequities::depthofmarket::mach::v1_3_d::mach_packet_type::enum_type::heartbeat) {
            ++heartbeats;
            return miax::pearlequities::depthofmarket::mach::v1_3_d::seq_action::skip;
        }

        if (transport.mach_packet_type.get().value() == miax::pearlequities::depthofmarket::mach::v1_3_d::mach_packet_type::enum_type::start_of_session) {
            ++heartbeats;
            return miax::pearlequities::depthofmarket::mach::v1_3_d::seq_action::skip;
        }

        if (transport.mach_packet_type.get().value() == miax::pearlequities::depthofmarket::mach::v1_3_d::mach_packet_type::enum_type::end_of_session) {
            ++heartbeats;
            return miax::pearlequities::depthofmarket::mach::v1_3_d::seq_action::skip;
        }

        // how many messages this segment holds is however many the walk finds; each is counted as it arrives

        return miax::pearlequities::depthofmarket::mach::v1_3_d::seq_action::process;
    }

    // one overload per dispatched message
    void on_message(const miax::pearlequities::depthofmarket::mach::v1_3_d::system_time_message&, std::uint64_t, const miax::pearlequities::depthofmarket::mach::v1_3_d::mach_message&)
        { ++system_time_message; ++matched_messages; ++total_messages; }
    void on_message(const miax::pearlequities::depthofmarket::mach::v1_3_d::symbol_update_message&, std::uint64_t, const miax::pearlequities::depthofmarket::mach::v1_3_d::mach_message&)
        { ++symbol_update_message; ++matched_messages; ++total_messages; }
    void on_message(const miax::pearlequities::depthofmarket::mach::v1_3_d::system_state_message&, std::uint64_t, const miax::pearlequities::depthofmarket::mach::v1_3_d::mach_message&)
        { ++system_state_message; ++matched_messages; ++total_messages; }
    void on_message(const miax::pearlequities::depthofmarket::mach::v1_3_d::security_trading_status_notification_message&, std::uint64_t, const miax::pearlequities::depthofmarket::mach::v1_3_d::mach_message&)
        { ++security_trading_status_notification_message; ++matched_messages; ++total_messages; }
    void on_message(const miax::pearlequities::depthofmarket::mach::v1_3_d::symbol_clear_message&, std::uint64_t, const miax::pearlequities::depthofmarket::mach::v1_3_d::mach_message&)
        { ++symbol_clear_message; ++matched_messages; ++total_messages; }
    void on_message(const miax::pearlequities::depthofmarket::mach::v1_3_d::add_order_message&, std::uint64_t, const miax::pearlequities::depthofmarket::mach::v1_3_d::mach_message&)
        { ++add_order_message; ++matched_messages; ++total_messages; }
    void on_message(const miax::pearlequities::depthofmarket::mach::v1_3_d::modify_order_message&, std::uint64_t, const miax::pearlequities::depthofmarket::mach::v1_3_d::mach_message&)
        { ++modify_order_message; ++matched_messages; ++total_messages; }
    void on_message(const miax::pearlequities::depthofmarket::mach::v1_3_d::delete_order_message&, std::uint64_t, const miax::pearlequities::depthofmarket::mach::v1_3_d::mach_message&)
        { ++delete_order_message; ++matched_messages; ++total_messages; }
    void on_message(const miax::pearlequities::depthofmarket::mach::v1_3_d::order_execution_message&, std::uint64_t, const miax::pearlequities::depthofmarket::mach::v1_3_d::mach_message&)
        { ++order_execution_message; ++matched_messages; ++total_messages; }
    void on_message(const miax::pearlequities::depthofmarket::mach::v1_3_d::trade_message&, std::uint64_t, const miax::pearlequities::depthofmarket::mach::v1_3_d::mach_message&)
        { ++trade_message; ++matched_messages; ++total_messages; }
    void on_message(const miax::pearlequities::depthofmarket::mach::v1_3_d::trade_cancel_message&, std::uint64_t, const miax::pearlequities::depthofmarket::mach::v1_3_d::mach_message&)
        { ++trade_cancel_message; ++matched_messages; ++total_messages; }
    void on_message(const miax::pearlequities::depthofmarket::mach::v1_3_d::refresh_request_message&, std::uint64_t, const miax::pearlequities::depthofmarket::mach::v1_3_d::mach_message&)
        { ++refresh_request_message; ++matched_messages; ++total_messages; }
    void on_message(const miax::pearlequities::depthofmarket::mach::v1_3_d::refresh_response_message&, std::uint64_t, const miax::pearlequities::depthofmarket::mach::v1_3_d::mach_message&)
        { ++refresh_response_message; ++matched_messages; ++total_messages; }
    void on_message(const miax::pearlequities::depthofmarket::mach::v1_3_d::end_of_refresh_notification_message&, std::uint64_t, const miax::pearlequities::depthofmarket::mach::v1_3_d::mach_message&)
        { ++end_of_refresh_notification_message; ++matched_messages; ++total_messages; }

    // a code none of the messages answer to: counted, so what the walk found adds up
    void on_unknown(const std::byte*, std::size_t, std::uint64_t, const miax::pearlequities::depthofmarket::mach::v1_3_d::mach_message&)
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
        std::cout << "  SystemTimeMessage (49)                        " << system_time_message << std::endl;
        std::cout << "  SymbolUpdateMessage (1)                       " << symbol_update_message << std::endl;
        std::cout << "  SystemStateMessage (83)                       " << system_state_message << std::endl;
        std::cout << "  SecurityTradingStatusNotificationMessage (4)  " << security_trading_status_notification_message << std::endl;
        std::cout << "  SymbolClearMessage (5)                        " << symbol_clear_message << std::endl;
        std::cout << "  AddOrderMessage (20)                          " << add_order_message << std::endl;
        std::cout << "  ModifyOrderMessage (21)                       " << modify_order_message << std::endl;
        std::cout << "  DeleteOrderMessage (23)                       " << delete_order_message << std::endl;
        std::cout << "  OrderExecutionMessage (24)                    " << order_execution_message << std::endl;
        std::cout << "  TradeMessage (10)                             " << trade_message << std::endl;
        std::cout << "  TradeCancelMessage (11)                       " << trade_cancel_message << std::endl;
        std::cout << "  RefreshRequestMessage (R)                     " << refresh_request_message << std::endl;
        std::cout << "  RefreshResponseMessage (r)                    " << refresh_response_message << std::endl;
        std::cout << "  EndOfRefreshNotificationMessage (E)           " << end_of_refresh_notification_message << std::endl;
    }
};
}
