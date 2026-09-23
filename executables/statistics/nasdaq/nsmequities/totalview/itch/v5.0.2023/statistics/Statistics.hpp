#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/advanced/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/session.hpp"

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
    uint64_t debug_packet = 0;
    uint64_t login_request_packet = 0;
    uint64_t unsequenced_data_packet = 0;
    uint64_t login_accepted_packet = 0;
    uint64_t login_rejected_packet = 0;
    uint64_t sequenced_data_packet = 0;
    uint64_t system_event_message = 0;
    uint64_t stock_directory_message = 0;
    uint64_t stock_trading_action_message = 0;
    uint64_t reg_sho_short_sale_price_test_restricted_indicator_message = 0;
    uint64_t market_participant_position_message = 0;
    uint64_t mwcb_decline_level_message = 0;
    uint64_t mwcb_status_level_message = 0;
    uint64_t ipo_quoting_period_update = 0;
    uint64_t luld_auction_collar_message = 0;
    uint64_t operational_halt_message = 0;
    uint64_t add_order_no_mpid_attribution_message = 0;
    uint64_t add_order_with_mpid_attribution_message = 0;
    uint64_t order_executed_message = 0;
    uint64_t order_executed_with_price_message = 0;
    uint64_t order_cancel_message = 0;
    uint64_t order_delete_message = 0;
    uint64_t order_replace_message = 0;
    uint64_t non_cross_trade_message = 0;
    uint64_t cross_trade_message = 0;
    uint64_t broken_trade_message = 0;
    uint64_t net_order_imbalance_indicator_message = 0;
    uint64_t retail_price_improvement_indicator_message = 0;
    uint64_t direct_listing_with_capital_raise_price_discovery_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process udp packet: the session layer walks the segment and dispatches
    // each message back to this handler
    void udp() {
        const auto& frame = parser.frame();

        nasdaq::nsmequities::totalview::itch::v5_0_2023::process_segment(*this, frame.payload, frame.payload_len, parser.source.timestamp_ns(), frame);

        // whatever dispatch did not recognise is unknown
        unknown_messages = total_messages - matched_messages;
    }

    // called once per segment, before any message is dispatched
    nasdaq::nsmequities::totalview::itch::v5_0_2023::seq_action on_transport_header(const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header& transport, const packet::Frame&) {
        if (transport.message_count.get().value() == 0) {
            ++heartbeats;
            return nasdaq::nsmequities::totalview::itch::v5_0_2023::seq_action::skip;
        }

        if (transport.message_count.get().value() == 65535) {
            ++heartbeats;
            return nasdaq::nsmequities::totalview::itch::v5_0_2023::seq_action::skip;
        }

        total_messages += transport.message_count.get().value();

        return nasdaq::nsmequities::totalview::itch::v5_0_2023::seq_action::process;
    }

    // one overload per dispatched message
    void on_message(const nasdaq::nsmequities::totalview::itch::v5_0_2023::debug_packet&, std::uint64_t, const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header&)
        { ++debug_packet; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::totalview::itch::v5_0_2023::login_request_packet&, std::uint64_t, const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header&)
        { ++login_request_packet; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::totalview::itch::v5_0_2023::unsequenced_data_packet&, std::uint64_t, const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header&)
        { ++unsequenced_data_packet; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::totalview::itch::v5_0_2023::login_accepted_packet&, std::uint64_t, const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header&)
        { ++login_accepted_packet; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::totalview::itch::v5_0_2023::login_rejected_packet&, std::uint64_t, const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header&)
        { ++login_rejected_packet; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::totalview::itch::v5_0_2023::sequenced_data_packet&, std::uint64_t, const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header&)
        { ++sequenced_data_packet; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::totalview::itch::v5_0_2023::system_event_message&, std::uint64_t, const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header&)
        { ++system_event_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::totalview::itch::v5_0_2023::stock_directory_message&, std::uint64_t, const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header&)
        { ++stock_directory_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::totalview::itch::v5_0_2023::stock_trading_action_message&, std::uint64_t, const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header&)
        { ++stock_trading_action_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::totalview::itch::v5_0_2023::reg_sho_short_sale_price_test_restricted_indicator_message&, std::uint64_t, const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header&)
        { ++reg_sho_short_sale_price_test_restricted_indicator_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::totalview::itch::v5_0_2023::market_participant_position_message&, std::uint64_t, const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header&)
        { ++market_participant_position_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::totalview::itch::v5_0_2023::mwcb_decline_level_message&, std::uint64_t, const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header&)
        { ++mwcb_decline_level_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::totalview::itch::v5_0_2023::mwcb_status_level_message&, std::uint64_t, const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header&)
        { ++mwcb_status_level_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::totalview::itch::v5_0_2023::ipo_quoting_period_update&, std::uint64_t, const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header&)
        { ++ipo_quoting_period_update; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::totalview::itch::v5_0_2023::luld_auction_collar_message&, std::uint64_t, const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header&)
        { ++luld_auction_collar_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::totalview::itch::v5_0_2023::operational_halt_message&, std::uint64_t, const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header&)
        { ++operational_halt_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::totalview::itch::v5_0_2023::add_order_no_mpid_attribution_message&, std::uint64_t, const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header&)
        { ++add_order_no_mpid_attribution_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::totalview::itch::v5_0_2023::add_order_with_mpid_attribution_message&, std::uint64_t, const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header&)
        { ++add_order_with_mpid_attribution_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::totalview::itch::v5_0_2023::order_executed_message&, std::uint64_t, const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header&)
        { ++order_executed_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::totalview::itch::v5_0_2023::order_executed_with_price_message&, std::uint64_t, const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header&)
        { ++order_executed_with_price_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::totalview::itch::v5_0_2023::order_cancel_message&, std::uint64_t, const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header&)
        { ++order_cancel_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::totalview::itch::v5_0_2023::order_delete_message&, std::uint64_t, const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header&)
        { ++order_delete_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::totalview::itch::v5_0_2023::order_replace_message&, std::uint64_t, const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header&)
        { ++order_replace_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::totalview::itch::v5_0_2023::non_cross_trade_message&, std::uint64_t, const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header&)
        { ++non_cross_trade_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::totalview::itch::v5_0_2023::cross_trade_message&, std::uint64_t, const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header&)
        { ++cross_trade_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::totalview::itch::v5_0_2023::broken_trade_message&, std::uint64_t, const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header&)
        { ++broken_trade_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::totalview::itch::v5_0_2023::net_order_imbalance_indicator_message&, std::uint64_t, const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header&)
        { ++net_order_imbalance_indicator_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::totalview::itch::v5_0_2023::retail_price_improvement_indicator_message&, std::uint64_t, const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header&)
        { ++retail_price_improvement_indicator_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::totalview::itch::v5_0_2023::direct_listing_with_capital_raise_price_discovery_message&, std::uint64_t, const nasdaq::nsmequities::totalview::itch::v5_0_2023::packet_header&)
        { ++direct_listing_with_capital_raise_price_discovery_message; ++matched_messages; }

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
        std::cout << "  DebugPacket                                             " << debug_packet << std::endl;
        std::cout << "  LoginRequestPacket (L)                                  " << login_request_packet << std::endl;
        std::cout << "  UnsequencedDataPacket                                   " << unsequenced_data_packet << std::endl;
        std::cout << "  LoginAcceptedPacket                                     " << login_accepted_packet << std::endl;
        std::cout << "  LoginRejectedPacket                                     " << login_rejected_packet << std::endl;
        std::cout << "  SequencedDataPacket                                     " << sequenced_data_packet << std::endl;
        std::cout << "  SystemEventMessage (S)                                  " << system_event_message << std::endl;
        std::cout << "  StockDirectoryMessage (R)                               " << stock_directory_message << std::endl;
        std::cout << "  StockTradingActionMessage (H)                           " << stock_trading_action_message << std::endl;
        std::cout << "  RegShoShortSalePriceTestRestrictedIndicatorMessage (Y)  " << reg_sho_short_sale_price_test_restricted_indicator_message << std::endl;
        std::cout << "  MarketParticipantPositionMessage (L)                    " << market_participant_position_message << std::endl;
        std::cout << "  MwcbDeclineLevelMessage (V)                             " << mwcb_decline_level_message << std::endl;
        std::cout << "  MwcbStatusLevelMessage (W)                              " << mwcb_status_level_message << std::endl;
        std::cout << "  IpoQuotingPeriodUpdate (K)                              " << ipo_quoting_period_update << std::endl;
        std::cout << "  LuldAuctionCollarMessage (J)                            " << luld_auction_collar_message << std::endl;
        std::cout << "  OperationalHaltMessage (h)                              " << operational_halt_message << std::endl;
        std::cout << "  AddOrderNoMpidAttributionMessage (A)                    " << add_order_no_mpid_attribution_message << std::endl;
        std::cout << "  AddOrderWithMpidAttributionMessage (F)                  " << add_order_with_mpid_attribution_message << std::endl;
        std::cout << "  OrderExecutedMessage (E)                                " << order_executed_message << std::endl;
        std::cout << "  OrderExecutedWithPriceMessage (C)                       " << order_executed_with_price_message << std::endl;
        std::cout << "  OrderCancelMessage (X)                                  " << order_cancel_message << std::endl;
        std::cout << "  OrderDeleteMessage (D)                                  " << order_delete_message << std::endl;
        std::cout << "  OrderReplaceMessage (U)                                 " << order_replace_message << std::endl;
        std::cout << "  NonCrossTradeMessage (P)                                " << non_cross_trade_message << std::endl;
        std::cout << "  CrossTradeMessage (Q)                                   " << cross_trade_message << std::endl;
        std::cout << "  BrokenTradeMessage (B)                                  " << broken_trade_message << std::endl;
        std::cout << "  NetOrderImbalanceIndicatorMessage (I)                   " << net_order_imbalance_indicator_message << std::endl;
        std::cout << "  RetailPriceImprovementIndicatorMessage (N)              " << retail_price_improvement_indicator_message << std::endl;
        std::cout << "  DirectListingWithCapitalRaisePriceDiscoveryMessage (O)  " << direct_listing_with_capital_raise_price_discovery_message << std::endl;
    }
};
}
