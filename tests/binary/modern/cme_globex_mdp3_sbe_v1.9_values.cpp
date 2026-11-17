// Cme.Globex.Mdp3.Sbe.v1.9 canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/binary/modern/cme/globex/mdp3/sbe/v1.9/definitions.hpp"

namespace protocol = ::cme::mdp3::v9;

namespace {

// The values the Modern iterator reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    values["udppacket.binarypacketheader.packetsequencenumber"] = canonical::number(iterator.binary_packet_header->packet_sequence_number.get());
    values["udppacket.binarypacketheader.sendingtime"] = canonical::number(iterator.binary_packet_header->sending_time.get());

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "udppacket.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(iterator.message_header->message_size.get());
        values[entry + ".messageheader.simplebinaryheader.blocklength"] = canonical::number(iterator.message_header->simple_binary_header.block_length.get());
        values[entry + ".messageheader.simplebinaryheader.templateid"] = canonical::number(iterator.message_header->simple_binary_header.template_id.get());
        values[entry + ".messageheader.simplebinaryheader.schemaid"] = canonical::number(iterator.message_header->simple_binary_header.schema_id.get());
        values[entry + ".messageheader.simplebinaryheader.version"] = canonical::number(iterator.message_header->simple_binary_header.version.get());

        if (iterator.schema_id == 1) {
            values[entry + ".payload"] = "udppacket.message.payload.mktdatamessage";
            [[maybe_unused]] const auto* message = protocol::MktdataMessage::parse(iterator.message);
        } else if (iterator.schema_id == 2) {
            values[entry + ".payload"] = "udppacket.message.payload.mdpsessionmgmtmessage";
            [[maybe_unused]] const auto* message = protocol::MdpsessionmgmtMessage::parse(iterator.message);
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
    std::printf("== Cme.Globex.Mdp3.Sbe.v1.9 (modern values)\n");
    int failures = 0;
    failures += check("MdIncrementalRefreshBook", "Cme/Globex.Mdp3.Sbe.v1.9/MdIncrementalRefreshBook.pcap", "cme/globex/mdp3/sbe/v1.9/MdIncrementalRefreshBook.values");
    failures += check("MdIncrementalRefreshOrderBook", "Cme/Globex.Mdp3.Sbe.v1.9/MdIncrementalRefreshOrderBook.pcap", "cme/globex/mdp3/sbe/v1.9/MdIncrementalRefreshOrderBook.values");
    failures += check("MdIncrementalRefreshTradeSummary", "Cme/Globex.Mdp3.Sbe.v1.9/MdIncrementalRefreshTradeSummary.pcap", "cme/globex/mdp3/sbe/v1.9/MdIncrementalRefreshTradeSummary.values");
    failures += check("MdIncrementalRefreshVolume", "Cme/Globex.Mdp3.Sbe.v1.9/MdIncrementalRefreshVolume.pcap", "cme/globex/mdp3/sbe/v1.9/MdIncrementalRefreshVolume.values");
    return failures == 0 ? 0 : 1;
}
