// CixAts.CixAspen.MarketDataFeed.Aspen.v1.4 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/cixats/cixaspen/marketdatafeed/aspen/v1.4.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/cixats/cixaspen/marketdatafeed/aspen/v1.4/definitions.hpp"

namespace protocol = ::cixats::cixaspen::marketdatafeed::aspen::v1_4;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        checksum += bench::digest(packet.packet_header().market_day_identifier());
        checksum += bench::digest(packet.packet_header().feed_identifier());
        checksum += bench::digest(packet.packet_header().sequence());
        checksum += bench::digest(packet.packet_header().count());
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

    void on(const protocol::MarketEventMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.reserved_2());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.event());
    }

    void on(const protocol::SymbolInformationMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.symbol_id());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.listing_market());
        checksum += bench::digest(message.board_lot_size());
    }

    void on(const protocol::SymbolStateMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.symbol_id());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.state());
        checksum += bench::digest(message.reserved_1());
        checksum += bench::digest(message.info());
    }

    void on(const protocol::NewOrderAddMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.symbol_id());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.quantity().mantissa());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.broker());
        checksum += bench::digest(message.reserved_1());
    }

    void on(const protocol::OrderPartialCancelMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.quantity_canceled().mantissa());
    }

    void on(const protocol::OrderCancelAllMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.order_id());
    }

    void on(const protocol::OrderExecutedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.quantity().mantissa());
        checksum += bench::digest(message.execution_id());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.broker());
        checksum += bench::digest(message.contra_broker());
    }

    void on(const protocol::TradeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.symbol_id());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.reserved_8());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.shares().mantissa());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.execution_id());
        checksum += bench::digest(message.broker());
        checksum += bench::digest(message.contra_broker());
    }

    void on(const protocol::TradeCancelMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.symbol_id());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.reserved_8());
        checksum += bench::digest(message.reserved_1());
        checksum += bench::digest(message.shares().mantissa());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.execution_id());
        checksum += bench::digest(message.broker());
        checksum += bench::digest(message.contra_broker());
    }

    void on(const protocol::TradeCorrectMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.symbol_id());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.reserved_8());
        checksum += bench::digest(message.reserved_1());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.execution_id());
        checksum += bench::digest(message.broker());
        checksum += bench::digest(message.contra_broker());
        checksum += bench::digest(message.original_execution_id());
        checksum += bench::digest(message.original_trade_price().mantissa());
        checksum += bench::digest(message.original_trade_quantity().mantissa());
        checksum += bench::digest(message.corrected_trade_price().mantissa());
        checksum += bench::digest(message.corrected_trade_quantity().mantissa());
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
    return bench::run("CixAts.CixAspen.MarketDataFeed.Aspen.v1.4", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
