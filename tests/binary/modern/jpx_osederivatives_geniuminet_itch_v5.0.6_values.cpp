// Jpx.OseDerivatives.GeniumInet.Itch.v5.0.6 canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/binary/modern/jpx/osederivatives/geniuminet/itch/v5.0.6/definitions.hpp"

namespace protocol = ::jpx::osederivatives::geniuminet::itch::v5_0_6;

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
            values[entry + ".payload.secondsmessage.seconds"] = canonical::number(message->seconds.get());
        } else if (iterator.message_type == protocol::OrderBookDirectory::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderbookdirectory";
            [[maybe_unused]] const auto* message = protocol::OrderBookDirectory::parse(iterator.message);
            values[entry + ".payload.orderbookdirectory.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.orderbookdirectory.orderbookid"] = canonical::number(message->order_book_id.get());
            values[entry + ".payload.orderbookdirectory.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".payload.orderbookdirectory.longname"] = canonical::text(std::string(message->long_name.get()), ' ', false);
            values[entry + ".payload.orderbookdirectory.isin"] = canonical::text(std::string(message->isin.get()), ' ', false);
            values[entry + ".payload.orderbookdirectory.financialproduct"] = canonical::number(message->financial_product.get());
            values[entry + ".payload.orderbookdirectory.tradingcurrency"] = canonical::text(std::string(message->trading_currency.get()), ' ', false);
            values[entry + ".payload.orderbookdirectory.decimalsinprice"] = canonical::number(message->decimals_in_price.get());
            values[entry + ".payload.orderbookdirectory.decimalsinnominalvalue"] = canonical::number(message->decimals_in_nominal_value.get());
            values[entry + ".payload.orderbookdirectory.oddlotsize"] = canonical::number(message->odd_lot_size.get());
            values[entry + ".payload.orderbookdirectory.roundlotsize"] = canonical::number(message->round_lot_size.get());
            values[entry + ".payload.orderbookdirectory.blocklotsize"] = canonical::number(message->block_lot_size.get());
            values[entry + ".payload.orderbookdirectory.nominalvalue"] = canonical::number(message->nominal_value.get());
            values[entry + ".payload.orderbookdirectory.numberoflegs"] = canonical::number(message->number_of_legs.get());
            values[entry + ".payload.orderbookdirectory.underlyingorderbookid"] = canonical::number(message->underlying_orderbook_id.get());
            values[entry + ".payload.orderbookdirectory.strikeprice"] = canonical::number(message->strike_price.get());
            values[entry + ".payload.orderbookdirectory.expirationdate"] = canonical::number(message->expiration_date.get());
            values[entry + ".payload.orderbookdirectory.decimalsinstrikeprice"] = canonical::number(message->decimals_in_strike_price.get());
            values[entry + ".payload.orderbookdirectory.putorcall"] = canonical::number(message->put_or_call.get());
        } else if (iterator.message_type == protocol::CombinationOrderbookLeg::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.combinationorderbookleg";
            [[maybe_unused]] const auto* message = protocol::CombinationOrderbookLeg::parse(iterator.message);
            values[entry + ".payload.combinationorderbookleg.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.combinationorderbookleg.combinationorderbookid"] = canonical::number(message->combination_orderbook_id.get());
            values[entry + ".payload.combinationorderbookleg.legorderbookid"] = canonical::number(message->leg_orderbook_id.get());
            values[entry + ".payload.combinationorderbookleg.legside"] = canonical::text(canonical::character(message->leg_side.get()), ' ', false);
            values[entry + ".payload.combinationorderbookleg.legratio"] = canonical::number(message->leg_ratio.get());
        } else if (iterator.message_type == protocol::TickSizeTableEntry::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.ticksizetableentry";
            [[maybe_unused]] const auto* message = protocol::TickSizeTableEntry::parse(iterator.message);
            values[entry + ".payload.ticksizetableentry.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.ticksizetableentry.orderbookid"] = canonical::number(message->order_book_id.get());
            values[entry + ".payload.ticksizetableentry.ticksize"] = canonical::number(message->tick_size.get());
            values[entry + ".payload.ticksizetableentry.pricefrom"] = canonical::number(message->price_from.get());
            values[entry + ".payload.ticksizetableentry.priceto"] = canonical::number(message->price_to.get());
        } else if (iterator.message_type == protocol::SystemEventMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.systemeventmessage";
            [[maybe_unused]] const auto* message = protocol::SystemEventMessage::parse(iterator.message);
            values[entry + ".payload.systemeventmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.systemeventmessage.eventcode"] = canonical::text(canonical::character(message->event_code.get()), ' ', false);
        } else if (iterator.message_type == protocol::OrderBookStateMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderbookstatemessage";
            [[maybe_unused]] const auto* message = protocol::OrderBookStateMessage::parse(iterator.message);
            values[entry + ".payload.orderbookstatemessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.orderbookstatemessage.orderbookid"] = canonical::number(message->order_book_id.get());
            values[entry + ".payload.orderbookstatemessage.statename"] = canonical::text(std::string(message->state_name.get()), ' ', false);
        } else if (iterator.message_type == protocol::AddOrderNoMpid::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.addordernompid";
            [[maybe_unused]] const auto* message = protocol::AddOrderNoMpid::parse(iterator.message);
            values[entry + ".payload.addordernompid.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.addordernompid.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.addordernompid.orderbookid"] = canonical::number(message->order_book_id.get());
            values[entry + ".payload.addordernompid.side"] = canonical::text(canonical::character(message->side.get()), ' ', false);
            values[entry + ".payload.addordernompid.orderbookposition"] = canonical::number(message->order_book_position.get());
            values[entry + ".payload.addordernompid.quantity"] = canonical::number(message->quantity.get());
            values[entry + ".payload.addordernompid.price"] = canonical::number(message->price.get());
            values[entry + ".payload.addordernompid.orderattributes.force"] = canonical::number(static_cast<std::uint64_t>(message->order_attributes.Force()));
            values[entry + ".payload.addordernompid.orderattributes.shortsell"] = canonical::number(static_cast<std::uint64_t>(message->order_attributes.ShortSell()));
            values[entry + ".payload.addordernompid.orderattributes.marketbid"] = canonical::number(static_cast<std::uint64_t>(message->order_attributes.MarketBid()));
            values[entry + ".payload.addordernompid.orderattributes.pricestabilization"] = canonical::number(static_cast<std::uint64_t>(message->order_attributes.PriceStabilization()));
            values[entry + ".payload.addordernompid.orderattributes.overridecrossing"] = canonical::number(static_cast<std::uint64_t>(message->order_attributes.OverrideCrossing()));
            values[entry + ".payload.addordernompid.orderattributes.undisclosed"] = canonical::number(static_cast<std::uint64_t>(message->order_attributes.Undisclosed()));
            values[entry + ".payload.addordernompid.lottype"] = canonical::number(message->lot_type.get());
        } else if (iterator.message_type == protocol::AddOrderWithMpid::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.addorderwithmpid";
            [[maybe_unused]] const auto* message = protocol::AddOrderWithMpid::parse(iterator.message);
            values[entry + ".payload.addorderwithmpid.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.addorderwithmpid.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.addorderwithmpid.orderbookid"] = canonical::number(message->order_book_id.get());
            values[entry + ".payload.addorderwithmpid.side"] = canonical::text(canonical::character(message->side.get()), ' ', false);
            values[entry + ".payload.addorderwithmpid.orderbookposition"] = canonical::number(message->order_book_position.get());
            values[entry + ".payload.addorderwithmpid.quantity"] = canonical::number(message->quantity.get());
            values[entry + ".payload.addorderwithmpid.price"] = canonical::number(message->price.get());
            values[entry + ".payload.addorderwithmpid.orderattributes.force"] = canonical::number(static_cast<std::uint64_t>(message->order_attributes.Force()));
            values[entry + ".payload.addorderwithmpid.orderattributes.shortsell"] = canonical::number(static_cast<std::uint64_t>(message->order_attributes.ShortSell()));
            values[entry + ".payload.addorderwithmpid.orderattributes.marketbid"] = canonical::number(static_cast<std::uint64_t>(message->order_attributes.MarketBid()));
            values[entry + ".payload.addorderwithmpid.orderattributes.pricestabilization"] = canonical::number(static_cast<std::uint64_t>(message->order_attributes.PriceStabilization()));
            values[entry + ".payload.addorderwithmpid.orderattributes.overridecrossing"] = canonical::number(static_cast<std::uint64_t>(message->order_attributes.OverrideCrossing()));
            values[entry + ".payload.addorderwithmpid.orderattributes.undisclosed"] = canonical::number(static_cast<std::uint64_t>(message->order_attributes.Undisclosed()));
            values[entry + ".payload.addorderwithmpid.lottype"] = canonical::number(message->lot_type.get());
            values[entry + ".payload.addorderwithmpid.participantid"] = canonical::text(std::string(message->participant_id.get()), ' ', false);
        } else if (iterator.message_type == protocol::OrderExecutedMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedmessage";
            [[maybe_unused]] const auto* message = protocol::OrderExecutedMessage::parse(iterator.message);
            values[entry + ".payload.orderexecutedmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.orderexecutedmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.orderexecutedmessage.orderbookid"] = canonical::number(message->order_book_id.get());
            values[entry + ".payload.orderexecutedmessage.side"] = canonical::text(canonical::character(message->side.get()), ' ', false);
            values[entry + ".payload.orderexecutedmessage.executedquantity"] = canonical::number(message->executed_quantity.get());
            values[entry + ".payload.orderexecutedmessage.matchid"] = canonical::number(message->match_id.get());
            values[entry + ".payload.orderexecutedmessage.combogroupid"] = canonical::number(message->combo_group_id.get());
            values[entry + ".payload.orderexecutedmessage.participantidowner"] = canonical::text(std::string(message->participant_id_owner.get()), ' ', false);
            values[entry + ".payload.orderexecutedmessage.participantidcounterparty"] = canonical::text(std::string(message->participant_id_counterparty.get()), ' ', false);
        } else if (iterator.message_type == protocol::OrderExecutedWithPriceMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedwithpricemessage";
            [[maybe_unused]] const auto* message = protocol::OrderExecutedWithPriceMessage::parse(iterator.message);
            values[entry + ".payload.orderexecutedwithpricemessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.orderexecutedwithpricemessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.orderexecutedwithpricemessage.orderbookid"] = canonical::number(message->order_book_id.get());
            values[entry + ".payload.orderexecutedwithpricemessage.side"] = canonical::text(canonical::character(message->side.get()), ' ', false);
            values[entry + ".payload.orderexecutedwithpricemessage.executedquantity"] = canonical::number(message->executed_quantity.get());
            values[entry + ".payload.orderexecutedwithpricemessage.matchid"] = canonical::number(message->match_id.get());
            values[entry + ".payload.orderexecutedwithpricemessage.combogroupid"] = canonical::number(message->combo_group_id.get());
            values[entry + ".payload.orderexecutedwithpricemessage.ownerparticipantid"] = canonical::text(std::string(message->owner_participant_id.get()), ' ', false);
            values[entry + ".payload.orderexecutedwithpricemessage.counterpartyparticipantid"] = canonical::text(std::string(message->counterparty_participant_id.get()), ' ', false);
            values[entry + ".payload.orderexecutedwithpricemessage.tradeprice"] = canonical::number(message->trade_price.get());
            values[entry + ".payload.orderexecutedwithpricemessage.occurredatcross"] = canonical::text(canonical::character(message->occurred_at_cross.get()), ' ', false);
            values[entry + ".payload.orderexecutedwithpricemessage.printable"] = canonical::text(canonical::character(message->printable.get()), ' ', false);
        } else if (iterator.message_type == protocol::OrderReplaceMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderreplacemessage";
            [[maybe_unused]] const auto* message = protocol::OrderReplaceMessage::parse(iterator.message);
            values[entry + ".payload.orderreplacemessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.orderreplacemessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.orderreplacemessage.orderbookid"] = canonical::number(message->order_book_id.get());
            values[entry + ".payload.orderreplacemessage.side"] = canonical::text(canonical::character(message->side.get()), ' ', false);
            values[entry + ".payload.orderreplacemessage.neworderbookposition"] = canonical::number(message->new_orderbook_position.get());
            values[entry + ".payload.orderreplacemessage.quantity"] = canonical::number(message->quantity.get());
            values[entry + ".payload.orderreplacemessage.price"] = canonical::number(message->price.get());
            values[entry + ".payload.orderreplacemessage.orderattributes.force"] = canonical::number(static_cast<std::uint64_t>(message->order_attributes.Force()));
            values[entry + ".payload.orderreplacemessage.orderattributes.shortsell"] = canonical::number(static_cast<std::uint64_t>(message->order_attributes.ShortSell()));
            values[entry + ".payload.orderreplacemessage.orderattributes.marketbid"] = canonical::number(static_cast<std::uint64_t>(message->order_attributes.MarketBid()));
            values[entry + ".payload.orderreplacemessage.orderattributes.pricestabilization"] = canonical::number(static_cast<std::uint64_t>(message->order_attributes.PriceStabilization()));
            values[entry + ".payload.orderreplacemessage.orderattributes.overridecrossing"] = canonical::number(static_cast<std::uint64_t>(message->order_attributes.OverrideCrossing()));
            values[entry + ".payload.orderreplacemessage.orderattributes.undisclosed"] = canonical::number(static_cast<std::uint64_t>(message->order_attributes.Undisclosed()));
        } else if (iterator.message_type == protocol::OrderDeleteMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderdeletemessage";
            [[maybe_unused]] const auto* message = protocol::OrderDeleteMessage::parse(iterator.message);
            values[entry + ".payload.orderdeletemessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.orderdeletemessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.orderdeletemessage.orderbookid"] = canonical::number(message->order_book_id.get());
            values[entry + ".payload.orderdeletemessage.side"] = canonical::text(canonical::character(message->side.get()), ' ', false);
        } else if (iterator.message_type == protocol::TradeMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.trademessage";
            [[maybe_unused]] const auto* message = protocol::TradeMessage::parse(iterator.message);
            values[entry + ".payload.trademessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.trademessage.matchid"] = canonical::number(message->match_id.get());
            values[entry + ".payload.trademessage.combogroupid"] = canonical::number(message->combo_group_id.get());
            values[entry + ".payload.trademessage.side"] = canonical::text(canonical::character(message->side.get()), ' ', false);
            values[entry + ".payload.trademessage.quantity"] = canonical::number(message->quantity.get());
            values[entry + ".payload.trademessage.orderbookid"] = canonical::number(message->order_book_id.get());
            values[entry + ".payload.trademessage.tradeprice"] = canonical::number(message->trade_price.get());
            values[entry + ".payload.trademessage.ownerparticipantid"] = canonical::text(std::string(message->owner_participant_id.get()), ' ', false);
            values[entry + ".payload.trademessage.counterpartyparticipantid"] = canonical::text(std::string(message->counterparty_participant_id.get()), ' ', false);
            values[entry + ".payload.trademessage.printable"] = canonical::text(canonical::character(message->printable.get()), ' ', false);
            values[entry + ".payload.trademessage.occurredatcross"] = canonical::text(canonical::character(message->occurred_at_cross.get()), ' ', false);
        } else if (iterator.message_type == protocol::EquilibriumPriceUpdate::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.equilibriumpriceupdate";
            [[maybe_unused]] const auto* message = protocol::EquilibriumPriceUpdate::parse(iterator.message);
            values[entry + ".payload.equilibriumpriceupdate.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".payload.equilibriumpriceupdate.orderbookid"] = canonical::number(message->order_book_id.get());
            values[entry + ".payload.equilibriumpriceupdate.availablebidquantityatequilibriumprice"] = canonical::number(message->available_bid_quantity_at_equilibrium_price.get());
            values[entry + ".payload.equilibriumpriceupdate.availableaskquantityatequilibriumprice"] = canonical::number(message->available_ask_quantity_at_equilibrium_price.get());
            values[entry + ".payload.equilibriumpriceupdate.equilibriumprice"] = canonical::number(message->equilibrium_price.get());
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
    std::printf("== Jpx.OseDerivatives.GeniumInet.Itch.v5.0.6 (modern values)\n");
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
