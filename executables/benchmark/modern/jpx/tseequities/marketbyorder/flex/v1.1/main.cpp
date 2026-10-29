// Jpx.TseEquities.MarketByOrder.Flex.v1.1 benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/jpx/tseequities/marketbyorder/flex/v1.1.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/jpx/tseequities/marketbyorder/flex/v1.1/definitions.hpp"

namespace protocol = ::jpx::tseequities::marketbyorder::flex::v1_1;

namespace {

// The values the Modern iterator reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    checksum += bench::digest(iterator.packet_header->multicast_group_number.get());
    checksum += bench::digest(iterator.packet_header->number_of_system_reboots.get());
    checksum += bench::digest(iterator.packet_header->sequence_number.get());
    checksum += bench::digest(iterator.packet_header->issue_code.get());
    checksum += bench::digest(iterator.packet_header->update_number.get());
    checksum += bench::digest(iterator.packet_header->packet_number.get());
    checksum += bench::digest(iterator.packet_header->total_number_of_packets.get());
    checksum += bench::digest(iterator.packet_header->utility_flag.get());
    checksum += bench::digest(iterator.packet_header->message_count.get());

    std::size_t index = 0;

    while (iterator.next()) {
        checksum += index++;
        checksum += bench::digest(iterator.message_header->tag_length.get());
        checksum += bench::digest(iterator.message_header->message_type.get());

        if (iterator.message_type == protocol::SecondsTimestampMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SecondsTimestampMessage::parse(iterator.message);
            checksum += bench::digest(message->time_seconds.get());
        } else if (iterator.message_type == protocol::TradingStatusMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradingStatusMessage::parse(iterator.message);
            checksum += bench::digest(message->time_microseconds.get());
            checksum += bench::digest(message->market_status.get());
            checksum += bench::digest(message->status_flag.get());
            checksum += bench::digest(message->short_selling_status.get());
            checksum += bench::digest(message->pricing_method.get());
            checksum += bench::digest(message->book_center_price.integer());
        } else if (iterator.message_type == protocol::ExecutionSummaryMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ExecutionSummaryMessage::parse(iterator.message);
            checksum += bench::digest(message->time_microseconds.get());
            checksum += bench::digest(message->triggered_side.get());
            checksum += bench::digest(message->total_volume.get());
            checksum += bench::digest(message->total_invalidation.get());
            checksum += bench::digest(message->last_price.integer());
            checksum += bench::digest(message->match_id.get());
            checksum += (static_cast<std::uint64_t>(message->best_offer.integer()) != 0x0ULL ? bench::digest(message->best_offer.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->best_bid.integer()) != 0x0ULL ? bench::digest(message->best_bid.integer()) : std::uint64_t{0});
        } else if (iterator.message_type == protocol::AddOrderMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddOrderMessage::parse(iterator.message);
            checksum += bench::digest(message->time_microseconds.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->quantity.get());
            checksum += (static_cast<std::uint64_t>(message->price.integer()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->price.integer()) : std::uint64_t{0});
            checksum += bench::digest(message->order_condition.get());
            checksum += bench::digest(message->modification_flag.get());
        } else if (iterator.message_type == protocol::OrderExecutedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderExecutedMessage::parse(iterator.message);
            checksum += bench::digest(message->time_microseconds.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->volume.get());
            checksum += bench::digest(message->match_id.get());
        } else if (iterator.message_type == protocol::OrderExecutedWithPriceMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderExecutedWithPriceMessage::parse(iterator.message);
            checksum += bench::digest(message->time_microseconds.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->volume.get());
            checksum += bench::digest(message->match_id.get());
            checksum += bench::digest(message->execution_price.integer());
            checksum += bench::digest(message->adopted_pricing_method.get());
        } else if (iterator.message_type == protocol::OrderDeleteMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderDeleteMessage::parse(iterator.message);
            checksum += bench::digest(message->time_microseconds.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->modification_flag.get());
        } else if (iterator.message_type == protocol::ResetMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ResetMessage::parse(iterator.message);
            checksum += bench::digest(message->reset_start_end_flag.get());
        } else if (iterator.message_type == protocol::CommunicationControlMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::CommunicationControlMessage::parse(iterator.message);
            checksum += bench::digest(message->test_mode_flag.get());
            checksum += bench::digest(message->communication_start_end_flag.get());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Jpx.TseEquities.MarketByOrder.Flex.v1.1", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
