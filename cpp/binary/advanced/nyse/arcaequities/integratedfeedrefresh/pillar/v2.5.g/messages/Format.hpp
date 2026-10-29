#pragma once

#include <ostream>
#include <string_view>

#include "SequenceNumberResetMessage.hpp"
#include "SourceTimeReferenceMessage.hpp"
#include "SymbolIndexMappingMessage.hpp"
#include "SecurityStatusMessage.hpp"
#include "RefreshHeaderMessage.hpp"
#include "ImbalanceMessage.hpp"
#include "AddOrderRefreshMessage.hpp"

namespace nyse::arcaequities::integratedfeedrefresh::pillar::v2_5_g {

namespace pillar_integratedfeedrefresh = ::nyse::arcaequities::integratedfeedrefresh::pillar::v2_5_g;

inline std::ostream& operator<<(std::ostream& os, const packet_header& value) {
    os << "pkt_size=" << value.pkt_size.get().value()
       << ",delivery_flag=\"" << pillar_integratedfeedrefresh::delivery_flag::to_string(value.delivery_flag.get().value()) << '"'
       << ",number_msgs=" << static_cast<unsigned>(value.number_msgs.get().value())
       << ",seq_num=" << value.seq_num.get().value()
       << ",send_time.seconds=" << value.send_time.seconds.get().value()
       << ",send_time.nanoseconds=" << value.send_time.nanoseconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "message_size=" << value.message_size.get().value()
       << ",message_type=\"" << pillar_integratedfeedrefresh::message_type::to_string(value.message_type.get().value()) << '"'
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
       << ",market_id=\"" << pillar_integratedfeedrefresh::market_id::to_string(msg.fields.market_id.get().value()) << '"'
       << ",system_id=" << static_cast<unsigned>(msg.fields.system_id.get().value())
       << ",exchange_code=\"" << pillar_integratedfeedrefresh::exchange_code::to_string(msg.fields.exchange_code.get().value()) << '"'
       << ",price_scale_code=" << static_cast<unsigned>(msg.fields.price_scale_code.get().value())
       << ",security_type=\"" << pillar_integratedfeedrefresh::security_type::to_string(msg.fields.security_type.get().value()) << '"'
       << ",lot_size=" << msg.fields.lot_size.get().value()
       << ",prev_close_price=" << msg.fields.prev_close_price.get().value()
       << ",prev_close_volume=" << msg.fields.prev_close_volume.get().value()
       << ",price_resolution=\"" << pillar_integratedfeedrefresh::price_resolution::to_string(msg.fields.price_resolution.get().value()) << '"'
       << ",round_lot=\"" << pillar_integratedfeedrefresh::round_lot::to_string(msg.fields.round_lot.get().value()) << '"'
       << ",mpv=" << msg.fields.mpv.get().value()
       << ",unit_of_trade=" << msg.fields.unit_of_trade.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const security_status_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",security_status=\"" << pillar_integratedfeedrefresh::security_status::to_string(msg.fields.security_status.get().value()) << '"'
       << ",halt_condition=\"" << pillar_integratedfeedrefresh::halt_condition::to_string(msg.fields.halt_condition.get().value()) << '"'
       << ",price_1=" << msg.fields.price_1.get().value()
       << ",price_2=" << msg.fields.price_2.get().value()
       << ",ssr_triggering_exchange_id=\"" << pillar_integratedfeedrefresh::ssr_triggering_exchange_id::to_string(msg.fields.ssr_triggering_exchange_id.get().value()) << '"'
       << ",ssr_triggering_volume=" << msg.fields.ssr_triggering_volume.get().value()
       << ",time=" << (msg.fields.time.get().has_value() ? std::to_string(msg.fields.time.get().value()) : std::string_view("null"))
       << ",ssr_state=\"" << pillar_integratedfeedrefresh::ssr_state::to_string(msg.fields.ssr_state.get().value()) << '"'
       << ",market_state=\"" << pillar_integratedfeedrefresh::market_state::to_string(msg.fields.market_state.get().value()) << '"'
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
       << ",auction_type=\"" << pillar_integratedfeedrefresh::auction_type::to_string(msg.fields.auction_type.get().value()) << '"'
       << ",imbalance_side=\"" << pillar_integratedfeedrefresh::imbalance_side::to_string(msg.fields.imbalance_side.get().value()) << '"'
       << ",continuous_book_clearing_price=" << msg.fields.continuous_book_clearing_price.get().value()
       << ",auction_interest_clearing_price=" << msg.fields.auction_interest_clearing_price.get().value()
       << ",ssr_filing_price=" << msg.fields.ssr_filing_price.get().value()
       << ",indicative_match_price=" << msg.fields.indicative_match_price.get().value()
       << ",upper_collar=" << msg.fields.upper_collar.get().value()
       << ",lower_collar=" << msg.fields.lower_collar.get().value()
       << ",auction_status=\"" << pillar_integratedfeedrefresh::auction_status::to_string(msg.fields.auction_status.get().value()) << '"'
       << ",freeze_status=\"" << pillar_integratedfeedrefresh::freeze_status::to_string(msg.fields.freeze_status.get().value()) << '"'
       << ",num_extensions=" << static_cast<unsigned>(msg.fields.num_extensions.get().value())
       << ",unpaired_qty=" << msg.fields.unpaired_qty.get().value()
       << ",unpaired_side=\"" << pillar_integratedfeedrefresh::unpaired_side::to_string(msg.fields.unpaired_side.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_order_refresh_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",volume=" << msg.fields.volume.get().value()
       << ",side=\"" << pillar_integratedfeedrefresh::side::to_string(msg.fields.side.get().value()) << '"'
       << ",firm_id=\"" << msg.fields.firm_id.get_trimmed().value() << '"'
       ;
    return os;
}

}
