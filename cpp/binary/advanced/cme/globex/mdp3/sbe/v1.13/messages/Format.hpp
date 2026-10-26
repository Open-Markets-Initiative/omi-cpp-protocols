#pragma once

#include <ostream>
#include <string_view>

#include "MktdataMessage.hpp"
#include "ChannelReset.hpp"
#include "AdminHeartbeat.hpp"
#include "AdminLogin.hpp"
#include "AdminLogout.hpp"
#include "SecurityStatus.hpp"
#include "MdIncrementalRefreshVolume.hpp"
#include "QuoteRequest.hpp"
#include "MdIncrementalRefreshBook.hpp"
#include "MdIncrementalRefreshOrderBook.hpp"
#include "MdIncrementalRefreshTradeSummary.hpp"
#include "MdIncrementalRefreshDailyStatistics.hpp"
#include "MdIncrementalRefreshLimitsBanding.hpp"
#include "MdIncrementalRefreshSessionStatistics.hpp"
#include "SnapshotFullRefresh.hpp"
#include "SnapshotFullRefreshOrderBook.hpp"
#include "MdInstrumentDefinitionFuture.hpp"
#include "MdInstrumentDefinitionOption.hpp"
#include "MdInstrumentDefinitionSpread.hpp"
#include "MdInstrumentDefinitionFixedIncome.hpp"
#include "MdInstrumentDefinitionRepo.hpp"
#include "SnapshotRefreshTopOrders.hpp"
#include "SecurityStatusWorkup.hpp"
#include "SnapshotFullRefreshTcp.hpp"
#include "CollateralMarketValue.hpp"
#include "MdInstrumentDefinitionFx.hpp"
#include "MdIncrementalRefreshBookLongQty.hpp"
#include "MdIncrementalRefreshTradeSummaryLongQty.hpp"
#include "MdIncrementalRefreshVolumeLongQty.hpp"
#include "MdIncrementalRefreshSessionStatisticsLongQty.hpp"
#include "SnapshotFullRefreshTcpLongQty.hpp"
#include "SnapshotFullRefreshLongQty.hpp"
#include "MdpsessionmgmtMessage.hpp"
#include "Negotiate.hpp"
#include "NegotiationReject.hpp"
#include "NegotiationResponse.hpp"
#include "Terminate.hpp"
#include "MarketDataRequest.hpp"
#include "RequestAck.hpp"
#include "RequestReject.hpp"
#include "SecurityListRequest.hpp"
#include "SecurityStatusRequest.hpp"
#include "SubscriberHeartbeat.hpp"
#include "../json/messages/mktdata_message_json.hpp"
#include "../json/messages/channel_reset_json.hpp"
#include "../json/messages/md_incremental_refresh_volume_json.hpp"
#include "../json/messages/quote_request_json.hpp"
#include "../json/messages/md_incremental_refresh_book_json.hpp"
#include "../json/messages/md_incremental_refresh_order_book_json.hpp"
#include "../json/messages/md_incremental_refresh_trade_summary_json.hpp"
#include "../json/messages/md_incremental_refresh_daily_statistics_json.hpp"
#include "../json/messages/md_incremental_refresh_limits_banding_json.hpp"
#include "../json/messages/md_incremental_refresh_session_statistics_json.hpp"
#include "../json/messages/snapshot_full_refresh_json.hpp"
#include "../json/messages/snapshot_full_refresh_order_book_json.hpp"
#include "../json/messages/md_instrument_definition_future_json.hpp"
#include "../json/messages/md_instrument_definition_option_json.hpp"
#include "../json/messages/md_instrument_definition_spread_json.hpp"
#include "../json/messages/md_instrument_definition_fixed_income_json.hpp"
#include "../json/messages/md_instrument_definition_repo_json.hpp"
#include "../json/messages/snapshot_refresh_top_orders_json.hpp"
#include "../json/messages/security_status_workup_json.hpp"
#include "../json/messages/snapshot_full_refresh_tcp_json.hpp"
#include "../json/messages/collateral_market_value_json.hpp"
#include "../json/messages/md_instrument_definition_fx_json.hpp"
#include "../json/messages/md_incremental_refresh_book_long_qty_json.hpp"
#include "../json/messages/md_incremental_refresh_trade_summary_long_qty_json.hpp"
#include "../json/messages/md_incremental_refresh_volume_long_qty_json.hpp"
#include "../json/messages/md_incremental_refresh_session_statistics_long_qty_json.hpp"
#include "../json/messages/snapshot_full_refresh_tcp_long_qty_json.hpp"
#include "../json/messages/snapshot_full_refresh_long_qty_json.hpp"
#include "../json/messages/mdpsessionmgmt_message_json.hpp"
#include "../json/messages/market_data_request_json.hpp"
#include "../json/messages/request_ack_json.hpp"
#include "../json/messages/security_list_request_json.hpp"
#include "../json/messages/security_status_request_json.hpp"

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

