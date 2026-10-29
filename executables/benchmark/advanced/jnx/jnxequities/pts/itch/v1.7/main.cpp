// Jnx.JnxEquities.Pts.Itch.v1.7 benchmark, through the Advanced session layer: every value it reads from every message of the simulated
// sequence (tests/simulated/jnx/jnxequities/pts/itch/v1.7.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/advanced/jnx/jnxequities/pts/itch/v1.7/messages/session.hpp"

namespace protocol = ::jnx::jnxequities::pts::itch::v1_7;

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

    void on_message(const protocol::system_event_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.group.get().value());
        checksum += bench::digest(message.fields.system_event.get().value());
    }

    void on_message(const protocol::price_tick_size_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.price_tick_size_table_id.get().value());
        checksum += bench::digest(message.fields.price_tick_size.get().value());
        checksum += bench::digest(message.fields.price_start.get().value());
    }

    void on_message(const protocol::orderbook_directory_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.orderbook_id.get().value());
        checksum += bench::digest(message.fields.orderbook_code.get().value());
        checksum += bench::digest(message.fields.group.get().value());
        checksum += bench::digest(message.fields.round_lot_size.get().value());
        checksum += bench::digest(message.fields.price_tick_size_table_id.get().value());
        checksum += bench::digest(message.fields.price_decimals.get().value());
        checksum += bench::digest(message.fields.upper_price_limit.get().value());
        checksum += bench::digest(message.fields.lower_price_limit.get().value());
    }

    void on_message(const protocol::trading_state_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.orderbook_id.get().value());
        checksum += bench::digest(message.fields.group.get().value());
        checksum += bench::digest(message.fields.trading_state.get().value());
    }

    void on_message(const protocol::short_selling_price_restriction_state_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.orderbook_id.get().value());
        checksum += bench::digest(message.fields.group.get().value());
        checksum += bench::digest(message.fields.short_selling_state.get().value());
    }

    void on_message(const protocol::order_added_without_attributes_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.order_number.get().value());
        checksum += bench::digest(message.fields.buy_sell_indicator.get().value());
        checksum += bench::digest(message.fields.quantity.get().value());
        checksum += bench::digest(message.fields.orderbook_id.get().value());
        checksum += bench::digest(message.fields.group.get().value());
        checksum += bench::digest(message.fields.price.get().value());
    }

    void on_message(const protocol::order_added_with_attributes_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.order_number.get().value());
        checksum += bench::digest(message.fields.buy_sell_indicator.get().value());
        checksum += bench::digest(message.fields.quantity.get().value());
        checksum += bench::digest(message.fields.orderbook_id.get().value());
        checksum += bench::digest(message.fields.group.get().value());
        checksum += bench::digest(message.fields.price.get().value());
        checksum += bench::digest(message.fields.attribution.get().value());
        checksum += bench::digest(message.fields.order_type.get().value());
    }

    void on_message(const protocol::order_executed_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.order_number.get().value());
        checksum += bench::digest(message.fields.executed_quantity.get().value());
        checksum += bench::digest(message.fields.match_number.get().value());
    }

    void on_message(const protocol::order_deleted_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.order_number.get().value());
    }

    void on_message(const protocol::order_replaced_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.original_order_number.get().value());
        checksum += bench::digest(message.fields.new_order_number.get().value());
        checksum += bench::digest(message.fields.quantity.get().value());
        checksum += bench::digest(message.fields.price.get().value());
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
    return bench::run("Jnx.JnxEquities.Pts.Itch.v1.7", "advanced", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
