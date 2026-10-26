// Jpx.OseDerivatives.GeniumInet.Itch.v5.0.6 canonical values, through the Classes Packet: every value Classes decodes from
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
#include "cpp/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/definitions.hpp"

namespace protocol = ::jpx::osederivatives::geniuminet::itch::v5_0_6;

namespace {

// The values the Classes Packet decodes from one datagram, by indexed address. A datagram it cannot
// decode is a value the model never reads, so it fails rather than passing with nothing compared.
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::Packet packet;

    try {
        packet.decode(frame.payload, frame.payload_len);
    } catch (const protocol::DecodeError& error) {
        values["(does not decode)"] = error.what();
        return values;
    }

    values["packet.packetheader.session"] = canonical::text(std::string(packet.packet_header().session()), '\0', false);
    values["packet.packetheader.sequencenumber"] = canonical::number(packet.packet_header().sequence_number());
    values["packet.packetheader.messagecount"] = canonical::number(packet.packet_header().message_count());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(each.message_header().message_length());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(each.message_header().message_type()));

        if (const auto* message = dynamic_cast<const protocol::SecondsMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.secondsmessage";
            values[entry + ".payload.secondsmessage.seconds"] = canonical::number((*message).seconds());
        } else if (const auto* message = dynamic_cast<const protocol::OrderBookDirectory*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderbookdirectory";
            values[entry + ".payload.orderbookdirectory.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.orderbookdirectory.orderbookid"] = canonical::number((*message).order_book_id());
            values[entry + ".payload.orderbookdirectory.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".payload.orderbookdirectory.longname"] = canonical::text(std::string((*message).long_name()), ' ', false);
            values[entry + ".payload.orderbookdirectory.isin"] = canonical::text(std::string((*message).isin()), ' ', false);
            values[entry + ".payload.orderbookdirectory.financialproduct"] = canonical::number((*message).financial_product());
            values[entry + ".payload.orderbookdirectory.tradingcurrency"] = canonical::text(std::string((*message).trading_currency()), ' ', false);
            values[entry + ".payload.orderbookdirectory.decimalsinprice"] = canonical::number((*message).decimals_in_price());
            values[entry + ".payload.orderbookdirectory.decimalsinnominalvalue"] = canonical::number((*message).decimals_in_nominal_value());
            values[entry + ".payload.orderbookdirectory.oddlotsize"] = canonical::number((*message).odd_lot_size());
            values[entry + ".payload.orderbookdirectory.roundlotsize"] = canonical::number((*message).round_lot_size());
            values[entry + ".payload.orderbookdirectory.blocklotsize"] = canonical::number((*message).block_lot_size());
            values[entry + ".payload.orderbookdirectory.nominalvalue"] = canonical::number((*message).nominal_value());
            values[entry + ".payload.orderbookdirectory.numberoflegs"] = canonical::number((*message).number_of_legs());
            values[entry + ".payload.orderbookdirectory.underlyingorderbookid"] = canonical::number((*message).underlying_orderbook_id());
            values[entry + ".payload.orderbookdirectory.strikeprice"] = canonical::number((*message).strike_price());
            values[entry + ".payload.orderbookdirectory.expirationdate"] = canonical::number((*message).expiration_date());
            values[entry + ".payload.orderbookdirectory.decimalsinstrikeprice"] = canonical::number((*message).decimals_in_strike_price());
            values[entry + ".payload.orderbookdirectory.putorcall"] = canonical::number((*message).put_or_call());
        } else if (const auto* message = dynamic_cast<const protocol::CombinationOrderbookLeg*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.combinationorderbookleg";
            values[entry + ".payload.combinationorderbookleg.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.combinationorderbookleg.combinationorderbookid"] = canonical::number((*message).combination_orderbook_id());
            values[entry + ".payload.combinationorderbookleg.legorderbookid"] = canonical::number((*message).leg_orderbook_id());
            values[entry + ".payload.combinationorderbookleg.legside"] = canonical::text(canonical::character((*message).leg_side()), ' ', false);
            values[entry + ".payload.combinationorderbookleg.legratio"] = canonical::number((*message).leg_ratio());
        } else if (const auto* message = dynamic_cast<const protocol::TickSizeTableEntry*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.ticksizetableentry";
            values[entry + ".payload.ticksizetableentry.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.ticksizetableentry.orderbookid"] = canonical::number((*message).order_book_id());
            values[entry + ".payload.ticksizetableentry.ticksize"] = canonical::number((*message).tick_size());
            values[entry + ".payload.ticksizetableentry.pricefrom"] = canonical::number((*message).price_from());
            values[entry + ".payload.ticksizetableentry.priceto"] = canonical::number((*message).price_to());
        } else if (const auto* message = dynamic_cast<const protocol::SystemEventMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.systemeventmessage";
            values[entry + ".payload.systemeventmessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.systemeventmessage.eventcode"] = canonical::text(canonical::character((*message).event_code()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::OrderBookStateMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderbookstatemessage";
            values[entry + ".payload.orderbookstatemessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.orderbookstatemessage.orderbookid"] = canonical::number((*message).order_book_id());
            values[entry + ".payload.orderbookstatemessage.statename"] = canonical::text(std::string((*message).state_name()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderNoMpid*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.addordernompid";
            values[entry + ".payload.addordernompid.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.addordernompid.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.addordernompid.orderbookid"] = canonical::number((*message).order_book_id());
            values[entry + ".payload.addordernompid.side"] = canonical::text(canonical::character((*message).side()), ' ', false);
            values[entry + ".payload.addordernompid.orderbookposition"] = canonical::number((*message).order_book_position());
            values[entry + ".payload.addordernompid.quantity"] = canonical::number((*message).quantity());
            values[entry + ".payload.addordernompid.price"] = canonical::number((*message).price());
            values[entry + ".payload.addordernompid.lottype"] = canonical::number((*message).lot_type());
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderWithMpid*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.addorderwithmpid";
            values[entry + ".payload.addorderwithmpid.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.addorderwithmpid.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.addorderwithmpid.orderbookid"] = canonical::number((*message).order_book_id());
            values[entry + ".payload.addorderwithmpid.side"] = canonical::text(canonical::character((*message).side()), ' ', false);
            values[entry + ".payload.addorderwithmpid.orderbookposition"] = canonical::number((*message).order_book_position());
            values[entry + ".payload.addorderwithmpid.quantity"] = canonical::number((*message).quantity());
            values[entry + ".payload.addorderwithmpid.price"] = canonical::number((*message).price());
            values[entry + ".payload.addorderwithmpid.lottype"] = canonical::number((*message).lot_type());
            values[entry + ".payload.addorderwithmpid.participantid"] = canonical::text(std::string((*message).participant_id()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedmessage";
            values[entry + ".payload.orderexecutedmessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.orderexecutedmessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.orderexecutedmessage.orderbookid"] = canonical::number((*message).order_book_id());
            values[entry + ".payload.orderexecutedmessage.side"] = canonical::text(canonical::character((*message).side()), ' ', false);
            values[entry + ".payload.orderexecutedmessage.executedquantity"] = canonical::number((*message).executed_quantity());
            values[entry + ".payload.orderexecutedmessage.matchid"] = canonical::number((*message).match_id());
            values[entry + ".payload.orderexecutedmessage.combogroupid"] = canonical::number((*message).combo_group_id());
            values[entry + ".payload.orderexecutedmessage.participantidowner"] = canonical::text(std::string((*message).participant_id_owner()), ' ', false);
            values[entry + ".payload.orderexecutedmessage.participantidcounterparty"] = canonical::text(std::string((*message).participant_id_counterparty()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedWithPriceMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedwithpricemessage";
            values[entry + ".payload.orderexecutedwithpricemessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.orderexecutedwithpricemessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.orderexecutedwithpricemessage.orderbookid"] = canonical::number((*message).order_book_id());
            values[entry + ".payload.orderexecutedwithpricemessage.side"] = canonical::text(canonical::character((*message).side()), ' ', false);
            values[entry + ".payload.orderexecutedwithpricemessage.executedquantity"] = canonical::number((*message).executed_quantity());
            values[entry + ".payload.orderexecutedwithpricemessage.matchid"] = canonical::number((*message).match_id());
            values[entry + ".payload.orderexecutedwithpricemessage.combogroupid"] = canonical::number((*message).combo_group_id());
            values[entry + ".payload.orderexecutedwithpricemessage.ownerparticipantid"] = canonical::text(std::string((*message).owner_participant_id()), ' ', false);
            values[entry + ".payload.orderexecutedwithpricemessage.counterpartyparticipantid"] = canonical::text(std::string((*message).counterparty_participant_id()), ' ', false);
            values[entry + ".payload.orderexecutedwithpricemessage.tradeprice"] = canonical::number((*message).trade_price());
            values[entry + ".payload.orderexecutedwithpricemessage.occurredatcross"] = canonical::text(canonical::character((*message).occurred_at_cross()), ' ', false);
            values[entry + ".payload.orderexecutedwithpricemessage.printable"] = canonical::text(canonical::character((*message).printable()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::OrderReplaceMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderreplacemessage";
            values[entry + ".payload.orderreplacemessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.orderreplacemessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.orderreplacemessage.orderbookid"] = canonical::number((*message).order_book_id());
            values[entry + ".payload.orderreplacemessage.side"] = canonical::text(canonical::character((*message).side()), ' ', false);
            values[entry + ".payload.orderreplacemessage.neworderbookposition"] = canonical::number((*message).new_orderbook_position());
            values[entry + ".payload.orderreplacemessage.quantity"] = canonical::number((*message).quantity());
            values[entry + ".payload.orderreplacemessage.price"] = canonical::number((*message).price());
        } else if (const auto* message = dynamic_cast<const protocol::OrderDeleteMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderdeletemessage";
            values[entry + ".payload.orderdeletemessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.orderdeletemessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.orderdeletemessage.orderbookid"] = canonical::number((*message).order_book_id());
            values[entry + ".payload.orderdeletemessage.side"] = canonical::text(canonical::character((*message).side()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::TradeMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.trademessage";
            values[entry + ".payload.trademessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.trademessage.matchid"] = canonical::number((*message).match_id());
            values[entry + ".payload.trademessage.combogroupid"] = canonical::number((*message).combo_group_id());
            values[entry + ".payload.trademessage.side"] = canonical::text(canonical::character((*message).side()), ' ', false);
            values[entry + ".payload.trademessage.quantity"] = canonical::number((*message).quantity());
            values[entry + ".payload.trademessage.orderbookid"] = canonical::number((*message).order_book_id());
            values[entry + ".payload.trademessage.tradeprice"] = canonical::number((*message).trade_price());
            values[entry + ".payload.trademessage.ownerparticipantid"] = canonical::text(std::string((*message).owner_participant_id()), ' ', false);
            values[entry + ".payload.trademessage.counterpartyparticipantid"] = canonical::text(std::string((*message).counterparty_participant_id()), ' ', false);
            values[entry + ".payload.trademessage.printable"] = canonical::text(canonical::character((*message).printable()), ' ', false);
            values[entry + ".payload.trademessage.occurredatcross"] = canonical::text(canonical::character((*message).occurred_at_cross()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::EquilibriumPriceUpdate*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.equilibriumpriceupdate";
            values[entry + ".payload.equilibriumpriceupdate.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.equilibriumpriceupdate.orderbookid"] = canonical::number((*message).order_book_id());
            values[entry + ".payload.equilibriumpriceupdate.availablebidquantityatequilibriumprice"] = canonical::number((*message).available_bid_quantity_at_equilibrium_price());
            values[entry + ".payload.equilibriumpriceupdate.availableaskquantityatequilibriumprice"] = canonical::number((*message).available_ask_quantity_at_equilibrium_price());
            values[entry + ".payload.equilibriumpriceupdate.equilibriumprice"] = canonical::number((*message).equilibrium_price());
        }
    }

    return values;
}

// Read each datagram of a sample with Classes and hold it to the model's values
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
    std::printf("== Jpx.OseDerivatives.GeniumInet.Itch.v5.0.6 (classes values)\n");
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