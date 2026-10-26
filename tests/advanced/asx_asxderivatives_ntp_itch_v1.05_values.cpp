// Asx.AsxDerivatives.Ntp.Itch.v1.05 canonical values, through the Advanced session layer: every value Advanced
// reads from each sample, at its address, held to what the model reads.

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
#include "cpp/advanced/asx/asxderivatives/ntp/itch/v1.05/messages/session.hpp"

namespace protocol = ::asx::asxderivatives::ntp::itch::v1_05;

namespace {

// The handler the session layer hands each datagram's values to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    protocol::seq_action on_transport_header(const protocol::packet_header& header, const packet::Frame&) {
        values["packet.packetheader.session"] = canonical::text(std::string(header.session.get().value()), '\0', false);
        values["packet.packetheader.sequencenumber"] = canonical::number(header.sequence_number.get().value());
        values["packet.packetheader.messagecount"] = canonical::number(header.message_count.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::packet_header&) {
        ++index;
    }

    void on_message(const protocol::seconds_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.secondsmessage";
        values[entry + ".payload.secondsmessage.second"] = canonical::number(message.fields.second.get().value());
    }

    void on_message(const protocol::end_of_business_trade_date_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.endofbusinesstradedatemessage";
        values[entry + ".payload.endofbusinesstradedatemessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.endofbusinesstradedatemessage.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.endofbusinesstradedatemessage.eventcode"] = canonical::text(canonical::character(message.fields.event_code.get().value()), ' ', false);
    }

    void on_message(const protocol::future_symbol_directory_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.futuresymboldirectorymessage";
        values[entry + ".payload.futuresymboldirectorymessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.futuresymboldirectorymessage.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.futuresymboldirectorymessage.tradeableinstrumentid"] = canonical::number(message.fields.tradeable_instrument_id.get().value());
        values[entry + ".payload.futuresymboldirectorymessage.symbolname"] = canonical::text(std::string(message.fields.symbol_name.get().value()), ' ', false);
        values[entry + ".payload.futuresymboldirectorymessage.longname"] = canonical::text(std::string(message.fields.long_name.get().value()), ' ', false);
        values[entry + ".payload.futuresymboldirectorymessage.isin"] = canonical::text(std::string(message.fields.isin.get().value()), ' ', false);
        values[entry + ".payload.futuresymboldirectorymessage.exchange"] = canonical::text(std::string(message.fields.exchange.get().value()), ' ', false);
        values[entry + ".payload.futuresymboldirectorymessage.instrument"] = canonical::text(std::string(message.fields.instrument.get().value()), ' ', false);
        values[entry + ".payload.futuresymboldirectorymessage.cficode"] = canonical::text(std::string(message.fields.cfi_code.get().value()), ' ', false);
        values[entry + ".payload.futuresymboldirectorymessage.expiryyear"] = canonical::number(message.fields.expiry_year.get().value());
        values[entry + ".payload.futuresymboldirectorymessage.expirymonth"] = canonical::number(message.fields.expiry_month.get().value());
        values[entry + ".payload.futuresymboldirectorymessage.pricedisplaydecimals"] = canonical::number(message.fields.price_display_decimals.get().value());
        values[entry + ".payload.futuresymboldirectorymessage.pricefractionaldenominator"] = canonical::number(message.fields.price_fractional_denominator.get().value());
        values[entry + ".payload.futuresymboldirectorymessage.priceminimumtick"] = canonical::number(message.fields.price_minimum_tick.get().value());
        values[entry + ".payload.futuresymboldirectorymessage.lasttradingdate"] = canonical::number(message.fields.last_trading_date.get().value());
        values[entry + ".payload.futuresymboldirectorymessage.priordaysettlement"] = canonical::scaled(message.fields.prior_day_settlement.get().value(), -2);
        values[entry + ".payload.futuresymboldirectorymessage.currency"] = canonical::text(std::string(message.fields.currency.get().value()), ' ', false);
        values[entry + ".payload.futuresymboldirectorymessage.lotsizeorfacevalue"] = canonical::number(message.fields.lot_size_or_face_value.get().value());
        values[entry + ".payload.futuresymboldirectorymessage.maturityvalue"] = canonical::number(message.fields.maturity_value.get().value());
        values[entry + ".payload.futuresymboldirectorymessage.couponrate"] = canonical::number(message.fields.coupon_rate.get().value());
        values[entry + ".payload.futuresymboldirectorymessage.paymentsperyear"] = canonical::number(message.fields.payments_per_year.get().value());
        values[entry + ".payload.futuresymboldirectorymessage.blocklotsize"] = canonical::number(message.fields.block_lot_size.get().value());
        values[entry + ".payload.futuresymboldirectorymessage.expirydate"] = canonical::number(message.fields.expiry_date.get().value());
    }

