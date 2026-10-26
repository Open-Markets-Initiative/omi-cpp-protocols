#pragma once

#include <ostream>
#include <string_view>

#include "SequenceNumberResetMessage.hpp"
#include "SourceTimeReferenceMessage.hpp"
#include "SymbolIndexMappingMessage.hpp"
#include "SymbolClearMessage.hpp"
#include "SecurityStatusMessage.hpp"
#include "OutrightSeriesIndexMappingMessage.hpp"
#include "OptionsStatusMessage.hpp"
#include "ComplexSeriesIndexMappingMessage.hpp"
#include "RetransmissionRequestMessage.hpp"
#include "RefreshHeaderMessage.hpp"
#include "RefreshRequestMessage.hpp"
#include "SymbolIndexMappingRequestMessage.hpp"
#include "MessageUnavailableMessage.hpp"
#include "RequestResponseMessage.hpp"
#include "HeartbeatResponseMessage.hpp"
#include "OptionsAddOrderMessage.hpp"
#include "OptionsModifyOrderMessage.hpp"
#include "OptionsDeleteOrderMessage.hpp"
#include "OptionsOrderExecutionMessage.hpp"
#include "OptionsReplaceOrderMessage.hpp"
#include "OptionsImbalanceMessage.hpp"
#include "OptionsAddOrderRefreshMessage.hpp"
#include "OptionsSeriesRfqMessage.hpp"
#include "OptionsNonDisplayedTradeMessage.hpp"
#include "OptionsCrossTradeMessage.hpp"
#include "OptionsTradeCancelMessage.hpp"
#include "OptionsOutrightSeriesSummaryMessage.hpp"
#include "../json/messages/complex_series_index_mapping_message_json.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

namespace pillar_deepfeed = ::nyse::arcaoptions::deepfeed::pillar::v1_2_m;

