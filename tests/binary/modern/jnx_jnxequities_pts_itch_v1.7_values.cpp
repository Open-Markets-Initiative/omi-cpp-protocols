// Jnx.JnxEquities.Pts.Itch.v1.7 canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/binary/modern/jnx/jnxequities/pts/itch/v1.7/definitions.hpp"

namespace protocol = ::jnx::jnxequities::pts::itch::v1_7;

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
            values[entry + ".udppayload"] = "packet.messages.message.udppayload.secondsmessage";
            [[maybe_unused]] const auto* message = protocol::SecondsMessage::parse(iterator.message);
            values[entry + ".udppayload.secondsmessage.seconds"] = canonical::number(message->seconds.get());
        } else if (iterator.message_type == protocol::SystemEventMessage::message_type) {
            values[entry + ".udppayload"] = "packet.messages.message.udppayload.systemeventmessage";
            [[maybe_unused]] const auto* message = protocol::SystemEventMessage::parse(iterator.message);
            values[entry + ".udppayload.systemeventmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".udppayload.systemeventmessage.group"] = canonical::text(std::string(message->group.get()), ' ', false);
            values[entry + ".udppayload.systemeventmessage.systemevent"] = canonical::text(canonical::character(message->system_event.get()), ' ', false);
        } else if (iterator.message_type == protocol::PriceTickSizeMessage::message_type) {
            values[entry + ".udppayload"] = "packet.messages.message.udppayload.priceticksizemessage";
            [[maybe_unused]] const auto* message = protocol::PriceTickSizeMessage::parse(iterator.message);
            values[entry + ".udppayload.priceticksizemessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".udppayload.priceticksizemessage.priceticksizetableid"] = canonical::number(message->price_tick_size_table_id.get());
            values[entry + ".udppayload.priceticksizemessage.priceticksize"] = canonical::scaled(message->price_tick_size.integer(), -1);
            values[entry + ".udppayload.priceticksizemessage.pricestart"] = canonical::scaled(message->price_start.integer(), -1);
        } else if (iterator.message_type == protocol::OrderbookDirectoryMessage::message_type) {
            values[entry + ".udppayload"] = "packet.messages.message.udppayload.orderbookdirectorymessage";
            [[maybe_unused]] const auto* message = protocol::OrderbookDirectoryMessage::parse(iterator.message);
            values[entry + ".udppayload.orderbookdirectorymessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".udppayload.orderbookdirectorymessage.orderbookid"] = canonical::number(message->orderbook_id.get());
            values[entry + ".udppayload.orderbookdirectorymessage.orderbookcode"] = canonical::text(std::string(message->orderbook_code.get()), ' ', false);
            values[entry + ".udppayload.orderbookdirectorymessage.group"] = canonical::text(std::string(message->group.get()), ' ', false);
            values[entry + ".udppayload.orderbookdirectorymessage.roundlotsize"] = canonical::number(message->round_lot_size.get());
            values[entry + ".udppayload.orderbookdirectorymessage.priceticksizetableid"] = canonical::number(message->price_tick_size_table_id.get());
            values[entry + ".udppayload.orderbookdirectorymessage.pricedecimals"] = canonical::number(message->price_decimals.get());
            values[entry + ".udppayload.orderbookdirectorymessage.upperpricelimit"] = canonical::scaled(message->upper_price_limit.integer(), -1);
            values[entry + ".udppayload.orderbookdirectorymessage.lowerpricelimit"] = canonical::scaled(message->lower_price_limit.integer(), -1);
        } else if (iterator.message_type == protocol::TradingStateMessage::message_type) {
            values[entry + ".udppayload"] = "packet.messages.message.udppayload.tradingstatemessage";
            [[maybe_unused]] const auto* message = protocol::TradingStateMessage::parse(iterator.message);
            values[entry + ".udppayload.tradingstatemessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".udppayload.tradingstatemessage.orderbookid"] = canonical::number(message->orderbook_id.get());
            values[entry + ".udppayload.tradingstatemessage.group"] = canonical::text(std::string(message->group.get()), ' ', false);
            values[entry + ".udppayload.tradingstatemessage.tradingstate"] = canonical::text(canonical::character(message->trading_state.get()), ' ', false);
        } else if (iterator.message_type == protocol::ShortSellingPriceRestrictionStateMessage::message_type) {
            values[entry + ".udppayload"] = "packet.messages.message.udppayload.shortsellingpricerestrictionstatemessage";
            [[maybe_unused]] const auto* message = protocol::ShortSellingPriceRestrictionStateMessage::parse(iterator.message);
            values[entry + ".udppayload.shortsellingpricerestrictionstatemessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".udppayload.shortsellingpricerestrictionstatemessage.orderbookid"] = canonical::number(message->orderbook_id.get());
            values[entry + ".udppayload.shortsellingpricerestrictionstatemessage.group"] = canonical::text(std::string(message->group.get()), ' ', false);
            values[entry + ".udppayload.shortsellingpricerestrictionstatemessage.shortsellingstate"] = canonical::text(canonical::character(message->short_selling_state.get()), ' ', false);
        } else if (iterator.message_type == protocol::OrderAddedWithoutAttributesMessage::message_type) {
            values[entry + ".udppayload"] = "packet.messages.message.udppayload.orderaddedwithoutattributesmessage";
            [[maybe_unused]] const auto* message = protocol::OrderAddedWithoutAttributesMessage::parse(iterator.message);
            values[entry + ".udppayload.orderaddedwithoutattributesmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".udppayload.orderaddedwithoutattributesmessage.ordernumber"] = canonical::number(message->order_number.get());
            values[entry + ".udppayload.orderaddedwithoutattributesmessage.buysellindicator"] = canonical::text(canonical::character(message->buy_sell_indicator.get()), ' ', false);
            values[entry + ".udppayload.orderaddedwithoutattributesmessage.quantity"] = canonical::number(message->quantity.get());
            values[entry + ".udppayload.orderaddedwithoutattributesmessage.orderbookid"] = canonical::number(message->orderbook_id.get());
            values[entry + ".udppayload.orderaddedwithoutattributesmessage.group"] = canonical::text(std::string(message->group.get()), ' ', false);
            values[entry + ".udppayload.orderaddedwithoutattributesmessage.price"] = canonical::scaled(message->price.integer(), -1);
        } else if (iterator.message_type == protocol::OrderAddedWithAttributesMessage::message_type) {
            values[entry + ".udppayload"] = "packet.messages.message.udppayload.orderaddedwithattributesmessage";
            [[maybe_unused]] const auto* message = protocol::OrderAddedWithAttributesMessage::parse(iterator.message);
            values[entry + ".udppayload.orderaddedwithattributesmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".udppayload.orderaddedwithattributesmessage.ordernumber"] = canonical::number(message->order_number.get());
            values[entry + ".udppayload.orderaddedwithattributesmessage.buysellindicator"] = canonical::text(canonical::character(message->buy_sell_indicator.get()), ' ', false);
            values[entry + ".udppayload.orderaddedwithattributesmessage.quantity"] = canonical::number(message->quantity.get());
            values[entry + ".udppayload.orderaddedwithattributesmessage.orderbookid"] = canonical::number(message->orderbook_id.get());
            values[entry + ".udppayload.orderaddedwithattributesmessage.group"] = canonical::text(std::string(message->group.get()), ' ', false);
            values[entry + ".udppayload.orderaddedwithattributesmessage.price"] = canonical::scaled(message->price.integer(), -1);
            values[entry + ".udppayload.orderaddedwithattributesmessage.attribution"] = canonical::text(std::string(message->attribution.get()), ' ', false);
            values[entry + ".udppayload.orderaddedwithattributesmessage.ordertype"] = canonical::text(canonical::character(message->order_type.get()), ' ', false);
        } else if (iterator.message_type == protocol::OrderExecutedMessage::message_type) {
            values[entry + ".udppayload"] = "packet.messages.message.udppayload.orderexecutedmessage";
            [[maybe_unused]] const auto* message = protocol::OrderExecutedMessage::parse(iterator.message);
            values[entry + ".udppayload.orderexecutedmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".udppayload.orderexecutedmessage.ordernumber"] = canonical::number(message->order_number.get());
            values[entry + ".udppayload.orderexecutedmessage.executedquantity"] = canonical::number(message->executed_quantity.get());
            values[entry + ".udppayload.orderexecutedmessage.matchnumber"] = canonical::number(message->match_number.get());
        } else if (iterator.message_type == protocol::OrderDeletedMessage::message_type) {
            values[entry + ".udppayload"] = "packet.messages.message.udppayload.orderdeletedmessage";
            [[maybe_unused]] const auto* message = protocol::OrderDeletedMessage::parse(iterator.message);
            values[entry + ".udppayload.orderdeletedmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".udppayload.orderdeletedmessage.ordernumber"] = canonical::number(message->order_number.get());
        } else if (iterator.message_type == protocol::OrderReplacedMessage::message_type) {
            values[entry + ".udppayload"] = "packet.messages.message.udppayload.orderreplacedmessage";
            [[maybe_unused]] const auto* message = protocol::OrderReplacedMessage::parse(iterator.message);
            values[entry + ".udppayload.orderreplacedmessage.nanoseconds"] = canonical::number(message->nanoseconds.get());
            values[entry + ".udppayload.orderreplacedmessage.originalordernumber"] = canonical::number(message->original_order_number.get());
            values[entry + ".udppayload.orderreplacedmessage.newordernumber"] = canonical::number(message->new_order_number.get());
            values[entry + ".udppayload.orderreplacedmessage.quantity"] = canonical::number(message->quantity.get());
            values[entry + ".udppayload.orderreplacedmessage.price"] = canonical::scaled(message->price.integer(), -1);
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
    std::printf("== Jnx.JnxEquities.Pts.Itch.v1.7 (modern values)\n");
    int failures = 0;
    failures += check("OrderAddedWithoutAttributesMessage", "Jnx/JnxEquities.Pts.Itch.v1.7/OrderAddedWithoutAttributesMessage.pcap", "jnx/jnxequities/pts/itch/v1.7/OrderAddedWithoutAttributesMessage.values");
    failures += check("OrderDeletedMessage", "Jnx/JnxEquities.Pts.Itch.v1.7/OrderDeletedMessage.pcap", "jnx/jnxequities/pts/itch/v1.7/OrderDeletedMessage.values");
    failures += check("OrderExecutedMessage", "Jnx/JnxEquities.Pts.Itch.v1.7/OrderExecutedMessage.pcap", "jnx/jnxequities/pts/itch/v1.7/OrderExecutedMessage.values");
    failures += check("OrderReplacedMessage", "Jnx/JnxEquities.Pts.Itch.v1.7/OrderReplacedMessage.pcap", "jnx/jnxequities/pts/itch/v1.7/OrderReplacedMessage.values");
    failures += check("SecondsMessage", "Jnx/JnxEquities.Pts.Itch.v1.7/SecondsMessage.pcap", "jnx/jnxequities/pts/itch/v1.7/SecondsMessage.values");
    failures += check("ShortSellingPriceRestrictionStateMessage", "Jnx/JnxEquities.Pts.Itch.v1.7/ShortSellingPriceRestrictionStateMessage.pcap", "jnx/jnxequities/pts/itch/v1.7/ShortSellingPriceRestrictionStateMessage.values");
    failures += check("SystemEventMessage", "Jnx/JnxEquities.Pts.Itch.v1.7/SystemEventMessage.pcap", "jnx/jnxequities/pts/itch/v1.7/SystemEventMessage.values");
    failures += check("TradingStateMessage", "Jnx/JnxEquities.Pts.Itch.v1.7/TradingStateMessage.pcap", "jnx/jnxequities/pts/itch/v1.7/TradingStateMessage.values");
    return failures == 0 ? 0 : 1;
}
