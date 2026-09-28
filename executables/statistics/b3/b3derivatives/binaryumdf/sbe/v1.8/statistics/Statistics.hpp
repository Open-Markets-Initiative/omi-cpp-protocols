#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/advanced/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/session.hpp"

namespace statistics {

// B3 Sbe C++ statistics
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
    uint64_t sequence_reset_message = 0;
    uint64_t sequence_message = 0;
    uint64_t empty_book_message = 0;
    uint64_t channel_reset_11_message = 0;
    uint64_t security_status_3_message = 0;
    uint64_t security_group_phase_10_message = 0;
    uint64_t deprecated_security_definition_message = 0;
    uint64_t security_definition_message = 0;
    uint64_t news_5_message = 0;
    uint64_t opening_price_15_message = 0;
    uint64_t theoretical_opening_price_16_message = 0;
    uint64_t closing_price_17_message = 0;
    uint64_t auction_imbalance_19_message = 0;
    uint64_t price_band_20_message = 0;
    uint64_t quantity_band_21_message = 0;
    uint64_t price_band_22_message = 0;
    uint64_t high_price_24_message = 0;
    uint64_t low_price_25_message = 0;
    uint64_t last_trade_price_27_message = 0;
    uint64_t settlement_price_28_message = 0;
    uint64_t open_interest_29_message = 0;
    uint64_t snapshot_full_refresh_header_30_message = 0;
    uint64_t order_mb_o_50_message = 0;
    uint64_t delete_order_mb_o_51_message = 0;
    uint64_t mass_delete_orders_mb_o_52_message = 0;
    uint64_t trade_53_message = 0;
    uint64_t forward_trade_54_message = 0;
    uint64_t execution_summary_55_message = 0;
    uint64_t execution_statistics_56_message = 0;
    uint64_t trade_bust_57_message = 0;
    uint64_t snapshot_full_refresh_orders_mb_o_71_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process udp packet: the session layer walks the segment and dispatches
    // each message back to this handler
    void udp() {
        const auto& frame = parser.frame();

        b3::b3derivatives::binaryumdf::sbe::v1_8::process_segment(*this, frame.payload, frame.payload_len, parser.source.timestamp_ns(), frame);

        // whatever dispatch did not recognise is unknown
        unknown_messages = total_messages - matched_messages;
    }

    // called once per segment, before any message is dispatched
    b3::b3derivatives::binaryumdf::sbe::v1_8::seq_action on_transport_header(const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header& transport, const packet::Frame&) {
        // how many messages this segment holds is however many the walk finds; each is counted as it arrives

        return b3::b3derivatives::binaryumdf::sbe::v1_8::seq_action::process;
    }

