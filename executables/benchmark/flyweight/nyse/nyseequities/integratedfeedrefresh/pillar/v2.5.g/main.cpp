// Nyse.NyseEquities.IntegratedFeedRefresh.Pillar.v2.5.g benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/nyse/nyseequities/integratedfeedrefresh/pillar/v2.5.g.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/nyse/nyseequities/integratedfeedrefresh/pillar/v2.5.g/definitions.hpp"

namespace protocol = ::nyse::nyseequities::integratedfeedrefresh::pillar::v2_5_g;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        checksum += bench::digest(packet.packet_header().pkt_size());
        checksum += bench::digest(packet.packet_header().delivery_flag());
        checksum += bench::digest(packet.packet_header().number_msgs());
        checksum += bench::digest(packet.packet_header().seq_num());
        checksum += bench::digest(packet.packet_header().send_time().seconds());
        checksum += bench::digest(packet.packet_header().send_time().nanoseconds());
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

    void on(const protocol::SequenceNumberResetMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.source_time());
        checksum += bench::digest(message.source_time_ns());
        checksum += bench::digest(message.product_id());
        checksum += bench::digest(message.channel_id());
    }

    void on(const protocol::SourceTimeReferenceMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.id());
        checksum += bench::digest(message.symbol_seq_num());
        checksum += bench::digest(message.source_time());
    }

    void on(const protocol::SymbolIndexMappingMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.symbol_index());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.market_id());
        checksum += bench::digest(message.system_id());
        checksum += bench::digest(message.exchange_code());
        checksum += bench::digest(message.price_scale_code());
        checksum += bench::digest(message.security_type());
        checksum += bench::digest(message.lot_size());
        checksum += bench::digest(message.prev_close_price());
        checksum += bench::digest(message.prev_close_volume());
        checksum += bench::digest(message.price_resolution());
        checksum += bench::digest(message.round_lot());
        checksum += bench::digest(message.mpv());
        checksum += bench::digest(message.unit_of_trade());
    }

    void on(const protocol::SecurityStatusMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.source_time());
        checksum += bench::digest(message.source_time_ns());
        checksum += bench::digest(message.symbol_index());
        checksum += bench::digest(message.symbol_seq_num());
        checksum += bench::digest(message.security_status());
        checksum += bench::digest(message.halt_condition());
        checksum += bench::digest(message.price_1());
        checksum += bench::digest(message.price_2());
        checksum += bench::digest(message.ssr_triggering_exchange_id());
        checksum += bench::digest(message.ssr_triggering_volume());
        checksum += (message.time().has_value() ? bench::digest((*message.time())) : std::uint64_t{0});
        checksum += bench::digest(message.ssr_state());
        checksum += bench::digest(message.market_state());
        checksum += bench::digest(message.session_state());
    }

    void on(const protocol::RefreshHeaderMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.current_refresh_pkt());
        checksum += bench::digest(message.total_refresh_pkts());
    }

    void on(const protocol::ImbalanceMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.source_time());
        checksum += bench::digest(message.source_time_ns());
        checksum += bench::digest(message.symbol_index());
        checksum += bench::digest(message.symbol_seq_num());
        checksum += bench::digest(message.reference_price());
        checksum += bench::digest(message.paired_qty());
        checksum += bench::digest(message.total_imbalance_qty());
        checksum += bench::digest(message.market_imbalance_qty());
        checksum += bench::digest(message.auction_time());
        checksum += bench::digest(message.auction_type());
        checksum += bench::digest(message.imbalance_side());
        checksum += bench::digest(message.continuous_book_clearing_price());
        checksum += bench::digest(message.auction_interest_clearing_price());
        checksum += bench::digest(message.ssr_filing_price());
        checksum += bench::digest(message.indicative_match_price());
        checksum += bench::digest(message.upper_collar());
        checksum += bench::digest(message.lower_collar());
        checksum += bench::digest(message.auction_status());
        checksum += bench::digest(message.freeze_status());
        checksum += bench::digest(message.num_extensions());
        checksum += bench::digest(message.unpaired_qty());
        checksum += bench::digest(message.unpaired_side());
    }

    void on(const protocol::AddOrderRefreshMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.source_time());
        checksum += bench::digest(message.source_time_ns());
        checksum += bench::digest(message.symbol_index());
        checksum += bench::digest(message.symbol_seq_num());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.price());
        checksum += bench::digest(message.volume());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.firm_id());
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
    return bench::run("Nyse.NyseEquities.IntegratedFeedRefresh.Pillar.v2.5.g", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
