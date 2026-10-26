// Jpx.TseEquities.MarketByOrder.Flex.v1.1 canonical values, through the Classes Packet: every value Classes decodes from
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
#include "cpp/binary/classes/jpx/tseequities/marketbyorder/flex/v1.1/definitions.hpp"

namespace protocol = ::jpx::tseequities::marketbyorder::flex::v1_1;

namespace {

// The values the Classes Packet decodes from one datagram, by indexed address. A datagram it cannot
// decode is a value the model never reads, so it fails rather than passing with nothing compared.
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::UdpPacket packet;

    try {
        packet.decode(frame.payload, frame.payload_len);
    } catch (const protocol::DecodeError& error) {
        values["(does not decode)"] = error.what();
        return values;
    }

    values["udppacket.packetheader.multicastgroupnumber"] = canonical::number(packet.packet_header().multicast_group_number());
    values["udppacket.packetheader.numberofsystemreboots"] = canonical::number(packet.packet_header().number_of_system_reboots());
    values["udppacket.packetheader.sequencenumber"] = canonical::number(packet.packet_header().sequence_number());
    values["udppacket.packetheader.issuecode"] = canonical::text(std::string(packet.packet_header().issue_code()), ' ', false);
    values["udppacket.packetheader.updatenumber"] = canonical::number(packet.packet_header().update_number());
    values["udppacket.packetheader.packetnumber"] = canonical::number(packet.packet_header().packet_number());
    values["udppacket.packetheader.totalnumberofpackets"] = canonical::number(packet.packet_header().total_number_of_packets());
    values["udppacket.packetheader.utilityflag"] = canonical::number(packet.packet_header().utility_flag());
    values["udppacket.packetheader.messagecount"] = canonical::number(packet.packet_header().message_count());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.taglength"] = canonical::number(each.message_header().tag_length());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(each.message_header().message_type()));

