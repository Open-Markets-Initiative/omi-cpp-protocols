// Memx.MemxEquities.MemoirDepthFeed.Sbe.v1.3: main.cpp
// Memx.MemxEquities.MemoirDepthFeed.Sbe.v1.3 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/memx/memxequities/memoirdepthfeed/sbe/v1.3.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/memx/memxequities/memoirdepthfeed/sbe/v1.3/definitions.hpp"

namespace protocol = ::memx::memxequities::memoirdepthfeed::sbe::v1_3;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        checksum += bench::digest(packet.common_header().message_type());
        checksum += bench::digest(packet.common_header().header_length());
        checksum += bench::digest(packet.common_header().session_id());
        checksum += bench::digest(packet.common_header().sequence_number());
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

    void on(const protocol::InstrumentDirectoryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.symbol_sfx());
        checksum += bench::digest(message.round_lot());
        checksum += bench::digest(message.is_test_symbol());
        checksum += bench::digest(message.mpv().mantissa());
    }

    void on(const protocol::RegShoRestrictionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.short_sale_restriction());
    }

    void on(const protocol::SecurityTradingStatusMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.security_trading_status());
        checksum += bench::digest(message.security_trading_status_reason());
    }

    void on(const protocol::TradingSessionStatusMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.trading_session());
    }

    void on(const protocol::OrderAddedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.quantity());
        checksum += bench::digest(message.price().mantissa());
    }

    void on(const protocol::OrderDeletedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.order_id());
    }

    void on(const protocol::OrderReducedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.quantity());
    }

    void on(const protocol::OrderExecutedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.trade_id());
        checksum += bench::digest(message.quantity());
        checksum += bench::digest(message.price().mantissa());
    }

    void on(const protocol::TradeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.trade_id());
        checksum += bench::digest(message.quantity());
        checksum += bench::digest(message.price().mantissa());
    }

    void on(const protocol::BrokenTradeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.trade_id());
        checksum += bench::digest(message.original_quantity());
        checksum += bench::digest(message.original_price().mantissa());
    }

    void on(const protocol::CorrectedTradeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.trade_id());
        checksum += bench::digest(message.original_quantity());
        checksum += bench::digest(message.original_price().mantissa());
        checksum += bench::digest(message.corrected_quantity());
        checksum += bench::digest(message.corrected_price().mantissa());
    }

    void on(const protocol::ClearBookMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.security_id());
    }

    void on(const protocol::SnapshotCompleteMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.as_of_sequence_number());
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
    return bench::run("Memx.MemxEquities.MemoirDepthFeed.Sbe.v1.3", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
