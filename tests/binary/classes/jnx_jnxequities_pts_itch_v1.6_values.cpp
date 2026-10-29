// Jnx.JnxEquities.Pts.Itch.v1.6 canonical values, through the Classes Packet: every value Classes decodes from
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
#include "cpp/binary/classes/jnx/jnxequities/pts/itch/v1.6/definitions.hpp"

namespace protocol = ::jnx::jnxequities::pts::itch::v1_6;

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
        } else if (const auto* message = dynamic_cast<const protocol::SystemEventMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.systemeventmessage";
            values[entry + ".payload.systemeventmessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.systemeventmessage.group"] = canonical::text(std::string((*message).group()), ' ', false);
            values[entry + ".payload.systemeventmessage.systemevent"] = canonical::text(canonical::character((*message).system_event()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::PriceTickSizeMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.priceticksizemessage";
            values[entry + ".payload.priceticksizemessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.priceticksizemessage.priceticksizetableid"] = canonical::number((*message).price_tick_size_table_id());
            values[entry + ".payload.priceticksizemessage.priceticksize"] = canonical::scaled((*message).price_tick_size().mantissa(), (*message).price_tick_size().exponent());
            values[entry + ".payload.priceticksizemessage.pricestart"] = canonical::scaled((*message).price_start().mantissa(), (*message).price_start().exponent());
        } else if (const auto* message = dynamic_cast<const protocol::OrderbookDirectoryMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderbookdirectorymessage";
            values[entry + ".payload.orderbookdirectorymessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.orderbookdirectorymessage.orderbookid"] = canonical::number((*message).orderbook_id());
            values[entry + ".payload.orderbookdirectorymessage.orderbookcode"] = canonical::text(std::string((*message).orderbook_code()), ' ', false);
            values[entry + ".payload.orderbookdirectorymessage.group"] = canonical::text(std::string((*message).group()), ' ', false);
            values[entry + ".payload.orderbookdirectorymessage.roundlotsize"] = canonical::number((*message).round_lot_size());
            values[entry + ".payload.orderbookdirectorymessage.priceticksizetableid"] = canonical::number((*message).price_tick_size_table_id());
            values[entry + ".payload.orderbookdirectorymessage.pricedecimals"] = canonical::number((*message).price_decimals());
            values[entry + ".payload.orderbookdirectorymessage.upperpricelimit"] = canonical::scaled((*message).upper_price_limit().mantissa(), (*message).upper_price_limit().exponent());
            values[entry + ".payload.orderbookdirectorymessage.lowerpricelimit"] = canonical::scaled((*message).lower_price_limit().mantissa(), (*message).lower_price_limit().exponent());
        } else if (const auto* message = dynamic_cast<const protocol::TradingStateMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.tradingstatemessage";
            values[entry + ".payload.tradingstatemessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.tradingstatemessage.orderbookid"] = canonical::number((*message).orderbook_id());
            values[entry + ".payload.tradingstatemessage.group"] = canonical::text(std::string((*message).group()), ' ', false);
            values[entry + ".payload.tradingstatemessage.tradingstate"] = canonical::text(canonical::character((*message).trading_state()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::ShortSellingPriceRestrictionStateMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.shortsellingpricerestrictionstatemessage";
            values[entry + ".payload.shortsellingpricerestrictionstatemessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.shortsellingpricerestrictionstatemessage.orderbookid"] = canonical::number((*message).orderbook_id());
            values[entry + ".payload.shortsellingpricerestrictionstatemessage.group"] = canonical::text(std::string((*message).group()), ' ', false);
            values[entry + ".payload.shortsellingpricerestrictionstatemessage.shortsellingstate"] = canonical::text(canonical::character((*message).short_selling_state()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::OrderAddedWithoutAttributesMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderaddedwithoutattributesmessage";
            values[entry + ".payload.orderaddedwithoutattributesmessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.orderaddedwithoutattributesmessage.ordernumber"] = canonical::number((*message).order_number());
            values[entry + ".payload.orderaddedwithoutattributesmessage.buysellindicator"] = canonical::text(canonical::character((*message).buy_sell_indicator()), ' ', false);
            values[entry + ".payload.orderaddedwithoutattributesmessage.quantity"] = canonical::number((*message).quantity());
            values[entry + ".payload.orderaddedwithoutattributesmessage.orderbookid"] = canonical::number((*message).orderbook_id());
            values[entry + ".payload.orderaddedwithoutattributesmessage.group"] = canonical::text(std::string((*message).group()), ' ', false);
            values[entry + ".payload.orderaddedwithoutattributesmessage.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
        } else if (const auto* message = dynamic_cast<const protocol::OrderAddedWithAttributesMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderaddedwithattributesmessage";
            values[entry + ".payload.orderaddedwithattributesmessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.orderaddedwithattributesmessage.ordernumber"] = canonical::number((*message).order_number());
            values[entry + ".payload.orderaddedwithattributesmessage.buysellindicator"] = canonical::text(canonical::character((*message).buy_sell_indicator()), ' ', false);
            values[entry + ".payload.orderaddedwithattributesmessage.quantity"] = canonical::number((*message).quantity());
            values[entry + ".payload.orderaddedwithattributesmessage.orderbookid"] = canonical::number((*message).orderbook_id());
            values[entry + ".payload.orderaddedwithattributesmessage.group"] = canonical::text(std::string((*message).group()), ' ', false);
            values[entry + ".payload.orderaddedwithattributesmessage.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
            values[entry + ".payload.orderaddedwithattributesmessage.attribution"] = canonical::text(std::string((*message).attribution()), ' ', false);
            values[entry + ".payload.orderaddedwithattributesmessage.ordertype"] = canonical::text(canonical::character((*message).order_type()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedmessage";
            values[entry + ".payload.orderexecutedmessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.orderexecutedmessage.ordernumber"] = canonical::number((*message).order_number());
            values[entry + ".payload.orderexecutedmessage.executedquantity"] = canonical::number((*message).executed_quantity());
            values[entry + ".payload.orderexecutedmessage.matchnumber"] = canonical::number((*message).match_number());
        } else if (const auto* message = dynamic_cast<const protocol::OrderDeletedMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderdeletedmessage";
            values[entry + ".payload.orderdeletedmessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.orderdeletedmessage.ordernumber"] = canonical::number((*message).order_number());
        } else if (const auto* message = dynamic_cast<const protocol::OrderReplacedMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.orderreplacedmessage";
            values[entry + ".payload.orderreplacedmessage.nanoseconds"] = canonical::number((*message).nanoseconds());
            values[entry + ".payload.orderreplacedmessage.originalordernumber"] = canonical::number((*message).original_order_number());
            values[entry + ".payload.orderreplacedmessage.newordernumber"] = canonical::number((*message).new_order_number());
            values[entry + ".payload.orderreplacedmessage.quantity"] = canonical::number((*message).quantity());
            values[entry + ".payload.orderreplacedmessage.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
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
    std::printf("== Jnx.JnxEquities.Pts.Itch.v1.6 (classes values)\n");
    int failures = 0;
    failures += check("OrderDeletedMessage", "Jnx/JnxEquities.Pts.Itch.v1.6/OrderDeletedMessage.pcap", "jnx/jnxequities/pts/itch/v1.6/OrderDeletedMessage.values");
    failures += check("OrderExecutedMessage", "Jnx/JnxEquities.Pts.Itch.v1.6/OrderExecutedMessage.pcap", "jnx/jnxequities/pts/itch/v1.6/OrderExecutedMessage.values");
    failures += check("OrderReplacedMessage", "Jnx/JnxEquities.Pts.Itch.v1.6/OrderReplacedMessage.pcap", "jnx/jnxequities/pts/itch/v1.6/OrderReplacedMessage.values");
    failures += check("SecondsMessage", "Jnx/JnxEquities.Pts.Itch.v1.6/SecondsMessage.pcap", "jnx/jnxequities/pts/itch/v1.6/SecondsMessage.values");
    failures += check("ShortSellingPriceRestrictionStateMessage", "Jnx/JnxEquities.Pts.Itch.v1.6/ShortSellingPriceRestrictionStateMessage.pcap", "jnx/jnxequities/pts/itch/v1.6/ShortSellingPriceRestrictionStateMessage.values");
    return failures == 0 ? 0 : 1;
}
