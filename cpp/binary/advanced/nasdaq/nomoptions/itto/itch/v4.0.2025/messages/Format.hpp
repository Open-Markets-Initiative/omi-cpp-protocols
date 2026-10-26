#pragma once

#include <ostream>
#include <string_view>

#include "DebugPacket.hpp"
#include "LoginRequestPacket.hpp"
#include "UnsequencedDataPacket.hpp"
#include "LoginAcceptedPacket.hpp"
#include "LoginRejectedPacket.hpp"
#include "SequencedDataPacket.hpp"
#include "SystemEventMessage.hpp"
#include "OptionsDirectoryMessage.hpp"
#include "TradingActionMessage.hpp"
#include "SecurityOpenMessage.hpp"
#include "AddOrderMessageShortMessageForm.hpp"
#include "AddOrderMessageLongFormMessage.hpp"
#include "AddQuoteMessageShortFormMessage.hpp"
#include "AddQuoteMessageLongFormMessage.hpp"
#include "SingleSideExecutedMessage.hpp"
#include "SingleSideExecutedWithPriceMessage.hpp"
#include "OrderCancelMessage.hpp"
#include "SingleSideReplaceMessageShortForm.hpp"
#include "SingleSideReplaceMessageLongForm.hpp"
#include "SingleSideDeleteMessage.hpp"
#include "SingleSideChangeMessage.hpp"
#include "QuoteReplaceMessageShortForm.hpp"
#include "QuoteReplaceMessageLongForm.hpp"
#include "QuoteDeleteMessage.hpp"
#include "OptionsTradeMessagesNonAuction.hpp"
#include "OptionsCrossTradeMessage.hpp"
#include "BrokenTradeOrderExecutedMessage.hpp"
#include "NoiiMessage.hpp"
#include "EndOfReplaySequenceMessage.hpp"
#include "../json/messages/debug_packet_json.hpp"
#include "../json/messages/unsequenced_data_packet_json.hpp"
#include "../json/messages/sequenced_data_packet_json.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

namespace itch_itto = ::nasdaq::nomoptions::itto::itch::v4_0_2025;

