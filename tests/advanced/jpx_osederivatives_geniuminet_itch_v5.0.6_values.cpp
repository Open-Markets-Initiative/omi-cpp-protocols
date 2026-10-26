// Jpx.OseDerivatives.GeniumInet.Itch.v5.0.6 canonical values, through the Advanced session layer: every value Advanced
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
#include "cpp/advanced/jpx/osederivatives/geniuminet/itch/v5.0.6/messages/session.hpp"

namespace protocol = ::jpx::osederivatives::geniuminet::itch::v5_0_6;

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
        values[entry + ".payload.secondsmessage.seconds"] = canonical::number(message.fields.seconds.get().value());
    }

    void on_message(const protocol::order_book_directory& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.orderbookdirectory";
        values[entry + ".payload.orderbookdirectory.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.orderbookdirectory.orderbookid"] = canonical::number(message.fields.order_book_id.get().value());
        values[entry + ".payload.orderbookdirectory.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), ' ', false);
        values[entry + ".payload.orderbookdirectory.longname"] = canonical::text(std::string(message.fields.long_name.get().value()), ' ', false);
        values[entry + ".payload.orderbookdirectory.isin"] = canonical::text(std::string(message.fields.isin.get().value()), ' ', false);
        values[entry + ".payload.orderbookdirectory.financialproduct"] = canonical::number(message.fields.financial_product.get().value());
        values[entry + ".payload.orderbookdirectory.tradingcurrency"] = canonical::text(std::string(message.fields.trading_currency.get().value()), ' ', false);
        values[entry + ".payload.orderbookdirectory.decimalsinprice"] = canonical::number(message.fields.decimals_in_price.get().value());
        values[entry + ".payload.orderbookdirectory.decimalsinnominalvalue"] = canonical::number(message.fields.decimals_in_nominal_value.get().value());
        values[entry + ".payload.orderbookdirectory.oddlotsize"] = canonical::number(message.fields.odd_lot_size.get().value());
        values[entry + ".payload.orderbookdirectory.roundlotsize"] = canonical::number(message.fields.round_lot_size.get().value());
        values[entry + ".payload.orderbookdirectory.blocklotsize"] = canonical::number(message.fields.block_lot_size.get().value());
        values[entry + ".payload.orderbookdirectory.nominalvalue"] = canonical::number(message.fields.nominal_value.get().value());
        values[entry + ".payload.orderbookdirectory.numberoflegs"] = canonical::number(message.fields.number_of_legs.get().value());
        values[entry + ".payload.orderbookdirectory.underlyingorderbookid"] = canonical::number(message.fields.underlying_orderbook_id.get().value());
        values[entry + ".payload.orderbookdirectory.strikeprice"] = canonical::number(message.fields.strike_price.get().value());
        values[entry + ".payload.orderbookdirectory.expirationdate"] = canonical::number(message.fields.expiration_date.get().value());
        values[entry + ".payload.orderbookdirectory.decimalsinstrikeprice"] = canonical::number(message.fields.decimals_in_strike_price.get().value());
        values[entry + ".payload.orderbookdirectory.putorcall"] = canonical::number(message.fields.put_or_call.get().value());
    }

    void on_message(const protocol::combination_orderbook_leg& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.combinationorderbookleg";
        values[entry + ".payload.combinationorderbookleg.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.combinationorderbookleg.combinationorderbookid"] = canonical::number(message.fields.combination_orderbook_id.get().value());
        values[entry + ".payload.combinationorderbookleg.legorderbookid"] = canonical::number(message.fields.leg_orderbook_id.get().value());
        values[entry + ".payload.combinationorderbookleg.legside"] = canonical::text(canonical::character(message.fields.leg_side.get().value()), ' ', false);
        values[entry + ".payload.combinationorderbookleg.legratio"] = canonical::number(message.fields.leg_ratio.get().value());
    }

    void on_message(const protocol::tick_size_table_entry& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.ticksizetableentry";
        values[entry + ".payload.ticksizetableentry.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.ticksizetableentry.orderbookid"] = canonical::number(message.fields.order_book_id.get().value());
        values[entry + ".payload.ticksizetableentry.ticksize"] = canonical::number(message.fields.tick_size.get().value());
        values[entry + ".payload.ticksizetableentry.pricefrom"] = canonical::number(message.fields.price_from.get().value());
        values[entry + ".payload.ticksizetableentry.priceto"] = canonical::number(message.fields.price_to.get().value());
    }

    void on_message(const protocol::system_event_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.systemeventmessage";
        values[entry + ".payload.systemeventmessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.systemeventmessage.eventcode"] = canonical::text(canonical::character(message.fields.event_code.get().value()), ' ', false);
    }

    void on_message(const protocol::order_book_state_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.orderbookstatemessage";
        values[entry + ".payload.orderbookstatemessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.orderbookstatemessage.orderbookid"] = canonical::number(message.fields.order_book_id.get().value());
        values[entry + ".payload.orderbookstatemessage.statename"] = canonical::text(std::string(message.fields.state_name.get().value()), ' ', false);
    }

    void on_message(const protocol::add_order_no_mpid& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.addordernompid";
        values[entry + ".payload.addordernompid.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.addordernompid.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.addordernompid.orderbookid"] = canonical::number(message.fields.order_book_id.get().value());
        values[entry + ".payload.addordernompid.side"] = canonical::text(canonical::character(message.fields.side.get().value()), ' ', false);
        values[entry + ".payload.addordernompid.orderbookposition"] = canonical::number(message.fields.order_book_position.get().value());
        values[entry + ".payload.addordernompid.quantity"] = canonical::number(message.fields.quantity.get().value());
        values[entry + ".payload.addordernompid.price"] = canonical::number(message.fields.price.get().value());
        values[entry + ".payload.addordernompid.lottype"] = canonical::number(message.fields.lot_type.get().value());
    }

    void on_message(const protocol::add_order_with_mpid& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.addorderwithmpid";
        values[entry + ".payload.addorderwithmpid.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.addorderwithmpid.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.addorderwithmpid.orderbookid"] = canonical::number(message.fields.order_book_id.get().value());
        values[entry + ".payload.addorderwithmpid.side"] = canonical::text(canonical::character(message.fields.side.get().value()), ' ', false);
        values[entry + ".payload.addorderwithmpid.orderbookposition"] = canonical::number(message.fields.order_book_position.get().value());
        values[entry + ".payload.addorderwithmpid.quantity"] = canonical::number(message.fields.quantity.get().value());
        values[entry + ".payload.addorderwithmpid.price"] = canonical::number(message.fields.price.get().value());
        values[entry + ".payload.addorderwithmpid.lottype"] = canonical::number(message.fields.lot_type.get().value());
        values[entry + ".payload.addorderwithmpid.participantid"] = canonical::text(std::string(message.fields.participant_id.get().value()), ' ', false);
    }

    void on_message(const protocol::order_executed_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedmessage";
        values[entry + ".payload.orderexecutedmessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.orderexecutedmessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.orderexecutedmessage.orderbookid"] = canonical::number(message.fields.order_book_id.get().value());
        values[entry + ".payload.orderexecutedmessage.side"] = canonical::text(canonical::character(message.fields.side.get().value()), ' ', false);
        values[entry + ".payload.orderexecutedmessage.executedquantity"] = canonical::number(message.fields.executed_quantity.get().value());
        values[entry + ".payload.orderexecutedmessage.matchid"] = canonical::number(message.fields.match_id.get().value());
        values[entry + ".payload.orderexecutedmessage.combogroupid"] = canonical::number(message.fields.combo_group_id.get().value());
        values[entry + ".payload.orderexecutedmessage.participantidowner"] = canonical::text(std::string(message.fields.participant_id_owner.get().value()), ' ', false);
        values[entry + ".payload.orderexecutedmessage.participantidcounterparty"] = canonical::text(std::string(message.fields.participant_id_counterparty.get().value()), ' ', false);
    }

    void on_message(const protocol::order_executed_with_price_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedwithpricemessage";
        values[entry + ".payload.orderexecutedwithpricemessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.orderexecutedwithpricemessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.orderexecutedwithpricemessage.orderbookid"] = canonical::number(message.fields.order_book_id.get().value());
        values[entry + ".payload.orderexecutedwithpricemessage.side"] = canonical::text(canonical::character(message.fields.side.get().value()), ' ', false);
        values[entry + ".payload.orderexecutedwithpricemessage.executedquantity"] = canonical::number(message.fields.executed_quantity.get().value());
        values[entry + ".payload.orderexecutedwithpricemessage.matchid"] = canonical::number(message.fields.match_id.get().value());
        values[entry + ".payload.orderexecutedwithpricemessage.combogroupid"] = canonical::number(message.fields.combo_group_id.get().value());
        values[entry + ".payload.orderexecutedwithpricemessage.ownerparticipantid"] = canonical::text(std::string(message.fields.owner_participant_id.get().value()), ' ', false);
        values[entry + ".payload.orderexecutedwithpricemessage.counterpartyparticipantid"] = canonical::text(std::string(message.fields.counterparty_participant_id.get().value()), ' ', false);
        values[entry + ".payload.orderexecutedwithpricemessage.tradeprice"] = canonical::number(message.fields.trade_price.get().value());
        values[entry + ".payload.orderexecutedwithpricemessage.occurredatcross"] = canonical::text(canonical::character(message.fields.occurred_at_cross.get().value()), ' ', false);
        values[entry + ".payload.orderexecutedwithpricemessage.printable"] = canonical::text(canonical::character(message.fields.printable.get().value()), ' ', false);
    }

    void on_message(const protocol::order_replace_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.orderreplacemessage";
        values[entry + ".payload.orderreplacemessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.orderreplacemessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.orderreplacemessage.orderbookid"] = canonical::number(message.fields.order_book_id.get().value());
        values[entry + ".payload.orderreplacemessage.side"] = canonical::text(canonical::character(message.fields.side.get().value()), ' ', false);
        values[entry + ".payload.orderreplacemessage.neworderbookposition"] = canonical::number(message.fields.new_orderbook_position.get().value());
        values[entry + ".payload.orderreplacemessage.quantity"] = canonical::number(message.fields.quantity.get().value());
        values[entry + ".payload.orderreplacemessage.price"] = canonical::number(message.fields.price.get().value());
    }

    void on_message(const protocol::order_delete_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.orderdeletemessage";
        values[entry + ".payload.orderdeletemessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.orderdeletemessage.orderid"] = canonical::number(message.fields.order_id.get().value());
        values[entry + ".payload.orderdeletemessage.orderbookid"] = canonical::number(message.fields.order_book_id.get().value());
        values[entry + ".payload.orderdeletemessage.side"] = canonical::text(canonical::character(message.fields.side.get().value()), ' ', false);
    }

    void on_message(const protocol::trade_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.trademessage";
        values[entry + ".payload.trademessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.trademessage.matchid"] = canonical::number(message.fields.match_id.get().value());
        values[entry + ".payload.trademessage.combogroupid"] = canonical::number(message.fields.combo_group_id.get().value());
        values[entry + ".payload.trademessage.side"] = canonical::text(canonical::character(message.fields.side.get().value()), ' ', false);
        values[entry + ".payload.trademessage.quantity"] = canonical::number(message.fields.quantity.get().value());
        values[entry + ".payload.trademessage.orderbookid"] = canonical::number(message.fields.order_book_id.get().value());
        values[entry + ".payload.trademessage.tradeprice"] = canonical::number(message.fields.trade_price.get().value());
        values[entry + ".payload.trademessage.ownerparticipantid"] = canonical::text(std::string(message.fields.owner_participant_id.get().value()), ' ', false);
        values[entry + ".payload.trademessage.counterpartyparticipantid"] = canonical::text(std::string(message.fields.counterparty_participant_id.get().value()), ' ', false);
        values[entry + ".payload.trademessage.printable"] = canonical::text(canonical::character(message.fields.printable.get().value()), ' ', false);
        values[entry + ".payload.trademessage.occurredatcross"] = canonical::text(canonical::character(message.fields.occurred_at_cross.get().value()), ' ', false);
    }

    void on_message(const protocol::equilibrium_price_update& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.equilibriumpriceupdate";
        values[entry + ".payload.equilibriumpriceupdate.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.equilibriumpriceupdate.orderbookid"] = canonical::number(message.fields.order_book_id.get().value());
        values[entry + ".payload.equilibriumpriceupdate.availablebidquantityatequilibriumprice"] = canonical::number(message.fields.available_bid_quantity_at_equilibrium_price.get().value());
        values[entry + ".payload.equilibriumpriceupdate.availableaskquantityatequilibriumprice"] = canonical::number(message.fields.available_ask_quantity_at_equilibrium_price.get().value());
        values[entry + ".payload.equilibriumpriceupdate.equilibriumprice"] = canonical::number(message.fields.equilibrium_price.get().value());
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
    std::printf("== Jpx.OseDerivatives.GeniumInet.Itch.v5.0.6 (advanced values)\n");
    int failures = 0;
    failures += check("AddOrderNoMpid", "Jpx/OseDerivatives.GeniumInet.Itch.v5.0.6/AddOrderNoMpid.pcap", "jpx/osederivatives/geniuminet/itch/v5.0.6/AddOrderNoMpid.values");
    failures += check("EquilibriumPriceUpdate", "Jpx/OseDerivatives.GeniumInet.Itch.v5.0.6/EquilibriumPriceUpdate.pcap", "jpx/osederivatives/geniuminet/itch/v5.0.6/EquilibriumPriceUpdate.values");
    failures += check("OrderBookStateMessage", "Jpx/OseDerivatives.GeniumInet.Itch.v5.0.6/OrderBookStateMessage.pcap", "jpx/osederivatives/geniuminet/itch/v5.0.6/OrderBookStateMessage.values");
    failures += check("OrderDeleteMessage", "Jpx/OseDerivatives.GeniumInet.Itch.v5.0.6/OrderDeleteMessage.pcap", "jpx/osederivatives/geniuminet/itch/v5.0.6/OrderDeleteMessage.values");
    failures += check("OrderExecutedMessage", "Jpx/OseDerivatives.GeniumInet.Itch.v5.0.6/OrderExecutedMessage.pcap", "jpx/osederivatives/geniuminet/itch/v5.0.6/OrderExecutedMessage.values");
    failures += check("OrderExecutedWithPriceMessage", "Jpx/OseDerivatives.GeniumInet.Itch.v5.0.6/OrderExecutedWithPriceMessage.pcap", "jpx/osederivatives/geniuminet/itch/v5.0.6/OrderExecutedWithPriceMessage.values");
    failures += check("SecondsMessage", "Jpx/OseDerivatives.GeniumInet.Itch.v5.0.6/SecondsMessage.pcap", "jpx/osederivatives/geniuminet/itch/v5.0.6/SecondsMessage.values");
    return failures == 0 ? 0 : 1;
}