#pragma once

#include <ostream>
#include <string_view>

#include "SystemEventMessage.hpp"
#include "ComplexStrategyDirectoryMessage.hpp"
#include "StrategyTradingActionMessage.hpp"
#include "StrategyOpenClosedMessage.hpp"
#include "ComplexStrategyOrderOnBookMessage.hpp"
#include "ComplexStrategyAuctionMessage.hpp"
#include "../json/messages/complex_strategy_directory_message_json.hpp"
#include "../json/messages/complex_strategy_auction_message_json.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

namespace itch_ordercombofeed = ::nasdaq::iseoptions::ordercombofeed::itch::v1_1;

inline std::ostream& operator<<(std::ostream& os, const packet_header& value) {
    os << "session=\"" << value.session.get_trimmed().value() << '"'
       << ",sequence_number=" << value.sequence_number.get().value()
       << ",message_count=" << value.message_count.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "message_length=" << value.message_length.get().value()
       << ",message_type=\"" << itch_ordercombofeed::message_type::to_string(value.message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const system_event_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",event_code=\"" << itch_ordercombofeed::event_code::to_string(msg.fields.event_code.get().value()) << '"'
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
       << ",strategy_type=\"" << itch_ordercombofeed::strategy_type::to_string(msg.fields.strategy_type.get().value()) << '"'
       << ",source=" << static_cast<unsigned>(msg.fields.source.get().value())
       << ",underlying_symbol=\"" << msg.fields.underlying_symbol.get_trimmed().value() << '"'
       << ",number_of_legs=" << static_cast<unsigned>(msg.fields.number_of_legs.get().value())
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const strategy_trading_action_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",strategy_id=" << msg.fields.strategy_id.get().value()
       << ",current_trading_state=\"" << itch_ordercombofeed::current_trading_state::to_string(msg.fields.current_trading_state.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const strategy_open_closed_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",strategy_id=" << msg.fields.strategy_id.get().value()
       << ",open_state=\"" << itch_ordercombofeed::open_state::to_string(msg.fields.open_state.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const complex_strategy_order_on_book_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",strategy_id=" << msg.fields.strategy_id.get().value()
       << ",order_type=\"" << itch_ordercombofeed::order_type::to_string(msg.fields.order_type.get().value()) << '"'
       << ",side=\"" << itch_ordercombofeed::side::to_string(msg.fields.side.get().value()) << '"'
       << ",price=" << msg.fields.price.get().value()
       << ",size=" << msg.fields.size.get().value()
       << ",exec_flag=\"" << itch_ordercombofeed::exec_flag::to_string(msg.fields.exec_flag.get().value()) << '"'
       << ",order_capacity=\"" << itch_ordercombofeed::order_capacity::to_string(msg.fields.order_capacity.get().value()) << '"'
       << ",scope=\"" << itch_ordercombofeed::scope::to_string(msg.fields.scope.get().value()) << '"'
       << ",owner_id=\"" << msg.fields.owner_id.get_trimmed().value() << '"'
       << ",giveup=\"" << msg.fields.giveup.get_trimmed().value() << '"'
       << ",cmta=\"" << msg.fields.cmta.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const complex_strategy_auction_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",strategy_id=" << msg.fields.strategy_id.get().value()
       << ",auction_id=" << msg.fields.auction_id.get().value()
       << ",order_type=\"" << itch_ordercombofeed::order_type::to_string(msg.fields.order_type.get().value()) << '"'
       << ",side=\"" << itch_ordercombofeed::side::to_string(msg.fields.side.get().value()) << '"'
       << ",price=" << msg.fields.price.get().value()
       << ",size=" << msg.fields.size.get().value()
       << ",exec_flag=\"" << itch_ordercombofeed::exec_flag::to_string(msg.fields.exec_flag.get().value()) << '"'
       << ",order_capacity=\"" << itch_ordercombofeed::order_capacity::to_string(msg.fields.order_capacity.get().value()) << '"'
       << ",scope=\"" << itch_ordercombofeed::scope::to_string(msg.fields.scope.get().value()) << '"'
       << ",owner_id=\"" << msg.fields.owner_id.get_trimmed().value() << '"'
       << ",giveup=\"" << msg.fields.giveup.get_trimmed().value() << '"'
       << ",cmta=\"" << msg.fields.cmta.get_trimmed().value() << '"'
       << ",auction_event=\"" << itch_ordercombofeed::auction_event::to_string(msg.fields.auction_event.get().value()) << '"'
       << ",auction_type=\"" << itch_ordercombofeed::auction_type::to_string(msg.fields.auction_type.get().value()) << '"'
       << ",number_of_responses=" << static_cast<unsigned>(msg.fields.number_of_responses.get().value())
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

}
