// Nasdaq.IseOptions.TopComboQuoteFeed.Itch.v1.0 benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/iseoptions/topcomboquotefeed/itch/v1.0.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/definitions.hpp"

namespace protocol = ::nasdaq::iseoptions::topcomboquotefeed::itch::v1_0;

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
        } else if (iterator.message_type == protocol::StrategyOpenClosedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::StrategyOpenClosedMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->strategy_id.get());
            checksum += bench::digest(message->open_state.get());
        } else if (iterator.message_type == protocol::StrategyTradingActionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::StrategyTradingActionMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->strategy_id.get());
            checksum += bench::digest(message->current_trading_state.get());
        } else if (iterator.message_type == protocol::StrategyBestBidAndAskUpdate::message_type) {
            [[maybe_unused]] const auto* message = protocol::StrategyBestBidAndAskUpdate::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->strategy_id.get());
            checksum += bench::digest(message->quote_condition.get());
            checksum += bench::digest(message->bid_price.integer());
            checksum += bench::digest(message->bid_size.get());
            checksum += bench::digest(message->bid_cust_size.get());
            checksum += bench::digest(message->bid_pro_cust_size.get());
            checksum += bench::digest(message->bid_ntt_size.get());
            checksum += bench::digest(message->bid_market_size.get());
            checksum += bench::digest(message->bid_ntt_market_size.get());
            checksum += bench::digest(message->ask_price.integer());
            checksum += bench::digest(message->ask_size.get());
            checksum += bench::digest(message->ask_cust_size.get());
            checksum += bench::digest(message->ask_pro_cust_size.get());
            checksum += bench::digest(message->ask_ntt_size.get());
            checksum += bench::digest(message->ask_market_size.get());
            checksum += bench::digest(message->ask_ntt_market_size.get());
        } else if (iterator.message_type == protocol::StrategyBestBidUpdate::message_type) {
            [[maybe_unused]] const auto* message = protocol::StrategyBestBidUpdate::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->strategy_id.get());
            checksum += bench::digest(message->quote_condition.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->size.get());
            checksum += bench::digest(message->cust_size.get());
            checksum += bench::digest(message->pro_cust_size.get());
            checksum += bench::digest(message->ntt_size.get());
            checksum += bench::digest(message->market_size.get());
            checksum += bench::digest(message->ntt_market_size.get());
        } else if (iterator.message_type == protocol::StrategyBestAskUpdate::message_type) {
            [[maybe_unused]] const auto* message = protocol::StrategyBestAskUpdate::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->strategy_id.get());
            checksum += bench::digest(message->quote_condition.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->size.get());
            checksum += bench::digest(message->cust_size.get());
            checksum += bench::digest(message->pro_cust_size.get());
            checksum += bench::digest(message->ntt_size.get());
            checksum += bench::digest(message->market_size.get());
            checksum += bench::digest(message->ntt_market_size.get());
        } else if (iterator.message_type == protocol::ComplexStrategyTickerMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ComplexStrategyTickerMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->strategy_id.get());
            checksum += bench::digest(message->last_price.integer());
            checksum += bench::digest(message->size.get());
            checksum += bench::digest(message->volume.get());
            checksum += bench::digest(message->high.get());
            checksum += bench::digest(message->low.get());
            checksum += bench::digest(message->first.get());
            checksum += bench::digest(message->trade_condition.get());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nasdaq.IseOptions.TopComboQuoteFeed.Itch.v1.0", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
