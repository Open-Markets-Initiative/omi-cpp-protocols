// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: messages/Format.hpp
#pragma once

#include <ostream>
#include <string_view>

#include "SimpleInstrumentDefinitionMessage.hpp"
#include "ComplexInstrumentDefinitionMessage.hpp"
#include "SystemStateMessage.hpp"
#include "InstrumentTradingStatusNotificationMessage.hpp"
#include "BestBidAndOfferMessage.hpp"
#include "LastSaleMessage.hpp"
#include "TradeCancelMessage.hpp"
#include "../json/messages/complex_instrument_definition_message_json.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

namespace mach_topofmarket = ::miax::onyxfutures::topofmarket::mach::v1_0_b;

inline std::ostream& operator<<(std::ostream& os, const mach_packet_header& value) {
    os << "sequence_number=" << value.sequence_number.get().value()
       << ",packet_length=" << value.packet_length.get().value()
       << ",packet_type=\"" << mach_topofmarket::packet_type::to_string(value.packet_type.get().value()) << '"'
       << ",session_number=" << static_cast<unsigned>(value.session_number.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const application_message& value) {
    os << "message_type=\"" << mach_topofmarket::message_type::to_string(value.message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const simple_instrument_definition_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",instrument_id=" << msg.fields.instrument_id.get().value()
       << ",underlying_asset_type=\"" << mach_topofmarket::underlying_asset_type::to_string(msg.fields.underlying_asset_type.get().value()) << '"'
       << ",underlying_asset=\"" << msg.fields.underlying_asset.get_trimmed().value() << '"'
       << ",product_group_code=\"" << msg.fields.product_group_code.get_trimmed().value() << '"'
       << ",exchange=\"" << msg.fields.exchange.get_trimmed().value() << '"'
       << ",instrument_id_source=\"" << mach_topofmarket::instrument_id_source::to_string(msg.fields.instrument_id_source.get().value()) << '"'
       << ",instrument_type=\"" << mach_topofmarket::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",maturity_month_year=" << msg.fields.maturity_month_year.get().value()
       << ",currency=\"" << mach_topofmarket::currency::to_string(msg.fields.currency.get().value()) << '"'
       << ",settlement_currency=\"" << mach_topofmarket::settlement_currency::to_string(msg.fields.settlement_currency.get().value()) << '"'
       << ",match_algorithm=\"" << mach_topofmarket::match_algorithm::to_string(msg.fields.match_algorithm.get().value()) << '"'
       << ",minimum_size=" << msg.fields.minimum_size.get().value()
       << ",maximum_size=" << msg.fields.maximum_size.get().value()
       << ",tick=" << msg.fields.tick.get().value()
       << ",unit_of_measure=\"" << msg.fields.unit_of_measure.get_trimmed().value() << '"'
       << ",unit_of_measure_quantity=" << msg.fields.unit_of_measure_quantity.get().value()
       << ",settlement_price=" << msg.fields.settlement_price.get().value()
       << ",settlement_price_type_calc_method=\"" << mach_topofmarket::settlement_price_type_calc_method::to_string(msg.fields.settlement_price_type_calc_method.get().value()) << '"'
       << ",total_volume=" << msg.fields.total_volume.get().value()
       << ",open_interest_quantity=" << msg.fields.open_interest_quantity.get().value()
       << ",high_limit_price=" << msg.fields.high_limit_price.get().value()
       << ",low_limit_price=" << msg.fields.low_limit_price.get().value()
       << ",trading_collar_variation_type=\"" << mach_topofmarket::trading_collar_variation_type::to_string(msg.fields.trading_collar_variation_type.get().value()) << '"'
       << ",trading_collar_variation=" << msg.fields.trading_collar_variation.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const complex_instrument_definition_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",strategy_id=" << msg.fields.strategy_id.get().value()
       << ",underlying_asset_type=\"" << mach_topofmarket::underlying_asset_type::to_string(msg.fields.underlying_asset_type.get().value()) << '"'
       << ",underlying_asset=\"" << msg.fields.underlying_asset.get_trimmed().value() << '"'
       << ",product_group_code=\"" << msg.fields.product_group_code.get_trimmed().value() << '"'
       << ",spread_type=\"" << msg.fields.spread_type.get().value() << '"'
       << ",exchange=\"" << msg.fields.exchange.get_trimmed().value() << '"'
       << ",instrument_id_source=\"" << mach_topofmarket::instrument_id_source::to_string(msg.fields.instrument_id_source.get().value()) << '"'
       << ",instrument_type=\"" << mach_topofmarket::instrument_type::to_string(msg.fields.instrument_type.get().value()) << '"'
       << ",currency=\"" << mach_topofmarket::currency::to_string(msg.fields.currency.get().value()) << '"'
       << ",settlement_currency=\"" << mach_topofmarket::settlement_currency::to_string(msg.fields.settlement_currency.get().value()) << '"'
       << ",match_algorithm=\"" << mach_topofmarket::match_algorithm::to_string(msg.fields.match_algorithm.get().value()) << '"'
       << ",minimum_size=" << msg.fields.minimum_size.get().value()
       << ",maximum_size=" << msg.fields.maximum_size.get().value()
       << ",tick=" << msg.fields.tick.get().value()
       << ",unit_of_measure=\"" << msg.fields.unit_of_measure.get_trimmed().value() << '"'
       << ",unit_of_measure_quantity=" << msg.fields.unit_of_measure_quantity.get().value()
       << ",trading_collar_variation_type=\"" << mach_topofmarket::trading_collar_variation_type::to_string(msg.fields.trading_collar_variation_type.get().value()) << '"'
       << ",trading_collar_variation=" << msg.fields.trading_collar_variation.get().value()
       << ",number_of_legs=" << static_cast<unsigned>(msg.fields.number_of_legs.get().value())
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const system_state_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",tom_version=\"" << msg.fields.tom_version.get_trimmed().value() << '"'
       << ",session_id=" << static_cast<unsigned>(msg.fields.session_id.get().value())
       << ",system_status=\"" << mach_topofmarket::system_status::to_string(msg.fields.system_status.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const instrument_trading_status_notification_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",instrument_id=" << msg.fields.instrument_id.get().value()
       << ",trading_status=\"" << mach_topofmarket::trading_status::to_string(msg.fields.trading_status.get().value()) << '"'
       << ",market_state=\"" << mach_topofmarket::market_state::to_string(msg.fields.market_state.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const best_bid_and_offer_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",instrument_id=" << msg.fields.instrument_id.get().value()
       << ",mbb_price=" << (msg.fields.mbb_price.get().has_value() ? std::to_string(msg.fields.mbb_price.get().value()) : std::string_view("null"))
       << ",mbb_size=" << msg.fields.mbb_size.get().value()
       << ",mbo_price=" << (msg.fields.mbo_price.get().has_value() ? std::to_string(msg.fields.mbo_price.get().value()) : std::string_view("null"))
       << ",mbo_size=" << msg.fields.mbo_size.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const last_sale_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",instrument_id=" << msg.fields.instrument_id.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",size=" << msg.fields.size.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_cancel_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",instrument_id=" << msg.fields.instrument_id.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",correction_number=" << static_cast<unsigned>(msg.fields.correction_number.get().value())
       << ",price=" << msg.fields.price.get().value()
       << ",size=" << msg.fields.size.get().value()
       ;
    return os;
}

}
