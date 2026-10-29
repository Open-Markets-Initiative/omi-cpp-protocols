#pragma once

#include <ostream>
#include <string_view>

#include "SequenceNumberResetMessage.hpp"
#include "SourceTimeReferenceMessage.hpp"
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
#include "AddOrderMessage.hpp"
#include "ModifyOrderMessage.hpp"
#include "ReplaceOrderMessage.hpp"
#include "DeleteOrderMessage.hpp"
#include "TradeCancelMessage.hpp"
#include "CrossTradeMessage.hpp"
#include "CrossCorrectionMessage.hpp"
#include "RetailPriceImprovementMessage.hpp"
#include "AddOrderRefreshMessage.hpp"
#include "ImbalanceMessage.hpp"
#include "OrderExecutionMessage.hpp"
#include "NonDisplayedTradeMessage.hpp"
#include "StockSummaryMessage.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

namespace xdp_integratedfeed = ::nyse::nyseequities::integratedfeed::xdp::v2_1_g;

inline std::ostream& operator<<(std::ostream& os, const packet_header& value) {
    os << "packet_size=" << value.packet_size.get().value()
       << ",delivery_flag=\"" << xdp_integratedfeed::delivery_flag::to_string(value.delivery_flag.get().value()) << '"'
       << ",message_count=" << static_cast<unsigned>(value.message_count.get().value())
       << ",sequence_number=" << value.sequence_number.get().value()
       << ",send_time.seconds=" << value.send_time.seconds.get().value()
       << ",send_time.nanoseconds=" << value.send_time.nanoseconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "message_size=" << value.message_size.get().value()
       << ",message_type=\"" << xdp_integratedfeed::message_type::to_string(value.message_type.get().value()) << '"'
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
       << ",market_id=\"" << xdp_integratedfeed::market_id::to_string(msg.fields.market_id.get().value()) << '"'
       << ",system_id=" << static_cast<unsigned>(msg.fields.system_id.get().value())
       << ",exchange_code=\"" << xdp_integratedfeed::exchange_code::to_string(msg.fields.exchange_code.get().value()) << '"'
       << ",price_scale_code=" << static_cast<unsigned>(msg.fields.price_scale_code.get().value())
       << ",security_type=\"" << xdp_integratedfeed::security_type::to_string(msg.fields.security_type.get().value()) << '"'
       << ",lot_size=" << msg.fields.lot_size.get().value()
       << ",prev_close_price=" << msg.fields.prev_close_price.get().value()
       << ",prev_close_volume=" << msg.fields.prev_close_volume.get().value()
       << ",price_resolution=\"" << xdp_integratedfeed::price_resolution::to_string(msg.fields.price_resolution.get().value()) << '"'
       << ",round_lot=\"" << xdp_integratedfeed::round_lot::to_string(msg.fields.round_lot.get().value()) << '"'
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
       << ",status=\"" << xdp_integratedfeed::status::to_string(msg.fields.status.get().value()) << '"'
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
       << ",retransmit_method=\"" << xdp_integratedfeed::retransmit_method::to_string(msg.fields.retransmit_method.get().value()) << '"'
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
       << ",security_status=\"" << xdp_integratedfeed::security_status::to_string(msg.fields.security_status.get().value()) << '"'
       << ",halt_condition=\"" << xdp_integratedfeed::halt_condition::to_string(msg.fields.halt_condition.get().value()) << '"'
       << ",price_1=" << msg.fields.price_1.get().value()
       << ",price_2=" << msg.fields.price_2.get().value()
       << ",ssr_triggering_exchange_id=\"" << xdp_integratedfeed::ssr_triggering_exchange_id::to_string(msg.fields.ssr_triggering_exchange_id.get().value()) << '"'
       << ",ssr_triggering_volume=" << msg.fields.ssr_triggering_volume.get().value()
       << ",time=" << (msg.fields.time.get().has_value() ? std::to_string(msg.fields.time.get().value()) : std::string_view("null"))
       << ",ssr_state=\"" << xdp_integratedfeed::ssr_state::to_string(msg.fields.ssr_state.get().value()) << '"'
       << ",market_state=\"" << xdp_integratedfeed::market_state::to_string(msg.fields.market_state.get().value()) << '"'
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

inline std::ostream& operator<<(std::ostream& os, const add_order_message& msg) {
    os << "source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",volume=" << msg.fields.volume.get().value()
       << ",side=\"" << xdp_integratedfeed::side::to_string(msg.fields.side.get().value()) << '"'
       << ",firm_id=\"" << msg.fields.firm_id.get_trimmed().value() << '"'
       << ",num_parity_splits=" << static_cast<unsigned>(msg.fields.num_parity_splits.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const modify_order_message& msg) {
    os << "source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",volume=" << msg.fields.volume.get().value()
       << ",position_change=\"" << xdp_integratedfeed::position_change::to_string(msg.fields.position_change.get().value()) << '"'
       << ",prev_price_parity_splits=" << static_cast<unsigned>(msg.fields.prev_price_parity_splits.get().value())
       << ",new_price_parity_splits=" << static_cast<unsigned>(msg.fields.new_price_parity_splits.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const replace_order_message& msg) {
    os << "source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",new_order_id=" << msg.fields.new_order_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",volume=" << msg.fields.volume.get().value()
       << ",prev_price_parity_splits=" << static_cast<unsigned>(msg.fields.prev_price_parity_splits.get().value())
       << ",new_price_parity_splits=" << static_cast<unsigned>(msg.fields.new_price_parity_splits.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const delete_order_message& msg) {
    os << "source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",num_parity_splits=" << static_cast<unsigned>(msg.fields.num_parity_splits.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_cancel_message& msg) {
    os << "source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const cross_trade_message& msg) {
    os << "source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",cross_id=" << msg.fields.cross_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",volume=" << msg.fields.volume.get().value()
       << ",cross_type=\"" << xdp_integratedfeed::cross_type::to_string(msg.fields.cross_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const cross_correction_message& msg) {
    os << "source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",cross_id=" << msg.fields.cross_id.get().value()
       << ",volume=" << msg.fields.volume.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const retail_price_improvement_message& msg) {
    os << "source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",rpi_indicator=\"" << xdp_integratedfeed::rpi_indicator::to_string(msg.fields.rpi_indicator.get().value()) << '"'
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
       << ",side=\"" << xdp_integratedfeed::side::to_string(msg.fields.side.get().value()) << '"'
       << ",firm_id=\"" << msg.fields.firm_id.get_trimmed().value() << '"'
       << ",num_parity_splits=" << static_cast<unsigned>(msg.fields.num_parity_splits.get().value())
       ;
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
       << ",auction_type=\"" << xdp_integratedfeed::auction_type::to_string(msg.fields.auction_type.get().value()) << '"'
       << ",imbalance_side=\"" << xdp_integratedfeed::imbalance_side::to_string(msg.fields.imbalance_side.get().value()) << '"'
       << ",continuous_book_clearing_price=" << msg.fields.continuous_book_clearing_price.get().value()
       << ",closing_only_clearing_price=" << msg.fields.closing_only_clearing_price.get().value()
       << ",ssr_filing_price=" << msg.fields.ssr_filing_price.get().value()
       << ",indicative_match_price=" << msg.fields.indicative_match_price.get().value()
       << ",upper_collar=" << msg.fields.upper_collar.get().value()
       << ",lower_collar=" << msg.fields.lower_collar.get().value()
       << ",auction_status=\"" << xdp_integratedfeed::auction_status::to_string(msg.fields.auction_status.get().value()) << '"'
       << ",freeze_status=\"" << xdp_integratedfeed::freeze_status::to_string(msg.fields.freeze_status.get().value()) << '"'
       << ",num_extensions=" << static_cast<unsigned>(msg.fields.num_extensions.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_execution_message& msg) {
    os << "source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",volume=" << msg.fields.volume.get().value()
       << ",printable_flag=\"" << xdp_integratedfeed::printable_flag::to_string(msg.fields.printable_flag.get().value()) << '"'
       << ",num_parity_splits=" << static_cast<unsigned>(msg.fields.num_parity_splits.get().value())
       << ",db_exec_id=" << msg.fields.db_exec_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const non_displayed_trade_message& msg) {
    os << "source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",symbol_index=" << msg.fields.symbol_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",volume=" << msg.fields.volume.get().value()
       << ",printable_flag=\"" << xdp_integratedfeed::printable_flag::to_string(msg.fields.printable_flag.get().value()) << '"'
       << ",db_exec_id=" << msg.fields.db_exec_id.get().value()
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

}
