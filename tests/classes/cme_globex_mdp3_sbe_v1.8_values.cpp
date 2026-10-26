// Cme.Globex.Mdp3.Sbe.v1.8 canonical values, through the Classes Packet: every value Classes decodes from
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
#include "cpp/classes/cme/globex/mdp3/sbe/v1.8/definitions.hpp"

namespace protocol = ::cme::globex::mdp3::sbe::v1_8;

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

    values["udppacket.binarypacketheader.packetsequencenumber"] = canonical::number(packet.binary_packet_header().packet_sequence_number());
    values["udppacket.binarypacketheader.sendingtime"] = canonical::number(packet.binary_packet_header().sending_time());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(each.message_header().message_size());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(each.message_header().simple_binary_header().block_length());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(each.message_header().simple_binary_header().template_id());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(each.message_header().simple_binary_header().schema_id());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(each.message_header().simple_binary_header().version());

        if (const auto* message = dynamic_cast<const protocol::MktdataMessage*>(each.message())) {
            values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
        } else if (const auto* message = dynamic_cast<const protocol::MdpsessionmgmtMessage*>(each.message())) {
            values[entry + ".payload"] = "udppacket.message.payload.mdpsessionmgmtmessage";
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
    std::printf("== Cme.Globex.Mdp3.Sbe.v1.8 (classes values)\n");
    int failures = 0;
    failures += check("MdIncrementalRefreshTradeSummary", "Cme/Globex.Mdp3.Sbe.v1.8/MdIncrementalRefreshTradeSummary.pcap", "cme/globex/mdp3/sbe/v1.8/MdIncrementalRefreshTradeSummary.values");
    return failures == 0 ? 0 : 1;
}