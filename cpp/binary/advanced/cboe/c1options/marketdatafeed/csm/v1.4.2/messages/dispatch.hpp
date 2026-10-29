#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/MessageHeader.hpp"
#include "../structs/PacketHeader.hpp"

#include "SecurityDefinitionMessage.hpp"
#include "CurrentMarketRefreshMessage.hpp"
#include "MarketDataRefreshMessage.hpp"
#include "CurrentMarketUpdateMessage.hpp"
#include "RecapUpdateMessage.hpp"
#include "TickerMessage.hpp"
#include "ExpectedOpeningPriceAndSizeMessage.hpp"
#include "IndexValueMessage.hpp"
#include "SettlementValueMessage.hpp"
#include "SummaryMessage.hpp"
#include "MarketDataControlMessage.hpp"
#include "HeartbeatMessage.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
std::size_t dispatch(Handler& handler, const std::byte* buffer, std::size_t length, std::uint64_t packet_receive_time, const packet_header& transport) {
    (void)length;
    const auto* header = message_header::parse(buffer);

    switch (header->template_id.get().value()) {
        case template_id::enum_type::security_definition_message: {
            const auto* msg = security_definition_message::parse(buffer);
            handler.on_message(*msg, packet_receive_time, transport);
            return sizeof(security_definition_message);
        }
        case template_id::enum_type::current_market_refresh_message: {
            const auto* msg = current_market_refresh_message::parse(buffer);
            handler.on_message(*msg, packet_receive_time, transport);
            return sizeof(current_market_refresh_message);
        }
        case template_id::enum_type::market_data_refresh_message: {
            const auto* msg = market_data_refresh_message::parse(buffer);
            handler.on_message(*msg, packet_receive_time, transport);
            return sizeof(market_data_refresh_message);
        }
        case template_id::enum_type::current_market_update_message: {
            const auto* msg = current_market_update_message::parse(buffer);
            handler.on_message(*msg, packet_receive_time, transport);
            return sizeof(current_market_update_message);
        }
        case template_id::enum_type::recap_update_message: {
            const auto* msg = recap_update_message::parse(buffer);
            handler.on_message(*msg, packet_receive_time, transport);
            return sizeof(recap_update_message);
        }
        case template_id::enum_type::ticker_message: {
            const auto* msg = ticker_message::parse(buffer);
            handler.on_message(*msg, packet_receive_time, transport);
            return sizeof(ticker_message);
        }
        case template_id::enum_type::expected_opening_price_and_size_message: {
            const auto* msg = expected_opening_price_and_size_message::parse(buffer);
            handler.on_message(*msg, packet_receive_time, transport);
            return sizeof(expected_opening_price_and_size_message);
        }
        case template_id::enum_type::index_value_message: {
            const auto* msg = index_value_message::parse(buffer);
            handler.on_message(*msg, packet_receive_time, transport);
            return sizeof(index_value_message);
        }
        case template_id::enum_type::settlement_value_message: {
            const auto* msg = settlement_value_message::parse(buffer);
            handler.on_message(*msg, packet_receive_time, transport);
            return sizeof(settlement_value_message);
        }
        case template_id::enum_type::summary_message: {
            const auto* msg = summary_message::parse(buffer);
            handler.on_message(*msg, packet_receive_time, transport);
            return sizeof(summary_message);
        }
        case template_id::enum_type::market_data_control_message: {
            const auto* msg = market_data_control_message::parse(buffer);
            handler.on_message(*msg, packet_receive_time, transport);
            return sizeof(market_data_control_message);
        }
        case template_id::enum_type::heartbeat_message: {
            const auto* msg = heartbeat_message::parse(buffer);
            handler.on_message(*msg, packet_receive_time, transport);
            return sizeof(heartbeat_message);
        }
        default:
            return 0;
            break;
    }
}

}
