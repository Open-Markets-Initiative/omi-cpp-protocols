#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/binary/advanced/asx/asxderivatives/ntp/itch/v1.05/messages/session.hpp"

namespace statistics {

// Asx Itch C++ statistics
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
    uint64_t seconds_message = 0;
    uint64_t end_of_business_trade_date_message = 0;
    uint64_t future_symbol_directory_message = 0;
    uint64_t options_symbol_directory_message = 0;
    uint64_t combination_symbol_directory_message = 0;
    uint64_t bundles_symbol_directory = 0;
    uint64_t order_book_state_message = 0;
    uint64_t add_order_message = 0;
    uint64_t order_volume_cancelled_message = 0;
    uint64_t order_deleted_message = 0;
    uint64_t order_executed_message = 0;
    uint64_t auction_order_executed_message = 0;
    uint64_t combination_order_executed_message = 0;
    uint64_t implied_order_added_message = 0;
    uint64_t implied_order_replaced_message = 0;
    uint64_t implied_order_deleted_message = 0;
    uint64_t trade_executed_message = 0;
    uint64_t combination_trade_executed_message = 0;
    uint64_t trade_cancellation_message = 0;
    uint64_t equilibrium_price_message = 0;
    uint64_t open_high_low_last_trade_adjustment_message = 0;
    uint64_t market_settlement_message = 0;
    uint64_t text_message = 0;
    uint64_t request_for_quote_message = 0;
    uint64_t anomalous_order_threshold_publish_message = 0;
    uint64_t volume_and_open_interest_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process udp packet: the session layer walks the segment and dispatches
    // each message back to this handler
    void udp() {
        const auto& frame = parser.frame();

        asx::asxderivatives::ntp::itch::v1_05::process_segment(*this, frame.payload, frame.payload_len, parser.source.timestamp_ns(), frame);

        // whatever dispatch did not recognise is unknown
        unknown_messages = total_messages - matched_messages;
    }

    // called once per segment, before any message is dispatched
    asx::asxderivatives::ntp::itch::v1_05::seq_action on_transport_header(const asx::asxderivatives::ntp::itch::v1_05::packet_header& transport, const packet::Frame&) {
        if (transport.message_count.get().value() == 0) {
            ++heartbeats;
            return asx::asxderivatives::ntp::itch::v1_05::seq_action::skip;
        }

        if (transport.message_count.get().value() == 65535) {
            ++heartbeats;
            return asx::asxderivatives::ntp::itch::v1_05::seq_action::skip;
        }

        total_messages += transport.message_count.get().value();

        return asx::asxderivatives::ntp::itch::v1_05::seq_action::process;
    }

