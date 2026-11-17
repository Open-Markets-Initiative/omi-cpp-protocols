// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/Format.hpp
#pragma once

#include <ostream>
#include <string_view>

#include "StartOfSpinMessage.hpp"
#include "EndOfSpinMessage.hpp"
#include "MarketOpenMessage.hpp"
#include "MarketCloseMessage.hpp"
#include "SecurityMessage.hpp"
#include "QuoteMessage.hpp"
#include "QuoteUpdateMessage.hpp"
#include "InsideMessage.hpp"
#include "InsideUpdateMessage.hpp"
#include "ReferencePriceMessage.hpp"
#include "ReferencePriceUpdateMessage.hpp"
#include "ExtendedSecurityMessage.hpp"
#include "ExtendedSecurityNoCusipMessage.hpp"
#include "TradeMessage.hpp"
#include "../json/messages/extended_security_message_json.hpp"
#include "../json/messages/extended_security_no_cusip_message_json.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

namespace link_multicast = ::otcmarkets::linkats::multicast::link::v4_3;

inline std::ostream& operator<<(std::ostream& os, const packet_header& value) {
    os << "packet_size=" << value.packet_size.get().value()
       << ",seq_num=" << value.seq_num.get().value()
       << ",packet_flag=" << static_cast<unsigned>(value.packet_flag.get().value())
       << ",message_count=" << static_cast<unsigned>(value.message_count.get().value())
       << ",packet_milli=" << value.packet_milli.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "message_size=" << value.message_size.get().value()
       << ",message_type=\"" << link_multicast::message_type::to_string(value.message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const start_of_spin_message& msg) {
    os << "channel_seq_num=" << msg.fields.channel_seq_num.get().value()
       << ",spin_type=\"" << link_multicast::spin_type::to_string(msg.fields.spin_type.get().value()) << '"'
       << ",spin_start_time_milli=" << msg.fields.spin_start_time_milli.get().value()
       << ",spin_last_seq_num=" << msg.fields.spin_last_seq_num.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const end_of_spin_message& msg) {
    os << "channel_seq_num=" << msg.fields.channel_seq_num.get().value()
       << ",spin_type=\"" << link_multicast::spin_type::to_string(msg.fields.spin_type.get().value()) << '"'
       << ",spin_msg_ct=" << msg.fields.spin_msg_ct.get().value()
       << ",spin_end_time_milli=" << msg.fields.spin_end_time_milli.get().value()
       << ",spin_last_seq_num=" << msg.fields.spin_last_seq_num.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const market_open_message& msg) {
    os << "channel_seq_num=" << msg.fields.channel_seq_num.get().value()
       << ",market_open=" << msg.fields.market_open.get().value()
       << ",market_close=" << msg.fields.market_close.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const market_close_message& msg) {
    os << "channel_seq_num=" << msg.fields.channel_seq_num.get().value()
       << ",market_close_time_milli=" << msg.fields.market_close_time_milli.get().value()
       << ",market_msg_ct=" << msg.fields.market_msg_ct.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const security_message& msg) {
    os << "channel_seq_num=" << msg.fields.channel_seq_num.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",last_update_milli=" << msg.fields.last_update_milli.get().value()
       << ",security_action=\"" << link_multicast::security_action::to_string(msg.fields.security_action.get().value()) << '"'
       << ",asset_class=\"" << link_multicast::asset_class::to_string(msg.fields.asset_class.get().value()) << '"'
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",security_flags=" << static_cast<unsigned>(msg.fields.security_flags.get().value())
       << ",tier=\"" << link_multicast::tier::to_string(msg.fields.tier.get().value()) << '"'
       << ",reporting_status=\"" << link_multicast::reporting_status::to_string(msg.fields.reporting_status.get().value()) << '"'
       << ",security_status=\"" << link_multicast::security_status::to_string(msg.fields.security_status.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const quote_message& msg) {
    os << "channel_seq_num=" << msg.fields.channel_seq_num.get().value()
       << ",quote_id=" << msg.fields.quote_id.get().value()
       << ",quote_action=" << static_cast<unsigned>(msg.fields.quote_action.get().value())
       << ",quote_flags=" << static_cast<unsigned>(msg.fields.quote_flags.get().value())
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",mpid=\"" << msg.fields.mpid.get_trimmed().value() << '"'
       << ",ask_price=" << msg.fields.ask_price.get().value()
       << ",ask_size=" << msg.fields.ask_size.get().value()
       << ",ask_qap=" << static_cast<int>(msg.fields.ask_qap.get().value())
       << ",ask_time_milli=" << msg.fields.ask_time_milli.get().value()
       << ",bid_price=" << msg.fields.bid_price.get().value()
       << ",bid_size=" << msg.fields.bid_size.get().value()
       << ",bid_qap=" << static_cast<int>(msg.fields.bid_qap.get().value())
       << ",bid_time_milli=" << msg.fields.bid_time_milli.get().value()
       << ",quote_reference_id=" << msg.fields.quote_reference_id.get().value()
       << ",extended_quote_flags=" << static_cast<unsigned>(msg.fields.extended_quote_flags.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const quote_update_message& msg) {
    os << "channel_seq_num=" << msg.fields.channel_seq_num.get().value()
       << ",quote_id=" << msg.fields.quote_id.get().value()
       << ",quote_flags=" << static_cast<unsigned>(msg.fields.quote_flags.get().value())
       << ",price=" << msg.fields.price.get().value()
       << ",size=" << msg.fields.size.get().value()
       << ",qap=" << static_cast<int>(msg.fields.qap.get().value())
       << ",quote_time_milli=" << msg.fields.quote_time_milli.get().value()
       << ",quote_reference_id=" << msg.fields.quote_reference_id.get().value()
       << ",extended_quote_flags=" << static_cast<unsigned>(msg.fields.extended_quote_flags.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const inside_message& msg) {
    os << "channel_seq_num=" << msg.fields.channel_seq_num.get().value()
       << ",inside_id=" << msg.fields.inside_id.get().value()
       << ",inside_action=\"" << link_multicast::inside_action::to_string(msg.fields.inside_action.get().value()) << '"'
       << ",quote_flags=" << static_cast<unsigned>(msg.fields.quote_flags.get().value())
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",ask_price=" << msg.fields.ask_price.get().value()
       << ",ask_size=" << msg.fields.ask_size.get().value()
       << ",ask_time_milli=" << msg.fields.ask_time_milli.get().value()
       << ",bid_price=" << msg.fields.bid_price.get().value()
       << ",bid_size=" << msg.fields.bid_size.get().value()
       << ",bid_time_milli=" << msg.fields.bid_time_milli.get().value()
       << ",ask_num_priced_mp=" << static_cast<unsigned>(msg.fields.ask_num_priced_mp.get().value())
       << ",bid_num_priced_mp=" << static_cast<unsigned>(msg.fields.bid_num_priced_mp.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const inside_update_message& msg) {
    os << "channel_seq_num=" << msg.fields.channel_seq_num.get().value()
       << ",inside_id=" << msg.fields.inside_id.get().value()
       << ",quote_flags=" << static_cast<unsigned>(msg.fields.quote_flags.get().value())
       << ",price=" << msg.fields.price.get().value()
       << ",size=" << msg.fields.size.get().value()
       << ",inside_time_milli=" << msg.fields.inside_time_milli.get().value()
       << ",num_priced_mp=" << static_cast<unsigned>(msg.fields.num_priced_mp.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const reference_price_message& msg) {
    os << "channel_seq_num=" << msg.fields.channel_seq_num.get().value()
       << ",reference_price_id=" << msg.fields.reference_price_id.get().value()
       << ",reference_price_action=\"" << link_multicast::reference_price_action::to_string(msg.fields.reference_price_action.get().value()) << '"'
       << ",quote_flags=" << static_cast<unsigned>(msg.fields.quote_flags.get().value())
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",ask_price=" << msg.fields.ask_price.get().value()
       << ",ask_size=" << msg.fields.ask_size.get().value()
       << ",ask_time_milli=" << msg.fields.ask_time_milli.get().value()
       << ",bid_price=" << msg.fields.bid_price.get().value()
       << ",bid_size=" << msg.fields.bid_size.get().value()
       << ",bid_time_milli=" << msg.fields.bid_time_milli.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const reference_price_update_message& msg) {
    os << "channel_seq_num=" << msg.fields.channel_seq_num.get().value()
       << ",reference_price_id=" << msg.fields.reference_price_id.get().value()
       << ",quote_flags=" << static_cast<unsigned>(msg.fields.quote_flags.get().value())
       << ",price=" << msg.fields.price.get().value()
       << ",size=" << msg.fields.size.get().value()
       << ",time_milli=" << msg.fields.time_milli.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const extended_security_message& msg) {
    os << "channel_seq_num=" << msg.fields.channel_seq_num.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",last_update_milli=" << msg.fields.last_update_milli.get().value()
       << ",security_action=\"" << link_multicast::security_action::to_string(msg.fields.security_action.get().value()) << '"'
       << ",otc_issuer_id=" << msg.fields.otc_issuer_id.get().value()
       << ",security_desc=\"" << msg.fields.security_desc.get_trimmed().value() << '"'
       << ",short_name=\"" << msg.fields.short_name.get_trimmed().value() << '"'
       << ",asset_class=\"" << link_multicast::asset_class::to_string(msg.fields.asset_class.get().value()) << '"'
       << ",security_type=\"" << msg.fields.security_type.get_trimmed().value() << '"'
       << ",primary_market=\"" << msg.fields.primary_market.get_trimmed().value() << '"'
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",extended_security_flags=" << static_cast<unsigned>(msg.fields.extended_security_flags.get().value())
       << ",tier=\"" << link_multicast::tier::to_string(msg.fields.tier.get().value()) << '"'
       << ",reporting_status=\"" << link_multicast::reporting_status::to_string(msg.fields.reporting_status.get().value()) << '"'
       << ",disclosure_status=\"" << link_multicast::disclosure_status::to_string(msg.fields.disclosure_status.get().value()) << '"'
       << ",security_status=\"" << link_multicast::security_status::to_string(msg.fields.security_status.get().value()) << '"'
       << ",par_value=" << msg.fields.par_value.get().value()
       << ",coupon=" << msg.fields.coupon.get().value()
       << ",maturity_date_milli=" << msg.fields.maturity_date_milli.get().value()
       << ",callable_date_milli=" << msg.fields.callable_date_milli.get().value()
       << ",adr_ratio=" << msg.fields.adr_ratio.get().value()
       << ",adr_level=\"" << msg.fields.adr_level.get_trimmed().value() << '"'
       << ",cusip=\"" << msg.fields.cusip.get_trimmed().value() << '"'
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const extended_security_no_cusip_message& msg) {
    os << "channel_seq_num=" << msg.fields.channel_seq_num.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",last_update_milli=" << msg.fields.last_update_milli.get().value()
       << ",security_action=\"" << link_multicast::security_action::to_string(msg.fields.security_action.get().value()) << '"'
       << ",otc_issuer_id=" << msg.fields.otc_issuer_id.get().value()
       << ",security_desc=\"" << msg.fields.security_desc.get_trimmed().value() << '"'
       << ",short_name=\"" << msg.fields.short_name.get_trimmed().value() << '"'
       << ",asset_class=\"" << link_multicast::asset_class::to_string(msg.fields.asset_class.get().value()) << '"'
       << ",security_type=\"" << msg.fields.security_type.get_trimmed().value() << '"'
       << ",primary_market=\"" << msg.fields.primary_market.get_trimmed().value() << '"'
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",security_flags=" << static_cast<unsigned>(msg.fields.security_flags.get().value())
       << ",tier=\"" << link_multicast::tier::to_string(msg.fields.tier.get().value()) << '"'
       << ",reporting_status=\"" << link_multicast::reporting_status::to_string(msg.fields.reporting_status.get().value()) << '"'
       << ",disclosure_status=\"" << link_multicast::disclosure_status::to_string(msg.fields.disclosure_status.get().value()) << '"'
       << ",security_status=\"" << link_multicast::security_status::to_string(msg.fields.security_status.get().value()) << '"'
       << ",par_value=" << msg.fields.par_value.get().value()
       << ",coupon=" << msg.fields.coupon.get().value()
       << ",maturity_date_milli=" << msg.fields.maturity_date_milli.get().value()
       << ",callable_date_milli=" << msg.fields.callable_date_milli.get().value()
       << ",adr_ratio=" << msg.fields.adr_ratio.get().value()
       << ",adr_level=\"" << msg.fields.adr_level.get_trimmed().value() << '"'
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_message& msg) {
    os << "channel_seq_num=" << msg.fields.channel_seq_num.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",trade_action=\"" << link_multicast::trade_action::to_string(msg.fields.trade_action.get().value()) << '"'
       << ",trade_flags=" << static_cast<unsigned>(msg.fields.trade_flags.get().value())
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",trade_status=" << static_cast<unsigned>(msg.fields.trade_status.get().value())
       << ",deprecated=\"" << msg.fields.deprecated.get_trimmed().value() << '"'
       << ",trade_price=" << msg.fields.trade_price.get().value()
       << ",trade_size=" << msg.fields.trade_size.get().value()
       << ",trade_time_milli=" << msg.fields.trade_time_milli.get().value()
       ;
    return os;
}

}
