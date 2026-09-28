#pragma once

#include <ostream>
#include <string_view>

#include "SequenceResetMessage.hpp"
#include "SequenceMessage.hpp"
#include "SecurityStatus3Message.hpp"
#include "SecurityGroupPhase10Message.hpp"
#include "DeprecatedSecurityDefinitionMessage.hpp"
#include "News5Message.hpp"
#include "EmptyBookMessage.hpp"
#include "ChannelReset11Message.hpp"
#include "OpeningPrice15Message.hpp"
#include "TheoreticalOpeningPrice16Message.hpp"
#include "ClosingPrice17Message.hpp"
#include "AuctionImbalance19Message.hpp"
#include "PriceBand20Message.hpp"
#include "QuantityBand21Message.hpp"
#include "HighPrice24Message.hpp"
#include "LowPrice25Message.hpp"
#include "LastTradePrice27Message.hpp"
#include "SnapshotFullRefreshHeader30Message.hpp"
#include "OrderMbO50Message.hpp"
#include "DeleteOrderMbO51Message.hpp"
#include "MassDeleteOrdersMbO52Message.hpp"
#include "Trade53Message.hpp"
#include "ForwardTrade54Message.hpp"
#include "ExecutionSummary55Message.hpp"
#include "ExecutionStatistics56Message.hpp"
#include "TradeBust57Message.hpp"
#include "SnapshotFullRefreshOrdersMbO71Message.hpp"
#include "../json/messages/deprecated_security_definition_message_json.hpp"
#include "../json/messages/news_5_message_json.hpp"
#include "../json/messages/snapshot_full_refresh_orders_mb_o_71_message_json.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v1_6;

