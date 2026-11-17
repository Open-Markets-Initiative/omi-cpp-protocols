// Cme.Globex.Mdp3.Sbe.v1.9: main.cpp
// Cme.Globex.Mdp3.Sbe.v1.9 benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/cme/globex/mdp3/sbe/v1.9.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "executables/benchmark/Benchmark.hpp"
#include "cpp/binary/modern/cme/globex/mdp3/sbe/v1.9/definitions.hpp"

namespace protocol = ::cme::mdp3::v9;

namespace {

// The values the Modern iterator reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    checksum += bench::digest(iterator.binary_packet_header->packet_sequence_number.get());
    checksum += bench::digest(iterator.binary_packet_header->sending_time.get());

    std::size_t index = 0;

    while (iterator.next()) {
        checksum += index++;
        checksum += bench::digest(iterator.message_header->message_size.get());
        checksum += bench::digest(iterator.message_header->simple_binary_header.block_length.get());
        checksum += bench::digest(iterator.message_header->simple_binary_header.template_id.get());
        checksum += bench::digest(iterator.message_header->simple_binary_header.schema_id.get());
        checksum += bench::digest(iterator.message_header->simple_binary_header.version.get());

        if (iterator.schema_id == 1) {
            [[maybe_unused]] const auto* message = protocol::MktdataMessage::parse(iterator.message);
        } else if (iterator.schema_id == 2) {
            [[maybe_unused]] const auto* message = protocol::MdpsessionmgmtMessage::parse(iterator.message);
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Cme.Globex.Mdp3.Sbe.v1.9", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
