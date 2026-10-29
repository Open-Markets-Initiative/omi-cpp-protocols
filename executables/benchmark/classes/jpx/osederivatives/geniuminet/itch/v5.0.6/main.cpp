// Jpx.OseDerivatives.GeniumInet.Itch.v5.0.6 benchmark, through the Classes Packet: every value it reads from every message of the simulated
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
#include "cpp/binary/classes/jpx/osederivatives/geniuminet/itch/v5.0.6/definitions.hpp"

namespace protocol = ::jpx::osederivatives::geniuminet::itch::v5_0_6;

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

    checksum += bench::digest(packet.packet_header().session());
    checksum += bench::digest(packet.packet_header().sequence_number());
    checksum += bench::digest(packet.packet_header().message_count());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.message_header().message_length());
        checksum += bench::digest(each.message_header().message_type());

        if (const auto* message = dynamic_cast<const protocol::SecondsMessage*>(each.message())) {
            checksum += bench::digest((*message).seconds());
        } else if (const auto* message = dynamic_cast<const protocol::OrderBookDirectory*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).order_book_id());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).long_name());
            checksum += bench::digest((*message).isin());
            checksum += bench::digest((*message).financial_product());
            checksum += bench::digest((*message).trading_currency());
            checksum += bench::digest((*message).decimals_in_price());
            checksum += bench::digest((*message).decimals_in_nominal_value());
            checksum += bench::digest((*message).odd_lot_size());
            checksum += bench::digest((*message).round_lot_size());
            checksum += bench::digest((*message).block_lot_size());
            checksum += bench::digest((*message).nominal_value());
            checksum += bench::digest((*message).number_of_legs());
            checksum += bench::digest((*message).underlying_orderbook_id());
            checksum += bench::digest((*message).strike_price());
            checksum += bench::digest((*message).expiration_date());
            checksum += bench::digest((*message).decimals_in_strike_price());
            checksum += bench::digest((*message).put_or_call());
        } else if (const auto* message = dynamic_cast<const protocol::CombinationOrderbookLeg*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).combination_orderbook_id());
            checksum += bench::digest((*message).leg_orderbook_id());
            checksum += bench::digest((*message).leg_side());
            checksum += bench::digest((*message).leg_ratio());
        } else if (const auto* message = dynamic_cast<const protocol::TickSizeTableEntry*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).order_book_id());
            checksum += bench::digest((*message).tick_size());
            checksum += bench::digest((*message).price_from());
            checksum += bench::digest((*message).price_to());
        } else if (const auto* message = dynamic_cast<const protocol::SystemEventMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).event_code());
        } else if (const auto* message = dynamic_cast<const protocol::OrderBookStateMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).order_book_id());
            checksum += bench::digest((*message).state_name());
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderNoMpid*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).order_book_id());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).order_book_position());
            checksum += bench::digest((*message).quantity());
            checksum += bench::digest((*message).price());
            checksum += bench::digest((*message).order_attributes().force());
            checksum += bench::digest((*message).order_attributes().short_sell());
            checksum += bench::digest((*message).order_attributes().market_bid());
            checksum += bench::digest((*message).order_attributes().price_stabilization());
            checksum += bench::digest((*message).order_attributes().override_crossing());
            checksum += bench::digest((*message).order_attributes().undisclosed());
            checksum += bench::digest((*message).lot_type());
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderWithMpid*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).order_book_id());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).order_book_position());
            checksum += bench::digest((*message).quantity());
            checksum += bench::digest((*message).price());
            checksum += bench::digest((*message).order_attributes().force());
            checksum += bench::digest((*message).order_attributes().short_sell());
            checksum += bench::digest((*message).order_attributes().market_bid());
            checksum += bench::digest((*message).order_attributes().price_stabilization());
            checksum += bench::digest((*message).order_attributes().override_crossing());
            checksum += bench::digest((*message).order_attributes().undisclosed());
            checksum += bench::digest((*message).lot_type());
            checksum += bench::digest((*message).participant_id());
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).order_book_id());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).executed_quantity());
            checksum += bench::digest((*message).match_id());
            checksum += bench::digest((*message).combo_group_id());
            checksum += bench::digest((*message).participant_id_owner());
            checksum += bench::digest((*message).participant_id_counterparty());
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedWithPriceMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).order_book_id());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).executed_quantity());
            checksum += bench::digest((*message).match_id());
            checksum += bench::digest((*message).combo_group_id());
            checksum += bench::digest((*message).owner_participant_id());
            checksum += bench::digest((*message).counterparty_participant_id());
            checksum += bench::digest((*message).trade_price());
            checksum += bench::digest((*message).occurred_at_cross());
            checksum += bench::digest((*message).printable());
        } else if (const auto* message = dynamic_cast<const protocol::OrderReplaceMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).order_book_id());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).new_orderbook_position());
            checksum += bench::digest((*message).quantity());
            checksum += bench::digest((*message).price());
            checksum += bench::digest((*message).order_attributes().force());
            checksum += bench::digest((*message).order_attributes().short_sell());
            checksum += bench::digest((*message).order_attributes().market_bid());
            checksum += bench::digest((*message).order_attributes().price_stabilization());
            checksum += bench::digest((*message).order_attributes().override_crossing());
            checksum += bench::digest((*message).order_attributes().undisclosed());
        } else if (const auto* message = dynamic_cast<const protocol::OrderDeleteMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).order_book_id());
            checksum += bench::digest((*message).side());
        } else if (const auto* message = dynamic_cast<const protocol::TradeMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).match_id());
            checksum += bench::digest((*message).combo_group_id());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).quantity());
            checksum += bench::digest((*message).order_book_id());
            checksum += bench::digest((*message).trade_price());
            checksum += bench::digest((*message).owner_participant_id());
            checksum += bench::digest((*message).counterparty_participant_id());
            checksum += bench::digest((*message).printable());
            checksum += bench::digest((*message).occurred_at_cross());
        } else if (const auto* message = dynamic_cast<const protocol::EquilibriumPriceUpdate*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).order_book_id());
            checksum += bench::digest((*message).available_bid_quantity_at_equilibrium_price());
            checksum += bench::digest((*message).available_ask_quantity_at_equilibrium_price());
            checksum += bench::digest((*message).equilibrium_price());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Jpx.OseDerivatives.GeniumInet.Itch.v5.0.6", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
