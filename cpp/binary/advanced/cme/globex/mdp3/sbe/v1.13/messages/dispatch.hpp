#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/SimpleBinaryHeader.hpp"
#include "../structs/BinaryPacketHeader.hpp"
#include "../types/MessageSize.hpp"

namespace cme::mdp3::v13 {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length, std::uint64_t packet_receive_time, const binary_packet_header& transport) {
    (void)length;

    switch (mktdata_message::parse(buffer)->header.simple_binary_header.schema_id.get().value()) {
        case schema_id::enum_type::mktdata: {
            switch (channel_reset::parse(buffer)->header.simple_binary_header.template_id.get().value()) {
                case template_id::enum_type::channel_reset:
                    handler.on_message(*channel_reset::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::admin_heartbeat:
                    handler.on_message(*admin_heartbeat::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::admin_login:
                    handler.on_message(*admin_login::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::admin_logout:
                    handler.on_message(*admin_logout::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::security_status:
                    handler.on_message(*security_status::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::md_incremental_refresh_volume:
                    handler.on_message(*md_incremental_refresh_volume::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::quote_request:
                    handler.on_message(*quote_request::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::md_incremental_refresh_book:
                    handler.on_message(*md_incremental_refresh_book::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::md_incremental_refresh_order_book:
                    handler.on_message(*md_incremental_refresh_order_book::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::md_incremental_refresh_trade_summary:
                    handler.on_message(*md_incremental_refresh_trade_summary::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::md_incremental_refresh_daily_statistics:
                    handler.on_message(*md_incremental_refresh_daily_statistics::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::md_incremental_refresh_limits_banding:
                    handler.on_message(*md_incremental_refresh_limits_banding::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::md_incremental_refresh_session_statistics:
                    handler.on_message(*md_incremental_refresh_session_statistics::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::snapshot_full_refresh:
                    handler.on_message(*snapshot_full_refresh::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::snapshot_full_refresh_order_book:
                    handler.on_message(*snapshot_full_refresh_order_book::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::md_instrument_definition_future:
                    handler.on_message(*md_instrument_definition_future::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::md_instrument_definition_option:
                    handler.on_message(*md_instrument_definition_option::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::md_instrument_definition_spread:
                    handler.on_message(*md_instrument_definition_spread::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::md_instrument_definition_fixed_income:
                    handler.on_message(*md_instrument_definition_fixed_income::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::md_instrument_definition_repo:
                    handler.on_message(*md_instrument_definition_repo::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::snapshot_refresh_top_orders:
                    handler.on_message(*snapshot_refresh_top_orders::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::security_status_workup:
                    handler.on_message(*security_status_workup::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::snapshot_full_refresh_tcp:
                    handler.on_message(*snapshot_full_refresh_tcp::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::collateral_market_value:
                    handler.on_message(*collateral_market_value::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::md_instrument_definition_fx:
                    handler.on_message(*md_instrument_definition_fx::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::md_incremental_refresh_book_long_qty:
                    handler.on_message(*md_incremental_refresh_book_long_qty::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::md_incremental_refresh_trade_summary_long_qty:
                    handler.on_message(*md_incremental_refresh_trade_summary_long_qty::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::md_incremental_refresh_volume_long_qty:
                    handler.on_message(*md_incremental_refresh_volume_long_qty::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::md_incremental_refresh_session_statistics_long_qty:
                    handler.on_message(*md_incremental_refresh_session_statistics_long_qty::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::snapshot_full_refresh_tcp_long_qty:
                    handler.on_message(*snapshot_full_refresh_tcp_long_qty::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::snapshot_full_refresh_long_qty:
                    handler.on_message(*snapshot_full_refresh_long_qty::parse(buffer), packet_receive_time, transport);
                    break;
                default:
                    // none of the messages it carries: the Mktdata Message itself
                    handler.on_message(*mktdata_message::parse(buffer), packet_receive_time, transport);
                    break;
            }
            break;
        }
        case schema_id::enum_type::mdpsessionmgmt: {
            switch (negotiate::parse(buffer)->header.simple_binary_header.template_id.get().value()) {
                case template_id::enum_type::negotiate:
                    handler.on_message(*negotiate::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::negotiation_reject:
                    handler.on_message(*negotiation_reject::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::negotiation_response:
                    handler.on_message(*negotiation_response::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::terminate:
                    handler.on_message(*terminate::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::market_data_request:
                    handler.on_message(*market_data_request::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::request_ack:
                    handler.on_message(*request_ack::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::request_reject:
                    handler.on_message(*request_reject::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::security_list_request:
                    handler.on_message(*security_list_request::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::security_status_request:
                    handler.on_message(*security_status_request::parse(buffer), packet_receive_time, transport);
                    break;
                case template_id::enum_type::subscriber_heartbeat:
                    handler.on_message(*subscriber_heartbeat::parse(buffer), packet_receive_time, transport);
                    break;
                default:
                    // none of the messages it carries: the Mdpsessionmgmt Message itself
                    handler.on_message(*mdpsessionmgmt_message::parse(buffer), packet_receive_time, transport);
                    break;
            }
            break;
        }
        default:
            // a code none of the messages answer to: the handler is told when it wants to be
            if constexpr (requires { handler.on_unknown(buffer, length, packet_receive_time, transport); }) {
                handler.on_unknown(buffer, length, packet_receive_time, transport);
            }
            break;
    }
}

}
