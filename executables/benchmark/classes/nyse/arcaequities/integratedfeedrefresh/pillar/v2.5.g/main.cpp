// Nyse.ArcaEquities.IntegratedFeedRefresh.Pillar.v2.5.g benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/nyse/arcaequities/integratedfeedrefresh/pillar/v2.5.g.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/classes/nyse/arcaequities/integratedfeedrefresh/pillar/v2.5.g/definitions.hpp"

namespace protocol = ::nyse::arcaequities::integratedfeedrefresh::pillar::v2_5_g;

namespace {

// The values the Classes Packet decodes from one datagram, folded into a checksum. A datagram it cannot
// decode is a value the model never reads, so the benchmark refuses to time it.
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::Packet packet;

    try {
        packet.decode(frame.payload, frame.payload_len);
    } catch (const protocol::DecodeError& error) {
        throw;
        return checksum;
    }

    checksum += bench::digest(packet.packet_header().pkt_size());
    checksum += bench::digest(packet.packet_header().delivery_flag());
    checksum += bench::digest(packet.packet_header().number_msgs());
    checksum += bench::digest(packet.packet_header().seq_num());
    checksum += bench::digest(packet.packet_header().send_time().seconds());
    checksum += bench::digest(packet.packet_header().send_time().nanoseconds());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.message_header().message_size());
        checksum += bench::digest(each.message_header().message_type());

        if (const auto* message = dynamic_cast<const protocol::SequenceNumberResetMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time());
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).product_id());
            checksum += bench::digest((*message).channel_id());
        } else if (const auto* message = dynamic_cast<const protocol::SourceTimeReferenceMessage*>(each.message())) {
            checksum += bench::digest((*message).id());
            checksum += bench::digest((*message).symbol_seq_num());
            checksum += bench::digest((*message).source_time());
        } else if (const auto* message = dynamic_cast<const protocol::SymbolIndexMappingMessage*>(each.message())) {
            checksum += bench::digest((*message).symbol_index());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).market_id());
            checksum += bench::digest((*message).system_id());
            checksum += bench::digest((*message).exchange_code());
            checksum += bench::digest((*message).price_scale_code());
            checksum += bench::digest((*message).security_type());
            checksum += bench::digest((*message).lot_size());
            checksum += bench::digest((*message).prev_close_price());
            checksum += bench::digest((*message).prev_close_volume());
            checksum += bench::digest((*message).price_resolution());
            checksum += bench::digest((*message).round_lot());
            checksum += bench::digest((*message).mpv());
            checksum += bench::digest((*message).unit_of_trade());
        } else if (const auto* message = dynamic_cast<const protocol::SecurityStatusMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time());
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).symbol_index());
            checksum += bench::digest((*message).symbol_seq_num());
            checksum += bench::digest((*message).security_status());
            checksum += bench::digest((*message).halt_condition());
            checksum += bench::digest((*message).price_1());
            checksum += bench::digest((*message).price_2());
            checksum += bench::digest((*message).ssr_triggering_exchange_id());
            checksum += bench::digest((*message).ssr_triggering_volume());
            checksum += ((*message).time().has_value() ? bench::digest((*(*message).time())) : std::uint64_t{0});
            checksum += bench::digest((*message).ssr_state());
            checksum += bench::digest((*message).market_state());
            checksum += bench::digest((*message).session_state());
        } else if (const auto* message = dynamic_cast<const protocol::RefreshHeaderMessage*>(each.message())) {
            checksum += bench::digest((*message).current_refresh_pkt());
            checksum += bench::digest((*message).total_refresh_pkts());
        } else if (const auto* message = dynamic_cast<const protocol::ImbalanceMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time());
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).symbol_index());
            checksum += bench::digest((*message).symbol_seq_num());
            checksum += bench::digest((*message).reference_price());
            checksum += bench::digest((*message).paired_qty());
            checksum += bench::digest((*message).total_imbalance_qty());
            checksum += bench::digest((*message).market_imbalance_qty());
            checksum += bench::digest((*message).auction_time());
            checksum += bench::digest((*message).auction_type());
            checksum += bench::digest((*message).imbalance_side());
            checksum += bench::digest((*message).continuous_book_clearing_price());
            checksum += bench::digest((*message).auction_interest_clearing_price());
            checksum += bench::digest((*message).ssr_filing_price());
            checksum += bench::digest((*message).indicative_match_price());
            checksum += bench::digest((*message).upper_collar());
            checksum += bench::digest((*message).lower_collar());
            checksum += bench::digest((*message).auction_status());
            checksum += bench::digest((*message).freeze_status());
            checksum += bench::digest((*message).num_extensions());
            checksum += bench::digest((*message).unpaired_qty());
            checksum += bench::digest((*message).unpaired_side());
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderRefreshMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time());
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).symbol_index());
            checksum += bench::digest((*message).symbol_seq_num());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).price());
            checksum += bench::digest((*message).volume());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).firm_id());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nyse.ArcaEquities.IntegratedFeedRefresh.Pillar.v2.5.g", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
