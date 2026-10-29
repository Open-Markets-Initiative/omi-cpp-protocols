// Nasdaq.NsmEquities.TotalView.Itch.v4.0 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/nsmequities/totalview/itch/v4.0.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/nasdaq/nsmequities/totalview/itch/v4.0/definitions.hpp"

namespace protocol = ::nasdaq::nsmequities::totalview::itch::v4_0;

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

    void on(const protocol::PayloadTimestampMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.second());
    }

    void on(const protocol::PayloadSystemEventMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.event_code());
    }

    void on(const protocol::PayloadStockDirectoryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.market_category());
        checksum += bench::digest(message.financial_status_indicator());
        checksum += bench::digest(message.round_lot_size());
        checksum += bench::digest(message.round_lots_only());
    }

    void on(const protocol::PayloadStockTradingActionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.trading_state());
        checksum += bench::digest(message.reserved());
        checksum += bench::digest(message.reason());
    }

    void on(const protocol::PayloadMarketParticipantPositionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.mpid());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.primary_market_maker());
        checksum += bench::digest(message.market_maker_mode());
        checksum += bench::digest(message.market_participant_state());
    }

    void on(const protocol::PayloadAddOrderMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.order_reference_number());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.shares());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.price().mantissa());
    }

    void on(const protocol::PayloadAddOrderWithMpidMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.order_reference_number());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.shares());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.attribution());
    }

    void on(const protocol::PayloadOrderExecutedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.order_reference_number());
        checksum += bench::digest(message.executed_shares());
        checksum += bench::digest(message.match_number());
    }

    void on(const protocol::PayloadOrderExecutedWithPriceMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.order_reference_number());
        checksum += bench::digest(message.executed_shares());
        checksum += bench::digest(message.match_number());
        checksum += bench::digest(message.printable());
        checksum += bench::digest(message.execution_price().mantissa());
    }

    void on(const protocol::PayloadOrderCancelMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.order_reference_number());
        checksum += bench::digest(message.canceled_shares());
    }

    void on(const protocol::PayloadOrderDeleteMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.order_reference_number());
    }

    void on(const protocol::PayloadOrderReplaceMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.original_order_reference_number());
        checksum += bench::digest(message.new_order_reference_number());
        checksum += bench::digest(message.shares());
        checksum += bench::digest(message.price().mantissa());
    }

    void on(const protocol::PayloadTradeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.order_reference_number());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.shares());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.match_number());
    }

    void on(const protocol::PayloadCrossTradeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.cross_shares());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.cross_price().mantissa());
        checksum += bench::digest(message.match_number());
        checksum += bench::digest(message.cross_type());
    }

    void on(const protocol::PayloadBrokenTradeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.match_number());
    }

    void on(const protocol::PayloadNetOrderImbalanceIndicatorMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.paired_shares());
        checksum += bench::digest(message.imbalance_shares());
        checksum += bench::digest(message.imbalance_direction());
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.far_price().mantissa());
        checksum += bench::digest(message.near_price().mantissa());
        checksum += bench::digest(message.current_reference_price().mantissa());
        checksum += bench::digest(message.cross_type());
        checksum += bench::digest(message.price_variation_indicator());
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
    return bench::run("Nasdaq.NsmEquities.TotalView.Itch.v4.0", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
