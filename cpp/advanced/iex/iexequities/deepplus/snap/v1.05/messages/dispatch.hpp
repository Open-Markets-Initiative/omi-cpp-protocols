#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/MessageHeader.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length) {
    (void)length;
    const auto* header = message_header::parse(buffer);

    switch (header->message_type.get().value()) {
        case message_type::enum_type::snapshot_request_message:
            handler.on_message(*snapshot_request_message::parse(buffer));
            break;
        case message_type::enum_type::error_response_message:
            handler.on_message(*error_response_message::parse(buffer));
            break;
        case message_type::enum_type::snapshot_start_message:
            handler.on_message(*snapshot_start_message::parse(buffer));
            break;
        case message_type::enum_type::snapshot_data_message:
            handler.on_message(*snapshot_data_message::parse(buffer));
            break;
        case message_type::enum_type::system_event_message:
            handler.on_message(*system_event_message::parse(buffer));
            break;
        case message_type::enum_type::security_directory_message:
            handler.on_message(*security_directory_message::parse(buffer));
            break;
        case message_type::enum_type::trading_status_message:
            handler.on_message(*trading_status_message::parse(buffer));
            break;
        case message_type::enum_type::retail_liquidity_indicator_message:
            handler.on_message(*retail_liquidity_indicator_message::parse(buffer));
            break;
        case message_type::enum_type::operational_halt_status_message:
            handler.on_message(*operational_halt_status_message::parse(buffer));
            break;
        case message_type::enum_type::short_sale_price_test_status_message:
            handler.on_message(*short_sale_price_test_status_message::parse(buffer));
            break;
        case message_type::enum_type::security_event_message:
            handler.on_message(*security_event_message::parse(buffer));
            break;
        case message_type::enum_type::add_order_message:
            handler.on_message(*add_order_message::parse(buffer));
            break;
        case message_type::enum_type::order_modify_message:
            handler.on_message(*order_modify_message::parse(buffer));
            break;
        case message_type::enum_type::order_delete_message:
            handler.on_message(*order_delete_message::parse(buffer));
            break;
        case message_type::enum_type::order_executed_message:
            handler.on_message(*order_executed_message::parse(buffer));
            break;
        case message_type::enum_type::trade_message:
            handler.on_message(*trade_message::parse(buffer));
            break;
        case message_type::enum_type::trade_break_message:
            handler.on_message(*trade_break_message::parse(buffer));
            break;
        case message_type::enum_type::clear_book_message:
            handler.on_message(*clear_book_message::parse(buffer));
            break;
        case message_type::enum_type::snapshot_end_message:
            handler.on_message(*snapshot_end_message::parse(buffer));
            break;
        default:
            // Unknown message type - handler should implement on_unknown if needed
            break;
    }
}

}
