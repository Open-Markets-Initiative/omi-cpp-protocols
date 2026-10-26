// Asx.AsxDerivatives.Ntp.Itch.v1.05 canonical values, through the Modern iterator: every value Modern reads from
// each sample, at its address, held to what the model reads.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "tests/canonical/Canonical.hpp"
#include "cpp/binary/modern/asx/asxderivatives/ntp/itch/v1.05/definitions.hpp"

namespace protocol = ::asx::asxderivatives::ntp::itch::v1_05;

namespace {

// The values the Modern iterator reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    values["packet.packetheader.session"] = canonical::text(std::string(iterator.packet_header->session.get()), '\0', false);
    values["packet.packetheader.sequencenumber"] = canonical::number(iterator.packet_header->sequence_number.get());
    values["packet.packetheader.messagecount"] = canonical::number(iterator.packet_header->message_count.get());

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(iterator.message_header->message_length.get());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(iterator.message_header->message_type.get()));

        if (iterator.message_type == protocol::SecondsMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.secondsmessage";
            [[maybe_unused]] const auto* message = protocol::SecondsMessage::parse(iterator.message);
            values[entry + ".payload.secondsmessage.second"] = canonical::number(message->second.get());
        } else if (iterator.message_type == protocol::EndOfBusinessTradeDateMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.endofbusinesstradedatemessage";
            [[maybe_unused]] const auto* message = protocol::EndOfBusinessTradeDateMessage::parse(iterator.message);
            values[entry + ".payload.endofbusinesstradedatemessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.endofbusinesstradedatemessage.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.endofbusinesstradedatemessage.eventcode"] = canonical::text(canonical::character(message->event_code.get()), ' ', false);
        } else if (iterator.message_type == protocol::FutureSymbolDirectoryMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.futuresymboldirectorymessage";
            [[maybe_unused]] const auto* message = protocol::FutureSymbolDirectoryMessage::parse(iterator.message);
            values[entry + ".payload.futuresymboldirectorymessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.futuresymboldirectorymessage.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.futuresymboldirectorymessage.tradeableinstrumentid"] = canonical::number(message->tradeable_instrument_id.get());
            values[entry + ".payload.futuresymboldirectorymessage.symbolname"] = canonical::text(std::string(message->symbol_name.get()), ' ', false);
            values[entry + ".payload.futuresymboldirectorymessage.longname"] = canonical::text(std::string(message->long_name.get()), ' ', false);
            values[entry + ".payload.futuresymboldirectorymessage.isin"] = canonical::text(std::string(message->isin.get()), ' ', false);
            values[entry + ".payload.futuresymboldirectorymessage.exchange"] = canonical::text(std::string(message->exchange.get()), ' ', false);
            values[entry + ".payload.futuresymboldirectorymessage.instrument"] = canonical::text(std::string(message->instrument.get()), ' ', false);
            values[entry + ".payload.futuresymboldirectorymessage.cficode"] = canonical::text(std::string(message->cfi_code.get()), ' ', false);
            values[entry + ".payload.futuresymboldirectorymessage.expiryyear"] = canonical::number(message->expiry_year.get());
            values[entry + ".payload.futuresymboldirectorymessage.expirymonth"] = canonical::number(message->expiry_month.get());
            values[entry + ".payload.futuresymboldirectorymessage.pricedisplaydecimals"] = canonical::number(message->price_display_decimals.get());
            values[entry + ".payload.futuresymboldirectorymessage.pricefractionaldenominator"] = canonical::number(message->price_fractional_denominator.get());
            values[entry + ".payload.futuresymboldirectorymessage.priceminimumtick"] = canonical::number(message->price_minimum_tick.get());
            values[entry + ".payload.futuresymboldirectorymessage.lasttradingdate"] = canonical::number(message->last_trading_date.get());
            values[entry + ".payload.futuresymboldirectorymessage.priordaysettlement"] = canonical::scaled(message->prior_day_settlement.integer(), -2);
            values[entry + ".payload.futuresymboldirectorymessage.currency"] = canonical::text(std::string(message->currency.get()), ' ', false);
            values[entry + ".payload.futuresymboldirectorymessage.lotsizeorfacevalue"] = canonical::number(message->lot_size_or_face_value.get());
            values[entry + ".payload.futuresymboldirectorymessage.maturityvalue"] = canonical::number(message->maturity_value.get());
            values[entry + ".payload.futuresymboldirectorymessage.couponrate"] = canonical::number(message->coupon_rate.get());
            values[entry + ".payload.futuresymboldirectorymessage.paymentsperyear"] = canonical::number(message->payments_per_year.get());
            values[entry + ".payload.futuresymboldirectorymessage.blocklotsize"] = canonical::number(message->block_lot_size.get());
            values[entry + ".payload.futuresymboldirectorymessage.expirydate"] = canonical::number(message->expiry_date.get());
        } else if (iterator.message_type == protocol::OptionsSymbolDirectoryMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.optionssymboldirectorymessage";
            [[maybe_unused]] const auto* message = protocol::OptionsSymbolDirectoryMessage::parse(iterator.message);
            values[entry + ".payload.optionssymboldirectorymessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.optionssymboldirectorymessage.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.optionssymboldirectorymessage.tradeableinstrumentid"] = canonical::number(message->tradeable_instrument_id.get());
            values[entry + ".payload.optionssymboldirectorymessage.symbolname"] = canonical::text(std::string(message->symbol_name.get()), ' ', false);
            values[entry + ".payload.optionssymboldirectorymessage.longname"] = canonical::text(std::string(message->long_name.get()), ' ', false);
            values[entry + ".payload.optionssymboldirectorymessage.isin"] = canonical::text(std::string(message->isin.get()), ' ', false);
            values[entry + ".payload.optionssymboldirectorymessage.exchange"] = canonical::text(std::string(message->exchange.get()), ' ', false);
            values[entry + ".payload.optionssymboldirectorymessage.instrument"] = canonical::text(std::string(message->instrument.get()), ' ', false);
            values[entry + ".payload.optionssymboldirectorymessage.cficode"] = canonical::text(std::string(message->cfi_code.get()), ' ', false);
            values[entry + ".payload.optionssymboldirectorymessage.expiryyear"] = canonical::number(message->expiry_year.get());
            values[entry + ".payload.optionssymboldirectorymessage.expirymonth"] = canonical::number(message->expiry_month.get());
            values[entry + ".payload.optionssymboldirectorymessage.optiontype"] = canonical::text(canonical::character(message->option_type.get()), ' ', false);
            values[entry + ".payload.optionssymboldirectorymessage.strike"] = canonical::scaled(message->strike.integer(), -2);
            values[entry + ".payload.optionssymboldirectorymessage.underlyingtradeableinstrumentid"] = canonical::number(message->underlying_tradeable_instrument_id.get());
            values[entry + ".payload.optionssymboldirectorymessage.pricedisplaydecimals"] = canonical::number(message->price_display_decimals.get());
            values[entry + ".payload.optionssymboldirectorymessage.pricefractionaldenominator"] = canonical::number(message->price_fractional_denominator.get());
            values[entry + ".payload.optionssymboldirectorymessage.priceminimumtick"] = canonical::number(message->price_minimum_tick.get());
            values[entry + ".payload.optionssymboldirectorymessage.strikepricedecimalposition"] = canonical::number(message->strike_price_decimal_position.get());
            values[entry + ".payload.optionssymboldirectorymessage.strikepricefractionaldenominator"] = canonical::number(message->strike_price_fractional_denominator.get());
            values[entry + ".payload.optionssymboldirectorymessage.strikepriceminimumtick"] = canonical::number(message->strike_price_minimum_tick.get());
            values[entry + ".payload.optionssymboldirectorymessage.lasttradingdate"] = canonical::number(message->last_trading_date.get());
            values[entry + ".payload.optionssymboldirectorymessage.priordaysettlement"] = canonical::scaled(message->prior_day_settlement.integer(), -2);
            values[entry + ".payload.optionssymboldirectorymessage.volatility"] = canonical::number(message->volatility.get());
            values[entry + ".payload.optionssymboldirectorymessage.currency"] = canonical::text(std::string(message->currency.get()), ' ', false);
            values[entry + ".payload.optionssymboldirectorymessage.lotsizeorfacevalue"] = canonical::number(message->lot_size_or_face_value.get());
            values[entry + ".payload.optionssymboldirectorymessage.maturityvalue"] = canonical::number(message->maturity_value.get());
            values[entry + ".payload.optionssymboldirectorymessage.couponrate"] = canonical::number(message->coupon_rate.get());
            values[entry + ".payload.optionssymboldirectorymessage.paymentsperyear"] = canonical::number(message->payments_per_year.get());
            values[entry + ".payload.optionssymboldirectorymessage.blocklotsize"] = canonical::number(message->block_lot_size.get());
            values[entry + ".payload.optionssymboldirectorymessage.expirydate"] = canonical::number(message->expiry_date.get());
            values[entry + ".payload.optionssymboldirectorymessage.basisofquotation"] = canonical::text(std::string(message->basis_of_quotation.get()), ' ', false);
        } else if (iterator.message_type == protocol::CombinationSymbolDirectoryMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.combinationsymboldirectorymessage";
            [[maybe_unused]] const auto* message = protocol::CombinationSymbolDirectoryMessage::parse(iterator.message);
            values[entry + ".payload.combinationsymboldirectorymessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.combinationsymboldirectorymessage.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.combinationsymboldirectorymessage.tradeableinstrumentid"] = canonical::number(message->tradeable_instrument_id.get());
            values[entry + ".payload.combinationsymboldirectorymessage.symbolname"] = canonical::text(std::string(message->symbol_name.get()), ' ', false);
            values[entry + ".payload.combinationsymboldirectorymessage.longname"] = canonical::text(std::string(message->long_name.get()), ' ', false);
            values[entry + ".payload.combinationsymboldirectorymessage.cficode"] = canonical::text(std::string(message->cfi_code.get()), ' ', false);
            values[entry + ".payload.combinationsymboldirectorymessage.pricemethod"] = canonical::number(message->price_method.get());
            values[entry + ".payload.combinationsymboldirectorymessage.pricedisplaydecimals"] = canonical::number(message->price_display_decimals.get());
            values[entry + ".payload.combinationsymboldirectorymessage.pricefractionaldenominator"] = canonical::number(message->price_fractional_denominator.get());
            values[entry + ".payload.combinationsymboldirectorymessage.priceminimumtick"] = canonical::number(message->price_minimum_tick.get());
            values[entry + ".payload.combinationsymboldirectorymessage.legs"] = canonical::number(message->legs.get());
        } else if (iterator.message_type == protocol::BundlesSymbolDirectory::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.bundlessymboldirectory";
            [[maybe_unused]] const auto* message = protocol::BundlesSymbolDirectory::parse(iterator.message);
            values[entry + ".payload.bundlessymboldirectory.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.bundlessymboldirectory.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.bundlessymboldirectory.tradeableinstrumentid"] = canonical::number(message->tradeable_instrument_id.get());
            values[entry + ".payload.bundlessymboldirectory.symbolname"] = canonical::text(std::string(message->symbol_name.get()), ' ', false);
            values[entry + ".payload.bundlessymboldirectory.longname"] = canonical::text(std::string(message->long_name.get()), ' ', false);
            values[entry + ".payload.bundlessymboldirectory.cficode"] = canonical::text(std::string(message->cfi_code.get()), ' ', false);
            values[entry + ".payload.bundlessymboldirectory.pricemethod"] = canonical::number(message->price_method.get());
            values[entry + ".payload.bundlessymboldirectory.pricedisplaydecimals"] = canonical::number(message->price_display_decimals.get());
            values[entry + ".payload.bundlessymboldirectory.pricefractionaldenominator"] = canonical::number(message->price_fractional_denominator.get());
            values[entry + ".payload.bundlessymboldirectory.priceminimumtick"] = canonical::number(message->price_minimum_tick.get());
            values[entry + ".payload.bundlessymboldirectory.legs"] = canonical::number(message->legs.get());
        } else if (iterator.message_type == protocol::OrderBookStateMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderbookstatemessage";
            [[maybe_unused]] const auto* message = protocol::OrderBookStateMessage::parse(iterator.message);
            values[entry + ".payload.orderbookstatemessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.orderbookstatemessage.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.orderbookstatemessage.tradeableinstrumentid"] = canonical::number(message->tradeable_instrument_id.get());
            values[entry + ".payload.orderbookstatemessage.sessionstate"] = canonical::text(canonical::character(message->session_state.get()), ' ', false);
        } else if (iterator.message_type == protocol::AddOrderMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.addordermessage";
            [[maybe_unused]] const auto* message = protocol::AddOrderMessage::parse(iterator.message);
            values[entry + ".payload.addordermessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.addordermessage.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.addordermessage.tradeableinstrumentid"] = canonical::number(message->tradeable_instrument_id.get());
            values[entry + ".payload.addordermessage.side"] = canonical::text(canonical::character(message->side.get()), ' ', false);
            values[entry + ".payload.addordermessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.addordermessage.orderbookpriority"] = canonical::number(message->order_book_priority.get());
            values[entry + ".payload.addordermessage.quantity"] = canonical::number(message->quantity.get());
            values[entry + ".payload.addordermessage.price"] = canonical::scaled(message->price.integer(), -2);
        } else if (iterator.message_type == protocol::OrderVolumeCancelledMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.ordervolumecancelledmessage";
            [[maybe_unused]] const auto* message = protocol::OrderVolumeCancelledMessage::parse(iterator.message);
            values[entry + ".payload.ordervolumecancelledmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.ordervolumecancelledmessage.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.ordervolumecancelledmessage.tradeableinstrumentid"] = canonical::number(message->tradeable_instrument_id.get());
            values[entry + ".payload.ordervolumecancelledmessage.side"] = canonical::text(canonical::character(message->side.get()), ' ', false);
            values[entry + ".payload.ordervolumecancelledmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.ordervolumecancelledmessage.quantity"] = canonical::number(message->quantity.get());
        } else if (iterator.message_type == protocol::OrderDeletedMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderdeletedmessage";
            [[maybe_unused]] const auto* message = protocol::OrderDeletedMessage::parse(iterator.message);
            values[entry + ".payload.orderdeletedmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.orderdeletedmessage.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.orderdeletedmessage.tradeableinstrumentid"] = canonical::number(message->tradeable_instrument_id.get());
            values[entry + ".payload.orderdeletedmessage.side"] = canonical::text(canonical::character(message->side.get()), ' ', false);
            values[entry + ".payload.orderdeletedmessage.orderid"] = canonical::number(message->order_id.get());
        } else if (iterator.message_type == protocol::OrderExecutedMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedmessage";
            [[maybe_unused]] const auto* message = protocol::OrderExecutedMessage::parse(iterator.message);
            values[entry + ".payload.orderexecutedmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.orderexecutedmessage.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.orderexecutedmessage.tradeableinstrumentid"] = canonical::number(message->tradeable_instrument_id.get());
            values[entry + ".payload.orderexecutedmessage.side"] = canonical::text(canonical::character(message->side.get()), ' ', false);
            values[entry + ".payload.orderexecutedmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.orderexecutedmessage.quantityremaining"] = canonical::number(message->quantity_remaining.get());
            values[entry + ".payload.orderexecutedmessage.tradetype"] = canonical::text(canonical::character(message->trade_type.get()), ' ', false);
            values[entry + ".payload.orderexecutedmessage.tradeid"] = canonical::number(message->trade_id.get());
            values[entry + ".payload.orderexecutedmessage.executedquantity"] = canonical::number(message->executed_quantity.get());
            values[entry + ".payload.orderexecutedmessage.tradeprice"] = canonical::scaled(message->trade_price.integer(), -2);
            values[entry + ".payload.orderexecutedmessage.combinationtradeid"] = canonical::number(message->combination_trade_id.get());
            values[entry + ".payload.orderexecutedmessage.counterpartyid"] = canonical::text(std::string(message->counter_party_id.get()), ' ', false);
        } else if (iterator.message_type == protocol::AuctionOrderExecutedMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.auctionorderexecutedmessage";
            [[maybe_unused]] const auto* message = protocol::AuctionOrderExecutedMessage::parse(iterator.message);
            values[entry + ".payload.auctionorderexecutedmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.auctionorderexecutedmessage.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.auctionorderexecutedmessage.tradeableinstrumentid"] = canonical::number(message->tradeable_instrument_id.get());
            values[entry + ".payload.auctionorderexecutedmessage.side"] = canonical::text(canonical::character(message->side.get()), ' ', false);
            values[entry + ".payload.auctionorderexecutedmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.auctionorderexecutedmessage.quantityremaining"] = canonical::number(message->quantity_remaining.get());
            values[entry + ".payload.auctionorderexecutedmessage.tradetype"] = canonical::text(canonical::character(message->trade_type.get()), ' ', false);
            values[entry + ".payload.auctionorderexecutedmessage.tradeid"] = canonical::number(message->trade_id.get());
            values[entry + ".payload.auctionorderexecutedmessage.executedquantity"] = canonical::number(message->executed_quantity.get());
            values[entry + ".payload.auctionorderexecutedmessage.tradeprice"] = canonical::scaled(message->trade_price.integer(), -2);
            values[entry + ".payload.auctionorderexecutedmessage.oppositeorderid"] = canonical::number(message->opposite_order_id.get());
        } else if (iterator.message_type == protocol::CombinationOrderExecutedMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.combinationorderexecutedmessage";
            [[maybe_unused]] const auto* message = protocol::CombinationOrderExecutedMessage::parse(iterator.message);
            values[entry + ".payload.combinationorderexecutedmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.combinationorderexecutedmessage.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.combinationorderexecutedmessage.tradeableinstrumentid"] = canonical::number(message->tradeable_instrument_id.get());
            values[entry + ".payload.combinationorderexecutedmessage.side"] = canonical::text(canonical::character(message->side.get()), ' ', false);
            values[entry + ".payload.combinationorderexecutedmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.combinationorderexecutedmessage.quantityremaining"] = canonical::number(message->quantity_remaining.get());
            values[entry + ".payload.combinationorderexecutedmessage.tradetype"] = canonical::text(canonical::character(message->trade_type.get()), ' ', false);
            values[entry + ".payload.combinationorderexecutedmessage.tradeid"] = canonical::number(message->trade_id.get());
            values[entry + ".payload.combinationorderexecutedmessage.executedquantity"] = canonical::number(message->executed_quantity.get());
            values[entry + ".payload.combinationorderexecutedmessage.tradeprice"] = canonical::scaled(message->trade_price.integer(), -2);
            values[entry + ".payload.combinationorderexecutedmessage.oppositetradeableinstrumentid"] = canonical::number(message->opposite_tradeable_instrument_id.get());
            values[entry + ".payload.combinationorderexecutedmessage.oppositeside"] = canonical::text(canonical::character(message->opposite_side.get()), ' ', false);
            values[entry + ".payload.combinationorderexecutedmessage.oppositeorderid"] = canonical::number(message->opposite_order_id.get());
            values[entry + ".payload.combinationorderexecutedmessage.combinationtradeid"] = canonical::number(message->combination_trade_id.get());
        } else if (iterator.message_type == protocol::ImpliedOrderAddedMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.impliedorderaddedmessage";
            [[maybe_unused]] const auto* message = protocol::ImpliedOrderAddedMessage::parse(iterator.message);
            values[entry + ".payload.impliedorderaddedmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.impliedorderaddedmessage.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.impliedorderaddedmessage.tradeableinstrumentid"] = canonical::number(message->tradeable_instrument_id.get());
            values[entry + ".payload.impliedorderaddedmessage.side"] = canonical::text(canonical::character(message->side.get()), ' ', false);
            values[entry + ".payload.impliedorderaddedmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.impliedorderaddedmessage.orderbookpriority"] = canonical::number(message->order_book_priority.get());
            values[entry + ".payload.impliedorderaddedmessage.quantity"] = canonical::number(message->quantity.get());
            values[entry + ".payload.impliedorderaddedmessage.price"] = canonical::scaled(message->price.integer(), -2);
        } else if (iterator.message_type == protocol::ImpliedOrderReplacedMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.impliedorderreplacedmessage";
            [[maybe_unused]] const auto* message = protocol::ImpliedOrderReplacedMessage::parse(iterator.message);
            values[entry + ".payload.impliedorderreplacedmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.impliedorderreplacedmessage.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.impliedorderreplacedmessage.tradeableinstrumentid"] = canonical::number(message->tradeable_instrument_id.get());
            values[entry + ".payload.impliedorderreplacedmessage.side"] = canonical::text(canonical::character(message->side.get()), ' ', false);
            values[entry + ".payload.impliedorderreplacedmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.impliedorderreplacedmessage.orderbookpriority"] = canonical::number(message->order_book_priority.get());
            values[entry + ".payload.impliedorderreplacedmessage.quantity"] = canonical::number(message->quantity.get());
            values[entry + ".payload.impliedorderreplacedmessage.price"] = canonical::scaled(message->price.integer(), -2);
        } else if (iterator.message_type == protocol::ImpliedOrderDeletedMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.impliedorderdeletedmessage";
            [[maybe_unused]] const auto* message = protocol::ImpliedOrderDeletedMessage::parse(iterator.message);
            values[entry + ".payload.impliedorderdeletedmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.impliedorderdeletedmessage.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.impliedorderdeletedmessage.tradeableinstrumentid"] = canonical::number(message->tradeable_instrument_id.get());
            values[entry + ".payload.impliedorderdeletedmessage.side"] = canonical::text(canonical::character(message->side.get()), ' ', false);
            values[entry + ".payload.impliedorderdeletedmessage.orderid"] = canonical::number(message->order_id.get());
        } else if (iterator.message_type == protocol::TradeExecutedMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.tradeexecutedmessage";
            [[maybe_unused]] const auto* message = protocol::TradeExecutedMessage::parse(iterator.message);
            values[entry + ".payload.tradeexecutedmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.tradeexecutedmessage.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.tradeexecutedmessage.tradeableinstrumentid"] = canonical::number(message->tradeable_instrument_id.get());
            values[entry + ".payload.tradeexecutedmessage.tradetype"] = canonical::text(canonical::character(message->trade_type.get()), ' ', false);
            values[entry + ".payload.tradeexecutedmessage.tradeid"] = canonical::number(message->trade_id.get());
            values[entry + ".payload.tradeexecutedmessage.executedquantity"] = canonical::number(message->executed_quantity.get());
            values[entry + ".payload.tradeexecutedmessage.tradeprice"] = canonical::scaled(message->trade_price.integer(), -2);
            values[entry + ".payload.tradeexecutedmessage.combinationtradeid"] = canonical::number(message->combination_trade_id.get());
            values[entry + ".payload.tradeexecutedmessage.participantidbuyer"] = canonical::text(std::string(message->participant_id_buyer.get()), ' ', false);
            values[entry + ".payload.tradeexecutedmessage.participantidseller"] = canonical::text(std::string(message->participant_id_seller.get()), ' ', false);
        } else if (iterator.message_type == protocol::CombinationTradeExecutedMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.combinationtradeexecutedmessage";
            [[maybe_unused]] const auto* message = protocol::CombinationTradeExecutedMessage::parse(iterator.message);
            values[entry + ".payload.combinationtradeexecutedmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.combinationtradeexecutedmessage.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.combinationtradeexecutedmessage.tradeableinstrumentid"] = canonical::number(message->tradeable_instrument_id.get());
            values[entry + ".payload.combinationtradeexecutedmessage.tradetype"] = canonical::text(canonical::character(message->trade_type.get()), ' ', false);
            values[entry + ".payload.combinationtradeexecutedmessage.tradeid"] = canonical::number(message->trade_id.get());
            values[entry + ".payload.combinationtradeexecutedmessage.executedquantity"] = canonical::number(message->executed_quantity.get());
            values[entry + ".payload.combinationtradeexecutedmessage.tradeprice"] = canonical::scaled(message->trade_price.integer(), -2);
            values[entry + ".payload.combinationtradeexecutedmessage.buyertradeableinstrumentid"] = canonical::number(message->buyer_tradeable_instrument_id.get());
            values[entry + ".payload.combinationtradeexecutedmessage.buyerside"] = canonical::text(canonical::character(message->buyer_side.get()), ' ', false);
            values[entry + ".payload.combinationtradeexecutedmessage.buyerorderid"] = canonical::number(message->buyer_order_id.get());
            values[entry + ".payload.combinationtradeexecutedmessage.buyercombinationtradeid"] = canonical::number(message->buyer_combination_trade_id.get());
            values[entry + ".payload.combinationtradeexecutedmessage.buyerparticipantid"] = canonical::text(std::string(message->buyer_participant_id.get()), ' ', false);
            values[entry + ".payload.combinationtradeexecutedmessage.sellertradeableinstrumentid"] = canonical::number(message->seller_tradeable_instrument_id.get());
            values[entry + ".payload.combinationtradeexecutedmessage.sellerside"] = canonical::text(canonical::character(message->seller_side.get()), ' ', false);
            values[entry + ".payload.combinationtradeexecutedmessage.sellerorderid"] = canonical::number(message->seller_order_id.get());
            values[entry + ".payload.combinationtradeexecutedmessage.sellercombinationtradeid"] = canonical::number(message->seller_combination_trade_id.get());
            values[entry + ".payload.combinationtradeexecutedmessage.sellerparticipantid"] = canonical::text(std::string(message->seller_participant_id.get()), ' ', false);
        } else if (iterator.message_type == protocol::TradeCancellationMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.tradecancellationmessage";
            [[maybe_unused]] const auto* message = protocol::TradeCancellationMessage::parse(iterator.message);
            values[entry + ".payload.tradecancellationmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.tradecancellationmessage.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.tradecancellationmessage.tradeableinstrumentid"] = canonical::number(message->tradeable_instrument_id.get());
            values[entry + ".payload.tradecancellationmessage.tradeid"] = canonical::number(message->trade_id.get());
        } else if (iterator.message_type == protocol::EquilibriumPriceMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.equilibriumpricemessage";
            [[maybe_unused]] const auto* message = protocol::EquilibriumPriceMessage::parse(iterator.message);
            values[entry + ".payload.equilibriumpricemessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.equilibriumpricemessage.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.equilibriumpricemessage.tradeableinstrumentid"] = canonical::number(message->tradeable_instrument_id.get());
            values[entry + ".payload.equilibriumpricemessage.equilibriumprice"] = canonical::scaled(message->equilibrium_price.integer(), -2);
            values[entry + ".payload.equilibriumpricemessage.matchedquantity"] = canonical::number(message->matched_quantity.get());
            values[entry + ".payload.equilibriumpricemessage.bidquantity"] = canonical::number(message->bid_quantity.get());
            values[entry + ".payload.equilibriumpricemessage.askquantity"] = canonical::number(message->ask_quantity.get());
        } else if (iterator.message_type == protocol::OpenHighLowLastTradeAdjustmentMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.openhighlowlasttradeadjustmentmessage";
            [[maybe_unused]] const auto* message = protocol::OpenHighLowLastTradeAdjustmentMessage::parse(iterator.message);
            values[entry + ".payload.openhighlowlasttradeadjustmentmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.openhighlowlasttradeadjustmentmessage.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.openhighlowlasttradeadjustmentmessage.tradeableinstrumentid"] = canonical::number(message->tradeable_instrument_id.get());
            values[entry + ".payload.openhighlowlasttradeadjustmentmessage.openingtrade"] = canonical::scaled(message->opening_trade.integer(), -2);
            values[entry + ".payload.openhighlowlasttradeadjustmentmessage.highesttrade"] = canonical::scaled(message->highest_trade.integer(), -2);
            values[entry + ".payload.openhighlowlasttradeadjustmentmessage.lowesttrade"] = canonical::scaled(message->lowest_trade.integer(), -2);
            values[entry + ".payload.openhighlowlasttradeadjustmentmessage.lasttrade"] = canonical::scaled(message->last_trade.integer(), -2);
            values[entry + ".payload.openhighlowlasttradeadjustmentmessage.lastvolume"] = canonical::number(message->last_volume.get());
            values[entry + ".payload.openhighlowlasttradeadjustmentmessage.totaltradedvolume"] = canonical::number(message->total_traded_volume.get());
        } else if (iterator.message_type == protocol::MarketSettlementMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.marketsettlementmessage";
            [[maybe_unused]] const auto* message = protocol::MarketSettlementMessage::parse(iterator.message);
            values[entry + ".payload.marketsettlementmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.marketsettlementmessage.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.marketsettlementmessage.tradeableinstrumentid"] = canonical::number(message->tradeable_instrument_id.get());
            values[entry + ".payload.marketsettlementmessage.openingtrade"] = canonical::scaled(message->opening_trade.integer(), -2);
            values[entry + ".payload.marketsettlementmessage.highesttrade"] = canonical::scaled(message->highest_trade.integer(), -2);
            values[entry + ".payload.marketsettlementmessage.lowesttrade"] = canonical::scaled(message->lowest_trade.integer(), -2);
            values[entry + ".payload.marketsettlementmessage.lasttrade"] = canonical::scaled(message->last_trade.integer(), -2);
            values[entry + ".payload.marketsettlementmessage.lastvolume"] = canonical::number(message->last_volume.get());
            values[entry + ".payload.marketsettlementmessage.totaltradedvolume"] = canonical::number(message->total_traded_volume.get());
        } else if (iterator.message_type == protocol::TextMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.textmessage";
            [[maybe_unused]] const auto* message = protocol::TextMessage::parse(iterator.message);
            values[entry + ".payload.textmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.textmessage.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.textmessage.sourceid"] = canonical::text(std::string(message->source_id.get()), ' ', false);
            values[entry + ".payload.textmessage.text"] = canonical::text(std::string(message->text.get()), ' ', false);
        } else if (iterator.message_type == protocol::RequestForQuoteMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.requestforquotemessage";
            [[maybe_unused]] const auto* message = protocol::RequestForQuoteMessage::parse(iterator.message);
            values[entry + ".payload.requestforquotemessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.requestforquotemessage.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.requestforquotemessage.tradeableinstrumentid"] = canonical::number(message->tradeable_instrument_id.get());
            values[entry + ".payload.requestforquotemessage.rfqside"] = canonical::text(canonical::character(message->rfq_side.get()), ' ', false);
            values[entry + ".payload.requestforquotemessage.quantity"] = canonical::number(message->quantity.get());
        } else if (iterator.message_type == protocol::AnomalousOrderThresholdPublishMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.anomalousorderthresholdpublishmessage";
            [[maybe_unused]] const auto* message = protocol::AnomalousOrderThresholdPublishMessage::parse(iterator.message);
            values[entry + ".payload.anomalousorderthresholdpublishmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.anomalousorderthresholdpublishmessage.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.anomalousorderthresholdpublishmessage.tradeableinstrumentid"] = canonical::number(message->tradeable_instrument_id.get());
            values[entry + ".payload.anomalousorderthresholdpublishmessage.aotprice"] = canonical::scaled(message->aot_price.integer(), -2);
            values[entry + ".payload.anomalousorderthresholdpublishmessage.aotupperprice"] = canonical::scaled(message->aot_upper_price.integer(), -2);
            values[entry + ".payload.anomalousorderthresholdpublishmessage.aotlowerprice"] = canonical::scaled(message->aot_lower_price.integer(), -2);
            values[entry + ".payload.anomalousorderthresholdpublishmessage.etrprice"] = canonical::scaled(message->etr_price.integer(), -2);
            values[entry + ".payload.anomalousorderthresholdpublishmessage.etrupperprice"] = canonical::scaled(message->etr_upper_price.integer(), -2);
            values[entry + ".payload.anomalousorderthresholdpublishmessage.etrlowerprice"] = canonical::scaled(message->etr_lower_price.integer(), -2);
        } else if (iterator.message_type == protocol::VolumeAndOpenInterestMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.volumeandopeninterestmessage";
            [[maybe_unused]] const auto* message = protocol::VolumeAndOpenInterestMessage::parse(iterator.message);
            values[entry + ".payload.volumeandopeninterestmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.volumeandopeninterestmessage.tradedate"] = canonical::number(message->trade_date.get());
            values[entry + ".payload.volumeandopeninterestmessage.tradeableinstrumentid"] = canonical::number(message->tradeable_instrument_id.get());
            values[entry + ".payload.volumeandopeninterestmessage.cumulativevolume"] = canonical::number(message->cumulative_volume.get());
            values[entry + ".payload.volumeandopeninterestmessage.openinterest"] = canonical::number(message->open_interest.get());
            values[entry + ".payload.volumeandopeninterestmessage.voitradedate"] = canonical::number(message->voi_trade_date.get());
        }
    }

    return values;
}

