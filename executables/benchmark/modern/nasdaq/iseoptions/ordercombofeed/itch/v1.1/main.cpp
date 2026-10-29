// Nasdaq.IseOptions.OrderComboFeed.Itch.v1.1 benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/iseoptions/ordercombofeed/itch/v1.1.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/nasdaq/iseoptions/ordercombofeed/itch/v1.1/definitions.hpp"

namespace protocol = ::nasdaq::iseoptions::ordercombofeed::itch::v1_1;

namespace {

// The values the Modern iterator reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    checksum += bench::digest(iterator.packet_header->session.get());
    checksum += bench::digest(iterator.packet_header->sequence_number.get());
    checksum += bench::digest(iterator.packet_header->message_count.get());

    std::size_t index = 0;

    while (iterator.next()) {
        checksum += index++;
        checksum += bench::digest(iterator.message_header->message_length.get());
        checksum += bench::digest(iterator.message_header->message_type.get());

        if (iterator.message_type == protocol::SystemEventMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SystemEventMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->event_code.get());
            checksum += bench::digest(message->current_year.get());
            checksum += bench::digest(message->current_month.get());
            checksum += bench::digest(message->current_day.get());
            checksum += bench::digest(message->version.get());
            checksum += bench::digest(message->sub_version.get());
        } else if (iterator.message_type == protocol::ComplexStrategyDirectoryMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ComplexStrategyDirectoryMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->strategy_id.get());
            checksum += bench::digest(message->strategy_type.get());
            checksum += bench::digest(message->source.get());
            checksum += bench::digest(message->underlying_symbol.get());
            checksum += bench::digest(message->number_of_legs.get());
        } else if (iterator.message_type == protocol::StrategyTradingActionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::StrategyTradingActionMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->strategy_id.get());
            checksum += bench::digest(message->current_trading_state.get());
        } else if (iterator.message_type == protocol::StrategyOpenClosedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::StrategyOpenClosedMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->strategy_id.get());
            checksum += bench::digest(message->open_state.get());
        } else if (iterator.message_type == protocol::ComplexStrategyOrderOnBookMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ComplexStrategyOrderOnBookMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->strategy_id.get());
            checksum += bench::digest(message->order_type.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->size.get());
            checksum += bench::digest(message->exec_flag.get());
            checksum += bench::digest(message->order_capacity.get());
            checksum += bench::digest(message->scope.get());
            checksum += bench::digest(message->owner_id.get());
            checksum += bench::digest(message->giveup.get());
            checksum += bench::digest(message->cmta.get());
        } else if (iterator.message_type == protocol::ComplexStrategyAuctionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ComplexStrategyAuctionMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->strategy_id.get());
            checksum += bench::digest(message->auction_id.get());
            checksum += bench::digest(message->order_type.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->size.get());
            checksum += bench::digest(message->exec_flag.get());
            checksum += bench::digest(message->order_capacity.get());
            checksum += bench::digest(message->scope.get());
            checksum += bench::digest(message->owner_id.get());
            checksum += bench::digest(message->giveup.get());
            checksum += bench::digest(message->cmta.get());
            checksum += bench::digest(message->auction_event.get());
            checksum += bench::digest(message->auction_type.get());
            checksum += bench::digest(message->number_of_responses.get());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nasdaq.IseOptions.OrderComboFeed.Itch.v1.1", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
