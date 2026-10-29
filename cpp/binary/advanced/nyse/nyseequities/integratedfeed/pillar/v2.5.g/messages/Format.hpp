#pragma once

#include <ostream>
#include <string_view>

#include "SequenceNumberResetMessage.hpp"
#include "SourceTimeReferenceMessage.hpp"
#include "SymbolIndexMappingMessage.hpp"
#include "SymbolClearMessage.hpp"
#include "SecurityStatusMessage.hpp"
#include "AddOrderMessage.hpp"
#include "ModifyOrderMessage.hpp"
#include "DeleteOrderMessage.hpp"
#include "OrderExecutionMessage.hpp"
#include "ReplaceOrderMessage.hpp"
#include "ImbalanceMessage.hpp"
#include "AddOrderRefreshMessage.hpp"
#include "NonDisplayedTradeMessage.hpp"
#include "CrossTradeMessage.hpp"
#include "TradeCancelMessage.hpp"
#include "CrossCorrectionMessage.hpp"
#include "RetailPriceImprovementMessage.hpp"

namespace nyse::nyseequities::integratedfeed::pillar::v2_5_g {

namespace pillar_integratedfeed = ::nyse::nyseequities::integratedfeed::pillar::v2_5_g;

inline std::ostream& operator<<(std::ostream& os, const packet_header& value) {
    os << "pkt_size=" << value.pkt_size.get().value()
       << ",delivery_flag=\"" << pillar_integratedfeed::delivery_flag::to_string(value.delivery_flag.get().value()) << '"'
       << ",number_msgs=" << static_cast<unsigned>(value.number_msgs.get().value())
       << ",seq_num=" << value.seq_num.get().value()
       << ",send_time.seconds=" << value.send_time.seconds.get().value()
       << ",send_time.nanoseconds=" << value.send_time.nanoseconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "message_size=" << value.message_size.get().value()
       << ",message_type=\"" << pillar_integratedfeed::message_type::to_string(value.message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const send_time& value) {
    os << "seconds=" << value.seconds.get().value()
       << ",nanoseconds=" << value.nanoseconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const sequence_number_reset_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",product_id=" << static_cast<unsigned>(msg.fields.product_id.get().value())
       << ",channel_id=" << static_cast<unsigned>(msg.fields.channel_id.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const source_time_reference_message& msg) {
    os << "id=" << msg.fields.id.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",source_time=" << msg.fields.source_time.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const symbol_index_mapping_message& msg) {
    os << "symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",market_id=\"" << pillar_integratedfeed::market_id::to_string(msg.fields.market_id.get().value()) << '"'
       << ",system_id=" << static_cast<unsigned>(msg.fields.system_id.get().value())
       << ",exchange_code=\"" << pillar_integratedfeed::exchange_code::to_string(msg.fields.exchange_code.get().value()) << '"'
       << ",price_scale_code=" << static_cast<unsigned>(msg.fields.price_scale_code.get().value())
       << ",security_type=\"" << pillar_integratedfeed::security_type::to_string(msg.fields.security_type.get().value()) << '"'
       << ",lot_size=" << msg.fields.lot_size.get().value()
       << ",prev_close_price=" << msg.fields.prev_close_price.get().value()
       << ",prev_close_volume=" << msg.fields.prev_close_volume.get().value()
       << ",price_resolution=\"" << pillar_integratedfeed::price_resolution::to_string(msg.fields.price_resolution.get().value()) << '"'
       << ",round_lot=\"" << pillar_integratedfeed::round_lot::to_string(msg.fields.round_lot.get().value()) << '"'
       << ",mpv=" << msg.fields.mpv.get().value()
       << ",unit_of_trade=" << msg.fields.unit_of_trade.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const symbol_clear_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",next_source_seq_num=" << msg.fields.next_source_seq_num.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const security_status_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",security_status=\"" << pillar_integratedfeed::security_status::to_string(msg.fields.security_status.get().value()) << '"'
       << ",halt_condition=\"" << pillar_integratedfeed::halt_condition::to_string(msg.fields.halt_condition.get().value()) << '"'
       << ",price_1=" << msg.fields.price_1.get().value()
       << ",price_2=" << msg.fields.price_2.get().value()
       << ",ssr_triggering_exchange_id=\"" << pillar_integratedfeed::ssr_triggering_exchange_id::to_string(msg.fields.ssr_triggering_exchange_id.get().value()) << '"'
       << ",ssr_triggering_volume=" << msg.fields.ssr_triggering_volume.get().value()
       << ",time=" << (msg.fields.time.get().has_value() ? std::to_string(msg.fields.time.get().value()) : std::string_view("null"))
       << ",ssr_state=\"" << pillar_integratedfeed::ssr_state::to_string(msg.fields.ssr_state.get().value()) << '"'
       << ",market_state=\"" << pillar_integratedfeed::market_state::to_string(msg.fields.market_state.get().value()) << '"'
       << ",session_state=\"" << msg.fields.session_state.get().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_order_message& msg) {
    os << "source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",volume=" << msg.fields.volume.get().value()
       << ",side=\"" << pillar_integratedfeed::side::to_string(msg.fields.side.get().value()) << '"'
       << ",firm_id=\"" << msg.fields.firm_id.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const modify_order_message& msg) {
    os << "source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",volume=" << msg.fields.volume.get().value()
       << ",position_change=" << static_cast<unsigned>(msg.fields.position_change.get().value())
       << ",side=\"" << pillar_integratedfeed::side::to_string(msg.fields.side.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const delete_order_message& msg) {
    os << "source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_execution_message& msg) {
    os << "source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",volume=" << msg.fields.volume.get().value()
       << ",printable_flag=\"" << pillar_integratedfeed::printable_flag::to_string(msg.fields.printable_flag.get().value()) << '"'
       << ",trade_cond_1=\"" << pillar_integratedfeed::trade_cond_1::to_string(msg.fields.trade_cond_1.get().value()) << '"'
       << ",trade_cond_2=\"" << pillar_integratedfeed::trade_cond_2::to_string(msg.fields.trade_cond_2.get().value()) << '"'
       << ",trade_cond_3=\"" << pillar_integratedfeed::trade_cond_3::to_string(msg.fields.trade_cond_3.get().value()) << '"'
       << ",trade_cond_4=\"" << pillar_integratedfeed::trade_cond_4::to_string(msg.fields.trade_cond_4.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const replace_order_message& msg) {
    os << "source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",new_order_id=" << msg.fields.new_order_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",volume=" << msg.fields.volume.get().value()
       << ",side=\"" << pillar_integratedfeed::side::to_string(msg.fields.side.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const imbalance_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",reference_price=" << msg.fields.reference_price.get().value()
       << ",paired_qty=" << msg.fields.paired_qty.get().value()
       << ",total_imbalance_qty=" << msg.fields.total_imbalance_qty.get().value()
       << ",market_imbalance_qty=" << msg.fields.market_imbalance_qty.get().value()
       << ",auction_time=" << msg.fields.auction_time.get().value()
       << ",auction_type=\"" << pillar_integratedfeed::auction_type::to_string(msg.fields.auction_type.get().value()) << '"'
       << ",imbalance_side=\"" << pillar_integratedfeed::imbalance_side::to_string(msg.fields.imbalance_side.get().value()) << '"'
       << ",continuous_book_clearing_price=" << msg.fields.continuous_book_clearing_price.get().value()
       << ",auction_interest_clearing_price=" << msg.fields.auction_interest_clearing_price.get().value()
       << ",ssr_filing_price=" << msg.fields.ssr_filing_price.get().value()
       << ",indicative_match_price=" << msg.fields.indicative_match_price.get().value()
       << ",upper_collar=" << msg.fields.upper_collar.get().value()
       << ",lower_collar=" << msg.fields.lower_collar.get().value()
       << ",auction_status=\"" << pillar_integratedfeed::auction_status::to_string(msg.fields.auction_status.get().value()) << '"'
       << ",freeze_status=\"" << pillar_integratedfeed::freeze_status::to_string(msg.fields.freeze_status.get().value()) << '"'
       << ",num_extensions=" << static_cast<unsigned>(msg.fields.num_extensions.get().value())
       << ",unpaired_qty=" << msg.fields.unpaired_qty.get().value()
       << ",unpaired_side=\"" << pillar_integratedfeed::unpaired_side::to_string(msg.fields.unpaired_side.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_order_refresh_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",volume=" << msg.fields.volume.get().value()
       << ",side=\"" << pillar_integratedfeed::side::to_string(msg.fields.side.get().value()) << '"'
       << ",firm_id=\"" << msg.fields.firm_id.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const non_displayed_trade_message& msg) {
    os << "source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",volume=" << msg.fields.volume.get().value()
       << ",printable_flag=\"" << pillar_integratedfeed::printable_flag::to_string(msg.fields.printable_flag.get().value()) << '"'
       << ",trade_cond_1=\"" << pillar_integratedfeed::trade_cond_1::to_string(msg.fields.trade_cond_1.get().value()) << '"'
       << ",trade_cond_2=\"" << pillar_integratedfeed::trade_cond_2::to_string(msg.fields.trade_cond_2.get().value()) << '"'
       << ",trade_cond_3=\"" << pillar_integratedfeed::trade_cond_3::to_string(msg.fields.trade_cond_3.get().value()) << '"'
       << ",trade_cond_4=\"" << pillar_integratedfeed::trade_cond_4::to_string(msg.fields.trade_cond_4.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const cross_trade_message& msg) {
    os << "source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",cross_id=" << msg.fields.cross_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",volume=" << msg.fields.volume.get().value()
       << ",cross_type=\"" << pillar_integratedfeed::cross_type::to_string(msg.fields.cross_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_cancel_message& msg) {
    os << "source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const cross_correction_message& msg) {
    os << "source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",cross_id=" << msg.fields.cross_id.get().value()
       << ",volume=" << msg.fields.volume.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const retail_price_improvement_message& msg) {
    os << "source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",rpi_indicator=\"" << pillar_integratedfeed::rpi_indicator::to_string(msg.fields.rpi_indicator.get().value()) << '"'
       ;
    return os;
}

}
