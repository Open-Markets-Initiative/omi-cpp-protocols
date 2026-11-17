// Cboe.CfeFutures.MulticastDepthOfBook.Pitch.v1.2.22: main.cpp
// Cboe.CfeFutures.MulticastDepthOfBook.Pitch.v1.2.22 benchmark, through the Advanced session layer: every value it reads from every message of the simulated
// sequence (tests/simulated/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/advanced/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/messages/session.hpp"

namespace protocol = ::cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22;

namespace {

// The handler the session layer hands each datagram's values to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    protocol::seq_action on_transport_header(const protocol::packet_header& header, const packet::Frame&) {
        checksum += bench::digest(header.length.get().value());
        checksum += bench::digest(header.message_count.get().value());
        checksum += bench::digest(header.unit.get().value());
        checksum += bench::digest(header.sequence.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::packet_header&) {
        ++index;
    }

    void on_message(const protocol::time_reference_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.midnight_reference.get().value());
        checksum += bench::digest(message.fields.time_reference.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
    }

    void on_message(const protocol::time_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_reference.get().value());
        checksum += bench::digest(message.fields.epoch_time.get().value());
    }

    void on_message(const protocol::unit_clear_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
    }

    void on_message(const protocol::futures_instrument_definition_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.unit_timestamp.get().value());
        checksum += bench::digest(message.fields.report_symbol.get().value());
        checksum += bench::digest(message.fields.futures_flags.has_variance());
        checksum += bench::digest(message.fields.expiration_date.get().value());
        checksum += bench::digest(message.fields.contract_size.get().value());
        checksum += bench::digest(message.fields.listing_state.get().value());
        checksum += bench::digest(message.fields.price_increment.get().value());
        checksum += bench::digest(message.fields.leg_count.get().value());
        checksum += bench::digest(message.fields.leg_offset.get().value());
        checksum += bench::digest(message.fields.reserved_1.get().value());
        checksum += bench::digest(message.fields.contract_date.get().value());
    }

    void on_message(const protocol::futures_variance_symbol_mapping_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.unit_timestamp.get().value());
        checksum += bench::digest(message.fields.feed_symbol.get().value());
        checksum += bench::digest(message.fields.futures_symbol.get().value());
        checksum += bench::digest(message.fields.accrued_day_variance.get().value());
        checksum += bench::digest(message.fields.num_final_returns.get().value());
        checksum += bench::digest(message.fields.num_elapsed_returns.get().value());
    }

    void on_message(const protocol::price_limits_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.upper_price_limit.get().value());
        checksum += bench::digest(message.fields.lower_price_limit.get().value());
    }

    void on_message(const protocol::add_order_long_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.side_indicator.get().value());
        checksum += bench::digest(message.fields.quantity_long.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.price_long.get().value());
    }

    void on_message(const protocol::add_order_short_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.side_indicator.get().value());
        checksum += bench::digest(message.fields.quantity_short.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.price_short.get().value());
    }

    void on_message(const protocol::order_executed_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.executed_quantity.get().value());
        checksum += bench::digest(message.fields.execution_id.get().value());
        checksum += bench::digest(message.fields.trade_condition.get().value());
    }

    void on_message(const protocol::reduce_size_long_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.canceled_quantity_long.get().value());
    }

    void on_message(const protocol::reduce_size_short_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.canceled_quantity_short.get().value());
    }

    void on_message(const protocol::modify_order_long_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.quantity_long.get().value());
        checksum += bench::digest(message.fields.price_long.get().value());
    }

    void on_message(const protocol::modify_order_short_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.quantity_short.get().value());
        checksum += bench::digest(message.fields.price_short.get().value());
    }

    void on_message(const protocol::delete_order_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
    }

    void on_message(const protocol::trade_long_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.side_indicator.get().value());
        checksum += bench::digest(message.fields.quantity_long.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.price_long.get().value());
        checksum += bench::digest(message.fields.execution_id.get().value());
        checksum += bench::digest(message.fields.trade_condition.get().value());
    }

    void on_message(const protocol::trade_short_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.side_indicator.get().value());
        checksum += bench::digest(message.fields.quantity_short.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.price_short.get().value());
        checksum += bench::digest(message.fields.execution_id.get().value());
        checksum += bench::digest(message.fields.trade_condition.get().value());
    }

    void on_message(const protocol::transaction_begin_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
    }

    void on_message(const protocol::transaction_end_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
    }

    void on_message(const protocol::trade_break_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.execution_id.get().value());
    }

    void on_message(const protocol::settlement_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.settlement_price.get().value());
        checksum += bench::digest(message.fields.issue.get().value());
    }

    void on_message(const protocol::open_interest_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.open_interest.get().value());
    }

    void on_message(const protocol::end_of_day_summary_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.open_interest.get().value());
        checksum += bench::digest(message.fields.high_price.get().value());
        checksum += bench::digest(message.fields.low_price.get().value());
        checksum += bench::digest(message.fields.open_price.get().value());
        checksum += bench::digest(message.fields.close_price.get().value());
        checksum += bench::digest(message.fields.total_volume.get().value());
        checksum += bench::digest(message.fields.block_volume.get().value());
        checksum += bench::digest(message.fields.ecrp_volume.get().value());
        checksum += bench::digest(message.fields.summary_flags.has_high_price_valid());
        checksum += bench::digest(message.fields.summary_flags.has_high_price_is_bid());
        checksum += bench::digest(message.fields.summary_flags.has_low_price_valid());
        checksum += bench::digest(message.fields.summary_flags.has_low_price_is_offer());
        checksum += bench::digest(message.fields.summary_flags.has_open_close_valid());
    }

    void on_message(const protocol::trading_status_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.reserved_2.get().value());
        checksum += bench::digest(message.fields.trading_status.get().value());
        checksum += bench::digest(message.fields.reserved_3.get().value());
    }

    void on_message(const protocol::end_of_session_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
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
    return bench::run("Cboe.CfeFutures.MulticastDepthOfBook.Pitch.v1.2.22", "advanced", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
