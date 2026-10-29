#pragma once

#include <ostream>
#include <string_view>

#include "SecurityDefinitionMessage.hpp"
#include "CurrentMarketRefreshMessage.hpp"
#include "MarketDataRefreshMessage.hpp"
#include "CurrentMarketUpdateMessage.hpp"
#include "RecapUpdateMessage.hpp"
#include "TickerMessage.hpp"
#include "ExpectedOpeningPriceAndSizeMessage.hpp"
#include "IndexValueMessage.hpp"
#include "SettlementValueMessage.hpp"
#include "SummaryMessage.hpp"
#include "MarketDataControlMessage.hpp"
#include "HeartbeatMessage.hpp"
#include "../json/messages/security_definition_message_json.hpp"
#include "../json/messages/current_market_refresh_message_json.hpp"
#include "../json/messages/market_data_refresh_message_json.hpp"
#include "../json/messages/current_market_update_message_json.hpp"
#include "../json/messages/recap_update_message_json.hpp"
#include "../json/messages/ticker_message_json.hpp"
#include "../json/messages/index_value_message_json.hpp"
#include "../json/messages/settlement_value_message_json.hpp"
#include "../json/messages/summary_message_json.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;

inline std::ostream& operator<<(std::ostream& os, const packet_header& value) {
    os << "version=" << static_cast<unsigned>(value.version.get().value())
       << ",packet_length=" << value.packet_length.get().value()
       << ",sending_time=" << value.sending_time.get().value()
       << ",message_count=" << static_cast<unsigned>(value.message_count.get().value())
       << ",first_msg_seq_num=" << value.first_msg_seq_num.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "message_length=" << value.message_length.get().value()
       << ",template_id=\"" << csm_marketdatafeed::template_id::to_string(value.template_id.get().value()) << '"'
       << ",message_type=\"" << value.message_type.get().value() << '"'
       << ",msg_seq_num=" << value.msg_seq_num.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const security_definition_message& msg) {
    os << "security_exchange=\"" << csm_marketdatafeed::security_exchange::to_string(msg.fields.security_exchange.get().value()) << '"'
       << ",class_key=" << msg.fields.class_key.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",maturity_date=" << msg.fields.maturity_date.get().value()
       << ",price_type=" << static_cast<unsigned>(msg.fields.price_type.get().value())
       << ",strike_price.strike_price_exponent=" << static_cast<int>(msg.fields.strike_price.strike_price_exponent.get().value())
       << ",strike_price.strike_price_mantissa=" << msg.fields.strike_price.strike_price_mantissa.get().value()
       << ",put_or_call=\"" << csm_marketdatafeed::put_or_call::to_string(msg.fields.put_or_call.get().value()) << '"'
       << ",minimum_strike_price_fraction.minimum_strike_price_fraction_exponent=" << static_cast<int>(msg.fields.minimum_strike_price_fraction.minimum_strike_price_fraction_exponent.get().value())
       << ",minimum_strike_price_fraction.minimum_strike_price_fraction_mantissa=" << msg.fields.minimum_strike_price_fraction.minimum_strike_price_fraction_mantissa.get().value()
       << ",max_strike_price.max_strike_price_exponent=" << static_cast<int>(msg.fields.max_strike_price.max_strike_price_exponent.get().value())
       << ",max_strike_price.max_strike_price_mantissa=" << msg.fields.max_strike_price.max_strike_price_mantissa.get().value()
       << ",premium_break_point.premium_break_point_exponent=" << static_cast<int>(msg.fields.premium_break_point.premium_break_point_exponent.get().value())
       << ",premium_break_point.premium_break_point_mantissa=" << msg.fields.premium_break_point.premium_break_point_mantissa.get().value()
       << ",minimum_above_premium_fraction.minimum_above_premium_fraction_exponent=" << static_cast<int>(msg.fields.minimum_above_premium_fraction.minimum_above_premium_fraction_exponent.get().value())
       << ",minimum_above_premium_fraction.minimum_above_premium_fraction_mantissa=" << msg.fields.minimum_above_premium_fraction.minimum_above_premium_fraction_mantissa.get().value()
       << ",minimum_below_premium_fraction.minimum_below_premium_fraction_exponent=" << static_cast<int>(msg.fields.minimum_below_premium_fraction.minimum_below_premium_fraction_exponent.get().value())
       << ",minimum_below_premium_fraction.minimum_below_premium_fraction_mantissa=" << msg.fields.minimum_below_premium_fraction.minimum_below_premium_fraction_mantissa.get().value()
       << ",exercise_style=\"" << csm_marketdatafeed::exercise_style::to_string(msg.fields.exercise_style.get().value()) << '"'
       << ",contract_size=" << msg.fields.contract_size.get().value()
       << ",no_legs=" << static_cast<unsigned>(msg.fields.no_legs.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const current_market_refresh_message& msg) {
    os << "class_key=" << msg.fields.class_key.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",security_trading_status=\"" << csm_marketdatafeed::security_trading_status::to_string(msg.fields.security_trading_status.get().value()) << '"'
       << ",price_type=" << static_cast<unsigned>(msg.fields.price_type.get().value())
       << ",appl_seq_num=" << msg.fields.appl_seq_num.get().value()
       << ",no_entries=" << static_cast<unsigned>(msg.fields.no_entries.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const market_data_refresh_message& msg) {
    os << "class_key=" << msg.fields.class_key.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",security_trading_status=\"" << csm_marketdatafeed::security_trading_status::to_string(msg.fields.security_trading_status.get().value()) << '"'
       << ",price_type=" << static_cast<unsigned>(msg.fields.price_type.get().value())
       << ",appl_seq_num=" << msg.fields.appl_seq_num.get().value()
       << ",prev_close_px.prev_close_px_exponent=" << static_cast<int>(msg.fields.prev_close_px.prev_close_px_exponent.get().value())
       << ",prev_close_px.prev_close_px_mantissa=" << msg.fields.prev_close_px.prev_close_px_mantissa.get().value()
       << ",trade_volume=" << msg.fields.trade_volume.get().value()
       << ",no_entries=" << static_cast<unsigned>(msg.fields.no_entries.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const current_market_update_message& msg) {
    os << "class_key=" << msg.fields.class_key.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",security_trading_status=\"" << csm_marketdatafeed::security_trading_status::to_string(msg.fields.security_trading_status.get().value()) << '"'
       << ",price_type=" << static_cast<unsigned>(msg.fields.price_type.get().value())
       << ",no_entries=" << static_cast<unsigned>(msg.fields.no_entries.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const recap_update_message& msg) {
    os << "class_key=" << msg.fields.class_key.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",price_type=" << static_cast<unsigned>(msg.fields.price_type.get().value())
       << ",prev_close_px.prev_close_px_exponent=" << static_cast<int>(msg.fields.prev_close_px.prev_close_px_exponent.get().value())
       << ",prev_close_px.prev_close_px_mantissa=" << msg.fields.prev_close_px.prev_close_px_mantissa.get().value()
       << ",trade_volume=" << msg.fields.trade_volume.get().value()
       << ",no_entries=" << static_cast<unsigned>(msg.fields.no_entries.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const ticker_message& msg) {
    os << "class_key=" << msg.fields.class_key.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",price_type=" << static_cast<unsigned>(msg.fields.price_type.get().value())
       << ",no_entries=" << static_cast<unsigned>(msg.fields.no_entries.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const expected_opening_price_and_size_message& msg) {
    os << "class_key=" << msg.fields.class_key.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",eop.eop_exponent=" << static_cast<int>(msg.fields.eop.eop_exponent.get().value())
       << ",eop.eop_mantissa=" << msg.fields.eop.eop_mantissa.get().value()
       << ",eos=" << msg.fields.eos.get().value()
       << ",eop_type=\"" << csm_marketdatafeed::eop_type::to_string(msg.fields.eop_type.get().value()) << '"'
       << ",legal_market=\"" << csm_marketdatafeed::legal_market::to_string(msg.fields.legal_market.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const index_value_message& msg) {
    os << "no_entries=" << static_cast<unsigned>(msg.fields.no_entries.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const settlement_value_message& msg) {
    os << "class_key=" << msg.fields.class_key.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",price_type=" << static_cast<unsigned>(msg.fields.price_type.get().value())
       << ",no_entries=" << static_cast<unsigned>(msg.fields.no_entries.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const summary_message& msg) {
    os << "class_key=" << msg.fields.class_key.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",price_type=" << static_cast<unsigned>(msg.fields.price_type.get().value())
       << ",trade_volume=" << msg.fields.trade_volume.get().value()
       << ",open_interest=" << msg.fields.open_interest.get().value()
       << ",net_chg_prev_day.net_chg_prev_day_exponent=" << static_cast<int>(msg.fields.net_chg_prev_day.net_chg_prev_day_exponent.get().value())
       << ",net_chg_prev_day.net_chg_prev_day_mantissa=" << msg.fields.net_chg_prev_day.net_chg_prev_day_mantissa.get().value()
       << ",underlying_px.underlying_px_exponent=" << static_cast<int>(msg.fields.underlying_px.underlying_px_exponent.get().value())
       << ",underlying_px.underlying_px_mantissa=" << msg.fields.underlying_px.underlying_px_mantissa.get().value()
       << ",no_entries=" << static_cast<unsigned>(msg.fields.no_entries.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const market_data_control_message& msg) {
    os << "md_control_type=\"" << csm_marketdatafeed::md_control_type::to_string(msg.fields.md_control_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const heartbeat_message&) {
    return os;
}

}
