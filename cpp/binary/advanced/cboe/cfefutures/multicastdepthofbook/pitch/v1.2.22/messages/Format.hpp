#pragma once

#include <ostream>
#include <string_view>

#include "TimeReferenceMessage.hpp"
#include "TimeMessage.hpp"
#include "UnitClearMessage.hpp"
#include "FuturesInstrumentDefinitionMessage.hpp"
#include "FuturesVarianceSymbolMappingMessage.hpp"
#include "PriceLimitsMessage.hpp"
#include "AddOrderLongMessage.hpp"
#include "AddOrderShortMessage.hpp"
#include "OrderExecutedMessage.hpp"
#include "ReduceSizeLongMessage.hpp"
#include "ReduceSizeShortMessage.hpp"
#include "ModifyOrderLongMessage.hpp"
#include "ModifyOrderShortMessage.hpp"
#include "DeleteOrderMessage.hpp"
#include "TradeLongMessage.hpp"
#include "TradeShortMessage.hpp"
#include "TransactionBeginMessage.hpp"
#include "TransactionEndMessage.hpp"
#include "TradeBreakMessage.hpp"
#include "SettlementMessage.hpp"
#include "OpenInterestMessage.hpp"
#include "EndOfDaySummaryMessage.hpp"
#include "TradingStatusMessage.hpp"
#include "EndOfSessionMessage.hpp"
#include "../json/messages/futures_instrument_definition_message_json.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

namespace pitch_multicastdepthofbook = ::cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22;

inline std::ostream& operator<<(std::ostream& os, const packet_header& value) {
    os << "length=" << value.length.get().value()
       << ",message_count=" << static_cast<unsigned>(value.message_count.get().value())
       << ",unit=" << static_cast<unsigned>(value.unit.get().value())
       << ",sequence=" << value.sequence.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "message_length=" << static_cast<unsigned>(value.message_length.get().value())
       << ",message_type=\"" << pitch_multicastdepthofbook::message_type::to_string(value.message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const time_reference_message& msg) {
    os << "midnight_reference=" << msg.fields.midnight_reference.get().value()
       << ",time_reference=" << msg.fields.time_reference.get().value()
       << ",time_offset=" << msg.fields.time_offset.get().value()
       << ",trade_date=" << msg.fields.trade_date.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const time_message& msg) {
    os << "time_reference=" << msg.fields.time_reference.get().value()
       << ",epoch_time=" << msg.fields.epoch_time.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const unit_clear_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const futures_instrument_definition_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",unit_timestamp=" << msg.fields.unit_timestamp.get().value()
       << ",report_symbol=\"" << msg.fields.report_symbol.get_trimmed().value() << '"'
       << ",futures_flags=" << static_cast<unsigned>(msg.fields.futures_flags.get().value())
       << ",expiration_date=" << msg.fields.expiration_date.get().value()
       << ",contract_size=" << msg.fields.contract_size.get().value()
       << ",listing_state=\"" << pitch_multicastdepthofbook::listing_state::to_string(msg.fields.listing_state.get().value()) << '"'
       << ",price_increment=" << msg.fields.price_increment.get().value()
       << ",leg_count=" << static_cast<unsigned>(msg.fields.leg_count.get().value())
       << ",leg_offset=" << static_cast<unsigned>(msg.fields.leg_offset.get().value())
       << ",contract_date=" << msg.fields.contract_date.get().value()
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const futures_variance_symbol_mapping_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",unit_timestamp=" << msg.fields.unit_timestamp.get().value()
       << ",feed_symbol=\"" << msg.fields.feed_symbol.get_trimmed().value() << '"'
       << ",futures_symbol=\"" << msg.fields.futures_symbol.get_trimmed().value() << '"'
       << ",accrued_day_variance=" << msg.fields.accrued_day_variance.get().value()
       << ",num_final_returns=" << msg.fields.num_final_returns.get().value()
       << ",num_elapsed_returns=" << msg.fields.num_elapsed_returns.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const price_limits_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",upper_price_limit=" << msg.fields.upper_price_limit.get().value()
       << ",lower_price_limit=" << msg.fields.lower_price_limit.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_order_long_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",side_indicator=\"" << pitch_multicastdepthofbook::side_indicator::to_string(msg.fields.side_indicator.get().value()) << '"'
       << ",quantity_long=" << msg.fields.quantity_long.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",price_long=" << msg.fields.price_long.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_order_short_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",side_indicator=\"" << pitch_multicastdepthofbook::side_indicator::to_string(msg.fields.side_indicator.get().value()) << '"'
       << ",quantity_short=" << msg.fields.quantity_short.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",price_short=" << msg.fields.price_short.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_executed_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",executed_quantity=" << msg.fields.executed_quantity.get().value()
       << ",execution_id=" << msg.fields.execution_id.get().value()
       << ",trade_condition=\"" << pitch_multicastdepthofbook::trade_condition::to_string(msg.fields.trade_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const reduce_size_long_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",canceled_quantity_long=" << msg.fields.canceled_quantity_long.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const reduce_size_short_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",canceled_quantity_short=" << msg.fields.canceled_quantity_short.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const modify_order_long_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",quantity_long=" << msg.fields.quantity_long.get().value()
       << ",price_long=" << msg.fields.price_long.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const modify_order_short_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",quantity_short=" << msg.fields.quantity_short.get().value()
       << ",price_short=" << msg.fields.price_short.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const delete_order_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_long_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",side_indicator=\"" << pitch_multicastdepthofbook::side_indicator::to_string(msg.fields.side_indicator.get().value()) << '"'
       << ",quantity_long=" << msg.fields.quantity_long.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",price_long=" << msg.fields.price_long.get().value()
       << ",execution_id=" << msg.fields.execution_id.get().value()
       << ",trade_condition=\"" << pitch_multicastdepthofbook::trade_condition::to_string(msg.fields.trade_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_short_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",side_indicator=\"" << pitch_multicastdepthofbook::side_indicator::to_string(msg.fields.side_indicator.get().value()) << '"'
       << ",quantity_short=" << msg.fields.quantity_short.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",price_short=" << msg.fields.price_short.get().value()
       << ",execution_id=" << msg.fields.execution_id.get().value()
       << ",trade_condition=\"" << pitch_multicastdepthofbook::trade_condition::to_string(msg.fields.trade_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const transaction_begin_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const transaction_end_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_break_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",execution_id=" << msg.fields.execution_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const settlement_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",settlement_price=" << msg.fields.settlement_price.get().value()
       << ",issue=\"" << pitch_multicastdepthofbook::issue::to_string(msg.fields.issue.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const open_interest_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",open_interest=" << msg.fields.open_interest.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const end_of_day_summary_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",open_interest=" << msg.fields.open_interest.get().value()
       << ",high_price=" << msg.fields.high_price.get().value()
       << ",low_price=" << msg.fields.low_price.get().value()
       << ",open_price=" << msg.fields.open_price.get().value()
       << ",close_price=" << msg.fields.close_price.get().value()
       << ",total_volume=" << msg.fields.total_volume.get().value()
       << ",block_volume=" << msg.fields.block_volume.get().value()
       << ",ecrp_volume=" << msg.fields.ecrp_volume.get().value()
       << ",summary_flags=" << static_cast<unsigned>(msg.fields.summary_flags.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trading_status_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",trading_status=\"" << pitch_multicastdepthofbook::trading_status::to_string(msg.fields.trading_status.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const end_of_session_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       ;
    return os;
}

}
