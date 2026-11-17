// Cboe.C1Options.Complex.Pitch.v2.1.18 canonical values, through the Advanced session layer: every value Advanced
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
#include "cpp/binary/advanced/cboe/c1options/complex/pitch/v2.1.18/messages/session.hpp"

namespace protocol = ::cboe::c1options::complex::pitch::v2_1_18;

namespace {

// The handler the session layer hands each datagram's values to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    protocol::seq_action on_transport_header(const protocol::packet_header& header, const packet::Frame&) {
        values["packet.packetheader.length"] = canonical::number(header.length.get().value());
        values["packet.packetheader.messagecount"] = canonical::number(header.message_count.get().value());
        values["packet.packetheader.unit"] = canonical::number(header.unit.get().value());
        values["packet.packetheader.sequence"] = canonical::number(header.sequence.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::packet_header&) {
        ++index;
    }

    void on_message(const protocol::time_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.timemessage";
        values[entry + ".payload.timemessage.time"] = canonical::number(message.fields.time.get().value());
    }

    void on_message(const protocol::unit_clear_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.unitclearmessage";
        values[entry + ".payload.unitclearmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
    }

    void on_message(const protocol::transaction_begin& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.transactionbegin";
        values[entry + ".payload.transactionbegin.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
    }

    void on_message(const protocol::transaction_end_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.transactionendmessage";
        values[entry + ".payload.transactionendmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
    }

    void on_message(const protocol::complex_instrument_definition_expanded_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.complexinstrumentdefinitionexpandedmessage";
        values[entry + ".payload.complexinstrumentdefinitionexpandedmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.complexinstrumentdefinitionexpandedmessage.complexinstrumentid"] = canonical::text(std::string(message.fields.complex_instrument_id.get().value()), ' ', false);
        values[entry + ".payload.complexinstrumentdefinitionexpandedmessage.complexinstrumentunderlying"] = canonical::text(std::string(message.fields.complex_instrument_underlying.get().value()), ' ', false);
        values[entry + ".payload.complexinstrumentdefinitionexpandedmessage.complexinstrumenttype"] = canonical::text(std::string(message.fields.complex_instrument_type.get().value()), ' ', false);
        values[entry + ".payload.complexinstrumentdefinitionexpandedmessage.legcount"] = canonical::number(message.fields.leg_count.get().value());
    }

    void on_message(const protocol::symbol_mapping_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.symbolmappingmessage";
        values[entry + ".payload.symbolmappingmessage.feedsymbol"] = canonical::text(std::string(message.fields.feed_symbol.get().value()), ' ', false);
        values[entry + ".payload.symbolmappingmessage.osisymbol"] = canonical::text(std::string(message.fields.osi_symbol.get().value()), ' ', false);
        values[entry + ".payload.symbolmappingmessage.symbolcondition"] = canonical::text(canonical::character(message.fields.symbol_condition.get().value()), ' ', false);
        values[entry + ".payload.symbolmappingmessage.underlying"] = canonical::text(std::string(message.fields.underlying.get().value()), ' ', false);
    }

    void on_message(const protocol::add_order_long_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.addorderlongmessage";
        values[entry + ".payload.addorderlongmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.addorderlongmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.addorderlongmessage.sideindicator"] = canonical::text(canonical::character(message.fields.side_indicator.get().value()), ' ', false);
        values[entry + ".payload.addorderlongmessage.quantity"] = canonical::number(message.fields.quantity.get().value());
        values[entry + ".payload.addorderlongmessage.complexinstrumentid"] = canonical::text(std::string(message.fields.complex_instrument_id.get().value()), ' ', false);
        values[entry + ".payload.addorderlongmessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
    }

    void on_message(const protocol::add_order_short_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.addordershortmessage";
        values[entry + ".payload.addordershortmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.addordershortmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.addordershortmessage.sideindicator"] = canonical::text(canonical::character(message.fields.side_indicator.get().value()), ' ', false);
        values[entry + ".payload.addordershortmessage.quantityshort"] = canonical::number(message.fields.quantity_short.get().value());
        values[entry + ".payload.addordershortmessage.complexinstrumentid"] = canonical::text(std::string(message.fields.complex_instrument_id.get().value()), ' ', false);
        values[entry + ".payload.addordershortmessage.priceshort"] = canonical::scaled(message.fields.price_short.get().value(), -2);
    }

    void on_message(const protocol::add_order_expanded_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.addorderexpandedmessage";
        values[entry + ".payload.addorderexpandedmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.addorderexpandedmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.addorderexpandedmessage.sideindicator"] = canonical::text(canonical::character(message.fields.side_indicator.get().value()), ' ', false);
        values[entry + ".payload.addorderexpandedmessage.quantity"] = canonical::number(message.fields.quantity.get().value());
        values[entry + ".payload.addorderexpandedmessage.complexinstrumentid8"] = canonical::text(std::string(message.fields.complex_instrument_id_8.get().value()), ' ', false);
        values[entry + ".payload.addorderexpandedmessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
        values[entry + ".payload.addorderexpandedmessage.participantid"] = canonical::text(std::string(message.fields.participant_id.get().value()), ' ', false);
        values[entry + ".payload.addorderexpandedmessage.customerindicator"] = canonical::text(canonical::character(message.fields.customer_indicator.get().value()), ' ', false);
        values[entry + ".payload.addorderexpandedmessage.clientid"] = canonical::text(std::string(message.fields.client_id.get().value()), ' ', false);
    }

    void on_message(const protocol::order_executed_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedmessage";
        values[entry + ".payload.orderexecutedmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.orderexecutedmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.orderexecutedmessage.executedquantity"] = canonical::number(message.fields.executed_quantity.get().value());
        values[entry + ".payload.orderexecutedmessage.executionid"] = canonical::number(message.fields.execution_id.get().value());
        values[entry + ".payload.orderexecutedmessage.tradecondition"] = canonical::text(canonical::character(message.fields.trade_condition.get().value()), ' ', false);
    }

    void on_message(const protocol::order_executed_at_price_size_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedatpricesizemessage";
        values[entry + ".payload.orderexecutedatpricesizemessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.orderexecutedatpricesizemessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.orderexecutedatpricesizemessage.executedquantity"] = canonical::number(message.fields.executed_quantity.get().value());
        values[entry + ".payload.orderexecutedatpricesizemessage.remainingquantity"] = canonical::number(message.fields.remaining_quantity.get().value());
        values[entry + ".payload.orderexecutedatpricesizemessage.executionid"] = canonical::number(message.fields.execution_id.get().value());
        values[entry + ".payload.orderexecutedatpricesizemessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
        values[entry + ".payload.orderexecutedatpricesizemessage.tradecondition"] = canonical::text(canonical::character(message.fields.trade_condition.get().value()), ' ', false);
    }

    void on_message(const protocol::reduce_size_long_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.reducesizelongmessage";
        values[entry + ".payload.reducesizelongmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.reducesizelongmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.reducesizelongmessage.canceledquantity"] = canonical::number(message.fields.canceled_quantity.get().value());
    }

    void on_message(const protocol::reduce_size_short_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.reducesizeshortmessage";
        values[entry + ".payload.reducesizeshortmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.reducesizeshortmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.reducesizeshortmessage.canceledquantityshort"] = canonical::number(message.fields.canceled_quantity_short.get().value());
    }

    void on_message(const protocol::modify_order_long_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.modifyorderlongmessage";
        values[entry + ".payload.modifyorderlongmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.modifyorderlongmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.modifyorderlongmessage.quantity"] = canonical::number(message.fields.quantity.get().value());
        values[entry + ".payload.modifyorderlongmessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
    }

    void on_message(const protocol::modify_order_short_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.modifyordershortmessage";
        values[entry + ".payload.modifyordershortmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.modifyordershortmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.modifyordershortmessage.quantityshort"] = canonical::number(message.fields.quantity_short.get().value());
        values[entry + ".payload.modifyordershortmessage.priceshort"] = canonical::scaled(message.fields.price_short.get().value(), -2);
    }

    void on_message(const protocol::delete_order_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.deleteordermessage";
        values[entry + ".payload.deleteordermessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.deleteordermessage.orderid"] = canonical::number(message.fields.order_id.get().value());
    }

    void on_message(const protocol::trade_long_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.tradelongmessage";
        values[entry + ".payload.tradelongmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.tradelongmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.tradelongmessage.sideindicator"] = canonical::text(canonical::character(message.fields.side_indicator.get().value()), ' ', false);
        values[entry + ".payload.tradelongmessage.quantity"] = canonical::number(message.fields.quantity.get().value());
        values[entry + ".payload.tradelongmessage.complexinstrumentid"] = canonical::text(std::string(message.fields.complex_instrument_id.get().value()), ' ', false);
        values[entry + ".payload.tradelongmessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
        values[entry + ".payload.tradelongmessage.executionid"] = canonical::number(message.fields.execution_id.get().value());
        values[entry + ".payload.tradelongmessage.tradecondition"] = canonical::text(canonical::character(message.fields.trade_condition.get().value()), ' ', false);
    }

    void on_message(const protocol::trade_short_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.tradeshortmessage";
        values[entry + ".payload.tradeshortmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.tradeshortmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.tradeshortmessage.sideindicator"] = canonical::text(canonical::character(message.fields.side_indicator.get().value()), ' ', false);
        values[entry + ".payload.tradeshortmessage.quantityshort"] = canonical::number(message.fields.quantity_short.get().value());
        values[entry + ".payload.tradeshortmessage.complexinstrumentid"] = canonical::text(std::string(message.fields.complex_instrument_id.get().value()), ' ', false);
        values[entry + ".payload.tradeshortmessage.priceshort"] = canonical::scaled(message.fields.price_short.get().value(), -2);
        values[entry + ".payload.tradeshortmessage.executionid"] = canonical::number(message.fields.execution_id.get().value());
        values[entry + ".payload.tradeshortmessage.tradecondition"] = canonical::text(canonical::character(message.fields.trade_condition.get().value()), ' ', false);
    }

    void on_message(const protocol::auction_notification_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.auctionnotificationmessage";
        values[entry + ".payload.auctionnotificationmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.auctionnotificationmessage.complexinstrumentid"] = canonical::text(std::string(message.fields.complex_instrument_id.get().value()), ' ', false);
        values[entry + ".payload.auctionnotificationmessage.auctionid"] = canonical::number(message.fields.auction_id.get().value());
        values[entry + ".payload.auctionnotificationmessage.auctiontype"] = canonical::text(canonical::character(message.fields.auction_type.get().value()), ' ', false);
        values[entry + ".payload.auctionnotificationmessage.sideindicator"] = canonical::text(canonical::character(message.fields.side_indicator.get().value()), ' ', false);
        values[entry + ".payload.auctionnotificationmessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
        values[entry + ".payload.auctionnotificationmessage.quantity"] = canonical::number(message.fields.quantity.get().value());
        values[entry + ".payload.auctionnotificationmessage.customerindicator"] = canonical::text(canonical::character(message.fields.customer_indicator.get().value()), ' ', false);
        values[entry + ".payload.auctionnotificationmessage.participantid"] = canonical::text(std::string(message.fields.participant_id.get().value()), ' ', false);
        values[entry + ".payload.auctionnotificationmessage.auctionendoffset"] = canonical::number(message.fields.auction_end_offset.get().value());
        values[entry + ".payload.auctionnotificationmessage.clientid"] = canonical::text(std::string(message.fields.client_id.get().value()), ' ', false);
    }

    void on_message(const protocol::auction_cancel_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.auctioncancelmessage";
        values[entry + ".payload.auctioncancelmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.auctioncancelmessage.auctionid"] = canonical::number(message.fields.auction_id.get().value());
    }

    void on_message(const protocol::auction_trade_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.auctiontrademessage";
        values[entry + ".payload.auctiontrademessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.auctiontrademessage.auctionid"] = canonical::number(message.fields.auction_id.get().value());
        values[entry + ".payload.auctiontrademessage.executionid"] = canonical::number(message.fields.execution_id.get().value());
        values[entry + ".payload.auctiontrademessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
        values[entry + ".payload.auctiontrademessage.quantity"] = canonical::number(message.fields.quantity.get().value());
    }

    void on_message(const protocol::trading_status_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.tradingstatusmessage";
        values[entry + ".payload.tradingstatusmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.tradingstatusmessage.complexsymbolid"] = canonical::text(std::string(message.fields.complex_symbol_id.get().value()), ' ', false);
        values[entry + ".payload.tradingstatusmessage.tradingstatus"] = canonical::text(canonical::character(message.fields.trading_status.get().value()), ' ', false);
        values[entry + ".payload.tradingstatusmessage.gthtradingstatus"] = canonical::text(canonical::character(message.fields.gth_trading_status.get().value()), ' ', false);
    }

    void on_message(const protocol::auction_update_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.auctionupdatemessage";
        values[entry + ".payload.auctionupdatemessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.auctionupdatemessage.complexinstrumentid8"] = canonical::text(std::string(message.fields.complex_instrument_id_8.get().value()), ' ', false);
        values[entry + ".payload.auctionupdatemessage.auctionopeningtype"] = canonical::text(canonical::character(message.fields.auction_opening_type.get().value()), ' ', false);
        values[entry + ".payload.auctionupdatemessage.referenceprice"] = canonical::scaled(message.fields.reference_price.get().value(), -4);
        values[entry + ".payload.auctionupdatemessage.buycontracts"] = canonical::number(message.fields.buy_contracts.get().value());
        values[entry + ".payload.auctionupdatemessage.sellcontracts"] = canonical::number(message.fields.sell_contracts.get().value());
        values[entry + ".payload.auctionupdatemessage.indicativeprice"] = canonical::scaled(message.fields.indicative_price.get().value(), -4);
        values[entry + ".payload.auctionupdatemessage.auctiononlyprice"] = canonical::scaled(message.fields.auction_only_price.get().value(), -4);
        values[entry + ".payload.auctionupdatemessage.openingcondition"] = canonical::text(canonical::character(message.fields.opening_condition.get().value()), ' ', false);
        values[entry + ".payload.auctionupdatemessage.compositemarketbidprice"] = canonical::scaled(message.fields.composite_market_bid_price.get().value(), -4);
        values[entry + ".payload.auctionupdatemessage.compositemarketofferprice"] = canonical::scaled(message.fields.composite_market_offer_price.get().value(), -4);
    }

    void on_message(const protocol::auction_summary_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.auctionsummarymessage";
        values[entry + ".payload.auctionsummarymessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
        values[entry + ".payload.auctionsummarymessage.complexinstrumentid8"] = canonical::text(std::string(message.fields.complex_instrument_id_8.get().value()), ' ', false);
        values[entry + ".payload.auctionsummarymessage.auctionopeningtype"] = canonical::text(canonical::character(message.fields.auction_opening_type.get().value()), ' ', false);
        values[entry + ".payload.auctionsummarymessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
        values[entry + ".payload.auctionsummarymessage.quantity"] = canonical::number(message.fields.quantity.get().value());
    }

    void on_message(const protocol::end_of_session_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.endofsessionmessage";
        values[entry + ".payload.endofsessionmessage.timeoffset"] = canonical::number(message.fields.time_offset.get().value());
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
    std::printf("== Cboe.C1Options.Complex.Pitch.v2.1.18 (advanced values)\n");
    int failures = 0;
    failures += check("AuctionCancelMessage", "Cboe/C1Options.Complex.Pitch.v2.1.18/AuctionCancelMessage.pcap", "cboe/c1options/complex/pitch/v2.1.18/AuctionCancelMessage.values");
    failures += check("AuctionNotificationMessage", "Cboe/C1Options.Complex.Pitch.v2.1.18/AuctionNotificationMessage.pcap", "cboe/c1options/complex/pitch/v2.1.18/AuctionNotificationMessage.values");
    failures += check("AuctionUpdateMessage", "Cboe/C1Options.Complex.Pitch.v2.1.18/AuctionUpdateMessage.pcap", "cboe/c1options/complex/pitch/v2.1.18/AuctionUpdateMessage.values");
    failures += check("ComplexInstrumentDefinitionExpandedMessage", "Cboe/C1Options.Complex.Pitch.v2.1.18/ComplexInstrumentDefinitionExpandedMessage.pcap", "cboe/c1options/complex/pitch/v2.1.18/ComplexInstrumentDefinitionExpandedMessage.values");
    failures += check("DeleteOrderMessage", "Cboe/C1Options.Complex.Pitch.v2.1.18/DeleteOrderMessage.pcap", "cboe/c1options/complex/pitch/v2.1.18/DeleteOrderMessage.values");
    failures += check("Heartbeat", "Cboe/C1Options.Complex.Pitch.v2.1.18/Heartbeat.pcap", "cboe/c1options/complex/pitch/v2.1.18/Heartbeat.values");
    failures += check("ModifyOrderShortMessage", "Cboe/C1Options.Complex.Pitch.v2.1.18/ModifyOrderShortMessage.pcap", "cboe/c1options/complex/pitch/v2.1.18/ModifyOrderShortMessage.values");
    failures += check("OrderExecutedMessage", "Cboe/C1Options.Complex.Pitch.v2.1.18/OrderExecutedMessage.pcap", "cboe/c1options/complex/pitch/v2.1.18/OrderExecutedMessage.values");
    failures += check("SymbolMappingMessage", "Cboe/C1Options.Complex.Pitch.v2.1.18/SymbolMappingMessage.pcap", "cboe/c1options/complex/pitch/v2.1.18/SymbolMappingMessage.values");
    failures += check("TimeMessage", "Cboe/C1Options.Complex.Pitch.v2.1.18/TimeMessage.pcap", "cboe/c1options/complex/pitch/v2.1.18/TimeMessage.values");
    return failures == 0 ? 0 : 1;
}
