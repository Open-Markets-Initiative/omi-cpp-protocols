// Nyse.TexasEquities.IntegratedFeedRefresh.Pillar.v2.5.g benchmark, through the Advanced session layer: every value it reads from every message of the simulated
// sequence (tests/simulated/nyse/texasequities/integratedfeedrefresh/pillar/v2.5.g.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "executables/benchmark/Benchmark.hpp"
#include "cpp/binary/advanced/nyse/texasequities/integratedfeedrefresh/pillar/v2.5.g/messages/session.hpp"

namespace protocol = ::nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g;

namespace {

// The handler the session layer hands each datagram's values to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    protocol::seq_action on_transport_header(const protocol::packet_header& header, const packet::Frame&) {
        checksum += bench::digest(header.pkt_size.get().value());
        checksum += bench::digest(header.delivery_flag.get().value());
        checksum += bench::digest(header.number_msgs.get().value());
        checksum += bench::digest(header.seq_num.get().value());
        checksum += bench::digest(header.send_time.seconds.get().value());
        checksum += bench::digest(header.send_time.nanoseconds.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::packet_header&) {
        ++index;
    }

    void on_message(const protocol::sequence_number_reset_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.source_time.get().value());
        checksum += bench::digest(message.fields.source_time_ns.get().value());
        checksum += bench::digest(message.fields.product_id.get().value());
        checksum += bench::digest(message.fields.channel_id.get().value());
    }

    void on_message(const protocol::source_time_reference_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.id.get().value());
        checksum += bench::digest(message.fields.symbol_seq_num.get().value());
        checksum += bench::digest(message.fields.source_time.get().value());
    }

    void on_message(const protocol::symbol_index_mapping_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.symbol_index.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.market_id.get().value());
        checksum += bench::digest(message.fields.system_id.get().value());
        checksum += bench::digest(message.fields.exchange_code.get().value());
        checksum += bench::digest(message.fields.price_scale_code.get().value());
        checksum += bench::digest(message.fields.security_type.get().value());
        checksum += bench::digest(message.fields.lot_size.get().value());
        checksum += bench::digest(message.fields.prev_close_price.get().value());
        checksum += bench::digest(message.fields.prev_close_volume.get().value());
        checksum += bench::digest(message.fields.price_resolution.get().value());
        checksum += bench::digest(message.fields.round_lot.get().value());
        checksum += bench::digest(message.fields.mpv.get().value());
        checksum += bench::digest(message.fields.unit_of_trade.get().value());
    }

    void on_message(const protocol::security_status_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.source_time.get().value());
        checksum += bench::digest(message.fields.source_time_ns.get().value());
        checksum += bench::digest(message.fields.symbol_index.get().value());
        checksum += bench::digest(message.fields.symbol_seq_num.get().value());
        checksum += bench::digest(message.fields.security_status.get().value());
        checksum += bench::digest(message.fields.halt_condition.get().value());
        checksum += bench::digest(message.fields.price_1.get().value());
        checksum += bench::digest(message.fields.price_2.get().value());
        checksum += bench::digest(message.fields.ssr_triggering_exchange_id.get().value());
        checksum += bench::digest(message.fields.ssr_triggering_volume.get().value());
        checksum += (message.fields.time.get().has_value() ? bench::digest(message.fields.time.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.ssr_state.get().value());
        checksum += bench::digest(message.fields.market_state.get().value());
        checksum += bench::digest(message.fields.session_state.get().value());
    }

    void on_message(const protocol::refresh_header_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.current_refresh_pkt.get().value());
        checksum += bench::digest(message.fields.total_refresh_pkts.get().value());
    }

    void on_message(const protocol::imbalance_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.source_time.get().value());
        checksum += bench::digest(message.fields.source_time_ns.get().value());
        checksum += bench::digest(message.fields.symbol_index.get().value());
        checksum += bench::digest(message.fields.symbol_seq_num.get().value());
        checksum += bench::digest(message.fields.reference_price.get().value());
        checksum += bench::digest(message.fields.paired_qty.get().value());
        checksum += bench::digest(message.fields.total_imbalance_qty.get().value());
        checksum += bench::digest(message.fields.market_imbalance_qty.get().value());
        checksum += bench::digest(message.fields.auction_time.get().value());
        checksum += bench::digest(message.fields.auction_type.get().value());
        checksum += bench::digest(message.fields.imbalance_side.get().value());
        checksum += bench::digest(message.fields.continuous_book_clearing_price.get().value());
        checksum += bench::digest(message.fields.auction_interest_clearing_price.get().value());
        checksum += bench::digest(message.fields.ssr_filing_price.get().value());
        checksum += bench::digest(message.fields.indicative_match_price.get().value());
        checksum += bench::digest(message.fields.upper_collar.get().value());
        checksum += bench::digest(message.fields.lower_collar.get().value());
        checksum += bench::digest(message.fields.auction_status.get().value());
        checksum += bench::digest(message.fields.freeze_status.get().value());
        checksum += bench::digest(message.fields.num_extensions.get().value());
        checksum += bench::digest(message.fields.unpaired_qty.get().value());
        checksum += bench::digest(message.fields.unpaired_side.get().value());
    }

    void on_message(const protocol::add_order_refresh_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.source_time.get().value());
        checksum += bench::digest(message.fields.source_time_ns.get().value());
        checksum += bench::digest(message.fields.symbol_index.get().value());
        checksum += bench::digest(message.fields.symbol_seq_num.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.price.get().value());
        checksum += bench::digest(message.fields.volume.get().value());
        checksum += bench::digest(message.fields.side.get().value());
        checksum += bench::digest(message.fields.firm_id.get().value());
    }
};

// The values Advanced reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    Reader reader;
    protocol::process_segment(reader, frame.payload, frame.payload_len, 0, frame);
    return reader.checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nyse.TexasEquities.IntegratedFeedRefresh.Pillar.v2.5.g", "advanced", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
