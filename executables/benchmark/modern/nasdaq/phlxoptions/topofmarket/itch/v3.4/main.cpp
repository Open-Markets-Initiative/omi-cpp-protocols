// Nasdaq.PhlxOptions.TopOfMarket.Itch.v3.4 benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/phlxoptions/topofmarket/itch/v3.4.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/nasdaq/phlxoptions/topofmarket/itch/v3.4/definitions.hpp"

namespace protocol = ::nasdaq::phlxoptions::topofmarket::itch::v3_4;

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

        if (iterator.message_type == protocol::TimestampMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TimestampMessage::parse(iterator.message);
            checksum += bench::digest(message->second.get());
        } else if (iterator.message_type == protocol::SystemEventMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SystemEventMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->event_code.get());
            checksum += bench::digest(message->version.get());
            checksum += bench::digest(message->sub_version.get());
        } else if (iterator.message_type == protocol::OptionsDirectoryMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OptionsDirectoryMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->option_id.get());
            checksum += bench::digest(message->security_symbol.get());
            checksum += bench::digest(message->expiration_year.get());
            checksum += bench::digest(message->expiration_month.get());
            checksum += bench::digest(message->expiration_day.get());
            checksum += bench::digest(message->strike_price.integer());
            checksum += bench::digest(message->option_type.get());
            checksum += bench::digest(message->source.get());
            checksum += bench::digest(message->underlying_symbol.get());
            checksum += bench::digest(message->option_closing_type.get());
            checksum += bench::digest(message->tradable.get());
            checksum += bench::digest(message->mpv.get());
        } else if (iterator.message_type == protocol::TradingActionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradingActionMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->option_id.get());
            checksum += bench::digest(message->current_trading_state.get());
        } else if (iterator.message_type == protocol::SecurityOpenClosedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SecurityOpenClosedMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->option_id.get());
            checksum += bench::digest(message->open_state.get());
        } else if (iterator.message_type == protocol::ShortBestBidAndAskUpdateMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ShortBestBidAndAskUpdateMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->option_id.get());
            checksum += bench::digest(message->quote_condition.get());
            checksum += bench::digest(message->bid_price_2.integer());
            checksum += bench::digest(message->bid_size_2.get());
            checksum += bench::digest(message->ask_price_2.integer());
            checksum += bench::digest(message->ask_size_2.get());
        } else if (iterator.message_type == protocol::LongBestBidAndAskUpdateMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::LongBestBidAndAskUpdateMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->option_id.get());
            checksum += bench::digest(message->quote_condition.get());
            checksum += bench::digest(message->bid_price_4.integer());
            checksum += bench::digest(message->bid_size_4.get());
            checksum += bench::digest(message->ask_price_4.integer());
            checksum += bench::digest(message->ask_size_4.get());
        } else if (iterator.message_type == protocol::ShortBestAskUpdateMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ShortBestAskUpdateMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->option_id.get());
            checksum += bench::digest(message->quote_condition.get());
            checksum += bench::digest(message->price_2.integer());
            checksum += bench::digest(message->size_2.get());
        } else if (iterator.message_type == protocol::ShortBestBidUpdateMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ShortBestBidUpdateMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->option_id.get());
            checksum += bench::digest(message->quote_condition.get());
            checksum += bench::digest(message->price_2.integer());
            checksum += bench::digest(message->size_2.get());
        } else if (iterator.message_type == protocol::LongBestAskUpdateMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::LongBestAskUpdateMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->option_id.get());
            checksum += bench::digest(message->quote_condition.get());
            checksum += bench::digest(message->price_4.integer());
            checksum += bench::digest(message->size_4.get());
        } else if (iterator.message_type == protocol::LongBestBidUpdateMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::LongBestBidUpdateMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->option_id.get());
            checksum += bench::digest(message->quote_condition.get());
            checksum += bench::digest(message->price_4.integer());
            checksum += bench::digest(message->size_4.get());
        } else if (iterator.message_type == protocol::TradeReportMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeReportMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->option_id.get());
            checksum += bench::digest(message->cross_id.get());
            checksum += bench::digest(message->trade_condition.get());
            checksum += bench::digest(message->price_4.integer());
            checksum += bench::digest(message->volume.get());
        } else if (iterator.message_type == protocol::BrokenTradeReportMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::BrokenTradeReportMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->option_id.get());
            checksum += bench::digest(message->original_cross_id.get());
            checksum += bench::digest(message->original_price.integer());
            checksum += bench::digest(message->original_volume.get());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nasdaq.PhlxOptions.TopOfMarket.Itch.v3.4", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
