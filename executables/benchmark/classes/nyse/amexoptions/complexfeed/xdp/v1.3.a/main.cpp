// Nyse.AmexOptions.ComplexFeed.Xdp.v1.3.a benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/nyse/amexoptions/complexfeed/xdp/v1.3.a.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/classes/nyse/amexoptions/complexfeed/xdp/v1.3.a/definitions.hpp"

namespace protocol = ::nyse::amexoptions::complexfeed::xdp::v1_3_a;

namespace {

// The values the Classes Packet decodes from one datagram, folded into a checksum. A datagram it cannot
// decode is a value the model never reads, so the benchmark refuses to time it.
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::Packet packet;

    try {
        packet.decode(frame.payload, frame.payload_len);
    } catch (const protocol::DecodeError& error) {
        throw;
        return checksum;
    }

    checksum += bench::digest(packet.packet_header().packet_size());
    checksum += bench::digest(packet.packet_header().delivery_flag());
    checksum += bench::digest(packet.packet_header().message_count());
    checksum += bench::digest(packet.packet_header().sequence_number());
    checksum += bench::digest(packet.packet_header().send_time().seconds());
    checksum += bench::digest(packet.packet_header().send_time().nanoseconds());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.message_header().message_size());
        checksum += bench::digest(each.message_header().message_type());

        if (const auto* message = dynamic_cast<const protocol::ComplexQuoteMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time());
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).complex_index());
            checksum += bench::digest((*message).symbol_seq_num());
            checksum += bench::digest((*message).ask_price());
            checksum += bench::digest((*message).bid_price());
            checksum += bench::digest((*message).ask_volume());
            checksum += bench::digest((*message).bid_volume());
            checksum += bench::digest((*message).ask_customer_volume());
            checksum += bench::digest((*message).bid_customer_volume());
            checksum += bench::digest((*message).quote_condition());
        } else if (const auto* message = dynamic_cast<const protocol::ComplexTradeMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time());
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).complex_index());
            checksum += bench::digest((*message).symbol_seq_num());
            checksum += bench::digest((*message).trade_id());
            checksum += bench::digest((*message).price());
            checksum += bench::digest((*message).volume_4());
            checksum += bench::digest((*message).trade_cond_1());
            checksum += bench::digest((*message).trade_cond_2());
        } else if (const auto* message = dynamic_cast<const protocol::ComplexCrossingRfqMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time());
            checksum += bench::digest((*message).source_ns());
            checksum += bench::digest((*message).complex_index());
            checksum += bench::digest((*message).symbol_seq_num());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).volume_2());
            checksum += bench::digest((*message).price());
        } else if (const auto* message = dynamic_cast<const protocol::ComplexCubeRfqMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time());
            checksum += bench::digest((*message).source_ns());
            checksum += bench::digest((*message).complex_index());
            checksum += bench::digest((*message).symbol_seq_num());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).volume_2());
            checksum += bench::digest((*message).price());
        } else if (const auto* message = dynamic_cast<const protocol::ComplexStatusMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time());
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).complex_index());
            checksum += bench::digest((*message).symbol_seq_num());
            checksum += bench::digest((*message).security_status());
            checksum += bench::digest((*message).halt_condition());
        } else if (const auto* message = dynamic_cast<const protocol::RefreshComplexQuoteMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time());
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).complex_index());
            checksum += bench::digest((*message).symbol_seq_num());
            checksum += bench::digest((*message).ask_price());
            checksum += bench::digest((*message).bid_price());
            checksum += bench::digest((*message).ask_volume());
            checksum += bench::digest((*message).bid_volume());
            checksum += bench::digest((*message).ask_customer_volume());
            checksum += bench::digest((*message).bid_customer_volume());
            checksum += bench::digest((*message).quote_condition());
        } else if (const auto* message = dynamic_cast<const protocol::RefreshComplexTradeMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time());
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).complex_index());
            checksum += bench::digest((*message).symbol_seq_num());
            checksum += bench::digest((*message).trade_id());
            checksum += bench::digest((*message).price());
            checksum += bench::digest((*message).volume_4());
            checksum += bench::digest((*message).trade_cond_1());
            checksum += bench::digest((*message).trade_cond_2());
        } else if (const auto* message = dynamic_cast<const protocol::ComplexSymbolDefinitionMessage*>(each.message())) {
            checksum += bench::digest((*message).complex_index());
            checksum += bench::digest((*message).complex_symbol());
            checksum += bench::digest((*message).channel_id());
            checksum += bench::digest((*message).market_id());
            checksum += bench::digest((*message).system_id());
            checksum += bench::digest((*message).stream_id());
            checksum += bench::digest((*message).no_of_legs());
        } else if (const auto* message = dynamic_cast<const protocol::StreamIdMessage*>(each.message())) {
            checksum += bench::digest((*message).stream_id());
        } else if (const auto* message = dynamic_cast<const protocol::SequenceNumberResetMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time());
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).product_id());
            checksum += bench::digest((*message).channel_id());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nyse.AmexOptions.ComplexFeed.Xdp.v1.3.a", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
