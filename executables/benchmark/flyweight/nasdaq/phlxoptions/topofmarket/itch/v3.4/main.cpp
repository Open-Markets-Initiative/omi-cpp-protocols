// Nasdaq.PhlxOptions.TopOfMarket.Itch.v3.4 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/phlxoptions/topofmarket/itch/v3.4.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/nasdaq/phlxoptions/topofmarket/itch/v3.4/definitions.hpp"

namespace protocol = ::nasdaq::phlxoptions::topofmarket::itch::v3_4;

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
        checksum += bench::digest(message.version());
        checksum += bench::digest(message.sub_version());
    }

    void on(const protocol::PayloadOptionsDirectoryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.option_id());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.expiration_year());
        checksum += bench::digest(message.expiration_month());
        checksum += bench::digest(message.expiration_day());
        checksum += bench::digest(message.strike_price().mantissa());
        checksum += bench::digest(message.option_type());
        checksum += bench::digest(message.source());
        checksum += bench::digest(message.underlying_symbol());
        checksum += bench::digest(message.option_closing_type());
        checksum += bench::digest(message.tradable());
        checksum += bench::digest(message.mpv());
    }

    void on(const protocol::PayloadTradingActionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.option_id());
        checksum += bench::digest(message.current_trading_state());
    }

    void on(const protocol::PayloadSecurityOpenClosedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.option_id());
        checksum += bench::digest(message.open_state());
    }

    void on(const protocol::PayloadShortBestBidAndAskUpdateMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.option_id());
        checksum += bench::digest(message.quote_condition());
        checksum += bench::digest(message.bid_price_2().mantissa());
        checksum += bench::digest(message.bid_size_2());
        checksum += bench::digest(message.ask_price_2().mantissa());
        checksum += bench::digest(message.ask_size_2());
    }

    void on(const protocol::PayloadLongBestBidAndAskUpdateMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.option_id());
        checksum += bench::digest(message.quote_condition());
        checksum += bench::digest(message.bid_price_4().mantissa());
        checksum += bench::digest(message.bid_size_4());
        checksum += bench::digest(message.ask_price_4().mantissa());
        checksum += bench::digest(message.ask_size_4());
    }

    void on(const protocol::PayloadShortBestAskUpdateMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.option_id());
        checksum += bench::digest(message.quote_condition());
        checksum += bench::digest(message.price_2().mantissa());
        checksum += bench::digest(message.size_2());
    }

    void on(const protocol::PayloadShortBestBidUpdateMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.option_id());
        checksum += bench::digest(message.quote_condition());
        checksum += bench::digest(message.price_2().mantissa());
        checksum += bench::digest(message.size_2());
    }

    void on(const protocol::PayloadLongBestAskUpdateMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.option_id());
        checksum += bench::digest(message.quote_condition());
        checksum += bench::digest(message.price_4().mantissa());
        checksum += bench::digest(message.size_4());
    }

    void on(const protocol::PayloadLongBestBidUpdateMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.option_id());
        checksum += bench::digest(message.quote_condition());
        checksum += bench::digest(message.price_4().mantissa());
        checksum += bench::digest(message.size_4());
    }

    void on(const protocol::PayloadTradeReportMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.option_id());
        checksum += bench::digest(message.cross_id());
        checksum += bench::digest(message.trade_condition());
        checksum += bench::digest(message.price_4().mantissa());
        checksum += bench::digest(message.volume());
    }

    void on(const protocol::PayloadBrokenTradeReportMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.option_id());
        checksum += bench::digest(message.original_cross_id());
        checksum += bench::digest(message.original_price().mantissa());
        checksum += bench::digest(message.original_volume());
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
    return bench::run("Nasdaq.PhlxOptions.TopOfMarket.Itch.v3.4", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
