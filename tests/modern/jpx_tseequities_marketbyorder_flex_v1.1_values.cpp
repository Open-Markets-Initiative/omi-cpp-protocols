// Jpx.TseEquities.MarketByOrder.Flex.v1.1 canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/modern/jpx/tseequities/marketbyorder/flex/v1.1/definitions.hpp"

namespace protocol = ::jpx::tseequities::marketbyorder::flex::v1_1;

namespace {

// The values the Modern iterator reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    values["udppacket.packetheader.multicastgroupnumber"] = canonical::number(iterator.packet_header->multicast_group_number.get());
    values["udppacket.packetheader.numberofsystemreboots"] = canonical::number(iterator.packet_header->number_of_system_reboots.get());
    values["udppacket.packetheader.sequencenumber"] = canonical::number(iterator.packet_header->sequence_number.get());
    values["udppacket.packetheader.issuecode"] = canonical::text(std::string(iterator.packet_header->issue_code.get()), ' ', false);
    values["udppacket.packetheader.updatenumber"] = canonical::number(iterator.packet_header->update_number.get());
    values["udppacket.packetheader.packetnumber"] = canonical::number(iterator.packet_header->packet_number.get());
    values["udppacket.packetheader.totalnumberofpackets"] = canonical::number(iterator.packet_header->total_number_of_packets.get());
    values["udppacket.packetheader.utilityflag"] = canonical::number(iterator.packet_header->utility_flag.get());
    values["udppacket.packetheader.messagecount"] = canonical::number(iterator.packet_header->message_count.get());

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.taglength"] = canonical::number(iterator.message_header->tag_length.get());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(iterator.message_header->message_type.get()));

