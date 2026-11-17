// Siac.Cqs.Output.Cta.v2.10.a: main.cpp
// Siac.Cqs.Output.Cta.v2.10.a benchmark, through the Advanced session layer: every value it reads from every message of the simulated
// sequence (tests/simulated/siac/cqs/output/cta/v2.10.a.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/advanced/siac/cqs/output/cta/v2.10.a/messages/session.hpp"

namespace protocol = ::siac::cqs::output::cta::v2_10_a;

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
        checksum += bench::digest(header.block_sequence_number.get().value());
        checksum += bench::digest(header.messages_in_block.get().value());
        checksum += bench::digest(header.sip_block_timestamp.seconds.get().value());
        checksum += bench::digest(header.sip_block_timestamp.nanoseconds.get().value());
        checksum += bench::digest(header.block_checksum.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::block_header&) {
        ++index;
    }

    void on_message(const protocol::symbol_reference_data_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.administrative_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.prior_security_symbol.get().value());
        checksum += bench::digest(message.fields.primary_listing_market_participant_id.get().value());
        checksum += bench::digest(message.fields.primary_listing_market_previous_closing_price.get().value());
        checksum += bench::digest(message.fields.consolidated_closing_price.get().value());
        checksum += bench::digest(message.fields.round_lot_size.get().value());
        checksum += bench::digest(message.fields.luld_tier.get().value());
        checksum += bench::digest(message.fields.luld_leverage_ratio.get().value());
        checksum += bench::digest(message.fields.test.get().value());
        checksum += bench::digest(message.fields.ipo.get().value());
        checksum += bench::digest(message.fields.financial_status_indicator.get().value());
        checksum += bench::digest(message.fields.short_sale_restriction_indicator.get().value());
        checksum += bench::digest(message.fields.halt_reason.get().value());
        checksum += bench::digest(message.fields.instrument_type.get().value());
    }

    void on_message(const protocol::start_of_day_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.control_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
    }

    void on_message(const protocol::finra_close_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.control_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
    }

    void on_message(const protocol::reset_block_sequence_number_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.control_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
    }

    void on_message(const protocol::finra_open_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.control_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
    }

    void on_message(const protocol::disaster_recovery_data_center_activation_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.control_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
    }

    void on_message(const protocol::line_integrity_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.control_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
    }

    void on_message(const protocol::end_of_day_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.control_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
    }

    void on_message(const protocol::market_wide_circuit_breaker_decline_level_status_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.market_status_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.mwcb_level_1.get().value());
        checksum += bench::digest(message.fields.mwcb_level_2.get().value());
        checksum += bench::digest(message.fields.mwcb_level_3.get().value());
    }

    void on_message(const protocol::market_wide_circuit_breaker_status_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.market_status_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.market_wide_circuit_breaker_level_indicator.get().value());
    }

    void on_message(const protocol::auction_status_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.quote_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.instrument_type.get().value());
        checksum += bench::digest(message.fields.auction_collar_reference_price.get().value());
        checksum += bench::digest(message.fields.auction_collar_upper_threshold_price.get().value());
        checksum += bench::digest(message.fields.auction_collar_lower_threshold_price.get().value());
        checksum += bench::digest(message.fields.number_of_extensions.get().value());
        checksum += bench::digest(message.fields.short_sale_restriction_indicator.get().value());
        checksum += bench::digest(message.fields.primary_listing_market_participant_id.get().value());
        checksum += bench::digest(message.fields.financial_status_indicator.get().value());
    }

    void on_message(const protocol::long_quote_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.quote_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.instrument_type.get().value());
        checksum += bench::digest(message.fields.quote_condition.get().value());
        checksum += bench::digest(message.fields.security_status_indicator.get().value());
        checksum += bench::digest(message.fields.bid_price_lower_limit_price_band.get().value());
        checksum += bench::digest(message.fields.bid_size_long.get().value());
        checksum += bench::digest(message.fields.offer_price_upper_limit_price_band.get().value());
        checksum += bench::digest(message.fields.offer_size_long.get().value());
        checksum += bench::digest(message.fields.retail_interest_indicator.get().value());
        checksum += bench::digest(message.fields.settlement_condition.get().value());
        checksum += bench::digest(message.fields.market_condition.get().value());
        checksum += bench::digest(message.fields.finra_market_maker_id.get().value());
        checksum += bench::digest(message.fields.finra_bbo_indicator.get().value());
        checksum += bench::digest(message.fields.short_sale_restriction_indicator.get().value());
        checksum += bench::digest(message.fields.primary_listing_market_participant_id.get().value());
        checksum += bench::digest(message.fields.financial_status_indicator.get().value());
        checksum += bench::digest(message.fields.sip_generated_message_identifier.get().value());
        checksum += bench::digest(message.fields.limit_up_limit_down_luld_indicator.get().value());
        checksum += bench::digest(message.fields.national_bbo_luld_indicator.get().value());
        checksum += bench::digest(message.fields.national_bbo_indicator.get().value());
    }

    void on_message(const protocol::short_quote_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.quote_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.bid_price_short.get().value());
        checksum += bench::digest(message.fields.bid_size_short.get().value());
        checksum += bench::digest(message.fields.offer_price_short.get().value());
        checksum += bench::digest(message.fields.offer_size_short.get().value());
        checksum += bench::digest(message.fields.primary_listing_market_participant_id.get().value());
        checksum += bench::digest(message.fields.national_bbo_indicator.get().value());
    }

    void on_message(const protocol::special_long_quote_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.quote_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.instrument_type.get().value());
        checksum += bench::digest(message.fields.quote_condition.get().value());
        checksum += bench::digest(message.fields.security_status_indicator.get().value());
        checksum += bench::digest(message.fields.bid_price_long.get().value());
        checksum += bench::digest(message.fields.bid_size_long.get().value());
        checksum += bench::digest(message.fields.offer_price_long.get().value());
        checksum += bench::digest(message.fields.offer_size_long.get().value());
        checksum += bench::digest(message.fields.retail_interest_indicator.get().value());
        checksum += bench::digest(message.fields.settlement_condition.get().value());
        checksum += bench::digest(message.fields.market_condition.get().value());
        checksum += bench::digest(message.fields.finra_market_maker_id.get().value());
        checksum += bench::digest(message.fields.finra_best_bid_quote_condition.get().value());
        checksum += bench::digest(message.fields.finra_best_bid_price.get().value());
        checksum += bench::digest(message.fields.finra_best_bid_size.get().value());
        checksum += bench::digest(message.fields.finra_best_bid_market_maker_id.get().value());
        checksum += bench::digest(message.fields.finra_best_offer_quote_condition.get().value());
        checksum += bench::digest(message.fields.finra_best_offer_price.get().value());
        checksum += bench::digest(message.fields.finra_best_offer_size.get().value());
        checksum += bench::digest(message.fields.finra_best_offer_market_maker_id.get().value());
        checksum += bench::digest(message.fields.short_sale_restriction_indicator.get().value());
        checksum += bench::digest(message.fields.primary_listing_market_participant_id.get().value());
        checksum += bench::digest(message.fields.financial_status_indicator.get().value());
        checksum += bench::digest(message.fields.sip_generated_message_identifier.get().value());
        checksum += bench::digest(message.fields.finra_bbo_luld_indicator.get().value());
        checksum += bench::digest(message.fields.national_bbo_luld_indicator.get().value());
        checksum += bench::digest(message.fields.national_bbo_indicator.get().value());
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
    return bench::run("Siac.Cqs.Output.Cta.v2.10.a", "advanced", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