// Read each datagram of a sample with Modern and hold it to the model's values
int check(const char* name, const char* capture, const char* expected) {
    const char* packets = std::getenv("OMI_PACKETS_DIR");

    if (packets == nullptr) {
        std::printf("FAIL: OMI_PACKETS_DIR is not set\n");
        return 1;
    }

    const auto model = canonical::load(canonical::root() + "/" + expected);
    std::vector<std::pair<std::string, std::int64_t>> sources;
    sources.emplace_back(std::string{packets} + "/" + capture, 0);

    packet::PcapIterator captures(sources);
    std::size_t datagram = 0;
    int differences = 0;

    while (captures.advance()) {
        const packet::Frame frame(captures.data(), captures.length());

        if (!frame.valid() || !frame.is_udp()) { continue; }

        if (datagram >= model.size()) {
            std::printf("FAIL %s: more datagrams than the model read\n", name);
            return 1;
        }

        differences += canonical::compare(name, datagram, model[datagram], read(frame));
        ++datagram;
    }

    if (datagram != model.size()) {
        std::printf("FAIL %s: %zu datagrams, the model read %zu\n", name, datagram, model.size());
        return 1;
    }

    if (differences == 0) {
        std::printf("ok   %s: %zu datagrams\n", name, datagram);
    }

    return differences == 0 ? 0 : 1;
}

}

