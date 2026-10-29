// Jpx.OseDerivatives.GeniumInet.Itch.v5.0.6 benchmark, through the Advanced session layer: every value it reads from every message of the simulated
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
#include "cpp/binary/advanced/jpx/osederivatives/geniuminet/itch/v5.0.6/messages/session.hpp"

namespace protocol = ::jpx::osederivatives::geniuminet::itch::v5_0_6;

namespace {

// The handler the session layer hands each datagram's values to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    protocol::seq_action on_transport_header(const protocol::packet_header& header, const packet::Frame&) {
        checksum += bench::digest(header.session.get().value());
        checksum += bench::digest(header.sequence_number.get().value());
        checksum += bench::digest(header.message_count.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::packet_header&) {
        ++index;
    }

    void on_message(const protocol::seconds_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.seconds.get().value());
    }

    void on_message(const protocol::order_book_directory& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.order_book_id.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.long_name.get().value());
        checksum += bench::digest(message.fields.isin.get().value());
        checksum += bench::digest(message.fields.financial_product.get().value());
        checksum += bench::digest(message.fields.trading_currency.get().value());
        checksum += bench::digest(message.fields.decimals_in_price.get().value());
        checksum += bench::digest(message.fields.decimals_in_nominal_value.get().value());
        checksum += bench::digest(message.fields.odd_lot_size.get().value());
        checksum += bench::digest(message.fields.round_lot_size.get().value());
        checksum += bench::digest(message.fields.block_lot_size.get().value());
        checksum += bench::digest(message.fields.nominal_value.get().value());
        checksum += bench::digest(message.fields.number_of_legs.get().value());
        checksum += bench::digest(message.fields.underlying_orderbook_id.get().value());
        checksum += bench::digest(message.fields.strike_price.get().value());
        checksum += bench::digest(message.fields.expiration_date.get().value());
        checksum += bench::digest(message.fields.decimals_in_strike_price.get().value());
        checksum += bench::digest(message.fields.put_or_call.get().value());
    }

    void on_message(const protocol::combination_orderbook_leg& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.combination_orderbook_id.get().value());
        checksum += bench::digest(message.fields.leg_orderbook_id.get().value());
        checksum += bench::digest(message.fields.leg_side.get().value());
        checksum += bench::digest(message.fields.leg_ratio.get().value());
    }

    void on_message(const protocol::tick_size_table_entry& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.order_book_id.get().value());
        checksum += bench::digest(message.fields.tick_size.get().value());
        checksum += bench::digest(message.fields.price_from.get().value());
        checksum += bench::digest(message.fields.price_to.get().value());
    }

    void on_message(const protocol::system_event_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.event_code.get().value());
    }

    void on_message(const protocol::order_book_state_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.order_book_id.get().value());
        checksum += bench::digest(message.fields.state_name.get().value());
    }

    void on_message(const protocol::add_order_no_mpid& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.order_book_id.get().value());
        checksum += bench::digest(message.fields.side.get().value());
        checksum += bench::digest(message.fields.order_book_position.get().value());
        checksum += bench::digest(message.fields.quantity.get().value());
        checksum += bench::digest(message.fields.price.get().value());
        checksum += bench::digest(message.fields.order_attributes.has_force());
        checksum += bench::digest(message.fields.order_attributes.has_short_sell());
        checksum += bench::digest(message.fields.order_attributes.has_market_bid());
        checksum += bench::digest(message.fields.order_attributes.has_price_stabilization());
        checksum += bench::digest(message.fields.order_attributes.has_override_crossing());
        checksum += bench::digest(message.fields.order_attributes.has_undisclosed());
        checksum += bench::digest(message.fields.lot_type.get().value());
    }

    void on_message(const protocol::add_order_with_mpid& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.order_book_id.get().value());
        checksum += bench::digest(message.fields.side.get().value());
        checksum += bench::digest(message.fields.order_book_position.get().value());
        checksum += bench::digest(message.fields.quantity.get().value());
        checksum += bench::digest(message.fields.price.get().value());
        checksum += bench::digest(message.fields.order_attributes.has_force());
        checksum += bench::digest(message.fields.order_attributes.has_short_sell());
        checksum += bench::digest(message.fields.order_attributes.has_market_bid());
        checksum += bench::digest(message.fields.order_attributes.has_price_stabilization());
        checksum += bench::digest(message.fields.order_attributes.has_override_crossing());
        checksum += bench::digest(message.fields.order_attributes.has_undisclosed());
        checksum += bench::digest(message.fields.lot_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
    }

    void on_message(const protocol::order_executed_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.order_book_id.get().value());
        checksum += bench::digest(message.fields.side.get().value());
        checksum += bench::digest(message.fields.executed_quantity.get().value());
        checksum += bench::digest(message.fields.match_id.get().value());
        checksum += bench::digest(message.fields.combo_group_id.get().value());
        checksum += bench::digest(message.fields.participant_id_owner.get().value());
        checksum += bench::digest(message.fields.participant_id_counterparty.get().value());
    }

    void on_message(const protocol::order_executed_with_price_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.order_book_id.get().value());
        checksum += bench::digest(message.fields.side.get().value());
        checksum += bench::digest(message.fields.executed_quantity.get().value());
        checksum += bench::digest(message.fields.match_id.get().value());
        checksum += bench::digest(message.fields.combo_group_id.get().value());
        checksum += bench::digest(message.fields.owner_participant_id.get().value());
        checksum += bench::digest(message.fields.counterparty_participant_id.get().value());
        checksum += bench::digest(message.fields.trade_price.get().value());
        checksum += bench::digest(message.fields.occurred_at_cross.get().value());
        checksum += bench::digest(message.fields.printable.get().value());
    }

    void on_message(const protocol::order_replace_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.order_book_id.get().value());
        checksum += bench::digest(message.fields.side.get().value());
        checksum += bench::digest(message.fields.new_orderbook_position.get().value());
        checksum += bench::digest(message.fields.quantity.get().value());
        checksum += bench::digest(message.fields.price.get().value());
        checksum += bench::digest(message.fields.order_attributes.has_force());
        checksum += bench::digest(message.fields.order_attributes.has_short_sell());
        checksum += bench::digest(message.fields.order_attributes.has_market_bid());
        checksum += bench::digest(message.fields.order_attributes.has_price_stabilization());
        checksum += bench::digest(message.fields.order_attributes.has_override_crossing());
        checksum += bench::digest(message.fields.order_attributes.has_undisclosed());
    }

    void on_message(const protocol::order_delete_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.order_book_id.get().value());
        checksum += bench::digest(message.fields.side.get().value());
    }

    void on_message(const protocol::trade_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.match_id.get().value());
        checksum += bench::digest(message.fields.combo_group_id.get().value());
        checksum += bench::digest(message.fields.side.get().value());
        checksum += bench::digest(message.fields.quantity.get().value());
        checksum += bench::digest(message.fields.order_book_id.get().value());
        checksum += bench::digest(message.fields.trade_price.get().value());
        checksum += bench::digest(message.fields.owner_participant_id.get().value());
        checksum += bench::digest(message.fields.counterparty_participant_id.get().value());
        checksum += bench::digest(message.fields.printable.get().value());
        checksum += bench::digest(message.fields.occurred_at_cross.get().value());
    }

    void on_message(const protocol::equilibrium_price_update& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.order_book_id.get().value());
        checksum += bench::digest(message.fields.available_bid_quantity_at_equilibrium_price.get().value());
        checksum += bench::digest(message.fields.available_ask_quantity_at_equilibrium_price.get().value());
        checksum += bench::digest(message.fields.equilibrium_price.get().value());
    }
};

// The values Advanced reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    Reader reader;
    protocol::process_segment(reader, frame.payload, frame.payload_len, 0, frame);
    return reader.checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Jpx.OseDerivatives.GeniumInet.Itch.v5.0.6", "advanced", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
