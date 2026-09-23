#pragma once

#include <ostream>
#include <string_view>

#include "DebugPacket.hpp"
#include "LoginRequestPacket.hpp"
#include "UnsequencedDataPacket.hpp"
#include "LoginAcceptedPacket.hpp"
#include "LoginRejectedPacket.hpp"
#include "SequencedDataPacket.hpp"
#include "SystemEventMessage.hpp"
#include "StockDirectoryMessage.hpp"
#include "StockTradingActionMessage.hpp"
#include "RegShoShortSalePriceTestRestrictedIndicatorMessage.hpp"
#include "MarketParticipantPositionMessage.hpp"
#include "MwcbDeclineLevelMessage.hpp"
#include "MwcbStatusLevelMessage.hpp"
#include "IpoQuotingPeriodUpdate.hpp"
#include "LuldAuctionCollarMessage.hpp"
#include "OperationalHaltMessage.hpp"
#include "AddOrderNoMpidAttributionMessage.hpp"
#include "AddOrderWithMpidAttributionMessage.hpp"
#include "OrderExecutedMessage.hpp"
#include "OrderExecutedWithPriceMessage.hpp"
#include "OrderCancelMessage.hpp"
#include "OrderDeleteMessage.hpp"
#include "OrderReplaceMessage.hpp"
#include "NonCrossTradeMessage.hpp"
#include "CrossTradeMessage.hpp"
#include "BrokenTradeMessage.hpp"
#include "NetOrderImbalanceIndicatorMessage.hpp"
#include "RetailPriceImprovementIndicatorMessage.hpp"
#include "DirectListingWithCapitalRaisePriceDiscoveryMessage.hpp"
#include "../json/messages/unsequenced_data_packet_json.hpp"
#include "../json/messages/sequenced_data_packet_json.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v5_0_2023;

