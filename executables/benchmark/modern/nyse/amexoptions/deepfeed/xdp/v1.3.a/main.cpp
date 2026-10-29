// Nyse.AmexOptions.DeepFeed.Xdp.v1.3.a benchmark, through the Modern iterator: every value it reads from every message of the simulated
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
#include "cpp/binary/modern/nyse/amexoptions/deepfeed/xdp/v1.3.a/definitions.hpp"

namespace protocol = ::nyse::amexoptions::deepfeed::xdp::v1_3_a;

namespace {

// The values the Modern iterator reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    checksum += bench::digest(iterator.packet_header->packet_size.get());
    checksum += bench::digest(iterator.packet_header->delivery_flag.get());
    checksum += bench::digest(iterator.packet_header->message_count.get());
    checksum += bench::digest(iterator.packet_header->sequence_number.get());
    checksum += bench::digest(iterator.packet_header->send_time.seconds.get());
    checksum += bench::digest(iterator.packet_header->send_time.nanoseconds.get());

    std::size_t index = 0;

    while (iterator.next()) {
        checksum += index++;
        checksum += bench::digest(iterator.message_header->message_size.get());
        checksum += bench::digest(iterator.message_header->message_type.get());

        if (iterator.message_type == protocol::OutrightMarketDepthBuyMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OutrightMarketDepthBuyMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time.get());
            checksum += bench::digest(message->source_ns.get());
            checksum += bench::digest(message->series_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->first_level_price.get());
            checksum += bench::digest(message->second_level_price.get());
            checksum += bench::digest(message->third_level_price.get());
            checksum += bench::digest(message->first_level_volume.get());
            checksum += bench::digest(message->second_level_volume.get());
            checksum += bench::digest(message->third_level_volume.get());
            checksum += bench::digest(message->quote_condition.get());
            checksum += bench::digest(message->first_level_customer_volume.get());
            checksum += bench::digest(message->second_level_customer_volume.get());
            checksum += bench::digest(message->third_level_customer_volume.get());
        } else if (iterator.message_type == protocol::OutrightMarketDepthSellMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OutrightMarketDepthSellMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time.get());
            checksum += bench::digest(message->source_ns.get());
            checksum += bench::digest(message->series_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->first_level_price.get());
            checksum += bench::digest(message->second_level_price.get());
            checksum += bench::digest(message->third_level_price.get());
            checksum += bench::digest(message->first_volume.get());
            checksum += bench::digest(message->second_volume.get());
            checksum += bench::digest(message->third_volume.get());
            checksum += bench::digest(message->quote_condition.get());
            checksum += bench::digest(message->first_level_customer_volume.get());
            checksum += bench::digest(message->second_level_customer_volume.get());
            checksum += bench::digest(message->third_level_customer_volume.get());
        } else if (iterator.message_type == protocol::UnderlyingStatusMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::UnderlyingStatusMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time.get());
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->underlying_index.get());
            checksum += bench::digest(message->underlying_seq_num.get());
            checksum += bench::digest(message->security_status.get());
            checksum += bench::digest(message->halt_condition.get());
        } else if (iterator.message_type == protocol::OutrightSeriesStatusMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OutrightSeriesStatusMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time.get());
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->series_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->security_status.get());
            checksum += bench::digest(message->halt_condition.get());
        } else if (iterator.message_type == protocol::RefreshOutrightMarketDepthBuyMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::RefreshOutrightMarketDepthBuyMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time.get());
            checksum += bench::digest(message->source_ns.get());
            checksum += bench::digest(message->series_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->first_level_price.get());
            checksum += bench::digest(message->second_level_price.get());
            checksum += bench::digest(message->third_level_price.get());
            checksum += bench::digest(message->first_volume.get());
            checksum += bench::digest(message->second_volume.get());
            checksum += bench::digest(message->third_volume.get());
            checksum += bench::digest(message->quote_condition.get());
            checksum += bench::digest(message->first_level_customer_volume.get());
            checksum += bench::digest(message->second_level_customer_volume.get());
            checksum += bench::digest(message->third_level_customer_volume.get());
        } else if (iterator.message_type == protocol::RefreshOutrightMarketDepthSellMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::RefreshOutrightMarketDepthSellMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time.get());
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->series_index.get());
            checksum += bench::digest(message->symbol_seq_num.get());
            checksum += bench::digest(message->first_level_price.get());
            checksum += bench::digest(message->second_level_price.get());
            checksum += bench::digest(message->third_level_price.get());
            checksum += bench::digest(message->first_volume.get());
            checksum += bench::digest(message->second_volume.get());
            checksum += bench::digest(message->third_volume.get());
            checksum += bench::digest(message->quote_condition.get());
            checksum += bench::digest(message->first_level_customer_volume.get());
            checksum += bench::digest(message->second_level_customer_volume.get());
            checksum += bench::digest(message->third_level_customer_volume.get());
        } else if (iterator.message_type == protocol::UnderlyingIndexMappingMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::UnderlyingIndexMappingMessage::parse(iterator.message);
            checksum += bench::digest(message->underlying_index.get());
            checksum += bench::digest(message->underlying_symbol.get());
            checksum += bench::digest(message->channel_id.get());
            checksum += bench::digest(message->market_id.get());
            checksum += bench::digest(message->system_id.get());
            checksum += bench::digest(message->exchange_code.get());
            checksum += bench::digest(message->price_scale_code.get());
            checksum += bench::digest(message->security_type.get());
            checksum += bench::digest(message->price_resolution.get());
        } else if (iterator.message_type == protocol::SeriesIndexMappingMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SeriesIndexMappingMessage::parse(iterator.message);
            checksum += bench::digest(message->series_index.get());
            checksum += bench::digest(message->channel_id.get());
            checksum += bench::digest(message->market_id.get());
            checksum += bench::digest(message->system_id.get());
            checksum += bench::digest(message->stream_id.get());
            checksum += bench::digest(message->underlying_index.get());
            checksum += bench::digest(message->contract_multiplier.get());
            checksum += bench::digest(message->maturity_date.get());
            checksum += bench::digest(message->put_or_call.get());
            checksum += bench::digest(message->strike_price.get());
            checksum += bench::digest(message->price_scale_code.get());
            checksum += bench::digest(message->underlying_symbol.get());
            checksum += bench::digest(message->option_symbol_root.get());
            checksum += bench::digest(message->group_id.get());
        } else if (iterator.message_type == protocol::StreamIdMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::StreamIdMessage::parse(iterator.message);
            checksum += bench::digest(message->stream_id.get());
        } else if (iterator.message_type == protocol::SequenceNumberResetMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SequenceNumberResetMessage::parse(iterator.message);
            checksum += bench::digest(message->source_time.get());
            checksum += bench::digest(message->source_time_ns.get());
            checksum += bench::digest(message->product_id.get());
            checksum += bench::digest(message->channel_id.get());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nyse.AmexOptions.DeepFeed.Xdp.v1.3.a", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