inline std::ostream& operator<<(std::ostream& os, const client_packet_header& value) {
    os << "packet_length=" << value.packet_length.get().value()
       << ",client_packet_type=\"" << itch_itto::client_packet_type::to_string(value.client_packet_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const server_packet_header& value) {
    os << "packet_length=" << value.packet_length.get().value()
       << ",server_packet_type=\"" << itch_itto::server_packet_type::to_string(value.server_packet_type.get().value()) << '"'
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
       << ",message_type=\"" << itch_itto::message_type::to_string(value.message_type.get().value()) << '"'
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
    os << "reject_reason_code=\"" << itch_itto::reject_reason_code::to_string(msg.fields.reject_reason_code.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const sequenced_data_packet& msg) {
    os << "sequenced_message_type=\"" << itch_itto::sequenced_message_type::to_string(msg.fields.sequenced_message_type.get().value()) << '"'
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const system_event_message& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",event_code=\"" << itch_itto::event_code::to_string(msg.fields.event_code.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const options_directory_message& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",option_id=" << msg.fields.option_id.get().value()
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",expiration_year=" << static_cast<unsigned>(msg.fields.expiration_year.get().value())
       << ",expiration_month=" << static_cast<unsigned>(msg.fields.expiration_month.get().value())
       << ",expiration_date=" << static_cast<unsigned>(msg.fields.expiration_date.get().value())
       << ",explicit_strike_price=" << msg.fields.explicit_strike_price.get().value()
       << ",option_type=\"" << itch_itto::option_type::to_string(msg.fields.option_type.get().value()) << '"'
       << ",source=" << static_cast<unsigned>(msg.fields.source.get().value())
       << ",underlying_symbol=\"" << msg.fields.underlying_symbol.get_trimmed().value() << '"'
       << ",options_closing_type=\"" << itch_itto::options_closing_type::to_string(msg.fields.options_closing_type.get().value()) << '"'
       << ",tradable=\"" << itch_itto::tradable::to_string(msg.fields.tradable.get().value()) << '"'
       << ",mpv=\"" << itch_itto::mpv::to_string(msg.fields.mpv.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trading_action_message& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",option_id=" << msg.fields.option_id.get().value()
       << ",current_trading_state=\"" << itch_itto::current_trading_state::to_string(msg.fields.current_trading_state.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const security_open_message& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",option_id=" << msg.fields.option_id.get().value()
       << ",open_state=\"" << itch_itto::open_state::to_string(msg.fields.open_state.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_order_message_short_message_form& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",order_reference_number=" << msg.fields.order_reference_number.get().value()
       << ",market_side=\"" << itch_itto::market_side::to_string(msg.fields.market_side.get().value()) << '"'
       << ",option_id=" << msg.fields.option_id.get().value()
       << ",price_short=" << msg.fields.price_short.get().value()
       << ",volume_short=" << msg.fields.volume_short.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_order_message_long_form_message& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",order_reference_number=" << msg.fields.order_reference_number.get().value()
       << ",market_side=\"" << itch_itto::market_side::to_string(msg.fields.market_side.get().value()) << '"'
       << ",option_id=" << msg.fields.option_id.get().value()
       << ",price_long=" << msg.fields.price_long.get().value()
       << ",volume_long=" << msg.fields.volume_long.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_quote_message_short_form_message& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",bid_reference_number=" << msg.fields.bid_reference_number.get().value()
       << ",ask_reference_number=" << msg.fields.ask_reference_number.get().value()
       << ",option_id=" << msg.fields.option_id.get().value()
       << ",bid_price_short=" << msg.fields.bid_price_short.get().value()
       << ",bid_size_short=" << msg.fields.bid_size_short.get().value()
       << ",ask_price_short=" << msg.fields.ask_price_short.get().value()
       << ",ask_size_short=" << msg.fields.ask_size_short.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_quote_message_long_form_message& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",bid_reference_number=" << msg.fields.bid_reference_number.get().value()
       << ",ask_reference_number=" << msg.fields.ask_reference_number.get().value()
       << ",option_id=" << msg.fields.option_id.get().value()
       << ",bid=" << msg.fields.bid.get().value()
       << ",bid_size_long=" << msg.fields.bid_size_long.get().value()
       << ",ask=" << msg.fields.ask.get().value()
       << ",ask_size_long=" << msg.fields.ask_size_long.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const single_side_executed_message& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",reference_number=" << msg.fields.reference_number.get().value()
       << ",executed_contracts=" << msg.fields.executed_contracts.get().value()
       << ",cross_number=" << msg.fields.cross_number.get().value()
       << ",match_number=" << msg.fields.match_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const single_side_executed_with_price_message& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",reference_number=" << msg.fields.reference_number.get().value()
       << ",cross_number=" << msg.fields.cross_number.get().value()
       << ",match_number=" << msg.fields.match_number.get().value()
       << ",printable=\"" << itch_itto::printable::to_string(msg.fields.printable.get().value()) << '"'
       << ",price_long=" << msg.fields.price_long.get().value()
       << ",volume_long=" << msg.fields.volume_long.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_cancel_message& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",order_reference_number=" << msg.fields.order_reference_number.get().value()
       << ",cancelled_contracts=" << msg.fields.cancelled_contracts.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const single_side_replace_message_short_form& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",original_reference_number=" << msg.fields.original_reference_number.get().value()
       << ",new_reference_number=" << msg.fields.new_reference_number.get().value()
       << ",price_short=" << msg.fields.price_short.get().value()
       << ",volume_short=" << msg.fields.volume_short.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const single_side_replace_message_long_form& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",original_reference_number=" << msg.fields.original_reference_number.get().value()
       << ",new_reference_number=" << msg.fields.new_reference_number.get().value()
       << ",price_long=" << msg.fields.price_long.get().value()
       << ",volume_long=" << msg.fields.volume_long.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const single_side_delete_message& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",reference_number=" << msg.fields.reference_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const single_side_change_message& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",reference_number=" << msg.fields.reference_number.get().value()
       << ",change_reason=\"" << itch_itto::change_reason::to_string(msg.fields.change_reason.get().value()) << '"'
       << ",price_long=" << msg.fields.price_long.get().value()
       << ",volume_long=" << msg.fields.volume_long.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const quote_replace_message_short_form& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",original_bid_reference_number=" << msg.fields.original_bid_reference_number.get().value()
       << ",bid_reference_number=" << msg.fields.bid_reference_number.get().value()
       << ",original_ask_reference_number=" << msg.fields.original_ask_reference_number.get().value()
       << ",ask_reference_number=" << msg.fields.ask_reference_number.get().value()
       << ",bid_price_short=" << msg.fields.bid_price_short.get().value()
       << ",bid_size_short=" << msg.fields.bid_size_short.get().value()
       << ",ask_price_short=" << msg.fields.ask_price_short.get().value()
       << ",ask_size_short=" << msg.fields.ask_size_short.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const quote_replace_message_long_form& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",original_bid_reference_number=" << msg.fields.original_bid_reference_number.get().value()
       << ",bid_reference_number=" << msg.fields.bid_reference_number.get().value()
       << ",original_ask_reference_number=" << msg.fields.original_ask_reference_number.get().value()
       << ",ask_reference_number=" << msg.fields.ask_reference_number.get().value()
       << ",bid_price_long=" << msg.fields.bid_price_long.get().value()
       << ",bid_size_long=" << msg.fields.bid_size_long.get().value()
       << ",ask_price_long=" << msg.fields.ask_price_long.get().value()
       << ",ask_size_long=" << msg.fields.ask_size_long.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const quote_delete_message& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",bid_reference_number=" << msg.fields.bid_reference_number.get().value()
       << ",ask_reference_number=" << msg.fields.ask_reference_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const options_trade_messages_non_auction& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",buy_sell_indicator=\"" << itch_itto::buy_sell_indicator::to_string(msg.fields.buy_sell_indicator.get().value()) << '"'
       << ",option_id=" << msg.fields.option_id.get().value()
       << ",cross_number=" << msg.fields.cross_number.get().value()
       << ",match_number=" << msg.fields.match_number.get().value()
       << ",price_long=" << msg.fields.price_long.get().value()
       << ",volume_long=" << msg.fields.volume_long.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const options_cross_trade_message& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",option_id=" << msg.fields.option_id.get().value()
       << ",cross_number=" << msg.fields.cross_number.get().value()
       << ",match_number=" << msg.fields.match_number.get().value()
       << ",cross_type=\"" << itch_itto::cross_type::to_string(msg.fields.cross_type.get().value()) << '"'
       << ",price_long=" << msg.fields.price_long.get().value()
       << ",volume_long=" << msg.fields.volume_long.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const broken_trade_order_executed_message& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",cross_number=" << msg.fields.cross_number.get().value()
       << ",match_number=" << msg.fields.match_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const noii_message& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",auction_id=" << msg.fields.auction_id.get().value()
       << ",auction_type=\"" << itch_itto::auction_type::to_string(msg.fields.auction_type.get().value()) << '"'
       << ",paired_contracts=" << msg.fields.paired_contracts.get().value()
       << ",imbalance_direction=\"" << itch_itto::imbalance_direction::to_string(msg.fields.imbalance_direction.get().value()) << '"'
       << ",option_id=" << msg.fields.option_id.get().value()
       << ",imbalance_price=" << msg.fields.imbalance_price.get().value()
       << ",imbalance_volume=" << msg.fields.imbalance_volume.get().value()
       << ",customer_firm_indicator=\"" << itch_itto::customer_firm_indicator::to_string(msg.fields.customer_firm_indicator.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const end_of_replay_sequence_message& msg) {
    os << "end_of_replay_sequence_number=\"" << msg.fields.end_of_replay_sequence_number.get_trimmed().value() << '"'
       ;
    return os;
}

}
