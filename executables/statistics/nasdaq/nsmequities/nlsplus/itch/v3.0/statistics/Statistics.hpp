#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/binary/advanced/nasdaq/nsmequities/nlsplus/itch/v3.0/messages/session.hpp"

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
    uint64_t trade_report_message = 0;
    uint64_t long_form_trade_report_message = 0;
    uint64_t next_shares_trade_report_message = 0;
    uint64_t trade_cancel_error_message = 0;
    uint64_t long_form_trade_cancel_error_message = 0;
    uint64_t next_shares_trade_cancel_error_message = 0;
    uint64_t trade_correction_message = 0;
    uint64_t long_form_trade_correction_message = 0;
    uint64_t next_shares_trade_correction_message = 0;
    uint64_t stock_trading_action_message = 0;
    uint64_t stock_directory_message = 0;
    uint64_t reg_sho_short_sale_price_test_restricted_indicator_message = 0;
    uint64_t adjusted_closing_price_message = 0;
    uint64_t long_form_adjusted_closing_price_message = 0;
    uint64_t end_of_day_trade_summary_message = 0;
    uint64_t long_form_end_of_day_trade_summary_message = 0;
    uint64_t next_shares_end_of_day_trade_summary_message = 0;
    uint64_t ipo_information_message = 0;
    uint64_t mwcb_decline_level_message = 0;
    uint64_t mwcb_status_message = 0;
    uint64_t ipo_quoting_period_update_message = 0;
    uint64_t operational_halt_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process udp packet: the session layer walks the segment and dispatches
    // each message back to this handler
    void udp() {
        const auto& frame = parser.frame();

        nasdaq::nsmequities::nlsplus::itch::v3_0::process_segment(*this, frame.payload, frame.payload_len, parser.source.timestamp_ns(), frame);

        // whatever dispatch did not recognise is unknown
        unknown_messages = total_messages - matched_messages;
    }

    // called once per segment, before any message is dispatched
    nasdaq::nsmequities::nlsplus::itch::v3_0::seq_action on_transport_header(const nasdaq::nsmequities::nlsplus::itch::v3_0::packet_header& transport, const packet::Frame&) {
        if (transport.message_count.get().value() == 0) {
            ++heartbeats;
            return nasdaq::nsmequities::nlsplus::itch::v3_0::seq_action::skip;
        }

        if (transport.message_count.get().value() == 65535) {
            ++heartbeats;
            return nasdaq::nsmequities::nlsplus::itch::v3_0::seq_action::skip;
        }

        total_messages += transport.message_count.get().value();

        return nasdaq::nsmequities::nlsplus::itch::v3_0::seq_action::process;
    }

    // one overload per dispatched message
    void on_message(const nasdaq::nsmequities::nlsplus::itch::v3_0::system_event_message&, std::uint64_t, const nasdaq::nsmequities::nlsplus::itch::v3_0::packet_header&)
        { ++system_event_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::nlsplus::itch::v3_0::trade_report_message&, std::uint64_t, const nasdaq::nsmequities::nlsplus::itch::v3_0::packet_header&)
        { ++trade_report_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::nlsplus::itch::v3_0::long_form_trade_report_message&, std::uint64_t, const nasdaq::nsmequities::nlsplus::itch::v3_0::packet_header&)
        { ++long_form_trade_report_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::nlsplus::itch::v3_0::next_shares_trade_report_message&, std::uint64_t, const nasdaq::nsmequities::nlsplus::itch::v3_0::packet_header&)
        { ++next_shares_trade_report_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::nlsplus::itch::v3_0::trade_cancel_error_message&, std::uint64_t, const nasdaq::nsmequities::nlsplus::itch::v3_0::packet_header&)
        { ++trade_cancel_error_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::nlsplus::itch::v3_0::long_form_trade_cancel_error_message&, std::uint64_t, const nasdaq::nsmequities::nlsplus::itch::v3_0::packet_header&)
        { ++long_form_trade_cancel_error_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::nlsplus::itch::v3_0::next_shares_trade_cancel_error_message&, std::uint64_t, const nasdaq::nsmequities::nlsplus::itch::v3_0::packet_header&)
        { ++next_shares_trade_cancel_error_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::nlsplus::itch::v3_0::trade_correction_message&, std::uint64_t, const nasdaq::nsmequities::nlsplus::itch::v3_0::packet_header&)
        { ++trade_correction_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::nlsplus::itch::v3_0::long_form_trade_correction_message&, std::uint64_t, const nasdaq::nsmequities::nlsplus::itch::v3_0::packet_header&)
        { ++long_form_trade_correction_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::nlsplus::itch::v3_0::next_shares_trade_correction_message&, std::uint64_t, const nasdaq::nsmequities::nlsplus::itch::v3_0::packet_header&)
        { ++next_shares_trade_correction_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::nlsplus::itch::v3_0::stock_trading_action_message&, std::uint64_t, const nasdaq::nsmequities::nlsplus::itch::v3_0::packet_header&)
        { ++stock_trading_action_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::nlsplus::itch::v3_0::stock_directory_message&, std::uint64_t, const nasdaq::nsmequities::nlsplus::itch::v3_0::packet_header&)
        { ++stock_directory_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::nlsplus::itch::v3_0::reg_sho_short_sale_price_test_restricted_indicator_message&, std::uint64_t, const nasdaq::nsmequities::nlsplus::itch::v3_0::packet_header&)
        { ++reg_sho_short_sale_price_test_restricted_indicator_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::nlsplus::itch::v3_0::adjusted_closing_price_message&, std::uint64_t, const nasdaq::nsmequities::nlsplus::itch::v3_0::packet_header&)
        { ++adjusted_closing_price_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::nlsplus::itch::v3_0::long_form_adjusted_closing_price_message&, std::uint64_t, const nasdaq::nsmequities::nlsplus::itch::v3_0::packet_header&)
        { ++long_form_adjusted_closing_price_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::nlsplus::itch::v3_0::end_of_day_trade_summary_message&, std::uint64_t, const nasdaq::nsmequities::nlsplus::itch::v3_0::packet_header&)
        { ++end_of_day_trade_summary_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::nlsplus::itch::v3_0::long_form_end_of_day_trade_summary_message&, std::uint64_t, const nasdaq::nsmequities::nlsplus::itch::v3_0::packet_header&)
        { ++long_form_end_of_day_trade_summary_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::nlsplus::itch::v3_0::next_shares_end_of_day_trade_summary_message&, std::uint64_t, const nasdaq::nsmequities::nlsplus::itch::v3_0::packet_header&)
        { ++next_shares_end_of_day_trade_summary_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::nlsplus::itch::v3_0::ipo_information_message&, std::uint64_t, const nasdaq::nsmequities::nlsplus::itch::v3_0::packet_header&)
        { ++ipo_information_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::nlsplus::itch::v3_0::mwcb_decline_level_message&, std::uint64_t, const nasdaq::nsmequities::nlsplus::itch::v3_0::packet_header&)
        { ++mwcb_decline_level_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::nlsplus::itch::v3_0::mwcb_status_message&, std::uint64_t, const nasdaq::nsmequities::nlsplus::itch::v3_0::packet_header&)
        { ++mwcb_status_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::nlsplus::itch::v3_0::ipo_quoting_period_update_message&, std::uint64_t, const nasdaq::nsmequities::nlsplus::itch::v3_0::packet_header&)
        { ++ipo_quoting_period_update_message; ++matched_messages; }
    void on_message(const nasdaq::nsmequities::nlsplus::itch::v3_0::operational_halt_message&, std::uint64_t, const nasdaq::nsmequities::nlsplus::itch::v3_0::packet_header&)
        { ++operational_halt_message; ++matched_messages; }

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
        std::cout << "  SystemEventMessage (S)                                  " << system_event_message << std::endl;
        std::cout << "  TradeReportMessage (T)                                  " << trade_report_message << std::endl;
        std::cout << "  LongFormTradeReportMessage (t)                          " << long_form_trade_report_message << std::endl;
        std::cout << "  NextSharesTradeReportMessage (M)                        " << next_shares_trade_report_message << std::endl;
        std::cout << "  TradeCancelErrorMessage (X)                             " << trade_cancel_error_message << std::endl;
        std::cout << "  LongFormTradeCancelErrorMessage (x)                     " << long_form_trade_cancel_error_message << std::endl;
        std::cout << "  NextSharesTradeCancelErrorMessage (O)                   " << next_shares_trade_cancel_error_message << std::endl;
        std::cout << "  TradeCorrectionMessage (C)                              " << trade_correction_message << std::endl;
        std::cout << "  LongFormTradeCorrectionMessage (c)                      " << long_form_trade_correction_message << std::endl;
        std::cout << "  NextSharesTradeCorrectionMessage (Z)                    " << next_shares_trade_correction_message << std::endl;
        std::cout << "  StockTradingActionMessage (H)                           " << stock_trading_action_message << std::endl;
        std::cout << "  StockDirectoryMessage (R)                               " << stock_directory_message << std::endl;
        std::cout << "  RegShoShortSalePriceTestRestrictedIndicatorMessage (Y)  " << reg_sho_short_sale_price_test_restricted_indicator_message << std::endl;
        std::cout << "  AdjustedClosingPriceMessage (G)                         " << adjusted_closing_price_message << std::endl;
        std::cout << "  LongFormAdjustedClosingPriceMessage (g)                 " << long_form_adjusted_closing_price_message << std::endl;
        std::cout << "  EndOfDayTradeSummaryMessage (J)                         " << end_of_day_trade_summary_message << std::endl;
        std::cout << "  LongFormEndOfDayTradeSummaryMessage (j)                 " << long_form_end_of_day_trade_summary_message << std::endl;
        std::cout << "  NextSharesEndOfDayTradeSummaryMessage (N)               " << next_shares_end_of_day_trade_summary_message << std::endl;
        std::cout << "  IpoInformationMessage (I)                               " << ipo_information_message << std::endl;
        std::cout << "  MwcbDeclineLevelMessage (V)                             " << mwcb_decline_level_message << std::endl;
        std::cout << "  MwcbStatusMessage (W)                                   " << mwcb_status_message << std::endl;
        std::cout << "  IpoQuotingPeriodUpdateMessage (K)                       " << ipo_quoting_period_update_message << std::endl;
        std::cout << "  OperationalHaltMessage (h)                              " << operational_halt_message << std::endl;
    }
};
}