inline std::ostream& operator<<(std::ostream& os, const packet_header& value) {
    os << "pkt_size=" << value.pkt_size.get().value()
       << ",delivery_flag=\"" << pillar_deepfeed::delivery_flag::to_string(value.delivery_flag.get().value()) << '"'
       << ",number_msgs=" << static_cast<unsigned>(value.number_msgs.get().value())
       << ",seq_num=" << value.seq_num.get().value()
       << ",send_time.seconds=" << value.send_time.seconds.get().value()
       << ",send_time.nanoseconds=" << value.send_time.nanoseconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "message_size=" << value.message_size.get().value()
       << ",message_type=\"" << pillar_deepfeed::message_type::to_string(value.message_type.get().value()) << '"'
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
       << ",market_id=\"" << pillar_deepfeed::market_id::to_string(msg.fields.market_id.get().value()) << '"'
       << ",system_id=" << static_cast<unsigned>(msg.fields.system_id.get().value())
       << ",exchange_code=\"" << pillar_deepfeed::exchange_code::to_string(msg.fields.exchange_code.get().value()) << '"'
       << ",price_scale_code=\"" << pillar_deepfeed::price_scale_code::to_string(msg.fields.price_scale_code.get().value()) << '"'
       << ",security_type=\"" << pillar_deepfeed::security_type::to_string(msg.fields.security_type.get().value()) << '"'
       << ",lot_size=" << msg.fields.lot_size.get().value()
       << ",prev_close_price=" << msg.fields.prev_close_price.get().value()
       << ",prev_close_volume=" << msg.fields.prev_close_volume.get().value()
       << ",price_resolution=\"" << pillar_deepfeed::price_resolution::to_string(msg.fields.price_resolution.get().value()) << '"'
       << ",round_lot=\"" << pillar_deepfeed::round_lot::to_string(msg.fields.round_lot.get().value()) << '"'
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
       << ",security_status=\"" << pillar_deepfeed::security_status::to_string(msg.fields.security_status.get().value()) << '"'
       << ",halt_condition=\"" << pillar_deepfeed::halt_condition::to_string(msg.fields.halt_condition.get().value()) << '"'
       << ",price_1=" << msg.fields.price_1.get().value()
       << ",price_2=" << msg.fields.price_2.get().value()
       << ",ssr_triggering_exchange_id=\"" << pillar_deepfeed::ssr_triggering_exchange_id::to_string(msg.fields.ssr_triggering_exchange_id.get().value()) << '"'
       << ",ssr_triggering_volume=" << msg.fields.ssr_triggering_volume.get().value()
       << ",time=" << (msg.fields.time.get().has_value() ? std::to_string(msg.fields.time.get().value()) : std::string_view("null"))
       << ",ssr_state=\"" << pillar_deepfeed::ssr_state::to_string(msg.fields.ssr_state.get().value()) << '"'
       << ",market_state=\"" << pillar_deepfeed::market_state::to_string(msg.fields.market_state.get().value()) << '"'
       << ",session_state=\"" << msg.fields.session_state.get().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const outright_series_index_mapping_message& msg) {
    os << "series_index=" << msg.fields.series_index.get().value()
       << ",series_type=\"" << pillar_deepfeed::series_type::to_string(msg.fields.series_type.get().value()) << '"'
       << ",market_id=\"" << pillar_deepfeed::market_id::to_string(msg.fields.market_id.get().value()) << '"'
       << ",system_id=" << static_cast<unsigned>(msg.fields.system_id.get().value())
       << ",option_symbol_root=\"" << msg.fields.option_symbol_root.get_trimmed().value() << '"'
       << ",underlying_symbol=\"" << msg.fields.underlying_symbol.get_trimmed().value() << '"'
       << ",underlying_index=" << msg.fields.underlying_index.get().value()
       << ",price_scale_code=\"" << pillar_deepfeed::price_scale_code::to_string(msg.fields.price_scale_code.get().value()) << '"'
       << ",contract_multiplier=" << msg.fields.contract_multiplier.get().value()
       << ",maturity_date=\"" << msg.fields.maturity_date.get_trimmed().value() << '"'
       << ",put_or_call=\"" << pillar_deepfeed::put_or_call::to_string(msg.fields.put_or_call.get().value()) << '"'
       << ",strike_price=\"" << msg.fields.strike_price.get_trimmed().value() << '"'
       << ",closing_only_indicator=\"" << pillar_deepfeed::closing_only_indicator::to_string(msg.fields.closing_only_indicator.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const options_status_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",series_index=" << msg.fields.series_index.get().value()
       << ",series_seq_num=" << msg.fields.series_seq_num.get().value()
       << ",series_status=\"" << pillar_deepfeed::series_status::to_string(msg.fields.series_status.get().value()) << '"'
       << ",market_state=\"" << pillar_deepfeed::market_state::to_string(msg.fields.market_state.get().value()) << '"'
       << ",options_status_halt_condition=\"" << pillar_deepfeed::options_status_halt_condition::to_string(msg.fields.options_status_halt_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const complex_series_index_mapping_message& msg) {
    os << "series_index=" << msg.fields.series_index.get().value()
       << ",market_id=\"" << pillar_deepfeed::market_id::to_string(msg.fields.market_id.get().value()) << '"'
       << ",system_id=" << static_cast<unsigned>(msg.fields.system_id.get().value())
       << ",no_of_legs=" << msg.fields.no_of_legs.get().value()
       << ",tail=" << json::tail_to_json_string(msg)
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

inline std::ostream& operator<<(std::ostream& os, const refresh_request_message& msg) {
    os << "symbol_index=" << msg.fields.symbol_index.get().value()
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
       << ",retransmit_method=\"" << pillar_deepfeed::retransmit_method::to_string(msg.fields.retransmit_method.get().value()) << '"'
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

inline std::ostream& operator<<(std::ostream& os, const request_response_message& msg) {
    os << "request_seq_num=" << msg.fields.request_seq_num.get().value()
       << ",begin_seq_num=" << msg.fields.begin_seq_num.get().value()
       << ",end_seq_num=" << msg.fields.end_seq_num.get().value()
       << ",source_id=\"" << msg.fields.source_id.get_trimmed().value() << '"'
       << ",product_id=" << static_cast<unsigned>(msg.fields.product_id.get().value())
       << ",channel_id=" << static_cast<unsigned>(msg.fields.channel_id.get().value())
       << ",status=\"" << pillar_deepfeed::status::to_string(msg.fields.status.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const heartbeat_response_message& msg) {
    os << "source_id=\"" << msg.fields.source_id.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const options_add_order_message& msg) {
    os << "source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",series_index=" << msg.fields.series_index.get().value()
       << ",series_seq_num=" << msg.fields.series_seq_num.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",volume=" << msg.fields.volume.get().value()
       << ",side=\"" << pillar_deepfeed::side::to_string(msg.fields.side.get().value()) << '"'
       << ",firm_id=\"" << msg.fields.firm_id.get_trimmed().value() << '"'
       << ",cust_indicator=\"" << pillar_deepfeed::cust_indicator::to_string(msg.fields.cust_indicator.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const options_modify_order_message& msg) {
    os << "source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",series_index=" << msg.fields.series_index.get().value()
       << ",series_seq_num=" << msg.fields.series_seq_num.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",volume=" << msg.fields.volume.get().value()
       << ",position_change=" << static_cast<unsigned>(msg.fields.position_change.get().value())
       << ",side=\"" << pillar_deepfeed::side::to_string(msg.fields.side.get().value()) << '"'
       << ",cust_indicator=\"" << pillar_deepfeed::cust_indicator::to_string(msg.fields.cust_indicator.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const options_delete_order_message& msg) {
    os << "source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",series_index=" << msg.fields.series_index.get().value()
       << ",series_seq_num=" << msg.fields.series_seq_num.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const options_order_execution_message& msg) {
    os << "source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",series_index=" << msg.fields.series_index.get().value()
       << ",series_seq_num=" << msg.fields.series_seq_num.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",volume=" << msg.fields.volume.get().value()
       << ",printable_flag=\"" << pillar_deepfeed::printable_flag::to_string(msg.fields.printable_flag.get().value()) << '"'
       << ",trade_cond_1=\"" << pillar_deepfeed::trade_cond_1::to_string(msg.fields.trade_cond_1.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const options_replace_order_message& msg) {
    os << "source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",series_index=" << msg.fields.series_index.get().value()
       << ",series_seq_num=" << msg.fields.series_seq_num.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",new_order_id=" << msg.fields.new_order_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",volume=" << msg.fields.volume.get().value()
       << ",side=\"" << pillar_deepfeed::side::to_string(msg.fields.side.get().value()) << '"'
       << ",cust_indicator=\"" << pillar_deepfeed::cust_indicator::to_string(msg.fields.cust_indicator.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const options_imbalance_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",series_index=" << msg.fields.series_index.get().value()
       << ",series_seq_num=" << msg.fields.series_seq_num.get().value()
       << ",paired_qty=" << msg.fields.paired_qty.get().value()
       << ",total_imbalance_qty=" << msg.fields.total_imbalance_qty.get().value()
       << ",market_imbalance_qty=" << msg.fields.market_imbalance_qty.get().value()
       << ",auction_type=\"" << pillar_deepfeed::auction_type::to_string(msg.fields.auction_type.get().value()) << '"'
       << ",imbalance_side=\"" << pillar_deepfeed::imbalance_side::to_string(msg.fields.imbalance_side.get().value()) << '"'
       << ",continuous_book_clearing_price=" << msg.fields.continuous_book_clearing_price.get().value()
       << ",auction_interest_clearing_price=" << msg.fields.auction_interest_clearing_price.get().value()
       << ",indicative_match_price=" << msg.fields.indicative_match_price.get().value()
       << ",upper_collar=" << msg.fields.upper_collar.get().value()
       << ",lower_collar=" << msg.fields.lower_collar.get().value()
       << ",auction_status=\"" << pillar_deepfeed::auction_status::to_string(msg.fields.auction_status.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const options_add_order_refresh_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",series_index=" << msg.fields.series_index.get().value()
       << ",series_seq_num=" << msg.fields.series_seq_num.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",volume=" << msg.fields.volume.get().value()
       << ",side=\"" << pillar_deepfeed::side::to_string(msg.fields.side.get().value()) << '"'
       << ",firm_id=\"" << msg.fields.firm_id.get_trimmed().value() << '"'
       << ",cust_indicator=\"" << pillar_deepfeed::cust_indicator::to_string(msg.fields.cust_indicator.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const options_series_rfq_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",series_index=" << msg.fields.series_index.get().value()
       << ",series_seq_num=" << msg.fields.series_seq_num.get().value()
       << ",rfq_side=\"" << pillar_deepfeed::rfq_side::to_string(msg.fields.rfq_side.get().value()) << '"'
       << ",type=\"" << pillar_deepfeed::type::to_string(msg.fields.type.get().value()) << '"'
       << ",capacity=\"" << pillar_deepfeed::capacity::to_string(msg.fields.capacity.get().value()) << '"'
       << ",total_quantity=" << msg.fields.total_quantity.get().value()
       << ",working_price=" << msg.fields.working_price.get().value()
       << ",participant=" << msg.fields.participant.get().value()
       << ",auction_id=" << msg.fields.auction_id.get().value()
       << ",rfq_status=\"" << pillar_deepfeed::rfq_status::to_string(msg.fields.rfq_status.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const options_non_displayed_trade_message& msg) {
    os << "source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",series_index=" << msg.fields.series_index.get().value()
       << ",series_seq_num=" << msg.fields.series_seq_num.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",volume=" << msg.fields.volume.get().value()
       << ",printable_flag=\"" << pillar_deepfeed::printable_flag::to_string(msg.fields.printable_flag.get().value()) << '"'
       << ",non_displayed_trade_trade_cond_1=\"" << pillar_deepfeed::non_displayed_trade_trade_cond_1::to_string(msg.fields.non_displayed_trade_trade_cond_1.get().value()) << '"'
       << ",price_type=\"" << pillar_deepfeed::price_type::to_string(msg.fields.price_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const options_cross_trade_message& msg) {
    os << "source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",series_index=" << msg.fields.series_index.get().value()
       << ",series_seq_num=" << msg.fields.series_seq_num.get().value()
       << ",cross_id=" << msg.fields.cross_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",volume=" << msg.fields.volume.get().value()
       << ",cross_type=\"" << pillar_deepfeed::cross_type::to_string(msg.fields.cross_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const options_trade_cancel_message& msg) {
    os << "source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",series_index=" << msg.fields.series_index.get().value()
       << ",series_seq_num=" << msg.fields.series_seq_num.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const options_outright_series_summary_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",series_index=" << msg.fields.series_index.get().value()
       << ",high_price=" << msg.fields.high_price.get().value()
       << ",low_price=" << msg.fields.low_price.get().value()
       << ",open=" << msg.fields.open.get().value()
       << ",close=" << msg.fields.close.get().value()
       << ",total_volume=" << msg.fields.total_volume.get().value()
       ;
    return os;
}

}
