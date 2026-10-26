// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d canonical values, through the Classes Packet: every value Classes decodes from
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
#include "cpp/classes/miax/pearlequities/depthofmarket/mach/v1.3.d/definitions.hpp"

namespace protocol = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

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


    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        const std::string entry = "udppacket.machmessage[" + std::to_string(index++) + "]";
        values[entry + ".machpacketheader.sequencenumber"] = canonical::number(each.mach_packet_header().sequence_number());
        values[entry + ".machpacketheader.machpacketlength"] = canonical::number(each.mach_packet_header().mach_packet_length());
        values[entry + ".machpacketheader.machpackettype"] = canonical::number(each.mach_packet_header().mach_packet_type());
        values[entry + ".machpacketheader.sessionnumber"] = canonical::number(each.mach_packet_header().session_number());

        if (const auto* message = dynamic_cast<const protocol::ApplicationMessage*>(each.message())) {
            values[entry + ".payload"] = "udppacket.machmessage.payload.applicationmessage";
            values[entry + ".payload.applicationmessage.messagetype"] = canonical::number((*message).message_type_field());
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
    std::printf("== Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d (classes values)\n");
    int failures = 0;
    failures += check("AddOrderMessage", "Miax/PearlEquities.DepthOfMarket.Mach.v1.3.d/AddOrderMessage.pcap", "miax/pearlequities/depthofmarket/mach/v1.3.d/AddOrderMessage.values");
    failures += check("DeleteOrderMessage", "Miax/PearlEquities.DepthOfMarket.Mach.v1.3.d/DeleteOrderMessage.pcap", "miax/pearlequities/depthofmarket/mach/v1.3.d/DeleteOrderMessage.values");
    failures += check("ModifyOrderMessage", "Miax/PearlEquities.DepthOfMarket.Mach.v1.3.d/ModifyOrderMessage.pcap", "miax/pearlequities/depthofmarket/mach/v1.3.d/ModifyOrderMessage.values");
    failures += check("OrderExecutionMessage", "Miax/PearlEquities.DepthOfMarket.Mach.v1.3.d/OrderExecutionMessage.pcap", "miax/pearlequities/depthofmarket/mach/v1.3.d/OrderExecutionMessage.values");
    failures += check("SecurityTradingStatusNotificationMessage", "Miax/PearlEquities.DepthOfMarket.Mach.v1.3.d/SecurityTradingStatusNotificationMessage.pcap", "miax/pearlequities/depthofmarket/mach/v1.3.d/SecurityTradingStatusNotificationMessage.values");
    failures += check("SystemTimeMessage", "Miax/PearlEquities.DepthOfMarket.Mach.v1.3.d/SystemTimeMessage.pcap", "miax/pearlequities/depthofmarket/mach/v1.3.d/SystemTimeMessage.values");
    failures += check("TradeMessage", "Miax/PearlEquities.DepthOfMarket.Mach.v1.3.d/TradeMessage.pcap", "miax/pearlequities/depthofmarket/mach/v1.3.d/TradeMessage.values");
    return failures == 0 ? 0 : 1;
}