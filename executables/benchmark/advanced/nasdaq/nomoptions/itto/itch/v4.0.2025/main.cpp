// Nasdaq.NomOptions.Itto.Itch.v4.0.2025 benchmark, through the Advanced session layer: every value it reads from every message of the simulated
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
#include "cpp/binary/advanced/nasdaq/nomoptions/itto/itch/v4.0.2025/messages/session.hpp"

namespace protocol = ::nasdaq::nomoptions::itto::itch::v4_0_2025;

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

    void on_message(const protocol::system_event_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.event_code.get().value());
    }

    void on_message(const protocol::options_directory_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.option_id.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.expiration_year.get().value());
        checksum += bench::digest(message.fields.expiration_month.get().value());
        checksum += bench::digest(message.fields.expiration_date.get().value());
        checksum += bench::digest(message.fields.explicit_strike_price.get().value());
        checksum += bench::digest(message.fields.option_type.get().value());
        checksum += bench::digest(message.fields.source.get().value());
        checksum += bench::digest(message.fields.underlying_symbol.get().value());
        checksum += bench::digest(message.fields.options_closing_type.get().value());
        checksum += bench::digest(message.fields.tradable.get().value());
        checksum += bench::digest(message.fields.mpv.get().value());
    }

    void on_message(const protocol::trading_action_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.option_id.get().value());
        checksum += bench::digest(message.fields.current_trading_state.get().value());
    }

    void on_message(const protocol::security_open_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.option_id.get().value());
        checksum += bench::digest(message.fields.open_state.get().value());
    }

    void on_message(const protocol::add_order_message_short_message_form& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.order_reference_number.get().value());
        checksum += bench::digest(message.fields.market_side.get().value());
        checksum += bench::digest(message.fields.option_id.get().value());
        checksum += bench::digest(message.fields.price_short.get().value());
        checksum += bench::digest(message.fields.volume_short.get().value());
    }

    void on_message(const protocol::add_order_message_long_form_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.order_reference_number.get().value());
        checksum += bench::digest(message.fields.market_side.get().value());
        checksum += bench::digest(message.fields.option_id.get().value());
        checksum += bench::digest(message.fields.price_long.get().value());
        checksum += bench::digest(message.fields.volume_long.get().value());
    }

    void on_message(const protocol::add_quote_message_short_form_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.bid_reference_number.get().value());
        checksum += bench::digest(message.fields.ask_reference_number.get().value());
        checksum += bench::digest(message.fields.option_id.get().value());
        checksum += bench::digest(message.fields.bid_price_short.get().value());
        checksum += bench::digest(message.fields.bid_size_short.get().value());
        checksum += bench::digest(message.fields.ask_price_short.get().value());
        checksum += bench::digest(message.fields.ask_size_short.get().value());
    }

    void on_message(const protocol::add_quote_message_long_form_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.bid_reference_number.get().value());
        checksum += bench::digest(message.fields.ask_reference_number.get().value());
        checksum += bench::digest(message.fields.option_id.get().value());
        checksum += bench::digest(message.fields.bid.get().value());
        checksum += bench::digest(message.fields.bid_size_long.get().value());
        checksum += bench::digest(message.fields.ask.get().value());
        checksum += bench::digest(message.fields.ask_size_long.get().value());
    }

    void on_message(const protocol::single_side_executed_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.reference_number.get().value());
        checksum += bench::digest(message.fields.executed_contracts.get().value());
        checksum += bench::digest(message.fields.cross_number.get().value());
        checksum += bench::digest(message.fields.match_number.get().value());
    }

    void on_message(const protocol::single_side_executed_with_price_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.reference_number.get().value());
        checksum += bench::digest(message.fields.cross_number.get().value());
        checksum += bench::digest(message.fields.match_number.get().value());
        checksum += bench::digest(message.fields.printable.get().value());
        checksum += bench::digest(message.fields.price_long.get().value());
        checksum += bench::digest(message.fields.volume_long.get().value());
    }

    void on_message(const protocol::order_cancel_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.order_reference_number.get().value());
        checksum += bench::digest(message.fields.cancelled_contracts.get().value());
    }

    void on_message(const protocol::single_side_replace_message_short_form& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.original_reference_number.get().value());
        checksum += bench::digest(message.fields.new_reference_number.get().value());
        checksum += bench::digest(message.fields.price_short.get().value());
        checksum += bench::digest(message.fields.volume_short.get().value());
    }

    void on_message(const protocol::single_side_replace_message_long_form& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.original_reference_number.get().value());
        checksum += bench::digest(message.fields.new_reference_number.get().value());
        checksum += bench::digest(message.fields.price_long.get().value());
        checksum += bench::digest(message.fields.volume_long.get().value());
    }

    void on_message(const protocol::single_side_delete_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.reference_number.get().value());
    }

    void on_message(const protocol::single_side_change_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.reference_number.get().value());
        checksum += bench::digest(message.fields.change_reason.get().value());
        checksum += bench::digest(message.fields.price_long.get().value());
        checksum += bench::digest(message.fields.volume_long.get().value());
    }

    void on_message(const protocol::quote_replace_message_short_form& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.original_bid_reference_number.get().value());
        checksum += bench::digest(message.fields.bid_reference_number.get().value());
        checksum += bench::digest(message.fields.original_ask_reference_number.get().value());
        checksum += bench::digest(message.fields.ask_reference_number.get().value());
        checksum += bench::digest(message.fields.bid_price_short.get().value());
        checksum += bench::digest(message.fields.bid_size_short.get().value());
        checksum += bench::digest(message.fields.ask_price_short.get().value());
        checksum += bench::digest(message.fields.ask_size_short.get().value());
    }

    void on_message(const protocol::quote_replace_message_long_form& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.original_bid_reference_number.get().value());
        checksum += bench::digest(message.fields.bid_reference_number.get().value());
        checksum += bench::digest(message.fields.original_ask_reference_number.get().value());
        checksum += bench::digest(message.fields.ask_reference_number.get().value());
        checksum += bench::digest(message.fields.bid_price_long.get().value());
        checksum += bench::digest(message.fields.bid_size_long.get().value());
        checksum += bench::digest(message.fields.ask_price_long.get().value());
        checksum += bench::digest(message.fields.ask_size_long.get().value());
    }

    void on_message(const protocol::quote_delete_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.bid_reference_number.get().value());
        checksum += bench::digest(message.fields.ask_reference_number.get().value());
    }

    void on_message(const protocol::options_trade_messages_non_auction& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.buy_sell_indicator.get().value());
        checksum += bench::digest(message.fields.option_id.get().value());
        checksum += bench::digest(message.fields.cross_number.get().value());
        checksum += bench::digest(message.fields.match_number.get().value());
        checksum += bench::digest(message.fields.price_long.get().value());
        checksum += bench::digest(message.fields.volume_long.get().value());
    }

    void on_message(const protocol::options_cross_trade_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.option_id.get().value());
        checksum += bench::digest(message.fields.cross_number.get().value());
        checksum += bench::digest(message.fields.match_number.get().value());
        checksum += bench::digest(message.fields.cross_type.get().value());
        checksum += bench::digest(message.fields.price_long.get().value());
        checksum += bench::digest(message.fields.volume_long.get().value());
    }

    void on_message(const protocol::broken_trade_order_executed_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.cross_number.get().value());
        checksum += bench::digest(message.fields.match_number.get().value());
    }

    void on_message(const protocol::noii_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.tracking_number.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.auction_id.get().value());
        checksum += bench::digest(message.fields.auction_type.get().value());
        checksum += bench::digest(message.fields.paired_contracts.get().value());
        checksum += bench::digest(message.fields.imbalance_direction.get().value());
        checksum += bench::digest(message.fields.option_id.get().value());
        checksum += bench::digest(message.fields.imbalance_price.get().value());
        checksum += bench::digest(message.fields.imbalance_volume.get().value());
        checksum += bench::digest(message.fields.customer_firm_indicator.get().value());
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
    return bench::run("Nasdaq.NomOptions.Itto.Itch.v4.0.2025", "advanced", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
