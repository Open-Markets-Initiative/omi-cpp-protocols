// Databento.MarketData.Normalized.Dbn.v1: messages/Format.hpp
#pragma once

#include <ostream>
#include <string_view>

#include "TradeMsg.hpp"
#include "Mbp1Msg.hpp"
#include "Mbp10Msg.hpp"
#include "OhlcvMsg.hpp"
#include "StatusMsg.hpp"
#include "InstrumentDefMsg.hpp"
#include "ImbalanceMsg.hpp"
#include "ErrorMsg.hpp"
#include "SymbolMappingMsg.hpp"
#include "SystemMsg.hpp"
#include "StatMsg.hpp"
#include "MboMsg.hpp"
#include "Cmbp1Msg.hpp"
#include "CbboMsg.hpp"
#include "BboMsg.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

namespace dbn_normalized = ::databento::marketdata::normalized::dbn::v1;

inline std::ostream& operator<<(std::ostream& os, const record& value) {
    os << "record_header.record_length=" << static_cast<unsigned>(value.record_header.record_length.get().value())
       << ",record_header.rtype=\"" << dbn_normalized::rtype::to_string(value.record_header.rtype.get().value()) << '"'
       << ",record_header.publisher_id=" << value.record_header.publisher_id.get().value()
       << ",record_header.instrument_id=" << value.record_header.instrument_id.get().value()
       << ",record_header.ts_event=" << (value.record_header.ts_event.get().has_value() ? std::to_string(value.record_header.ts_event.get().value()) : std::string_view("null"))
       << ",ts_out_time=" << value.ts_out_time.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const record_header& value) {
    os << "record_length=" << static_cast<unsigned>(value.record_length.get().value())
       << ",rtype=\"" << dbn_normalized::rtype::to_string(value.rtype.get().value()) << '"'
       << ",publisher_id=" << value.publisher_id.get().value()
       << ",instrument_id=" << value.instrument_id.get().value()
       << ",ts_event=" << (value.ts_event.get().has_value() ? std::to_string(value.ts_event.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_msg& msg) {
    os << "price=" << (msg.fields.price.get().has_value() ? std::to_string(msg.fields.price.get().value()) : std::string_view("null"))
       << ",size=" << msg.fields.size.get().value()
       << ",action=\"" << dbn_normalized::action::to_string(msg.fields.action.get().value()) << '"'
       << ",side=\"" << dbn_normalized::side::to_string(msg.fields.side.get().value()) << '"'
       << ",flags=" << static_cast<unsigned>(msg.fields.flags.get().value())
       << ",depth=" << static_cast<unsigned>(msg.fields.depth.get().value())
       << ",ts_recv=" << (msg.fields.ts_recv.get().has_value() ? std::to_string(msg.fields.ts_recv.get().value()) : std::string_view("null"))
       << ",ts_in_delta=" << msg.fields.ts_in_delta.get().value()
       << ",sequence=" << msg.fields.sequence.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const mbp_1_msg& msg) {
    os << "price=" << (msg.fields.price.get().has_value() ? std::to_string(msg.fields.price.get().value()) : std::string_view("null"))
       << ",size=" << msg.fields.size.get().value()
       << ",action=\"" << dbn_normalized::action::to_string(msg.fields.action.get().value()) << '"'
       << ",side=\"" << dbn_normalized::side::to_string(msg.fields.side.get().value()) << '"'
       << ",flags=" << static_cast<unsigned>(msg.fields.flags.get().value())
       << ",depth=" << static_cast<unsigned>(msg.fields.depth.get().value())
       << ",ts_recv=" << (msg.fields.ts_recv.get().has_value() ? std::to_string(msg.fields.ts_recv.get().value()) : std::string_view("null"))
       << ",ts_in_delta=" << msg.fields.ts_in_delta.get().value()
       << ",sequence=" << msg.fields.sequence.get().value()
       << ",bid_ask_pair.bid_px=" << (msg.fields.bid_ask_pair.bid_px.get().has_value() ? std::to_string(msg.fields.bid_ask_pair.bid_px.get().value()) : std::string_view("null"))
       << ",bid_ask_pair.ask_px=" << (msg.fields.bid_ask_pair.ask_px.get().has_value() ? std::to_string(msg.fields.bid_ask_pair.ask_px.get().value()) : std::string_view("null"))
       << ",bid_ask_pair.bid_sz=" << msg.fields.bid_ask_pair.bid_sz.get().value()
       << ",bid_ask_pair.ask_sz=" << msg.fields.bid_ask_pair.ask_sz.get().value()
       << ",bid_ask_pair.bid_ct=" << msg.fields.bid_ask_pair.bid_ct.get().value()
       << ",bid_ask_pair.ask_ct=" << msg.fields.bid_ask_pair.ask_ct.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const mbp_10_msg& msg) {
    os << "price=" << (msg.fields.price.get().has_value() ? std::to_string(msg.fields.price.get().value()) : std::string_view("null"))
       << ",size=" << msg.fields.size.get().value()
       << ",action=\"" << dbn_normalized::action::to_string(msg.fields.action.get().value()) << '"'
       << ",side=\"" << dbn_normalized::side::to_string(msg.fields.side.get().value()) << '"'
       << ",flags=" << static_cast<unsigned>(msg.fields.flags.get().value())
       << ",depth=" << static_cast<unsigned>(msg.fields.depth.get().value())
       << ",ts_recv=" << (msg.fields.ts_recv.get().has_value() ? std::to_string(msg.fields.ts_recv.get().value()) : std::string_view("null"))
       << ",ts_in_delta=" << msg.fields.ts_in_delta.get().value()
       << ",sequence=" << msg.fields.sequence.get().value()
       << ",bid_ask_pair.bid_px=" << (msg.fields.bid_ask_pair.bid_px.get().has_value() ? std::to_string(msg.fields.bid_ask_pair.bid_px.get().value()) : std::string_view("null"))
       << ",bid_ask_pair.ask_px=" << (msg.fields.bid_ask_pair.ask_px.get().has_value() ? std::to_string(msg.fields.bid_ask_pair.ask_px.get().value()) : std::string_view("null"))
       << ",bid_ask_pair.bid_sz=" << msg.fields.bid_ask_pair.bid_sz.get().value()
       << ",bid_ask_pair.ask_sz=" << msg.fields.bid_ask_pair.ask_sz.get().value()
       << ",bid_ask_pair.bid_ct=" << msg.fields.bid_ask_pair.bid_ct.get().value()
       << ",bid_ask_pair.ask_ct=" << msg.fields.bid_ask_pair.ask_ct.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const ohlcv_msg& msg) {
    os << "open=" << (msg.fields.open.get().has_value() ? std::to_string(msg.fields.open.get().value()) : std::string_view("null"))
       << ",high=" << (msg.fields.high.get().has_value() ? std::to_string(msg.fields.high.get().value()) : std::string_view("null"))
       << ",low=" << (msg.fields.low.get().has_value() ? std::to_string(msg.fields.low.get().value()) : std::string_view("null"))
       << ",close=" << (msg.fields.close.get().has_value() ? std::to_string(msg.fields.close.get().value()) : std::string_view("null"))
       << ",volume=" << msg.fields.volume.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const status_msg& msg) {
    os << "ts_recv=" << (msg.fields.ts_recv.get().has_value() ? std::to_string(msg.fields.ts_recv.get().value()) : std::string_view("null"))
       << ",status_action=\"" << dbn_normalized::status_action::to_string(msg.fields.status_action.get().value()) << '"'
       << ",status_reason=\"" << dbn_normalized::status_reason::to_string(msg.fields.status_reason.get().value()) << '"'
       << ",trading_event=\"" << dbn_normalized::trading_event::to_string(msg.fields.trading_event.get().value()) << '"'
       << ",is_trading=\"" << dbn_normalized::is_trading::to_string(msg.fields.is_trading.get().value()) << '"'
       << ",is_quoting=\"" << dbn_normalized::is_quoting::to_string(msg.fields.is_quoting.get().value()) << '"'
       << ",is_short_sell_restricted=\"" << dbn_normalized::is_short_sell_restricted::to_string(msg.fields.is_short_sell_restricted.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const instrument_def_msg& msg) {
    os << "ts_recv=" << (msg.fields.ts_recv.get().has_value() ? std::to_string(msg.fields.ts_recv.get().value()) : std::string_view("null"))
       << ",min_price_increment=" << (msg.fields.min_price_increment.get().has_value() ? std::to_string(msg.fields.min_price_increment.get().value()) : std::string_view("null"))
       << ",display_factor=" << (msg.fields.display_factor.get().has_value() ? std::to_string(msg.fields.display_factor.get().value()) : std::string_view("null"))
       << ",expiration=" << (msg.fields.expiration.get().has_value() ? std::to_string(msg.fields.expiration.get().value()) : std::string_view("null"))
       << ",activation=" << (msg.fields.activation.get().has_value() ? std::to_string(msg.fields.activation.get().value()) : std::string_view("null"))
       << ",high_limit_price=" << (msg.fields.high_limit_price.get().has_value() ? std::to_string(msg.fields.high_limit_price.get().value()) : std::string_view("null"))
       << ",low_limit_price=" << (msg.fields.low_limit_price.get().has_value() ? std::to_string(msg.fields.low_limit_price.get().value()) : std::string_view("null"))
       << ",max_price_variation=" << (msg.fields.max_price_variation.get().has_value() ? std::to_string(msg.fields.max_price_variation.get().value()) : std::string_view("null"))
       << ",trading_reference_price=" << (msg.fields.trading_reference_price.get().has_value() ? std::to_string(msg.fields.trading_reference_price.get().value()) : std::string_view("null"))
       << ",unit_of_measure_qty=" << (msg.fields.unit_of_measure_qty.get().has_value() ? std::to_string(msg.fields.unit_of_measure_qty.get().value()) : std::string_view("null"))
       << ",min_price_increment_amount=" << (msg.fields.min_price_increment_amount.get().has_value() ? std::to_string(msg.fields.min_price_increment_amount.get().value()) : std::string_view("null"))
       << ",price_ratio=" << (msg.fields.price_ratio.get().has_value() ? std::to_string(msg.fields.price_ratio.get().value()) : std::string_view("null"))
       << ",inst_attrib_value=" << msg.fields.inst_attrib_value.get().value()
       << ",underlying_id=" << msg.fields.underlying_id.get().value()
       << ",raw_instrument_id=" << msg.fields.raw_instrument_id.get().value()
       << ",market_depth_implied=" << msg.fields.market_depth_implied.get().value()
       << ",market_depth=" << msg.fields.market_depth.get().value()
       << ",market_segment_id=" << msg.fields.market_segment_id.get().value()
       << ",max_trade_vol=" << msg.fields.max_trade_vol.get().value()
       << ",min_lot_size=" << msg.fields.min_lot_size.get().value()
       << ",min_lot_size_block=" << msg.fields.min_lot_size_block.get().value()
       << ",min_lot_size_round_lot=" << msg.fields.min_lot_size_round_lot.get().value()
       << ",min_trade_vol=" << msg.fields.min_trade_vol.get().value()
       << ",contract_multiplier=" << msg.fields.contract_multiplier.get().value()
       << ",decay_quantity=" << msg.fields.decay_quantity.get().value()
       << ",original_contract_size=" << msg.fields.original_contract_size.get().value()
       << ",trading_reference_date=" << msg.fields.trading_reference_date.get().value()
       << ",appl_id=" << msg.fields.appl_id.get().value()
       << ",maturity_year=" << msg.fields.maturity_year.get().value()
       << ",decay_start_date=" << msg.fields.decay_start_date.get().value()
       << ",channel=" << msg.fields.channel.get().value()
       << ",currency=\"" << msg.fields.currency.get_trimmed().value() << '"'
       << ",settl_currency=\"" << msg.fields.settl_currency.get_trimmed().value() << '"'
       << ",secsubtype=\"" << msg.fields.secsubtype.get_trimmed().value() << '"'
       << ",raw_symbol=\"" << msg.fields.raw_symbol.get_trimmed().value() << '"'
       << ",group=\"" << msg.fields.group.get_trimmed().value() << '"'
       << ",exchange=\"" << msg.fields.exchange.get_trimmed().value() << '"'
       << ",asset=\"" << msg.fields.asset.get_trimmed().value() << '"'
       << ",cfi=\"" << msg.fields.cfi.get_trimmed().value() << '"'
       << ",security_type=\"" << msg.fields.security_type.get_trimmed().value() << '"'
       << ",unit_of_measure=\"" << msg.fields.unit_of_measure.get_trimmed().value() << '"'
       << ",underlying=\"" << msg.fields.underlying.get_trimmed().value() << '"'
       << ",strike_price_currency=\"" << msg.fields.strike_price_currency.get_trimmed().value() << '"'
       << ",instrument_class=\"" << dbn_normalized::instrument_class::to_string(msg.fields.instrument_class.get().value()) << '"'
       << ",strike_price=" << (msg.fields.strike_price.get().has_value() ? std::to_string(msg.fields.strike_price.get().value()) : std::string_view("null"))
       << ",match_algorithm=\"" << dbn_normalized::match_algorithm::to_string(msg.fields.match_algorithm.get().value()) << '"'
       << ",md_security_trading_status=" << static_cast<unsigned>(msg.fields.md_security_trading_status.get().value())
       << ",main_fraction=" << static_cast<unsigned>(msg.fields.main_fraction.get().value())
       << ",price_display_format=" << static_cast<unsigned>(msg.fields.price_display_format.get().value())
       << ",settl_price_type=" << static_cast<unsigned>(msg.fields.settl_price_type.get().value())
       << ",sub_fraction=" << static_cast<unsigned>(msg.fields.sub_fraction.get().value())
       << ",underlying_product=" << static_cast<unsigned>(msg.fields.underlying_product.get().value())
       << ",security_update_action=\"" << dbn_normalized::security_update_action::to_string(msg.fields.security_update_action.get().value()) << '"'
       << ",maturity_month=" << static_cast<unsigned>(msg.fields.maturity_month.get().value())
       << ",maturity_day=" << static_cast<unsigned>(msg.fields.maturity_day.get().value())
       << ",maturity_week=" << static_cast<unsigned>(msg.fields.maturity_week.get().value())
       << ",user_defined_instrument=\"" << dbn_normalized::user_defined_instrument::to_string(msg.fields.user_defined_instrument.get().value()) << '"'
       << ",contract_multiplier_unit=" << static_cast<int>(msg.fields.contract_multiplier_unit.get().value())
       << ",flow_schedule_type=" << static_cast<int>(msg.fields.flow_schedule_type.get().value())
       << ",tick_rule=" << static_cast<unsigned>(msg.fields.tick_rule.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const imbalance_msg& msg) {
    os << "ts_recv=" << (msg.fields.ts_recv.get().has_value() ? std::to_string(msg.fields.ts_recv.get().value()) : std::string_view("null"))
       << ",ref_price=" << (msg.fields.ref_price.get().has_value() ? std::to_string(msg.fields.ref_price.get().value()) : std::string_view("null"))
       << ",auction_time=" << (msg.fields.auction_time.get().has_value() ? std::to_string(msg.fields.auction_time.get().value()) : std::string_view("null"))
       << ",cont_book_clr_price=" << (msg.fields.cont_book_clr_price.get().has_value() ? std::to_string(msg.fields.cont_book_clr_price.get().value()) : std::string_view("null"))
       << ",auct_interest_clr_price=" << (msg.fields.auct_interest_clr_price.get().has_value() ? std::to_string(msg.fields.auct_interest_clr_price.get().value()) : std::string_view("null"))
       << ",ssr_filling_price=" << (msg.fields.ssr_filling_price.get().has_value() ? std::to_string(msg.fields.ssr_filling_price.get().value()) : std::string_view("null"))
       << ",ind_match_price=" << (msg.fields.ind_match_price.get().has_value() ? std::to_string(msg.fields.ind_match_price.get().value()) : std::string_view("null"))
       << ",upper_collar=" << (msg.fields.upper_collar.get().has_value() ? std::to_string(msg.fields.upper_collar.get().value()) : std::string_view("null"))
       << ",lower_collar=" << (msg.fields.lower_collar.get().has_value() ? std::to_string(msg.fields.lower_collar.get().value()) : std::string_view("null"))
       << ",paired_qty=" << msg.fields.paired_qty.get().value()
       << ",total_imbalance_qty=" << msg.fields.total_imbalance_qty.get().value()
       << ",market_imbalance_qty=" << msg.fields.market_imbalance_qty.get().value()
       << ",unpaired_qty=" << msg.fields.unpaired_qty.get().value()
       << ",auction_type=\"" << msg.fields.auction_type.get().value() << '"'
       << ",side=\"" << dbn_normalized::side::to_string(msg.fields.side.get().value()) << '"'
       << ",auction_status=" << static_cast<unsigned>(msg.fields.auction_status.get().value())
       << ",freeze_status=" << static_cast<unsigned>(msg.fields.freeze_status.get().value())
       << ",num_extensions=" << static_cast<unsigned>(msg.fields.num_extensions.get().value())
       << ",unpaired_side=\"" << dbn_normalized::unpaired_side::to_string(msg.fields.unpaired_side.get().value()) << '"'
       << ",significant_imbalance=\"" << msg.fields.significant_imbalance.get().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const error_msg& msg) {
    os << "err=\"" << msg.fields.err.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const symbol_mapping_msg& msg) {
    os << "stype_in_symbol=\"" << msg.fields.stype_in_symbol.get_trimmed().value() << '"'
       << ",stype_out_symbol=\"" << msg.fields.stype_out_symbol.get_trimmed().value() << '"'
       << ",start_ts=" << (msg.fields.start_ts.get().has_value() ? std::to_string(msg.fields.start_ts.get().value()) : std::string_view("null"))
       << ",end_ts=" << (msg.fields.end_ts.get().has_value() ? std::to_string(msg.fields.end_ts.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const system_msg& msg) {
    os << "msg=\"" << msg.fields.msg.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const stat_msg& msg) {
    os << "ts_recv=" << (msg.fields.ts_recv.get().has_value() ? std::to_string(msg.fields.ts_recv.get().value()) : std::string_view("null"))
       << ",ts_ref=" << (msg.fields.ts_ref.get().has_value() ? std::to_string(msg.fields.ts_ref.get().value()) : std::string_view("null"))
       << ",price=" << (msg.fields.price.get().has_value() ? std::to_string(msg.fields.price.get().value()) : std::string_view("null"))
       << ",quantity=" << (msg.fields.quantity.get().has_value() ? std::to_string(msg.fields.quantity.get().value()) : std::string_view("null"))
       << ",sequence=" << msg.fields.sequence.get().value()
       << ",ts_in_delta=" << msg.fields.ts_in_delta.get().value()
       << ",stat_type=\"" << dbn_normalized::stat_type::to_string(msg.fields.stat_type.get().value()) << '"'
       << ",channel=" << msg.fields.channel.get().value()
       << ",update_action=\"" << dbn_normalized::update_action::to_string(msg.fields.update_action.get().value()) << '"'
       << ",stat_flags=" << static_cast<unsigned>(msg.fields.stat_flags.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const mbo_msg& msg) {
    os << "order_id=" << msg.fields.order_id.get().value()
       << ",price=" << (msg.fields.price.get().has_value() ? std::to_string(msg.fields.price.get().value()) : std::string_view("null"))
       << ",size=" << msg.fields.size.get().value()
       << ",flags=" << static_cast<unsigned>(msg.fields.flags.get().value())
       << ",channel_id=" << static_cast<unsigned>(msg.fields.channel_id.get().value())
       << ",action=\"" << dbn_normalized::action::to_string(msg.fields.action.get().value()) << '"'
       << ",side=\"" << dbn_normalized::side::to_string(msg.fields.side.get().value()) << '"'
       << ",ts_recv=" << (msg.fields.ts_recv.get().has_value() ? std::to_string(msg.fields.ts_recv.get().value()) : std::string_view("null"))
       << ",ts_in_delta=" << msg.fields.ts_in_delta.get().value()
       << ",sequence=" << msg.fields.sequence.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const cmbp_1_msg& msg) {
    os << "price=" << (msg.fields.price.get().has_value() ? std::to_string(msg.fields.price.get().value()) : std::string_view("null"))
       << ",size=" << msg.fields.size.get().value()
       << ",action=\"" << dbn_normalized::action::to_string(msg.fields.action.get().value()) << '"'
       << ",side=\"" << dbn_normalized::side::to_string(msg.fields.side.get().value()) << '"'
       << ",flags=" << static_cast<unsigned>(msg.fields.flags.get().value())
       << ",ts_recv=" << (msg.fields.ts_recv.get().has_value() ? std::to_string(msg.fields.ts_recv.get().value()) : std::string_view("null"))
       << ",ts_in_delta=" << msg.fields.ts_in_delta.get().value()
       << ",consolidated_bid_ask_pair.bid_px=" << (msg.fields.consolidated_bid_ask_pair.bid_px.get().has_value() ? std::to_string(msg.fields.consolidated_bid_ask_pair.bid_px.get().value()) : std::string_view("null"))
       << ",consolidated_bid_ask_pair.ask_px=" << (msg.fields.consolidated_bid_ask_pair.ask_px.get().has_value() ? std::to_string(msg.fields.consolidated_bid_ask_pair.ask_px.get().value()) : std::string_view("null"))
       << ",consolidated_bid_ask_pair.bid_sz=" << msg.fields.consolidated_bid_ask_pair.bid_sz.get().value()
       << ",consolidated_bid_ask_pair.ask_sz=" << msg.fields.consolidated_bid_ask_pair.ask_sz.get().value()
       << ",consolidated_bid_ask_pair.bid_pb=" << msg.fields.consolidated_bid_ask_pair.bid_pb.get().value()
       << ",consolidated_bid_ask_pair.ask_pb=" << msg.fields.consolidated_bid_ask_pair.ask_pb.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const cbbo_msg& msg) {
    os << "price=" << (msg.fields.price.get().has_value() ? std::to_string(msg.fields.price.get().value()) : std::string_view("null"))
       << ",size=" << msg.fields.size.get().value()
       << ",side=\"" << dbn_normalized::side::to_string(msg.fields.side.get().value()) << '"'
       << ",flags=" << static_cast<unsigned>(msg.fields.flags.get().value())
       << ",ts_recv=" << (msg.fields.ts_recv.get().has_value() ? std::to_string(msg.fields.ts_recv.get().value()) : std::string_view("null"))
       << ",consolidated_bid_ask_pair.bid_px=" << (msg.fields.consolidated_bid_ask_pair.bid_px.get().has_value() ? std::to_string(msg.fields.consolidated_bid_ask_pair.bid_px.get().value()) : std::string_view("null"))
       << ",consolidated_bid_ask_pair.ask_px=" << (msg.fields.consolidated_bid_ask_pair.ask_px.get().has_value() ? std::to_string(msg.fields.consolidated_bid_ask_pair.ask_px.get().value()) : std::string_view("null"))
       << ",consolidated_bid_ask_pair.bid_sz=" << msg.fields.consolidated_bid_ask_pair.bid_sz.get().value()
       << ",consolidated_bid_ask_pair.ask_sz=" << msg.fields.consolidated_bid_ask_pair.ask_sz.get().value()
       << ",consolidated_bid_ask_pair.bid_pb=" << msg.fields.consolidated_bid_ask_pair.bid_pb.get().value()
       << ",consolidated_bid_ask_pair.ask_pb=" << msg.fields.consolidated_bid_ask_pair.ask_pb.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const bbo_msg& msg) {
    os << "price=" << (msg.fields.price.get().has_value() ? std::to_string(msg.fields.price.get().value()) : std::string_view("null"))
       << ",size=" << msg.fields.size.get().value()
       << ",side=\"" << dbn_normalized::side::to_string(msg.fields.side.get().value()) << '"'
       << ",flags=" << static_cast<unsigned>(msg.fields.flags.get().value())
       << ",ts_recv=" << (msg.fields.ts_recv.get().has_value() ? std::to_string(msg.fields.ts_recv.get().value()) : std::string_view("null"))
       << ",sequence=" << msg.fields.sequence.get().value()
       << ",bid_ask_pair.bid_px=" << (msg.fields.bid_ask_pair.bid_px.get().has_value() ? std::to_string(msg.fields.bid_ask_pair.bid_px.get().value()) : std::string_view("null"))
       << ",bid_ask_pair.ask_px=" << (msg.fields.bid_ask_pair.ask_px.get().has_value() ? std::to_string(msg.fields.bid_ask_pair.ask_px.get().value()) : std::string_view("null"))
       << ",bid_ask_pair.bid_sz=" << msg.fields.bid_ask_pair.bid_sz.get().value()
       << ",bid_ask_pair.ask_sz=" << msg.fields.bid_ask_pair.ask_sz.get().value()
       << ",bid_ask_pair.bid_ct=" << msg.fields.bid_ask_pair.bid_ct.get().value()
       << ",bid_ask_pair.ask_ct=" << msg.fields.bid_ask_pair.ask_ct.get().value()
       ;
    return os;
}

}
