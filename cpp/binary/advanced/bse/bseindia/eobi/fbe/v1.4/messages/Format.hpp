#pragma once

#include <ostream>
#include <string_view>

#include "HeartbeatMessage.hpp"
#include "ProductSummaryMessage.hpp"
#include "SnapshotOrderMessage.hpp"
#include "InstrumentSummaryMessage.hpp"
#include "AuctionBestBidOfferMessage.hpp"
#include "AuctionClearingPriceMessage.hpp"
#include "TopOfBookMessage.hpp"
#include "OrderAddMessage.hpp"
#include "OrderModifyMessage.hpp"
#include "OrderModifySamePriorityMessage.hpp"
#include "OrderDeleteMessage.hpp"
#include "OrderMassDeleteMessage.hpp"
#include "PartialOrderExecutionMessage.hpp"
#include "FullOrderExecutionMessage.hpp"
#include "TradeReversalMessage.hpp"
#include "ExecutionSummaryMessage.hpp"
#include "InstrumentInfoMessage.hpp"
#include "LppRangeMessage.hpp"
#include "ProductStateChangeMessage.hpp"
#include "InstrumentStateChangeMessage.hpp"
#include "AddComplexInstrumentMessage.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

namespace fbe_eobi = ::bse::bseindia::eobi::fbe::v1_4;

