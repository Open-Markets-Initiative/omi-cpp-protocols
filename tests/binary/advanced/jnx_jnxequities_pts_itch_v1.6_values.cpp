// Jnx.JnxEquities.Pts.Itch.v1.6 canonical values, through the Advanced session layer: every value Advanced
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
#include "cpp/binary/advanced/jnx/jnxequities/pts/itch/v1.6/messages/session.hpp"

namespace protocol = ::jnx::jnxequities::pts::itch::v1_6;

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

    void on_message(const protocol::system_event_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.systemeventmessage";
        values[entry + ".payload.systemeventmessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.systemeventmessage.group"] = canonical::text(std::string(message.fields.group.get().value()), ' ', false);
        values[entry + ".payload.systemeventmessage.systemevent"] = canonical::text(canonical::character(message.fields.system_event.get().value()), ' ', false);
    }

    void on_message(const protocol::price_tick_size_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.priceticksizemessage";
        values[entry + ".payload.priceticksizemessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.priceticksizemessage.priceticksizetableid"] = canonical::number(message.fields.price_tick_size_table_id.get().value());
        values[entry + ".payload.priceticksizemessage.priceticksize"] = canonical::scaled(message.fields.price_tick_size.get().value(), -1);
        values[entry + ".payload.priceticksizemessage.pricestart"] = canonical::scaled(message.fields.price_start.get().value(), -1);
    }

    void on_message(const protocol::orderbook_directory_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.orderbookdirectorymessage";
        values[entry + ".payload.orderbookdirectorymessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.orderbookdirectorymessage.orderbookid"] = canonical::number(message.fields.orderbook_id.get().value());
        values[entry + ".payload.orderbookdirectorymessage.orderbookcode"] = canonical::text(std::string(message.fields.orderbook_code.get().value()), ' ', false);
        values[entry + ".payload.orderbookdirectorymessage.group"] = canonical::text(std::string(message.fields.group.get().value()), ' ', false);
        values[entry + ".payload.orderbookdirectorymessage.roundlotsize"] = canonical::number(message.fields.round_lot_size.get().value());
        values[entry + ".payload.orderbookdirectorymessage.priceticksizetableid"] = canonical::number(message.fields.price_tick_size_table_id.get().value());
        values[entry + ".payload.orderbookdirectorymessage.pricedecimals"] = canonical::number(message.fields.price_decimals.get().value());
        values[entry + ".payload.orderbookdirectorymessage.upperpricelimit"] = canonical::scaled(message.fields.upper_price_limit.get().value(), -1);
        values[entry + ".payload.orderbookdirectorymessage.lowerpricelimit"] = canonical::scaled(message.fields.lower_price_limit.get().value(), -1);
    }

    void on_message(const protocol::trading_state_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.tradingstatemessage";
        values[entry + ".payload.tradingstatemessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.tradingstatemessage.orderbookid"] = canonical::number(message.fields.orderbook_id.get().value());
        values[entry + ".payload.tradingstatemessage.group"] = canonical::text(std::string(message.fields.group.get().value()), ' ', false);
        values[entry + ".payload.tradingstatemessage.tradingstate"] = canonical::text(canonical::character(message.fields.trading_state.get().value()), ' ', false);
    }

    void on_message(const protocol::short_selling_price_restriction_state_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.shortsellingpricerestrictionstatemessage";
        values[entry + ".payload.shortsellingpricerestrictionstatemessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.shortsellingpricerestrictionstatemessage.orderbookid"] = canonical::number(message.fields.orderbook_id.get().value());
        values[entry + ".payload.shortsellingpricerestrictionstatemessage.group"] = canonical::text(std::string(message.fields.group.get().value()), ' ', false);
        values[entry + ".payload.shortsellingpricerestrictionstatemessage.shortsellingstate"] = canonical::text(canonical::character(message.fields.short_selling_state.get().value()), ' ', false);
    }

    void on_message(const protocol::order_added_without_attributes_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.orderaddedwithoutattributesmessage";
        values[entry + ".payload.orderaddedwithoutattributesmessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.orderaddedwithoutattributesmessage.ordernumber"] = canonical::number(message.fields.order_number.get().value());
        values[entry + ".payload.orderaddedwithoutattributesmessage.buysellindicator"] = canonical::text(canonical::character(message.fields.buy_sell_indicator.get().value()), ' ', false);
        values[entry + ".payload.orderaddedwithoutattributesmessage.quantity"] = canonical::number(message.fields.quantity.get().value());
        values[entry + ".payload.orderaddedwithoutattributesmessage.orderbookid"] = canonical::number(message.fields.orderbook_id.get().value());
        values[entry + ".payload.orderaddedwithoutattributesmessage.group"] = canonical::text(std::string(message.fields.group.get().value()), ' ', false);
        values[entry + ".payload.orderaddedwithoutattributesmessage.price"] = canonical::scaled(message.fields.price.get().value(), -1);
    }

    void on_message(const protocol::order_added_with_attributes_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.orderaddedwithattributesmessage";
        values[entry + ".payload.orderaddedwithattributesmessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.orderaddedwithattributesmessage.ordernumber"] = canonical::number(message.fields.order_number.get().value());
        values[entry + ".payload.orderaddedwithattributesmessage.buysellindicator"] = canonical::text(canonical::character(message.fields.buy_sell_indicator.get().value()), ' ', false);
        values[entry + ".payload.orderaddedwithattributesmessage.quantity"] = canonical::number(message.fields.quantity.get().value());
        values[entry + ".payload.orderaddedwithattributesmessage.orderbookid"] = canonical::number(message.fields.orderbook_id.get().value());
        values[entry + ".payload.orderaddedwithattributesmessage.group"] = canonical::text(std::string(message.fields.group.get().value()), ' ', false);
        values[entry + ".payload.orderaddedwithattributesmessage.price"] = canonical::scaled(message.fields.price.get().value(), -1);
        values[entry + ".payload.orderaddedwithattributesmessage.attribution"] = canonical::text(std::string(message.fields.attribution.get().value()), ' ', false);
        values[entry + ".payload.orderaddedwithattributesmessage.ordertype"] = canonical::text(canonical::character(message.fields.order_type.get().value()), ' ', false);
    }

    void on_message(const protocol::order_executed_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedmessage";
        values[entry + ".payload.orderexecutedmessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.orderexecutedmessage.ordernumber"] = canonical::number(message.fields.order_number.get().value());
        values[entry + ".payload.orderexecutedmessage.executedquantity"] = canonical::number(message.fields.executed_quantity.get().value());
        values[entry + ".payload.orderexecutedmessage.matchnumber"] = canonical::number(message.fields.match_number.get().value());
    }

    void on_message(const protocol::order_deleted_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.orderdeletedmessage";
        values[entry + ".payload.orderdeletedmessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.orderdeletedmessage.ordernumber"] = canonical::number(message.fields.order_number.get().value());
    }

    void on_message(const protocol::order_replaced_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.orderreplacedmessage";
        values[entry + ".payload.orderreplacedmessage.nanoseconds"] = canonical::number(message.fields.nanoseconds.get().value());
        values[entry + ".payload.orderreplacedmessage.originalordernumber"] = canonical::number(message.fields.original_order_number.get().value());
        values[entry + ".payload.orderreplacedmessage.newordernumber"] = canonical::number(message.fields.new_order_number.get().value());
        values[entry + ".payload.orderreplacedmessage.quantity"] = canonical::number(message.fields.quantity.get().value());
        values[entry + ".payload.orderreplacedmessage.price"] = canonical::scaled(message.fields.price.get().value(), -1);
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
    std::printf("== Jnx.JnxEquities.Pts.Itch.v1.6 (advanced values)\n");
    int failures = 0;
    failures += check("OrderDeletedMessage", "Jnx/JnxEquities.Pts.Itch.v1.6/OrderDeletedMessage.pcap", "jnx/jnxequities/pts/itch/v1.6/OrderDeletedMessage.values");
    failures += check("OrderExecutedMessage", "Jnx/JnxEquities.Pts.Itch.v1.6/OrderExecutedMessage.pcap", "jnx/jnxequities/pts/itch/v1.6/OrderExecutedMessage.values");
    failures += check("OrderReplacedMessage", "Jnx/JnxEquities.Pts.Itch.v1.6/OrderReplacedMessage.pcap", "jnx/jnxequities/pts/itch/v1.6/OrderReplacedMessage.values");
    failures += check("SecondsMessage", "Jnx/JnxEquities.Pts.Itch.v1.6/SecondsMessage.pcap", "jnx/jnxequities/pts/itch/v1.6/SecondsMessage.values");
    failures += check("ShortSellingPriceRestrictionStateMessage", "Jnx/JnxEquities.Pts.Itch.v1.6/ShortSellingPriceRestrictionStateMessage.pcap", "jnx/jnxequities/pts/itch/v1.6/ShortSellingPriceRestrictionStateMessage.values");
    return failures == 0 ? 0 : 1;
}
