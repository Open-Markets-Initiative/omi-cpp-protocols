// Databento.MarketData.Normalized.Dbn.v3: messages/dispatch.hpp
#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/RecordHeader.hpp"
#include "../structs/Record.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length, std::uint64_t packet_receive_time, const record& transport) {
    (void)length;
    const auto* header = record_header::parse(buffer);

    switch (header->rtype.get().value()) {
        case rtype::enum_type::market_by_price_0:
            handler.on_message(*trade_msg::parse(buffer), packet_receive_time, transport);
            break;
        case rtype::enum_type::market_by_price_1:
            handler.on_message(*mbp_1_msg::parse(buffer), packet_receive_time, transport);
            break;
        case rtype::enum_type::market_by_price_10:
            handler.on_message(*mbp_10_msg::parse(buffer), packet_receive_time, transport);
            break;
        case rtype::enum_type::ohlcv_deprecated:
        case rtype::enum_type::ohlcv_1_second:
        case rtype::enum_type::ohlcv_1_minute:
        case rtype::enum_type::ohlcv_1_hour:
        case rtype::enum_type::ohlcv_1_day:
        case rtype::enum_type::ohlcv_end_of_day:
            handler.on_message(*ohlcv_msg::parse(buffer), packet_receive_time, transport);
            break;
        case rtype::enum_type::status:
            handler.on_message(*status_msg::parse(buffer), packet_receive_time, transport);
            break;
        case rtype::enum_type::instrument_definition:
            handler.on_message(*instrument_def_msg::parse(buffer), packet_receive_time, transport);
            break;
        case rtype::enum_type::imbalance:
            handler.on_message(*imbalance_msg::parse(buffer), packet_receive_time, transport);
            break;
        case rtype::enum_type::error:
            handler.on_message(*error_msg::parse(buffer), packet_receive_time, transport);
            break;
        case rtype::enum_type::symbol_mapping:
            handler.on_message(*symbol_mapping_msg::parse(buffer), packet_receive_time, transport);
            break;
        case rtype::enum_type::system:
            handler.on_message(*system_msg::parse(buffer), packet_receive_time, transport);
            break;
        case rtype::enum_type::statistics:
            handler.on_message(*stat_msg::parse(buffer), packet_receive_time, transport);
            break;
        case rtype::enum_type::market_by_order:
            handler.on_message(*mbo_msg::parse(buffer), packet_receive_time, transport);
            break;
        case rtype::enum_type::consolidated_market_by_price_1:
        case rtype::enum_type::trade_with_consolidated_bbo:
            handler.on_message(*cmbp_1_msg::parse(buffer), packet_receive_time, transport);
            break;
        case rtype::enum_type::consolidated_bbo_1_second:
        case rtype::enum_type::consolidated_bbo_1_minute:
            handler.on_message(*cbbo_msg::parse(buffer), packet_receive_time, transport);
            break;
        case rtype::enum_type::bbo_1_second:
        case rtype::enum_type::bbo_1_minute:
            handler.on_message(*bbo_msg::parse(buffer), packet_receive_time, transport);
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
