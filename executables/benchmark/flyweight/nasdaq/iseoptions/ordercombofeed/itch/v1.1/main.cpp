// Nasdaq.IseOptions.OrderComboFeed.Itch.v1.1 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/iseoptions/ordercombofeed/itch/v1.1.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/nasdaq/iseoptions/ordercombofeed/itch/v1.1/definitions.hpp"

namespace protocol = ::nasdaq::iseoptions::ordercombofeed::itch::v1_1;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        checksum += bench::digest(packet.packet_header().session());
        checksum += bench::digest(packet.packet_header().sequence_number());
        checksum += bench::digest(packet.packet_header().message_count());
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

    void on(const protocol::SystemEventMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.event_code());
        checksum += bench::digest(message.current_year());
        checksum += bench::digest(message.current_month());
        checksum += bench::digest(message.current_day());
        checksum += bench::digest(message.version());
        checksum += bench::digest(message.sub_version());
    }

    void on(const protocol::ComplexStrategyDirectoryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.strategy_id());
        checksum += bench::digest(message.strategy_type());
        checksum += bench::digest(message.source());
        checksum += bench::digest(message.underlying_symbol());
        checksum += bench::digest(message.number_of_legs());
    }

    void on(const protocol::StrategyTradingActionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.strategy_id());
        checksum += bench::digest(message.current_trading_state());
    }

    void on(const protocol::StrategyOpenClosedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.strategy_id());
        checksum += bench::digest(message.open_state());
    }

    void on(const protocol::ComplexStrategyOrderOnBookMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.strategy_id());
        checksum += bench::digest(message.order_type());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.size());
        checksum += bench::digest(message.exec_flag());
        checksum += bench::digest(message.order_capacity());
        checksum += bench::digest(message.scope());
        checksum += bench::digest(message.owner_id());
        checksum += bench::digest(message.giveup());
        checksum += bench::digest(message.cmta());
    }

    void on(const protocol::ComplexStrategyAuctionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.strategy_id());
        checksum += bench::digest(message.auction_id());
        checksum += bench::digest(message.order_type());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.size());
        checksum += bench::digest(message.exec_flag());
        checksum += bench::digest(message.order_capacity());
        checksum += bench::digest(message.scope());
        checksum += bench::digest(message.owner_id());
        checksum += bench::digest(message.giveup());
        checksum += bench::digest(message.cmta());
        checksum += bench::digest(message.auction_event());
        checksum += bench::digest(message.auction_type());
        checksum += bench::digest(message.number_of_responses());
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
    return bench::run("Nasdaq.IseOptions.OrderComboFeed.Itch.v1.1", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
