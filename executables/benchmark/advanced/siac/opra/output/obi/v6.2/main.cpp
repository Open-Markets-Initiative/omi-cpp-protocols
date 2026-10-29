// Siac.Opra.Output.Obi.v6.2 benchmark, through the Advanced session layer: every value it reads from every message of the simulated
// sequence (tests/simulated/siac/opra/output/obi/v6.2.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/advanced/siac/opra/output/obi/v6.2/messages/session.hpp"

namespace protocol = ::siac::opra::output::obi::v6_2;

namespace {

// The handler the session layer hands each datagram's values to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    protocol::seq_action on_transport_header(const protocol::block_header& header, const packet::Frame&) {
        checksum += bench::digest(header.version.get().value());
        checksum += bench::digest(header.block_size.get().value());
        checksum += bench::digest(header.data_feed_indicator.get().value());
        checksum += bench::digest(header.retransmission_indicator.get().value());
        checksum += bench::digest(header.session_indicator.get().value());
        checksum += bench::digest(header.block_sequence_number.get().value());
        checksum += bench::digest(header.messages_in_block.get().value());
        checksum += bench::digest(header.block_timestamp.seconds.get().value());
        checksum += bench::digest(header.block_timestamp.nanoseconds.get().value());
        checksum += bench::digest(header.block_checksum.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::block_header&) {
        ++index;
    }

