// Jnx.JnxEquities.Pts.Itch.v1.7 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/jnx/jnxequities/pts/itch/v1.7.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/jnx/jnxequities/pts/itch/v1.7/definitions.hpp"

namespace protocol = ::jnx::jnxequities::pts::itch::v1_7;

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

    void on(const protocol::UdpPayloadSecondsMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.seconds());
    }

    void on(const protocol::UdpPayloadSystemEventMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.group());
        checksum += bench::digest(message.system_event());
    }

    void on(const protocol::UdpPayloadPriceTickSizeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.price_tick_size_table_id());
        checksum += bench::digest(message.price_tick_size().mantissa());
        checksum += bench::digest(message.price_start().mantissa());
    }

    void on(const protocol::UdpPayloadOrderbookDirectoryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.orderbook_id());
        checksum += bench::digest(message.orderbook_code());
        checksum += bench::digest(message.group());
        checksum += bench::digest(message.round_lot_size());
        checksum += bench::digest(message.price_tick_size_table_id());
        checksum += bench::digest(message.price_decimals());
        checksum += bench::digest(message.upper_price_limit().mantissa());
        checksum += bench::digest(message.lower_price_limit().mantissa());
    }

    void on(const protocol::UdpPayloadTradingStateMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.orderbook_id());
        checksum += bench::digest(message.group());
        checksum += bench::digest(message.trading_state());
    }

    void on(const protocol::UdpPayloadShortSellingPriceRestrictionStateMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.orderbook_id());
        checksum += bench::digest(message.group());
        checksum += bench::digest(message.short_selling_state());
    }

    void on(const protocol::UdpPayloadOrderAddedWithoutAttributesMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.order_number());
        checksum += bench::digest(message.buy_sell_indicator());
        checksum += bench::digest(message.quantity());
        checksum += bench::digest(message.orderbook_id());
        checksum += bench::digest(message.group());
        checksum += bench::digest(message.price().mantissa());
    }

    void on(const protocol::UdpPayloadOrderAddedWithAttributesMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.order_number());
        checksum += bench::digest(message.buy_sell_indicator());
        checksum += bench::digest(message.quantity());
        checksum += bench::digest(message.orderbook_id());
        checksum += bench::digest(message.group());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.attribution());
        checksum += bench::digest(message.order_type());
    }

    void on(const protocol::UdpPayloadOrderExecutedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.order_number());
        checksum += bench::digest(message.executed_quantity());
        checksum += bench::digest(message.match_number());
    }

    void on(const protocol::UdpPayloadOrderDeletedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.order_number());
    }

    void on(const protocol::UdpPayloadOrderReplacedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.original_order_number());
        checksum += bench::digest(message.new_order_number());
        checksum += bench::digest(message.quantity());
        checksum += bench::digest(message.price().mantissa());
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
    return bench::run("Jnx.JnxEquities.Pts.Itch.v1.7", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
