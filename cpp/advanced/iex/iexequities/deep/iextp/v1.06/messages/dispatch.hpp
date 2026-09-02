#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/MessageHeader.hpp"
#include "../structs/IextpHeader.hpp"

namespace iex::iexequities::deep::iextp::v1_06 {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length, std::uint64_t packet_receive_time, const iextp_header& transport) {
    (void)length;
    const auto* header = message_header::parse(buffer);

    switch (header->message_type.get().value()) {
        case message_type::enum_type::system_event_message:
            handler.on_message(*system_event_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::security_directory_message:
            handler.on_message(*security_directory_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::trading_status_message:
            handler.on_message(*trading_status_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::operational_halt_status_message:
            handler.on_message(*operational_halt_status_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::short_sale_price_test_status_message:
            handler.on_message(*short_sale_price_test_status_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::security_event_message:
            handler.on_message(*security_event_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::price_level_buy_update_message:
            handler.on_message(*price_level_buy_update_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::price_level_sell_update_message:
            handler.on_message(*price_level_sell_update_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::trade_report_message:
            handler.on_message(*trade_report_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::official_price_message:
            handler.on_message(*official_price_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::trade_break_message:
            handler.on_message(*trade_break_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::auction_information_message:
            handler.on_message(*auction_information_message::parse(buffer), packet_receive_time, transport);
            break;
        default:
            // Unknown message type - handler should implement on_unknown if needed
            break;
    }
}

}
