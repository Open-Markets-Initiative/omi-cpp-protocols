// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: messages/dispatch.hpp
#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/MessageHeader.hpp"
#include "../structs/PacketHeader.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length, std::uint64_t packet_receive_time, const packet_header& transport) {
    (void)length;
    const auto* header = message_header::parse(buffer);

    switch (header->template_id.get().value()) {
        case template_id::enum_type::security_definition_message:
            handler.on_message(*security_definition_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::current_market_refresh_message:
            handler.on_message(*current_market_refresh_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::market_data_refresh_message:
            handler.on_message(*market_data_refresh_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::current_market_update_message:
            handler.on_message(*current_market_update_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::recap_update_message:
            handler.on_message(*recap_update_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::ticker_message:
            handler.on_message(*ticker_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::expected_opening_price_and_size_message:
            handler.on_message(*expected_opening_price_and_size_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::index_value_message:
            handler.on_message(*index_value_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::settlement_value_message:
            handler.on_message(*settlement_value_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::summary_message:
            handler.on_message(*summary_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::market_data_control_message:
            handler.on_message(*market_data_control_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::heartbeat_message:
            handler.on_message(*heartbeat_message::parse(buffer), packet_receive_time, transport);
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
