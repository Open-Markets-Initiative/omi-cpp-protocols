#pragma once

#include <ostream>
#include <string_view>

#include "DebugPacket.hpp"
#include "LoginRequestPacket.hpp"
#include "UnsequencedDataPacket.hpp"
#include "LoginAcceptedPacket.hpp"
#include "LoginRejectedPacket.hpp"
#include "SequencedDataPacket.hpp"
#include "TimestampMessage.hpp"
#include "SystemEventMessage.hpp"
#include "OptionsDirectoryMessage.hpp"
#include "TradingActionMessage.hpp"
#include "SecurityOpenClosedMessage.hpp"
#include "ShortBestBidAndAskUpdateMessage.hpp"
#include "LongBestBidAndAskUpdateMessage.hpp"
#include "ShortBestAskUpdateMessage.hpp"
#include "ShortBestBidUpdateMessage.hpp"
#include "LongBestAskUpdateMessage.hpp"
#include "LongBestBidUpdateMessage.hpp"
#include "TradeReportMessage.hpp"
#include "BrokenTradeReportMessage.hpp"
#include "EndOfReplaySequenceMessage.hpp"
#include "../json/messages/debug_packet_json.hpp"
#include "../json/messages/unsequenced_data_packet_json.hpp"
#include "../json/messages/sequenced_data_packet_json.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

namespace itch_topofmarket = ::nasdaq::phlxoptions::topofmarket::itch::v3_4;