inline std::ostream& operator<<(std::ostream& os, const packet_header& value) {
    os << "channel_id=" << static_cast<unsigned>(value.channel_id.get().value())
       << ",packet_reserved=" << static_cast<unsigned>(value.packet_reserved.get().value())
       << ",sequence_version=" << value.sequence_version.get().value()
       << ",sequence_number=" << value.sequence_number.get().value()
       << ",sending_time=" << value.sending_time.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message& value) {
    os << "framing_header.message_length=" << value.framing_header.message_length.get().value()
       << ",framing_header.encoding_type=" << value.framing_header.encoding_type.get().value()
       << ",message_header.block_length=" << value.message_header.block_length.get().value()
       << ",message_header.template_id=\"" << sbe_binaryumdf::template_id::to_string(value.message_header.template_id.get().value()) << '"'
       << ",message_header.schema_id=" << value.message_header.schema_id.get().value()
       << ",message_header.version=" << value.message_header.version.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "block_length=" << value.block_length.get().value()
       << ",template_id=\"" << sbe_binaryumdf::template_id::to_string(value.template_id.get().value()) << '"'
       << ",schema_id=" << value.schema_id.get().value()
       << ",version=" << value.version.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const deprecated_underlyings_groups& value) {
    os << "group_size_encoding.block_length=" << value.group_size_encoding.block_length.get().value()
       << ",group_size_encoding.num_in_group=" << static_cast<unsigned>(value.group_size_encoding.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const deprecated_legs_groups& value) {
    os << "group_size_encoding.block_length=" << value.group_size_encoding.block_length.get().value()
       << ",group_size_encoding.num_in_group=" << static_cast<unsigned>(value.group_size_encoding.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const deprecated_instr_attribs_groups& value) {
    os << "group_size_encoding.block_length=" << value.group_size_encoding.block_length.get().value()
       << ",group_size_encoding.num_in_group=" << static_cast<unsigned>(value.group_size_encoding.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups& value) {
    os << "group_size_encoding.block_length=" << value.group_size_encoding.block_length.get().value()
       << ",group_size_encoding.num_in_group=" << static_cast<unsigned>(value.group_size_encoding.num_in_group.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const sequence_reset_message&) {
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const sequence_message& msg) {
    os << "next_seq_no=" << msg.fields.next_seq_no.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const security_status_3_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",trading_session_id=\"" << sbe_binaryumdf::trading_session_id::to_string(msg.fields.trading_session_id.get().value()) << '"'
       << ",security_trading_status=\"" << sbe_binaryumdf::security_trading_status::to_string(msg.fields.security_trading_status.get().value()) << '"'
       << ",security_trading_event=\"" << sbe_binaryumdf::security_trading_event::to_string(msg.fields.security_trading_event.get().value()) << '"'
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",trad_ses_open_time=" << (msg.fields.trad_ses_open_time.get().has_value() ? std::to_string(msg.fields.trad_ses_open_time.get().value()) : std::string_view("null"))
       << ",transact_time=" << (msg.fields.transact_time.get().has_value() ? std::to_string(msg.fields.transact_time.get().value()) : std::string_view("null"))
       << ",rpt_seq=" << (msg.fields.rpt_seq.get().has_value() ? std::to_string(msg.fields.rpt_seq.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const security_group_phase_10_message& msg) {
    os << "security_group=\"" << msg.fields.security_group.get_trimmed().value() << '"'
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",trading_session_id=\"" << sbe_binaryumdf::trading_session_id::to_string(msg.fields.trading_session_id.get().value()) << '"'
       << ",trading_session_sub_id=\"" << sbe_binaryumdf::trading_session_sub_id::to_string(msg.fields.trading_session_sub_id.get().value()) << '"'
       << ",security_trading_event=\"" << sbe_binaryumdf::security_trading_event::to_string(msg.fields.security_trading_event.get().value()) << '"'
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",trad_ses_open_time=" << (msg.fields.trad_ses_open_time.get().has_value() ? std::to_string(msg.fields.trad_ses_open_time.get().value()) : std::string_view("null"))
       << ",transact_time=" << (msg.fields.transact_time.get().has_value() ? std::to_string(msg.fields.transact_time.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const deprecated_security_definition_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",security_exchange=\"" << msg.fields.security_exchange.get_trimmed().value() << '"'
       << ",security_id_source=\"" << sbe_binaryumdf::security_id_source::to_string(msg.fields.security_id_source.get().value()) << '"'
       << ",security_group=\"" << msg.fields.security_group.get_trimmed().value() << '"'
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",security_update_action=\"" << sbe_binaryumdf::security_update_action::to_string(msg.fields.security_update_action.get().value()) << '"'
       << ",security_type=\"" << sbe_binaryumdf::security_type::to_string(msg.fields.security_type.get().value()) << '"'
       << ",security_sub_type=" << msg.fields.security_sub_type.get().value()
       << ",tot_no_related_sym=" << msg.fields.tot_no_related_sym.get().value()
       << ",min_price_increment=" << (msg.fields.min_price_increment.get().has_value() ? std::to_string(msg.fields.min_price_increment.get().value()) : std::string_view("null"))
       << ",strike_price=" << (msg.fields.strike_price.get().has_value() ? std::to_string(msg.fields.strike_price.get().value()) : std::string_view("null"))
       << ",contract_multiplier=" << (msg.fields.contract_multiplier.get().has_value() ? std::to_string(msg.fields.contract_multiplier.get().value()) : std::string_view("null"))
       << ",price_divisor=" << (msg.fields.price_divisor.get().has_value() ? std::to_string(msg.fields.price_divisor.get().value()) : std::string_view("null"))
       << ",security_validity_timestamp=" << (msg.fields.security_validity_timestamp.get().has_value() ? std::to_string(msg.fields.security_validity_timestamp.get().value()) : std::string_view("null"))
       << ",no_shares_issued=" << (msg.fields.no_shares_issued.get().has_value() ? std::to_string(msg.fields.no_shares_issued.get().value()) : std::string_view("null"))
       << ",clearing_house_id=" << (msg.fields.clearing_house_id.get().has_value() ? std::to_string(msg.fields.clearing_house_id.get().value()) : std::string_view("null"))
       << ",min_order_qty=" << (msg.fields.min_order_qty.get().has_value() ? std::to_string(msg.fields.min_order_qty.get().value()) : std::string_view("null"))
       << ",max_order_qty=" << (msg.fields.max_order_qty.get().has_value() ? std::to_string(msg.fields.max_order_qty.get().value()) : std::string_view("null"))
       << ",min_lot_size=" << (msg.fields.min_lot_size.get().has_value() ? std::to_string(msg.fields.min_lot_size.get().value()) : std::string_view("null"))
       << ",min_trade_vol=" << (msg.fields.min_trade_vol.get().has_value() ? std::to_string(msg.fields.min_trade_vol.get().value()) : std::string_view("null"))
       << ",corporate_action_event_id=" << (msg.fields.corporate_action_event_id.get().has_value() ? std::to_string(msg.fields.corporate_action_event_id.get().value()) : std::string_view("null"))
       << ",issue_date=" << msg.fields.issue_date.get().value()
       << ",maturity_date=" << (msg.fields.maturity_date.get().has_value() ? std::to_string(msg.fields.maturity_date.get().value()) : std::string_view("null"))
       << ",country_of_issue=\"" << (msg.fields.country_of_issue.get_trimmed().has_value() ? msg.fields.country_of_issue.get_trimmed().value() : std::string_view("null")) << '"'
       << ",start_date=" << (msg.fields.start_date.get().has_value() ? std::to_string(msg.fields.start_date.get().value()) : std::string_view("null"))
       << ",end_date=" << (msg.fields.end_date.get().has_value() ? std::to_string(msg.fields.end_date.get().value()) : std::string_view("null"))
       << ",settl_type=" << (msg.fields.settl_type.get().has_value() ? std::to_string(msg.fields.settl_type.get().value()) : std::string_view("null"))
       << ",settl_date=" << (msg.fields.settl_date.get().has_value() ? std::to_string(msg.fields.settl_date.get().value()) : std::string_view("null"))
       << ",dated_date=" << (msg.fields.dated_date.get().has_value() ? std::to_string(msg.fields.dated_date.get().value()) : std::string_view("null"))
       << ",isin_number=\"" << (msg.fields.isin_number.get_trimmed().has_value() ? msg.fields.isin_number.get_trimmed().value() : std::string_view("null")) << '"'
       << ",asset=\"" << msg.fields.asset.get_trimmed().value() << '"'
       << ",cfi_code=\"" << msg.fields.cfi_code.get_trimmed().value() << '"'
       << ",maturity_month_year.year=" << msg.fields.maturity_month_year.year.get().value()
       << ",maturity_month_year.month=" << static_cast<unsigned>(msg.fields.maturity_month_year.month.get().value())
       << ",maturity_month_year.day=" << static_cast<unsigned>(msg.fields.maturity_month_year.day.get().value())
       << ",maturity_month_year.week=" << static_cast<unsigned>(msg.fields.maturity_month_year.week.get().value())
       << ",contract_settl_month.year=" << msg.fields.contract_settl_month.year.get().value()
       << ",contract_settl_month.month=" << static_cast<unsigned>(msg.fields.contract_settl_month.month.get().value())
       << ",contract_settl_month.day=" << static_cast<unsigned>(msg.fields.contract_settl_month.day.get().value())
       << ",contract_settl_month.week=" << static_cast<unsigned>(msg.fields.contract_settl_month.week.get().value())
       << ",currency=\"" << msg.fields.currency.get_trimmed().value() << '"'
       << ",strike_currency=\"" << (msg.fields.strike_currency.get_trimmed().has_value() ? msg.fields.strike_currency.get_trimmed().value() : std::string_view("null")) << '"'
       << ",settl_currency=\"" << (msg.fields.settl_currency.get_trimmed().has_value() ? msg.fields.settl_currency.get_trimmed().value() : std::string_view("null")) << '"'
       << ",security_strategy_type=\"" << (msg.fields.security_strategy_type.get_trimmed().has_value() ? msg.fields.security_strategy_type.get_trimmed().value() : std::string_view("null")) << '"'
       << ",lot_type=\"" << sbe_binaryumdf::lot_type::to_string(msg.fields.lot_type.get().value()) << '"'
       << ",tick_size_denominator=" << (msg.fields.tick_size_denominator.get().has_value() ? std::to_string(msg.fields.tick_size_denominator.get().value()) : std::string_view("null"))
       << ",product=\"" << sbe_binaryumdf::product::to_string(msg.fields.product.get().value()) << '"'
       << ",exercise_style=\"" << sbe_binaryumdf::exercise_style::to_string(msg.fields.exercise_style.get().value()) << '"'
       << ",put_or_call=\"" << sbe_binaryumdf::put_or_call::to_string(msg.fields.put_or_call.get().value()) << '"'
       << ",price_type=\"" << sbe_binaryumdf::price_type::to_string(msg.fields.price_type.get().value()) << '"'
       << ",market_segment_id=" << (msg.fields.market_segment_id.get().has_value() ? std::to_string(msg.fields.market_segment_id.get().value()) : std::string_view("null"))
       << ",governance_indicator=\"" << sbe_binaryumdf::governance_indicator::to_string(msg.fields.governance_indicator.get().value()) << '"'
       << ",security_match_type=\"" << sbe_binaryumdf::security_match_type::to_string(msg.fields.security_match_type.get().value()) << '"'
       << ",last_fragment=\"" << sbe_binaryumdf::last_fragment::to_string(msg.fields.last_fragment.get().value()) << '"'
       << ",multi_leg_model=\"" << sbe_binaryumdf::multi_leg_model::to_string(msg.fields.multi_leg_model.get().value()) << '"'
       << ",multi_leg_price_method=\"" << sbe_binaryumdf::multi_leg_price_method::to_string(msg.fields.multi_leg_price_method.get().value()) << '"'
       << ",min_cross_qty=" << (msg.fields.min_cross_qty.get().has_value() ? std::to_string(msg.fields.min_cross_qty.get().value()) : std::string_view("null"))
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const news_5_message& msg) {
    os << "security_id_optional=" << (msg.fields.security_id_optional.get().has_value() ? std::to_string(msg.fields.security_id_optional.get().value()) : std::string_view("null"))
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",news_source=\"" << sbe_binaryumdf::news_source::to_string(msg.fields.news_source.get().value()) << '"'
       << ",language_code=\"" << (msg.fields.language_code.get_trimmed().has_value() ? msg.fields.language_code.get_trimmed().value() : std::string_view("null")) << '"'
       << ",part_count=" << msg.fields.part_count.get().value()
       << ",part_number=" << msg.fields.part_number.get().value()
       << ",news_id=" << (msg.fields.news_id.get().has_value() ? std::to_string(msg.fields.news_id.get().value()) : std::string_view("null"))
       << ",orig_time=" << (msg.fields.orig_time.get().has_value() ? std::to_string(msg.fields.orig_time.get().value()) : std::string_view("null"))
       << ",total_text_length=" << msg.fields.total_text_length.get().value()
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const empty_book_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",md_entry_timestamp=" << (msg.fields.md_entry_timestamp.get().has_value() ? std::to_string(msg.fields.md_entry_timestamp.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const channel_reset_11_message& msg) {
    os << "match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",md_entry_timestamp=" << (msg.fields.md_entry_timestamp.get().has_value() ? std::to_string(msg.fields.md_entry_timestamp.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const opening_price_15_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",md_update_action=\"" << sbe_binaryumdf::md_update_action::to_string(msg.fields.md_update_action.get().value()) << '"'
       << ",open_close_settl_flag=\"" << sbe_binaryumdf::open_close_settl_flag::to_string(msg.fields.open_close_settl_flag.get().value()) << '"'
       << ",md_future_price=" << msg.fields.md_future_price.get().value()
       << ",net_chg_prev_day=" << (msg.fields.net_chg_prev_day.get().has_value() ? std::to_string(msg.fields.net_chg_prev_day.get().value()) : std::string_view("null"))
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",md_entry_timestamp=" << (msg.fields.md_entry_timestamp.get().has_value() ? std::to_string(msg.fields.md_entry_timestamp.get().value()) : std::string_view("null"))
       << ",rpt_seq=" << (msg.fields.rpt_seq.get().has_value() ? std::to_string(msg.fields.rpt_seq.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const theoretical_opening_price_16_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",md_update_action=\"" << sbe_binaryumdf::md_update_action::to_string(msg.fields.md_update_action.get().value()) << '"'
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",md_corporate_offset_price_optional=" << (msg.fields.md_corporate_offset_price_optional.get().has_value() ? std::to_string(msg.fields.md_corporate_offset_price_optional.get().value()) : std::string_view("null"))
       << ",md_entry_size_quantity_optional=" << (msg.fields.md_entry_size_quantity_optional.get().has_value() ? std::to_string(msg.fields.md_entry_size_quantity_optional.get().value()) : std::string_view("null"))
       << ",md_entry_timestamp=" << (msg.fields.md_entry_timestamp.get().has_value() ? std::to_string(msg.fields.md_entry_timestamp.get().value()) : std::string_view("null"))
       << ",rpt_seq=" << (msg.fields.rpt_seq.get().has_value() ? std::to_string(msg.fields.rpt_seq.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const closing_price_17_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",open_close_settl_flag=\"" << sbe_binaryumdf::open_close_settl_flag::to_string(msg.fields.open_close_settl_flag.get().value()) << '"'
       << ",md_corporate_price=" << msg.fields.md_corporate_price.get().value()
       << ",last_trade_date=" << (msg.fields.last_trade_date.get().has_value() ? std::to_string(msg.fields.last_trade_date.get().value()) : std::string_view("null"))
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",md_entry_timestamp=" << (msg.fields.md_entry_timestamp.get().has_value() ? std::to_string(msg.fields.md_entry_timestamp.get().value()) : std::string_view("null"))
       << ",rpt_seq=" << (msg.fields.rpt_seq.get().has_value() ? std::to_string(msg.fields.rpt_seq.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const auction_imbalance_19_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",md_update_action=\"" << sbe_binaryumdf::md_update_action::to_string(msg.fields.md_update_action.get().value()) << '"'
       << ",imbalance_condition=" << static_cast<unsigned>(msg.fields.imbalance_condition.get().value())
       << ",md_entry_size_quantity_optional=" << (msg.fields.md_entry_size_quantity_optional.get().has_value() ? std::to_string(msg.fields.md_entry_size_quantity_optional.get().value()) : std::string_view("null"))
       << ",md_entry_timestamp=" << (msg.fields.md_entry_timestamp.get().has_value() ? std::to_string(msg.fields.md_entry_timestamp.get().value()) : std::string_view("null"))
       << ",rpt_seq=" << (msg.fields.rpt_seq.get().has_value() ? std::to_string(msg.fields.rpt_seq.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const price_band_20_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",price_band_type=\"" << sbe_binaryumdf::price_band_type::to_string(msg.fields.price_band_type.get().value()) << '"'
       << ",price_limit_type=\"" << sbe_binaryumdf::price_limit_type::to_string(msg.fields.price_limit_type.get().value()) << '"'
       << ",price_band_midpoint_price_type=\"" << sbe_binaryumdf::price_band_midpoint_price_type::to_string(msg.fields.price_band_midpoint_price_type.get().value()) << '"'
       << ",low_limit_price=" << (msg.fields.low_limit_price.get().has_value() ? std::to_string(msg.fields.low_limit_price.get().value()) : std::string_view("null"))
       << ",high_limit_price=" << (msg.fields.high_limit_price.get().has_value() ? std::to_string(msg.fields.high_limit_price.get().value()) : std::string_view("null"))
       << ",trading_reference_price=" << (msg.fields.trading_reference_price.get().has_value() ? std::to_string(msg.fields.trading_reference_price.get().value()) : std::string_view("null"))
       << ",md_entry_timestamp=" << (msg.fields.md_entry_timestamp.get().has_value() ? std::to_string(msg.fields.md_entry_timestamp.get().value()) : std::string_view("null"))
       << ",rpt_seq=" << (msg.fields.rpt_seq.get().has_value() ? std::to_string(msg.fields.rpt_seq.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const quantity_band_21_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",avg_daily_traded_qty=" << (msg.fields.avg_daily_traded_qty.get().has_value() ? std::to_string(msg.fields.avg_daily_traded_qty.get().value()) : std::string_view("null"))
       << ",max_trade_vol=" << (msg.fields.max_trade_vol.get().has_value() ? std::to_string(msg.fields.max_trade_vol.get().value()) : std::string_view("null"))
       << ",md_entry_timestamp=" << (msg.fields.md_entry_timestamp.get().has_value() ? std::to_string(msg.fields.md_entry_timestamp.get().value()) : std::string_view("null"))
       << ",rpt_seq=" << (msg.fields.rpt_seq.get().has_value() ? std::to_string(msg.fields.rpt_seq.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const high_price_24_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",md_update_action=\"" << sbe_binaryumdf::md_update_action::to_string(msg.fields.md_update_action.get().value()) << '"'
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",md_future_price=" << msg.fields.md_future_price.get().value()
       << ",md_entry_timestamp=" << (msg.fields.md_entry_timestamp.get().has_value() ? std::to_string(msg.fields.md_entry_timestamp.get().value()) : std::string_view("null"))
       << ",rpt_seq=" << (msg.fields.rpt_seq.get().has_value() ? std::to_string(msg.fields.rpt_seq.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const low_price_25_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",md_update_action=\"" << sbe_binaryumdf::md_update_action::to_string(msg.fields.md_update_action.get().value()) << '"'
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",md_future_price=" << msg.fields.md_future_price.get().value()
       << ",md_entry_timestamp=" << (msg.fields.md_entry_timestamp.get().has_value() ? std::to_string(msg.fields.md_entry_timestamp.get().value()) : std::string_view("null"))
       << ",rpt_seq=" << (msg.fields.rpt_seq.get().has_value() ? std::to_string(msg.fields.rpt_seq.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const last_trade_price_27_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",trading_session_id=\"" << sbe_binaryumdf::trading_session_id::to_string(msg.fields.trading_session_id.get().value()) << '"'
       << ",trade_condition=" << static_cast<unsigned>(msg.fields.trade_condition.get().value())
       << ",md_future_price=" << msg.fields.md_future_price.get().value()
       << ",md_entry_size_quantity=" << msg.fields.md_entry_size_quantity.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",md_entry_buyer=" << (msg.fields.md_entry_buyer.get().has_value() ? std::to_string(msg.fields.md_entry_buyer.get().value()) : std::string_view("null"))
       << ",md_entry_seller=" << (msg.fields.md_entry_seller.get().has_value() ? std::to_string(msg.fields.md_entry_seller.get().value()) : std::string_view("null"))
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",md_entry_timestamp=" << (msg.fields.md_entry_timestamp.get().has_value() ? std::to_string(msg.fields.md_entry_timestamp.get().value()) : std::string_view("null"))
       << ",rpt_seq=" << (msg.fields.rpt_seq.get().has_value() ? std::to_string(msg.fields.rpt_seq.get().value()) : std::string_view("null"))
       << ",seller_days=" << (msg.fields.seller_days.get().has_value() ? std::to_string(msg.fields.seller_days.get().value()) : std::string_view("null"))
       << ",md_entry_interest_rate=" << (msg.fields.md_entry_interest_rate.get().has_value() ? std::to_string(msg.fields.md_entry_interest_rate.get().value()) : std::string_view("null"))
       << ",trd_sub_type=\"" << sbe_binaryumdf::trd_sub_type::to_string(msg.fields.trd_sub_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const snapshot_full_refresh_header_30_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",last_msg_seq_num_processed=" << msg.fields.last_msg_seq_num_processed.get().value()
       << ",tot_num_reports=" << msg.fields.tot_num_reports.get().value()
       << ",tot_num_bids=" << msg.fields.tot_num_bids.get().value()
       << ",tot_num_offers=" << msg.fields.tot_num_offers.get().value()
       << ",tot_num_stats=" << msg.fields.tot_num_stats.get().value()
       << ",last_rpt_seq=" << (msg.fields.last_rpt_seq.get().has_value() ? std::to_string(msg.fields.last_rpt_seq.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_mb_o_50_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",md_update_action=\"" << sbe_binaryumdf::md_update_action::to_string(msg.fields.md_update_action.get().value()) << '"'
       << ",md_entry_type=\"" << sbe_binaryumdf::md_entry_type::to_string(msg.fields.md_entry_type.get().value()) << '"'
       << ",md_corporate_offset_price_optional=" << (msg.fields.md_corporate_offset_price_optional.get().has_value() ? std::to_string(msg.fields.md_corporate_offset_price_optional.get().value()) : std::string_view("null"))
       << ",md_entry_size_quantity=" << msg.fields.md_entry_size_quantity.get().value()
       << ",md_entry_position_no=" << msg.fields.md_entry_position_no.get().value()
       << ",entering_firm=" << (msg.fields.entering_firm.get().has_value() ? std::to_string(msg.fields.entering_firm.get().value()) : std::string_view("null"))
       << ",md_insert_timestamp=" << (msg.fields.md_insert_timestamp.get().has_value() ? std::to_string(msg.fields.md_insert_timestamp.get().value()) : std::string_view("null"))
       << ",secondary_order_id=" << msg.fields.secondary_order_id.get().value()
       << ",rpt_seq=" << (msg.fields.rpt_seq.get().has_value() ? std::to_string(msg.fields.rpt_seq.get().value()) : std::string_view("null"))
       << ",md_entry_timestamp=" << (msg.fields.md_entry_timestamp.get().has_value() ? std::to_string(msg.fields.md_entry_timestamp.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const delete_order_mb_o_51_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",md_entry_type=\"" << sbe_binaryumdf::md_entry_type::to_string(msg.fields.md_entry_type.get().value()) << '"'
       << ",md_entry_position_no=" << msg.fields.md_entry_position_no.get().value()
       << ",md_entry_size_quantity_optional=" << (msg.fields.md_entry_size_quantity_optional.get().has_value() ? std::to_string(msg.fields.md_entry_size_quantity_optional.get().value()) : std::string_view("null"))
       << ",secondary_order_id=" << msg.fields.secondary_order_id.get().value()
       << ",md_entry_timestamp=" << (msg.fields.md_entry_timestamp.get().has_value() ? std::to_string(msg.fields.md_entry_timestamp.get().value()) : std::string_view("null"))
       << ",rpt_seq=" << (msg.fields.rpt_seq.get().has_value() ? std::to_string(msg.fields.rpt_seq.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const mass_delete_orders_mb_o_52_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",md_update_action=\"" << sbe_binaryumdf::md_update_action::to_string(msg.fields.md_update_action.get().value()) << '"'
       << ",md_entry_type=\"" << sbe_binaryumdf::md_entry_type::to_string(msg.fields.md_entry_type.get().value()) << '"'
       << ",md_entry_position_no=" << msg.fields.md_entry_position_no.get().value()
       << ",md_entry_timestamp=" << (msg.fields.md_entry_timestamp.get().has_value() ? std::to_string(msg.fields.md_entry_timestamp.get().value()) : std::string_view("null"))
       << ",rpt_seq=" << (msg.fields.rpt_seq.get().has_value() ? std::to_string(msg.fields.rpt_seq.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_53_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",trading_session_id=\"" << sbe_binaryumdf::trading_session_id::to_string(msg.fields.trading_session_id.get().value()) << '"'
       << ",trade_condition=" << static_cast<unsigned>(msg.fields.trade_condition.get().value())
       << ",md_future_price=" << msg.fields.md_future_price.get().value()
       << ",md_entry_size_quantity=" << msg.fields.md_entry_size_quantity.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",md_entry_buyer=" << (msg.fields.md_entry_buyer.get().has_value() ? std::to_string(msg.fields.md_entry_buyer.get().value()) : std::string_view("null"))
       << ",md_entry_seller=" << (msg.fields.md_entry_seller.get().has_value() ? std::to_string(msg.fields.md_entry_seller.get().value()) : std::string_view("null"))
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",trd_sub_type=\"" << sbe_binaryumdf::trd_sub_type::to_string(msg.fields.trd_sub_type.get().value()) << '"'
       << ",md_entry_timestamp=" << (msg.fields.md_entry_timestamp.get().has_value() ? std::to_string(msg.fields.md_entry_timestamp.get().value()) : std::string_view("null"))
       << ",rpt_seq=" << (msg.fields.rpt_seq.get().has_value() ? std::to_string(msg.fields.rpt_seq.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const forward_trade_54_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",trading_session_id=\"" << sbe_binaryumdf::trading_session_id::to_string(msg.fields.trading_session_id.get().value()) << '"'
       << ",trade_condition=" << static_cast<unsigned>(msg.fields.trade_condition.get().value())
       << ",md_future_price=" << msg.fields.md_future_price.get().value()
       << ",md_entry_size_quantity=" << msg.fields.md_entry_size_quantity.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",md_entry_buyer=" << (msg.fields.md_entry_buyer.get().has_value() ? std::to_string(msg.fields.md_entry_buyer.get().value()) : std::string_view("null"))
       << ",md_entry_seller=" << (msg.fields.md_entry_seller.get().has_value() ? std::to_string(msg.fields.md_entry_seller.get().value()) : std::string_view("null"))
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",md_entry_timestamp=" << (msg.fields.md_entry_timestamp.get().has_value() ? std::to_string(msg.fields.md_entry_timestamp.get().value()) : std::string_view("null"))
       << ",rpt_seq=" << (msg.fields.rpt_seq.get().has_value() ? std::to_string(msg.fields.rpt_seq.get().value()) : std::string_view("null"))
       << ",seller_days=" << (msg.fields.seller_days.get().has_value() ? std::to_string(msg.fields.seller_days.get().value()) : std::string_view("null"))
       << ",md_entry_interest_rate=" << (msg.fields.md_entry_interest_rate.get().has_value() ? std::to_string(msg.fields.md_entry_interest_rate.get().value()) : std::string_view("null"))
       << ",trd_sub_type=\"" << sbe_binaryumdf::trd_sub_type::to_string(msg.fields.trd_sub_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const execution_summary_55_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",aggressor_side=\"" << sbe_binaryumdf::aggressor_side::to_string(msg.fields.aggressor_side.get().value()) << '"'
       << ",last_px=" << msg.fields.last_px.get().value()
       << ",fill_qty=" << msg.fields.fill_qty.get().value()
       << ",traded_hidden_qty=" << (msg.fields.traded_hidden_qty.get().has_value() ? std::to_string(msg.fields.traded_hidden_qty.get().value()) : std::string_view("null"))
       << ",cxl_qty=" << (msg.fields.cxl_qty.get().has_value() ? std::to_string(msg.fields.cxl_qty.get().value()) : std::string_view("null"))
       << ",aggressor_time=" << (msg.fields.aggressor_time.get().has_value() ? std::to_string(msg.fields.aggressor_time.get().value()) : std::string_view("null"))
       << ",rpt_seq=" << (msg.fields.rpt_seq.get().has_value() ? std::to_string(msg.fields.rpt_seq.get().value()) : std::string_view("null"))
       << ",md_entry_timestamp=" << (msg.fields.md_entry_timestamp.get().has_value() ? std::to_string(msg.fields.md_entry_timestamp.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const execution_statistics_56_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",trading_session_id=\"" << sbe_binaryumdf::trading_session_id::to_string(msg.fields.trading_session_id.get().value()) << '"'
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",trade_volume=" << msg.fields.trade_volume.get().value()
       << ",vwap_px=" << (msg.fields.vwap_px.get().has_value() ? std::to_string(msg.fields.vwap_px.get().value()) : std::string_view("null"))
       << ",net_chg_prev_day=" << (msg.fields.net_chg_prev_day.get().has_value() ? std::to_string(msg.fields.net_chg_prev_day.get().value()) : std::string_view("null"))
       << ",number_of_trades=" << msg.fields.number_of_trades.get().value()
       << ",md_entry_timestamp=" << (msg.fields.md_entry_timestamp.get().has_value() ? std::to_string(msg.fields.md_entry_timestamp.get().value()) : std::string_view("null"))
       << ",rpt_seq=" << (msg.fields.rpt_seq.get().has_value() ? std::to_string(msg.fields.rpt_seq.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_bust_57_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",match_event_indicator=" << static_cast<unsigned>(msg.fields.match_event_indicator.get().value())
       << ",trading_session_id=\"" << sbe_binaryumdf::trading_session_id::to_string(msg.fields.trading_session_id.get().value()) << '"'
       << ",md_future_price=" << msg.fields.md_future_price.get().value()
       << ",md_entry_size_quantity=" << msg.fields.md_entry_size_quantity.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",md_entry_timestamp=" << (msg.fields.md_entry_timestamp.get().has_value() ? std::to_string(msg.fields.md_entry_timestamp.get().value()) : std::string_view("null"))
       << ",rpt_seq=" << (msg.fields.rpt_seq.get().has_value() ? std::to_string(msg.fields.rpt_seq.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const snapshot_full_refresh_orders_mb_o_71_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

}
