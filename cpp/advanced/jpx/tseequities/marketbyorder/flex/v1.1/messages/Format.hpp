#pragma once

#include <ostream>
#include <string_view>

#include "SecondsTimestampMessage.hpp"
#include "TradingStatusMessage.hpp"
#include "ExecutionSummaryMessage.hpp"
#include "AddOrderMessage.hpp"
#include "OrderExecutedMessage.hpp"
#include "OrderExecutedWithPriceMessage.hpp"
#include "OrderDeleteMessage.hpp"
#include "ResetMessage.hpp"
#include "CommunicationControlMessage.hpp"
#include "LoginRequestMessage.hpp"
#include "LoginResultMessage.hpp"
#include "MessageResponseMessage.hpp"
#include "EndOfMessageMessage.hpp"
#include "../json/messages/message_response_message_json.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

namespace flex_marketbyorder = ::jpx::tseequities::marketbyorder::flex::v1_1;

inline std::ostream& operator<<(std::ostream& os, const packet_header& value) {
    os << "multicast_group_number=" << static_cast<unsigned>(value.multicast_group_number.get().value())
       << ",number_of_system_reboots=" << static_cast<unsigned>(value.number_of_system_reboots.get().value())
       << ",sequence_number=" << value.sequence_number.get().value()
       << ",issue_code=\"" << value.issue_code.get_trimmed().value() << '"'
       << ",update_number=" << value.update_number.get().value()
       << ",packet_number=" << static_cast<unsigned>(value.packet_number.get().value())
       << ",total_number_of_packets=" << static_cast<unsigned>(value.total_number_of_packets.get().value())
       << ",utility_flag=" << static_cast<unsigned>(value.utility_flag.get().value())
       << ",message_count=" << static_cast<unsigned>(value.message_count.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "tag_length=" << static_cast<unsigned>(value.tag_length.get().value())
       << ",message_type=\"" << flex_marketbyorder::message_type::to_string(value.message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const tcp_packet_header& value) {
    os << "packet_length=" << value.packet_length.get().value()
       << ",packet_type=\"" << flex_marketbyorder::packet_type::to_string(value.packet_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const seconds_timestamp_message& msg) {
    os << "time_seconds=" << msg.fields.time_seconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trading_status_message& msg) {
    os << "time_microseconds=" << msg.fields.time_microseconds.get().value()
       << ",market_status=\"" << flex_marketbyorder::market_status::to_string(msg.fields.market_status.get().value()) << '"'
       << ",status_flag=\"" << msg.fields.status_flag.get_trimmed().value() << '"'
       << ",short_selling_status=\"" << flex_marketbyorder::short_selling_status::to_string(msg.fields.short_selling_status.get().value()) << '"'
       << ",pricing_method=\"" << flex_marketbyorder::pricing_method::to_string(msg.fields.pricing_method.get().value()) << '"'
       << ",book_center_price=" << msg.fields.book_center_price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const execution_summary_message& msg) {
    os << "time_microseconds=" << msg.fields.time_microseconds.get().value()
       << ",triggered_side=\"" << flex_marketbyorder::triggered_side::to_string(msg.fields.triggered_side.get().value()) << '"'
       << ",total_volume=" << msg.fields.total_volume.get().value()
       << ",total_invalidation=" << msg.fields.total_invalidation.get().value()
       << ",last_price=" << msg.fields.last_price.get().value()
       << ",match_id=" << msg.fields.match_id.get().value()
       << ",best_offer=" << msg.fields.best_offer.get().value()
       << ",best_bid=" << msg.fields.best_bid.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_order_message& msg) {
    os << "time_microseconds=" << msg.fields.time_microseconds.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",side=\"" << flex_marketbyorder::side::to_string(msg.fields.side.get().value()) << '"'
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",order_condition=\"" << flex_marketbyorder::order_condition::to_string(msg.fields.order_condition.get().value()) << '"'
       << ",modification_flag=\"" << flex_marketbyorder::modification_flag::to_string(msg.fields.modification_flag.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_executed_message& msg) {
    os << "time_microseconds=" << msg.fields.time_microseconds.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",side=\"" << flex_marketbyorder::side::to_string(msg.fields.side.get().value()) << '"'
       << ",volume=" << msg.fields.volume.get().value()
       << ",match_id=" << msg.fields.match_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_executed_with_price_message& msg) {
    os << "time_microseconds=" << msg.fields.time_microseconds.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",side=\"" << flex_marketbyorder::side::to_string(msg.fields.side.get().value()) << '"'
       << ",volume=" << msg.fields.volume.get().value()
       << ",match_id=" << msg.fields.match_id.get().value()
       << ",execution_price=" << msg.fields.execution_price.get().value()
       << ",adopted_pricing_method=\"" << flex_marketbyorder::adopted_pricing_method::to_string(msg.fields.adopted_pricing_method.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_delete_message& msg) {
    os << "time_microseconds=" << msg.fields.time_microseconds.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",side=\"" << flex_marketbyorder::side::to_string(msg.fields.side.get().value()) << '"'
       << ",modification_flag=\"" << flex_marketbyorder::modification_flag::to_string(msg.fields.modification_flag.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const reset_message& msg) {
    os << "reset_start_end_flag=\"" << flex_marketbyorder::reset_start_end_flag::to_string(msg.fields.reset_start_end_flag.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const communication_control_message& msg) {
    os << "test_mode_flag=\"" << flex_marketbyorder::test_mode_flag::to_string(msg.fields.test_mode_flag.get().value()) << '"'
       << ",communication_start_end_flag=\"" << flex_marketbyorder::communication_start_end_flag::to_string(msg.fields.communication_start_end_flag.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const login_request_message& msg) {
    os << "user_id=\"" << msg.fields.user_id.get_trimmed().value() << '"'
       << ",multicast_group_number=" << static_cast<unsigned>(msg.fields.multicast_group_number.get().value())
       << ",number_of_system_reboots=" << static_cast<unsigned>(msg.fields.number_of_system_reboots.get().value())
       << ",sequence_number=" << msg.fields.sequence_number.get().value()
       << ",requested_message_count=" << msg.fields.requested_message_count.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const login_result_message& msg) {
    os << "multicast_group_number=" << static_cast<unsigned>(msg.fields.multicast_group_number.get().value())
       << ",result_code=\"" << flex_marketbyorder::result_code::to_string(msg.fields.result_code.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_response_message& msg) {
    os << "tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const end_of_message_message& msg) {
    os << "multicast_group_number=" << static_cast<unsigned>(msg.fields.multicast_group_number.get().value())
       << ",number_of_system_reboots=" << static_cast<unsigned>(msg.fields.number_of_system_reboots.get().value())
       << ",next_sequence_number=" << msg.fields.next_sequence_number.get().value()
       ;
    return os;
}

}
