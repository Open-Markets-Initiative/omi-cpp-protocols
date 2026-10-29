// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/cboe/c1options/marketdatafeed/csm/v1.4.2.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/cboe/c1options/marketdatafeed/csm/v1.4.2/definitions.hpp"

namespace protocol = ::cboe::c1options::marketdatafeed::csm::v1_4_2;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        checksum += bench::digest(packet.packet_header().version());
        checksum += bench::digest(packet.packet_header().packet_length());
        checksum += bench::digest(packet.packet_header().sending_time());
        checksum += bench::digest(packet.packet_header().message_count());
        checksum += bench::digest(packet.packet_header().first_msg_seq_num());
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

    void on(const protocol::SecurityDefinitionMessage&) {
        checksum += index++;
    }

    void on(const protocol::CurrentMarketRefreshMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.class_key());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.security_trading_status());
        checksum += bench::digest(message.price_type());
        checksum += bench::digest(message.appl_seq_num());
        checksum += bench::digest(message.no_entries());
    }

    void on(const protocol::MarketDataRefreshMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.class_key());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.security_trading_status());
        checksum += bench::digest(message.price_type());
        checksum += bench::digest(message.appl_seq_num());
        checksum += bench::digest(message.prev_close_px().prev_close_px_exponent());
        checksum += bench::digest(message.prev_close_px().prev_close_px_mantissa());
        checksum += bench::digest(message.trade_volume());
        checksum += bench::digest(message.no_entries());
    }

    void on(const protocol::CurrentMarketUpdateMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.class_key());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.security_trading_status());
        checksum += bench::digest(message.price_type());
        checksum += bench::digest(message.no_entries());
    }

    void on(const protocol::RecapUpdateMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.class_key());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.price_type());
        checksum += bench::digest(message.prev_close_px().prev_close_px_exponent());
        checksum += bench::digest(message.prev_close_px().prev_close_px_mantissa());
        checksum += bench::digest(message.trade_volume());
        checksum += bench::digest(message.no_entries());
    }

    void on(const protocol::TickerMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.class_key());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.price_type());
        checksum += bench::digest(message.no_entries());
    }

    void on(const protocol::ExpectedOpeningPriceAndSizeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.class_key());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.eop().eop_exponent());
        checksum += bench::digest(message.eop().eop_mantissa());
        checksum += bench::digest(message.eos());
        checksum += bench::digest(message.eop_type());
        checksum += bench::digest(message.legal_market());
    }

    void on(const protocol::IndexValueMessage&) {
        checksum += index++;
    }

    void on(const protocol::SettlementValueMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.class_key());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.price_type());
        checksum += bench::digest(message.no_entries());
    }

    void on(const protocol::SummaryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.class_key());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.price_type());
        checksum += bench::digest(message.trade_volume());
        checksum += bench::digest(message.open_interest());
        checksum += bench::digest(message.net_chg_prev_day().net_chg_prev_day_exponent());
        checksum += bench::digest(message.net_chg_prev_day().net_chg_prev_day_mantissa());
        checksum += bench::digest(message.underlying_px().underlying_px_exponent());
        checksum += bench::digest(message.underlying_px().underlying_px_mantissa());
        checksum += bench::digest(message.no_entries());
    }

    void on(const protocol::MarketDataControlMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.md_control_type());
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
    return bench::run("Cboe.C1Options.MarketDataFeed.Csm.v1.4.2", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
