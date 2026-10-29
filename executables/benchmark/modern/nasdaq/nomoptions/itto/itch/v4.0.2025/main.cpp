// Nasdaq.NomOptions.Itto.Itch.v4.0.2025 benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/nomoptions/itto/itch/v4.0.2025.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/nasdaq/nomoptions/itto/itch/v4.0.2025/definitions.hpp"

namespace protocol = ::nasdaq::nomoptions::itto::itch::v4_0_2025;

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
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->event_code.get());
        } else if (iterator.message_type == protocol::OptionsDirectoryMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OptionsDirectoryMessage::parse(iterator.message);
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->option_id.get());
            checksum += bench::digest(message->security_symbol.get());
            checksum += bench::digest(message->expiration_year.get());
            checksum += bench::digest(message->expiration_month.get());
            checksum += bench::digest(message->expiration_date.get());
            checksum += bench::digest(message->explicit_strike_price.integer());
            checksum += bench::digest(message->option_type.get());
            checksum += bench::digest(message->source.get());
            checksum += bench::digest(message->underlying_symbol.get());
            checksum += bench::digest(message->options_closing_type.get());
            checksum += bench::digest(message->tradable.get());
            checksum += bench::digest(message->mpv.get());
        } else if (iterator.message_type == protocol::TradingActionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradingActionMessage::parse(iterator.message);
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->option_id.get());
            checksum += bench::digest(message->current_trading_state.get());
        } else if (iterator.message_type == protocol::SecurityOpenMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SecurityOpenMessage::parse(iterator.message);
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->option_id.get());
            checksum += bench::digest(message->open_state.get());
        } else if (iterator.message_type == protocol::AddOrderMessageShortMessageForm::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddOrderMessageShortMessageForm::parse(iterator.message);
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->order_reference_number.get());
            checksum += bench::digest(message->market_side.get());
            checksum += bench::digest(message->option_id.get());
            checksum += bench::digest(message->price_short.integer());
            checksum += bench::digest(message->volume_short.get());
        } else if (iterator.message_type == protocol::AddOrderMessageLongFormMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddOrderMessageLongFormMessage::parse(iterator.message);
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->order_reference_number.get());
            checksum += bench::digest(message->market_side.get());
            checksum += bench::digest(message->option_id.get());
            checksum += bench::digest(message->price_long.integer());
            checksum += bench::digest(message->volume_long.get());
        } else if (iterator.message_type == protocol::AddQuoteMessageShortFormMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddQuoteMessageShortFormMessage::parse(iterator.message);
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->bid_reference_number.get());
            checksum += bench::digest(message->ask_reference_number.get());
            checksum += bench::digest(message->option_id.get());
            checksum += bench::digest(message->bid_price_short.integer());
            checksum += bench::digest(message->bid_size_short.get());
            checksum += bench::digest(message->ask_price_short.integer());
            checksum += bench::digest(message->ask_size_short.get());
        } else if (iterator.message_type == protocol::AddQuoteMessageLongFormMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddQuoteMessageLongFormMessage::parse(iterator.message);
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->bid_reference_number.get());
            checksum += bench::digest(message->ask_reference_number.get());
            checksum += bench::digest(message->option_id.get());
            checksum += bench::digest(message->bid.get());
            checksum += bench::digest(message->bid_size_long.get());
            checksum += bench::digest(message->ask.get());
            checksum += bench::digest(message->ask_size_long.get());
        } else if (iterator.message_type == protocol::SingleSideExecutedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SingleSideExecutedMessage::parse(iterator.message);
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->reference_number.get());
            checksum += bench::digest(message->executed_contracts.get());
            checksum += bench::digest(message->cross_number.get());
            checksum += bench::digest(message->match_number.get());
        } else if (iterator.message_type == protocol::SingleSideExecutedWithPriceMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SingleSideExecutedWithPriceMessage::parse(iterator.message);
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->reference_number.get());
            checksum += bench::digest(message->cross_number.get());
            checksum += bench::digest(message->match_number.get());
            checksum += bench::digest(message->printable.get());
            checksum += bench::digest(message->price_long.integer());
            checksum += bench::digest(message->volume_long.get());
        } else if (iterator.message_type == protocol::OrderCancelMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderCancelMessage::parse(iterator.message);
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->order_reference_number.get());
            checksum += bench::digest(message->cancelled_contracts.get());
        } else if (iterator.message_type == protocol::SingleSideReplaceMessageShortForm::message_type) {
            [[maybe_unused]] const auto* message = protocol::SingleSideReplaceMessageShortForm::parse(iterator.message);
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->original_reference_number.get());
            checksum += bench::digest(message->new_reference_number.get());
            checksum += bench::digest(message->price_short.integer());
            checksum += bench::digest(message->volume_short.get());
        } else if (iterator.message_type == protocol::SingleSideReplaceMessageLongForm::message_type) {
            [[maybe_unused]] const auto* message = protocol::SingleSideReplaceMessageLongForm::parse(iterator.message);
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->original_reference_number.get());
            checksum += bench::digest(message->new_reference_number.get());
            checksum += bench::digest(message->price_long.integer());
            checksum += bench::digest(message->volume_long.get());
        } else if (iterator.message_type == protocol::SingleSideDeleteMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SingleSideDeleteMessage::parse(iterator.message);
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->reference_number.get());
        } else if (iterator.message_type == protocol::SingleSideChangeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SingleSideChangeMessage::parse(iterator.message);
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->reference_number.get());
            checksum += bench::digest(message->change_reason.get());
            checksum += bench::digest(message->price_long.integer());
            checksum += bench::digest(message->volume_long.get());
        } else if (iterator.message_type == protocol::QuoteReplaceMessageShortForm::message_type) {
            [[maybe_unused]] const auto* message = protocol::QuoteReplaceMessageShortForm::parse(iterator.message);
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->original_bid_reference_number.get());
            checksum += bench::digest(message->bid_reference_number.get());
            checksum += bench::digest(message->original_ask_reference_number.get());
            checksum += bench::digest(message->ask_reference_number.get());
            checksum += bench::digest(message->bid_price_short.integer());
            checksum += bench::digest(message->bid_size_short.get());
            checksum += bench::digest(message->ask_price_short.integer());
            checksum += bench::digest(message->ask_size_short.get());
        } else if (iterator.message_type == protocol::QuoteReplaceMessageLongForm::message_type) {
            [[maybe_unused]] const auto* message = protocol::QuoteReplaceMessageLongForm::parse(iterator.message);
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->original_bid_reference_number.get());
            checksum += bench::digest(message->bid_reference_number.get());
            checksum += bench::digest(message->original_ask_reference_number.get());
            checksum += bench::digest(message->ask_reference_number.get());
            checksum += bench::digest(message->bid_price_long.integer());
            checksum += bench::digest(message->bid_size_long.get());
            checksum += bench::digest(message->ask_price_long.integer());
            checksum += bench::digest(message->ask_size_long.get());
        } else if (iterator.message_type == protocol::QuoteDeleteMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::QuoteDeleteMessage::parse(iterator.message);
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->bid_reference_number.get());
            checksum += bench::digest(message->ask_reference_number.get());
        } else if (iterator.message_type == protocol::OptionsTradeMessagesNonAuction::message_type) {
            [[maybe_unused]] const auto* message = protocol::OptionsTradeMessagesNonAuction::parse(iterator.message);
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->buy_sell_indicator.get());
            checksum += bench::digest(message->option_id.get());
            checksum += bench::digest(message->cross_number.get());
            checksum += bench::digest(message->match_number.get());
            checksum += bench::digest(message->price_long.integer());
            checksum += bench::digest(message->volume_long.get());
        } else if (iterator.message_type == protocol::OptionsCrossTradeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OptionsCrossTradeMessage::parse(iterator.message);
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->option_id.get());
            checksum += bench::digest(message->cross_number.get());
            checksum += bench::digest(message->match_number.get());
            checksum += bench::digest(message->cross_type.get());
            checksum += bench::digest(message->price_long.integer());
            checksum += bench::digest(message->volume_long.get());
        } else if (iterator.message_type == protocol::BrokenTradeOrderExecutedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::BrokenTradeOrderExecutedMessage::parse(iterator.message);
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->cross_number.get());
            checksum += bench::digest(message->match_number.get());
        } else if (iterator.message_type == protocol::NoiiMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::NoiiMessage::parse(iterator.message);
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->auction_id.get());
            checksum += bench::digest(message->auction_type.get());
            checksum += bench::digest(message->paired_contracts.get());
            checksum += bench::digest(message->imbalance_direction.get());
            checksum += bench::digest(message->option_id.get());
            checksum += bench::digest(message->imbalance_price.integer());
            checksum += bench::digest(message->imbalance_volume.get());
            checksum += bench::digest(message->customer_firm_indicator.get());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nasdaq.NomOptions.Itto.Itch.v4.0.2025", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
