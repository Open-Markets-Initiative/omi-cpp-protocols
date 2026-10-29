// Jnx.JnxEquities.Pts.Itch.v1.7 canonical values, through the Flyweight reader: every value Flyweight reads
// from each sample, at its address, held to what the model reads.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <span>
#include <string>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "tests/canonical/Canonical.hpp"
#include "cpp/binary/flyweight/jnx/jnxequities/pts/itch/v1.7/definitions.hpp"

namespace protocol = ::jnx::jnxequities::pts::itch::v1_7;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        values["packet.packetheader.session"] = canonical::text(std::string(packet.packet_header().session()), '\0', false);
        values["packet.packetheader.sequencenumber"] = canonical::number(packet.packet_header().sequence_number());
        values["packet.packetheader.messagecount"] = canonical::number(packet.packet_header().message_count());
    }

    // a message this test prints no values of, or a code no message answers to, still takes its entry
    template <typename Message>
    void on(const Message&) {
        ++index;
    }

    template <typename Code>
    void on_unknown(Code, std::span<const std::byte>) {
        ++index;
    }

    void on(const protocol::UdpPayloadSecondsMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".udppayload"] = "packet.messages.message.udppayload.secondsmessage";
        values[entry + ".udppayload.secondsmessage.seconds"] = canonical::number(message.seconds());
    }

    void on(const protocol::UdpPayloadSystemEventMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".udppayload"] = "packet.messages.message.udppayload.systemeventmessage";
        values[entry + ".udppayload.systemeventmessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".udppayload.systemeventmessage.group"] = canonical::text(std::string(message.group()), ' ', false);
        values[entry + ".udppayload.systemeventmessage.systemevent"] = canonical::text(canonical::character(message.system_event()), ' ', false);
    }

    void on(const protocol::UdpPayloadPriceTickSizeMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".udppayload"] = "packet.messages.message.udppayload.priceticksizemessage";
        values[entry + ".udppayload.priceticksizemessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".udppayload.priceticksizemessage.priceticksizetableid"] = canonical::number(message.price_tick_size_table_id());
        values[entry + ".udppayload.priceticksizemessage.priceticksize"] = canonical::scaled(message.price_tick_size().mantissa(), message.price_tick_size().exponent());
        values[entry + ".udppayload.priceticksizemessage.pricestart"] = canonical::scaled(message.price_start().mantissa(), message.price_start().exponent());
    }

    void on(const protocol::UdpPayloadOrderbookDirectoryMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".udppayload"] = "packet.messages.message.udppayload.orderbookdirectorymessage";
        values[entry + ".udppayload.orderbookdirectorymessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".udppayload.orderbookdirectorymessage.orderbookid"] = canonical::number(message.orderbook_id());
        values[entry + ".udppayload.orderbookdirectorymessage.orderbookcode"] = canonical::text(std::string(message.orderbook_code()), ' ', false);
        values[entry + ".udppayload.orderbookdirectorymessage.group"] = canonical::text(std::string(message.group()), ' ', false);
        values[entry + ".udppayload.orderbookdirectorymessage.roundlotsize"] = canonical::number(message.round_lot_size());
        values[entry + ".udppayload.orderbookdirectorymessage.priceticksizetableid"] = canonical::number(message.price_tick_size_table_id());
        values[entry + ".udppayload.orderbookdirectorymessage.pricedecimals"] = canonical::number(message.price_decimals());
        values[entry + ".udppayload.orderbookdirectorymessage.upperpricelimit"] = canonical::scaled(message.upper_price_limit().mantissa(), message.upper_price_limit().exponent());
        values[entry + ".udppayload.orderbookdirectorymessage.lowerpricelimit"] = canonical::scaled(message.lower_price_limit().mantissa(), message.lower_price_limit().exponent());
    }

    void on(const protocol::UdpPayloadTradingStateMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".udppayload"] = "packet.messages.message.udppayload.tradingstatemessage";
        values[entry + ".udppayload.tradingstatemessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".udppayload.tradingstatemessage.orderbookid"] = canonical::number(message.orderbook_id());
        values[entry + ".udppayload.tradingstatemessage.group"] = canonical::text(std::string(message.group()), ' ', false);
        values[entry + ".udppayload.tradingstatemessage.tradingstate"] = canonical::text(canonical::character(message.trading_state()), ' ', false);
    }

    void on(const protocol::UdpPayloadShortSellingPriceRestrictionStateMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".udppayload"] = "packet.messages.message.udppayload.shortsellingpricerestrictionstatemessage";
        values[entry + ".udppayload.shortsellingpricerestrictionstatemessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".udppayload.shortsellingpricerestrictionstatemessage.orderbookid"] = canonical::number(message.orderbook_id());
        values[entry + ".udppayload.shortsellingpricerestrictionstatemessage.group"] = canonical::text(std::string(message.group()), ' ', false);
        values[entry + ".udppayload.shortsellingpricerestrictionstatemessage.shortsellingstate"] = canonical::text(canonical::character(message.short_selling_state()), ' ', false);
    }

    void on(const protocol::UdpPayloadOrderAddedWithoutAttributesMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".udppayload"] = "packet.messages.message.udppayload.orderaddedwithoutattributesmessage";
        values[entry + ".udppayload.orderaddedwithoutattributesmessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".udppayload.orderaddedwithoutattributesmessage.ordernumber"] = canonical::number(message.order_number());
        values[entry + ".udppayload.orderaddedwithoutattributesmessage.buysellindicator"] = canonical::text(canonical::character(message.buy_sell_indicator()), ' ', false);
        values[entry + ".udppayload.orderaddedwithoutattributesmessage.quantity"] = canonical::number(message.quantity());
        values[entry + ".udppayload.orderaddedwithoutattributesmessage.orderbookid"] = canonical::number(message.orderbook_id());
        values[entry + ".udppayload.orderaddedwithoutattributesmessage.group"] = canonical::text(std::string(message.group()), ' ', false);
        values[entry + ".udppayload.orderaddedwithoutattributesmessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
    }

    void on(const protocol::UdpPayloadOrderAddedWithAttributesMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".udppayload"] = "packet.messages.message.udppayload.orderaddedwithattributesmessage";
        values[entry + ".udppayload.orderaddedwithattributesmessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".udppayload.orderaddedwithattributesmessage.ordernumber"] = canonical::number(message.order_number());
        values[entry + ".udppayload.orderaddedwithattributesmessage.buysellindicator"] = canonical::text(canonical::character(message.buy_sell_indicator()), ' ', false);
        values[entry + ".udppayload.orderaddedwithattributesmessage.quantity"] = canonical::number(message.quantity());
        values[entry + ".udppayload.orderaddedwithattributesmessage.orderbookid"] = canonical::number(message.orderbook_id());
        values[entry + ".udppayload.orderaddedwithattributesmessage.group"] = canonical::text(std::string(message.group()), ' ', false);
        values[entry + ".udppayload.orderaddedwithattributesmessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".udppayload.orderaddedwithattributesmessage.attribution"] = canonical::text(std::string(message.attribution()), ' ', false);
        values[entry + ".udppayload.orderaddedwithattributesmessage.ordertype"] = canonical::text(canonical::character(message.order_type()), ' ', false);
    }

    void on(const protocol::UdpPayloadOrderExecutedMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".udppayload"] = "packet.messages.message.udppayload.orderexecutedmessage";
        values[entry + ".udppayload.orderexecutedmessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".udppayload.orderexecutedmessage.ordernumber"] = canonical::number(message.order_number());
        values[entry + ".udppayload.orderexecutedmessage.executedquantity"] = canonical::number(message.executed_quantity());
        values[entry + ".udppayload.orderexecutedmessage.matchnumber"] = canonical::number(message.match_number());
    }

    void on(const protocol::UdpPayloadOrderDeletedMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".udppayload"] = "packet.messages.message.udppayload.orderdeletedmessage";
        values[entry + ".udppayload.orderdeletedmessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".udppayload.orderdeletedmessage.ordernumber"] = canonical::number(message.order_number());
    }

    void on(const protocol::UdpPayloadOrderReplacedMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".udppayload"] = "packet.messages.message.udppayload.orderreplacedmessage";
        values[entry + ".udppayload.orderreplacedmessage.nanoseconds"] = canonical::number(message.nanoseconds());
        values[entry + ".udppayload.orderreplacedmessage.originalordernumber"] = canonical::number(message.original_order_number());
        values[entry + ".udppayload.orderreplacedmessage.newordernumber"] = canonical::number(message.new_order_number());
        values[entry + ".udppayload.orderreplacedmessage.quantity"] = canonical::number(message.quantity());
        values[entry + ".udppayload.orderreplacedmessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
    }
};

// The values the Flyweight reader reads from one datagram, by indexed address. A datagram it cannot
// read is a value the model never reads, so it fails rather than passing with nothing compared.
canonical::Listing read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::PacketReader::read(std::span<const std::byte>(frame.payload, frame.payload_len), reader);
    } catch (const protocol::DecodeError& error) {
        reader.values["(does not decode)"] = error.what();
    }

    return reader.values;
}

// Read each datagram of a sample with Flyweight and hold it to the model's values
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
    std::printf("== Jnx.JnxEquities.Pts.Itch.v1.7 (flyweight values)\n");
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