    // one overload per dispatched message
    void on_message(const asx::asxderivatives::ntp::itch::v1_05::seconds_message&, std::uint64_t, const asx::asxderivatives::ntp::itch::v1_05::packet_header&)
        { ++seconds_message; ++matched_messages; }
    void on_message(const asx::asxderivatives::ntp::itch::v1_05::end_of_business_trade_date_message&, std::uint64_t, const asx::asxderivatives::ntp::itch::v1_05::packet_header&)
        { ++end_of_business_trade_date_message; ++matched_messages; }
    void on_message(const asx::asxderivatives::ntp::itch::v1_05::future_symbol_directory_message&, std::uint64_t, const asx::asxderivatives::ntp::itch::v1_05::packet_header&)
        { ++future_symbol_directory_message; ++matched_messages; }
    void on_message(const asx::asxderivatives::ntp::itch::v1_05::options_symbol_directory_message&, std::uint64_t, const asx::asxderivatives::ntp::itch::v1_05::packet_header&)
        { ++options_symbol_directory_message; ++matched_messages; }
    void on_message(const asx::asxderivatives::ntp::itch::v1_05::combination_symbol_directory_message&, std::uint64_t, const asx::asxderivatives::ntp::itch::v1_05::packet_header&)
        { ++combination_symbol_directory_message; ++matched_messages; }
    void on_message(const asx::asxderivatives::ntp::itch::v1_05::bundles_symbol_directory&, std::uint64_t, const asx::asxderivatives::ntp::itch::v1_05::packet_header&)
        { ++bundles_symbol_directory; ++matched_messages; }
    void on_message(const asx::asxderivatives::ntp::itch::v1_05::order_book_state_message&, std::uint64_t, const asx::asxderivatives::ntp::itch::v1_05::packet_header&)
        { ++order_book_state_message; ++matched_messages; }
    void on_message(const asx::asxderivatives::ntp::itch::v1_05::add_order_message&, std::uint64_t, const asx::asxderivatives::ntp::itch::v1_05::packet_header&)
        { ++add_order_message; ++matched_messages; }
    void on_message(const asx::asxderivatives::ntp::itch::v1_05::order_volume_cancelled_message&, std::uint64_t, const asx::asxderivatives::ntp::itch::v1_05::packet_header&)
        { ++order_volume_cancelled_message; ++matched_messages; }
    void on_message(const asx::asxderivatives::ntp::itch::v1_05::order_deleted_message&, std::uint64_t, const asx::asxderivatives::ntp::itch::v1_05::packet_header&)
        { ++order_deleted_message; ++matched_messages; }
    void on_message(const asx::asxderivatives::ntp::itch::v1_05::order_executed_message&, std::uint64_t, const asx::asxderivatives::ntp::itch::v1_05::packet_header&)
        { ++order_executed_message; ++matched_messages; }
    void on_message(const asx::asxderivatives::ntp::itch::v1_05::auction_order_executed_message&, std::uint64_t, const asx::asxderivatives::ntp::itch::v1_05::packet_header&)
        { ++auction_order_executed_message; ++matched_messages; }
    void on_message(const asx::asxderivatives::ntp::itch::v1_05::combination_order_executed_message&, std::uint64_t, const asx::asxderivatives::ntp::itch::v1_05::packet_header&)
        { ++combination_order_executed_message; ++matched_messages; }
    void on_message(const asx::asxderivatives::ntp::itch::v1_05::implied_order_added_message&, std::uint64_t, const asx::asxderivatives::ntp::itch::v1_05::packet_header&)
        { ++implied_order_added_message; ++matched_messages; }
    void on_message(const asx::asxderivatives::ntp::itch::v1_05::implied_order_replaced_message&, std::uint64_t, const asx::asxderivatives::ntp::itch::v1_05::packet_header&)
        { ++implied_order_replaced_message; ++matched_messages; }
    void on_message(const asx::asxderivatives::ntp::itch::v1_05::implied_order_deleted_message&, std::uint64_t, const asx::asxderivatives::ntp::itch::v1_05::packet_header&)
        { ++implied_order_deleted_message; ++matched_messages; }
    void on_message(const asx::asxderivatives::ntp::itch::v1_05::trade_executed_message&, std::uint64_t, const asx::asxderivatives::ntp::itch::v1_05::packet_header&)
        { ++trade_executed_message; ++matched_messages; }
    void on_message(const asx::asxderivatives::ntp::itch::v1_05::combination_trade_executed_message&, std::uint64_t, const asx::asxderivatives::ntp::itch::v1_05::packet_header&)
        { ++combination_trade_executed_message; ++matched_messages; }
    void on_message(const asx::asxderivatives::ntp::itch::v1_05::trade_cancellation_message&, std::uint64_t, const asx::asxderivatives::ntp::itch::v1_05::packet_header&)
        { ++trade_cancellation_message; ++matched_messages; }
    void on_message(const asx::asxderivatives::ntp::itch::v1_05::equilibrium_price_message&, std::uint64_t, const asx::asxderivatives::ntp::itch::v1_05::packet_header&)
        { ++equilibrium_price_message; ++matched_messages; }
    void on_message(const asx::asxderivatives::ntp::itch::v1_05::open_high_low_last_trade_adjustment_message&, std::uint64_t, const asx::asxderivatives::ntp::itch::v1_05::packet_header&)
        { ++open_high_low_last_trade_adjustment_message; ++matched_messages; }
    void on_message(const asx::asxderivatives::ntp::itch::v1_05::market_settlement_message&, std::uint64_t, const asx::asxderivatives::ntp::itch::v1_05::packet_header&)
        { ++market_settlement_message; ++matched_messages; }
    void on_message(const asx::asxderivatives::ntp::itch::v1_05::text_message&, std::uint64_t, const asx::asxderivatives::ntp::itch::v1_05::packet_header&)
        { ++text_message; ++matched_messages; }
    void on_message(const asx::asxderivatives::ntp::itch::v1_05::request_for_quote_message&, std::uint64_t, const asx::asxderivatives::ntp::itch::v1_05::packet_header&)
        { ++request_for_quote_message; ++matched_messages; }
    void on_message(const asx::asxderivatives::ntp::itch::v1_05::anomalous_order_threshold_publish_message&, std::uint64_t, const asx::asxderivatives::ntp::itch::v1_05::packet_header&)
        { ++anomalous_order_threshold_publish_message; ++matched_messages; }
    void on_message(const asx::asxderivatives::ntp::itch::v1_05::volume_and_open_interest_message&, std::uint64_t, const asx::asxderivatives::ntp::itch::v1_05::packet_header&)
        { ++volume_and_open_interest_message; ++matched_messages; }

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
        std::cout << "  SecondsMessage (T)                         " << seconds_message << std::endl;
        std::cout << "  EndOfBusinessTradeDateMessage (S)          " << end_of_business_trade_date_message << std::endl;
        std::cout << "  FutureSymbolDirectoryMessage (f)           " << future_symbol_directory_message << std::endl;
        std::cout << "  OptionsSymbolDirectoryMessage (h)          " << options_symbol_directory_message << std::endl;
        std::cout << "  CombinationSymbolDirectoryMessage (M)      " << combination_symbol_directory_message << std::endl;
        std::cout << "  BundlesSymbolDirectory (m)                 " << bundles_symbol_directory << std::endl;
        std::cout << "  OrderBookStateMessage (O)                  " << order_book_state_message << std::endl;
        std::cout << "  AddOrderMessage (A)                        " << add_order_message << std::endl;
        std::cout << "  OrderVolumeCancelledMessage (X)            " << order_volume_cancelled_message << std::endl;
        std::cout << "  OrderDeletedMessage (D)                    " << order_deleted_message << std::endl;
        std::cout << "  OrderExecutedMessage (E)                   " << order_executed_message << std::endl;
        std::cout << "  AuctionOrderExecutedMessage (C)            " << auction_order_executed_message << std::endl;
        std::cout << "  CombinationOrderExecutedMessage (e)        " << combination_order_executed_message << std::endl;
        std::cout << "  ImpliedOrderAddedMessage (j)               " << implied_order_added_message << std::endl;
        std::cout << "  ImpliedOrderReplacedMessage (l)            " << implied_order_replaced_message << std::endl;
        std::cout << "  ImpliedOrderDeletedMessage (k)             " << implied_order_deleted_message << std::endl;
        std::cout << "  TradeExecutedMessage (P)                   " << trade_executed_message << std::endl;
        std::cout << "  CombinationTradeExecutedMessage (p)        " << combination_trade_executed_message << std::endl;
        std::cout << "  TradeCancellationMessage (B)               " << trade_cancellation_message << std::endl;
        std::cout << "  EquilibriumPriceMessage (Z)                " << equilibrium_price_message << std::endl;
        std::cout << "  OpenHighLowLastTradeAdjustmentMessage (t)  " << open_high_low_last_trade_adjustment_message << std::endl;
        std::cout << "  MarketSettlementMessage (Y)                " << market_settlement_message << std::endl;
        std::cout << "  TextMessage (x)                            " << text_message << std::endl;
        std::cout << "  RequestForQuoteMessage (q)                 " << request_for_quote_message << std::endl;
        std::cout << "  AnomalousOrderThresholdPublishMessage (W)  " << anomalous_order_threshold_publish_message << std::endl;
        std::cout << "  VolumeAndOpenInterestMessage (V)           " << volume_and_open_interest_message << std::endl;
    }
};
}
