// Jpx.TseEquities.MarketByOrder.Flex.v1.1 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/jpx/tseequities/marketbyorder/flex/v1.1.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/jpx/tseequities/marketbyorder/flex/v1.1/definitions.hpp"

namespace protocol = ::jpx::tseequities::marketbyorder::flex::v1_1;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    void on(const protocol::UdpPacket& packet) {
        checksum += bench::digest(packet.packet_header().multicast_group_number());
        checksum += bench::digest(packet.packet_header().number_of_system_reboots());
        checksum += bench::digest(packet.packet_header().sequence_number());
        checksum += bench::digest(packet.packet_header().issue_code());
        checksum += bench::digest(packet.packet_header().update_number());
        checksum += bench::digest(packet.packet_header().packet_number());
        checksum += bench::digest(packet.packet_header().total_number_of_packets());
        checksum += bench::digest(packet.packet_header().utility_flag());
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

    void on(const protocol::SecondsTimestampMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_seconds());
    }

    void on(const protocol::TradingStatusMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_microseconds());
        checksum += bench::digest(message.market_status());
        checksum += bench::digest(message.status_flag());
        checksum += bench::digest(message.short_selling_status());
        checksum += bench::digest(message.pricing_method());
        checksum += bench::digest(message.book_center_price().mantissa());
    }

    void on(const protocol::ExecutionSummaryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_microseconds());
        checksum += bench::digest(message.triggered_side());
        checksum += bench::digest(message.total_volume());
        checksum += bench::digest(message.total_invalidation());
        checksum += bench::digest(message.last_price().mantissa());
        checksum += bench::digest(message.match_id());
        checksum += (message.best_offer().has_value() ? bench::digest((*message.best_offer()).mantissa()) : std::uint64_t{0});
        checksum += (message.best_bid().has_value() ? bench::digest((*message.best_bid()).mantissa()) : std::uint64_t{0});
    }

    void on(const protocol::AddOrderMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_microseconds());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.quantity());
        checksum += (message.price().has_value() ? bench::digest((*message.price()).mantissa()) : std::uint64_t{0});
        checksum += bench::digest(message.order_condition());
        checksum += bench::digest(message.modification_flag());
    }

    void on(const protocol::OrderExecutedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_microseconds());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.volume());
        checksum += bench::digest(message.match_id());
    }

    void on(const protocol::OrderExecutedWithPriceMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_microseconds());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.volume());
        checksum += bench::digest(message.match_id());
        checksum += bench::digest(message.execution_price().mantissa());
        checksum += bench::digest(message.adopted_pricing_method());
    }

    void on(const protocol::OrderDeleteMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_microseconds());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.modification_flag());
    }

    void on(const protocol::ResetMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.reset_start_end_flag());
    }

    void on(const protocol::CommunicationControlMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.test_mode_flag());
        checksum += bench::digest(message.communication_start_end_flag());
    }
};

// The values the Flyweight reader reads from one datagram, folded into a checksum. A datagram it cannot
// read is a value the model never reads, so the benchmark refuses to time it.
std::uint64_t read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::UdpPacketReader::read(std::span<const std::byte>(frame.payload, frame.payload_len), reader);
    } catch (const protocol::DecodeError& error) {
        throw;
    }

    return reader.checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Jpx.TseEquities.MarketByOrder.Flex.v1.1", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
