#pragma once

#include <ostream>
#include <string_view>

#include "SequenceNumberResetMessage.hpp"
#include "SourceTimeReferenceMessage.hpp"
#include "SymbolIndexMappingMessage.hpp"
#include "SymbolClearMessage.hpp"
#include "SecurityStatusMessage.hpp"
#include "RetransmissionRequestMessage.hpp"
#include "SymbolIndexMappingRequestMessage.hpp"
#include "RefreshRequestMessage.hpp"
#include "MessageUnavailableMessage.hpp"
#include "RefreshHeaderMessage.hpp"
#include "RequestResponseMessage.hpp"
#include "HeartbeatResponseMessage.hpp"
#include "TradeMessage.hpp"
#include "TradeCancelMessage.hpp"
#include "TradeCorrectionMessage.hpp"
#include "StockSummaryMessage.hpp"
#include "TrfFractionalTradeMessage.hpp"
#include "TrfTradeCancelMessage.hpp"
#include "TrfFractionalTradeCorrectionMessage.hpp"
#include "TrfFractionalPriorDayTradeMessage.hpp"
#include "TrfFractionalPriorDayTradeCancelMessage.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

namespace pillar_trades = ::nyse::nationalequities::trades::pillar::v2_6;

inline std::ostream& operator<<(std::ostream& os, const packet_header& value) {
    os << "pkt_size=" << value.pkt_size.get().value()
       << ",delivery_flag=\"" << pillar_trades::delivery_flag::to_string(value.delivery_flag.get().value()) << '"'
       << ",number_msgs=" << static_cast<unsigned>(value.number_msgs.get().value())
       << ",seq_num=" << value.seq_num.get().value()
       << ",send_time.seconds=" << value.send_time.seconds.get().value()
       << ",send_time.nanoseconds=" << value.send_time.nanoseconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "message_size=" << value.message_size.get().value()
       << ",message_type=\"" << pillar_trades::message_type::to_string(value.message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const send_time& value) {
    os << "seconds=" << value.seconds.get().value()
       << ",nanoseconds=" << value.nanoseconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const full_refresh_header& value) {
    os << "last_seq_num=" << value.last_seq_num.get().value()
       << ",last_symbol_seq_num=" << value.last_symbol_seq_num.get().value()
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
       << ",market_id=\"" << pillar_trades::market_id::to_string(msg.fields.market_id.get().value()) << '"'
       << ",system_id=" << static_cast<unsigned>(msg.fields.system_id.get().value())
       << ",exchange_code=\"" << pillar_trades::exchange_code::to_string(msg.fields.exchange_code.get().value()) << '"'
       << ",price_scale_code=" << static_cast<unsigned>(msg.fields.price_scale_code.get().value())
       << ",security_type=\"" << pillar_trades::security_type::to_string(msg.fields.security_type.get().value()) << '"'
       << ",lot_size=" << msg.fields.lot_size.get().value()
       << ",prev_close_price=" << msg.fields.prev_close_price.get().value()
       << ",prev_close_volume=" << msg.fields.prev_close_volume.get().value()
       << ",price_resolution=\"" << pillar_trades::price_resolution::to_string(msg.fields.price_resolution.get().value()) << '"'
       << ",round_lot=\"" << pillar_trades::round_lot::to_string(msg.fields.round_lot.get().value()) << '"'
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
       << ",security_status=\"" << pillar_trades::security_status::to_string(msg.fields.security_status.get().value()) << '"'
       << ",halt_condition=\"" << pillar_trades::halt_condition::to_string(msg.fields.halt_condition.get().value()) << '"'
       << ",price_1=" << msg.fields.price_1.get().value()
       << ",price_2=" << msg.fields.price_2.get().value()
       << ",ssr_triggering_exchange_id=\"" << pillar_trades::ssr_triggering_exchange_id::to_string(msg.fields.ssr_triggering_exchange_id.get().value()) << '"'
       << ",ssr_triggering_volume=" << msg.fields.ssr_triggering_volume.get().value()
       << ",time=" << (msg.fields.time.get().has_value() ? std::to_string(msg.fields.time.get().value()) : std::string_view("null"))
       << ",ssr_state=\"" << pillar_trades::ssr_state::to_string(msg.fields.ssr_state.get().value()) << '"'
       << ",market_state=\"" << pillar_trades::market_state::to_string(msg.fields.market_state.get().value()) << '"'
       << ",session_state=\"" << msg.fields.session_state.get().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const retransmission_request_message& msg) {
    os << "begin_seq_num=" << msg.fields.begin_seq_num.get().value()
       << ",end_seq_num=" << msg.fields.end_seq_num.get().value()
       << ",source_id=\"" << msg.fields.source_id.get_trimmed().value() << '"'
       << ",product_id=" << static_cast<unsigned>(msg.fields.product_id.get().value())
       << ",channel_id=" << static_cast<unsigned>(msg.fields.channel_id.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const symbol_index_mapping_request_message& msg) {
    os << "symbol_index=" << msg.fields.symbol_index.get().value()
       << ",source_id=\"" << msg.fields.source_id.get_trimmed().value() << '"'
       << ",product_id=" << static_cast<unsigned>(msg.fields.product_id.get().value())
       << ",channel_id=" << static_cast<unsigned>(msg.fields.channel_id.get().value())
       << ",retransmit_method=\"" << pillar_trades::retransmit_method::to_string(msg.fields.retransmit_method.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const refresh_request_message& msg) {
    os << "symbol_index=" << msg.fields.symbol_index.get().value()
       << ",source_id=\"" << msg.fields.source_id.get_trimmed().value() << '"'
       << ",product_id=" << static_cast<unsigned>(msg.fields.product_id.get().value())
       << ",channel_id=" << static_cast<unsigned>(msg.fields.channel_id.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_unavailable_message& msg) {
    os << "begin_seq_num=" << msg.fields.begin_seq_num.get().value()
       << ",end_seq_num=" << msg.fields.end_seq_num.get().value()
       << ",product_id=" << static_cast<unsigned>(msg.fields.product_id.get().value())
       << ",channel_id=" << static_cast<unsigned>(msg.fields.channel_id.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const refresh_header_message& msg) {
    os << "current_refresh_pkt=" << msg.fields.current_refresh_pkt.get().value()
       << ",total_refresh_pkts=" << msg.fields.total_refresh_pkts.get().value()
       ;
    {
        auto desc = msg.describe_appendages();
        if (desc.has_bid || desc.has_offer) {
            if (desc.has_bid == false && desc.has_offer == false) {
                if (auto* a = msg.full_refresh_header()) os << ",full_refresh_header={" << *a << "}";
            }
        }
    }
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const request_response_message& msg) {
    os << "request_seq_num=" << msg.fields.request_seq_num.get().value()
       << ",begin_seq_num=" << msg.fields.begin_seq_num.get().value()
       << ",end_seq_num=" << msg.fields.end_seq_num.get().value()
       << ",source_id=\"" << msg.fields.source_id.get_trimmed().value() << '"'
       << ",product_id=" << static_cast<unsigned>(msg.fields.product_id.get().value())
       << ",channel_id=" << static_cast<unsigned>(msg.fields.channel_id.get().value())
       << ",status=\"" << pillar_trades::status::to_string(msg.fields.status.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const heartbeat_response_message& msg) {
    os << "source_id=\"" << msg.fields.source_id.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",volume=" << msg.fields.volume.get().value()
       << ",trade_cond_1=\"" << pillar_trades::trade_cond_1::to_string(msg.fields.trade_cond_1.get().value()) << '"'
       << ",trade_cond_2=\"" << pillar_trades::trade_cond_2::to_string(msg.fields.trade_cond_2.get().value()) << '"'
       << ",trade_cond_3=\"" << pillar_trades::trade_cond_3::to_string(msg.fields.trade_cond_3.get().value()) << '"'
       << ",trade_cond_4=\"" << pillar_trades::trade_cond_4::to_string(msg.fields.trade_cond_4.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_cancel_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",original_trade_id=" << msg.fields.original_trade_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_correction_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",original_trade_id=" << msg.fields.original_trade_id.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",volume=" << msg.fields.volume.get().value()
       << ",trade_cond_1=\"" << pillar_trades::trade_cond_1::to_string(msg.fields.trade_cond_1.get().value()) << '"'
       << ",trade_cond_2=\"" << pillar_trades::trade_cond_2::to_string(msg.fields.trade_cond_2.get().value()) << '"'
       << ",trade_cond_3=\"" << pillar_trades::trade_cond_3::to_string(msg.fields.trade_cond_3.get().value()) << '"'
       << ",trade_cond_4=\"" << pillar_trades::trade_cond_4::to_string(msg.fields.trade_cond_4.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const stock_summary_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",high_price=" << msg.fields.high_price.get().value()
       << ",low_price=" << msg.fields.low_price.get().value()
       << ",open=" << msg.fields.open.get().value()
       << ",close=" << msg.fields.close.get().value()
       << ",total_volume=" << msg.fields.total_volume.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trf_fractional_trade_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",fractional_volume=" << msg.fields.fractional_volume.get().value()
       << ",trade_cond_1=\"" << pillar_trades::trade_cond_1::to_string(msg.fields.trade_cond_1.get().value()) << '"'
       << ",trade_cond_2=\"" << pillar_trades::trade_cond_2::to_string(msg.fields.trade_cond_2.get().value()) << '"'
       << ",trade_cond_3=\"" << pillar_trades::trade_cond_3::to_string(msg.fields.trade_cond_3.get().value()) << '"'
       << ",trade_cond_4=\"" << pillar_trades::trade_cond_4::to_string(msg.fields.trade_cond_4.get().value()) << '"'
       << ",exec_day_time=" << msg.fields.exec_day_time.get().value()
       << ",exec_day_time_ns=" << msg.fields.exec_day_time_ns.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trf_trade_cancel_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",original_trade_id=" << msg.fields.original_trade_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trf_fractional_trade_correction_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",original_trade_id=" << msg.fields.original_trade_id.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",fractional_volume=" << msg.fields.fractional_volume.get().value()
       << ",trade_cond_1=\"" << pillar_trades::trade_cond_1::to_string(msg.fields.trade_cond_1.get().value()) << '"'
       << ",trade_cond_2=\"" << pillar_trades::trade_cond_2::to_string(msg.fields.trade_cond_2.get().value()) << '"'
       << ",trade_cond_3=\"" << pillar_trades::trade_cond_3::to_string(msg.fields.trade_cond_3.get().value()) << '"'
       << ",trade_cond_4=\"" << pillar_trades::trade_cond_4::to_string(msg.fields.trade_cond_4.get().value()) << '"'
       << ",exec_day_time=" << msg.fields.exec_day_time.get().value()
       << ",exec_day_time_ns=" << msg.fields.exec_day_time_ns.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trf_fractional_prior_day_trade_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",fractional_volume=" << msg.fields.fractional_volume.get().value()
       << ",trade_cond_1=\"" << pillar_trades::trade_cond_1::to_string(msg.fields.trade_cond_1.get().value()) << '"'
       << ",trade_cond_2=\"" << pillar_trades::trade_cond_2::to_string(msg.fields.trade_cond_2.get().value()) << '"'
       << ",trade_cond_3=\"" << pillar_trades::trade_cond_3::to_string(msg.fields.trade_cond_3.get().value()) << '"'
       << ",trade_cond_4=\"" << pillar_trades::trade_cond_4::to_string(msg.fields.trade_cond_4.get().value()) << '"'
       << ",prior_day_time=" << msg.fields.prior_day_time.get().value()
       << ",prior_day_time_ns=" << msg.fields.prior_day_time_ns.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trf_fractional_prior_day_trade_cancel_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",fractional_volume=" << msg.fields.fractional_volume.get().value()
       << ",prior_day_time=" << msg.fields.prior_day_time.get().value()
       << ",prior_day_time_ns=" << msg.fields.prior_day_time_ns.get().value()
       ;
    return os;
}

}
