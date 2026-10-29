// Iex.IexEquities.Tops.IexTp.v1.56 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/iex/iexequities/tops/iextp/v1.56.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/iex/iexequities/tops/iextp/v1.56/definitions.hpp"

namespace protocol = ::iex::iexequities::tops::iextp::v1_56;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        checksum += bench::digest(packet.iextp_header().version());
        checksum += bench::digest(packet.iextp_header().message_protocol_id());
        checksum += bench::digest(packet.iextp_header().channel_id());
        checksum += bench::digest(packet.iextp_header().session_id());
        checksum += bench::digest(packet.iextp_header().payload_length());
        checksum += bench::digest(packet.iextp_header().message_count());
        checksum += bench::digest(packet.iextp_header().stream_offset());
        checksum += bench::digest(packet.iextp_header().first_message_sequence_number());
        checksum += bench::digest(packet.iextp_header().send_time());
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

    void on(const protocol::QuoteUpdateMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.quote_update_flags().market_session());
        checksum += bench::digest(message.quote_update_flags().symbol_availability());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.bid_size());
        checksum += bench::digest(message.bid_price().mantissa());
        checksum += bench::digest(message.ask_price().mantissa());
        checksum += bench::digest(message.ask_size());
    }

    void on(const protocol::TradeReportMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.sale_condition_flags().trade_through_exempt());
        checksum += bench::digest(message.sale_condition_flags().odd_lot());
        checksum += bench::digest(message.sale_condition_flags().extended_hours());
        checksum += bench::digest(message.sale_condition_flags().intermarket_sweep());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.size());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.trade_id());
        checksum += bench::digest(message.reserved_4());
    }

    void on(const protocol::TradeBreakMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.sale_condition_flags().trade_through_exempt());
        checksum += bench::digest(message.sale_condition_flags().odd_lot());
        checksum += bench::digest(message.sale_condition_flags().extended_hours());
        checksum += bench::digest(message.sale_condition_flags().intermarket_sweep());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.size());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.trade_id());
        checksum += bench::digest(message.reserved_4());
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
    return bench::run("Iex.IexEquities.Tops.IexTp.v1.56", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
