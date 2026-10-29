// Cboe.EdgxOptions.MulticastDepthOfBook.Pitch.v2.41.80 benchmark, through the Advanced session layer: every value it reads from every message of the simulated
// sequence (tests/simulated/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/advanced/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/messages/session.hpp"

namespace protocol = ::cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80;

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

    void on_message(const protocol::time_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time.get().value());
    }

    void on_message(const protocol::unit_clear_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
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
        checksum += bench::digest(message.fields.add_flags.has_aon());
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
        checksum += bench::digest(message.fields.add_flags.has_aon());
    }

    void on_message(const protocol::add_order_expanded_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.side_indicator.get().value());
        checksum += bench::digest(message.fields.quantity_long.get().value());
        checksum += bench::digest(message.fields.expanded_symbol.get().value());
        checksum += bench::digest(message.fields.price_long.get().value());
        checksum += bench::digest(message.fields.add_flags.has_aon());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.customer_indicator.get().value());
        checksum += bench::digest(message.fields.client_id.get().value());
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

    void on_message(const protocol::order_executed_at_price_size_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.executed_quantity.get().value());
        checksum += bench::digest(message.fields.remaining_quantity.get().value());
        checksum += bench::digest(message.fields.execution_id.get().value());
        checksum += bench::digest(message.fields.price_long.get().value());
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
        checksum += bench::digest(message.fields.modify_flags.has_display());
        checksum += bench::digest(message.fields.modify_flags.has_maintain_priority());
    }

    void on_message(const protocol::modify_order_short_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.quantity_short.get().value());
        checksum += bench::digest(message.fields.price_short.get().value());
        checksum += bench::digest(message.fields.modify_flags.has_display());
        checksum += bench::digest(message.fields.modify_flags.has_maintain_priority());
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

    void on_message(const protocol::trade_expanded_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.side_indicator.get().value());
        checksum += bench::digest(message.fields.quantity_long.get().value());
        checksum += bench::digest(message.fields.expanded_symbol.get().value());
        checksum += bench::digest(message.fields.price_long.get().value());
        checksum += bench::digest(message.fields.execution_id.get().value());
        checksum += bench::digest(message.fields.trade_condition.get().value());
    }

    void on_message(const protocol::trade_break_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.execution_id.get().value());
    }

    void on_message(const protocol::end_of_session_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
    }

    void on_message(const protocol::symbol_mapping_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.feed_symbol.get().value());
        checksum += bench::digest(message.fields.osi_symbol.get().value());
        checksum += bench::digest(message.fields.symbol_condition.get().value());
        checksum += bench::digest(message.fields.underlying.get().value());
    }

    void on_message(const protocol::trading_status_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.trading_status.get().value());
        checksum += bench::digest(message.fields.gth_trading_status.get().value());
    }

    void on_message(const protocol::width_update_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.underlying.get().value());
        checksum += bench::digest(message.fields.width_type.get().value());
        checksum += bench::digest(message.fields.multiplier.get().value());
    }

    void on_message(const protocol::options_auction_update_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.expanded_symbol.get().value());
        checksum += bench::digest(message.fields.auction_type.get().value());
        checksum += bench::digest(message.fields.reference_price.get().value());
        checksum += bench::digest(message.fields.buy_contracts.get().value());
        checksum += bench::digest(message.fields.sell_contracts.get().value());
        checksum += bench::digest(message.fields.indicative_price.get().value());
        checksum += bench::digest(message.fields.auction_only_price.get().value());
        checksum += bench::digest(message.fields.opening_condition.get().value());
        checksum += bench::digest(message.fields.composite_market_bid_price.get().value());
        checksum += bench::digest(message.fields.composite_market_offer_price.get().value());
    }

    void on_message(const protocol::auction_summary_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.stock_symbol.get().value());
        checksum += bench::digest(message.fields.auction_type.get().value());
        checksum += bench::digest(message.fields.price_long.get().value());
        checksum += bench::digest(message.fields.shares_contracts.get().value());
    }

    void on_message(const protocol::auction_notification_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.auction_id.get().value());
        checksum += bench::digest(message.fields.auction_type.get().value());
        checksum += bench::digest(message.fields.side.get().value());
        checksum += bench::digest(message.fields.price_long.get().value());
        checksum += bench::digest(message.fields.contracts.get().value());
        checksum += bench::digest(message.fields.customer_indicator.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.auction_end_offset.get().value());
        checksum += bench::digest(message.fields.client_id.get().value());
    }

    void on_message(const protocol::auction_cancel_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.auction_id.get().value());
    }

    void on_message(const protocol::auction_trade_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.auction_id.get().value());
        checksum += bench::digest(message.fields.execution_id.get().value());
        checksum += bench::digest(message.fields.price_long.get().value());
        checksum += bench::digest(message.fields.contracts.get().value());
    }

    void on_message(const protocol::soq_strike_range_update_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.time_offset.get().value());
        checksum += bench::digest(message.fields.soq_identifier.get().value());
        checksum += bench::digest(message.fields.lower_strike_price.get().value());
        checksum += bench::digest(message.fields.upper_strike_price.get().value());
    }

    void on_message(const protocol::constituent_symbol_mapping_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.feed_symbol.get().value());
        checksum += bench::digest(message.fields.osi_symbol.get().value());
        checksum += bench::digest(message.fields.symbol_condition.get().value());
        checksum += bench::digest(message.fields.underlying.get().value());
        checksum += bench::digest(message.fields.soq_identifier.get().value());
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
    return bench::run("Cboe.EdgxOptions.MulticastDepthOfBook.Pitch.v2.41.80", "advanced", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