        if (const auto* message = dynamic_cast<const protocol::SecondsTimestampMessage*>(each.message())) {
            values[entry + ".payload"] = "udppacket.message.payload.secondstimestampmessage";
            values[entry + ".payload.secondstimestampmessage.timeseconds"] = canonical::number((*message).time_seconds());
        } else if (const auto* message = dynamic_cast<const protocol::TradingStatusMessage*>(each.message())) {
            values[entry + ".payload"] = "udppacket.message.payload.tradingstatusmessage";
            values[entry + ".payload.tradingstatusmessage.timemicroseconds"] = canonical::number((*message).time_microseconds());
            values[entry + ".payload.tradingstatusmessage.marketstatus"] = canonical::number((*message).market_status());
            values[entry + ".payload.tradingstatusmessage.statusflag"] = canonical::text(std::string((*message).status_flag()), ' ', false);
            values[entry + ".payload.tradingstatusmessage.shortsellingstatus"] = canonical::number((*message).short_selling_status());
            values[entry + ".payload.tradingstatusmessage.pricingmethod"] = canonical::number((*message).pricing_method());
            values[entry + ".payload.tradingstatusmessage.bookcenterprice"] = canonical::scaled((*message).book_center_price().mantissa(), (*message).book_center_price().exponent());
        } else if (const auto* message = dynamic_cast<const protocol::ExecutionSummaryMessage*>(each.message())) {
            values[entry + ".payload"] = "udppacket.message.payload.executionsummarymessage";
            values[entry + ".payload.executionsummarymessage.timemicroseconds"] = canonical::number((*message).time_microseconds());
            values[entry + ".payload.executionsummarymessage.triggeredside"] = canonical::text(canonical::character((*message).triggered_side()));
            values[entry + ".payload.executionsummarymessage.totalvolume"] = canonical::number((*message).total_volume());
            values[entry + ".payload.executionsummarymessage.totalinvalidation"] = canonical::number((*message).total_invalidation());
            values[entry + ".payload.executionsummarymessage.lastprice"] = canonical::scaled((*message).last_price().mantissa(), (*message).last_price().exponent());
            values[entry + ".payload.executionsummarymessage.matchid"] = canonical::number((*message).match_id());
            values[entry + ".payload.executionsummarymessage.bestoffer"] = ((*message).best_offer().has_value() ? canonical::scaled((*(*message).best_offer()).mantissa(), (*(*message).best_offer()).exponent()) : canonical::absent());
            values[entry + ".payload.executionsummarymessage.bestbid"] = ((*message).best_bid().has_value() ? canonical::scaled((*(*message).best_bid()).mantissa(), (*(*message).best_bid()).exponent()) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderMessage*>(each.message())) {
            values[entry + ".payload"] = "udppacket.message.payload.addordermessage";
            values[entry + ".payload.addordermessage.timemicroseconds"] = canonical::number((*message).time_microseconds());
            values[entry + ".payload.addordermessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.addordermessage.side"] = canonical::text(canonical::character((*message).side()));
            values[entry + ".payload.addordermessage.quantity"] = canonical::number((*message).quantity());
            values[entry + ".payload.addordermessage.price"] = ((*message).price().has_value() ? canonical::scaled((*(*message).price()).mantissa(), (*(*message).price()).exponent()) : canonical::absent());
            values[entry + ".payload.addordermessage.ordercondition"] = canonical::number((*message).order_condition());
            values[entry + ".payload.addordermessage.modificationflag"] = canonical::number((*message).modification_flag());
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedMessage*>(each.message())) {
            values[entry + ".payload"] = "udppacket.message.payload.orderexecutedmessage";
            values[entry + ".payload.orderexecutedmessage.timemicroseconds"] = canonical::number((*message).time_microseconds());
            values[entry + ".payload.orderexecutedmessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.orderexecutedmessage.side"] = canonical::text(canonical::character((*message).side()));
            values[entry + ".payload.orderexecutedmessage.volume"] = canonical::number((*message).volume());
            values[entry + ".payload.orderexecutedmessage.matchid"] = canonical::number((*message).match_id());
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedWithPriceMessage*>(each.message())) {
            values[entry + ".payload"] = "udppacket.message.payload.orderexecutedwithpricemessage";
            values[entry + ".payload.orderexecutedwithpricemessage.timemicroseconds"] = canonical::number((*message).time_microseconds());
            values[entry + ".payload.orderexecutedwithpricemessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.orderexecutedwithpricemessage.side"] = canonical::text(canonical::character((*message).side()));
            values[entry + ".payload.orderexecutedwithpricemessage.volume"] = canonical::number((*message).volume());
            values[entry + ".payload.orderexecutedwithpricemessage.matchid"] = canonical::number((*message).match_id());
            values[entry + ".payload.orderexecutedwithpricemessage.executionprice"] = canonical::scaled((*message).execution_price().mantissa(), (*message).execution_price().exponent());
            values[entry + ".payload.orderexecutedwithpricemessage.adoptedpricingmethod"] = canonical::number((*message).adopted_pricing_method());
        } else if (const auto* message = dynamic_cast<const protocol::OrderDeleteMessage*>(each.message())) {
            values[entry + ".payload"] = "udppacket.message.payload.orderdeletemessage";
            values[entry + ".payload.orderdeletemessage.timemicroseconds"] = canonical::number((*message).time_microseconds());
            values[entry + ".payload.orderdeletemessage.orderid"] = canonical::number((*message).order_id());
            values[entry + ".payload.orderdeletemessage.side"] = canonical::text(canonical::character((*message).side()));
            values[entry + ".payload.orderdeletemessage.modificationflag"] = canonical::number((*message).modification_flag());
        } else if (const auto* message = dynamic_cast<const protocol::ResetMessage*>(each.message())) {
            values[entry + ".payload"] = "udppacket.message.payload.resetmessage";
            values[entry + ".payload.resetmessage.resetstartendflag"] = canonical::number((*message).reset_start_end_flag());
        } else if (const auto* message = dynamic_cast<const protocol::CommunicationControlMessage*>(each.message())) {
            values[entry + ".payload"] = "udppacket.message.payload.communicationcontrolmessage";
            values[entry + ".payload.communicationcontrolmessage.testmodeflag"] = canonical::number((*message).test_mode_flag());
            values[entry + ".payload.communicationcontrolmessage.communicationstartendflag"] = canonical::number((*message).communication_start_end_flag());
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
    std::printf("== Jpx.TseEquities.MarketByOrder.Flex.v1.1 (classes values)\n");
    int failures = 0;
    failures += check("AddOrderMessage", "Jpx/TseEquities.MarketByOrder.Flex.v1.1/AddOrderMessage.pcap", "jpx/tseequities/marketbyorder/flex/v1.1/AddOrderMessage.values");
    failures += check("CommunicationControlMessage", "Jpx/TseEquities.MarketByOrder.Flex.v1.1/CommunicationControlMessage.pcap", "jpx/tseequities/marketbyorder/flex/v1.1/CommunicationControlMessage.values");
    failures += check("OrderDeleteMessage", "Jpx/TseEquities.MarketByOrder.Flex.v1.1/OrderDeleteMessage.pcap", "jpx/tseequities/marketbyorder/flex/v1.1/OrderDeleteMessage.values");
    failures += check("TradingStatusMessage", "Jpx/TseEquities.MarketByOrder.Flex.v1.1/TradingStatusMessage.pcap", "jpx/tseequities/marketbyorder/flex/v1.1/TradingStatusMessage.values");
    return failures == 0 ? 0 : 1;
}