    void on_message(const protocol::options_symbol_directory_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.optionssymboldirectorymessage";
        values[entry + ".payload.optionssymboldirectorymessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.optionssymboldirectorymessage.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.optionssymboldirectorymessage.tradeableinstrumentid"] = canonical::number(message.fields.tradeable_instrument_id.get().value());
        values[entry + ".payload.optionssymboldirectorymessage.symbolname"] = canonical::text(std::string(message.fields.symbol_name.get().value()), ' ', false);
        values[entry + ".payload.optionssymboldirectorymessage.longname"] = canonical::text(std::string(message.fields.long_name.get().value()), ' ', false);
        values[entry + ".payload.optionssymboldirectorymessage.isin"] = canonical::text(std::string(message.fields.isin.get().value()), ' ', false);
        values[entry + ".payload.optionssymboldirectorymessage.exchange"] = canonical::text(std::string(message.fields.exchange.get().value()), ' ', false);
        values[entry + ".payload.optionssymboldirectorymessage.instrument"] = canonical::text(std::string(message.fields.instrument.get().value()), ' ', false);
        values[entry + ".payload.optionssymboldirectorymessage.cficode"] = canonical::text(std::string(message.fields.cfi_code.get().value()), ' ', false);
        values[entry + ".payload.optionssymboldirectorymessage.expiryyear"] = canonical::number(message.fields.expiry_year.get().value());
        values[entry + ".payload.optionssymboldirectorymessage.expirymonth"] = canonical::number(message.fields.expiry_month.get().value());
        values[entry + ".payload.optionssymboldirectorymessage.optiontype"] = canonical::text(canonical::character(message.fields.option_type.get().value()), ' ', false);
        values[entry + ".payload.optionssymboldirectorymessage.strike"] = canonical::scaled(message.fields.strike.get().value(), -2);
        values[entry + ".payload.optionssymboldirectorymessage.underlyingtradeableinstrumentid"] = canonical::number(message.fields.underlying_tradeable_instrument_id.get().value());
        values[entry + ".payload.optionssymboldirectorymessage.pricedisplaydecimals"] = canonical::number(message.fields.price_display_decimals.get().value());
        values[entry + ".payload.optionssymboldirectorymessage.pricefractionaldenominator"] = canonical::number(message.fields.price_fractional_denominator.get().value());
        values[entry + ".payload.optionssymboldirectorymessage.priceminimumtick"] = canonical::number(message.fields.price_minimum_tick.get().value());
        values[entry + ".payload.optionssymboldirectorymessage.strikepricedecimalposition"] = canonical::number(message.fields.strike_price_decimal_position.get().value());
        values[entry + ".payload.optionssymboldirectorymessage.strikepricefractionaldenominator"] = canonical::number(message.fields.strike_price_fractional_denominator.get().value());
        values[entry + ".payload.optionssymboldirectorymessage.strikepriceminimumtick"] = canonical::number(message.fields.strike_price_minimum_tick.get().value());
        values[entry + ".payload.optionssymboldirectorymessage.lasttradingdate"] = canonical::number(message.fields.last_trading_date.get().value());
        values[entry + ".payload.optionssymboldirectorymessage.priordaysettlement"] = canonical::scaled(message.fields.prior_day_settlement.get().value(), -2);
        values[entry + ".payload.optionssymboldirectorymessage.volatility"] = canonical::number(message.fields.volatility.get().value());
        values[entry + ".payload.optionssymboldirectorymessage.currency"] = canonical::text(std::string(message.fields.currency.get().value()), ' ', false);
        values[entry + ".payload.optionssymboldirectorymessage.lotsizeorfacevalue"] = canonical::number(message.fields.lot_size_or_face_value.get().value());
        values[entry + ".payload.optionssymboldirectorymessage.maturityvalue"] = canonical::number(message.fields.maturity_value.get().value());
        values[entry + ".payload.optionssymboldirectorymessage.couponrate"] = canonical::number(message.fields.coupon_rate.get().value());
        values[entry + ".payload.optionssymboldirectorymessage.paymentsperyear"] = canonical::number(message.fields.payments_per_year.get().value());
        values[entry + ".payload.optionssymboldirectorymessage.blocklotsize"] = canonical::number(message.fields.block_lot_size.get().value());
        values[entry + ".payload.optionssymboldirectorymessage.expirydate"] = canonical::number(message.fields.expiry_date.get().value());
        values[entry + ".payload.optionssymboldirectorymessage.basisofquotation"] = canonical::text(std::string(message.fields.basis_of_quotation.get().value()), ' ', false);
    }