inline std::ostream& operator<<(std::ostream& os, const client_packet_header& value) {
    os << "packet_length=" << value.packet_length.get().value()
       << ",client_packet_type=\"" << itch_totalview::client_packet_type::to_string(value.client_packet_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const server_packet_header& value) {
    os << "packet_length=" << value.packet_length.get().value()
       << ",server_packet_type=\"" << itch_totalview::server_packet_type::to_string(value.server_packet_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const packet_header& value) {
    os << "session=\"" << value.session.get_trimmed().value() << '"'
       << ",sequence_number=" << value.sequence_number.get().value()
       << ",message_count=" << value.message_count.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "message_length=" << value.message_length.get().value()
       << ",message_type=\"" << itch_totalview::message_type::to_string(value.message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const debug_packet& msg) {
    os << "text=\"" << msg.fields.text.get().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const login_request_packet& msg) {
    os << "username=\"" << msg.fields.username.get_trimmed().value() << '"'
       << ",password=\"" << msg.fields.password.get_trimmed().value() << '"'
       << ",requested_session=\"" << msg.fields.requested_session.get_trimmed().value() << '"'
       << ",requested_sequence_number=\"" << msg.fields.requested_sequence_number.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const unsequenced_data_packet& msg) {
    os << "unsequenced_message_type=\"" << msg.fields.unsequenced_message_type.get().value() << '"'
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const login_accepted_packet& msg) {
    os << "accepted_session=\"" << msg.fields.accepted_session.get_trimmed().value() << '"'
       << ",accepted_sequence_number=\"" << msg.fields.accepted_sequence_number.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const login_rejected_packet& msg) {
    os << "reject_reason_code=\"" << itch_totalview::reject_reason_code::to_string(msg.fields.reject_reason_code.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const sequenced_data_packet& msg) {
    os << "sequenced_message_type=\"" << msg.fields.sequenced_message_type.get().value() << '"'
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const system_event_message& msg) {
    os << "stock_locate=" << msg.fields.stock_locate.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",event_code=\"" << itch_totalview::event_code::to_string(msg.fields.event_code.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const stock_directory_message& msg) {
    os << "stock_locate=" << msg.fields.stock_locate.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",stock=\"" << msg.fields.stock.get_trimmed().value() << '"'
       << ",market_category=\"" << itch_totalview::market_category::to_string(msg.fields.market_category.get().value()) << '"'
       << ",financial_status_indicator=\"" << itch_totalview::financial_status_indicator::to_string(msg.fields.financial_status_indicator.get().value()) << '"'
       << ",round_lot_size=" << msg.fields.round_lot_size.get().value()
       << ",round_lots_only=\"" << itch_totalview::round_lots_only::to_string(msg.fields.round_lots_only.get().value()) << '"'
       << ",issue_classification=\"" << itch_totalview::issue_classification::to_string(msg.fields.issue_classification.get().value()) << '"'
       << ",issue_sub_type=\"" << msg.fields.issue_sub_type.get_trimmed().value() << '"'
       << ",authenticity=\"" << itch_totalview::authenticity::to_string(msg.fields.authenticity.get().value()) << '"'
       << ",short_sale_threshold_indicator=\"" << itch_totalview::short_sale_threshold_indicator::to_string(msg.fields.short_sale_threshold_indicator.get().value()) << '"'
       << ",ipo_flag=\"" << itch_totalview::ipo_flag::to_string(msg.fields.ipo_flag.get().value()) << '"'
       << ",luld_reference_price_tier=\"" << itch_totalview::luld_reference_price_tier::to_string(msg.fields.luld_reference_price_tier.get().value()) << '"'
       << ",etp_flag=\"" << itch_totalview::etp_flag::to_string(msg.fields.etp_flag.get().value()) << '"'
       << ",etp_leverage_factor=" << msg.fields.etp_leverage_factor.get().value()
       << ",inverse_indicator=\"" << itch_totalview::inverse_indicator::to_string(msg.fields.inverse_indicator.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const stock_trading_action_message& msg) {
    os << "stock_locate=" << msg.fields.stock_locate.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",stock=\"" << msg.fields.stock.get_trimmed().value() << '"'
       << ",trading_state=\"" << itch_totalview::trading_state::to_string(msg.fields.trading_state.get().value()) << '"'
       << ",reason_code=\"" << msg.fields.reason_code.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const reg_sho_short_sale_price_test_restricted_indicator_message& msg) {
    os << "locate_code=" << msg.fields.locate_code.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",stock=\"" << msg.fields.stock.get_trimmed().value() << '"'
       << ",reg_sho_action=\"" << itch_totalview::reg_sho_action::to_string(msg.fields.reg_sho_action.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const market_participant_position_message& msg) {
    os << "stock_locate=" << msg.fields.stock_locate.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",mpid=\"" << msg.fields.mpid.get_trimmed().value() << '"'
       << ",stock=\"" << msg.fields.stock.get_trimmed().value() << '"'
       << ",primary_market_maker=\"" << itch_totalview::primary_market_maker::to_string(msg.fields.primary_market_maker.get().value()) << '"'
       << ",market_maker_mode=\"" << itch_totalview::market_maker_mode::to_string(msg.fields.market_maker_mode.get().value()) << '"'
       << ",market_participant_state=\"" << itch_totalview::market_participant_state::to_string(msg.fields.market_participant_state.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const mwcb_decline_level_message& msg) {
    os << "stock_locate=" << msg.fields.stock_locate.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",level_1=" << msg.fields.level_1.get().value()
       << ",level_2=" << msg.fields.level_2.get().value()
       << ",level_3=" << msg.fields.level_3.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const mwcb_status_level_message& msg) {
    os << "stock_locate=" << msg.fields.stock_locate.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",breached_level=\"" << itch_totalview::breached_level::to_string(msg.fields.breached_level.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const ipo_quoting_period_update& msg) {
    os << "stock_locate=" << msg.fields.stock_locate.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",stock=\"" << msg.fields.stock.get_trimmed().value() << '"'
       << ",ipo_quotation_release_time=" << msg.fields.ipo_quotation_release_time.get().value()
       << ",ipo_quotation_release_qualifier=\"" << itch_totalview::ipo_quotation_release_qualifier::to_string(msg.fields.ipo_quotation_release_qualifier.get().value()) << '"'
       << ",ipo_price=" << msg.fields.ipo_price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const luld_auction_collar_message& msg) {
    os << "stock_locate=" << msg.fields.stock_locate.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",stock=\"" << msg.fields.stock.get_trimmed().value() << '"'
       << ",auction_collar_reference_price=" << msg.fields.auction_collar_reference_price.get().value()
       << ",upper_auction_collar_price=" << msg.fields.upper_auction_collar_price.get().value()
       << ",lower_auction_collar_price=" << msg.fields.lower_auction_collar_price.get().value()
       << ",auction_collar_extension=" << msg.fields.auction_collar_extension.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const operational_halt_message& msg) {
    os << "stock_locate=" << msg.fields.stock_locate.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",stock=\"" << msg.fields.stock.get_trimmed().value() << '"'
       << ",market_code=\"" << itch_totalview::market_code::to_string(msg.fields.market_code.get().value()) << '"'
       << ",operational_halt_action=\"" << itch_totalview::operational_halt_action::to_string(msg.fields.operational_halt_action.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_order_no_mpid_attribution_message& msg) {
    os << "stock_locate=" << msg.fields.stock_locate.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",order_reference_number=" << msg.fields.order_reference_number.get().value()
       << ",buy_sell_indicator=\"" << itch_totalview::buy_sell_indicator::to_string(msg.fields.buy_sell_indicator.get().value()) << '"'
       << ",shares=" << msg.fields.shares.get().value()
       << ",stock=\"" << msg.fields.stock.get_trimmed().value() << '"'
       << ",price=" << msg.fields.price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_order_with_mpid_attribution_message& msg) {
    os << "stock_locate=" << msg.fields.stock_locate.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",order_reference_number=" << msg.fields.order_reference_number.get().value()
       << ",buy_sell_indicator=\"" << itch_totalview::buy_sell_indicator::to_string(msg.fields.buy_sell_indicator.get().value()) << '"'
       << ",shares=" << msg.fields.shares.get().value()
       << ",stock=\"" << msg.fields.stock.get_trimmed().value() << '"'
       << ",price=" << msg.fields.price.get().value()
       << ",attribution=\"" << msg.fields.attribution.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_executed_message& msg) {
    os << "stock_locate=" << msg.fields.stock_locate.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",order_reference_number=" << msg.fields.order_reference_number.get().value()
       << ",executed_shares=" << msg.fields.executed_shares.get().value()
       << ",match_number=" << msg.fields.match_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_executed_with_price_message& msg) {
    os << "stock_locate=" << msg.fields.stock_locate.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",order_reference_number=" << msg.fields.order_reference_number.get().value()
       << ",executed_shares=" << msg.fields.executed_shares.get().value()
       << ",match_number=" << msg.fields.match_number.get().value()
       << ",printable=\"" << itch_totalview::printable::to_string(msg.fields.printable.get().value()) << '"'
       << ",execution_price=" << msg.fields.execution_price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_cancel_message& msg) {
    os << "stock_locate=" << msg.fields.stock_locate.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",order_reference_number=" << msg.fields.order_reference_number.get().value()
       << ",canceled_shares=" << msg.fields.canceled_shares.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_delete_message& msg) {
    os << "stock_locate=" << msg.fields.stock_locate.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",order_reference_number=" << msg.fields.order_reference_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_replace_message& msg) {
    os << "stock_locate=" << msg.fields.stock_locate.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",original_order_reference_number=" << msg.fields.original_order_reference_number.get().value()
       << ",new_order_reference_number=" << msg.fields.new_order_reference_number.get().value()
       << ",shares=" << msg.fields.shares.get().value()
       << ",price=" << msg.fields.price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const non_cross_trade_message& msg) {
    os << "stock_locate=" << msg.fields.stock_locate.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",order_reference_number=" << msg.fields.order_reference_number.get().value()
       << ",buy_sell_indicator=\"" << itch_totalview::buy_sell_indicator::to_string(msg.fields.buy_sell_indicator.get().value()) << '"'
       << ",shares=" << msg.fields.shares.get().value()
       << ",stock=\"" << msg.fields.stock.get_trimmed().value() << '"'
       << ",price=" << msg.fields.price.get().value()
       << ",match_number=" << msg.fields.match_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const cross_trade_message& msg) {
    os << "stock_locate=" << msg.fields.stock_locate.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",cross_shares=" << msg.fields.cross_shares.get().value()
       << ",stock=\"" << msg.fields.stock.get_trimmed().value() << '"'
       << ",cross_price=" << msg.fields.cross_price.get().value()
       << ",match_number=" << msg.fields.match_number.get().value()
       << ",cross_type=\"" << itch_totalview::cross_type::to_string(msg.fields.cross_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const broken_trade_message& msg) {
    os << "stock_locate=" << msg.fields.stock_locate.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",match_number=" << msg.fields.match_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const net_order_imbalance_indicator_message& msg) {
    os << "stock_locate=" << msg.fields.stock_locate.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",paired_shares=" << msg.fields.paired_shares.get().value()
       << ",imbalance_shares=" << msg.fields.imbalance_shares.get().value()
       << ",imbalance_direction=\"" << itch_totalview::imbalance_direction::to_string(msg.fields.imbalance_direction.get().value()) << '"'
       << ",stock=\"" << msg.fields.stock.get_trimmed().value() << '"'
       << ",far_price=" << msg.fields.far_price.get().value()
       << ",near_price=" << msg.fields.near_price.get().value()
       << ",current_reference_price=" << msg.fields.current_reference_price.get().value()
       << ",cross_type=\"" << itch_totalview::cross_type::to_string(msg.fields.cross_type.get().value()) << '"'
       << ",price_variation_indicator=\"" << itch_totalview::price_variation_indicator::to_string(msg.fields.price_variation_indicator.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const retail_price_improvement_indicator_message& msg) {
    os << "stock_locate=" << msg.fields.stock_locate.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",stock=\"" << msg.fields.stock.get_trimmed().value() << '"'
       << ",interest_flag=\"" << itch_totalview::interest_flag::to_string(msg.fields.interest_flag.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const direct_listing_with_capital_raise_price_discovery_message& msg) {
    os << "stock_locate=" << msg.fields.stock_locate.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",stock=\"" << msg.fields.stock.get_trimmed().value() << '"'
       << ",open_eligibility_status=\"" << itch_totalview::open_eligibility_status::to_string(msg.fields.open_eligibility_status.get().value()) << '"'
       << ",minimum_allowable_price=" << msg.fields.minimum_allowable_price.get().value()
       << ",maximum_allowable_price=" << msg.fields.maximum_allowable_price.get().value()
       << ",near_execution_price=" << msg.fields.near_execution_price.get().value()
       << ",near_execution_time=" << msg.fields.near_execution_time.get().value()
       << ",lower_price_range_collar=" << msg.fields.lower_price_range_collar.get().value()
       << ",upper_price_range_collar=" << msg.fields.upper_price_range_collar.get().value()
       ;
    return os;
}

}
