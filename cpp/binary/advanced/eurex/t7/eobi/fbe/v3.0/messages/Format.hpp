#pragma once

#include <ostream>
#include <string_view>

#include "AddComplexInstrument.hpp"
#include "AuctionBbo.hpp"
#include "AuctionClearingPrice.hpp"
#include "CrossRequest.hpp"
#include "ExecutionSummary.hpp"
#include "FullOrderExecution.hpp"
#include "Heartbeat.hpp"
#include "InstrumentStateChange.hpp"
#include "InstrumentSummary.hpp"
#include "OrderAdd.hpp"
#include "OrderDelete.hpp"
#include "OrderMassDelete.hpp"
#include "OrderModify.hpp"
#include "OrderModifySamePrio.hpp"
#include "PartialOrderExecution.hpp"
#include "ProductStateChange.hpp"
#include "ProductSummary.hpp"
#include "QuoteRequest.hpp"
#include "SnapshotOrder.hpp"
#include "TopOfBook.hpp"
#include "TradeReport.hpp"
#include "TradeReversal.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v3_0;

inline std::ostream& operator<<(std::ostream& os, const packet_header& value) {
    os << "eobi_header.body_len=" << value.eobi_header.body_len.get().value()
       << ",eobi_header.template_id=\"" << fbe_eobi::template_id::to_string(value.eobi_header.template_id.get().value()) << '"'
       << ",eobi_header.msg_seq_num=" << value.eobi_header.msg_seq_num.get().value()
       << ",appl_seq_num=" << value.appl_seq_num.get().value()
       << ",market_segment_id=" << (value.market_segment_id.get().has_value() ? std::to_string(value.market_segment_id.get().value()) : std::string_view("null"))
       << ",partition_id=" << (value.partition_id.get().has_value() ? std::to_string(value.partition_id.get().value()) : std::string_view("null"))
       << ",completion_indicator=\"" << fbe_eobi::completion_indicator::to_string(value.completion_indicator.get().value()) << '"'
       << ",appl_seq_reset_indicator=\"" << fbe_eobi::appl_seq_reset_indicator::to_string(value.appl_seq_reset_indicator.get().value()) << '"'
       << ",transact_time=" << (value.transact_time.get().has_value() ? std::to_string(value.transact_time.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const eobi_header& value) {
    os << "body_len=" << value.body_len.get().value()
       << ",template_id=\"" << fbe_eobi::template_id::to_string(value.template_id.get().value()) << '"'
       << ",msg_seq_num=" << value.msg_seq_num.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_complex_instrument& msg) {
    os << "security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",transact_time=" << (msg.fields.transact_time.get().has_value() ? std::to_string(msg.fields.transact_time.get().value()) : std::string_view("null"))
       << ",security_sub_type=" << (msg.fields.security_sub_type.get().has_value() ? std::to_string(msg.fields.security_sub_type.get().value()) : std::string_view("null"))
       << ",product_complex=\"" << fbe_eobi::product_complex::to_string(msg.fields.product_complex.get().value()) << '"'
       << ",implied_market_indicator=\"" << fbe_eobi::implied_market_indicator::to_string(msg.fields.implied_market_indicator.get().value()) << '"'
       << ",no_legs=" << (msg.fields.no_legs.get().has_value() ? std::to_string(msg.fields.no_legs.get().value()) : std::string_view("null"))
       << ",instrmt_leg_grp_comp.leg_symbol=" << (msg.fields.instrmt_leg_grp_comp.leg_symbol.get().has_value() ? std::to_string(msg.fields.instrmt_leg_grp_comp.leg_symbol.get().value()) : std::string_view("null"))
       << ",instrmt_leg_grp_comp.leg_security_id=" << (msg.fields.instrmt_leg_grp_comp.leg_security_id.get().has_value() ? std::to_string(msg.fields.instrmt_leg_grp_comp.leg_security_id.get().value()) : std::string_view("null"))
       << ",instrmt_leg_grp_comp.leg_ratio_qty=" << (msg.fields.instrmt_leg_grp_comp.leg_ratio_qty.get().has_value() ? std::to_string(msg.fields.instrmt_leg_grp_comp.leg_ratio_qty.get().value()) : std::string_view("null"))
       << ",instrmt_leg_grp_comp.leg_side=\"" << fbe_eobi::leg_side::to_string(msg.fields.instrmt_leg_grp_comp.leg_side.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const auction_bbo& msg) {
    os << "transact_time=" << (msg.fields.transact_time.get().has_value() ? std::to_string(msg.fields.transact_time.get().value()) : std::string_view("null"))
       << ",security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",bid_px=" << (msg.fields.bid_px.get().has_value() ? std::to_string(msg.fields.bid_px.get().value()) : std::string_view("null"))
       << ",offer_px=" << (msg.fields.offer_px.get().has_value() ? std::to_string(msg.fields.offer_px.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const auction_clearing_price& msg) {
    os << "transact_time=" << (msg.fields.transact_time.get().has_value() ? std::to_string(msg.fields.transact_time.get().value()) : std::string_view("null"))
       << ",security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",last_px=" << (msg.fields.last_px.get().has_value() ? std::to_string(msg.fields.last_px.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const cross_request& msg) {
    os << "security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",last_qty=" << (msg.fields.last_qty.get().has_value() ? std::to_string(msg.fields.last_qty.get().value()) : std::string_view("null"))
       << ",transact_time=" << (msg.fields.transact_time.get().has_value() ? std::to_string(msg.fields.transact_time.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const execution_summary& msg) {
    os << "security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",aggressor_timestamp=" << (msg.fields.aggressor_timestamp.get().has_value() ? std::to_string(msg.fields.aggressor_timestamp.get().value()) : std::string_view("null"))
       << ",request_time=" << (msg.fields.request_time.get().has_value() ? std::to_string(msg.fields.request_time.get().value()) : std::string_view("null"))
       << ",exec_id=" << (msg.fields.exec_id.get().has_value() ? std::to_string(msg.fields.exec_id.get().value()) : std::string_view("null"))
       << ",last_qty=" << (msg.fields.last_qty.get().has_value() ? std::to_string(msg.fields.last_qty.get().value()) : std::string_view("null"))
       << ",aggressor_side=\"" << fbe_eobi::aggressor_side::to_string(msg.fields.aggressor_side.get().value()) << '"'
       << ",trade_condition=\"" << fbe_eobi::trade_condition::to_string(msg.fields.trade_condition.get().value()) << '"'
       << ",last_px=" << (msg.fields.last_px.get().has_value() ? std::to_string(msg.fields.last_px.get().value()) : std::string_view("null"))
       << ",resting_hidden_qty=" << (msg.fields.resting_hidden_qty.get().has_value() ? std::to_string(msg.fields.resting_hidden_qty.get().value()) : std::string_view("null"))
       << ",resting_cxl_qty=" << (msg.fields.resting_cxl_qty.get().has_value() ? std::to_string(msg.fields.resting_cxl_qty.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const full_order_execution& msg) {
    os << "side=\"" << fbe_eobi::side::to_string(msg.fields.side.get().value()) << '"'
       << ",price=" << (msg.fields.price.get().has_value() ? std::to_string(msg.fields.price.get().value()) : std::string_view("null"))
       << ",trd_reg_ts_time_priority=" << (msg.fields.trd_reg_ts_time_priority.get().has_value() ? std::to_string(msg.fields.trd_reg_ts_time_priority.get().value()) : std::string_view("null"))
       << ",security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",trd_match_id=" << (msg.fields.trd_match_id.get().has_value() ? std::to_string(msg.fields.trd_match_id.get().value()) : std::string_view("null"))
       << ",last_qty=" << (msg.fields.last_qty.get().has_value() ? std::to_string(msg.fields.last_qty.get().value()) : std::string_view("null"))
       << ",last_px=" << (msg.fields.last_px.get().has_value() ? std::to_string(msg.fields.last_px.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const heartbeat& msg) {
    os << "last_msg_seq_num_processed=" << (msg.fields.last_msg_seq_num_processed.get().has_value() ? std::to_string(msg.fields.last_msg_seq_num_processed.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const instrument_state_change& msg) {
    os << "security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",security_status=\"" << fbe_eobi::security_status::to_string(msg.fields.security_status.get().value()) << '"'
       << ",security_trading_status=\"" << fbe_eobi::security_trading_status::to_string(msg.fields.security_trading_status.get().value()) << '"'
       << ",fast_market_indicator=\"" << fbe_eobi::fast_market_indicator::to_string(msg.fields.fast_market_indicator.get().value()) << '"'
       << ",transact_time=" << (msg.fields.transact_time.get().has_value() ? std::to_string(msg.fields.transact_time.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const instrument_summary& msg) {
    os << "security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",last_update_time=" << (msg.fields.last_update_time.get().has_value() ? std::to_string(msg.fields.last_update_time.get().value()) : std::string_view("null"))
       << ",trd_reg_ts_execution_time=" << (msg.fields.trd_reg_ts_execution_time.get().has_value() ? std::to_string(msg.fields.trd_reg_ts_execution_time.get().value()) : std::string_view("null"))
       << ",tot_no_orders=" << (msg.fields.tot_no_orders.get().has_value() ? std::to_string(msg.fields.tot_no_orders.get().value()) : std::string_view("null"))
       << ",security_status=\"" << fbe_eobi::security_status::to_string(msg.fields.security_status.get().value()) << '"'
       << ",security_trading_status=\"" << fbe_eobi::security_trading_status::to_string(msg.fields.security_trading_status.get().value()) << '"'
       << ",fast_market_indicator=\"" << fbe_eobi::fast_market_indicator::to_string(msg.fields.fast_market_indicator.get().value()) << '"'
       << ",no_md_entries=" << (msg.fields.no_md_entries.get().has_value() ? std::to_string(msg.fields.no_md_entries.get().value()) : std::string_view("null"))
       << ",md_instrument_entry_grp_comp.md_entry_px=" << (msg.fields.md_instrument_entry_grp_comp.md_entry_px.get().has_value() ? std::to_string(msg.fields.md_instrument_entry_grp_comp.md_entry_px.get().value()) : std::string_view("null"))
       << ",md_instrument_entry_grp_comp.md_entry_size=" << (msg.fields.md_instrument_entry_grp_comp.md_entry_size.get().has_value() ? std::to_string(msg.fields.md_instrument_entry_grp_comp.md_entry_size.get().value()) : std::string_view("null"))
       << ",md_instrument_entry_grp_comp.md_entry_type=\"" << fbe_eobi::md_entry_type::to_string(msg.fields.md_instrument_entry_grp_comp.md_entry_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_add& msg) {
    os << "trd_reg_ts_time_in=" << (msg.fields.trd_reg_ts_time_in.get().has_value() ? std::to_string(msg.fields.trd_reg_ts_time_in.get().value()) : std::string_view("null"))
       << ",security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",order_details_comp.trd_reg_ts_time_priority=" << (msg.fields.order_details_comp.trd_reg_ts_time_priority.get().has_value() ? std::to_string(msg.fields.order_details_comp.trd_reg_ts_time_priority.get().value()) : std::string_view("null"))
       << ",order_details_comp.display_qty=" << (msg.fields.order_details_comp.display_qty.get().has_value() ? std::to_string(msg.fields.order_details_comp.display_qty.get().value()) : std::string_view("null"))
       << ",order_details_comp.side=\"" << fbe_eobi::side::to_string(msg.fields.order_details_comp.side.get().value()) << '"'
       << ",order_details_comp.price=" << (msg.fields.order_details_comp.price.get().has_value() ? std::to_string(msg.fields.order_details_comp.price.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_delete& msg) {
    os << "trd_reg_ts_time_in=" << (msg.fields.trd_reg_ts_time_in.get().has_value() ? std::to_string(msg.fields.trd_reg_ts_time_in.get().value()) : std::string_view("null"))
       << ",transact_time=" << (msg.fields.transact_time.get().has_value() ? std::to_string(msg.fields.transact_time.get().value()) : std::string_view("null"))
       << ",security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",order_details_comp.trd_reg_ts_time_priority=" << (msg.fields.order_details_comp.trd_reg_ts_time_priority.get().has_value() ? std::to_string(msg.fields.order_details_comp.trd_reg_ts_time_priority.get().value()) : std::string_view("null"))
       << ",order_details_comp.display_qty=" << (msg.fields.order_details_comp.display_qty.get().has_value() ? std::to_string(msg.fields.order_details_comp.display_qty.get().value()) : std::string_view("null"))
       << ",order_details_comp.side=\"" << fbe_eobi::side::to_string(msg.fields.order_details_comp.side.get().value()) << '"'
       << ",order_details_comp.price=" << (msg.fields.order_details_comp.price.get().has_value() ? std::to_string(msg.fields.order_details_comp.price.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_mass_delete& msg) {
    os << "security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",transact_time=" << (msg.fields.transact_time.get().has_value() ? std::to_string(msg.fields.transact_time.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_modify& msg) {
    os << "trd_reg_ts_time_in=" << (msg.fields.trd_reg_ts_time_in.get().has_value() ? std::to_string(msg.fields.trd_reg_ts_time_in.get().value()) : std::string_view("null"))
       << ",trd_reg_ts_prev_time_priority=" << (msg.fields.trd_reg_ts_prev_time_priority.get().has_value() ? std::to_string(msg.fields.trd_reg_ts_prev_time_priority.get().value()) : std::string_view("null"))
       << ",prev_price=" << (msg.fields.prev_price.get().has_value() ? std::to_string(msg.fields.prev_price.get().value()) : std::string_view("null"))
       << ",prev_display_qty=" << (msg.fields.prev_display_qty.get().has_value() ? std::to_string(msg.fields.prev_display_qty.get().value()) : std::string_view("null"))
       << ",security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",order_details_comp.trd_reg_ts_time_priority=" << (msg.fields.order_details_comp.trd_reg_ts_time_priority.get().has_value() ? std::to_string(msg.fields.order_details_comp.trd_reg_ts_time_priority.get().value()) : std::string_view("null"))
       << ",order_details_comp.display_qty=" << (msg.fields.order_details_comp.display_qty.get().has_value() ? std::to_string(msg.fields.order_details_comp.display_qty.get().value()) : std::string_view("null"))
       << ",order_details_comp.side=\"" << fbe_eobi::side::to_string(msg.fields.order_details_comp.side.get().value()) << '"'
       << ",order_details_comp.price=" << (msg.fields.order_details_comp.price.get().has_value() ? std::to_string(msg.fields.order_details_comp.price.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_modify_same_prio& msg) {
    os << "trd_reg_ts_time_in=" << (msg.fields.trd_reg_ts_time_in.get().has_value() ? std::to_string(msg.fields.trd_reg_ts_time_in.get().value()) : std::string_view("null"))
       << ",transact_time=" << (msg.fields.transact_time.get().has_value() ? std::to_string(msg.fields.transact_time.get().value()) : std::string_view("null"))
       << ",prev_display_qty=" << (msg.fields.prev_display_qty.get().has_value() ? std::to_string(msg.fields.prev_display_qty.get().value()) : std::string_view("null"))
       << ",security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",order_details_comp.trd_reg_ts_time_priority=" << (msg.fields.order_details_comp.trd_reg_ts_time_priority.get().has_value() ? std::to_string(msg.fields.order_details_comp.trd_reg_ts_time_priority.get().value()) : std::string_view("null"))
       << ",order_details_comp.display_qty=" << (msg.fields.order_details_comp.display_qty.get().has_value() ? std::to_string(msg.fields.order_details_comp.display_qty.get().value()) : std::string_view("null"))
       << ",order_details_comp.side=\"" << fbe_eobi::side::to_string(msg.fields.order_details_comp.side.get().value()) << '"'
       << ",order_details_comp.price=" << (msg.fields.order_details_comp.price.get().has_value() ? std::to_string(msg.fields.order_details_comp.price.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const partial_order_execution& msg) {
    os << "side=\"" << fbe_eobi::side::to_string(msg.fields.side.get().value()) << '"'
       << ",price=" << (msg.fields.price.get().has_value() ? std::to_string(msg.fields.price.get().value()) : std::string_view("null"))
       << ",trd_reg_ts_time_priority=" << (msg.fields.trd_reg_ts_time_priority.get().has_value() ? std::to_string(msg.fields.trd_reg_ts_time_priority.get().value()) : std::string_view("null"))
       << ",security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",trd_match_id=" << (msg.fields.trd_match_id.get().has_value() ? std::to_string(msg.fields.trd_match_id.get().value()) : std::string_view("null"))
       << ",last_qty=" << (msg.fields.last_qty.get().has_value() ? std::to_string(msg.fields.last_qty.get().value()) : std::string_view("null"))
       << ",last_px=" << (msg.fields.last_px.get().has_value() ? std::to_string(msg.fields.last_px.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const product_state_change& msg) {
    os << "trading_session_id=\"" << fbe_eobi::trading_session_id::to_string(msg.fields.trading_session_id.get().value()) << '"'
       << ",trading_session_sub_id=\"" << fbe_eobi::trading_session_sub_id::to_string(msg.fields.trading_session_sub_id.get().value()) << '"'
       << ",trad_ses_status=\"" << fbe_eobi::trad_ses_status::to_string(msg.fields.trad_ses_status.get().value()) << '"'
       << ",fast_market_indicator=\"" << fbe_eobi::fast_market_indicator::to_string(msg.fields.fast_market_indicator.get().value()) << '"'
       << ",transact_time=" << (msg.fields.transact_time.get().has_value() ? std::to_string(msg.fields.transact_time.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const product_summary& msg) {
    os << "last_msg_seq_num_processed=" << (msg.fields.last_msg_seq_num_processed.get().has_value() ? std::to_string(msg.fields.last_msg_seq_num_processed.get().value()) : std::string_view("null"))
       << ",trading_session_id=\"" << fbe_eobi::trading_session_id::to_string(msg.fields.trading_session_id.get().value()) << '"'
       << ",trading_session_sub_id=\"" << fbe_eobi::trading_session_sub_id::to_string(msg.fields.trading_session_sub_id.get().value()) << '"'
       << ",trad_ses_status=\"" << fbe_eobi::trad_ses_status::to_string(msg.fields.trad_ses_status.get().value()) << '"'
       << ",fast_market_indicator=\"" << fbe_eobi::fast_market_indicator::to_string(msg.fields.fast_market_indicator.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const quote_request& msg) {
    os << "security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",last_qty=" << (msg.fields.last_qty.get().has_value() ? std::to_string(msg.fields.last_qty.get().value()) : std::string_view("null"))
       << ",side=\"" << fbe_eobi::side::to_string(msg.fields.side.get().value()) << '"'
       << ",transact_time=" << (msg.fields.transact_time.get().has_value() ? std::to_string(msg.fields.transact_time.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const snapshot_order& msg) {
    os << "order_details_comp.trd_reg_ts_time_priority=" << (msg.fields.order_details_comp.trd_reg_ts_time_priority.get().has_value() ? std::to_string(msg.fields.order_details_comp.trd_reg_ts_time_priority.get().value()) : std::string_view("null"))
       << ",order_details_comp.display_qty=" << (msg.fields.order_details_comp.display_qty.get().has_value() ? std::to_string(msg.fields.order_details_comp.display_qty.get().value()) : std::string_view("null"))
       << ",order_details_comp.side=\"" << fbe_eobi::side::to_string(msg.fields.order_details_comp.side.get().value()) << '"'
       << ",order_details_comp.price=" << (msg.fields.order_details_comp.price.get().has_value() ? std::to_string(msg.fields.order_details_comp.price.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const top_of_book& msg) {
    os << "transact_time=" << (msg.fields.transact_time.get().has_value() ? std::to_string(msg.fields.transact_time.get().value()) : std::string_view("null"))
       << ",security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",bid_px=" << (msg.fields.bid_px.get().has_value() ? std::to_string(msg.fields.bid_px.get().value()) : std::string_view("null"))
       << ",offer_px=" << (msg.fields.offer_px.get().has_value() ? std::to_string(msg.fields.offer_px.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_report& msg) {
    os << "security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",transact_time=" << (msg.fields.transact_time.get().has_value() ? std::to_string(msg.fields.transact_time.get().value()) : std::string_view("null"))
       << ",trd_match_id=" << (msg.fields.trd_match_id.get().has_value() ? std::to_string(msg.fields.trd_match_id.get().value()) : std::string_view("null"))
       << ",last_qty=" << (msg.fields.last_qty.get().has_value() ? std::to_string(msg.fields.last_qty.get().value()) : std::string_view("null"))
       << ",last_px=" << (msg.fields.last_px.get().has_value() ? std::to_string(msg.fields.last_px.get().value()) : std::string_view("null"))
       << ",match_type=\"" << fbe_eobi::match_type::to_string(msg.fields.match_type.get().value()) << '"'
       << ",match_sub_type=\"" << fbe_eobi::match_sub_type::to_string(msg.fields.match_sub_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_reversal& msg) {
    os << "security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",transact_time=" << (msg.fields.transact_time.get().has_value() ? std::to_string(msg.fields.transact_time.get().value()) : std::string_view("null"))
       << ",trd_match_id=" << (msg.fields.trd_match_id.get().has_value() ? std::to_string(msg.fields.trd_match_id.get().value()) : std::string_view("null"))
       << ",last_qty=" << (msg.fields.last_qty.get().has_value() ? std::to_string(msg.fields.last_qty.get().value()) : std::string_view("null"))
       << ",last_px=" << (msg.fields.last_px.get().has_value() ? std::to_string(msg.fields.last_px.get().value()) : std::string_view("null"))
       << ",trd_reg_ts_execution_time=" << (msg.fields.trd_reg_ts_execution_time.get().has_value() ? std::to_string(msg.fields.trd_reg_ts_execution_time.get().value()) : std::string_view("null"))
       << ",no_md_entries=" << (msg.fields.no_md_entries.get().has_value() ? std::to_string(msg.fields.no_md_entries.get().value()) : std::string_view("null"))
       << ",md_trade_entry_grp_comp.md_entry_px=" << (msg.fields.md_trade_entry_grp_comp.md_entry_px.get().has_value() ? std::to_string(msg.fields.md_trade_entry_grp_comp.md_entry_px.get().value()) : std::string_view("null"))
       << ",md_trade_entry_grp_comp.md_entry_size=" << (msg.fields.md_trade_entry_grp_comp.md_entry_size.get().has_value() ? std::to_string(msg.fields.md_trade_entry_grp_comp.md_entry_size.get().value()) : std::string_view("null"))
       << ",md_trade_entry_grp_comp.md_entry_type=\"" << fbe_eobi::md_entry_type::to_string(msg.fields.md_trade_entry_grp_comp.md_entry_type.get().value()) << '"'
       ;
    return os;
}

}
