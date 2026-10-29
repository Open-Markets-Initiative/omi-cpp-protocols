#pragma once

#include <ostream>
#include <string_view>

#include "OutrightMarketDepthBuyMessage.hpp"
#include "OutrightMarketDepthSellMessage.hpp"
#include "UnderlyingStatusMessage.hpp"
#include "OutrightSeriesStatusMessage.hpp"
#include "RefreshOutrightMarketDepthBuyMessage.hpp"
#include "RefreshOutrightMarketDepthSellMessage.hpp"
#include "UnderlyingIndexMappingMessage.hpp"
#include "SeriesIndexMappingMessage.hpp"
#include "StreamIdMessage.hpp"
#include "SequenceNumberResetMessage.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

namespace xdp_deepfeed = ::nyse::amexoptions::deepfeed::xdp::v1_3_a;

inline std::ostream& operator<<(std::ostream& os, const packet_header& value) {
    os << "packet_size=" << value.packet_size.get().value()
       << ",delivery_flag=\"" << xdp_deepfeed::delivery_flag::to_string(value.delivery_flag.get().value()) << '"'
       << ",message_count=" << static_cast<unsigned>(value.message_count.get().value())
       << ",sequence_number=" << value.sequence_number.get().value()
       << ",send_time.seconds=" << value.send_time.seconds.get().value()
       << ",send_time.nanoseconds=" << value.send_time.nanoseconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "message_size=" << value.message_size.get().value()
       << ",message_type=\"" << xdp_deepfeed::message_type::to_string(value.message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const send_time& value) {
    os << "seconds=" << value.seconds.get().value()
       << ",nanoseconds=" << value.nanoseconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const outright_market_depth_buy_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_ns=" << msg.fields.source_ns.get().value()
       << ",series_index=" << msg.fields.series_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",first_level_price=" << msg.fields.first_level_price.get().value()
       << ",second_level_price=" << msg.fields.second_level_price.get().value()
       << ",third_level_price=" << msg.fields.third_level_price.get().value()
       << ",first_level_volume=" << msg.fields.first_level_volume.get().value()
       << ",second_level_volume=" << msg.fields.second_level_volume.get().value()
       << ",third_level_volume=" << msg.fields.third_level_volume.get().value()
       << ",quote_condition=\"" << xdp_deepfeed::quote_condition::to_string(msg.fields.quote_condition.get().value()) << '"'
       << ",first_level_customer_volume=" << msg.fields.first_level_customer_volume.get().value()
       << ",second_level_customer_volume=" << msg.fields.second_level_customer_volume.get().value()
       << ",third_level_customer_volume=" << msg.fields.third_level_customer_volume.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const outright_market_depth_sell_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_ns=" << msg.fields.source_ns.get().value()
       << ",series_index=" << msg.fields.series_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",first_level_price=" << msg.fields.first_level_price.get().value()
       << ",second_level_price=" << msg.fields.second_level_price.get().value()
       << ",third_level_price=" << msg.fields.third_level_price.get().value()
       << ",first_volume=" << msg.fields.first_volume.get().value()
       << ",second_volume=" << msg.fields.second_volume.get().value()
       << ",third_volume=" << msg.fields.third_volume.get().value()
       << ",quote_condition=\"" << xdp_deepfeed::quote_condition::to_string(msg.fields.quote_condition.get().value()) << '"'
       << ",first_level_customer_volume=" << msg.fields.first_level_customer_volume.get().value()
       << ",second_level_customer_volume=" << msg.fields.second_level_customer_volume.get().value()
       << ",third_level_customer_volume=" << msg.fields.third_level_customer_volume.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const underlying_status_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",underlying_index=" << msg.fields.underlying_index.get().value()
       << ",underlying_seq_num=" << msg.fields.underlying_seq_num.get().value()
       << ",security_status=\"" << xdp_deepfeed::security_status::to_string(msg.fields.security_status.get().value()) << '"'
       << ",halt_condition=\"" << msg.fields.halt_condition.get().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const outright_series_status_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",series_index=" << msg.fields.series_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",security_status=\"" << xdp_deepfeed::security_status::to_string(msg.fields.security_status.get().value()) << '"'
       << ",halt_condition=\"" << msg.fields.halt_condition.get().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const refresh_outright_market_depth_buy_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_ns=" << msg.fields.source_ns.get().value()
       << ",series_index=" << msg.fields.series_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",first_level_price=" << msg.fields.first_level_price.get().value()
       << ",second_level_price=" << msg.fields.second_level_price.get().value()
       << ",third_level_price=" << msg.fields.third_level_price.get().value()
       << ",first_volume=" << msg.fields.first_volume.get().value()
       << ",second_volume=" << msg.fields.second_volume.get().value()
       << ",third_volume=" << msg.fields.third_volume.get().value()
       << ",quote_condition=\"" << xdp_deepfeed::quote_condition::to_string(msg.fields.quote_condition.get().value()) << '"'
       << ",first_level_customer_volume=" << msg.fields.first_level_customer_volume.get().value()
       << ",second_level_customer_volume=" << msg.fields.second_level_customer_volume.get().value()
       << ",third_level_customer_volume=" << msg.fields.third_level_customer_volume.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const refresh_outright_market_depth_sell_message& msg) {
    os << "source_time=" << msg.fields.source_time.get().value()
       << ",source_time_ns=" << msg.fields.source_time_ns.get().value()
       << ",series_index=" << msg.fields.series_index.get().value()
       << ",symbol_seq_num=" << msg.fields.symbol_seq_num.get().value()
       << ",first_level_price=" << msg.fields.first_level_price.get().value()
       << ",second_level_price=" << msg.fields.second_level_price.get().value()
       << ",third_level_price=" << msg.fields.third_level_price.get().value()
       << ",first_volume=" << msg.fields.first_volume.get().value()
       << ",second_volume=" << msg.fields.second_volume.get().value()
       << ",third_volume=" << msg.fields.third_volume.get().value()
       << ",quote_condition=\"" << xdp_deepfeed::quote_condition::to_string(msg.fields.quote_condition.get().value()) << '"'
       << ",first_level_customer_volume=" << msg.fields.first_level_customer_volume.get().value()
       << ",second_level_customer_volume=" << msg.fields.second_level_customer_volume.get().value()
       << ",third_level_customer_volume=" << msg.fields.third_level_customer_volume.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const underlying_index_mapping_message& msg) {
    os << "underlying_index=" << msg.fields.underlying_index.get().value()
       << ",underlying_symbol=\"" << msg.fields.underlying_symbol.get_trimmed().value() << '"'
       << ",channel_id=" << static_cast<unsigned>(msg.fields.channel_id.get().value())
       << ",market_id=\"" << xdp_deepfeed::market_id::to_string(msg.fields.market_id.get().value()) << '"'
       << ",system_id=" << static_cast<unsigned>(msg.fields.system_id.get().value())
       << ",exchange_code=\"" << xdp_deepfeed::exchange_code::to_string(msg.fields.exchange_code.get().value()) << '"'
       << ",price_scale_code=" << static_cast<unsigned>(msg.fields.price_scale_code.get().value())
       << ",security_type=\"" << xdp_deepfeed::security_type::to_string(msg.fields.security_type.get().value()) << '"'
       << ",price_resolution=\"" << xdp_deepfeed::price_resolution::to_string(msg.fields.price_resolution.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const series_index_mapping_message& msg) {
    os << "series_index=" << msg.fields.series_index.get().value()
       << ",channel_id=" << static_cast<unsigned>(msg.fields.channel_id.get().value())
       << ",market_id=\"" << xdp_deepfeed::market_id::to_string(msg.fields.market_id.get().value()) << '"'
       << ",system_id=" << static_cast<unsigned>(msg.fields.system_id.get().value())
       << ",stream_id=" << msg.fields.stream_id.get().value()
       << ",underlying_index=" << msg.fields.underlying_index.get().value()
       << ",contract_multiplier=" << msg.fields.contract_multiplier.get().value()
       << ",maturity_date=\"" << msg.fields.maturity_date.get_trimmed().value() << '"'
       << ",put_or_call=\"" << xdp_deepfeed::put_or_call::to_string(msg.fields.put_or_call.get().value()) << '"'
       << ",strike_price=\"" << msg.fields.strike_price.get_trimmed().value() << '"'
       << ",price_scale_code=" << static_cast<unsigned>(msg.fields.price_scale_code.get().value())
       << ",underlying_symbol=\"" << msg.fields.underlying_symbol.get_trimmed().value() << '"'
       << ",option_symbol_root=\"" << msg.fields.option_symbol_root.get_trimmed().value() << '"'
       << ",group_id=" << msg.fields.group_id.get().value()
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