    // one overload per dispatched message
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::sequence_reset_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++sequence_reset_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::sequence_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++sequence_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::empty_book_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++empty_book_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::channel_reset_11_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++channel_reset_11_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::security_status_3_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++security_status_3_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::security_group_phase_10_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++security_group_phase_10_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::deprecated_security_definition_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++deprecated_security_definition_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::security_definition_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++security_definition_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::news_5_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++news_5_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::opening_price_15_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++opening_price_15_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::theoretical_opening_price_16_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++theoretical_opening_price_16_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::closing_price_17_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++closing_price_17_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::auction_imbalance_19_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++auction_imbalance_19_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::price_band_20_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++price_band_20_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::quantity_band_21_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++quantity_band_21_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::price_band_22_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++price_band_22_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::high_price_24_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++high_price_24_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::low_price_25_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++low_price_25_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::last_trade_price_27_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++last_trade_price_27_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::settlement_price_28_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++settlement_price_28_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::open_interest_29_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++open_interest_29_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::snapshot_full_refresh_header_30_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++snapshot_full_refresh_header_30_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::order_mb_o_50_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++order_mb_o_50_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::delete_order_mb_o_51_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++delete_order_mb_o_51_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::mass_delete_orders_mb_o_52_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++mass_delete_orders_mb_o_52_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::trade_53_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++trade_53_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::forward_trade_54_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++forward_trade_54_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::execution_summary_55_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++execution_summary_55_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::execution_statistics_56_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++execution_statistics_56_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::trade_bust_57_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++trade_bust_57_message; ++matched_messages; ++total_messages; }
    void on_message(const b3::b3derivatives::binaryumdf::sbe::v1_8::snapshot_full_refresh_orders_mb_o_71_message&, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
        { ++snapshot_full_refresh_orders_mb_o_71_message; ++matched_messages; ++total_messages; }

    // a code none of the messages answer to: counted, so what the walk found adds up
    void on_unknown(const std::byte*, std::size_t, std::uint64_t, const b3::b3derivatives::binaryumdf::sbe::v1_8::packet_header&)
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
        std::cout << "  SequenceResetMessage                   " << sequence_reset_message << std::endl;
        std::cout << "  SequenceMessage                        " << sequence_message << std::endl;
        std::cout << "  EmptyBookMessage                       " << empty_book_message << std::endl;
        std::cout << "  ChannelReset11Message                  " << channel_reset_11_message << std::endl;
        std::cout << "  SecurityStatus3Message                 " << security_status_3_message << std::endl;
        std::cout << "  SecurityGroupPhase10Message            " << security_group_phase_10_message << std::endl;
        std::cout << "  DeprecatedSecurityDefinitionMessage    " << deprecated_security_definition_message << std::endl;
        std::cout << "  SecurityDefinitionMessage              " << security_definition_message << std::endl;
        std::cout << "  News5Message                           " << news_5_message << std::endl;
        std::cout << "  OpeningPrice15Message                  " << opening_price_15_message << std::endl;
        std::cout << "  TheoreticalOpeningPrice16Message       " << theoretical_opening_price_16_message << std::endl;
        std::cout << "  ClosingPrice17Message                  " << closing_price_17_message << std::endl;
        std::cout << "  AuctionImbalance19Message              " << auction_imbalance_19_message << std::endl;
        std::cout << "  PriceBand20Message                     " << price_band_20_message << std::endl;
        std::cout << "  QuantityBand21Message                  " << quantity_band_21_message << std::endl;
        std::cout << "  PriceBand22Message                     " << price_band_22_message << std::endl;
        std::cout << "  HighPrice24Message                     " << high_price_24_message << std::endl;
        std::cout << "  LowPrice25Message                      " << low_price_25_message << std::endl;
        std::cout << "  LastTradePrice27Message                " << last_trade_price_27_message << std::endl;
        std::cout << "  SettlementPrice28Message               " << settlement_price_28_message << std::endl;
        std::cout << "  OpenInterest29Message                  " << open_interest_29_message << std::endl;
        std::cout << "  SnapshotFullRefreshHeader30Message     " << snapshot_full_refresh_header_30_message << std::endl;
        std::cout << "  OrderMbO50Message                      " << order_mb_o_50_message << std::endl;
        std::cout << "  DeleteOrderMbO51Message                " << delete_order_mb_o_51_message << std::endl;
        std::cout << "  MassDeleteOrdersMbO52Message           " << mass_delete_orders_mb_o_52_message << std::endl;
        std::cout << "  Trade53Message                         " << trade_53_message << std::endl;
        std::cout << "  ForwardTrade54Message                  " << forward_trade_54_message << std::endl;
        std::cout << "  ExecutionSummary55Message              " << execution_summary_55_message << std::endl;
        std::cout << "  ExecutionStatistics56Message           " << execution_statistics_56_message << std::endl;
        std::cout << "  TradeBust57Message                     " << trade_bust_57_message << std::endl;
        std::cout << "  SnapshotFullRefreshOrdersMbO71Message  " << snapshot_full_refresh_orders_mb_o_71_message << std::endl;
    }
};
}
