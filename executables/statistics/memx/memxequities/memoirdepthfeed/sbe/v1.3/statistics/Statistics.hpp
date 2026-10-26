#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/binary/advanced/memx/memxequities/memoirdepthfeed/sbe/v1.3/messages/session.hpp"

namespace statistics {

// Memx Sbe C++ statistics
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
    uint64_t instrument_directory_message = 0;
    uint64_t reg_sho_restriction_message = 0;
    uint64_t security_trading_status_message = 0;
    uint64_t trading_session_status_message = 0;
    uint64_t order_added_message = 0;
    uint64_t order_deleted_message = 0;
    uint64_t order_reduced_message = 0;
    uint64_t order_executed_message = 0;
    uint64_t trade_message = 0;
    uint64_t broken_trade_message = 0;
    uint64_t corrected_trade_message = 0;
    uint64_t clear_book_message = 0;
    uint64_t snapshot_complete_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process udp packet: the session layer walks the segment and dispatches
    // each message back to this handler
    void udp() {
        const auto& frame = parser.frame();

        memx::memxequities::memoirdepthfeed::sbe::v1_3::process_segment(*this, frame.payload, frame.payload_len, parser.source.timestamp_ns(), frame);

        // whatever dispatch did not recognise is unknown
        unknown_messages = total_messages - matched_messages;
    }

    // called once per segment, before any message is dispatched
    memx::memxequities::memoirdepthfeed::sbe::v1_3::seq_action on_transport_header(const memx::memxequities::memoirdepthfeed::sbe::v1_3::common_header& transport, const packet::Frame&) {
        if (transport.message_type.get().value() == memx::memxequities::memoirdepthfeed::sbe::v1_3::message_type::enum_type::heartbeat_message) {
            ++heartbeats;
            return memx::memxequities::memoirdepthfeed::sbe::v1_3::seq_action::skip;
        }

        if (transport.message_type.get().value() == memx::memxequities::memoirdepthfeed::sbe::v1_3::message_type::enum_type::session_shutdown_message) {
            ++heartbeats;
            return memx::memxequities::memoirdepthfeed::sbe::v1_3::seq_action::skip;
        }

        // how many messages this segment holds is however many the walk finds; each is counted as it arrives

        return memx::memxequities::memoirdepthfeed::sbe::v1_3::seq_action::process;
    }

    // one overload per dispatched message
    void on_message(const memx::memxequities::memoirdepthfeed::sbe::v1_3::instrument_directory_message&, std::uint64_t, const memx::memxequities::memoirdepthfeed::sbe::v1_3::common_header&)
        { ++instrument_directory_message; ++matched_messages; ++total_messages; }
    void on_message(const memx::memxequities::memoirdepthfeed::sbe::v1_3::reg_sho_restriction_message&, std::uint64_t, const memx::memxequities::memoirdepthfeed::sbe::v1_3::common_header&)
        { ++reg_sho_restriction_message; ++matched_messages; ++total_messages; }
    void on_message(const memx::memxequities::memoirdepthfeed::sbe::v1_3::security_trading_status_message&, std::uint64_t, const memx::memxequities::memoirdepthfeed::sbe::v1_3::common_header&)
        { ++security_trading_status_message; ++matched_messages; ++total_messages; }
    void on_message(const memx::memxequities::memoirdepthfeed::sbe::v1_3::trading_session_status_message&, std::uint64_t, const memx::memxequities::memoirdepthfeed::sbe::v1_3::common_header&)
        { ++trading_session_status_message; ++matched_messages; ++total_messages; }
    void on_message(const memx::memxequities::memoirdepthfeed::sbe::v1_3::order_added_message&, std::uint64_t, const memx::memxequities::memoirdepthfeed::sbe::v1_3::common_header&)
        { ++order_added_message; ++matched_messages; ++total_messages; }
    void on_message(const memx::memxequities::memoirdepthfeed::sbe::v1_3::order_deleted_message&, std::uint64_t, const memx::memxequities::memoirdepthfeed::sbe::v1_3::common_header&)
        { ++order_deleted_message; ++matched_messages; ++total_messages; }
    void on_message(const memx::memxequities::memoirdepthfeed::sbe::v1_3::order_reduced_message&, std::uint64_t, const memx::memxequities::memoirdepthfeed::sbe::v1_3::common_header&)
        { ++order_reduced_message; ++matched_messages; ++total_messages; }
    void on_message(const memx::memxequities::memoirdepthfeed::sbe::v1_3::order_executed_message&, std::uint64_t, const memx::memxequities::memoirdepthfeed::sbe::v1_3::common_header&)
        { ++order_executed_message; ++matched_messages; ++total_messages; }
    void on_message(const memx::memxequities::memoirdepthfeed::sbe::v1_3::trade_message&, std::uint64_t, const memx::memxequities::memoirdepthfeed::sbe::v1_3::common_header&)
        { ++trade_message; ++matched_messages; ++total_messages; }
    void on_message(const memx::memxequities::memoirdepthfeed::sbe::v1_3::broken_trade_message&, std::uint64_t, const memx::memxequities::memoirdepthfeed::sbe::v1_3::common_header&)
        { ++broken_trade_message; ++matched_messages; ++total_messages; }
    void on_message(const memx::memxequities::memoirdepthfeed::sbe::v1_3::corrected_trade_message&, std::uint64_t, const memx::memxequities::memoirdepthfeed::sbe::v1_3::common_header&)
        { ++corrected_trade_message; ++matched_messages; ++total_messages; }
    void on_message(const memx::memxequities::memoirdepthfeed::sbe::v1_3::clear_book_message&, std::uint64_t, const memx::memxequities::memoirdepthfeed::sbe::v1_3::common_header&)
        { ++clear_book_message; ++matched_messages; ++total_messages; }
    void on_message(const memx::memxequities::memoirdepthfeed::sbe::v1_3::snapshot_complete_message&, std::uint64_t, const memx::memxequities::memoirdepthfeed::sbe::v1_3::common_header&)
        { ++snapshot_complete_message; ++matched_messages; ++total_messages; }

    // a code none of the messages answer to: counted, so what the walk found adds up
    void on_unknown(const std::byte*, std::size_t, std::uint64_t, const memx::memxequities::memoirdepthfeed::sbe::v1_3::common_header&)
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
        std::cout << "  InstrumentDirectoryMessage    " << instrument_directory_message << std::endl;
        std::cout << "  RegShoRestrictionMessage      " << reg_sho_restriction_message << std::endl;
        std::cout << "  SecurityTradingStatusMessage  " << security_trading_status_message << std::endl;
        std::cout << "  TradingSessionStatusMessage   " << trading_session_status_message << std::endl;
        std::cout << "  OrderAddedMessage             " << order_added_message << std::endl;
        std::cout << "  OrderDeletedMessage           " << order_deleted_message << std::endl;
        std::cout << "  OrderReducedMessage           " << order_reduced_message << std::endl;
        std::cout << "  OrderExecutedMessage          " << order_executed_message << std::endl;
        std::cout << "  TradeMessage                  " << trade_message << std::endl;
        std::cout << "  BrokenTradeMessage            " << broken_trade_message << std::endl;
        std::cout << "  CorrectedTradeMessage         " << corrected_trade_message << std::endl;
        std::cout << "  ClearBookMessage              " << clear_book_message << std::endl;
        std::cout << "  SnapshotCompleteMessage       " << snapshot_complete_message << std::endl;
    }
};
}