    void on_message(const protocol::administrative_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.participant_id.get().value());
        checksum += bench::digest(message.header.message_category.get().value());
        checksum += bench::digest(message.administrative_message_type.get().value());
        checksum += bench::digest(message.fields.message_indicator.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.message_data_length.get().value());
    }

    void on_message(const protocol::control_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.participant_id.get().value());
        checksum += bench::digest(message.header.message_category.get().value());
        checksum += bench::digest(message.control_message_type.get().value());
        checksum += bench::digest(message.fields.message_indicator.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
    }

    void on_message(const protocol::equity_and_index_last_sale_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.participant_id.get().value());
        checksum += bench::digest(message.header.message_category.get().value());
        checksum += bench::digest(message.equity_and_index_last_sale_message_type.get().value());
        checksum += bench::digest(message.fields.message_indicator.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.expiration_block.expiration_month.get().value());
        checksum += bench::digest(message.fields.expiration_block.expiration_day.get().value());
        checksum += bench::digest(message.fields.expiration_block.expiration_year.get().value());
        checksum += bench::digest(message.fields.strike_price_denominator_code.get().value());
        checksum += bench::digest(message.fields.strike_price.get().value());
        checksum += bench::digest(message.fields.volume.get().value());
        checksum += bench::digest(message.fields.premium_price_denominator_code.get().value());
        checksum += bench::digest(message.fields.premium_price.get().value());
        checksum += bench::digest(message.fields.trade_identifier.get().value());
    }

    void on_message(const protocol::open_interest_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.participant_id.get().value());
        checksum += bench::digest(message.header.message_category.get().value());
        checksum += bench::digest(message.open_interest_message_type.get().value());
        checksum += bench::digest(message.fields.message_indicator.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.expiration_block.expiration_month.get().value());
        checksum += bench::digest(message.fields.expiration_block.expiration_day.get().value());
        checksum += bench::digest(message.fields.expiration_block.expiration_year.get().value());
        checksum += bench::digest(message.fields.strike_price_denominator_code.get().value());
        checksum += bench::digest(message.fields.strike_price.get().value());
        checksum += bench::digest(message.fields.open_interest_volume.get().value());
    }

    void on_message(const protocol::equity_and_index_end_of_day_summary_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.participant_id.get().value());
        checksum += bench::digest(message.header.message_category.get().value());
        checksum += bench::digest(message.equity_and_index_end_of_day_summary_message_type.get().value());
        checksum += bench::digest(message.fields.message_indicator.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.expiration_block.expiration_month.get().value());
        checksum += bench::digest(message.fields.expiration_block.expiration_day.get().value());
        checksum += bench::digest(message.fields.expiration_block.expiration_year.get().value());
        checksum += bench::digest(message.fields.strike_price_denominator_code.get().value());
        checksum += bench::digest(message.fields.strike_price.get().value());
        checksum += bench::digest(message.fields.volume.get().value());
        checksum += bench::digest(message.fields.open_interest_volume.get().value());
        checksum += bench::digest(message.fields.premium_price_denominator_code.get().value());
        checksum += bench::digest(message.fields.open_price.get().value());
        checksum += bench::digest(message.fields.high_price.get().value());
        checksum += bench::digest(message.fields.low_price.get().value());
        checksum += bench::digest(message.fields.last_price.get().value());
        checksum += bench::digest(message.fields.net_change.get().value());
        checksum += bench::digest(message.fields.underlying_price_denominator_code.get().value());
        checksum += bench::digest(message.fields.underlying_price.get().value());
        checksum += bench::digest(message.fields.bid_price.get().value());
        checksum += bench::digest(message.fields.offer_price.get().value());
    }

    void on_message(const protocol::long_equity_and_index_quote_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.participant_id.get().value());
        checksum += bench::digest(message.header.message_category.get().value());
        checksum += bench::digest(message.long_equity_and_index_quote_message_type.get().value());
        checksum += bench::digest(message.fields.bbo_indicator.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.expiration_block.expiration_month.get().value());
        checksum += bench::digest(message.fields.expiration_block.expiration_day.get().value());
        checksum += bench::digest(message.fields.expiration_block.expiration_year.get().value());
        checksum += bench::digest(message.fields.strike_price_denominator_code.get().value());
        checksum += bench::digest(message.fields.strike_price.get().value());
        checksum += bench::digest(message.fields.premium_price_denominator_code.get().value());
        checksum += bench::digest(message.fields.bid_price.get().value());
        checksum += bench::digest(message.fields.bid_size.get().value());
        checksum += bench::digest(message.fields.offer_price.get().value());
        checksum += bench::digest(message.fields.offer_size.get().value());
    }

    void on_message(const protocol::short_equity_and_index_quote_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.participant_id.get().value());
        checksum += bench::digest(message.header.message_category.get().value());
        checksum += bench::digest(message.short_equity_and_index_quote_message_type.get().value());
        checksum += bench::digest(message.fields.bbo_indicator.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol_short.get().value());
        checksum += bench::digest(message.fields.expiration_block.expiration_month.get().value());
        checksum += bench::digest(message.fields.expiration_block.expiration_day.get().value());
        checksum += bench::digest(message.fields.expiration_block.expiration_year.get().value());
        checksum += bench::digest(message.fields.strike_price_short.get().value());
        checksum += bench::digest(message.fields.bid_price_short.get().value());
        checksum += bench::digest(message.fields.bid_size_short.get().value());
        checksum += bench::digest(message.fields.offer_price_short.get().value());
        checksum += bench::digest(message.fields.offer_size_short.get().value());
    }

    void on_message(const protocol::underlying_value_last_sale_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.participant_id.get().value());
        checksum += bench::digest(message.header.message_category.get().value());
        checksum += bench::digest(message.underlying_value_message_type.get().value());
        checksum += bench::digest(message.fields.message_indicator.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.index_value_denominator_code.get().value());
        checksum += bench::digest(message.fields.index_value.get().value());
    }

    void on_message(const protocol::underlying_value_bid_and_offer_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.participant_id.get().value());
        checksum += bench::digest(message.header.message_category.get().value());
        checksum += bench::digest(message.underlying_value_message_type.get().value());
        checksum += bench::digest(message.fields.message_indicator.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.index_value_denominator_code.get().value());
        checksum += bench::digest(message.fields.bid_index_value.get().value());
        checksum += bench::digest(message.fields.offer_index_value.get().value());
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
    return bench::run("Siac.Opra.Output.Obi.v6.2", "advanced", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
