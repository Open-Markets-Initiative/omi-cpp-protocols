// Nasdaq.PhlxOptions.TopOfMarket.Itch.v3.4 benchmark, through the Advanced session layer: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/phlxoptions/topofmarket/itch/v3.4.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/advanced/nasdaq/phlxoptions/topofmarket/itch/v3.4/messages/session.hpp"

namespace protocol = ::nasdaq::phlxoptions::topofmarket::itch::v3_4;

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
        checksum += bench::digest(message.fields.version.get().value());
        checksum += bench::digest(message.fields.sub_version.get().value());
    }

    void on_message(const protocol::options_directory_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.option_id.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.expiration_year.get().value());
        checksum += bench::digest(message.fields.expiration_month.get().value());
        checksum += bench::digest(message.fields.expiration_day.get().value());
        checksum += bench::digest(message.fields.strike_price.get().value());
        checksum += bench::digest(message.fields.option_type.get().value());
        checksum += bench::digest(message.fields.source.get().value());
        checksum += bench::digest(message.fields.underlying_symbol.get().value());
        checksum += bench::digest(message.fields.option_closing_type.get().value());
        checksum += bench::digest(message.fields.tradable.get().value());
        checksum += bench::digest(message.fields.mpv.get().value());
    }

    void on_message(const protocol::trading_action_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.option_id.get().value());
        checksum += bench::digest(message.fields.current_trading_state.get().value());
    }

    void on_message(const protocol::security_open_closed_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.option_id.get().value());
        checksum += bench::digest(message.fields.open_state.get().value());
    }

    void on_message(const protocol::short_best_bid_and_ask_update_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.option_id.get().value());
        checksum += bench::digest(message.fields.quote_condition.get().value());
        checksum += bench::digest(message.fields.bid_price_2.get().value());
        checksum += bench::digest(message.fields.bid_size_2.get().value());
        checksum += bench::digest(message.fields.ask_price_2.get().value());
        checksum += bench::digest(message.fields.ask_size_2.get().value());
    }

    void on_message(const protocol::long_best_bid_and_ask_update_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.option_id.get().value());
        checksum += bench::digest(message.fields.quote_condition.get().value());
        checksum += bench::digest(message.fields.bid_price_4.get().value());
        checksum += bench::digest(message.fields.bid_size_4.get().value());
        checksum += bench::digest(message.fields.ask_price_4.get().value());
        checksum += bench::digest(message.fields.ask_size_4.get().value());
    }

    void on_message(const protocol::short_best_ask_update_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.option_id.get().value());
        checksum += bench::digest(message.fields.quote_condition.get().value());
        checksum += bench::digest(message.fields.price_2.get().value());
        checksum += bench::digest(message.fields.size_2.get().value());
    }

    void on_message(const protocol::short_best_bid_update_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.option_id.get().value());
        checksum += bench::digest(message.fields.quote_condition.get().value());
        checksum += bench::digest(message.fields.price_2.get().value());
        checksum += bench::digest(message.fields.size_2.get().value());
    }

    void on_message(const protocol::long_best_ask_update_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.option_id.get().value());
        checksum += bench::digest(message.fields.quote_condition.get().value());
        checksum += bench::digest(message.fields.price_4.get().value());
        checksum += bench::digest(message.fields.size_4.get().value());
    }

    void on_message(const protocol::long_best_bid_update_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.option_id.get().value());
        checksum += bench::digest(message.fields.quote_condition.get().value());
        checksum += bench::digest(message.fields.price_4.get().value());
        checksum += bench::digest(message.fields.size_4.get().value());
    }

    void on_message(const protocol::trade_report_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.option_id.get().value());
        checksum += bench::digest(message.fields.cross_id.get().value());
        checksum += bench::digest(message.fields.trade_condition.get().value());
        checksum += bench::digest(message.fields.price_4.get().value());
        checksum += bench::digest(message.fields.volume.get().value());
    }

    void on_message(const protocol::broken_trade_report_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.option_id.get().value());
        checksum += bench::digest(message.fields.original_cross_id.get().value());
        checksum += bench::digest(message.fields.original_price.get().value());
        checksum += bench::digest(message.fields.original_volume.get().value());
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
    return bench::run("Nasdaq.PhlxOptions.TopOfMarket.Itch.v3.4", "advanced", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
