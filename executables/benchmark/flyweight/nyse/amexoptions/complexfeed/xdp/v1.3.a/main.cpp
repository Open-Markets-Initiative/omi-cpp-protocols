// Nyse.AmexOptions.ComplexFeed.Xdp.v1.3.a benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/nyse/amexoptions/complexfeed/xdp/v1.3.a.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "executables/benchmark/Benchmark.hpp"
#include "cpp/binary/flyweight/nyse/amexoptions/complexfeed/xdp/v1.3.a/definitions.hpp"

namespace protocol = ::nyse::amexoptions::complexfeed::xdp::v1_3_a;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        checksum += bench::digest(packet.packet_header().packet_size());
        checksum += bench::digest(packet.packet_header().delivery_flag());
        checksum += bench::digest(packet.packet_header().message_count());
        checksum += bench::digest(packet.packet_header().sequence_number());
        checksum += bench::digest(packet.packet_header().send_time().seconds());
        checksum += bench::digest(packet.packet_header().send_time().nanoseconds());
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

    void on(const protocol::ComplexQuoteMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.source_time());
        checksum += bench::digest(message.source_time_ns());
        checksum += bench::digest(message.complex_index());
        checksum += bench::digest(message.symbol_seq_num());
        checksum += bench::digest(message.ask_price());
        checksum += bench::digest(message.bid_price());
        checksum += bench::digest(message.ask_volume());
        checksum += bench::digest(message.bid_volume());
        checksum += bench::digest(message.ask_customer_volume());
        checksum += bench::digest(message.bid_customer_volume());
        checksum += bench::digest(message.quote_condition());
    }

    void on(const protocol::ComplexTradeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.source_time());
        checksum += bench::digest(message.source_time_ns());
        checksum += bench::digest(message.complex_index());
        checksum += bench::digest(message.symbol_seq_num());
        checksum += bench::digest(message.trade_id());
        checksum += bench::digest(message.price());
        checksum += bench::digest(message.volume_4());
        checksum += bench::digest(message.trade_cond_1());
        checksum += bench::digest(message.trade_cond_2());
    }

    void on(const protocol::ComplexCrossingRfqMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.source_time());
        checksum += bench::digest(message.source_ns());
        checksum += bench::digest(message.complex_index());
        checksum += bench::digest(message.symbol_seq_num());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.volume_2());
        checksum += bench::digest(message.price());
    }

    void on(const protocol::ComplexCubeRfqMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.source_time());
        checksum += bench::digest(message.source_ns());
        checksum += bench::digest(message.complex_index());
        checksum += bench::digest(message.symbol_seq_num());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.volume_2());
        checksum += bench::digest(message.price());
    }

    void on(const protocol::ComplexStatusMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.source_time());
        checksum += bench::digest(message.source_time_ns());
        checksum += bench::digest(message.complex_index());
        checksum += bench::digest(message.symbol_seq_num());
        checksum += bench::digest(message.security_status());
        checksum += bench::digest(message.halt_condition());
    }

    void on(const protocol::RefreshComplexQuoteMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.source_time());
        checksum += bench::digest(message.source_time_ns());
        checksum += bench::digest(message.complex_index());
        checksum += bench::digest(message.symbol_seq_num());
        checksum += bench::digest(message.ask_price());
        checksum += bench::digest(message.bid_price());
        checksum += bench::digest(message.ask_volume());
        checksum += bench::digest(message.bid_volume());
        checksum += bench::digest(message.ask_customer_volume());
        checksum += bench::digest(message.bid_customer_volume());
        checksum += bench::digest(message.quote_condition());
    }

    void on(const protocol::RefreshComplexTradeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.source_time());
        checksum += bench::digest(message.source_time_ns());
        checksum += bench::digest(message.complex_index());
        checksum += bench::digest(message.symbol_seq_num());
        checksum += bench::digest(message.trade_id());
        checksum += bench::digest(message.price());
        checksum += bench::digest(message.volume_4());
        checksum += bench::digest(message.trade_cond_1());
        checksum += bench::digest(message.trade_cond_2());
    }

    void on(const protocol::ComplexSymbolDefinitionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.complex_index());
        checksum += bench::digest(message.complex_symbol());
        checksum += bench::digest(message.channel_id());
        checksum += bench::digest(message.market_id());
        checksum += bench::digest(message.system_id());
        checksum += bench::digest(message.stream_id());
        checksum += bench::digest(message.no_of_legs());
    }

    void on(const protocol::StreamIdMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stream_id());
    }

    void on(const protocol::SequenceNumberResetMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.source_time());
        checksum += bench::digest(message.source_time_ns());
        checksum += bench::digest(message.product_id());
        checksum += bench::digest(message.channel_id());
    }
};

// The values the Flyweight reader reads from one datagram, folded into a checksum. A datagram it cannot
// read is a value the model never reads, so the benchmark refuses to time it.
std::uint64_t read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::PacketReader::read(std::span<const std::byte>(frame.payload, frame.payload_len), reader);
    } catch (const protocol::DecodeError& error) {
        throw;
    }

    return reader.checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nyse.AmexOptions.ComplexFeed.Xdp.v1.3.a", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
