// Lseg.Lse.Level2Mbo.Gtp.v26.2: main.cpp
// Lseg.Lse.Level2Mbo.Gtp.v26.2 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/lseg/lse/level2mbo/gtp/v26.2.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/lseg/lse/level2mbo/gtp/v26.2/definitions.hpp"

namespace protocol = ::lseg::lse::level2mbo::gtp::v26_2;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        checksum += bench::digest(packet.unit_header().length());
        checksum += bench::digest(packet.unit_header().message_count());
        checksum += bench::digest(packet.unit_header().market_data_group());
        checksum += bench::digest(packet.unit_header().sequence_number());
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
        checksum += bench::digest(message.source_venue());
    }

    void on(const protocol::InstrumentDirectoryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.instrument());
        checksum += bench::digest(message.allowed_book_types().firm_quote_book());
        checksum += bench::digest(message.allowed_book_types().off_book());
        checksum += bench::digest(message.allowed_book_types().electronic_order_book());
        checksum += bench::digest(message.allowed_book_types().private_rfq());
        checksum += bench::digest(message.source_venue());
        checksum += bench::digest(message.dynamic_circuit_breaker_tolerances().mantissa());
        checksum += bench::digest(message.static_circuit_breaker_tolerances().mantissa());
        checksum += bench::digest(message.average_daily_turnover_adt().mantissa());
    }

    void on(const protocol::InstrumentStatusMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.instrument());
        checksum += bench::digest(message.source_venue());
        checksum += bench::digest(message.session_change_reason());
        checksum += bench::digest(message.order_book_type());
    }

    void on(const protocol::AddOrderMboMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.size().mantissa());
        checksum += bench::digest(message.instrument());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.source_venue());
        checksum += bench::digest(message.order_book_type());
        checksum += bench::digest(message.depth());
    }

    void on(const protocol::AddOrderShortMboMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.size().mantissa());
        checksum += bench::digest(message.price().mantissa());
    }

    void on(const protocol::OrderBookClearMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.source_venue());
        checksum += bench::digest(message.instrument());
        checksum += bench::digest(message.order_book_type());
    }

    void on(const protocol::TradeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.transaction_time());
        checksum += bench::digest(message.source_venue());
        checksum += bench::digest(message.executed_size().mantissa());
        checksum += bench::digest(message.instrument());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.trade_id());
        checksum += bench::digest(message.trade_type());
        checksum += bench::digest(message.trade_flags().trade_cancellation());
        checksum += bench::digest(message.trade_flags().trade_correction());
        checksum += bench::digest(message.hidden_execution_indicator());
    }

    void on(const protocol::StatisticsMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.instrument());
        checksum += bench::digest(message.source_venue());
        checksum += bench::digest(message.volume().mantissa());
        checksum += bench::digest(message.volume_on_book_only().mantissa());
        checksum += bench::digest(message.vwap().mantissa());
        checksum += bench::digest(message.vwap_on_book_only().mantissa());
        checksum += bench::digest(message.number_of_trades());
        checksum += bench::digest(message.number_of_trades_on_book_only());
        checksum += bench::digest(message.turnover().mantissa());
        checksum += bench::digest(message.turnover_on_book_only().mantissa());
    }

    void on(const protocol::StatisticsUpdateMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.instrument());
        checksum += bench::digest(message.source_venue());
        checksum += bench::digest(message.statistic_type());
        checksum += bench::digest(message.statistic_price().mantissa());
        checksum += bench::digest(message.statistic_size().mantissa());
        checksum += bench::digest(message.imbalance_quantity().mantissa());
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
    return bench::run("Lseg.Lse.Level2Mbo.Gtp.v26.2", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
