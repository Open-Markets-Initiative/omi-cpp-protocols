#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/MessageHeader.hpp"
#include "../structs/PacketHeader.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length, std::uint64_t packet_receive_time, const packet_header& transport) {
    (void)length;
    const auto* header = message_header::parse(buffer);

    switch (header->message_type.get().value()) {
        case message_type::enum_type::system_event_message:
            handler.on_message(*system_event_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::trade_report_message:
            handler.on_message(*trade_report_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::long_form_trade_report_message:
            handler.on_message(*long_form_trade_report_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::next_shares_trade_report_message:
            handler.on_message(*next_shares_trade_report_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::trade_cancel_error_message:
            handler.on_message(*trade_cancel_error_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::long_form_trade_cancel_error_message:
            handler.on_message(*long_form_trade_cancel_error_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::next_shares_trade_cancel_error_message:
            handler.on_message(*next_shares_trade_cancel_error_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::trade_correction_message:
            handler.on_message(*trade_correction_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::long_form_trade_correction_message:
            handler.on_message(*long_form_trade_correction_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::next_shares_trade_correction_message:
            handler.on_message(*next_shares_trade_correction_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::stock_trading_action_message:
            handler.on_message(*stock_trading_action_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::stock_directory_message:
            handler.on_message(*stock_directory_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::reg_sho_short_sale_price_test_restricted_indicator_message:
            handler.on_message(*reg_sho_short_sale_price_test_restricted_indicator_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::adjusted_closing_price_message:
            handler.on_message(*adjusted_closing_price_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::long_form_adjusted_closing_price_message:
            handler.on_message(*long_form_adjusted_closing_price_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::end_of_day_trade_summary_message:
            handler.on_message(*end_of_day_trade_summary_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::long_form_end_of_day_trade_summary_message:
            handler.on_message(*long_form_end_of_day_trade_summary_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::next_shares_end_of_day_trade_summary_message:
            handler.on_message(*next_shares_end_of_day_trade_summary_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::ipo_information_message:
            handler.on_message(*ipo_information_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::mwcb_decline_level_message:
            handler.on_message(*mwcb_decline_level_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::mwcb_status_message:
            handler.on_message(*mwcb_status_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::ipo_quoting_period_update_message:
            handler.on_message(*ipo_quoting_period_update_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::operational_halt_message:
            handler.on_message(*operational_halt_message::parse(buffer), packet_receive_time, transport);
            break;
        default:
            // a code none of the messages answer to: the handler is told when it wants to be
            if constexpr (requires { handler.on_unknown(buffer, length, packet_receive_time, transport); }) {
                handler.on_unknown(buffer, length, packet_receive_time, transport);
            }
            break;
    }
}

}
