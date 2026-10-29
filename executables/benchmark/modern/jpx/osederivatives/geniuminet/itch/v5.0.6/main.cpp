// Jpx.OseDerivatives.GeniumInet.Itch.v5.0.6 benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/jpx/osederivatives/geniuminet/itch/v5.0.6.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/jpx/osederivatives/geniuminet/itch/v5.0.6/definitions.hpp"

namespace protocol = ::jpx::osederivatives::geniuminet::itch::v5_0_6;

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

        if (iterator.message_type == protocol::SecondsMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SecondsMessage::parse(iterator.message);
            checksum += bench::digest(message->seconds.get());
        } else if (iterator.message_type == protocol::OrderBookDirectory::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderBookDirectory::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->order_book_id.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->long_name.get());
            checksum += bench::digest(message->isin.get());
            checksum += bench::digest(message->financial_product.get());
            checksum += bench::digest(message->trading_currency.get());
            checksum += bench::digest(message->decimals_in_price.get());
            checksum += bench::digest(message->decimals_in_nominal_value.get());
            checksum += bench::digest(message->odd_lot_size.get());
            checksum += bench::digest(message->round_lot_size.get());
            checksum += bench::digest(message->block_lot_size.get());
            checksum += bench::digest(message->nominal_value.get());
            checksum += bench::digest(message->number_of_legs.get());
            checksum += bench::digest(message->underlying_orderbook_id.get());
            checksum += bench::digest(message->strike_price.get());
            checksum += bench::digest(message->expiration_date.get());
            checksum += bench::digest(message->decimals_in_strike_price.get());
            checksum += bench::digest(message->put_or_call.get());
        } else if (iterator.message_type == protocol::CombinationOrderbookLeg::message_type) {
            [[maybe_unused]] const auto* message = protocol::CombinationOrderbookLeg::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->combination_orderbook_id.get());
            checksum += bench::digest(message->leg_orderbook_id.get());
            checksum += bench::digest(message->leg_side.get());
            checksum += bench::digest(message->leg_ratio.get());
        } else if (iterator.message_type == protocol::TickSizeTableEntry::message_type) {
            [[maybe_unused]] const auto* message = protocol::TickSizeTableEntry::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->order_book_id.get());
            checksum += bench::digest(message->tick_size.get());
            checksum += bench::digest(message->price_from.get());
            checksum += bench::digest(message->price_to.get());
        } else if (iterator.message_type == protocol::SystemEventMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SystemEventMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->event_code.get());
        } else if (iterator.message_type == protocol::OrderBookStateMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderBookStateMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->order_book_id.get());
            checksum += bench::digest(message->state_name.get());
        } else if (iterator.message_type == protocol::AddOrderNoMpid::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddOrderNoMpid::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->order_book_id.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->order_book_position.get());
            checksum += bench::digest(message->quantity.get());
            checksum += bench::digest(message->price.get());
            checksum += bench::digest(message->order_attributes.Force());
            checksum += bench::digest(message->order_attributes.ShortSell());
            checksum += bench::digest(message->order_attributes.MarketBid());
            checksum += bench::digest(message->order_attributes.PriceStabilization());
            checksum += bench::digest(message->order_attributes.OverrideCrossing());
            checksum += bench::digest(message->order_attributes.Undisclosed());
            checksum += bench::digest(message->lot_type.get());
        } else if (iterator.message_type == protocol::AddOrderWithMpid::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddOrderWithMpid::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->order_book_id.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->order_book_position.get());
            checksum += bench::digest(message->quantity.get());
            checksum += bench::digest(message->price.get());
            checksum += bench::digest(message->order_attributes.Force());
            checksum += bench::digest(message->order_attributes.ShortSell());
            checksum += bench::digest(message->order_attributes.MarketBid());
            checksum += bench::digest(message->order_attributes.PriceStabilization());
            checksum += bench::digest(message->order_attributes.OverrideCrossing());
            checksum += bench::digest(message->order_attributes.Undisclosed());
            checksum += bench::digest(message->lot_type.get());
            checksum += bench::digest(message->participant_id.get());
        } else if (iterator.message_type == protocol::OrderExecutedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderExecutedMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->order_book_id.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->executed_quantity.get());
            checksum += bench::digest(message->match_id.get());
            checksum += bench::digest(message->combo_group_id.get());
            checksum += bench::digest(message->participant_id_owner.get());
            checksum += bench::digest(message->participant_id_counterparty.get());
        } else if (iterator.message_type == protocol::OrderExecutedWithPriceMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderExecutedWithPriceMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->order_book_id.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->executed_quantity.get());
            checksum += bench::digest(message->match_id.get());
            checksum += bench::digest(message->combo_group_id.get());
            checksum += bench::digest(message->owner_participant_id.get());
            checksum += bench::digest(message->counterparty_participant_id.get());
            checksum += bench::digest(message->trade_price.get());
            checksum += bench::digest(message->occurred_at_cross.get());
            checksum += bench::digest(message->printable.get());
        } else if (iterator.message_type == protocol::OrderReplaceMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderReplaceMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->order_book_id.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->new_orderbook_position.get());
            checksum += bench::digest(message->quantity.get());
            checksum += bench::digest(message->price.get());
            checksum += bench::digest(message->order_attributes.Force());
            checksum += bench::digest(message->order_attributes.ShortSell());
            checksum += bench::digest(message->order_attributes.MarketBid());
            checksum += bench::digest(message->order_attributes.PriceStabilization());
            checksum += bench::digest(message->order_attributes.OverrideCrossing());
            checksum += bench::digest(message->order_attributes.Undisclosed());
        } else if (iterator.message_type == protocol::OrderDeleteMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderDeleteMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->order_book_id.get());
            checksum += bench::digest(message->side.get());
        } else if (iterator.message_type == protocol::TradeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->match_id.get());
            checksum += bench::digest(message->combo_group_id.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->quantity.get());
            checksum += bench::digest(message->order_book_id.get());
            checksum += bench::digest(message->trade_price.get());
            checksum += bench::digest(message->owner_participant_id.get());
            checksum += bench::digest(message->counterparty_participant_id.get());
            checksum += bench::digest(message->printable.get());
            checksum += bench::digest(message->occurred_at_cross.get());
        } else if (iterator.message_type == protocol::EquilibriumPriceUpdate::message_type) {
            [[maybe_unused]] const auto* message = protocol::EquilibriumPriceUpdate::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->order_book_id.get());
            checksum += bench::digest(message->available_bid_quantity_at_equilibrium_price.get());
            checksum += bench::digest(message->available_ask_quantity_at_equilibrium_price.get());
            checksum += bench::digest(message->equilibrium_price.get());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Jpx.OseDerivatives.GeniumInet.Itch.v5.0.6", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