int main() {
    std::printf("== Asx.AsxDerivatives.Ntp.Itch.v1.05 (modern values)\n");
    int failures = 0;
    failures += check("AddOrderMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/AddOrderMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/AddOrderMessage.values");
    failures += check("AnomalousOrderThresholdPublishMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/AnomalousOrderThresholdPublishMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/AnomalousOrderThresholdPublishMessage.values");
    failures += check("AuctionOrderExecutedMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/AuctionOrderExecutedMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/AuctionOrderExecutedMessage.values");
    failures += check("CombinationOrderExecutedMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/CombinationOrderExecutedMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/CombinationOrderExecutedMessage.values");
    failures += check("CombinationSymbolDirectoryMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/CombinationSymbolDirectoryMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/CombinationSymbolDirectoryMessage.values");
    failures += check("CombinationTradeExecutedMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/CombinationTradeExecutedMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/CombinationTradeExecutedMessage.values");
    failures += check("EquilibriumPriceMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/EquilibriumPriceMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/EquilibriumPriceMessage.values");
    failures += check("FutureSymbolDirectoryMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/FutureSymbolDirectoryMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/FutureSymbolDirectoryMessage.values");
    failures += check("Heartbeat", "Asx/AsxDerivatives.Ntp.Itch.v1.05/Heartbeat.pcap", "asx/asxderivatives/ntp/itch/v1.05/Heartbeat.values");
    failures += check("ImpliedOrderAddedMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/ImpliedOrderAddedMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/ImpliedOrderAddedMessage.values");
    failures += check("ImpliedOrderDeletedMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/ImpliedOrderDeletedMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/ImpliedOrderDeletedMessage.values");
    failures += check("ImpliedOrderReplacedMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/ImpliedOrderReplacedMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/ImpliedOrderReplacedMessage.values");
    failures += check("OpenHighLowLastTradeAdjustmentMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/OpenHighLowLastTradeAdjustmentMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/OpenHighLowLastTradeAdjustmentMessage.values");
    failures += check("OptionsSymbolDirectoryMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/OptionsSymbolDirectoryMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/OptionsSymbolDirectoryMessage.values");
    failures += check("OrderBookStateMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/OrderBookStateMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/OrderBookStateMessage.values");
    failures += check("OrderDeletedMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/OrderDeletedMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/OrderDeletedMessage.values");
    failures += check("OrderExecutedMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/OrderExecutedMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/OrderExecutedMessage.values");
    failures += check("OrderVolumeCancelledMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/OrderVolumeCancelledMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/OrderVolumeCancelledMessage.values");
    failures += check("SecondsMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/SecondsMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/SecondsMessage.values");
    failures += check("TextMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/TextMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/TextMessage.values");
    failures += check("TradeExecutedMessage", "Asx/AsxDerivatives.Ntp.Itch.v1.05/TradeExecutedMessage.pcap", "asx/asxderivatives/ntp/itch/v1.05/TradeExecutedMessage.values");
    return failures == 0 ? 0 : 1;
}