    void on_message(const protocol::combination_symbol_directory_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.combinationsymboldirectorymessage";
        values[entry + ".payload.combinationsymboldirectorymessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.combinationsymboldirectorymessage.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.combinationsymboldirectorymessage.tradeableinstrumentid"] = canonical::number(message.fields.tradeable_instrument_id.get().value());
        values[entry + ".payload.combinationsymboldirectorymessage.symbolname"] = canonical::text(std::string(message.fields.symbol_name.get().value()), ' ', false);
        values[entry + ".payload.combinationsymboldirectorymessage.longname"] = canonical::text(std::string(message.fields.long_name.get().value()), ' ', false);
        values[entry + ".payload.combinationsymboldirectorymessage.cficode"] = canonical::text(std::string(message.fields.cfi_code.get().value()), ' ', false);
        values[entry + ".payload.combinationsymboldirectorymessage.pricemethod"] = canonical::number(message.fields.price_method.get().value());
        values[entry + ".payload.combinationsymboldirectorymessage.pricedisplaydecimals"] = canonical::number(message.fields.price_display_decimals.get().value());
        values[entry + ".payload.combinationsymboldirectorymessage.pricefractionaldenominator"] = canonical::number(message.fields.price_fractional_denominator.get().value());
        values[entry + ".payload.combinationsymboldirectorymessage.priceminimumtick"] = canonical::number(message.fields.price_minimum_tick.get().value());
        values[entry + ".payload.combinationsymboldirectorymessage.legs"] = canonical::number(message.fields.legs.get().value());
    }

    void on_message(const protocol::bundles_symbol_directory& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.bundlessymboldirectory";
        values[entry + ".payload.bundlessymboldirectory.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.bundlessymboldirectory.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.bundlessymboldirectory.tradeableinstrumentid"] = canonical::number(message.fields.tradeable_instrument_id.get().value());
        values[entry + ".payload.bundlessymboldirectory.symbolname"] = canonical::text(std::string(message.fields.symbol_name.get().value()), ' ', false);
        values[entry + ".payload.bundlessymboldirectory.longname"] = canonical::text(std::string(message.fields.long_name.get().value()), ' ', false);
        values[entry + ".payload.bundlessymboldirectory.cficode"] = canonical::text(std::string(message.fields.cfi_code.get().value()), ' ', false);
        values[entry + ".payload.bundlessymboldirectory.pricemethod"] = canonical::number(message.fields.price_method.get().value());
        values[entry + ".payload.bundlessymboldirectory.pricedisplaydecimals"] = canonical::number(message.fields.price_display_decimals.get().value());
        values[entry + ".payload.bundlessymboldirectory.pricefractionaldenominator"] = canonical::number(message.fields.price_fractional_denominator.get().value());
        values[entry + ".payload.bundlessymboldirectory.priceminimumtick"] = canonical::number(message.fields.price_minimum_tick.get().value());
        values[entry + ".payload.bundlessymboldirectory.legs"] = canonical::number(message.fields.legs.get().value());
    }