inline std::ostream& operator<<(std::ostream& os, const binary_packet_header& value) {
    os << "packet_sequence_number=" << value.packet_sequence_number.get().value()
       << ",sending_time=" << value.sending_time.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "message_size=" << value.message_size.get().value()
       << ",simple_binary_header.block_length=" << value.simple_binary_header.block_length.get().value()
       << ",simple_binary_header.template_id=\"" << sbe_mdp3::template_id::to_string(value.simple_binary_header.template_id.get().value()) << '"'
       << ",simple_binary_header.schema_id=\"" << sbe_mdp3::schema_id::to_string(value.simple_binary_header.schema_id.get().value()) << '"'
       << ",simple_binary_header.version=" << value.simple_binary_header.version.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const channel_reset_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const incremental_refresh_volume_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const related_sym_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const incremental_refresh_book_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const incremental_refresh_book_order_id_groups& value) {
    os << "group_size_8_byte.block_length=" << value.group_size_8_byte.block_length.get().value()
       << ",group_size_8_byte.num_in_group=" << static_cast<unsigned>(value.group_size_8_byte.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const incremental_refresh_order_book_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const incremental_refresh_trade_summary_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const incremental_refresh_trade_summary_order_id_groups& value) {
    os << "group_size_8_byte.block_length=" << value.group_size_8_byte.block_length.get().value()
       << ",group_size_8_byte.num_in_group=" << static_cast<unsigned>(value.group_size_8_byte.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const incremental_refresh_daily_statistics_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const incremental_refresh_limits_banding_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const incremental_refresh_session_statistics_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const snapshot_full_refresh_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const snapshot_full_refresh_order_book_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const events_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const feed_types_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const inst_attrib_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const lot_type_rules_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const option_underlyings_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const option_related_instruments_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const legs_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const repo_underlyings_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const repo_related_instruments_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const broken_dates_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const snapshot_refresh_top_orders_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const security_status_workup_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const snapshot_full_refresh_tcp_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const collateral_market_value_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const fx_lot_type_rules_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trading_sessions_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const incremental_refresh_book_long_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const incremental_refresh_book_long_order_id_groups& value) {
    os << "group_size_8_byte.block_length=" << value.group_size_8_byte.block_length.get().value()
       << ",group_size_8_byte.num_in_group=" << static_cast<unsigned>(value.group_size_8_byte.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const incremental_refresh_trade_summary_long_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const incremental_refresh_trade_summary_long_order_id_groups& value) {
    os << "group_size_8_byte.block_length=" << value.group_size_8_byte.block_length.get().value()
       << ",group_size_8_byte.num_in_group=" << static_cast<unsigned>(value.group_size_8_byte.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const incremental_refresh_volume_long_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const incremental_refresh_session_statistics_long_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const snapshotfull_refresh_tcp_long_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const snapshot_full_refresh_long_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const market_data_request_security_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const market_data_request_related_symbol_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const request_ack_security_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const request_ack_related_symbol_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const security_list_request_security_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const security_list_request_related_symbol_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const security_status_request_security_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const security_status_request_related_symbol_groups& value) {
    os << "group_size.block_length=" << value.group_size.block_length.get().value()
       << ",group_size.num_in_group=" << static_cast<unsigned>(value.group_size.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const client_technical_header& value) {
    os << "encoding_type=" << value.encoding_type.get().value()
       << ",message_sequence_number=" << value.message_sequence_number.get().value()
       << ",tcp_sending_time=" << value.tcp_sending_time.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const server_technical_header& value) {
    os << "encoding_type=" << value.encoding_type.get().value()
       << ",message_sequence_number=" << value.message_sequence_number.get().value()
       << ",tcp_sending_time=" << value.tcp_sending_time.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const simple_binary_header& value) {
    os << "block_length=" << value.block_length.get().value()
       << ",template_id=\"" << sbe_mdp3::template_id::to_string(value.template_id.get().value()) << '"'
       << ",schema_id=\"" << sbe_mdp3::schema_id::to_string(value.schema_id.get().value()) << '"'
       << ",version=" << value.version.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const mktdata_message& msg) {
    os << "tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const channel_reset& msg) {
    os << "transact_time=" << msg.fields.transact_time.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const admin_heartbeat&) {
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const admin_login& msg) {
    os << "heart_bt_int=" << static_cast<int>(msg.fields.heart_bt_int.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const admin_logout& msg) {
    os << "logout_text=\"" << msg.fields.logout_text.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const security_status& msg) {
    os << "transact_time=" << msg.fields.transact_time.get().value()
       << ",security_group=\"" << msg.fields.security_group.get_trimmed().value() << '"'
       << ",asset=\"" << msg.fields.asset.get_trimmed().value() << '"'
       << ",security_id_optional=" << (msg.fields.security_id_optional.get().has_value() ? std::to_string(msg.fields.security_id_optional.get().value()) : std::string_view("null"))
       << ",trade_date=" << (msg.fields.trade_date.get().has_value() ? std::to_string(msg.fields.trade_date.get().value()) : std::string_view("null"))
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",security_trading_status=\"" << sbe_mdp3::security_trading_status::to_string(msg.fields.security_trading_status.get().value()) << '"'
       << ",halt_reason=\"" << sbe_mdp3::halt_reason::to_string(msg.fields.halt_reason.get().value()) << '"'
       << ",security_trading_event=\"" << sbe_mdp3::security_trading_event::to_string(msg.fields.security_trading_event.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const md_incremental_refresh_volume& msg) {
    os << "transact_time=" << msg.fields.transact_time.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const quote_request& msg) {
    os << "transact_time=" << msg.fields.transact_time.get().value()
       << ",quote_req_id=\"" << msg.fields.quote_req_id.get_trimmed().value() << '"'
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const md_incremental_refresh_book& msg) {
    os << "transact_time=" << msg.fields.transact_time.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const md_incremental_refresh_order_book& msg) {
    os << "transact_time=" << msg.fields.transact_time.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const md_incremental_refresh_trade_summary& msg) {
    os << "transact_time=" << msg.fields.transact_time.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const md_incremental_refresh_daily_statistics& msg) {
    os << "transact_time=" << msg.fields.transact_time.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const md_incremental_refresh_limits_banding& msg) {
    os << "transact_time=" << msg.fields.transact_time.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const md_incremental_refresh_session_statistics& msg) {
    os << "transact_time=" << msg.fields.transact_time.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const snapshot_full_refresh& msg) {
    os << "last_msg_seq_num_processed=" << msg.fields.last_msg_seq_num_processed.get().value()
       << ",tot_num_reports=" << msg.fields.tot_num_reports.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",rpt_seq=" << msg.fields.rpt_seq.get().value()
       << ",transact_time=" << msg.fields.transact_time.get().value()
       << ",last_update_time=" << msg.fields.last_update_time.get().value()
       << ",trade_date=" << (msg.fields.trade_date.get().has_value() ? std::to_string(msg.fields.trade_date.get().value()) : std::string_view("null"))
       << ",md_security_trading_status=\"" << sbe_mdp3::md_security_trading_status::to_string(msg.fields.md_security_trading_status.get().value()) << '"'
       << ",high_limit_price=" << (msg.fields.high_limit_price.get().has_value() ? std::to_string(msg.fields.high_limit_price.get().value()) : std::string_view("null"))
       << ",low_limit_price=" << (msg.fields.low_limit_price.get().has_value() ? std::to_string(msg.fields.low_limit_price.get().value()) : std::string_view("null"))
       << ",max_price_variation=" << (msg.fields.max_price_variation.get().has_value() ? std::to_string(msg.fields.max_price_variation.get().value()) : std::string_view("null"))
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const snapshot_full_refresh_order_book& msg) {
    os << "last_msg_seq_num_processed=" << msg.fields.last_msg_seq_num_processed.get().value()
       << ",tot_num_reports=" << msg.fields.tot_num_reports.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",no_chunks=" << msg.fields.no_chunks.get().value()
       << ",current_chunk=" << msg.fields.current_chunk.get().value()
       << ",transact_time=" << msg.fields.transact_time.get().value()
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const md_instrument_definition_future& msg) {
    os << "match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",tot_num_reports_optional=" << (msg.fields.tot_num_reports_optional.get().has_value() ? std::to_string(msg.fields.tot_num_reports_optional.get().value()) : std::string_view("null"))
       << ",security_update_action=\"" << sbe_mdp3::security_update_action::to_string(msg.fields.security_update_action.get().value()) << '"'
       << ",last_update_time=" << msg.fields.last_update_time.get().value()
       << ",md_security_trading_status=\"" << sbe_mdp3::md_security_trading_status::to_string(msg.fields.md_security_trading_status.get().value()) << '"'
       << ",appl_id=" << msg.fields.appl_id.get().value()
       << ",market_segment_id=" << static_cast<unsigned>(msg.fields.market_segment_id.get().value())
       << ",underlying_product=" << static_cast<unsigned>(msg.fields.underlying_product.get().value())
       << ",security_exchange=\"" << msg.fields.security_exchange.get_trimmed().value() << '"'
       << ",security_group=\"" << msg.fields.security_group.get_trimmed().value() << '"'
       << ",asset=\"" << msg.fields.asset.get_trimmed().value() << '"'
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",security_type=\"" << msg.fields.security_type.get_trimmed().value() << '"'
       << ",cfi_code=\"" << msg.fields.cfi_code.get_trimmed().value() << '"'
       << ",maturity_month_year.year=" << (msg.fields.maturity_month_year.year.get().has_value() ? std::to_string(msg.fields.maturity_month_year.year.get().value()) : std::string_view("null"))
       << ",maturity_month_year.month=" << (msg.fields.maturity_month_year.month.get().has_value() ? std::to_string(msg.fields.maturity_month_year.month.get().value()) : std::string_view("null"))
       << ",maturity_month_year.day=" << (msg.fields.maturity_month_year.day.get().has_value() ? std::to_string(msg.fields.maturity_month_year.day.get().value()) : std::string_view("null"))
       << ",maturity_month_year.week=" << (msg.fields.maturity_month_year.week.get().has_value() ? std::to_string(msg.fields.maturity_month_year.week.get().value()) : std::string_view("null"))
       << ",currency=\"" << msg.fields.currency.get_trimmed().value() << '"'
       << ",settl_currency=\"" << msg.fields.settl_currency.get_trimmed().value() << '"'
       << ",match_algorithm=\"" << msg.fields.match_algorithm.get().value() << '"'
       << ",min_trade_vol=" << msg.fields.min_trade_vol.get().value()
       << ",max_trade_vol=" << msg.fields.max_trade_vol.get().value()
       << ",min_price_increment_ex=" << msg.fields.min_price_increment_ex.get().value()
       << ",display_factor=" << msg.fields.display_factor.get().value()
       << ",main_fraction=" << (msg.fields.main_fraction.get().has_value() ? std::to_string(msg.fields.main_fraction.get().value()) : std::string_view("null"))
       << ",sub_fraction=" << (msg.fields.sub_fraction.get().has_value() ? std::to_string(msg.fields.sub_fraction.get().value()) : std::string_view("null"))
       << ",price_display_format=" << (msg.fields.price_display_format.get().has_value() ? std::to_string(msg.fields.price_display_format.get().value()) : std::string_view("null"))
       << ",unit_of_measure=\"" << msg.fields.unit_of_measure.get_trimmed().value() << '"'
       << ",unit_of_measure_qty=" << (msg.fields.unit_of_measure_qty.get().has_value() ? std::to_string(msg.fields.unit_of_measure_qty.get().value()) : std::string_view("null"))
       << ",trading_reference_price=" << (msg.fields.trading_reference_price.get().has_value() ? std::to_string(msg.fields.trading_reference_price.get().value()) : std::string_view("null"))
       << ",settl_price_type=" << static_cast<unsigned>(msg.fields.settl_price_type.get().value())
       << ",open_interest_qty=" << (msg.fields.open_interest_qty.get().has_value() ? std::to_string(msg.fields.open_interest_qty.get().value()) : std::string_view("null"))
       << ",cleared_volume=" << (msg.fields.cleared_volume.get().has_value() ? std::to_string(msg.fields.cleared_volume.get().value()) : std::string_view("null"))
       << ",high_limit_price=" << (msg.fields.high_limit_price.get().has_value() ? std::to_string(msg.fields.high_limit_price.get().value()) : std::string_view("null"))
       << ",low_limit_price=" << (msg.fields.low_limit_price.get().has_value() ? std::to_string(msg.fields.low_limit_price.get().value()) : std::string_view("null"))
       << ",max_price_variation=" << (msg.fields.max_price_variation.get().has_value() ? std::to_string(msg.fields.max_price_variation.get().value()) : std::string_view("null"))
       << ",decay_quantity=" << (msg.fields.decay_quantity.get().has_value() ? std::to_string(msg.fields.decay_quantity.get().value()) : std::string_view("null"))
       << ",decay_start_date=" << (msg.fields.decay_start_date.get().has_value() ? std::to_string(msg.fields.decay_start_date.get().value()) : std::string_view("null"))
       << ",original_contract_size=" << (msg.fields.original_contract_size.get().has_value() ? std::to_string(msg.fields.original_contract_size.get().value()) : std::string_view("null"))
       << ",contract_multiplier=" << (msg.fields.contract_multiplier.get().has_value() ? std::to_string(msg.fields.contract_multiplier.get().value()) : std::string_view("null"))
       << ",contract_multiplier_unit=" << (msg.fields.contract_multiplier_unit.get().has_value() ? std::to_string(msg.fields.contract_multiplier_unit.get().value()) : std::string_view("null"))
       << ",flow_schedule_type=" << (msg.fields.flow_schedule_type.get().has_value() ? std::to_string(msg.fields.flow_schedule_type.get().value()) : std::string_view("null"))
       << ",min_price_increment_amount=" << (msg.fields.min_price_increment_amount.get().has_value() ? std::to_string(msg.fields.min_price_increment_amount.get().value()) : std::string_view("null"))
       << ",user_defined_instrument=\"" << msg.fields.user_defined_instrument.get().value() << '"'
       << ",trading_reference_date=" << (msg.fields.trading_reference_date.get().has_value() ? std::to_string(msg.fields.trading_reference_date.get().value()) : std::string_view("null"))
       << ",instrument_guid=" << (msg.fields.instrument_guid.get().has_value() ? std::to_string(msg.fields.instrument_guid.get().value()) : std::string_view("null"))
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const md_instrument_definition_option& msg) {
    os << "match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",tot_num_reports_optional=" << (msg.fields.tot_num_reports_optional.get().has_value() ? std::to_string(msg.fields.tot_num_reports_optional.get().value()) : std::string_view("null"))
       << ",security_update_action=\"" << sbe_mdp3::security_update_action::to_string(msg.fields.security_update_action.get().value()) << '"'
       << ",last_update_time=" << msg.fields.last_update_time.get().value()
       << ",md_security_trading_status=\"" << sbe_mdp3::md_security_trading_status::to_string(msg.fields.md_security_trading_status.get().value()) << '"'
       << ",appl_id=" << msg.fields.appl_id.get().value()
       << ",market_segment_id=" << static_cast<unsigned>(msg.fields.market_segment_id.get().value())
       << ",underlying_product=" << static_cast<unsigned>(msg.fields.underlying_product.get().value())
       << ",security_exchange=\"" << msg.fields.security_exchange.get_trimmed().value() << '"'
       << ",security_group=\"" << msg.fields.security_group.get_trimmed().value() << '"'
       << ",asset=\"" << msg.fields.asset.get_trimmed().value() << '"'
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",security_type=\"" << msg.fields.security_type.get_trimmed().value() << '"'
       << ",cfi_code=\"" << msg.fields.cfi_code.get_trimmed().value() << '"'
       << ",put_or_call=\"" << sbe_mdp3::put_or_call::to_string(msg.fields.put_or_call.get().value()) << '"'
       << ",maturity_month_year.year=" << (msg.fields.maturity_month_year.year.get().has_value() ? std::to_string(msg.fields.maturity_month_year.year.get().value()) : std::string_view("null"))
       << ",maturity_month_year.month=" << (msg.fields.maturity_month_year.month.get().has_value() ? std::to_string(msg.fields.maturity_month_year.month.get().value()) : std::string_view("null"))
       << ",maturity_month_year.day=" << (msg.fields.maturity_month_year.day.get().has_value() ? std::to_string(msg.fields.maturity_month_year.day.get().value()) : std::string_view("null"))
       << ",maturity_month_year.week=" << (msg.fields.maturity_month_year.week.get().has_value() ? std::to_string(msg.fields.maturity_month_year.week.get().value()) : std::string_view("null"))
       << ",currency=\"" << msg.fields.currency.get_trimmed().value() << '"'
       << ",strike_price=" << (msg.fields.strike_price.get().has_value() ? std::to_string(msg.fields.strike_price.get().value()) : std::string_view("null"))
       << ",strike_currency=\"" << msg.fields.strike_currency.get_trimmed().value() << '"'
       << ",settl_currency=\"" << msg.fields.settl_currency.get_trimmed().value() << '"'
       << ",min_cab_price=" << (msg.fields.min_cab_price.get().has_value() ? std::to_string(msg.fields.min_cab_price.get().value()) : std::string_view("null"))
       << ",match_algorithm=\"" << msg.fields.match_algorithm.get().value() << '"'
       << ",min_trade_vol=" << msg.fields.min_trade_vol.get().value()
       << ",max_trade_vol=" << msg.fields.max_trade_vol.get().value()
       << ",min_price_increment_optional_ex=" << (msg.fields.min_price_increment_optional_ex.get().has_value() ? std::to_string(msg.fields.min_price_increment_optional_ex.get().value()) : std::string_view("null"))
       << ",min_price_increment_amount=" << (msg.fields.min_price_increment_amount.get().has_value() ? std::to_string(msg.fields.min_price_increment_amount.get().value()) : std::string_view("null"))
       << ",display_factor=" << msg.fields.display_factor.get().value()
       << ",tick_rule=" << (msg.fields.tick_rule.get().has_value() ? std::to_string(msg.fields.tick_rule.get().value()) : std::string_view("null"))
       << ",main_fraction=" << (msg.fields.main_fraction.get().has_value() ? std::to_string(msg.fields.main_fraction.get().value()) : std::string_view("null"))
       << ",sub_fraction=" << (msg.fields.sub_fraction.get().has_value() ? std::to_string(msg.fields.sub_fraction.get().value()) : std::string_view("null"))
       << ",price_display_format=" << (msg.fields.price_display_format.get().has_value() ? std::to_string(msg.fields.price_display_format.get().value()) : std::string_view("null"))
       << ",unit_of_measure=\"" << msg.fields.unit_of_measure.get_trimmed().value() << '"'
       << ",unit_of_measure_qty=" << (msg.fields.unit_of_measure_qty.get().has_value() ? std::to_string(msg.fields.unit_of_measure_qty.get().value()) : std::string_view("null"))
       << ",trading_reference_price=" << (msg.fields.trading_reference_price.get().has_value() ? std::to_string(msg.fields.trading_reference_price.get().value()) : std::string_view("null"))
       << ",settl_price_type=" << static_cast<unsigned>(msg.fields.settl_price_type.get().value())
       << ",cleared_volume=" << (msg.fields.cleared_volume.get().has_value() ? std::to_string(msg.fields.cleared_volume.get().value()) : std::string_view("null"))
       << ",open_interest_qty=" << (msg.fields.open_interest_qty.get().has_value() ? std::to_string(msg.fields.open_interest_qty.get().value()) : std::string_view("null"))
       << ",low_limit_price=" << (msg.fields.low_limit_price.get().has_value() ? std::to_string(msg.fields.low_limit_price.get().value()) : std::string_view("null"))
       << ",high_limit_price=" << (msg.fields.high_limit_price.get().has_value() ? std::to_string(msg.fields.high_limit_price.get().value()) : std::string_view("null"))
       << ",user_defined_instrument=\"" << msg.fields.user_defined_instrument.get().value() << '"'
       << ",trading_reference_date=" << (msg.fields.trading_reference_date.get().has_value() ? std::to_string(msg.fields.trading_reference_date.get().value()) : std::string_view("null"))
       << ",instrument_guid=" << (msg.fields.instrument_guid.get().has_value() ? std::to_string(msg.fields.instrument_guid.get().value()) : std::string_view("null"))
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const md_instrument_definition_spread& msg) {
    os << "match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",tot_num_reports_optional=" << (msg.fields.tot_num_reports_optional.get().has_value() ? std::to_string(msg.fields.tot_num_reports_optional.get().value()) : std::string_view("null"))
       << ",security_update_action=\"" << sbe_mdp3::security_update_action::to_string(msg.fields.security_update_action.get().value()) << '"'
       << ",last_update_time=" << msg.fields.last_update_time.get().value()
       << ",md_security_trading_status=\"" << sbe_mdp3::md_security_trading_status::to_string(msg.fields.md_security_trading_status.get().value()) << '"'
       << ",appl_id=" << msg.fields.appl_id.get().value()
       << ",market_segment_id=" << static_cast<unsigned>(msg.fields.market_segment_id.get().value())
       << ",underlying_product_optional=" << (msg.fields.underlying_product_optional.get().has_value() ? std::to_string(msg.fields.underlying_product_optional.get().value()) : std::string_view("null"))
       << ",security_exchange=\"" << msg.fields.security_exchange.get_trimmed().value() << '"'
       << ",security_group=\"" << msg.fields.security_group.get_trimmed().value() << '"'
       << ",asset=\"" << msg.fields.asset.get_trimmed().value() << '"'
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",security_type=\"" << msg.fields.security_type.get_trimmed().value() << '"'
       << ",cfi_code=\"" << msg.fields.cfi_code.get_trimmed().value() << '"'
       << ",maturity_month_year.year=" << (msg.fields.maturity_month_year.year.get().has_value() ? std::to_string(msg.fields.maturity_month_year.year.get().value()) : std::string_view("null"))
       << ",maturity_month_year.month=" << (msg.fields.maturity_month_year.month.get().has_value() ? std::to_string(msg.fields.maturity_month_year.month.get().value()) : std::string_view("null"))
       << ",maturity_month_year.day=" << (msg.fields.maturity_month_year.day.get().has_value() ? std::to_string(msg.fields.maturity_month_year.day.get().value()) : std::string_view("null"))
       << ",maturity_month_year.week=" << (msg.fields.maturity_month_year.week.get().has_value() ? std::to_string(msg.fields.maturity_month_year.week.get().value()) : std::string_view("null"))
       << ",currency=\"" << msg.fields.currency.get_trimmed().value() << '"'
       << ",security_sub_type=\"" << msg.fields.security_sub_type.get_trimmed().value() << '"'
       << ",user_defined_instrument=\"" << msg.fields.user_defined_instrument.get().value() << '"'
       << ",match_algorithm=\"" << msg.fields.match_algorithm.get().value() << '"'
       << ",min_trade_vol=" << msg.fields.min_trade_vol.get().value()
       << ",max_trade_vol=" << msg.fields.max_trade_vol.get().value()
       << ",min_price_increment_optional_ex=" << (msg.fields.min_price_increment_optional_ex.get().has_value() ? std::to_string(msg.fields.min_price_increment_optional_ex.get().value()) : std::string_view("null"))
       << ",display_factor=" << msg.fields.display_factor.get().value()
       << ",price_display_format=" << (msg.fields.price_display_format.get().has_value() ? std::to_string(msg.fields.price_display_format.get().value()) : std::string_view("null"))
       << ",price_ratio=" << (msg.fields.price_ratio.get().has_value() ? std::to_string(msg.fields.price_ratio.get().value()) : std::string_view("null"))
       << ",tick_rule=" << (msg.fields.tick_rule.get().has_value() ? std::to_string(msg.fields.tick_rule.get().value()) : std::string_view("null"))
       << ",unit_of_measure=\"" << msg.fields.unit_of_measure.get_trimmed().value() << '"'
       << ",trading_reference_price=" << (msg.fields.trading_reference_price.get().has_value() ? std::to_string(msg.fields.trading_reference_price.get().value()) : std::string_view("null"))
       << ",settl_price_type=" << static_cast<unsigned>(msg.fields.settl_price_type.get().value())
       << ",open_interest_qty=" << (msg.fields.open_interest_qty.get().has_value() ? std::to_string(msg.fields.open_interest_qty.get().value()) : std::string_view("null"))
       << ",cleared_volume=" << (msg.fields.cleared_volume.get().has_value() ? std::to_string(msg.fields.cleared_volume.get().value()) : std::string_view("null"))
       << ",high_limit_price=" << (msg.fields.high_limit_price.get().has_value() ? std::to_string(msg.fields.high_limit_price.get().value()) : std::string_view("null"))
       << ",low_limit_price=" << (msg.fields.low_limit_price.get().has_value() ? std::to_string(msg.fields.low_limit_price.get().value()) : std::string_view("null"))
       << ",max_price_variation=" << (msg.fields.max_price_variation.get().has_value() ? std::to_string(msg.fields.max_price_variation.get().value()) : std::string_view("null"))
       << ",main_fraction=" << (msg.fields.main_fraction.get().has_value() ? std::to_string(msg.fields.main_fraction.get().value()) : std::string_view("null"))
       << ",sub_fraction=" << (msg.fields.sub_fraction.get().has_value() ? std::to_string(msg.fields.sub_fraction.get().value()) : std::string_view("null"))
       << ",trading_reference_date=" << (msg.fields.trading_reference_date.get().has_value() ? std::to_string(msg.fields.trading_reference_date.get().value()) : std::string_view("null"))
       << ",price_quote_method=\"" << msg.fields.price_quote_method.get_trimmed().value() << '"'
       << ",risk_set=\"" << msg.fields.risk_set.get_trimmed().value() << '"'
       << ",market_set=\"" << msg.fields.market_set.get_trimmed().value() << '"'
       << ",instrument_guid=" << (msg.fields.instrument_guid.get().has_value() ? std::to_string(msg.fields.instrument_guid.get().value()) : std::string_view("null"))
       << ",financial_instrument_full_name=\"" << msg.fields.financial_instrument_full_name.get_trimmed().value() << '"'
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const md_instrument_definition_fixed_income& msg) {
    os << "match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",tot_num_reports_optional=" << (msg.fields.tot_num_reports_optional.get().has_value() ? std::to_string(msg.fields.tot_num_reports_optional.get().value()) : std::string_view("null"))
       << ",security_update_action=\"" << sbe_mdp3::security_update_action::to_string(msg.fields.security_update_action.get().value()) << '"'
       << ",last_update_time=" << msg.fields.last_update_time.get().value()
       << ",md_security_trading_status=\"" << sbe_mdp3::md_security_trading_status::to_string(msg.fields.md_security_trading_status.get().value()) << '"'
       << ",appl_id=" << msg.fields.appl_id.get().value()
       << ",market_segment_id=" << static_cast<unsigned>(msg.fields.market_segment_id.get().value())
       << ",underlying_product=" << static_cast<unsigned>(msg.fields.underlying_product.get().value())
       << ",security_exchange=\"" << msg.fields.security_exchange.get_trimmed().value() << '"'
       << ",security_group=\"" << msg.fields.security_group.get_trimmed().value() << '"'
       << ",asset=\"" << msg.fields.asset.get_trimmed().value() << '"'
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",security_type=\"" << msg.fields.security_type.get_trimmed().value() << '"'
       << ",cfi_code=\"" << msg.fields.cfi_code.get_trimmed().value() << '"'
       << ",currency=\"" << msg.fields.currency.get_trimmed().value() << '"'
       << ",settl_currency=\"" << msg.fields.settl_currency.get_trimmed().value() << '"'
       << ",match_algorithm=\"" << msg.fields.match_algorithm.get().value() << '"'
       << ",min_trade_vol=" << msg.fields.min_trade_vol.get().value()
       << ",max_trade_vol=" << msg.fields.max_trade_vol.get().value()
       << ",min_price_increment_optional_ex=" << (msg.fields.min_price_increment_optional_ex.get().has_value() ? std::to_string(msg.fields.min_price_increment_optional_ex.get().value()) : std::string_view("null"))
       << ",display_factor=" << msg.fields.display_factor.get().value()
       << ",main_fraction=" << (msg.fields.main_fraction.get().has_value() ? std::to_string(msg.fields.main_fraction.get().value()) : std::string_view("null"))
       << ",sub_fraction=" << (msg.fields.sub_fraction.get().has_value() ? std::to_string(msg.fields.sub_fraction.get().value()) : std::string_view("null"))
       << ",price_display_format=" << (msg.fields.price_display_format.get().has_value() ? std::to_string(msg.fields.price_display_format.get().value()) : std::string_view("null"))
       << ",unit_of_measure=\"" << msg.fields.unit_of_measure.get_trimmed().value() << '"'
       << ",unit_of_measure_qty=" << (msg.fields.unit_of_measure_qty.get().has_value() ? std::to_string(msg.fields.unit_of_measure_qty.get().value()) : std::string_view("null"))
       << ",trading_reference_price=" << (msg.fields.trading_reference_price.get().has_value() ? std::to_string(msg.fields.trading_reference_price.get().value()) : std::string_view("null"))
       << ",trading_reference_date=" << (msg.fields.trading_reference_date.get().has_value() ? std::to_string(msg.fields.trading_reference_date.get().value()) : std::string_view("null"))
       << ",high_limit_price=" << (msg.fields.high_limit_price.get().has_value() ? std::to_string(msg.fields.high_limit_price.get().value()) : std::string_view("null"))
       << ",low_limit_price=" << (msg.fields.low_limit_price.get().has_value() ? std::to_string(msg.fields.low_limit_price.get().value()) : std::string_view("null"))
       << ",max_price_variation=" << (msg.fields.max_price_variation.get().has_value() ? std::to_string(msg.fields.max_price_variation.get().value()) : std::string_view("null"))
       << ",min_price_increment_amount=" << (msg.fields.min_price_increment_amount.get().has_value() ? std::to_string(msg.fields.min_price_increment_amount.get().value()) : std::string_view("null"))
       << ",issue_date=" << (msg.fields.issue_date.get().has_value() ? std::to_string(msg.fields.issue_date.get().value()) : std::string_view("null"))
       << ",dated_date=" << (msg.fields.dated_date.get().has_value() ? std::to_string(msg.fields.dated_date.get().value()) : std::string_view("null"))
       << ",maturity_date=" << (msg.fields.maturity_date.get().has_value() ? std::to_string(msg.fields.maturity_date.get().value()) : std::string_view("null"))
       << ",coupon_rate=" << (msg.fields.coupon_rate.get().has_value() ? std::to_string(msg.fields.coupon_rate.get().value()) : std::string_view("null"))
       << ",par_value=" << (msg.fields.par_value.get().has_value() ? std::to_string(msg.fields.par_value.get().value()) : std::string_view("null"))
       << ",coupon_frequency_unit=\"" << msg.fields.coupon_frequency_unit.get_trimmed().value() << '"'
       << ",coupon_frequency_period=" << (msg.fields.coupon_frequency_period.get().has_value() ? std::to_string(msg.fields.coupon_frequency_period.get().value()) : std::string_view("null"))
       << ",coupon_day_count=\"" << msg.fields.coupon_day_count.get_trimmed().value() << '"'
       << ",country_of_issue=\"" << msg.fields.country_of_issue.get_trimmed().value() << '"'
       << ",issuer=\"" << msg.fields.issuer.get_trimmed().value() << '"'
       << ",financial_instrument_full_name=\"" << msg.fields.financial_instrument_full_name.get_trimmed().value() << '"'
       << ",security_alt_id=\"" << msg.fields.security_alt_id.get_trimmed().value() << '"'
       << ",security_alt_id_source=\"" << sbe_mdp3::security_alt_id_source::to_string(msg.fields.security_alt_id_source.get().value()) << '"'
       << ",price_quote_method=\"" << msg.fields.price_quote_method.get_trimmed().value() << '"'
       << ",party_role_clearing_org=\"" << msg.fields.party_role_clearing_org.get_trimmed().value() << '"'
       << ",user_defined_instrument=\"" << msg.fields.user_defined_instrument.get().value() << '"'
       << ",risk_set=\"" << msg.fields.risk_set.get_trimmed().value() << '"'
       << ",market_set=\"" << msg.fields.market_set.get_trimmed().value() << '"'
       << ",instrument_guid=" << (msg.fields.instrument_guid.get().has_value() ? std::to_string(msg.fields.instrument_guid.get().value()) : std::string_view("null"))
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const md_instrument_definition_repo& msg) {
    os << "match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",tot_num_reports_optional=" << (msg.fields.tot_num_reports_optional.get().has_value() ? std::to_string(msg.fields.tot_num_reports_optional.get().value()) : std::string_view("null"))
       << ",security_update_action=\"" << sbe_mdp3::security_update_action::to_string(msg.fields.security_update_action.get().value()) << '"'
       << ",last_update_time=" << msg.fields.last_update_time.get().value()
       << ",md_security_trading_status=\"" << sbe_mdp3::md_security_trading_status::to_string(msg.fields.md_security_trading_status.get().value()) << '"'
       << ",appl_id=" << msg.fields.appl_id.get().value()
       << ",market_segment_id=" << static_cast<unsigned>(msg.fields.market_segment_id.get().value())
       << ",underlying_product=" << static_cast<unsigned>(msg.fields.underlying_product.get().value())
       << ",security_exchange=\"" << msg.fields.security_exchange.get_trimmed().value() << '"'
       << ",security_group=\"" << msg.fields.security_group.get_trimmed().value() << '"'
       << ",asset=\"" << msg.fields.asset.get_trimmed().value() << '"'
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",security_type=\"" << msg.fields.security_type.get_trimmed().value() << '"'
       << ",cfi_code=\"" << msg.fields.cfi_code.get_trimmed().value() << '"'
       << ",currency=\"" << msg.fields.currency.get_trimmed().value() << '"'
       << ",settl_currency=\"" << msg.fields.settl_currency.get_trimmed().value() << '"'
       << ",match_algorithm=\"" << msg.fields.match_algorithm.get().value() << '"'
       << ",min_trade_vol=" << msg.fields.min_trade_vol.get().value()
       << ",max_trade_vol=" << msg.fields.max_trade_vol.get().value()
       << ",min_price_increment_ex=" << msg.fields.min_price_increment_ex.get().value()
       << ",display_factor=" << msg.fields.display_factor.get().value()
       << ",unit_of_measure=\"" << msg.fields.unit_of_measure.get_trimmed().value() << '"'
       << ",unit_of_measure_qty=" << (msg.fields.unit_of_measure_qty.get().has_value() ? std::to_string(msg.fields.unit_of_measure_qty.get().value()) : std::string_view("null"))
       << ",trading_reference_price=" << (msg.fields.trading_reference_price.get().has_value() ? std::to_string(msg.fields.trading_reference_price.get().value()) : std::string_view("null"))
       << ",trading_reference_date=" << (msg.fields.trading_reference_date.get().has_value() ? std::to_string(msg.fields.trading_reference_date.get().value()) : std::string_view("null"))
       << ",high_limit_price=" << (msg.fields.high_limit_price.get().has_value() ? std::to_string(msg.fields.high_limit_price.get().value()) : std::string_view("null"))
       << ",low_limit_price=" << (msg.fields.low_limit_price.get().has_value() ? std::to_string(msg.fields.low_limit_price.get().value()) : std::string_view("null"))
       << ",max_price_variation=" << (msg.fields.max_price_variation.get().has_value() ? std::to_string(msg.fields.max_price_variation.get().value()) : std::string_view("null"))
       << ",financial_instrument_full_name=\"" << msg.fields.financial_instrument_full_name.get_trimmed().value() << '"'
       << ",party_role_clearing_org=\"" << msg.fields.party_role_clearing_org.get_trimmed().value() << '"'
       << ",start_date=" << (msg.fields.start_date.get().has_value() ? std::to_string(msg.fields.start_date.get().value()) : std::string_view("null"))
       << ",end_date=" << (msg.fields.end_date.get().has_value() ? std::to_string(msg.fields.end_date.get().value()) : std::string_view("null"))
       << ",termination_type=\"" << msg.fields.termination_type.get_trimmed().value() << '"'
       << ",repo_sub_type=\"" << sbe_mdp3::repo_sub_type::to_string(msg.fields.repo_sub_type.get().value()) << '"'
       << ",money_or_par=\"" << sbe_mdp3::money_or_par::to_string(msg.fields.money_or_par.get().value()) << '"'
       << ",max_no_of_substitutions=" << static_cast<unsigned>(msg.fields.max_no_of_substitutions.get().value())
       << ",price_quote_method=\"" << msg.fields.price_quote_method.get_trimmed().value() << '"'
       << ",user_defined_instrument=\"" << msg.fields.user_defined_instrument.get().value() << '"'
       << ",risk_set=\"" << msg.fields.risk_set.get_trimmed().value() << '"'
       << ",market_set=\"" << msg.fields.market_set.get_trimmed().value() << '"'
       << ",instrument_guid=" << (msg.fields.instrument_guid.get().has_value() ? std::to_string(msg.fields.instrument_guid.get().value()) : std::string_view("null"))
       << ",term_code=\"" << msg.fields.term_code.get_trimmed().value() << '"'
       << ",broken_date_term_type=" << (msg.fields.broken_date_term_type.get().has_value() ? std::to_string(msg.fields.broken_date_term_type.get().value()) : std::string_view("null"))
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const snapshot_refresh_top_orders& msg) {
    os << "transact_time=" << msg.fields.transact_time.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const security_status_workup& msg) {
    os << "transact_time=" << msg.fields.transact_time.get().value()
       << ",md_entry_px_optional_ex=" << (msg.fields.md_entry_px_optional_ex.get().has_value() ? std::to_string(msg.fields.md_entry_px_optional_ex.get().value()) : std::string_view("null"))
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",trade_date=" << (msg.fields.trade_date.get().has_value() ? std::to_string(msg.fields.trade_date.get().value()) : std::string_view("null"))
       << ",trade_link_id=" << msg.fields.trade_link_id.get().value()
       << ",workup_trading_status=\"" << sbe_mdp3::workup_trading_status::to_string(msg.fields.workup_trading_status.get().value()) << '"'
       << ",halt_reason=\"" << sbe_mdp3::halt_reason::to_string(msg.fields.halt_reason.get().value()) << '"'
       << ",security_trading_event=\"" << sbe_mdp3::security_trading_event::to_string(msg.fields.security_trading_event.get().value()) << '"'
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const snapshot_full_refresh_tcp& msg) {
    os << "transact_time=" << msg.fields.transact_time.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",high_limit_price=" << (msg.fields.high_limit_price.get().has_value() ? std::to_string(msg.fields.high_limit_price.get().value()) : std::string_view("null"))
       << ",low_limit_price=" << (msg.fields.low_limit_price.get().has_value() ? std::to_string(msg.fields.low_limit_price.get().value()) : std::string_view("null"))
       << ",max_price_variation=" << (msg.fields.max_price_variation.get().has_value() ? std::to_string(msg.fields.max_price_variation.get().value()) : std::string_view("null"))
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const collateral_market_value& msg) {
    os << "transact_time=" << msg.fields.transact_time.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const md_instrument_definition_fx& msg) {
    os << "match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",tot_num_reports_optional=" << (msg.fields.tot_num_reports_optional.get().has_value() ? std::to_string(msg.fields.tot_num_reports_optional.get().value()) : std::string_view("null"))
       << ",security_update_action=\"" << sbe_mdp3::security_update_action::to_string(msg.fields.security_update_action.get().value()) << '"'
       << ",last_update_time=" << msg.fields.last_update_time.get().value()
       << ",md_security_trading_status=\"" << sbe_mdp3::md_security_trading_status::to_string(msg.fields.md_security_trading_status.get().value()) << '"'
       << ",appl_id=" << msg.fields.appl_id.get().value()
       << ",market_segment_id=" << static_cast<unsigned>(msg.fields.market_segment_id.get().value())
       << ",underlying_product=" << static_cast<unsigned>(msg.fields.underlying_product.get().value())
       << ",security_exchange=\"" << msg.fields.security_exchange.get_trimmed().value() << '"'
       << ",security_group=\"" << msg.fields.security_group.get_trimmed().value() << '"'
       << ",asset=\"" << msg.fields.asset.get_trimmed().value() << '"'
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",security_type=\"" << msg.fields.security_type.get_trimmed().value() << '"'
       << ",cfi_code=\"" << msg.fields.cfi_code.get_trimmed().value() << '"'
       << ",currency=\"" << msg.fields.currency.get_trimmed().value() << '"'
       << ",settl_currency=\"" << msg.fields.settl_currency.get_trimmed().value() << '"'
       << ",price_quote_currency=\"" << msg.fields.price_quote_currency.get_trimmed().value() << '"'
       << ",match_algorithm=\"" << msg.fields.match_algorithm.get().value() << '"'
       << ",min_trade_vol=" << msg.fields.min_trade_vol.get().value()
       << ",max_trade_vol=" << msg.fields.max_trade_vol.get().value()
       << ",min_price_increment_ex=" << msg.fields.min_price_increment_ex.get().value()
       << ",display_factor=" << msg.fields.display_factor.get().value()
       << ",price_precision=" << static_cast<unsigned>(msg.fields.price_precision.get().value())
       << ",unit_of_measure=\"" << msg.fields.unit_of_measure.get_trimmed().value() << '"'
       << ",unit_of_measure_qty=" << (msg.fields.unit_of_measure_qty.get().has_value() ? std::to_string(msg.fields.unit_of_measure_qty.get().value()) : std::string_view("null"))
       << ",high_limit_price=" << (msg.fields.high_limit_price.get().has_value() ? std::to_string(msg.fields.high_limit_price.get().value()) : std::string_view("null"))
       << ",low_limit_price=" << (msg.fields.low_limit_price.get().has_value() ? std::to_string(msg.fields.low_limit_price.get().value()) : std::string_view("null"))
       << ",max_price_variation=" << (msg.fields.max_price_variation.get().has_value() ? std::to_string(msg.fields.max_price_variation.get().value()) : std::string_view("null"))
       << ",user_defined_instrument=\"" << msg.fields.user_defined_instrument.get().value() << '"'
       << ",financial_instrument_full_name=\"" << msg.fields.financial_instrument_full_name.get_trimmed().value() << '"'
       << ",fx_currency_symbol=\"" << msg.fields.fx_currency_symbol.get_trimmed().value() << '"'
       << ",settl_type=\"" << msg.fields.settl_type.get_trimmed().value() << '"'
       << ",intervening_days=" << msg.fields.intervening_days.get().value()
       << ",fx_benchmark_rate_fix=\"" << msg.fields.fx_benchmark_rate_fix.get_trimmed().value() << '"'
       << ",rate_source=\"" << msg.fields.rate_source.get_trimmed().value() << '"'
       << ",fix_rate_local_time=\"" << msg.fields.fix_rate_local_time.get_trimmed().value() << '"'
       << ",fix_rate_local_time_zone=\"" << msg.fields.fix_rate_local_time_zone.get_trimmed().value() << '"'
       << ",min_quote_life=" << msg.fields.min_quote_life.get().value()
       << ",max_price_discretion_offset=" << msg.fields.max_price_discretion_offset.get().value()
       << ",instrument_guid=" << (msg.fields.instrument_guid.get().has_value() ? std::to_string(msg.fields.instrument_guid.get().value()) : std::string_view("null"))
       << ",maturity_month_year.year=" << (msg.fields.maturity_month_year.year.get().has_value() ? std::to_string(msg.fields.maturity_month_year.year.get().value()) : std::string_view("null"))
       << ",maturity_month_year.month=" << (msg.fields.maturity_month_year.month.get().has_value() ? std::to_string(msg.fields.maturity_month_year.month.get().value()) : std::string_view("null"))
       << ",maturity_month_year.day=" << (msg.fields.maturity_month_year.day.get().has_value() ? std::to_string(msg.fields.maturity_month_year.day.get().value()) : std::string_view("null"))
       << ",maturity_month_year.week=" << (msg.fields.maturity_month_year.week.get().has_value() ? std::to_string(msg.fields.maturity_month_year.week.get().value()) : std::string_view("null"))
       << ",settlement_locale=\"" << msg.fields.settlement_locale.get_trimmed().value() << '"'
       << ",alt_min_price_increment=" << (msg.fields.alt_min_price_increment.get().has_value() ? std::to_string(msg.fields.alt_min_price_increment.get().value()) : std::string_view("null"))
       << ",alt_min_quote_life=" << (msg.fields.alt_min_quote_life.get().has_value() ? std::to_string(msg.fields.alt_min_quote_life.get().value()) : std::string_view("null"))
       << ",alt_price_increment_constraint=" << (msg.fields.alt_price_increment_constraint.get().has_value() ? std::to_string(msg.fields.alt_price_increment_constraint.get().value()) : std::string_view("null"))
       << ",max_bid_ask_constraint=" << (msg.fields.max_bid_ask_constraint.get().has_value() ? std::to_string(msg.fields.max_bid_ask_constraint.get().value()) : std::string_view("null"))
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const md_incremental_refresh_book_long_qty& msg) {
    os << "transact_time=" << msg.fields.transact_time.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const md_incremental_refresh_trade_summary_long_qty& msg) {
    os << "transact_time=" << msg.fields.transact_time.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const md_incremental_refresh_volume_long_qty& msg) {
    os << "transact_time=" << msg.fields.transact_time.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const md_incremental_refresh_session_statistics_long_qty& msg) {
    os << "transact_time=" << msg.fields.transact_time.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const snapshot_full_refresh_tcp_long_qty& msg) {
    os << "transact_time=" << msg.fields.transact_time.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",high_limit_price=" << (msg.fields.high_limit_price.get().has_value() ? std::to_string(msg.fields.high_limit_price.get().value()) : std::string_view("null"))
       << ",low_limit_price=" << (msg.fields.low_limit_price.get().has_value() ? std::to_string(msg.fields.low_limit_price.get().value()) : std::string_view("null"))
       << ",max_price_variation=" << (msg.fields.max_price_variation.get().has_value() ? std::to_string(msg.fields.max_price_variation.get().value()) : std::string_view("null"))
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const snapshot_full_refresh_long_qty& msg) {
    os << "last_msg_seq_num_processed=" << msg.fields.last_msg_seq_num_processed.get().value()
       << ",tot_num_reports=" << msg.fields.tot_num_reports.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",rpt_seq=" << msg.fields.rpt_seq.get().value()
       << ",transact_time=" << msg.fields.transact_time.get().value()
       << ",last_update_time=" << msg.fields.last_update_time.get().value()
       << ",trade_date=" << (msg.fields.trade_date.get().has_value() ? std::to_string(msg.fields.trade_date.get().value()) : std::string_view("null"))
       << ",md_security_trading_status=\"" << sbe_mdp3::md_security_trading_status::to_string(msg.fields.md_security_trading_status.get().value()) << '"'
       << ",high_limit_price=" << (msg.fields.high_limit_price.get().has_value() ? std::to_string(msg.fields.high_limit_price.get().value()) : std::string_view("null"))
       << ",low_limit_price=" << (msg.fields.low_limit_price.get().has_value() ? std::to_string(msg.fields.low_limit_price.get().value()) : std::string_view("null"))
       << ",max_price_variation=" << (msg.fields.max_price_variation.get().has_value() ? std::to_string(msg.fields.max_price_variation.get().value()) : std::string_view("null"))
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const mdpsessionmgmt_message& msg) {
    os << "tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const negotiate& msg) {
    os << "hmac_signature=\"" << msg.fields.hmac_signature.get_trimmed().value() << '"'
       << ",access_key_id=\"" << msg.fields.access_key_id.get_trimmed().value() << '"'
       << ",uuid=" << msg.fields.uuid.get().value()
       << ",request_timestamp=" << msg.fields.request_timestamp.get().value()
       << ",session=\"" << msg.fields.session.get_trimmed().value() << '"'
       << ",firm=\"" << msg.fields.firm.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const negotiation_reject& msg) {
    os << "reason=\"" << msg.fields.reason.get_trimmed().value() << '"'
       << ",uuid=" << msg.fields.uuid.get().value()
       << ",request_timestamp=" << msg.fields.request_timestamp.get().value()
       << ",error_codes=\"" << sbe_mdp3::error_codes::to_string(msg.fields.error_codes.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const negotiation_response& msg) {
    os << "uuid=" << msg.fields.uuid.get().value()
       << ",request_timestamp=" << msg.fields.request_timestamp.get().value()
       << ",secret_key_secure_id_expiration=" << (msg.fields.secret_key_secure_id_expiration.get().has_value() ? std::to_string(msg.fields.secret_key_secure_id_expiration.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const terminate& msg) {
    os << "reason=\"" << msg.fields.reason.get_trimmed().value() << '"'
       << ",uuid=" << msg.fields.uuid.get().value()
       << ",request_timestamp=" << msg.fields.request_timestamp.get().value()
       << ",error_codes=\"" << sbe_mdp3::error_codes::to_string(msg.fields.error_codes.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const market_data_request& msg) {
    os << "md_req_id=" << msg.fields.md_req_id.get().value()
       << ",subscription_req_type=\"" << sbe_mdp3::subscription_req_type::to_string(msg.fields.subscription_req_type.get().value()) << '"'
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const request_ack& msg) {
    os << "md_req_id=" << msg.fields.md_req_id.get().value()
       << ",subscription_req_type=\"" << sbe_mdp3::subscription_req_type::to_string(msg.fields.subscription_req_type.get().value()) << '"'
       << ",md_req_id_status=\"" << sbe_mdp3::md_req_id_status::to_string(msg.fields.md_req_id_status.get().value()) << '"'
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const request_reject& msg) {
    os << "md_req_id_optional=" << (msg.fields.md_req_id_optional.get().has_value() ? std::to_string(msg.fields.md_req_id_optional.get().value()) : std::string_view("null"))
       << ",md_req_rej_reason=\"" << sbe_mdp3::md_req_rej_reason::to_string(msg.fields.md_req_rej_reason.get().value()) << '"'
       << ",text=\"" << msg.fields.text.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const security_list_request& msg) {
    os << "md_req_id=" << msg.fields.md_req_id.get().value()
       << ",subscription_req_type=\"" << sbe_mdp3::subscription_req_type::to_string(msg.fields.subscription_req_type.get().value()) << '"'
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const security_status_request& msg) {
    os << "md_req_id=" << msg.fields.md_req_id.get().value()
       << ",subscription_req_type=\"" << sbe_mdp3::subscription_req_type::to_string(msg.fields.subscription_req_type.get().value()) << '"'
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const subscriber_heartbeat&) {
    return os;
}

}
