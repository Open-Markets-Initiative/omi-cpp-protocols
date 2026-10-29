#pragma once

#include <ostream>
#include <string_view>

#include "SystemEventMessage.hpp"
#include "ComplexStrategyDirectoryMessage.hpp"
#include "StrategyOpenClosedMessage.hpp"
#include "StrategyTradingActionMessage.hpp"
#include "StrategyBestBidAndAskUpdate.hpp"
#include "StrategyBestBidUpdate.hpp"
#include "StrategyBestAskUpdate.hpp"
#include "ComplexStrategyTickerMessage.hpp"
#include "../json/messages/complex_strategy_directory_message_json.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

namespace itch_topcomboquotefeed = ::nasdaq::iseoptions::topcomboquotefeed::itch::v1_0;

inline std::ostream& operator<<(std::ostream& os, const packet_header& value) {
    os << "session=\"" << value.session.get_trimmed().value() << '"'
       << ",sequence_number=" << value.sequence_number.get().value()
       << ",message_count=" << value.message_count.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "message_length=" << value.message_length.get().value()
       << ",message_type=\"" << itch_topcomboquotefeed::message_type::to_string(value.message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const system_event_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",event_code=\"" << itch_topcomboquotefeed::event_code::to_string(msg.fields.event_code.get().value()) << '"'
       << ",current_year=" << msg.fields.current_year.get().value()
       << ",current_month=" << static_cast<unsigned>(msg.fields.current_month.get().value())
       << ",current_day=" << static_cast<unsigned>(msg.fields.current_day.get().value())
       << ",version=" << static_cast<unsigned>(msg.fields.version.get().value())
       << ",sub_version=" << static_cast<unsigned>(msg.fields.sub_version.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const complex_strategy_directory_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",strategy_id=" << msg.fields.strategy_id.get().value()
       << ",strategy_type=\"" << itch_topcomboquotefeed::strategy_type::to_string(msg.fields.strategy_type.get().value()) << '"'
       << ",source=" << static_cast<unsigned>(msg.fields.source.get().value())
       << ",underlying_symbol=\"" << msg.fields.underlying_symbol.get_trimmed().value() << '"'
       << ",number_of_legs=" << static_cast<unsigned>(msg.fields.number_of_legs.get().value())
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const strategy_open_closed_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",strategy_id=" << msg.fields.strategy_id.get().value()
       << ",open_state=\"" << itch_topcomboquotefeed::open_state::to_string(msg.fields.open_state.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const strategy_trading_action_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",strategy_id=" << msg.fields.strategy_id.get().value()
       << ",current_trading_state=\"" << itch_topcomboquotefeed::current_trading_state::to_string(msg.fields.current_trading_state.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const strategy_best_bid_and_ask_update& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",strategy_id=" << msg.fields.strategy_id.get().value()
       << ",quote_condition=\"" << itch_topcomboquotefeed::quote_condition::to_string(msg.fields.quote_condition.get().value()) << '"'
       << ",bid_price=" << msg.fields.bid_price.get().value()
       << ",bid_size=" << msg.fields.bid_size.get().value()
       << ",bid_cust_size=" << msg.fields.bid_cust_size.get().value()
       << ",bid_pro_cust_size=" << msg.fields.bid_pro_cust_size.get().value()
       << ",bid_ntt_size=" << msg.fields.bid_ntt_size.get().value()
       << ",bid_market_size=" << msg.fields.bid_market_size.get().value()
       << ",bid_ntt_market_size=" << msg.fields.bid_ntt_market_size.get().value()
       << ",ask_price=" << msg.fields.ask_price.get().value()
       << ",ask_size=" << msg.fields.ask_size.get().value()
       << ",ask_cust_size=" << msg.fields.ask_cust_size.get().value()
       << ",ask_pro_cust_size=" << msg.fields.ask_pro_cust_size.get().value()
       << ",ask_ntt_size=" << msg.fields.ask_ntt_size.get().value()
       << ",ask_market_size=" << msg.fields.ask_market_size.get().value()
       << ",ask_ntt_market_size=" << msg.fields.ask_ntt_market_size.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const strategy_best_bid_update& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",strategy_id=" << msg.fields.strategy_id.get().value()
       << ",quote_condition=\"" << itch_topcomboquotefeed::quote_condition::to_string(msg.fields.quote_condition.get().value()) << '"'
       << ",price=" << msg.fields.price.get().value()
       << ",size=" << msg.fields.size.get().value()
       << ",cust_size=" << msg.fields.cust_size.get().value()
       << ",pro_cust_size=" << msg.fields.pro_cust_size.get().value()
       << ",ntt_size=" << msg.fields.ntt_size.get().value()
       << ",market_size=" << msg.fields.market_size.get().value()
       << ",ntt_market_size=" << msg.fields.ntt_market_size.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const strategy_best_ask_update& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",strategy_id=" << msg.fields.strategy_id.get().value()
       << ",quote_condition=\"" << itch_topcomboquotefeed::quote_condition::to_string(msg.fields.quote_condition.get().value()) << '"'
       << ",price=" << msg.fields.price.get().value()
       << ",size=" << msg.fields.size.get().value()
       << ",cust_size=" << msg.fields.cust_size.get().value()
       << ",pro_cust_size=" << msg.fields.pro_cust_size.get().value()
       << ",ntt_size=" << msg.fields.ntt_size.get().value()
       << ",market_size=" << msg.fields.market_size.get().value()
       << ",ntt_market_size=" << msg.fields.ntt_market_size.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const complex_strategy_ticker_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",strategy_id=" << msg.fields.strategy_id.get().value()
       << ",last_price=" << msg.fields.last_price.get().value()
       << ",size=" << msg.fields.size.get().value()
       << ",volume=" << msg.fields.volume.get().value()
       << ",high=" << msg.fields.high.get().value()
       << ",low=" << msg.fields.low.get().value()
       << ",first=" << msg.fields.first.get().value()
       << ",trade_condition=\"" << msg.fields.trade_condition.get().value() << '"'
       ;
    return os;
}

}