    void on_message(const protocol::order_book_state_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.orderbookstatemessage";
        values[entry + ".payload.orderbookstatemessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.orderbookstatemessage.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.orderbookstatemessage.tradeableinstrumentid"] = canonical::number(message.fields.tradeable_instrument_id.get().value());
        values[entry + ".payload.orderbookstatemessage.sessionstate"] = canonical::text(canonical::character(message.fields.session_state.get().value()), ' ', false);
    }

    void on_message(const protocol::add_order_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.addordermessage";
        values[entry + ".payload.addordermessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.addordermessage.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.addordermessage.tradeableinstrumentid"] = canonical::number(message.fields.tradeable_instrument_id.get().value());
        values[entry + ".payload.addordermessage.side"] = canonical::text(canonical::character(message.fields.side.get().value()), ' ', false);
        values[entry + ".payload.addordermessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.addordermessage.orderbookpriority"] = canonical::number(message.fields.order_book_priority.get().value());
        values[entry + ".payload.addordermessage.quantity"] = canonical::number(message.fields.quantity.get().value());
        values[entry + ".payload.addordermessage.price"] = canonical::scaled(message.fields.price.get().value(), -2);
    }

    void on_message(const protocol::order_volume_cancelled_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.ordervolumecancelledmessage";
        values[entry + ".payload.ordervolumecancelledmessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.ordervolumecancelledmessage.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.ordervolumecancelledmessage.tradeableinstrumentid"] = canonical::number(message.fields.tradeable_instrument_id.get().value());
        values[entry + ".payload.ordervolumecancelledmessage.side"] = canonical::text(canonical::character(message.fields.side.get().value()), ' ', false);
        values[entry + ".payload.ordervolumecancelledmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.ordervolumecancelledmessage.quantity"] = canonical::number(message.fields.quantity.get().value());
    }

