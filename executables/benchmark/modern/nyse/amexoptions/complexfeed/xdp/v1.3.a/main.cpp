// Nyse.AmexOptions.ComplexFeed.Xdp.v1.3.a benchmark, through the Modern iterator: every value it reads from every message of the simulated
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
#include "cpp/binary/modern/nyse/amexoptions/complexfeed/xdp/v1.3.a/definitions.hpp"

namespace protocol = ::nyse::amexoptions::complexfeed::xdp::v1_3_a;

namespace {

// The values the Modern iterator reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    checksum += bench::digest(iterator.packet_header->packet_size.get());
    checksum += bench::digest(iterator.packet_header->delivery_flag.get());
    checksum += bench::digest(iterator.packet_header->message_count.get());
    checksum += bench::digest(iterator.packet_header->sequence_number.get());
    checksum += bench::digest(iterator.packet_header->send_time.seconds.get());
    checksum += bench::digest(iterator.packet_header->send_time.nanoseconds.get());

    std::size_t index = 0;

    while (iterator.next()) {
        checksum += index++;
        checksum += bench::digest(iterator.message_header->message_size.get());
        checksum += bench::digest(iterator.message_header->message_type.get());

        if (iterator.message_type == protocol::ComplexQuoteMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ComplexQuoteMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time.get());
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->complex_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->ask_price.get());
            checksum += bench::digest(message->bid_price.get());
            checksum += bench::digest(message->ask_volume.get());
            checksum += bench::digest(message->bid_volume.get());
            checksum += bench::digest(message->ask_customer_volume.get());
            checksum += bench::digest(message->bid_customer_volume.get());
            checksum += bench::digest(message->quote_condition.get());
        } else if (iterator.message_type == protocol::ComplexTradeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ComplexTradeMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time.get());
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->complex_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->trade_id.get());
            checksum += bench::digest(message->price.get());
            checksum += bench::digest(message->volume_4.get());
            checksum += bench::digest(message->trade_cond_1.get());
            checksum += bench::digest(message->trade_cond_2.get());
        } else if (iterator.message_type == protocol::ComplexCrossingRfqMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ComplexCrossingRfqMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time.get());
            checksum += bench::digest(message->source_ns.get());
            checksum += bench::digest(message->complex_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->volume_2.get());
            checksum += bench::digest(message->price.get());
        } else if (iterator.message_type == protocol::ComplexCubeRfqMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ComplexCubeRfqMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time.get());
            checksum += bench::digest(message->source_ns.get());
            checksum += bench::digest(message->complex_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->volume_2.get());
            checksum += bench::digest(message->price.get());
        } else if (iterator.message_type == protocol::ComplexStatusMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ComplexStatusMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time.get());
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->complex_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->security_status.get());
            checksum += bench::digest(message->halt_condition.get());
        } else if (iterator.message_type == protocol::RefreshComplexQuoteMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::RefreshComplexQuoteMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time.get());
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->complex_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->ask_price.get());
            checksum += bench::digest(message->bid_price.get());
            checksum += bench::digest(message->ask_volume.get());
            checksum += bench::digest(message->bid_volume.get());
            checksum += bench::digest(message->ask_customer_volume.get());
            checksum += bench::digest(message->bid_customer_volume.get());
            checksum += bench::digest(message->quote_condition.get());
        } else if (iterator.message_type == protocol::RefreshComplexTradeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::RefreshComplexTradeMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time.get());
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->complex_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->trade_id.get());
            checksum += bench::digest(message->price.get());
            checksum += bench::digest(message->volume_4.get());
            checksum += bench::digest(message->trade_cond_1.get());
            checksum += bench::digest(message->trade_cond_2.get());
        } else if (iterator.message_type == protocol::ComplexSymbolDefinitionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ComplexSymbolDefinitionMessage::parse(iterator.message);
            checksum += bench::digest(message->complex_index.get());
            checksum += bench::digest(message->complex_symbol.get());
            checksum += bench::digest(message->channel_id.get());
            checksum += bench::digest(message->market_id.get());
            checksum += bench::digest(message->system_id.get());
            checksum += bench::digest(message->stream_id.get());
            checksum += bench::digest(message->no_of_legs.get());
        } else if (iterator.message_type == protocol::StreamIdMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::StreamIdMessage::parse(iterator.message);
            checksum += bench::digest(message->stream_id.get());
        } else if (iterator.message_type == protocol::SequenceNumberResetMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SequenceNumberResetMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time.get());
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->product_id.get());
            checksum += bench::digest(message->channel_id.get());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nyse.AmexOptions.ComplexFeed.Xdp.v1.3.a", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