        if (iterator.message_type == protocol::SecondsTimestampMessage::message_type) {
            values[entry + ".payload"] = "udppacket.message.payload.secondstimestampmessage";
            [[maybe_unused]] const auto* message = protocol::SecondsTimestampMessage::parse(iterator.message);
            values[entry + ".payload.secondstimestampmessage.timeseconds"] = canonical::number(message->time_seconds.get());
        } else if (iterator.message_type == protocol::TradingStatusMessage::message_type) {
            values[entry + ".payload"] = "udppacket.message.payload.tradingstatusmessage";
            [[maybe_unused]] const auto* message = protocol::TradingStatusMessage::parse(iterator.message);
            values[entry + ".payload.tradingstatusmessage.timemicroseconds"] = canonical::number(message->time_microseconds.get());
            values[entry + ".payload.tradingstatusmessage.marketstatus"] = canonical::number(message->market_status.get());
            values[entry + ".payload.tradingstatusmessage.statusflag"] = canonical::text(std::string(message->status_flag.get()), ' ', false);
            values[entry + ".payload.tradingstatusmessage.shortsellingstatus"] = canonical::number(message->short_selling_status.get());
            values[entry + ".payload.tradingstatusmessage.pricingmethod"] = canonical::number(message->pricing_method.get());
            values[entry + ".payload.tradingstatusmessage.bookcenterprice"] = canonical::scaled(message->book_center_price.integer(), -4);
        } else if (iterator.message_type == protocol::ExecutionSummaryMessage::message_type) {
            values[entry + ".payload"] = "udppacket.message.payload.executionsummarymessage";
            [[maybe_unused]] const auto* message = protocol::ExecutionSummaryMessage::parse(iterator.message);
            values[entry + ".payload.executionsummarymessage.timemicroseconds"] = canonical::number(message->time_microseconds.get());
            values[entry + ".payload.executionsummarymessage.triggeredside"] = canonical::text(canonical::character(message->triggered_side.get()));
            values[entry + ".payload.executionsummarymessage.totalvolume"] = canonical::number(message->total_volume.get());
            values[entry + ".payload.executionsummarymessage.totalinvalidation"] = canonical::number(message->total_invalidation.get());
            values[entry + ".payload.executionsummarymessage.lastprice"] = canonical::scaled(message->last_price.integer(), -4);
            values[entry + ".payload.executionsummarymessage.matchid"] = canonical::number(message->match_id.get());
        } else if (iterator.message_type == protocol::AddOrderMessage::message_type) {
            values[entry + ".payload"] = "udppacket.message.payload.addordermessage";
            [[maybe_unused]] const auto* message = protocol::AddOrderMessage::parse(iterator.message);
            values[entry + ".payload.addordermessage.timemicroseconds"] = canonical::number(message->time_microseconds.get());
            values[entry + ".payload.addordermessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.addordermessage.side"] = canonical::text(canonical::character(message->side.get()));
            values[entry + ".payload.addordermessage.quantity"] = canonical::number(message->quantity.get());
            values[entry + ".payload.addordermessage.ordercondition"] = canonical::number(message->order_condition.get());
            values[entry + ".payload.addordermessage.modificationflag"] = canonical::number(message->modification_flag.get());
        } else if (iterator.message_type == protocol::OrderExecutedMessage::message_type) {
            values[entry + ".payload"] = "udppacket.message.payload.orderexecutedmessage";
            [[maybe_unused]] const auto* message = protocol::OrderExecutedMessage::parse(iterator.message);
            values[entry + ".payload.orderexecutedmessage.timemicroseconds"] = canonical::number(message->time_microseconds.get());
            values[entry + ".payload.orderexecutedmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.orderexecutedmessage.side"] = canonical::text(canonical::character(message->side.get()));
            values[entry + ".payload.orderexecutedmessage.volume"] = canonical::number(message->volume.get());
            values[entry + ".payload.orderexecutedmessage.matchid"] = canonical::number(message->match_id.get());
        } else if (iterator.message_type == protocol::OrderExecutedWithPriceMessage::message_type) {
            values[entry + ".payload"] = "udppacket.message.payload.orderexecutedwithpricemessage";
            [[maybe_unused]] const auto* message = protocol::OrderExecutedWithPriceMessage::parse(iterator.message);
            values[entry + ".payload.orderexecutedwithpricemessage.timemicroseconds"] = canonical::number(message->time_microseconds.get());
            values[entry + ".payload.orderexecutedwithpricemessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.orderexecutedwithpricemessage.side"] = canonical::text(canonical::character(message->side.get()));
            values[entry + ".payload.orderexecutedwithpricemessage.volume"] = canonical::number(message->volume.get());
            values[entry + ".payload.orderexecutedwithpricemessage.matchid"] = canonical::number(message->match_id.get());
            values[entry + ".payload.orderexecutedwithpricemessage.executionprice"] = canonical::scaled(message->execution_price.integer(), -4);
            values[entry + ".payload.orderexecutedwithpricemessage.adoptedpricingmethod"] = canonical::number(message->adopted_pricing_method.get());
        } else if (iterator.message_type == protocol::OrderDeleteMessage::message_type) {
            values[entry + ".payload"] = "udppacket.message.payload.orderdeletemessage";
            [[maybe_unused]] const auto* message = protocol::OrderDeleteMessage::parse(iterator.message);
            values[entry + ".payload.orderdeletemessage.timemicroseconds"] = canonical::number(message->time_microseconds.get());
            values[entry + ".payload.orderdeletemessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.orderdeletemessage.side"] = canonical::text(canonical::character(message->side.get()));
            values[entry + ".payload.orderdeletemessage.modificationflag"] = canonical::number(message->modification_flag.get());
        } else if (iterator.message_type == protocol::ResetMessage::message_type) {
            values[entry + ".payload"] = "udppacket.message.payload.resetmessage";
            [[maybe_unused]] const auto* message = protocol::ResetMessage::parse(iterator.message);
            values[entry + ".payload.resetmessage.resetstartendflag"] = canonical::number(message->reset_start_end_flag.get());
        } else if (iterator.message_type == protocol::CommunicationControlMessage::message_type) {
            values[entry + ".payload"] = "udppacket.message.payload.communicationcontrolmessage";
            [[maybe_unused]] const auto* message = protocol::CommunicationControlMessage::parse(iterator.message);
            values[entry + ".payload.communicationcontrolmessage.testmodeflag"] = canonical::number(message->test_mode_flag.get());
            values[entry + ".payload.communicationcontrolmessage.communicationstartendflag"] = canonical::number(message->communication_start_end_flag.get());
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
    std::printf("== Jpx.TseEquities.MarketByOrder.Flex.v1.1 (modern values)\n");
    int failures = 0;
    failures += check("AddOrderMessage", "Jpx/TseEquities.MarketByOrder.Flex.v1.1/AddOrderMessage.pcap", "jpx/tseequities/marketbyorder/flex/v1.1/AddOrderMessage.values");
    failures += check("CommunicationControlMessage", "Jpx/TseEquities.MarketByOrder.Flex.v1.1/CommunicationControlMessage.pcap", "jpx/tseequities/marketbyorder/flex/v1.1/CommunicationControlMessage.values");
    failures += check("OrderDeleteMessage", "Jpx/TseEquities.MarketByOrder.Flex.v1.1/OrderDeleteMessage.pcap", "jpx/tseequities/marketbyorder/flex/v1.1/OrderDeleteMessage.values");
    failures += check("TradingStatusMessage", "Jpx/TseEquities.MarketByOrder.Flex.v1.1/TradingStatusMessage.pcap", "jpx/tseequities/marketbyorder/flex/v1.1/TradingStatusMessage.values");
    return failures == 0 ? 0 : 1;
}