    void on_message(const protocol::order_deleted_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.orderdeletedmessage";
        values[entry + ".payload.orderdeletedmessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.orderdeletedmessage.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.orderdeletedmessage.tradeableinstrumentid"] = canonical::number(message.fields.tradeable_instrument_id.get().value());
        values[entry + ".payload.orderdeletedmessage.side"] = canonical::text(canonical::character(message.fields.side.get().value()), ' ', false);
        values[entry + ".payload.orderdeletedmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
    }

    void on_message(const protocol::order_executed_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedmessage";
        values[entry + ".payload.orderexecutedmessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.orderexecutedmessage.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.orderexecutedmessage.tradeableinstrumentid"] = canonical::number(message.fields.tradeable_instrument_id.get().value());
        values[entry + ".payload.orderexecutedmessage.side"] = canonical::text(canonical::character(message.fields.side.get().value()), ' ', false);
        values[entry + ".payload.orderexecutedmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.orderexecutedmessage.quantityremaining"] = canonical::number(message.fields.quantity_remaining.get().value());
        values[entry + ".payload.orderexecutedmessage.tradetype"] = canonical::text(canonical::character(message.fields.trade_type.get().value()), ' ', false);
        values[entry + ".payload.orderexecutedmessage.tradeid"] = canonical::number(message.fields.trade_id.get().value());
        values[entry + ".payload.orderexecutedmessage.executedquantity"] = canonical::number(message.fields.executed_quantity.get().value());
        values[entry + ".payload.orderexecutedmessage.tradeprice"] = canonical::scaled(message.fields.trade_price.get().value(), -2);
        values[entry + ".payload.orderexecutedmessage.combinationtradeid"] = canonical::number(message.fields.combination_trade_id.get().value());
        values[entry + ".payload.orderexecutedmessage.counterpartyid"] = canonical::text(std::string(message.fields.counter_party_id.get().value()), ' ', false);
    }

    void on_message(const protocol::auction_order_executed_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.auctionorderexecutedmessage";
        values[entry + ".payload.auctionorderexecutedmessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.auctionorderexecutedmessage.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.auctionorderexecutedmessage.tradeableinstrumentid"] = canonical::number(message.fields.tradeable_instrument_id.get().value());
        values[entry + ".payload.auctionorderexecutedmessage.side"] = canonical::text(canonical::character(message.fields.side.get().value()), ' ', false);
        values[entry + ".payload.auctionorderexecutedmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.auctionorderexecutedmessage.quantityremaining"] = canonical::number(message.fields.quantity_remaining.get().value());
        values[entry + ".payload.auctionorderexecutedmessage.tradetype"] = canonical::text(canonical::character(message.fields.trade_type.get().value()), ' ', false);
        values[entry + ".payload.auctionorderexecutedmessage.tradeid"] = canonical::number(message.fields.trade_id.get().value());
        values[entry + ".payload.auctionorderexecutedmessage.executedquantity"] = canonical::number(message.fields.executed_quantity.get().value());
        values[entry + ".payload.auctionorderexecutedmessage.tradeprice"] = canonical::scaled(message.fields.trade_price.get().value(), -2);
        values[entry + ".payload.auctionorderexecutedmessage.oppositeorderid"] = canonical::number(message.fields.opposite_order_id.get().value());
    }

    void on_message(const protocol::combination_order_executed_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.combinationorderexecutedmessage";
        values[entry + ".payload.combinationorderexecutedmessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.combinationorderexecutedmessage.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.combinationorderexecutedmessage.tradeableinstrumentid"] = canonical::number(message.fields.tradeable_instrument_id.get().value());
        values[entry + ".payload.combinationorderexecutedmessage.side"] = canonical::text(canonical::character(message.fields.side.get().value()), ' ', false);
        values[entry + ".payload.combinationorderexecutedmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.combinationorderexecutedmessage.quantityremaining"] = canonical::number(message.fields.quantity_remaining.get().value());
        values[entry + ".payload.combinationorderexecutedmessage.tradetype"] = canonical::text(canonical::character(message.fields.trade_type.get().value()), ' ', false);
        values[entry + ".payload.combinationorderexecutedmessage.tradeid"] = canonical::number(message.fields.trade_id.get().value());
        values[entry + ".payload.combinationorderexecutedmessage.executedquantity"] = canonical::number(message.fields.executed_quantity.get().value());
        values[entry + ".payload.combinationorderexecutedmessage.tradeprice"] = canonical::scaled(message.fields.trade_price.get().value(), -2);
        values[entry + ".payload.combinationorderexecutedmessage.oppositetradeableinstrumentid"] = canonical::number(message.fields.opposite_tradeable_instrument_id.get().value());
        values[entry + ".payload.combinationorderexecutedmessage.oppositeside"] = canonical::text(canonical::character(message.fields.opposite_side.get().value()), ' ', false);
        values[entry + ".payload.combinationorderexecutedmessage.oppositeorderid"] = canonical::number(message.fields.opposite_order_id.get().value());
        values[entry + ".payload.combinationorderexecutedmessage.combinationtradeid"] = canonical::number(message.fields.combination_trade_id.get().value());
    }

    void on_message(const protocol::implied_order_added_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.impliedorderaddedmessage";
        values[entry + ".payload.impliedorderaddedmessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.impliedorderaddedmessage.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.impliedorderaddedmessage.tradeableinstrumentid"] = canonical::number(message.fields.tradeable_instrument_id.get().value());
        values[entry + ".payload.impliedorderaddedmessage.side"] = canonical::text(canonical::character(message.fields.side.get().value()), ' ', false);
        values[entry + ".payload.impliedorderaddedmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.impliedorderaddedmessage.orderbookpriority"] = canonical::number(message.fields.order_book_priority.get().value());
        values[entry + ".payload.impliedorderaddedmessage.quantity"] = canonical::number(message.fields.quantity.get().value());
        values[entry + ".payload.impliedorderaddedmessage.price"] = canonical::scaled(message.fields.price.get().value(), -2);
    }

    void on_message(const protocol::implied_order_replaced_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.impliedorderreplacedmessage";
        values[entry + ".payload.impliedorderreplacedmessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.impliedorderreplacedmessage.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.impliedorderreplacedmessage.tradeableinstrumentid"] = canonical::number(message.fields.tradeable_instrument_id.get().value());
        values[entry + ".payload.impliedorderreplacedmessage.side"] = canonical::text(canonical::character(message.fields.side.get().value()), ' ', false);
        values[entry + ".payload.impliedorderreplacedmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.impliedorderreplacedmessage.orderbookpriority"] = canonical::number(message.fields.order_book_priority.get().value());
        values[entry + ".payload.impliedorderreplacedmessage.quantity"] = canonical::number(message.fields.quantity.get().value());
        values[entry + ".payload.impliedorderreplacedmessage.price"] = canonical::scaled(message.fields.price.get().value(), -2);
    }

    void on_message(const protocol::implied_order_deleted_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.impliedorderdeletedmessage";
        values[entry + ".payload.impliedorderdeletedmessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.impliedorderdeletedmessage.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.impliedorderdeletedmessage.tradeableinstrumentid"] = canonical::number(message.fields.tradeable_instrument_id.get().value());
        values[entry + ".payload.impliedorderdeletedmessage.side"] = canonical::text(canonical::character(message.fields.side.get().value()), ' ', false);
        values[entry + ".payload.impliedorderdeletedmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
    }

    void on_message(const protocol::trade_executed_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.tradeexecutedmessage";
        values[entry + ".payload.tradeexecutedmessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.tradeexecutedmessage.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.tradeexecutedmessage.tradeableinstrumentid"] = canonical::number(message.fields.tradeable_instrument_id.get().value());
        values[entry + ".payload.tradeexecutedmessage.tradetype"] = canonical::text(canonical::character(message.fields.trade_type.get().value()), ' ', false);
        values[entry + ".payload.tradeexecutedmessage.tradeid"] = canonical::number(message.fields.trade_id.get().value());
        values[entry + ".payload.tradeexecutedmessage.executedquantity"] = canonical::number(message.fields.executed_quantity.get().value());
        values[entry + ".payload.tradeexecutedmessage.tradeprice"] = canonical::scaled(message.fields.trade_price.get().value(), -2);
        values[entry + ".payload.tradeexecutedmessage.combinationtradeid"] = canonical::number(message.fields.combination_trade_id.get().value());
        values[entry + ".payload.tradeexecutedmessage.participantidbuyer"] = canonical::text(std::string(message.fields.participant_id_buyer.get().value()), ' ', false);
        values[entry + ".payload.tradeexecutedmessage.participantidseller"] = canonical::text(std::string(message.fields.participant_id_seller.get().value()), ' ', false);
    }

    void on_message(const protocol::combination_trade_executed_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.combinationtradeexecutedmessage";
        values[entry + ".payload.combinationtradeexecutedmessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.combinationtradeexecutedmessage.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.combinationtradeexecutedmessage.tradeableinstrumentid"] = canonical::number(message.fields.tradeable_instrument_id.get().value());
        values[entry + ".payload.combinationtradeexecutedmessage.tradetype"] = canonical::text(canonical::character(message.fields.trade_type.get().value()), ' ', false);
        values[entry + ".payload.combinationtradeexecutedmessage.tradeid"] = canonical::number(message.fields.trade_id.get().value());
        values[entry + ".payload.combinationtradeexecutedmessage.executedquantity"] = canonical::number(message.fields.executed_quantity.get().value());
        values[entry + ".payload.combinationtradeexecutedmessage.tradeprice"] = canonical::scaled(message.fields.trade_price.get().value(), -2);
        values[entry + ".payload.combinationtradeexecutedmessage.buyertradeableinstrumentid"] = canonical::number(message.fields.buyer_tradeable_instrument_id.get().value());
        values[entry + ".payload.combinationtradeexecutedmessage.buyerside"] = canonical::text(canonical::character(message.fields.buyer_side.get().value()), ' ', false);
        values[entry + ".payload.combinationtradeexecutedmessage.buyerorderid"] = canonical::number(message.fields.buyer_order_id.get().value());
        values[entry + ".payload.combinationtradeexecutedmessage.buyercombinationtradeid"] = canonical::number(message.fields.buyer_combination_trade_id.get().value());
        values[entry + ".payload.combinationtradeexecutedmessage.buyerparticipantid"] = canonical::text(std::string(message.fields.buyer_participant_id.get().value()), ' ', false);
        values[entry + ".payload.combinationtradeexecutedmessage.sellertradeableinstrumentid"] = canonical::number(message.fields.seller_tradeable_instrument_id.get().value());
        values[entry + ".payload.combinationtradeexecutedmessage.sellerside"] = canonical::text(canonical::character(message.fields.seller_side.get().value()), ' ', false);
        values[entry + ".payload.combinationtradeexecutedmessage.sellerorderid"] = canonical::number(message.fields.seller_order_id.get().value());
        values[entry + ".payload.combinationtradeexecutedmessage.sellercombinationtradeid"] = canonical::number(message.fields.seller_combination_trade_id.get().value());
        values[entry + ".payload.combinationtradeexecutedmessage.sellerparticipantid"] = canonical::text(std::string(message.fields.seller_participant_id.get().value()), ' ', false);
    }

    void on_message(const protocol::trade_cancellation_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.tradecancellationmessage";
        values[entry + ".payload.tradecancellationmessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.tradecancellationmessage.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.tradecancellationmessage.tradeableinstrumentid"] = canonical::number(message.fields.tradeable_instrument_id.get().value());
        values[entry + ".payload.tradecancellationmessage.tradeid"] = canonical::number(message.fields.trade_id.get().value());
    }

    void on_message(const protocol::equilibrium_price_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.equilibriumpricemessage";
        values[entry + ".payload.equilibriumpricemessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.equilibriumpricemessage.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.equilibriumpricemessage.tradeableinstrumentid"] = canonical::number(message.fields.tradeable_instrument_id.get().value());
        values[entry + ".payload.equilibriumpricemessage.equilibriumprice"] = canonical::scaled(message.fields.equilibrium_price.get().value(), -2);
        values[entry + ".payload.equilibriumpricemessage.matchedquantity"] = canonical::number(message.fields.matched_quantity.get().value());
        values[entry + ".payload.equilibriumpricemessage.bidquantity"] = canonical::number(message.fields.bid_quantity.get().value());
        values[entry + ".payload.equilibriumpricemessage.askquantity"] = canonical::number(message.fields.ask_quantity.get().value());
    }

    void on_message(const protocol::open_high_low_last_trade_adjustment_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.openhighlowlasttradeadjustmentmessage";
        values[entry + ".payload.openhighlowlasttradeadjustmentmessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.openhighlowlasttradeadjustmentmessage.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.openhighlowlasttradeadjustmentmessage.tradeableinstrumentid"] = canonical::number(message.fields.tradeable_instrument_id.get().value());
        values[entry + ".payload.openhighlowlasttradeadjustmentmessage.openingtrade"] = canonical::scaled(message.fields.opening_trade.get().value(), -2);
        values[entry + ".payload.openhighlowlasttradeadjustmentmessage.highesttrade"] = canonical::scaled(message.fields.highest_trade.get().value(), -2);
        values[entry + ".payload.openhighlowlasttradeadjustmentmessage.lowesttrade"] = canonical::scaled(message.fields.lowest_trade.get().value(), -2);
        values[entry + ".payload.openhighlowlasttradeadjustmentmessage.lasttrade"] = canonical::scaled(message.fields.last_trade.get().value(), -2);
        values[entry + ".payload.openhighlowlasttradeadjustmentmessage.lastvolume"] = canonical::number(message.fields.last_volume.get().value());
        values[entry + ".payload.openhighlowlasttradeadjustmentmessage.totaltradedvolume"] = canonical::number(message.fields.total_traded_volume.get().value());
    }

    void on_message(const protocol::market_settlement_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.marketsettlementmessage";
        values[entry + ".payload.marketsettlementmessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.marketsettlementmessage.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.marketsettlementmessage.tradeableinstrumentid"] = canonical::number(message.fields.tradeable_instrument_id.get().value());
        values[entry + ".payload.marketsettlementmessage.openingtrade"] = canonical::scaled(message.fields.opening_trade.get().value(), -2);
        values[entry + ".payload.marketsettlementmessage.highesttrade"] = canonical::scaled(message.fields.highest_trade.get().value(), -2);
        values[entry + ".payload.marketsettlementmessage.lowesttrade"] = canonical::scaled(message.fields.lowest_trade.get().value(), -2);
        values[entry + ".payload.marketsettlementmessage.lasttrade"] = canonical::scaled(message.fields.last_trade.get().value(), -2);
        values[entry + ".payload.marketsettlementmessage.lastvolume"] = canonical::number(message.fields.last_volume.get().value());
        values[entry + ".payload.marketsettlementmessage.totaltradedvolume"] = canonical::number(message.fields.total_traded_volume.get().value());
    }

    void on_message(const protocol::text_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.textmessage";
        values[entry + ".payload.textmessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.textmessage.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.textmessage.sourceid"] = canonical::text(std::string(message.fields.source_id.get().value()), ' ', false);
        values[entry + ".payload.textmessage.text"] = canonical::text(std::string(message.fields.text.get().value()), ' ', false);
    }

    void on_message(const protocol::request_for_quote_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.requestforquotemessage";
        values[entry + ".payload.requestforquotemessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.requestforquotemessage.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.requestforquotemessage.tradeableinstrumentid"] = canonical::number(message.fields.tradeable_instrument_id.get().value());
        values[entry + ".payload.requestforquotemessage.rfqside"] = canonical::text(canonical::character(message.fields.rfq_side.get().value()), ' ', false);
        values[entry + ".payload.requestforquotemessage.quantity"] = canonical::number(message.fields.quantity.get().value());
    }

    void on_message(const protocol::anomalous_order_threshold_publish_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.anomalousorderthresholdpublishmessage";
        values[entry + ".payload.anomalousorderthresholdpublishmessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.anomalousorderthresholdpublishmessage.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.anomalousorderthresholdpublishmessage.tradeableinstrumentid"] = canonical::number(message.fields.tradeable_instrument_id.get().value());
        values[entry + ".payload.anomalousorderthresholdpublishmessage.aotprice"] = canonical::scaled(message.fields.aot_price.get().value(), -2);
        values[entry + ".payload.anomalousorderthresholdpublishmessage.aotupperprice"] = canonical::scaled(message.fields.aot_upper_price.get().value(), -2);
        values[entry + ".payload.anomalousorderthresholdpublishmessage.aotlowerprice"] = canonical::scaled(message.fields.aot_lower_price.get().value(), -2);
        values[entry + ".payload.anomalousorderthresholdpublishmessage.etrprice"] = canonical::scaled(message.fields.etr_price.get().value(), -2);
        values[entry + ".payload.anomalousorderthresholdpublishmessage.etrupperprice"] = canonical::scaled(message.fields.etr_upper_price.get().value(), -2);
        values[entry + ".payload.anomalousorderthresholdpublishmessage.etrlowerprice"] = canonical::scaled(message.fields.etr_lower_price.get().value(), -2);
    }

    void on_message(const protocol::volume_and_open_interest_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.volumeandopeninterestmessage";
        values[entry + ".payload.volumeandopeninterestmessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.volumeandopeninterestmessage.tradedate"] = canonical::number(message.fields.trade_date.get().value());
        values[entry + ".payload.volumeandopeninterestmessage.tradeableinstrumentid"] = canonical::number(message.fields.tradeable_instrument_id.get().value());
        values[entry + ".payload.volumeandopeninterestmessage.cumulativevolume"] = canonical::number(message.fields.cumulative_volume.get().value());
        values[entry + ".payload.volumeandopeninterestmessage.openinterest"] = canonical::number(message.fields.open_interest.get().value());
        values[entry + ".payload.volumeandopeninterestmessage.voitradedate"] = canonical::number(message.fields.voi_trade_date.get().value());
    }
};

// The values Advanced reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    Reader reader;
    protocol::process_segment(reader, frame.payload, frame.payload_len, 0, frame);
    return reader.values;
}

// Read each datagram of a sample with Advanced and hold it to the model's values
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
    std::printf("== Asx.AsxDerivatives.Ntp.Itch.v1.05 (advanced values)\n");
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