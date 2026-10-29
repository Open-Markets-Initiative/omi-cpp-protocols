#pragma once

#include <ostream>
#include <string_view>

#include "ComplexQuoteMessage.hpp"
#include "ComplexTradeMessage.hpp"
#include "ComplexCrossingRfqMessage.hpp"
#include "ComplexCubeRfqMessage.hpp"
#include "ComplexStatusMessage.hpp"
#include "RefreshComplexQuoteMessage.hpp"
#include "RefreshComplexTradeMessage.hpp"
#include "ComplexSymbolDefinitionMessage.hpp"
#include "StreamIdMessage.hpp"
#include "SequenceNumberResetMessage.hpp"
#include "../json/messages/complex_symbol_definition_message_json.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

namespace xdp_complexfeed = ::nyse::amexoptions::complexfeed::xdp::v1_3_a;

inline std::ostream& operator<<(std::ostream& os, const packet_header& value) {
    os << "packet_size=" << value.packet_size.get().value()
       << ",delivery_flag=\"" << xdp_complexfeed::delivery_flag::to_string(value.delivery_flag.get().value()) << '"'
       << ",message_count=" << static_cast<unsigned>(value.message_count.get().value())
       << ",sequence_number=" << value.sequence_number.get().value()
       << ",send_time.seconds=" << value.send_time.seconds.get().value()
       << ",send_time.nanoseconds=" << value.send_time.nanoseconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "message_size=" << value.message_size.get().value()
       << ",message_type=\"" << xdp_complexfeed::message_type::to_string(value.message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const send_time& value) {
    os << "seconds=" << value.seconds.get().value()
       << ",nanoseconds=" << value.nanoseconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const complex_quote_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",complex_index=" << msg.fields.complex_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",ask_price=" << msg.fields.ask_price.get().value()
       << ",bid_price=" << msg.fields.bid_price.get().value()
       << ",ask_volume=" << msg.fields.ask_volume.get().value()
       << ",bid_volume=" << msg.fields.bid_volume.get().value()
       << ",ask_customer_volume=" << msg.fields.ask_customer_volume.get().value()
       << ",bid_customer_volume=" << msg.fields.bid_customer_volume.get().value()
       << ",quote_condition=\"" << xdp_complexfeed::quote_condition::to_string(msg.fields.quote_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const complex_trade_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",complex_index=" << msg.fields.complex_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",volume_4=" << msg.fields.volume_4.get().value()
       << ",trade_cond_1=\"" << xdp_complexfeed::trade_cond_1::to_string(msg.fields.trade_cond_1.get().value()) << '"'
       << ",trade_cond_2=\"" << msg.fields.trade_cond_2.get().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const complex_crossing_rfq_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_ns=" << msg.fields.source_ns.get().value()
       << ",complex_index=" << msg.fields.complex_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",side=\"" << xdp_complexfeed::side::to_string(msg.fields.side.get().value()) << '"'
       << ",volume_2=" << msg.fields.volume_2.get().value()
       << ",price=" << msg.fields.price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const complex_cube_rfq_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_ns=" << msg.fields.source_ns.get().value()
       << ",complex_index=" << msg.fields.complex_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",side=\"" << xdp_complexfeed::side::to_string(msg.fields.side.get().value()) << '"'
       << ",volume_2=" << msg.fields.volume_2.get().value()
       << ",price=" << msg.fields.price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const complex_status_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",complex_index=" << msg.fields.complex_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",security_status=\"" << xdp_complexfeed::security_status::to_string(msg.fields.security_status.get().value()) << '"'
       << ",halt_condition=\"" << msg.fields.halt_condition.get().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const refresh_complex_quote_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",complex_index=" << msg.fields.complex_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",ask_price=" << msg.fields.ask_price.get().value()
       << ",bid_price=" << msg.fields.bid_price.get().value()
       << ",ask_volume=" << msg.fields.ask_volume.get().value()
       << ",bid_volume=" << msg.fields.bid_volume.get().value()
       << ",ask_customer_volume=" << msg.fields.ask_customer_volume.get().value()
       << ",bid_customer_volume=" << msg.fields.bid_customer_volume.get().value()
       << ",quote_condition=\"" << xdp_complexfeed::quote_condition::to_string(msg.fields.quote_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const refresh_complex_trade_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",complex_index=" << msg.fields.complex_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",volume_4=" << msg.fields.volume_4.get().value()
       << ",trade_cond_1=\"" << xdp_complexfeed::trade_cond_1::to_string(msg.fields.trade_cond_1.get().value()) << '"'
       << ",trade_cond_2=\"" << msg.fields.trade_cond_2.get().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const complex_symbol_definition_message& msg) {
    os << "complex_index=" << msg.fields.complex_index.get().value()
       << ",complex_symbol=\"" << msg.fields.complex_symbol.get_trimmed().value() << '"'
       << ",channel_id=" << static_cast<unsigned>(msg.fields.channel_id.get().value())
       << ",market_id=\"" << xdp_complexfeed::market_id::to_string(msg.fields.market_id.get().value()) << '"'
       << ",system_id=" << static_cast<unsigned>(msg.fields.system_id.get().value())
       << ",stream_id=" << msg.fields.stream_id.get().value()
       << ",no_of_legs=" << msg.fields.no_of_legs.get().value()
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const stream_id_message& msg) {
    os << "stream_id=" << msg.fields.stream_id.get().value()
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

}
