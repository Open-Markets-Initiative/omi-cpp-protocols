#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/AdministrativeCategory.hpp"
#include "../structs/BlockHeader.hpp"
#include "../types/MessageDataLength.hpp"

#include "AdministrativeMessage.hpp"
#include "ControlMessage.hpp"
#include "EquityAndIndexLastSaleMessage.hpp"
#include "OpenInterestMessage.hpp"
#include "EquityAndIndexEndOfDaySummaryMessage.hpp"
#include "LongEquityAndIndexQuoteMessage.hpp"
#include "ShortEquityAndIndexQuoteMessage.hpp"
#include "UnderlyingValueLastSaleMessage.hpp"
#include "UnderlyingValueBidAndOfferMessage.hpp"

namespace siac::opra::output::obi::v6_2 {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
std::size_t dispatch(Handler& handler, const std::byte* buffer, std::size_t length, std::uint64_t packet_receive_time, const block_header& transport) {
    (void)length;

    switch (administrative_message::parse(buffer)->header.message_category.get().value()) {
        case message_category::enum_type::administrative: {
            switch (administrative_message::parse(buffer)->administrative_message_type.get().value()) {
                case administrative_message_type::enum_type::administrative: {
                    const auto* msg = administrative_message::parse(buffer);
                    handler.on_message(*msg, packet_receive_time, transport);
                    return offsetof(administrative_message, tail) + msg->fields.message_data_length.get().value();
                }
                default:
                    // Unknown Administrative Message Type: nothing consumed
                    return 0;
                    break;
            }
            return 0;
        }
        case message_category::enum_type::control: {
            switch (control_message::parse(buffer)->control_message_type.get().value()) {
                case control_message_type::enum_type::start_of_day:
                case control_message_type::enum_type::start_of_summary:
                case control_message_type::enum_type::end_of_summary:
                case control_message_type::enum_type::end_of_day:
                case control_message_type::enum_type::reset_block_sequence_number:
                case control_message_type::enum_type::start_of_open_interest:
                case control_message_type::enum_type::end_of_open_interest:
                case control_message_type::enum_type::line_integrity:
                case control_message_type::enum_type::disaster_recovery_data_center_activation: {
                    const auto* msg = control_message::parse(buffer);
                    handler.on_message(*msg, packet_receive_time, transport);
                    return sizeof(control_message);
                }
                default:
                    // Unknown Control Message Type: nothing consumed
                    return 0;
                    break;
            }
            return 0;
        }
        case message_category::enum_type::equity_and_index_last_sale: {
            switch (equity_and_index_last_sale_message::parse(buffer)->equity_and_index_last_sale_message_type.get().value()) {
                case equity_and_index_last_sale_message_type::enum_type::canc:
                case equity_and_index_last_sale_message_type::enum_type::oseq:
                case equity_and_index_last_sale_message_type::enum_type::cncl:
                case equity_and_index_last_sale_message_type::enum_type::late:
                case equity_and_index_last_sale_message_type::enum_type::cnco:
                case equity_and_index_last_sale_message_type::enum_type::open:
                case equity_and_index_last_sale_message_type::enum_type::cnol:
                case equity_and_index_last_sale_message_type::enum_type::opnl:
                case equity_and_index_last_sale_message_type::enum_type::auto_value:
                case equity_and_index_last_sale_message_type::enum_type::reop:
                case equity_and_index_last_sale_message_type::enum_type::ajst:
                case equity_and_index_last_sale_message_type::enum_type::sprd:
                case equity_and_index_last_sale_message_type::enum_type::stdl:
                case equity_and_index_last_sale_message_type::enum_type::stpd:
                case equity_and_index_last_sale_message_type::enum_type::cstp:
                case equity_and_index_last_sale_message_type::enum_type::bwrt:
                case equity_and_index_last_sale_message_type::enum_type::cmbo:
                case equity_and_index_last_sale_message_type::enum_type::spim:
                case equity_and_index_last_sale_message_type::enum_type::isoi:
                case equity_and_index_last_sale_message_type::enum_type::bnmt:
                case equity_and_index_last_sale_message_type::enum_type::xmpt: {
                    const auto* msg = equity_and_index_last_sale_message::parse(buffer);
                    handler.on_message(*msg, packet_receive_time, transport);
                    return sizeof(equity_and_index_last_sale_message);
                }
                default:
                    // Unknown Equity And Index Last Sale Message Type: nothing consumed
                    return 0;
                    break;
            }
            return 0;
        }
        case message_category::enum_type::open_interest: {
            switch (open_interest_message::parse(buffer)->open_interest_message_type.get().value()) {
                case open_interest_message_type::enum_type::open_interest: {
                    const auto* msg = open_interest_message::parse(buffer);
                    handler.on_message(*msg, packet_receive_time, transport);
                    return sizeof(open_interest_message);
                }
                default:
                    // Unknown Open Interest Message Type: nothing consumed
                    return 0;
                    break;
            }
            return 0;
        }
        case message_category::enum_type::equity_and_index_end_of_day_summary: {
            switch (equity_and_index_end_of_day_summary_message::parse(buffer)->equity_and_index_end_of_day_summary_message_type.get().value()) {
                case equity_and_index_end_of_day_summary_message_type::enum_type::equity_and_index_end_of_day_summary: {
                    const auto* msg = equity_and_index_end_of_day_summary_message::parse(buffer);
                    handler.on_message(*msg, packet_receive_time, transport);
                    return sizeof(equity_and_index_end_of_day_summary_message);
                }
                default:
                    // Unknown Equity And Index End Of Day Summary Message Type: nothing consumed
                    return 0;
                    break;
            }
            return 0;
        }
        case message_category::enum_type::long_equity_and_index_quote: {
            switch (long_equity_and_index_quote_message::parse(buffer)->long_equity_and_index_quote_message_type.get().value()) {
                case long_equity_and_index_quote_message_type::enum_type::regular_trading:
                case long_equity_and_index_quote_message_type::enum_type::non_firm_quote:
                case long_equity_and_index_quote_message_type::enum_type::indicative_value:
                case long_equity_and_index_quote_message_type::enum_type::rotation:
                case long_equity_and_index_quote_message_type::enum_type::trading_halted:
                case long_equity_and_index_quote_message_type::enum_type::eligible_for_automatic_execution:
                case long_equity_and_index_quote_message_type::enum_type::bid_contains_customer_trading_interest:
                case long_equity_and_index_quote_message_type::enum_type::offer_contains_customer_trading_interest:
                case long_equity_and_index_quote_message_type::enum_type::both_bid_and_offer_contain_customer_trading_interest:
                case long_equity_and_index_quote_message_type::enum_type::offer_side_of_quote_not_firm_bid_side_firm:
                case long_equity_and_index_quote_message_type::enum_type::bid_side_of_quote_not_firm_offer_side_firm: {
                    const auto* msg = long_equity_and_index_quote_message::parse(buffer);
                    handler.on_message(*msg, packet_receive_time, transport);
                    std::size_t sz = offsetof(long_equity_and_index_quote_message, tail);
                    auto bbo = static_cast<char>(msg->fields.bbo_indicator.get().value());
                    if (bbo >= 'M' && bbo <= 'P') sz += 10;
                    if ((bbo & 3) == ('C' & 3)) sz += 10;
                    return sz;
                }
                default:
                    // Unknown Long Equity And Index Quote Message Type: nothing consumed
                    return 0;
                    break;
            }
            return 0;
        }
        case message_category::enum_type::short_equity_and_index_quote: {
            switch (short_equity_and_index_quote_message::parse(buffer)->short_equity_and_index_quote_message_type.get().value()) {
                case short_equity_and_index_quote_message_type::enum_type::regular_trading:
                case short_equity_and_index_quote_message_type::enum_type::non_firm_quote:
                case short_equity_and_index_quote_message_type::enum_type::indicative_value:
                case short_equity_and_index_quote_message_type::enum_type::rotation:
                case short_equity_and_index_quote_message_type::enum_type::trading_halted:
                case short_equity_and_index_quote_message_type::enum_type::eligible_for_automatic_execution:
                case short_equity_and_index_quote_message_type::enum_type::bid_contains_customer_trading_interest:
                case short_equity_and_index_quote_message_type::enum_type::offer_contains_customer_trading_interest:
                case short_equity_and_index_quote_message_type::enum_type::both_bid_and_offer_contain_customer_trading_interest:
                case short_equity_and_index_quote_message_type::enum_type::offer_side_of_quote_not_firm_bid_side_firm:
                case short_equity_and_index_quote_message_type::enum_type::bid_side_of_quote_not_firm_offer_side_firm: {
                    const auto* msg = short_equity_and_index_quote_message::parse(buffer);
                    handler.on_message(*msg, packet_receive_time, transport);
                    std::size_t sz = offsetof(short_equity_and_index_quote_message, tail);
                    auto bbo = static_cast<char>(msg->fields.bbo_indicator.get().value());
                    if (bbo >= 'M' && bbo <= 'P') sz += 10;
                    if ((bbo & 3) == ('C' & 3)) sz += 10;
                    return sz;
                }
                default:
                    // Unknown Short Equity And Index Quote Message Type: nothing consumed
                    return 0;
                    break;
            }
            return 0;
        }
        case message_category::enum_type::underlying_value: {
            switch (underlying_value_last_sale_message::parse(buffer)->underlying_value_message_type.get().value()) {
                case underlying_value_message_type::enum_type::index_based_on_last_sale: {
                    const auto* msg = underlying_value_last_sale_message::parse(buffer);
                    handler.on_message(*msg, packet_receive_time, transport);
                    return sizeof(underlying_value_last_sale_message);
                }
                case underlying_value_message_type::enum_type::index_based_on_bid_and_offer: {
                    const auto* msg = underlying_value_bid_and_offer_message::parse(buffer);
                    handler.on_message(*msg, packet_receive_time, transport);
                    return sizeof(underlying_value_bid_and_offer_message);
                }
                default:
                    // Unknown Underlying Value Message Type: nothing consumed
                    return 0;
                    break;
            }
            return 0;
        }
        default:
            // a code none of the messages answer to: nothing consumed, which ends the block
            return 0;
            break;
    }
}

}
