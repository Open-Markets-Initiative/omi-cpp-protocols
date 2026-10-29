// Nasdaq.NsmEquities.TotalView.Itch.v4.0 benchmark, through the Advanced session layer: every value it reads from every message of the simulated
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
#include "cpp/binary/advanced/nasdaq/nsmequities/totalview/itch/v4.0/messages/session.hpp"

namespace protocol = ::nasdaq::nsmequities::totalview::itch::v4_0;

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

    void on_message(const protocol::timestamp_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.second.get().value());
    }

    void on_message(const protocol::system_event_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.event_code.get().value());
    }

    void on_message(const protocol::stock_directory_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.stock.get().value());
        checksum += bench::digest(message.fields.market_category.get().value());
        checksum += bench::digest(message.fields.financial_status_indicator.get().value());
        checksum += bench::digest(message.fields.round_lot_size.get().value());
        checksum += bench::digest(message.fields.round_lots_only.get().value());
    }

    void on_message(const protocol::stock_trading_action_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.stock.get().value());
        checksum += bench::digest(message.fields.trading_state.get().value());
        checksum += bench::digest(message.fields.reserved.get().value());
        checksum += bench::digest(message.fields.reason.get().value());
    }

    void on_message(const protocol::market_participant_position_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.mpid.get().value());
        checksum += bench::digest(message.fields.stock.get().value());
        checksum += bench::digest(message.fields.primary_market_maker.get().value());
        checksum += bench::digest(message.fields.market_maker_mode.get().value());
        checksum += bench::digest(message.fields.market_participant_state.get().value());
    }

    void on_message(const protocol::add_order_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.order_reference_number.get().value());
        checksum += bench::digest(message.fields.side.get().value());
        checksum += bench::digest(message.fields.shares.get().value());
        checksum += bench::digest(message.fields.stock.get().value());
        checksum += bench::digest(message.fields.price.get().value());
    }

    void on_message(const protocol::add_order_with_mpid_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.order_reference_number.get().value());
        checksum += bench::digest(message.fields.side.get().value());
        checksum += bench::digest(message.fields.shares.get().value());
        checksum += bench::digest(message.fields.stock.get().value());
        checksum += bench::digest(message.fields.price.get().value());
        checksum += bench::digest(message.fields.attribution.get().value());
    }

    void on_message(const protocol::order_executed_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.order_reference_number.get().value());
        checksum += bench::digest(message.fields.executed_shares.get().value());
        checksum += bench::digest(message.fields.match_number.get().value());
    }

    void on_message(const protocol::order_executed_with_price_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.order_reference_number.get().value());
        checksum += bench::digest(message.fields.executed_shares.get().value());
        checksum += bench::digest(message.fields.match_number.get().value());
        checksum += bench::digest(message.fields.printable.get().value());
        checksum += bench::digest(message.fields.execution_price.get().value());
    }

    void on_message(const protocol::order_cancel_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.order_reference_number.get().value());
        checksum += bench::digest(message.fields.canceled_shares.get().value());
    }

    void on_message(const protocol::order_delete_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.order_reference_number.get().value());
    }

    void on_message(const protocol::order_replace_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.original_order_reference_number.get().value());
        checksum += bench::digest(message.fields.new_order_reference_number.get().value());
        checksum += bench::digest(message.fields.shares.get().value());
        checksum += bench::digest(message.fields.price.get().value());
    }

    void on_message(const protocol::trade_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.order_reference_number.get().value());
        checksum += bench::digest(message.fields.side.get().value());
        checksum += bench::digest(message.fields.shares.get().value());
        checksum += bench::digest(message.fields.stock.get().value());
        checksum += bench::digest(message.fields.price.get().value());
        checksum += bench::digest(message.fields.match_number.get().value());
    }

    void on_message(const protocol::cross_trade_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.cross_shares.get().value());
        checksum += bench::digest(message.fields.stock.get().value());
        checksum += bench::digest(message.fields.cross_price.get().value());
        checksum += bench::digest(message.fields.match_number.get().value());
        checksum += bench::digest(message.fields.cross_type.get().value());
    }

    void on_message(const protocol::broken_trade_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.match_number.get().value());
    }

    void on_message(const protocol::net_order_imbalance_indicator_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.paired_shares.get().value());
        checksum += bench::digest(message.fields.imbalance_shares.get().value());
        checksum += bench::digest(message.fields.imbalance_direction.get().value());
        checksum += bench::digest(message.fields.stock.get().value());
        checksum += bench::digest(message.fields.far_price.get().value());
        checksum += bench::digest(message.fields.near_price.get().value());
        checksum += bench::digest(message.fields.current_reference_price.get().value());
        checksum += bench::digest(message.fields.cross_type.get().value());
        checksum += bench::digest(message.fields.price_variation_indicator.get().value());
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
    return bench::run("Nasdaq.NsmEquities.TotalView.Itch.v4.0", "advanced", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