inline std::ostream& operator<<(std::ostream& os, const packet_header& value) {
    os << "eobi_header.body_len=" << value.eobi_header.body_len.get().value()
       << ",eobi_header.template_id=\"" << fbe_eobi::template_id::to_string(value.eobi_header.template_id.get().value()) << '"'
       << ",eobi_header.msg_seq_num=" << value.eobi_header.msg_seq_num.get().value()
       << ",appl_seq_num=" << value.appl_seq_num.get().value()
       << ",market_segment_id=" << value.market_segment_id.get().value()
       << ",partition_id=" << static_cast<unsigned>(value.partition_id.get().value())
       << ",completion_indicator=" << static_cast<unsigned>(value.completion_indicator.get().value())
       << ",appl_seq_reset_indicator=" << static_cast<unsigned>(value.appl_seq_reset_indicator.get().value())
       << ",transact_time=" << value.transact_time.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "body_len=" << value.body_len.get().value()
       << ",template_id=\"" << fbe_eobi::template_id::to_string(value.template_id.get().value()) << '"'
       << ",msg_seq_num=" << value.msg_seq_num.get().value()
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

inline std::ostream& operator<<(std::ostream& os, const heartbeat_message& msg) {
    os << "last_msg_seq_num_processed=" << msg.fields.last_msg_seq_num_processed.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const product_summary_message& msg) {
    os << "last_msg_seq_num_processed=" << msg.fields.last_msg_seq_num_processed.get().value()
       << ",trading_session_id=\"" << fbe_eobi::trading_session_id::to_string(msg.fields.trading_session_id.get().value()) << '"'
       << ",trading_session_sub_id=\"" << fbe_eobi::trading_session_sub_id::to_string(msg.fields.trading_session_sub_id.get().value()) << '"'
       << ",trad_ses_status=\"" << fbe_eobi::trad_ses_status::to_string(msg.fields.trad_ses_status.get().value()) << '"'
       << ",fast_market_indicator=\"" << fbe_eobi::fast_market_indicator::to_string(msg.fields.fast_market_indicator.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const snapshot_order_message& msg) {
    os << "order_details.trd_reg_ts_time_priority=" << msg.fields.order_details.trd_reg_ts_time_priority.get().value()
       << ",order_details.display_qty=" << msg.fields.order_details.display_qty.get().value()
       << ",order_details.side=\"" << fbe_eobi::side::to_string(msg.fields.order_details.side.get().value()) << '"'
       << ",order_details.price=" << msg.fields.order_details.price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const instrument_summary_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",last_update_time=" << msg.fields.last_update_time.get().value()
       << ",trd_reg_ts_execution_time=" << (msg.fields.trd_reg_ts_execution_time.get().has_value() ? std::to_string(msg.fields.trd_reg_ts_execution_time.get().value()) : std::string_view("null"))
       << ",tot_no_orders=" << msg.fields.tot_no_orders.get().value()
       << ",security_status=\"" << fbe_eobi::security_status::to_string(msg.fields.security_status.get().value()) << '"'
       << ",security_trading_status=\"" << fbe_eobi::security_trading_status::to_string(msg.fields.security_trading_status.get().value()) << '"'
       << ",fast_market_indicator=\"" << fbe_eobi::fast_market_indicator::to_string(msg.fields.fast_market_indicator.get().value()) << '"'
       << ",no_md_entries=" << static_cast<unsigned>(msg.fields.no_md_entries.get().value())
       << ",trade_volume=" << msg.fields.trade_volume.get().value()
       << ",no_of_trades=" << msg.fields.no_of_trades.get().value()
       << ",md_instrument_entry_grp.md_entry_px=" << (msg.fields.md_instrument_entry_grp.md_entry_px.get().has_value() ? std::to_string(msg.fields.md_instrument_entry_grp.md_entry_px.get().value()) : std::string_view("null"))
       << ",md_instrument_entry_grp.md_entry_size=" << (msg.fields.md_instrument_entry_grp.md_entry_size.get().has_value() ? std::to_string(msg.fields.md_instrument_entry_grp.md_entry_size.get().value()) : std::string_view("null"))
       << ",md_instrument_entry_grp.md_entry_type=\"" << fbe_eobi::md_entry_type::to_string(msg.fields.md_instrument_entry_grp.md_entry_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const auction_best_bid_offer_message& msg) {
    os << "transact_time=" << msg.fields.transact_time.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",bid_px=" << (msg.fields.bid_px.get().has_value() ? std::to_string(msg.fields.bid_px.get().value()) : std::string_view("null"))
       << ",offer_px=" << (msg.fields.offer_px.get().has_value() ? std::to_string(msg.fields.offer_px.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const auction_clearing_price_message& msg) {
    os << "transact_time=" << msg.fields.transact_time.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",last_px=" << msg.fields.last_px.get().value()
       << ",last_qty=" << msg.fields.last_qty.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const top_of_book_message& msg) {
    os << "transact_time=" << msg.fields.transact_time.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",bid_px=" << (msg.fields.bid_px.get().has_value() ? std::to_string(msg.fields.bid_px.get().value()) : std::string_view("null"))
       << ",offer_px=" << (msg.fields.offer_px.get().has_value() ? std::to_string(msg.fields.offer_px.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_add_message& msg) {
    os << "trd_reg_ts_time_in=" << (msg.fields.trd_reg_ts_time_in.get().has_value() ? std::to_string(msg.fields.trd_reg_ts_time_in.get().value()) : std::string_view("null"))
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",order_details.trd_reg_ts_time_priority=" << msg.fields.order_details.trd_reg_ts_time_priority.get().value()
       << ",order_details.display_qty=" << msg.fields.order_details.display_qty.get().value()
       << ",order_details.side=\"" << fbe_eobi::side::to_string(msg.fields.order_details.side.get().value()) << '"'
       << ",order_details.price=" << msg.fields.order_details.price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_modify_message& msg) {
    os << "trd_reg_ts_time_in=" << (msg.fields.trd_reg_ts_time_in.get().has_value() ? std::to_string(msg.fields.trd_reg_ts_time_in.get().value()) : std::string_view("null"))
       << ",trd_reg_ts_prev_time_priority=" << msg.fields.trd_reg_ts_prev_time_priority.get().value()
       << ",prev_price=" << msg.fields.prev_price.get().value()
       << ",prev_display_qty=" << msg.fields.prev_display_qty.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",order_details.trd_reg_ts_time_priority=" << msg.fields.order_details.trd_reg_ts_time_priority.get().value()
       << ",order_details.display_qty=" << msg.fields.order_details.display_qty.get().value()
       << ",order_details.side=\"" << fbe_eobi::side::to_string(msg.fields.order_details.side.get().value()) << '"'
       << ",order_details.price=" << msg.fields.order_details.price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_modify_same_priority_message& msg) {
    os << "trd_reg_ts_time_in=" << (msg.fields.trd_reg_ts_time_in.get().has_value() ? std::to_string(msg.fields.trd_reg_ts_time_in.get().value()) : std::string_view("null"))
       << ",transact_time=" << msg.fields.transact_time.get().value()
       << ",prev_display_qty=" << msg.fields.prev_display_qty.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",order_details.trd_reg_ts_time_priority=" << msg.fields.order_details.trd_reg_ts_time_priority.get().value()
       << ",order_details.display_qty=" << msg.fields.order_details.display_qty.get().value()
       << ",order_details.side=\"" << fbe_eobi::side::to_string(msg.fields.order_details.side.get().value()) << '"'
       << ",order_details.price=" << msg.fields.order_details.price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_delete_message& msg) {
    os << "trd_reg_ts_time_in=" << (msg.fields.trd_reg_ts_time_in.get().has_value() ? std::to_string(msg.fields.trd_reg_ts_time_in.get().value()) : std::string_view("null"))
       << ",transact_time=" << msg.fields.transact_time.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",order_details.trd_reg_ts_time_priority=" << msg.fields.order_details.trd_reg_ts_time_priority.get().value()
       << ",order_details.display_qty=" << msg.fields.order_details.display_qty.get().value()
       << ",order_details.side=\"" << fbe_eobi::side::to_string(msg.fields.order_details.side.get().value()) << '"'
       << ",order_details.price=" << msg.fields.order_details.price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_mass_delete_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",transact_time=" << msg.fields.transact_time.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const partial_order_execution_message& msg) {
    os << "side=\"" << fbe_eobi::side::to_string(msg.fields.side.get().value()) << '"'
       << ",price=" << msg.fields.price.get().value()
       << ",trd_reg_ts_time_priority=" << msg.fields.trd_reg_ts_time_priority.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",trd_match_id=" << msg.fields.trd_match_id.get().value()
       << ",last_qty=" << msg.fields.last_qty.get().value()
       << ",last_px=" << msg.fields.last_px.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const full_order_execution_message& msg) {
    os << "side=\"" << fbe_eobi::side::to_string(msg.fields.side.get().value()) << '"'
       << ",price=" << msg.fields.price.get().value()
       << ",trd_reg_ts_time_priority=" << msg.fields.trd_reg_ts_time_priority.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",trd_match_id=" << msg.fields.trd_match_id.get().value()
       << ",last_qty=" << msg.fields.last_qty.get().value()
       << ",last_px=" << msg.fields.last_px.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_reversal_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",transact_time=" << msg.fields.transact_time.get().value()
       << ",trd_match_id=" << msg.fields.trd_match_id.get().value()
       << ",last_qty=" << msg.fields.last_qty.get().value()
       << ",last_px=" << msg.fields.last_px.get().value()
       << ",trd_reg_ts_execution_time=" << (msg.fields.trd_reg_ts_execution_time.get().has_value() ? std::to_string(msg.fields.trd_reg_ts_execution_time.get().value()) : std::string_view("null"))
       << ",no_md_entries=" << static_cast<unsigned>(msg.fields.no_md_entries.get().value())
       << ",md_trade_entry_grp.md_entry_px=" << (msg.fields.md_trade_entry_grp.md_entry_px.get().has_value() ? std::to_string(msg.fields.md_trade_entry_grp.md_entry_px.get().value()) : std::string_view("null"))
       << ",md_trade_entry_grp.md_entry_size=" << (msg.fields.md_trade_entry_grp.md_entry_size.get().has_value() ? std::to_string(msg.fields.md_trade_entry_grp.md_entry_size.get().value()) : std::string_view("null"))
       << ",md_trade_entry_grp.md_entry_type=\"" << fbe_eobi::md_entry_type::to_string(msg.fields.md_trade_entry_grp.md_entry_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const execution_summary_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",aggressor_timestamp=" << (msg.fields.aggressor_timestamp.get().has_value() ? std::to_string(msg.fields.aggressor_timestamp.get().value()) : std::string_view("null"))
       << ",exec_id=" << msg.fields.exec_id.get().value()
       << ",last_qty=" << msg.fields.last_qty.get().value()
       << ",aggressor_side=\"" << fbe_eobi::aggressor_side::to_string(msg.fields.aggressor_side.get().value()) << '"'
       << ",trade_condition=\"" << fbe_eobi::trade_condition::to_string(msg.fields.trade_condition.get().value()) << '"'
       << ",last_px=" << msg.fields.last_px.get().value()
       << ",resting_hidden_qty=" << (msg.fields.resting_hidden_qty.get().has_value() ? std::to_string(msg.fields.resting_hidden_qty.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const instrument_info_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",close_price=" << (msg.fields.close_price.get().has_value() ? std::to_string(msg.fields.close_price.get().value()) : std::string_view("null"))
       << ",prev_close_price=" << (msg.fields.prev_close_price.get().has_value() ? std::to_string(msg.fields.prev_close_price.get().value()) : std::string_view("null"))
       << ",upper_ckt_limit=" << (msg.fields.upper_ckt_limit.get().has_value() ? std::to_string(msg.fields.upper_ckt_limit.get().value()) : std::string_view("null"))
       << ",lower_ckt_limit=" << (msg.fields.lower_ckt_limit.get().has_value() ? std::to_string(msg.fields.lower_ckt_limit.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const lpp_range_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",upper_exec_limit=" << msg.fields.upper_exec_limit.get().value()
       << ",lower_exec_limit=" << msg.fields.lower_exec_limit.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const product_state_change_message& msg) {
    os << "trading_session_id=\"" << fbe_eobi::trading_session_id::to_string(msg.fields.trading_session_id.get().value()) << '"'
       << ",trading_session_sub_id=\"" << fbe_eobi::trading_session_sub_id::to_string(msg.fields.trading_session_sub_id.get().value()) << '"'
       << ",trad_ses_status=\"" << fbe_eobi::trad_ses_status::to_string(msg.fields.trad_ses_status.get().value()) << '"'
       << ",fast_market_indicator=\"" << fbe_eobi::fast_market_indicator::to_string(msg.fields.fast_market_indicator.get().value()) << '"'
       << ",transact_time=" << msg.fields.transact_time.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const instrument_state_change_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",security_status=\"" << fbe_eobi::security_status::to_string(msg.fields.security_status.get().value()) << '"'
       << ",security_trading_status=\"" << fbe_eobi::security_trading_status::to_string(msg.fields.security_trading_status.get().value()) << '"'
       << ",fast_market_indicator=\"" << fbe_eobi::fast_market_indicator::to_string(msg.fields.fast_market_indicator.get().value()) << '"'
       << ",transact_time=" << msg.fields.transact_time.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_complex_instrument_message& msg) {
    os << "security_id=" << msg.fields.security_id.get().value()
       << ",transact_time=" << msg.fields.transact_time.get().value()
       << ",security_sub_type=" << (msg.fields.security_sub_type.get().has_value() ? std::to_string(msg.fields.security_sub_type.get().value()) : std::string_view("null"))
       << ",product_complex=\"" << fbe_eobi::product_complex::to_string(msg.fields.product_complex.get().value()) << '"'
       << ",implied_market_indicator=\"" << fbe_eobi::implied_market_indicator::to_string(msg.fields.implied_market_indicator.get().value()) << '"'
       << ",no_legs=" << static_cast<unsigned>(msg.fields.no_legs.get().value())
       << ",instrmt_leg_grp.leg_security_id=" << msg.fields.instrmt_leg_grp.leg_security_id.get().value()
       << ",instrmt_leg_grp.leg_ratio_qty=" << (msg.fields.instrmt_leg_grp.leg_ratio_qty.get().has_value() ? std::to_string(msg.fields.instrmt_leg_grp.leg_ratio_qty.get().value()) : std::string_view("null"))
       << ",instrmt_leg_grp.leg_side=\"" << fbe_eobi::leg_side::to_string(msg.fields.instrmt_leg_grp.leg_side.get().value()) << '"'
       ;
    return os;
}

}
