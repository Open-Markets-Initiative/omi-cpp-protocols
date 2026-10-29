// Iex.IexEquities.Tops.IexTp.v1.56 benchmark, through the Advanced session layer: every value it reads from every message of the simulated
// sequence (tests/simulated/iex/iexequities/tops/iextp/v1.56.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/advanced/iex/iexequities/tops/iextp/v1.56/messages/session.hpp"

namespace protocol = ::iex::iexequities::tops::iextp::v1_56;

namespace {

// The handler the session layer hands each datagram's values to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    protocol::seq_action on_transport_header(const protocol::iextp_header& header, const packet::Frame&) {
        checksum += bench::digest(header.version.get().value());
        checksum += bench::digest(header.message_protocol_id.get().value());
        checksum += bench::digest(header.channel_id.get().value());
        checksum += bench::digest(header.session_id.get().value());
        checksum += bench::digest(header.payload_length.get().value());
        checksum += bench::digest(header.message_count.get().value());
        checksum += bench::digest(header.stream_offset.get().value());
        checksum += bench::digest(header.first_message_sequence_number.get().value());
        checksum += bench::digest(header.send_time.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::iextp_header&) {
        ++index;
    }

    void on_message(const protocol::quote_update_message& message, std::uint64_t, const protocol::iextp_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.quote_update_flags.has_market_session());
        checksum += bench::digest(message.fields.quote_update_flags.has_symbol_availability());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.bid_size.get().value());
        checksum += bench::digest(message.fields.bid_price.get().value());
        checksum += bench::digest(message.fields.ask_price.get().value());
        checksum += bench::digest(message.fields.ask_size.get().value());
    }

    void on_message(const protocol::trade_report_message& message, std::uint64_t, const protocol::iextp_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.sale_condition_flags.has_trade_through_exempt());
        checksum += bench::digest(message.fields.sale_condition_flags.has_odd_lot());
        checksum += bench::digest(message.fields.sale_condition_flags.has_extended_hours());
        checksum += bench::digest(message.fields.sale_condition_flags.has_intermarket_sweep());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.size.get().value());
        checksum += bench::digest(message.fields.price.get().value());
        checksum += bench::digest(message.fields.trade_id.get().value());
        checksum += bench::digest(message.fields.reserved_4.get().value());
    }

    void on_message(const protocol::trade_break_message& message, std::uint64_t, const protocol::iextp_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.sale_condition_flags.has_trade_through_exempt());
        checksum += bench::digest(message.fields.sale_condition_flags.has_odd_lot());
        checksum += bench::digest(message.fields.sale_condition_flags.has_extended_hours());
        checksum += bench::digest(message.fields.sale_condition_flags.has_intermarket_sweep());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.size.get().value());
        checksum += bench::digest(message.fields.price.get().value());
        checksum += bench::digest(message.fields.trade_id.get().value());
        checksum += bench::digest(message.fields.reserved_4.get().value());
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
    return bench::run("Iex.IexEquities.Tops.IexTp.v1.56", "advanced", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
