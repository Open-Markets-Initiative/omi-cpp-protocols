#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/MessageHeader.hpp"
#include "../structs/PacketHeader.hpp"
#include "../types/MessageLength.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length, std::uint64_t packet_receive_time, const packet_header& transport) {
    (void)length;
    const auto* header = message_header::parse(buffer + sizeof(sbe_binaryumdf::message_length));

    switch (header->template_id.get().value()) {
        case template_id::enum_type::sequence_reset_1_message:
            handler.on_message(*sequence_reset_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::sequence_2_message:
            handler.on_message(*sequence_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::empty_book_9_message:
            handler.on_message(*empty_book_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::channel_reset_11_message:
            handler.on_message(*channel_reset_11_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::security_status_3_message:
            handler.on_message(*security_status_3_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::security_group_phase_10_message:
            handler.on_message(*security_group_phase_10_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::deprecatedsecurity_definition_message:
            handler.on_message(*deprecated_security_definition_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::security_definition_message:
            handler.on_message(*security_definition_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::news_5_message:
            handler.on_message(*news_5_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::opening_price_15_message:
            handler.on_message(*opening_price_15_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::theoretical_opening_price_16_message:
            handler.on_message(*theoretical_opening_price_16_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::closing_price_17_message:
            handler.on_message(*closing_price_17_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::auction_imbalance_19_message:
            handler.on_message(*auction_imbalance_19_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::price_band_20_message:
            handler.on_message(*price_band_20_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::quantity_band_21_message:
            handler.on_message(*quantity_band_21_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::price_band_22_message:
            handler.on_message(*price_band_22_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::high_price_24_message:
            handler.on_message(*high_price_24_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::low_price_25_message:
            handler.on_message(*low_price_25_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::last_trade_price_27_message:
            handler.on_message(*last_trade_price_27_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::settlement_price_28_message:
            handler.on_message(*settlement_price_28_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::open_interest_29_message:
            handler.on_message(*open_interest_29_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::snapshot_full_refresh_header_30_message:
            handler.on_message(*snapshot_full_refresh_header_30_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::order_mb_o_50_message:
            handler.on_message(*order_mb_o_50_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::delete_order_mb_o_51_message:
            handler.on_message(*delete_order_mb_o_51_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::mass_delete_orders_mb_o_52_message:
            handler.on_message(*mass_delete_orders_mb_o_52_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::trade_53_message:
            handler.on_message(*trade_53_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::forward_trade_54_message:
            handler.on_message(*forward_trade_54_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::execution_summary_55_message:
            handler.on_message(*execution_summary_55_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::execution_statistics_56_message:
            handler.on_message(*execution_statistics_56_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::trade_bust_57_message:
            handler.on_message(*trade_bust_57_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::snapshot_full_refresh_orders_mb_o_71_message:
            handler.on_message(*snapshot_full_refresh_orders_mb_o_71_message::parse(buffer), packet_receive_time, transport);
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
