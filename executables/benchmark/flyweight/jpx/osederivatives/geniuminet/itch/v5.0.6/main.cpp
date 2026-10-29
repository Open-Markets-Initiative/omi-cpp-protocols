// Jpx.OseDerivatives.GeniumInet.Itch.v5.0.6 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/jpx/osederivatives/geniuminet/itch/v5.0.6.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <span>
#include <string>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "executables/benchmark/Benchmark.hpp"
#include "cpp/binary/flyweight/jpx/osederivatives/geniuminet/itch/v5.0.6/definitions.hpp"

namespace protocol = ::jpx::osederivatives::geniuminet::itch::v5_0_6;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        checksum += bench::digest(packet.packet_header().session());
        checksum += bench::digest(packet.packet_header().sequence_number());
        checksum += bench::digest(packet.packet_header().message_count());
    }

    // a message this test prints no values of, or a code no message answers to, still takes its entry
    template <typename Message>
    void on(const Message&) {
        ++index;
    }

    template <typename Code>
    void on_unknown(Code, std::span<const std::byte>) {
        ++index;
    }

    void on(const protocol::SecondsMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.seconds());
    }

    void on(const protocol::OrderBookDirectory& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.order_book_id());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.long_name());
        checksum += bench::digest(message.isin());
        checksum += bench::digest(message.financial_product());
        checksum += bench::digest(message.trading_currency());
        checksum += bench::digest(message.decimals_in_price());
        checksum += bench::digest(message.decimals_in_nominal_value());
        checksum += bench::digest(message.odd_lot_size());
        checksum += bench::digest(message.round_lot_size());
        checksum += bench::digest(message.block_lot_size());
        checksum += bench::digest(message.nominal_value());
        checksum += bench::digest(message.number_of_legs());
        checksum += bench::digest(message.underlying_orderbook_id());
        checksum += bench::digest(message.strike_price());
        checksum += bench::digest(message.expiration_date());
        checksum += bench::digest(message.decimals_in_strike_price());
        checksum += bench::digest(message.put_or_call());
    }

    void on(const protocol::CombinationOrderbookLeg& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.combination_orderbook_id());
        checksum += bench::digest(message.leg_orderbook_id());
        checksum += bench::digest(message.leg_side());
        checksum += bench::digest(message.leg_ratio());
    }

    void on(const protocol::TickSizeTableEntry& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.order_book_id());
        checksum += bench::digest(message.tick_size());
        checksum += bench::digest(message.price_from());
        checksum += bench::digest(message.price_to());
    }

    void on(const protocol::SystemEventMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.event_code());
    }

    void on(const protocol::OrderBookStateMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.order_book_id());
        checksum += bench::digest(message.state_name());
    }

    void on(const protocol::AddOrderNoMpid& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.order_book_id());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.order_book_position());
        checksum += bench::digest(message.quantity());
        checksum += bench::digest(message.price());
        checksum += bench::digest(message.order_attributes().force());
        checksum += bench::digest(message.order_attributes().short_sell());
        checksum += bench::digest(message.order_attributes().market_bid());
        checksum += bench::digest(message.order_attributes().price_stabilization());
        checksum += bench::digest(message.order_attributes().override_crossing());
        checksum += bench::digest(message.order_attributes().undisclosed());
        checksum += bench::digest(message.lot_type());
    }

    void on(const protocol::AddOrderWithMpid& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.order_book_id());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.order_book_position());
        checksum += bench::digest(message.quantity());
        checksum += bench::digest(message.price());
        checksum += bench::digest(message.order_attributes().force());
        checksum += bench::digest(message.order_attributes().short_sell());
        checksum += bench::digest(message.order_attributes().market_bid());
        checksum += bench::digest(message.order_attributes().price_stabilization());
        checksum += bench::digest(message.order_attributes().override_crossing());
        checksum += bench::digest(message.order_attributes().undisclosed());
        checksum += bench::digest(message.lot_type());
        checksum += bench::digest(message.participant_id());
    }

    void on(const protocol::OrderExecutedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.order_book_id());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.executed_quantity());
        checksum += bench::digest(message.match_id());
        checksum += bench::digest(message.combo_group_id());
        checksum += bench::digest(message.participant_id_owner());
        checksum += bench::digest(message.participant_id_counterparty());
    }

    void on(const protocol::OrderExecutedWithPriceMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.order_book_id());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.executed_quantity());
        checksum += bench::digest(message.match_id());
        checksum += bench::digest(message.combo_group_id());
        checksum += bench::digest(message.owner_participant_id());
        checksum += bench::digest(message.counterparty_participant_id());
        checksum += bench::digest(message.trade_price());
        checksum += bench::digest(message.occurred_at_cross());
        checksum += bench::digest(message.printable());
    }

    void on(const protocol::OrderReplaceMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.order_book_id());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.new_orderbook_position());
        checksum += bench::digest(message.quantity());
        checksum += bench::digest(message.price());
        checksum += bench::digest(message.order_attributes().force());
        checksum += bench::digest(message.order_attributes().short_sell());
        checksum += bench::digest(message.order_attributes().market_bid());
        checksum += bench::digest(message.order_attributes().price_stabilization());
        checksum += bench::digest(message.order_attributes().override_crossing());
        checksum += bench::digest(message.order_attributes().undisclosed());
    }

    void on(const protocol::OrderDeleteMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.order_book_id());
        checksum += bench::digest(message.side());
    }

    void on(const protocol::TradeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.match_id());
        checksum += bench::digest(message.combo_group_id());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.quantity());
        checksum += bench::digest(message.order_book_id());
        checksum += bench::digest(message.trade_price());
        checksum += bench::digest(message.owner_participant_id());
        checksum += bench::digest(message.counterparty_participant_id());
        checksum += bench::digest(message.printable());
        checksum += bench::digest(message.occurred_at_cross());
    }

    void on(const protocol::EquilibriumPriceUpdate& message) {
        checksum += index++;
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.order_book_id());
        checksum += bench::digest(message.available_bid_quantity_at_equilibrium_price());
        checksum += bench::digest(message.available_ask_quantity_at_equilibrium_price());
        checksum += bench::digest(message.equilibrium_price());
    }
};

// The values the Flyweight reader reads from one datagram, folded into a checksum. A datagram it cannot
// read is a value the model never reads, so the benchmark refuses to time it.
std::uint64_t read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::PacketReader::read(std::span<const std::byte>(frame.payload, frame.payload_len), reader);
    } catch (const protocol::DecodeError& error) {
        throw;
    }

    return reader.checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Jpx.OseDerivatives.GeniumInet.Itch.v5.0.6", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