inline std::ostream& operator<<(std::ostream& os, const client_packet_header& value) {
    os << "packet_length=" << value.packet_length.get().value()
       << ",client_packet_type=\"" << itch_topofmarket::client_packet_type::to_string(value.client_packet_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const server_packet_header& value) {
    os << "packet_length=" << value.packet_length.get().value()
       << ",server_packet_type=\"" << itch_topofmarket::server_packet_type::to_string(value.server_packet_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const packet_header& value) {
    os << "session=\"" << value.session.get_trimmed().value() << '"'
       << ",sequence_number=" << value.sequence_number.get().value()
       << ",message_count=" << value.message_count.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "message_length=" << value.message_length.get().value()
       << ",message_type=\"" << itch_topofmarket::message_type::to_string(value.message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const debug_packet& msg) {
    os << "tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const login_request_packet& msg) {
    os << "username=\"" << msg.fields.username.get_trimmed().value() << '"'
       << ",password=\"" << msg.fields.password.get_trimmed().value() << '"'
       << ",requested_session=\"" << msg.fields.requested_session.get_trimmed().value() << '"'
       << ",requested_sequence_number=\"" << msg.fields.requested_sequence_number.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const unsequenced_data_packet& msg) {
    os << "unsequenced_message_type=\"" << msg.fields.unsequenced_message_type.get().value() << '"'
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const login_accepted_packet& msg) {
    os << "accepted_session=\"" << msg.fields.accepted_session.get_trimmed().value() << '"'
       << ",accepted_sequence_number=\"" << msg.fields.accepted_sequence_number.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const login_rejected_packet& msg) {
    os << "reject_reason_code=\"" << itch_topofmarket::reject_reason_code::to_string(msg.fields.reject_reason_code.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const sequenced_data_packet& msg) {
    os << "sequenced_message_type=\"" << itch_topofmarket::sequenced_message_type::to_string(msg.fields.sequenced_message_type.get().value()) << '"'
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const timestamp_message& msg) {
    os << "second=" << msg.fields.second.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const system_event_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",event_code=\"" << itch_topofmarket::event_code::to_string(msg.fields.event_code.get().value()) << '"'
       << ",version=" << static_cast<unsigned>(msg.fields.version.get().value())
       << ",sub_version=" << static_cast<unsigned>(msg.fields.sub_version.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const options_directory_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",option_id=" << msg.fields.option_id.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",expiration_year=" << static_cast<unsigned>(msg.fields.expiration_year.get().value())
       << ",expiration_month=" << static_cast<unsigned>(msg.fields.expiration_month.get().value())
       << ",expiration_day=" << static_cast<unsigned>(msg.fields.expiration_day.get().value())
       << ",strike_price=" << msg.fields.strike_price.get().value()
       << ",option_type=\"" << itch_topofmarket::option_type::to_string(msg.fields.option_type.get().value()) << '"'
       << ",source=" << static_cast<unsigned>(msg.fields.source.get().value())
       << ",underlying_symbol=\"" << msg.fields.underlying_symbol.get_trimmed().value() << '"'
       << ",option_closing_type=\"" << itch_topofmarket::option_closing_type::to_string(msg.fields.option_closing_type.get().value()) << '"'
       << ",tradable=\"" << itch_topofmarket::tradable::to_string(msg.fields.tradable.get().value()) << '"'
       << ",mpv=\"" << itch_topofmarket::mpv::to_string(msg.fields.mpv.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trading_action_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",option_id=" << msg.fields.option_id.get().value()
       << ",current_trading_state=\"" << itch_topofmarket::current_trading_state::to_string(msg.fields.current_trading_state.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const security_open_closed_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",option_id=" << msg.fields.option_id.get().value()
       << ",open_state=\"" << itch_topofmarket::open_state::to_string(msg.fields.open_state.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const short_best_bid_and_ask_update_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",option_id=" << msg.fields.option_id.get().value()
       << ",quote_condition=\"" << itch_topofmarket::quote_condition::to_string(msg.fields.quote_condition.get().value()) << '"'
       << ",bid_price_2=" << msg.fields.bid_price_2.get().value()
       << ",bid_size_2=" << msg.fields.bid_size_2.get().value()
       << ",ask_price_2=" << msg.fields.ask_price_2.get().value()
       << ",ask_size_2=" << msg.fields.ask_size_2.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const long_best_bid_and_ask_update_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",option_id=" << msg.fields.option_id.get().value()
       << ",quote_condition=\"" << itch_topofmarket::quote_condition::to_string(msg.fields.quote_condition.get().value()) << '"'
       << ",bid_price_4=" << msg.fields.bid_price_4.get().value()
       << ",bid_size_4=" << msg.fields.bid_size_4.get().value()
       << ",ask_price_4=" << msg.fields.ask_price_4.get().value()
       << ",ask_size_4=" << msg.fields.ask_size_4.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const short_best_ask_update_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",option_id=" << msg.fields.option_id.get().value()
       << ",quote_condition=\"" << itch_topofmarket::quote_condition::to_string(msg.fields.quote_condition.get().value()) << '"'
       << ",price_2=" << msg.fields.price_2.get().value()
       << ",size_2=" << msg.fields.size_2.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const short_best_bid_update_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",option_id=" << msg.fields.option_id.get().value()
       << ",quote_condition=\"" << itch_topofmarket::quote_condition::to_string(msg.fields.quote_condition.get().value()) << '"'
       << ",price_2=" << msg.fields.price_2.get().value()
       << ",size_2=" << msg.fields.size_2.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const long_best_ask_update_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",option_id=" << msg.fields.option_id.get().value()
       << ",quote_condition=\"" << itch_topofmarket::quote_condition::to_string(msg.fields.quote_condition.get().value()) << '"'
       << ",price_4=" << msg.fields.price_4.get().value()
       << ",size_4=" << msg.fields.size_4.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const long_best_bid_update_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",option_id=" << msg.fields.option_id.get().value()
       << ",quote_condition=\"" << itch_topofmarket::quote_condition::to_string(msg.fields.quote_condition.get().value()) << '"'
       << ",price_4=" << msg.fields.price_4.get().value()
       << ",size_4=" << msg.fields.size_4.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_report_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",option_id=" << msg.fields.option_id.get().value()
       << ",cross_id=" << msg.fields.cross_id.get().value()
       << ",trade_condition=\"" << msg.fields.trade_condition.get().value() << '"'
       << ",price_4=" << msg.fields.price_4.get().value()
       << ",volume=" << msg.fields.volume.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const broken_trade_report_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",option_id=" << msg.fields.option_id.get().value()
       << ",original_cross_id=" << msg.fields.original_cross_id.get().value()
       << ",original_price=" << msg.fields.original_price.get().value()
       << ",original_volume=" << msg.fields.original_volume.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const end_of_replay_sequence_message& msg) {
    os << "end_of_replay_sequence_number=\"" << msg.fields.end_of_replay_sequence_number.get_trimmed().value() << '"'
       ;
    return os;
}

}
