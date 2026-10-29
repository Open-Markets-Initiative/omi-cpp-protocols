// Nasdaq.NsmEquities.TotalView.Itch.v4.0 benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/nsmequities/totalview/itch/v4.0.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/nasdaq/nsmequities/totalview/itch/v4.0/definitions.hpp"

namespace protocol = ::nasdaq::nsmequities::totalview::itch::v4_0;

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
        } else if (iterator.message_type == protocol::StockDirectoryMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::StockDirectoryMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->stock.get());
            checksum += bench::digest(message->market_category.get());
            checksum += bench::digest(message->financial_status_indicator.get());
            checksum += bench::digest(message->round_lot_size.get());
            checksum += bench::digest(message->round_lots_only.get());
        } else if (iterator.message_type == protocol::StockTradingActionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::StockTradingActionMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->stock.get());
            checksum += bench::digest(message->trading_state.get());
            checksum += bench::digest(message->reserved.get());
            checksum += bench::digest(message->reason.get());
        } else if (iterator.message_type == protocol::MarketParticipantPositionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::MarketParticipantPositionMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->mpid.get());
            checksum += bench::digest(message->stock.get());
            checksum += bench::digest(message->primary_market_maker.get());
            checksum += bench::digest(message->market_maker_mode.get());
            checksum += bench::digest(message->market_participant_state.get());
        } else if (iterator.message_type == protocol::AddOrderMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddOrderMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->order_reference_number.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->shares.get());
            checksum += bench::digest(message->stock.get());
            checksum += bench::digest(message->price.integer());
        } else if (iterator.message_type == protocol::AddOrderWithMpidMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddOrderWithMpidMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->order_reference_number.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->shares.get());
            checksum += bench::digest(message->stock.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->attribution.get());
        } else if (iterator.message_type == protocol::OrderExecutedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderExecutedMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->order_reference_number.get());
            checksum += bench::digest(message->executed_shares.get());
            checksum += bench::digest(message->match_number.get());
        } else if (iterator.message_type == protocol::OrderExecutedWithPriceMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderExecutedWithPriceMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->order_reference_number.get());
            checksum += bench::digest(message->executed_shares.get());
            checksum += bench::digest(message->match_number.get());
            checksum += bench::digest(message->printable.get());
            checksum += bench::digest(message->execution_price.integer());
        } else if (iterator.message_type == protocol::OrderCancelMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderCancelMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->order_reference_number.get());
            checksum += bench::digest(message->canceled_shares.get());
        } else if (iterator.message_type == protocol::OrderDeleteMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderDeleteMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->order_reference_number.get());
        } else if (iterator.message_type == protocol::OrderReplaceMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderReplaceMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->original_order_reference_number.get());
            checksum += bench::digest(message->new_order_reference_number.get());
            checksum += bench::digest(message->shares.get());
            checksum += bench::digest(message->price.integer());
        } else if (iterator.message_type == protocol::TradeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->order_reference_number.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->shares.get());
            checksum += bench::digest(message->stock.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->match_number.get());
        } else if (iterator.message_type == protocol::CrossTradeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::CrossTradeMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->cross_shares.get());
            checksum += bench::digest(message->stock.get());
            checksum += bench::digest(message->cross_price.integer());
            checksum += bench::digest(message->match_number.get());
            checksum += bench::digest(message->cross_type.get());
        } else if (iterator.message_type == protocol::BrokenTradeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::BrokenTradeMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->match_number.get());
        } else if (iterator.message_type == protocol::NetOrderImbalanceIndicatorMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::NetOrderImbalanceIndicatorMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->paired_shares.get());
            checksum += bench::digest(message->imbalance_shares.get());
            checksum += bench::digest(message->imbalance_direction.get());
            checksum += bench::digest(message->stock.get());
            checksum += bench::digest(message->far_price.integer());
            checksum += bench::digest(message->near_price.integer());
            checksum += bench::digest(message->current_reference_price.integer());
            checksum += bench::digest(message->cross_type.get());
            checksum += bench::digest(message->price_variation_indicator.get());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nasdaq.NsmEquities.TotalView.Itch.v4.0", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
