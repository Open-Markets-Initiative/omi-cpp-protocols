#pragma once

#include <ostream>
#include <string_view>

#include "SequenceNumberResetMessage.hpp"
#include "SymbolIndexMappingMessage.hpp"
#include "RetransmissionRequestMessage.hpp"
#include "RequestResponseMessage.hpp"
#include "HeartbeatResponseMessage.hpp"
#include "SymbolIndexMappingRequestMessage.hpp"
#include "RefreshRequestMessage.hpp"
#include "MessageUnavailableMessage.hpp"
#include "SymbolClearMessage.hpp"
#include "SecurityStatusMessage.hpp"
#include "RefreshHeaderMessage.hpp"
#include "ImbalanceMessage.hpp"

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_1_f {

namespace xdp_imbalancesfeed = ::nyse::nyseequities::imbalancesfeed::xdp::v2_1_f;

inline std::ostream& operator<<(std::ostream& os, const packet_header& value) {
    os << "packet_size=" << value.packet_size.get().value()
       << ",delivery_flag=\"" << xdp_imbalancesfeed::delivery_flag::to_string(value.delivery_flag.get().value()) << '"'
       << ",message_count=" << static_cast<unsigned>(value.message_count.get().value())
       << ",sequence_number=" << value.sequence_number.get().value()
       << ",send_time.seconds=" << value.send_time.seconds.get().value()
       << ",send_time.nanoseconds=" << value.send_time.nanoseconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "message_size=" << value.message_size.get().value()
       << ",message_type=\"" << xdp_imbalancesfeed::message_type::to_string(value.message_type.get().value()) << '"'
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

inline std::ostream& operator<<(std::ostream& os, const symbol_index_mapping_message& msg) {
    os << "symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",market_id=" << msg.fields.market_id.get().value()
       << ",system_id=" << static_cast<unsigned>(msg.fields.system_id.get().value())
       << ",exchange_code=\"" << msg.fields.exchange_code.get().value() << '"'
       << ",price_scale_code=" << static_cast<unsigned>(msg.fields.price_scale_code.get().value())
       << ",security_type=\"" << msg.fields.security_type.get().value() << '"'
       << ",lot_size=" << msg.fields.lot_size.get().value()
       << ",prev_close_price=" << msg.fields.prev_close_price.get().value()
       << ",prev_close_volume=" << msg.fields.prev_close_volume.get().value()
       << ",price_resolution=" << static_cast<unsigned>(msg.fields.price_resolution.get().value())
       << ",round_lot=\"" << msg.fields.round_lot.get().value() << '"'
       << ",mpv=" << msg.fields.mpv.get().value()
       << ",unit_of_trade=" << msg.fields.unit_of_trade.get().value()
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

inline std::ostream& operator<<(std::ostream& os, const request_response_message& msg) {
    os << "request_seq_num=" << msg.fields.request_seq_num.get().value()
       << ",begin_seq_num=" << msg.fields.begin_seq_num.get().value()
       << ",end_seq_num=" << msg.fields.end_seq_num.get().value()
       << ",source_id=\"" << msg.fields.source_id.get_trimmed().value() << '"'
       << ",product_id=" << static_cast<unsigned>(msg.fields.product_id.get().value())
       << ",channel_id=" << static_cast<unsigned>(msg.fields.channel_id.get().value())
       << ",status=\"" << msg.fields.status.get().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const heartbeat_response_message& msg) {
    os << "source_id=\"" << msg.fields.source_id.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const symbol_index_mapping_request_message& msg) {
    os << "symbol_index=" << msg.fields.symbol_index.get().value()
       << ",source_id=\"" << msg.fields.source_id.get_trimmed().value() << '"'
       << ",product_id=" << static_cast<unsigned>(msg.fields.product_id.get().value())
       << ",channel_id=" << static_cast<unsigned>(msg.fields.channel_id.get().value())
       << ",retransmit_method=" << static_cast<unsigned>(msg.fields.retransmit_method.get().value())
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
       << ",security_status=\"" << msg.fields.security_status.get().value() << '"'
       << ",halt_condition=\"" << msg.fields.halt_condition.get().value() << '"'
       << ",price_1=" << msg.fields.price_1.get().value()
       << ",price_2=" << msg.fields.price_2.get().value()
       << ",ssr_triggering_exchange_id=\"" << msg.fields.ssr_triggering_exchange_id.get().value() << '"'
       << ",ssr_triggering_volume=" << msg.fields.ssr_triggering_volume.get().value()
       << ",time=" << (msg.fields.time.get().has_value() ? std::to_string(msg.fields.time.get().value()) : std::string_view("null"))
       << ",ssr_state=\"" << msg.fields.ssr_state.get().value() << '"'
       << ",market_state=\"" << msg.fields.market_state.get().value() << '"'
       << ",session_state=\"" << msg.fields.session_state.get().value() << '"'
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

inline std::ostream& operator<<(std::ostream& os, const imbalance_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",reference_price=" << msg.fields.reference_price.get().value()
       << ",paired_qty=" << msg.fields.paired_qty.get().value()
       << ",total_imbalance_qty=" << msg.fields.total_imbalance_qty.get().value()
       << ",market_imbalance_qty=" << msg.fields.market_imbalance_qty.get().value()
       << ",auction_time=" << msg.fields.auction_time.get().value()
       << ",auction_type=\"" << xdp_imbalancesfeed::auction_type::to_string(msg.fields.auction_type.get().value()) << '"'
       << ",imbalance_side=\"" << xdp_imbalancesfeed::imbalance_side::to_string(msg.fields.imbalance_side.get().value()) << '"'
       << ",continuous_book_clearing_price=" << msg.fields.continuous_book_clearing_price.get().value()
       << ",closing_only_clearing_price=" << msg.fields.closing_only_clearing_price.get().value()
       << ",ssr_filing_price=" << msg.fields.ssr_filing_price.get().value()
       << ",indicative_match_price=" << msg.fields.indicative_match_price.get().value()
       << ",upper_collar=" << msg.fields.upper_collar.get().value()
       << ",lower_collar=" << msg.fields.lower_collar.get().value()
       << ",auction_status=\"" << xdp_imbalancesfeed::auction_status::to_string(msg.fields.auction_status.get().value()) << '"'
       << ",freeze_status=\"" << xdp_imbalancesfeed::freeze_status::to_string(msg.fields.freeze_status.get().value()) << '"'
       << ",num_extensions=" << static_cast<unsigned>(msg.fields.num_extensions.get().value())
       ;
    return os;
}

}
