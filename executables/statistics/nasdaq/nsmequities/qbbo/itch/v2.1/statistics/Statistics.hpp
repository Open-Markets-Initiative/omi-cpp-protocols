#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/advanced/nasdaq/nsmequities/qbbo/itch/v2.1/messages/session.hpp"

namespace statistics {

// Nasdaq Itch C++ statistics
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
    uint64_t system_event_message = 0;
    uint64_t stock_directory_message = 0;
    uint64_t stock_trading_action_message = 0;
    uint64_t reg_sho_restriction_message = 0;
    uint64_t mwcb_decline_level_message = 0;
    uint64_t mwcb_breach_message = 0;
    uint64_t operational_halt_message = 0;
    uint64_t bbo_quotation_message = 0;
    uint64_t price_improvement_message = 0;
    uint64_t ipo_quoting_period_update_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process udp packet: the session layer walks the segment and dispatches
    // each message back to this handler
    void udp() {
        const auto& frame = parser.frame();

        nasdaq::nsmequities::qbbo::itch::v2_1::process_segment(*this, frame.payload, frame.payload_len, parser.source.timestamp_ns(), frame);

        // whatever dispatch did not recognise is unknown
        unknown_messages = total_messages - matched_messages;
    }

    // called once per segment, before any message is dispatched
    nasdaq::nsmequities::qbbo::itch::v2_1::seq_action on_transport_header(const nasdaq::nsmequities::qbbo::itch::v2_1::packet_header& transport, const packet::Frame&) {
        if (transport.message_count.get().value() == 0) {
            ++heartbeats;
            return nasdaq::nsmequities::qbbo::itch::v2_1::seq_action::skip;
        }

        if (transport.message_count.get().value() == 65535) {
            ++heartbeats;
            return nasdaq::nsmequities::qbbo::itch::v2_1::seq_action::skip;
        }

        total_messages += transport.message_count.get().value();

        return nasdaq::nsmequities::qbbo::itch::v2_1::seq_action::process;
    }

    // one overload per dispatched message
    void on_message(const nasdaq::nsmequities::qbbo::itch::v2_1::system_event_message&, std::uint64_t, const nasdaq::nsmequities::qbbo::itch::v2_1::packet_header&)
        { ++system_event_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::qbbo::itch::v2_1::stock_directory_message&, std::uint64_t, const nasdaq::nsmequities::qbbo::itch::v2_1::packet_header&)
        { ++stock_directory_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::qbbo::itch::v2_1::stock_trading_action_message&, std::uint64_t, const nasdaq::nsmequities::qbbo::itch::v2_1::packet_header&)
        { ++stock_trading_action_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::qbbo::itch::v2_1::reg_sho_restriction_message&, std::uint64_t, const nasdaq::nsmequities::qbbo::itch::v2_1::packet_header&)
        { ++reg_sho_restriction_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::qbbo::itch::v2_1::mwcb_decline_level_message&, std::uint64_t, const nasdaq::nsmequities::qbbo::itch::v2_1::packet_header&)
        { ++mwcb_decline_level_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::qbbo::itch::v2_1::mwcb_breach_message&, std::uint64_t, const nasdaq::nsmequities::qbbo::itch::v2_1::packet_header&)
        { ++mwcb_breach_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::qbbo::itch::v2_1::operational_halt_message&, std::uint64_t, const nasdaq::nsmequities::qbbo::itch::v2_1::packet_header&)
        { ++operational_halt_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::qbbo::itch::v2_1::bbo_quotation_message&, std::uint64_t, const nasdaq::nsmequities::qbbo::itch::v2_1::packet_header&)
        { ++bbo_quotation_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::qbbo::itch::v2_1::price_improvement_message&, std::uint64_t, const nasdaq::nsmequities::qbbo::itch::v2_1::packet_header&)
        { ++price_improvement_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::qbbo::itch::v2_1::ipo_quoting_period_update_message&, std::uint64_t, const nasdaq::nsmequities::qbbo::itch::v2_1::packet_header&)
        { ++ipo_quoting_period_update_message; ++matched_messages; }

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
        std::cout << "  SystemEventMessage (S)             " << system_event_message << std::endl;
        std::cout << "  StockDirectoryMessage (R)          " << stock_directory_message << std::endl;
        std::cout << "  StockTradingActionMessage (H)      " << stock_trading_action_message << std::endl;
        std::cout << "  RegShoRestrictionMessage (Y)       " << reg_sho_restriction_message << std::endl;
        std::cout << "  MwcbDeclineLevelMessage (V)        " << mwcb_decline_level_message << std::endl;
        std::cout << "  MwcbBreachMessage (W)              " << mwcb_breach_message << std::endl;
        std::cout << "  OperationalHaltMessage (h)         " << operational_halt_message << std::endl;
        std::cout << "  BboQuotationMessage (Q)            " << bbo_quotation_message << std::endl;
        std::cout << "  PriceImprovementMessage (N)        " << price_improvement_message << std::endl;
        std::cout << "  IpoQuotingPeriodUpdateMessage (K)  " << ipo_quoting_period_update_message << std::endl;
    }
};
}
