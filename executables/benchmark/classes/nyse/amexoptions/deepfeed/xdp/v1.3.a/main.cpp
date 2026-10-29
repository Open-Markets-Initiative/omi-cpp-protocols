// Nyse.AmexOptions.DeepFeed.Xdp.v1.3.a benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/nyse/amexoptions/deepfeed/xdp/v1.3.a.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/classes/nyse/amexoptions/deepfeed/xdp/v1.3.a/definitions.hpp"

namespace protocol = ::nyse::amexoptions::deepfeed::xdp::v1_3_a;

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

    checksum += bench::digest(packet.packet_header().packet_size());
    checksum += bench::digest(packet.packet_header().delivery_flag());
    checksum += bench::digest(packet.packet_header().message_count());
    checksum += bench::digest(packet.packet_header().sequence_number());
    checksum += bench::digest(packet.packet_header().send_time().seconds());
    checksum += bench::digest(packet.packet_header().send_time().nanoseconds());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.message_header().message_size());
        checksum += bench::digest(each.message_header().message_type());

        if (const auto* message = dynamic_cast<const protocol::OutrightMarketDepthBuyMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time());
            checksum += bench::digest((*message).source_ns());
            checksum += bench::digest((*message).series_index());
            checksum += bench::digest((*message).symbol_seq_num());
            checksum += bench::digest((*message).first_level_price());
            checksum += bench::digest((*message).second_level_price());
            checksum += bench::digest((*message).third_level_price());
            checksum += bench::digest((*message).first_level_volume());
            checksum += bench::digest((*message).second_level_volume());
            checksum += bench::digest((*message).third_level_volume());
            checksum += bench::digest((*message).quote_condition());
            checksum += bench::digest((*message).first_level_customer_volume());
            checksum += bench::digest((*message).second_level_customer_volume());
            checksum += bench::digest((*message).third_level_customer_volume());
        } else if (const auto* message = dynamic_cast<const protocol::OutrightMarketDepthSellMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time());
            checksum += bench::digest((*message).source_ns());
            checksum += bench::digest((*message).series_index());
            checksum += bench::digest((*message).symbol_seq_num());
            checksum += bench::digest((*message).first_level_price());
            checksum += bench::digest((*message).second_level_price());
            checksum += bench::digest((*message).third_level_price());
            checksum += bench::digest((*message).first_volume());
            checksum += bench::digest((*message).second_volume());
            checksum += bench::digest((*message).third_volume());
            checksum += bench::digest((*message).quote_condition());
            checksum += bench::digest((*message).first_level_customer_volume());
            checksum += bench::digest((*message).second_level_customer_volume());
            checksum += bench::digest((*message).third_level_customer_volume());
        } else if (const auto* message = dynamic_cast<const protocol::UnderlyingStatusMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time());
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).underlying_index());
            checksum += bench::digest((*message).underlying_seq_num());
            checksum += bench::digest((*message).security_status());
            checksum += bench::digest((*message).halt_condition());
        } else if (const auto* message = dynamic_cast<const protocol::OutrightSeriesStatusMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time());
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).series_index());
            checksum += bench::digest((*message).symbol_seq_num());
            checksum += bench::digest((*message).security_status());
            checksum += bench::digest((*message).halt_condition());
        } else if (const auto* message = dynamic_cast<const protocol::RefreshOutrightMarketDepthBuyMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time());
            checksum += bench::digest((*message).source_ns());
            checksum += bench::digest((*message).series_index());
            checksum += bench::digest((*message).symbol_seq_num());
            checksum += bench::digest((*message).first_level_price());
            checksum += bench::digest((*message).second_level_price());
            checksum += bench::digest((*message).third_level_price());
            checksum += bench::digest((*message).first_volume());
            checksum += bench::digest((*message).second_volume());
            checksum += bench::digest((*message).third_volume());
            checksum += bench::digest((*message).quote_condition());
            checksum += bench::digest((*message).first_level_customer_volume());
            checksum += bench::digest((*message).second_level_customer_volume());
            checksum += bench::digest((*message).third_level_customer_volume());
        } else if (const auto* message = dynamic_cast<const protocol::RefreshOutrightMarketDepthSellMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time());
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).series_index());
            checksum += bench::digest((*message).symbol_seq_num());
            checksum += bench::digest((*message).first_level_price());
            checksum += bench::digest((*message).second_level_price());
            checksum += bench::digest((*message).third_level_price());
            checksum += bench::digest((*message).first_volume());
            checksum += bench::digest((*message).second_volume());
            checksum += bench::digest((*message).third_volume());
            checksum += bench::digest((*message).quote_condition());
            checksum += bench::digest((*message).first_level_customer_volume());
            checksum += bench::digest((*message).second_level_customer_volume());
            checksum += bench::digest((*message).third_level_customer_volume());
        } else if (const auto* message = dynamic_cast<const protocol::UnderlyingIndexMappingMessage*>(each.message())) {
            checksum += bench::digest((*message).underlying_index());
            checksum += bench::digest((*message).underlying_symbol());
            checksum += bench::digest((*message).channel_id());
            checksum += bench::digest((*message).market_id());
            checksum += bench::digest((*message).system_id());
            checksum += bench::digest((*message).exchange_code());
            checksum += bench::digest((*message).price_scale_code());
            checksum += bench::digest((*message).security_type());
            checksum += bench::digest((*message).price_resolution());
        } else if (const auto* message = dynamic_cast<const protocol::SeriesIndexMappingMessage*>(each.message())) {
            checksum += bench::digest((*message).series_index());
            checksum += bench::digest((*message).channel_id());
            checksum += bench::digest((*message).market_id());
            checksum += bench::digest((*message).system_id());
            checksum += bench::digest((*message).stream_id());
            checksum += bench::digest((*message).underlying_index());
            checksum += bench::digest((*message).contract_multiplier());
            checksum += bench::digest((*message).maturity_date());
            checksum += bench::digest((*message).put_or_call());
            checksum += bench::digest((*message).strike_price());
            checksum += bench::digest((*message).price_scale_code());
            checksum += bench::digest((*message).underlying_symbol());
            checksum += bench::digest((*message).option_symbol_root());
            checksum += bench::digest((*message).group_id());
        } else if (const auto* message = dynamic_cast<const protocol::StreamIdMessage*>(each.message())) {
            checksum += bench::digest((*message).stream_id());
        } else if (const auto* message = dynamic_cast<const protocol::SequenceNumberResetMessage*>(each.message())) {
            checksum += bench::digest((*message).source_time());
            checksum += bench::digest((*message).source_time_ns());
            checksum += bench::digest((*message).product_id());
            checksum += bench::digest((*message).channel_id());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nyse.AmexOptions.DeepFeed.Xdp.v1.3.a", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
