#pragma once

#include <ostream>
#include <string_view>

#include "QuoteUpdateMessage.hpp"
#include "TradeReportMessage.hpp"
#include "TradeBreakMessage.hpp"

namespace iex::iexequities::tops::iextp::v1_56 {

namespace iextp_tops = ::iex::iexequities::tops::iextp::v1_56;

inline std::ostream& operator<<(std::ostream& os, const iextp_header& value) {
    os << "version=" << static_cast<unsigned>(value.version.get().value())
       << ",message_protocol_id=" << value.message_protocol_id.get().value()
       << ",channel_id=" << value.channel_id.get().value()
       << ",session_id=" << value.session_id.get().value()
       << ",payload_length=" << value.payload_length.get().value()
       << ",message_count=" << value.message_count.get().value()
       << ",stream_offset=" << value.stream_offset.get().value()
       << ",first_message_sequence_number=" << value.first_message_sequence_number.get().value()
       << ",send_time=" << value.send_time.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "message_length=" << value.message_length.get().value()
       << ",message_type=\"" << iextp_tops::message_type::to_string(value.message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const quote_update_message& msg) {
    os << "quote_update_flags=" << static_cast<unsigned>(msg.fields.quote_update_flags.get().value())
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",bid_size=" << msg.fields.bid_size.get().value()
       << ",bid_price=" << msg.fields.bid_price.get().value()
       << ",ask_price=" << msg.fields.ask_price.get().value()
       << ",ask_size=" << msg.fields.ask_size.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_report_message& msg) {
    os << "sale_condition_flags=" << static_cast<unsigned>(msg.fields.sale_condition_flags.get().value())
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",size=" << msg.fields.size.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_break_message& msg) {
    os << "sale_condition_flags=" << static_cast<unsigned>(msg.fields.sale_condition_flags.get().value())
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",size=" << msg.fields.size.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       ;
    return os;
}

}
