#pragma once

#include <ostream>
#include <string_view>

#include "AddComplexInstrument.hpp"
#include "AddFlexibleInstrument.hpp"
#include "AddScaledSimpleInstrument.hpp"
#include "AuctionBbo.hpp"
#include "AuctionClearingPrice.hpp"
#include "CrossRequest.hpp"
#include "ExecutionSummary.hpp"
#include "FullOrderExecution.hpp"
#include "Heartbeat.hpp"
#include "InstrumentStateChange.hpp"
#include "InstrumentSummary.hpp"
#include "MassInstrumentStateChange.hpp"
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
#include "TesTradeReport.hpp"
#include "TopOfBook.hpp"
#include "TradeReport.hpp"
#include "TradeReversal.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v15_0;

inline std::ostream& operator<<(std::ostream& os, const packet_header& value) {
    os << "eobi_header.body_len=" << value.eobi_header.body_len.get().value()
       << ",eobi_header.template_id=\"" << fbe_eobi::template_id::to_string(value.eobi_header.template_id.get().value()) << '"'
       << ",eobi_header.msg_seq_num=" << value.eobi_header.msg_seq_num.get().value()
       << ",appl_seq_num=" << value.appl_seq_num.get().value()
       << ",market_segment_id=" << (value.market_segment_id.get().has_value() ? std::to_string(value.market_segment_id.get().value()) : std::string_view("null"))
       << ",partition_id=" << (value.partition_id.get().has_value() ? std::to_string(value.partition_id.get().value()) : std::string_view("null"))
       << ",completion_indicator=\"" << fbe_eobi::completion_indicator::to_string(value.completion_indicator.get().value()) << '"'
       << ",appl_seq_reset_indicator=\"" << fbe_eobi::appl_seq_reset_indicator::to_string(value.appl_seq_reset_indicator.get().value()) << '"'
       << ",dscp=" << static_cast<unsigned>(value.dscp.get().value())
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
       << ",security_desc=\"" << (msg.fields.security_desc.get_trimmed().has_value() ? msg.fields.security_desc.get_trimmed().value() : std::string_view("null")) << '"'
       << ",security_sub_type=" << (msg.fields.security_sub_type.get().has_value() ? std::to_string(msg.fields.security_sub_type.get().value()) : std::string_view("null"))
       << ",product_complex=\"" << fbe_eobi::product_complex::to_string(msg.fields.product_complex.get().value()) << '"'
       << ",implied_market_indicator=\"" << fbe_eobi::implied_market_indicator::to_string(msg.fields.implied_market_indicator.get().value()) << '"'
       << ",quantity_scaling_factor=" << (msg.fields.quantity_scaling_factor.get().has_value() ? std::to_string(msg.fields.quantity_scaling_factor.get().value()) : std::string_view("null"))
       << ",leg_ratio_multiplier=" << (msg.fields.leg_ratio_multiplier.get().has_value() ? std::to_string(msg.fields.leg_ratio_multiplier.get().value()) : std::string_view("null"))
       << ",no_legs=" << (msg.fields.no_legs.get().has_value() ? std::to_string(msg.fields.no_legs.get().value()) : std::string_view("null"))
       << ",last_fragment=\"" << fbe_eobi::last_fragment::to_string(msg.fields.last_fragment.get().value()) << '"'
       << ",instrmt_leg_grp_comp.leg_symbol=" << (msg.fields.instrmt_leg_grp_comp.leg_symbol.get().has_value() ? std::to_string(msg.fields.instrmt_leg_grp_comp.leg_symbol.get().value()) : std::string_view("null"))
       << ",instrmt_leg_grp_comp.leg_security_id=" << (msg.fields.instrmt_leg_grp_comp.leg_security_id.get().has_value() ? std::to_string(msg.fields.instrmt_leg_grp_comp.leg_security_id.get().value()) : std::string_view("null"))
       << ",instrmt_leg_grp_comp.leg_price=" << (msg.fields.instrmt_leg_grp_comp.leg_price.get().has_value() ? std::to_string(msg.fields.instrmt_leg_grp_comp.leg_price.get().value()) : std::string_view("null"))
       << ",instrmt_leg_grp_comp.leg_ratio_qty=" << (msg.fields.instrmt_leg_grp_comp.leg_ratio_qty.get().has_value() ? std::to_string(msg.fields.instrmt_leg_grp_comp.leg_ratio_qty.get().value()) : std::string_view("null"))
       << ",instrmt_leg_grp_comp.leg_security_type=\"" << fbe_eobi::leg_security_type::to_string(msg.fields.instrmt_leg_grp_comp.leg_security_type.get().value()) << '"'
       << ",instrmt_leg_grp_comp.leg_side=\"" << fbe_eobi::leg_side::to_string(msg.fields.instrmt_leg_grp_comp.leg_side.get().value()) << '"'
       << ",instrmt_leg_grp_comp.related_price_type=\"" << fbe_eobi::related_price_type::to_string(msg.fields.instrmt_leg_grp_comp.related_price_type.get().value()) << '"'
       << ",instrmt_leg_grp_comp.trading_style=\"" << fbe_eobi::trading_style::to_string(msg.fields.instrmt_leg_grp_comp.trading_style.get().value()) << '"'
       << ",instrmt_leg_grp_comp.related_price=" << (msg.fields.instrmt_leg_grp_comp.related_price.get().has_value() ? std::to_string(msg.fields.instrmt_leg_grp_comp.related_price.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_flexible_instrument& msg) {
    os << "security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",transact_time=" << (msg.fields.transact_time.get().has_value() ? std::to_string(msg.fields.transact_time.get().value()) : std::string_view("null"))
       << ",security_desc=\"" << (msg.fields.security_desc.get_trimmed().has_value() ? msg.fields.security_desc.get_trimmed().value() : std::string_view("null")) << '"'
       << ",security_type=\"" << fbe_eobi::security_type::to_string(msg.fields.security_type.get().value()) << '"'
       << ",put_or_call=\"" << fbe_eobi::put_or_call::to_string(msg.fields.put_or_call.get().value()) << '"'
       << ",exercise_style=\"" << fbe_eobi::exercise_style::to_string(msg.fields.exercise_style.get().value()) << '"'
       << ",settl_method=\"" << fbe_eobi::settl_method::to_string(msg.fields.settl_method.get().value()) << '"'
       << ",maturity_date=" << (msg.fields.maturity_date.get().has_value() ? std::to_string(msg.fields.maturity_date.get().value()) : std::string_view("null"))
       << ",strike_price=" << (msg.fields.strike_price.get().has_value() ? std::to_string(msg.fields.strike_price.get().value()) : std::string_view("null"))
       << ",opt_attribute=" << (msg.fields.opt_attribute.get().has_value() ? std::to_string(msg.fields.opt_attribute.get().value()) : std::string_view("null"))
       << ",contract_date=" << (msg.fields.contract_date.get().has_value() ? std::to_string(msg.fields.contract_date.get().value()) : std::string_view("null"))
       << ",security_reference_data_supplement=" << (msg.fields.security_reference_data_supplement.get().has_value() ? std::to_string(msg.fields.security_reference_data_supplement.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_scaled_simple_instrument& msg) {
    os << "security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",transact_time=" << (msg.fields.transact_time.get().has_value() ? std::to_string(msg.fields.transact_time.get().value()) : std::string_view("null"))
       << ",security_desc=\"" << (msg.fields.security_desc.get_trimmed().has_value() ? msg.fields.security_desc.get_trimmed().value() : std::string_view("null")) << '"'
       << ",security_type=\"" << fbe_eobi::security_type::to_string(msg.fields.security_type.get().value()) << '"'
       << ",quantity_scaling_factor=" << (msg.fields.quantity_scaling_factor.get().has_value() ? std::to_string(msg.fields.quantity_scaling_factor.get().value()) : std::string_view("null"))
       << ",related_instrument_grp_comp.related_security_id=" << (msg.fields.related_instrument_grp_comp.related_security_id.get().has_value() ? std::to_string(msg.fields.related_instrument_grp_comp.related_security_id.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const auction_bbo& msg) {
    os << "transact_time=" << (msg.fields.transact_time.get().has_value() ? std::to_string(msg.fields.transact_time.get().value()) : std::string_view("null"))
       << ",security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",bid_px=" << (msg.fields.bid_px.get().has_value() ? std::to_string(msg.fields.bid_px.get().value()) : std::string_view("null"))
       << ",offer_px=" << (msg.fields.offer_px.get().has_value() ? std::to_string(msg.fields.offer_px.get().value()) : std::string_view("null"))
       << ",bid_size=" << (msg.fields.bid_size.get().has_value() ? std::to_string(msg.fields.bid_size.get().value()) : std::string_view("null"))
       << ",offer_size=" << (msg.fields.offer_size.get().has_value() ? std::to_string(msg.fields.offer_size.get().value()) : std::string_view("null"))
       << ",potential_security_trading_event=\"" << fbe_eobi::potential_security_trading_event::to_string(msg.fields.potential_security_trading_event.get().value()) << '"'
       << ",bid_ord_type=\"" << fbe_eobi::bid_ord_type::to_string(msg.fields.bid_ord_type.get().value()) << '"'
       << ",offer_ord_type=\"" << fbe_eobi::offer_ord_type::to_string(msg.fields.offer_ord_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const auction_clearing_price& msg) {
    os << "transact_time=" << (msg.fields.transact_time.get().has_value() ? std::to_string(msg.fields.transact_time.get().value()) : std::string_view("null"))
       << ",security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",last_px=" << (msg.fields.last_px.get().has_value() ? std::to_string(msg.fields.last_px.get().value()) : std::string_view("null"))
       << ",last_qty=" << (msg.fields.last_qty.get().has_value() ? std::to_string(msg.fields.last_qty.get().value()) : std::string_view("null"))
       << ",imbalance_qty=" << (msg.fields.imbalance_qty.get().has_value() ? std::to_string(msg.fields.imbalance_qty.get().value()) : std::string_view("null"))
       << ",security_trading_status=\"" << fbe_eobi::security_trading_status::to_string(msg.fields.security_trading_status.get().value()) << '"'
       << ",potential_security_trading_event=\"" << fbe_eobi::potential_security_trading_event::to_string(msg.fields.potential_security_trading_event.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const cross_request& msg) {
    os << "security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",last_px=" << (msg.fields.last_px.get().has_value() ? std::to_string(msg.fields.last_px.get().value()) : std::string_view("null"))
       << ",last_qty=" << (msg.fields.last_qty.get().has_value() ? std::to_string(msg.fields.last_qty.get().value()) : std::string_view("null"))
       << ",side=\"" << fbe_eobi::side::to_string(msg.fields.side.get().value()) << '"'
       << ",cross_request_type=\"" << fbe_eobi::cross_request_type::to_string(msg.fields.cross_request_type.get().value()) << '"'
       << ",input_source=\"" << fbe_eobi::input_source::to_string(msg.fields.input_source.get().value()) << '"'
       << ",transact_time=" << (msg.fields.transact_time.get().has_value() ? std::to_string(msg.fields.transact_time.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const execution_summary& msg) {
    os << "security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",request_time=" << (msg.fields.request_time.get().has_value() ? std::to_string(msg.fields.request_time.get().value()) : std::string_view("null"))
       << ",exec_id=" << (msg.fields.exec_id.get().has_value() ? std::to_string(msg.fields.exec_id.get().value()) : std::string_view("null"))
       << ",last_qty=" << (msg.fields.last_qty.get().has_value() ? std::to_string(msg.fields.last_qty.get().value()) : std::string_view("null"))
       << ",aggressor_side=\"" << fbe_eobi::aggressor_side::to_string(msg.fields.aggressor_side.get().value()) << '"'
       << ",trade_condition=\"" << fbe_eobi::trade_condition::to_string(msg.fields.trade_condition.get().value()) << '"'
       << ",trading_hhi_indicator=" << (msg.fields.trading_hhi_indicator.get().has_value() ? std::to_string(msg.fields.trading_hhi_indicator.get().value()) : std::string_view("null"))
       << ",last_px=" << (msg.fields.last_px.get().has_value() ? std::to_string(msg.fields.last_px.get().value()) : std::string_view("null"))
       << ",remaining_order_details_comp.trd_reg_ts_prev_time_priority=" << (msg.fields.remaining_order_details_comp.trd_reg_ts_prev_time_priority.get().has_value() ? std::to_string(msg.fields.remaining_order_details_comp.trd_reg_ts_prev_time_priority.get().value()) : std::string_view("null"))
       << ",remaining_order_details_comp.display_qty=" << (msg.fields.remaining_order_details_comp.display_qty.get().has_value() ? std::to_string(msg.fields.remaining_order_details_comp.display_qty.get().value()) : std::string_view("null"))
       << ",remaining_order_details_comp.price=" << (msg.fields.remaining_order_details_comp.price.get().has_value() ? std::to_string(msg.fields.remaining_order_details_comp.price.get().value()) : std::string_view("null"))
       << ",resting_hidden_qty=" << (msg.fields.resting_hidden_qty.get().has_value() ? std::to_string(msg.fields.resting_hidden_qty.get().value()) : std::string_view("null"))
       << ",resting_cxl_qty=" << (msg.fields.resting_cxl_qty.get().has_value() ? std::to_string(msg.fields.resting_cxl_qty.get().value()) : std::string_view("null"))
       << ",aggressor_time=" << (msg.fields.aggressor_time.get().has_value() ? std::to_string(msg.fields.aggressor_time.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const full_order_execution& msg) {
    os << "side=\"" << fbe_eobi::side::to_string(msg.fields.side.get().value()) << '"'
       << ",ord_type=\"" << fbe_eobi::ord_type::to_string(msg.fields.ord_type.get().value()) << '"'
       << ",algorithmic_trade_indicator=\"" << fbe_eobi::algorithmic_trade_indicator::to_string(msg.fields.algorithmic_trade_indicator.get().value()) << '"'
       << ",hhi_indicator=\"" << fbe_eobi::hhi_indicator::to_string(msg.fields.hhi_indicator.get().value()) << '"'
       << ",trd_match_id=" << (msg.fields.trd_match_id.get().has_value() ? std::to_string(msg.fields.trd_match_id.get().value()) : std::string_view("null"))
       << ",price=" << (msg.fields.price.get().has_value() ? std::to_string(msg.fields.price.get().value()) : std::string_view("null"))
       << ",trd_reg_ts_time_priority=" << (msg.fields.trd_reg_ts_time_priority.get().has_value() ? std::to_string(msg.fields.trd_reg_ts_time_priority.get().value()) : std::string_view("null"))
       << ",security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
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
       << ",market_condition=\"" << fbe_eobi::market_condition::to_string(msg.fields.market_condition.get().value()) << '"'
       << ",fast_market_indicator=\"" << fbe_eobi::fast_market_indicator::to_string(msg.fields.fast_market_indicator.get().value()) << '"'
       << ",security_trading_event=\"" << fbe_eobi::security_trading_event::to_string(msg.fields.security_trading_event.get().value()) << '"'
       << ",sold_out_indicator=\"" << fbe_eobi::sold_out_indicator::to_string(msg.fields.sold_out_indicator.get().value()) << '"'
       << ",high_px=" << (msg.fields.high_px.get().has_value() ? std::to_string(msg.fields.high_px.get().value()) : std::string_view("null"))
       << ",low_px=" << (msg.fields.low_px.get().has_value() ? std::to_string(msg.fields.low_px.get().value()) : std::string_view("null"))
       << ",transact_time=" << (msg.fields.transact_time.get().has_value() ? std::to_string(msg.fields.transact_time.get().value()) : std::string_view("null"))
       << ",tes_security_status=\"" << fbe_eobi::tes_security_status::to_string(msg.fields.tes_security_status.get().value()) << '"'
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
       << ",market_condition=\"" << fbe_eobi::market_condition::to_string(msg.fields.market_condition.get().value()) << '"'
       << ",fast_market_indicator=\"" << fbe_eobi::fast_market_indicator::to_string(msg.fields.fast_market_indicator.get().value()) << '"'
       << ",security_trading_event=\"" << fbe_eobi::security_trading_event::to_string(msg.fields.security_trading_event.get().value()) << '"'
       << ",sold_out_indicator=\"" << fbe_eobi::sold_out_indicator::to_string(msg.fields.sold_out_indicator.get().value()) << '"'
       << ",high_px=" << (msg.fields.high_px.get().has_value() ? std::to_string(msg.fields.high_px.get().value()) : std::string_view("null"))
       << ",low_px=" << (msg.fields.low_px.get().has_value() ? std::to_string(msg.fields.low_px.get().value()) : std::string_view("null"))
       << ",product_complex=\"" << fbe_eobi::product_complex::to_string(msg.fields.product_complex.get().value()) << '"'
       << ",no_md_entries=" << (msg.fields.no_md_entries.get().has_value() ? std::to_string(msg.fields.no_md_entries.get().value()) : std::string_view("null"))
       << ",tes_security_status=\"" << fbe_eobi::tes_security_status::to_string(msg.fields.tes_security_status.get().value()) << '"'
       << ",md_instrument_entry_grp_comp.md_entry_px=" << (msg.fields.md_instrument_entry_grp_comp.md_entry_px.get().has_value() ? std::to_string(msg.fields.md_instrument_entry_grp_comp.md_entry_px.get().value()) : std::string_view("null"))
       << ",md_instrument_entry_grp_comp.md_entry_size=" << (msg.fields.md_instrument_entry_grp_comp.md_entry_size.get().has_value() ? std::to_string(msg.fields.md_instrument_entry_grp_comp.md_entry_size.get().value()) : std::string_view("null"))
       << ",md_instrument_entry_grp_comp.md_origin_type=\"" << fbe_eobi::md_origin_type::to_string(msg.fields.md_instrument_entry_grp_comp.md_origin_type.get().value()) << '"'
       << ",md_instrument_entry_grp_comp.md_entry_type=\"" << fbe_eobi::md_entry_type::to_string(msg.fields.md_instrument_entry_grp_comp.md_entry_type.get().value()) << '"'
       << ",md_instrument_entry_grp_comp.trade_condition=\"" << fbe_eobi::trade_condition::to_string(msg.fields.md_instrument_entry_grp_comp.trade_condition.get().value()) << '"'
       << ",md_instrument_entry_grp_comp.trd_type=\"" << fbe_eobi::trd_type::to_string(msg.fields.md_instrument_entry_grp_comp.trd_type.get().value()) << '"'
       << ",md_instrument_entry_grp_comp.multi_leg_reporting_type=\"" << fbe_eobi::multi_leg_reporting_type::to_string(msg.fields.md_instrument_entry_grp_comp.multi_leg_reporting_type.get().value()) << '"'
       << ",md_instrument_entry_grp_comp.multi_leg_price_model=\"" << fbe_eobi::multi_leg_price_model::to_string(msg.fields.md_instrument_entry_grp_comp.multi_leg_price_model.get().value()) << '"'
       << ",md_instrument_entry_grp_comp.non_disclosed_trade_volume=" << (msg.fields.md_instrument_entry_grp_comp.non_disclosed_trade_volume.get().has_value() ? std::to_string(msg.fields.md_instrument_entry_grp_comp.non_disclosed_trade_volume.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const mass_instrument_state_change& msg) {
    os << "instrument_scope_product_complex=\"" << fbe_eobi::instrument_scope_product_complex::to_string(msg.fields.instrument_scope_product_complex.get().value()) << '"'
       << ",security_mass_status=\"" << fbe_eobi::security_mass_status::to_string(msg.fields.security_mass_status.get().value()) << '"'
       << ",security_mass_trading_status=\"" << fbe_eobi::security_mass_trading_status::to_string(msg.fields.security_mass_trading_status.get().value()) << '"'
       << ",mass_market_condition=\"" << fbe_eobi::mass_market_condition::to_string(msg.fields.mass_market_condition.get().value()) << '"'
       << ",fast_market_indicator=\"" << fbe_eobi::fast_market_indicator::to_string(msg.fields.fast_market_indicator.get().value()) << '"'
       << ",security_mass_trading_event=\"" << fbe_eobi::security_mass_trading_event::to_string(msg.fields.security_mass_trading_event.get().value()) << '"'
       << ",mass_sold_out_indicator=\"" << fbe_eobi::mass_sold_out_indicator::to_string(msg.fields.mass_sold_out_indicator.get().value()) << '"'
       << ",tes_security_mass_status=\"" << fbe_eobi::tes_security_mass_status::to_string(msg.fields.tes_security_mass_status.get().value()) << '"'
       << ",transact_time=" << (msg.fields.transact_time.get().has_value() ? std::to_string(msg.fields.transact_time.get().value()) : std::string_view("null"))
       << ",last_fragment=\"" << fbe_eobi::last_fragment::to_string(msg.fields.last_fragment.get().value()) << '"'
       << ",no_related_sym=" << (msg.fields.no_related_sym.get().has_value() ? std::to_string(msg.fields.no_related_sym.get().value()) : std::string_view("null"))
       << ",sec_mass_stat_grp_comp.security_id=" << (msg.fields.sec_mass_stat_grp_comp.security_id.get().has_value() ? std::to_string(msg.fields.sec_mass_stat_grp_comp.security_id.get().value()) : std::string_view("null"))
       << ",sec_mass_stat_grp_comp.high_px=" << (msg.fields.sec_mass_stat_grp_comp.high_px.get().has_value() ? std::to_string(msg.fields.sec_mass_stat_grp_comp.high_px.get().value()) : std::string_view("null"))
       << ",sec_mass_stat_grp_comp.low_px=" << (msg.fields.sec_mass_stat_grp_comp.low_px.get().has_value() ? std::to_string(msg.fields.sec_mass_stat_grp_comp.low_px.get().value()) : std::string_view("null"))
       << ",sec_mass_stat_grp_comp.security_status=\"" << fbe_eobi::security_status::to_string(msg.fields.sec_mass_stat_grp_comp.security_status.get().value()) << '"'
       << ",sec_mass_stat_grp_comp.security_trading_status=\"" << fbe_eobi::security_trading_status::to_string(msg.fields.sec_mass_stat_grp_comp.security_trading_status.get().value()) << '"'
       << ",sec_mass_stat_grp_comp.market_condition=\"" << fbe_eobi::market_condition::to_string(msg.fields.sec_mass_stat_grp_comp.market_condition.get().value()) << '"'
       << ",sec_mass_stat_grp_comp.security_trading_event=\"" << fbe_eobi::security_trading_event::to_string(msg.fields.sec_mass_stat_grp_comp.security_trading_event.get().value()) << '"'
       << ",sec_mass_stat_grp_comp.sold_out_indicator=\"" << fbe_eobi::sold_out_indicator::to_string(msg.fields.sec_mass_stat_grp_comp.sold_out_indicator.get().value()) << '"'
       << ",sec_mass_stat_grp_comp.tes_security_status=\"" << fbe_eobi::tes_security_status::to_string(msg.fields.sec_mass_stat_grp_comp.tes_security_status.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_add& msg) {
    os << "request_time=" << (msg.fields.request_time.get().has_value() ? std::to_string(msg.fields.request_time.get().value()) : std::string_view("null"))
       << ",security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",order_details_comp.trd_reg_ts_time_priority=" << (msg.fields.order_details_comp.trd_reg_ts_time_priority.get().has_value() ? std::to_string(msg.fields.order_details_comp.trd_reg_ts_time_priority.get().value()) : std::string_view("null"))
       << ",order_details_comp.display_qty=" << (msg.fields.order_details_comp.display_qty.get().has_value() ? std::to_string(msg.fields.order_details_comp.display_qty.get().value()) : std::string_view("null"))
       << ",order_details_comp.side=\"" << fbe_eobi::side::to_string(msg.fields.order_details_comp.side.get().value()) << '"'
       << ",order_details_comp.ord_type=\"" << fbe_eobi::ord_type::to_string(msg.fields.order_details_comp.ord_type.get().value()) << '"'
       << ",order_details_comp.hhi_indicator=\"" << fbe_eobi::hhi_indicator::to_string(msg.fields.order_details_comp.hhi_indicator.get().value()) << '"'
       << ",order_details_comp.price=" << (msg.fields.order_details_comp.price.get().has_value() ? std::to_string(msg.fields.order_details_comp.price.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_delete& msg) {
    os << "request_time=" << (msg.fields.request_time.get().has_value() ? std::to_string(msg.fields.request_time.get().value()) : std::string_view("null"))
       << ",transact_time=" << (msg.fields.transact_time.get().has_value() ? std::to_string(msg.fields.transact_time.get().value()) : std::string_view("null"))
       << ",security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",order_details_comp.trd_reg_ts_time_priority=" << (msg.fields.order_details_comp.trd_reg_ts_time_priority.get().has_value() ? std::to_string(msg.fields.order_details_comp.trd_reg_ts_time_priority.get().value()) : std::string_view("null"))
       << ",order_details_comp.display_qty=" << (msg.fields.order_details_comp.display_qty.get().has_value() ? std::to_string(msg.fields.order_details_comp.display_qty.get().value()) : std::string_view("null"))
       << ",order_details_comp.side=\"" << fbe_eobi::side::to_string(msg.fields.order_details_comp.side.get().value()) << '"'
       << ",order_details_comp.ord_type=\"" << fbe_eobi::ord_type::to_string(msg.fields.order_details_comp.ord_type.get().value()) << '"'
       << ",order_details_comp.hhi_indicator=\"" << fbe_eobi::hhi_indicator::to_string(msg.fields.order_details_comp.hhi_indicator.get().value()) << '"'
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
    os << "request_time=" << (msg.fields.request_time.get().has_value() ? std::to_string(msg.fields.request_time.get().value()) : std::string_view("null"))
       << ",trd_reg_ts_prev_time_priority=" << (msg.fields.trd_reg_ts_prev_time_priority.get().has_value() ? std::to_string(msg.fields.trd_reg_ts_prev_time_priority.get().value()) : std::string_view("null"))
       << ",prev_price=" << (msg.fields.prev_price.get().has_value() ? std::to_string(msg.fields.prev_price.get().value()) : std::string_view("null"))
       << ",prev_display_qty=" << (msg.fields.prev_display_qty.get().has_value() ? std::to_string(msg.fields.prev_display_qty.get().value()) : std::string_view("null"))
       << ",security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",order_details_comp.trd_reg_ts_time_priority=" << (msg.fields.order_details_comp.trd_reg_ts_time_priority.get().has_value() ? std::to_string(msg.fields.order_details_comp.trd_reg_ts_time_priority.get().value()) : std::string_view("null"))
       << ",order_details_comp.display_qty=" << (msg.fields.order_details_comp.display_qty.get().has_value() ? std::to_string(msg.fields.order_details_comp.display_qty.get().value()) : std::string_view("null"))
       << ",order_details_comp.side=\"" << fbe_eobi::side::to_string(msg.fields.order_details_comp.side.get().value()) << '"'
       << ",order_details_comp.ord_type=\"" << fbe_eobi::ord_type::to_string(msg.fields.order_details_comp.ord_type.get().value()) << '"'
       << ",order_details_comp.hhi_indicator=\"" << fbe_eobi::hhi_indicator::to_string(msg.fields.order_details_comp.hhi_indicator.get().value()) << '"'
       << ",order_details_comp.price=" << (msg.fields.order_details_comp.price.get().has_value() ? std::to_string(msg.fields.order_details_comp.price.get().value()) : std::string_view("null"))
       << ",prev_price_hhi_indicator=\"" << fbe_eobi::prev_price_hhi_indicator::to_string(msg.fields.prev_price_hhi_indicator.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_modify_same_prio& msg) {
    os << "request_time=" << (msg.fields.request_time.get().has_value() ? std::to_string(msg.fields.request_time.get().value()) : std::string_view("null"))
       << ",transact_time=" << (msg.fields.transact_time.get().has_value() ? std::to_string(msg.fields.transact_time.get().value()) : std::string_view("null"))
       << ",prev_display_qty=" << (msg.fields.prev_display_qty.get().has_value() ? std::to_string(msg.fields.prev_display_qty.get().value()) : std::string_view("null"))
       << ",security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",order_details_comp.trd_reg_ts_time_priority=" << (msg.fields.order_details_comp.trd_reg_ts_time_priority.get().has_value() ? std::to_string(msg.fields.order_details_comp.trd_reg_ts_time_priority.get().value()) : std::string_view("null"))
       << ",order_details_comp.display_qty=" << (msg.fields.order_details_comp.display_qty.get().has_value() ? std::to_string(msg.fields.order_details_comp.display_qty.get().value()) : std::string_view("null"))
       << ",order_details_comp.side=\"" << fbe_eobi::side::to_string(msg.fields.order_details_comp.side.get().value()) << '"'
       << ",order_details_comp.ord_type=\"" << fbe_eobi::ord_type::to_string(msg.fields.order_details_comp.ord_type.get().value()) << '"'
       << ",order_details_comp.hhi_indicator=\"" << fbe_eobi::hhi_indicator::to_string(msg.fields.order_details_comp.hhi_indicator.get().value()) << '"'
       << ",order_details_comp.price=" << (msg.fields.order_details_comp.price.get().has_value() ? std::to_string(msg.fields.order_details_comp.price.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const partial_order_execution& msg) {
    os << "side=\"" << fbe_eobi::side::to_string(msg.fields.side.get().value()) << '"'
       << ",ord_type=\"" << fbe_eobi::ord_type::to_string(msg.fields.ord_type.get().value()) << '"'
       << ",algorithmic_trade_indicator=\"" << fbe_eobi::algorithmic_trade_indicator::to_string(msg.fields.algorithmic_trade_indicator.get().value()) << '"'
       << ",hhi_indicator=\"" << fbe_eobi::hhi_indicator::to_string(msg.fields.hhi_indicator.get().value()) << '"'
       << ",trd_match_id=" << (msg.fields.trd_match_id.get().has_value() ? std::to_string(msg.fields.trd_match_id.get().value()) : std::string_view("null"))
       << ",price=" << (msg.fields.price.get().has_value() ? std::to_string(msg.fields.price.get().value()) : std::string_view("null"))
       << ",trd_reg_ts_time_priority=" << (msg.fields.trd_reg_ts_time_priority.get().has_value() ? std::to_string(msg.fields.trd_reg_ts_time_priority.get().value()) : std::string_view("null"))
       << ",security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",last_qty=" << (msg.fields.last_qty.get().has_value() ? std::to_string(msg.fields.last_qty.get().value()) : std::string_view("null"))
       << ",last_px=" << (msg.fields.last_px.get().has_value() ? std::to_string(msg.fields.last_px.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const product_state_change& msg) {
    os << "trading_session_id=\"" << fbe_eobi::trading_session_id::to_string(msg.fields.trading_session_id.get().value()) << '"'
       << ",trading_session_sub_id=\"" << fbe_eobi::trading_session_sub_id::to_string(msg.fields.trading_session_sub_id.get().value()) << '"'
       << ",trad_ses_status=\"" << fbe_eobi::trad_ses_status::to_string(msg.fields.trad_ses_status.get().value()) << '"'
       << ",market_condition=\"" << fbe_eobi::market_condition::to_string(msg.fields.market_condition.get().value()) << '"'
       << ",fast_market_indicator=\"" << fbe_eobi::fast_market_indicator::to_string(msg.fields.fast_market_indicator.get().value()) << '"'
       << ",tes_trad_ses_status=\"" << fbe_eobi::tes_trad_ses_status::to_string(msg.fields.tes_trad_ses_status.get().value()) << '"'
       << ",transact_time=" << (msg.fields.transact_time.get().has_value() ? std::to_string(msg.fields.transact_time.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const product_summary& msg) {
    os << "last_msg_seq_num_processed=" << (msg.fields.last_msg_seq_num_processed.get().has_value() ? std::to_string(msg.fields.last_msg_seq_num_processed.get().value()) : std::string_view("null"))
       << ",trading_session_id=\"" << fbe_eobi::trading_session_id::to_string(msg.fields.trading_session_id.get().value()) << '"'
       << ",trading_session_sub_id=\"" << fbe_eobi::trading_session_sub_id::to_string(msg.fields.trading_session_sub_id.get().value()) << '"'
       << ",trad_ses_status=\"" << fbe_eobi::trad_ses_status::to_string(msg.fields.trad_ses_status.get().value()) << '"'
       << ",market_condition=\"" << fbe_eobi::market_condition::to_string(msg.fields.market_condition.get().value()) << '"'
       << ",fast_market_indicator=\"" << fbe_eobi::fast_market_indicator::to_string(msg.fields.fast_market_indicator.get().value()) << '"'
       << ",tes_trad_ses_status=\"" << fbe_eobi::tes_trad_ses_status::to_string(msg.fields.tes_trad_ses_status.get().value()) << '"'
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
       << ",order_details_comp.ord_type=\"" << fbe_eobi::ord_type::to_string(msg.fields.order_details_comp.ord_type.get().value()) << '"'
       << ",order_details_comp.hhi_indicator=\"" << fbe_eobi::hhi_indicator::to_string(msg.fields.order_details_comp.hhi_indicator.get().value()) << '"'
       << ",order_details_comp.price=" << (msg.fields.order_details_comp.price.get().has_value() ? std::to_string(msg.fields.order_details_comp.price.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const tes_trade_report& msg) {
    os << "security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",transact_time=" << (msg.fields.transact_time.get().has_value() ? std::to_string(msg.fields.transact_time.get().value()) : std::string_view("null"))
       << ",last_qty=" << (msg.fields.last_qty.get().has_value() ? std::to_string(msg.fields.last_qty.get().value()) : std::string_view("null"))
       << ",last_px=" << (msg.fields.last_px.get().has_value() ? std::to_string(msg.fields.last_px.get().value()) : std::string_view("null"))
       << ",trd_match_id=" << (msg.fields.trd_match_id.get().has_value() ? std::to_string(msg.fields.trd_match_id.get().value()) : std::string_view("null"))
       << ",trd_type=\"" << fbe_eobi::trd_type::to_string(msg.fields.trd_type.get().value()) << '"'
       << ",trade_condition=\"" << fbe_eobi::trade_condition::to_string(msg.fields.trade_condition.get().value()) << '"'
       << ",multi_leg_reporting_type=\"" << fbe_eobi::multi_leg_reporting_type::to_string(msg.fields.multi_leg_reporting_type.get().value()) << '"'
       << ",multi_leg_price_model=\"" << fbe_eobi::multi_leg_price_model::to_string(msg.fields.multi_leg_price_model.get().value()) << '"'
       << ",non_disclosed_trade_volume=" << (msg.fields.non_disclosed_trade_volume.get().has_value() ? std::to_string(msg.fields.non_disclosed_trade_volume.get().value()) : std::string_view("null"))
       << ",trans_bkd_time=" << (msg.fields.trans_bkd_time.get().has_value() ? std::to_string(msg.fields.trans_bkd_time.get().value()) : std::string_view("null"))
       << ",number_of_buy_sides=" << (msg.fields.number_of_buy_sides.get().has_value() ? std::to_string(msg.fields.number_of_buy_sides.get().value()) : std::string_view("null"))
       << ",number_of_sell_sides=" << (msg.fields.number_of_sell_sides.get().has_value() ? std::to_string(msg.fields.number_of_sell_sides.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const top_of_book& msg) {
    os << "transact_time=" << (msg.fields.transact_time.get().has_value() ? std::to_string(msg.fields.transact_time.get().value()) : std::string_view("null"))
       << ",security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",bid_px=" << (msg.fields.bid_px.get().has_value() ? std::to_string(msg.fields.bid_px.get().value()) : std::string_view("null"))
       << ",offer_px=" << (msg.fields.offer_px.get().has_value() ? std::to_string(msg.fields.offer_px.get().value()) : std::string_view("null"))
       << ",bid_size=" << (msg.fields.bid_size.get().has_value() ? std::to_string(msg.fields.bid_size.get().value()) : std::string_view("null"))
       << ",offer_size=" << (msg.fields.offer_size.get().has_value() ? std::to_string(msg.fields.offer_size.get().value()) : std::string_view("null"))
       << ",number_of_buy_orders=" << (msg.fields.number_of_buy_orders.get().has_value() ? std::to_string(msg.fields.number_of_buy_orders.get().value()) : std::string_view("null"))
       << ",number_of_sell_orders=" << (msg.fields.number_of_sell_orders.get().has_value() ? std::to_string(msg.fields.number_of_sell_orders.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_report& msg) {
    os << "security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",transact_time=" << (msg.fields.transact_time.get().has_value() ? std::to_string(msg.fields.transact_time.get().value()) : std::string_view("null"))
       << ",last_qty=" << (msg.fields.last_qty.get().has_value() ? std::to_string(msg.fields.last_qty.get().value()) : std::string_view("null"))
       << ",last_px=" << (msg.fields.last_px.get().has_value() ? std::to_string(msg.fields.last_px.get().value()) : std::string_view("null"))
       << ",trd_match_id=" << (msg.fields.trd_match_id.get().has_value() ? std::to_string(msg.fields.trd_match_id.get().value()) : std::string_view("null"))
       << ",match_type=\"" << fbe_eobi::match_type::to_string(msg.fields.match_type.get().value()) << '"'
       << ",match_sub_type=\"" << fbe_eobi::match_sub_type::to_string(msg.fields.match_sub_type.get().value()) << '"'
       << ",algorithmic_trade_indicator=\"" << fbe_eobi::algorithmic_trade_indicator::to_string(msg.fields.algorithmic_trade_indicator.get().value()) << '"'
       << ",trade_condition=\"" << fbe_eobi::trade_condition::to_string(msg.fields.trade_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_reversal& msg) {
    os << "security_id=" << (msg.fields.security_id.get().has_value() ? std::to_string(msg.fields.security_id.get().value()) : std::string_view("null"))
       << ",transact_time=" << (msg.fields.transact_time.get().has_value() ? std::to_string(msg.fields.transact_time.get().value()) : std::string_view("null"))
       << ",last_qty=" << (msg.fields.last_qty.get().has_value() ? std::to_string(msg.fields.last_qty.get().value()) : std::string_view("null"))
       << ",last_px=" << (msg.fields.last_px.get().has_value() ? std::to_string(msg.fields.last_px.get().value()) : std::string_view("null"))
       << ",trd_reg_ts_execution_time=" << (msg.fields.trd_reg_ts_execution_time.get().has_value() ? std::to_string(msg.fields.trd_reg_ts_execution_time.get().value()) : std::string_view("null"))
       << ",trd_match_id=" << (msg.fields.trd_match_id.get().has_value() ? std::to_string(msg.fields.trd_match_id.get().value()) : std::string_view("null"))
       << ",trade_condition=\"" << fbe_eobi::trade_condition::to_string(msg.fields.trade_condition.get().value()) << '"'
       << ",md_origin_type=\"" << fbe_eobi::md_origin_type::to_string(msg.fields.md_origin_type.get().value()) << '"'
       << ",no_md_entries=" << (msg.fields.no_md_entries.get().has_value() ? std::to_string(msg.fields.no_md_entries.get().value()) : std::string_view("null"))
       << ",md_trade_entry_grp_comp.md_entry_px=" << (msg.fields.md_trade_entry_grp_comp.md_entry_px.get().has_value() ? std::to_string(msg.fields.md_trade_entry_grp_comp.md_entry_px.get().value()) : std::string_view("null"))
       << ",md_trade_entry_grp_comp.md_entry_size=" << (msg.fields.md_trade_entry_grp_comp.md_entry_size.get().has_value() ? std::to_string(msg.fields.md_trade_entry_grp_comp.md_entry_size.get().value()) : std::string_view("null"))
       << ",md_trade_entry_grp_comp.md_entry_type=\"" << fbe_eobi::md_entry_type::to_string(msg.fields.md_trade_entry_grp_comp.md_entry_type.get().value()) << '"'
       ;
    return os;
}

}
