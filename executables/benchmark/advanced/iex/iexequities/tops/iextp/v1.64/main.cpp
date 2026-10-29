// Iex.IexEquities.Tops.IexTp.v1.64 benchmark, through the Advanced session layer: every value it reads from every message of the simulated
// sequence (tests/simulated/iex/iexequities/tops/iextp/v1.64.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/advanced/iex/iexequities/tops/iextp/v1.64/messages/session.hpp"

namespace protocol = ::iex::iexequities::tops::iextp::v1_64;

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

    void on_message(const protocol::system_event_message& message, std::uint64_t, const protocol::iextp_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.system_event.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
    }

    void on_message(const protocol::security_directory_message& message, std::uint64_t, const protocol::iextp_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.security_directory_flags.has_etp());
        checksum += bench::digest(message.fields.security_directory_flags.has_when_issued());
        checksum += bench::digest(message.fields.security_directory_flags.has_test_security());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.round_lot_size.get().value());
        checksum += bench::digest(message.fields.adjusted_poc_price.get().value());
        checksum += bench::digest(message.fields.luld_tier.get().value());
    }

    void on_message(const protocol::trading_status_message& message, std::uint64_t, const protocol::iextp_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.trading_status.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.reason.get().value());
    }

    void on_message(const protocol::operational_halt_status_message& message, std::uint64_t, const protocol::iextp_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.operational_halt_status.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
    }

    void on_message(const protocol::short_sale_price_test_status_message& message, std::uint64_t, const protocol::iextp_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.short_sale_price_test_status.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.detail.get().value());
    }

    void on_message(const protocol::security_event_message& message, std::uint64_t, const protocol::iextp_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.security_event.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
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
        checksum += bench::digest(message.fields.sale_condition_flags.has_single_price_cross_trade());
        checksum += bench::digest(message.fields.sale_condition_flags.has_trade_through_exempt());
        checksum += bench::digest(message.fields.sale_condition_flags.has_odd_lot());
        checksum += bench::digest(message.fields.sale_condition_flags.has_extended_hours());
        checksum += bench::digest(message.fields.sale_condition_flags.has_intermarket_sweep());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.size.get().value());
        checksum += bench::digest(message.fields.price.get().value());
        checksum += bench::digest(message.fields.trade_id.get().value());
    }

    void on_message(const protocol::official_price_message& message, std::uint64_t, const protocol::iextp_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.price_type.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.official_price.get().value());
    }

    void on_message(const protocol::trade_break_message& message, std::uint64_t, const protocol::iextp_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.sale_condition_flags.has_single_price_cross_trade());
        checksum += bench::digest(message.fields.sale_condition_flags.has_trade_through_exempt());
        checksum += bench::digest(message.fields.sale_condition_flags.has_odd_lot());
        checksum += bench::digest(message.fields.sale_condition_flags.has_extended_hours());
        checksum += bench::digest(message.fields.sale_condition_flags.has_intermarket_sweep());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.size.get().value());
        checksum += bench::digest(message.fields.price.get().value());
        checksum += bench::digest(message.fields.trade_id.get().value());
    }

    void on_message(const protocol::auction_information_message& message, std::uint64_t, const protocol::iextp_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.auction_type.get().value());
        checksum += bench::digest(message.fields.timestamp.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.paired_shares.get().value());
        checksum += bench::digest(message.fields.reference_price.get().value());
        checksum += bench::digest(message.fields.indicative_clearing_price.get().value());
        checksum += bench::digest(message.fields.imbalance_shares.get().value());
        checksum += bench::digest(message.fields.imbalance_side.get().value());
        checksum += bench::digest(message.fields.extension_number.get().value());
        checksum += bench::digest(message.fields.scheduled_auction_time.get().value());
        checksum += bench::digest(message.fields.auction_book_clearing_price.get().value());
        checksum += bench::digest(message.fields.collar_reference_price.get().value());
        checksum += bench::digest(message.fields.lower_auction_collar.get().value());
        checksum += bench::digest(message.fields.upper_auction_collar.get().value());
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
    return bench::run("Iex.IexEquities.Tops.IexTp.v1.64", "advanced", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
