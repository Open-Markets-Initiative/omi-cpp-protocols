// Siac.Cqs.Output.Cta.v2.10.a benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/siac/cqs/output/cta/v2.10.a.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <span>
#include <string>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "executables/benchmark/Benchmark.hpp"
#include "cpp/binary/flyweight/siac/cqs/output/cta/v2.10.a/definitions.hpp"

namespace protocol = ::siac::cqs::output::cta::v2_10_a;

namespace {

// The messages Administrative Message Payload selects, their values set in the entry of the message holding it
struct AdministrativeMessagePayloadHandler {
    std::uint64_t& checksum;

    void on(const protocol::SymbolReferenceDataMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.prior_security_symbol());
        checksum += bench::digest(message.primary_listing_market_participant_id());
        checksum += bench::digest(message.primary_listing_market_previous_closing_price().mantissa());
        checksum += bench::digest(message.consolidated_closing_price().mantissa());
        checksum += bench::digest(message.round_lot_size());
        checksum += bench::digest(message.reserved());
        checksum += bench::digest(message.luld_tier());
        checksum += bench::digest(message.luld_leverage_ratio().mantissa());
        checksum += bench::digest(message.test());
        checksum += bench::digest(message.ipo());
        checksum += bench::digest(message.financial_status_indicator());
        checksum += bench::digest(message.short_sale_restriction_indicator());
        checksum += bench::digest(message.halt_reason());
        checksum += bench::digest(message.instrument_type());
        checksum += bench::digest(message.second_reserved());
        checksum += bench::digest(message.third_reserved());
        checksum += bench::digest(message.reserved_128());
    }
};

// The messages Control Message Payload selects, their values set in the entry of the message holding it
struct ControlMessagePayloadHandler {
    std::uint64_t& checksum;

    void on(const protocol::StartOfDayMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
    }

    void on(const protocol::FinraCloseMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
    }

    void on(const protocol::ResetBlockSequenceNumberMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
    }

    void on(const protocol::FinraOpenMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
    }

    void on(const protocol::DisasterRecoveryDataCenterActivationMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
    }

    void on(const protocol::LineIntegrityMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
    }

    void on(const protocol::EndOfDayMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
    }
};

// The messages Market Status Message Payload selects, their values set in the entry of the message holding it
struct MarketStatusMessagePayloadHandler {
    std::uint64_t& checksum;

    void on(const protocol::MarketWideCircuitBreakerDeclineLevelStatusMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.mwcb_level_1().mantissa());
        checksum += bench::digest(message.mwcb_level_2().mantissa());
        checksum += bench::digest(message.mwcb_level_3().mantissa());
        checksum += bench::digest(message.reserved());
    }

    void on(const protocol::MarketWideCircuitBreakerStatusMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.market_wide_circuit_breaker_level_indicator());
        checksum += bench::digest(message.reserved());
    }
};

// The messages Quote Message Payload selects, their values set in the entry of the message holding it
struct QuoteMessagePayloadHandler {
    std::uint64_t& checksum;

    void on(const protocol::AuctionStatusMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.instrument_type());
        checksum += bench::digest(message.auction_collar_reference_price().mantissa());
        checksum += bench::digest(message.auction_collar_upper_threshold_price().mantissa());
        checksum += bench::digest(message.auction_collar_lower_threshold_price().mantissa());
        checksum += bench::digest(message.number_of_extensions());
        checksum += bench::digest(message.short_sale_restriction_indicator());
        checksum += bench::digest(message.primary_listing_market_participant_id());
        checksum += bench::digest(message.financial_status_indicator());
        checksum += bench::digest(message.reserved_62());
    }

    void on(const protocol::LongQuoteMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.instrument_type());
        checksum += bench::digest(message.quote_condition());
        checksum += bench::digest(message.security_status_indicator());
        checksum += bench::digest(message.bid_price_lower_limit_price_band().mantissa());
        checksum += bench::digest(message.bid_size_long());
        checksum += bench::digest(message.offer_price_upper_limit_price_band().mantissa());
        checksum += bench::digest(message.offer_size_long());
        checksum += bench::digest(message.retail_interest_indicator());
        checksum += bench::digest(message.settlement_condition());
        checksum += bench::digest(message.market_condition());
        checksum += bench::digest(message.finra_market_maker_id());
        checksum += bench::digest(message.finra_bbo_indicator());
        checksum += bench::digest(message.timestamp_2().seconds());
        checksum += bench::digest(message.timestamp_2().nanoseconds());
        checksum += bench::digest(message.short_sale_restriction_indicator());
        checksum += bench::digest(message.primary_listing_market_participant_id());
        checksum += bench::digest(message.financial_status_indicator());
        checksum += bench::digest(message.sip_generated_message_identifier());
        checksum += bench::digest(message.limit_up_limit_down_luld_indicator());
        checksum += bench::digest(message.national_bbo_luld_indicator());
        checksum += bench::digest(message.national_bbo_indicator());
    }

    void on(const protocol::ShortQuoteMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.bid_price_short().mantissa());
        checksum += bench::digest(message.bid_size_short());
        checksum += bench::digest(message.offer_price_short().mantissa());
        checksum += bench::digest(message.offer_size_short());
        checksum += bench::digest(message.primary_listing_market_participant_id());
        checksum += bench::digest(message.national_bbo_indicator());
    }

    void on(const protocol::SpecialLongQuoteMessage& message) {
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.timestamp_1().seconds());
        checksum += bench::digest(message.timestamp_1().nanoseconds());
        checksum += bench::digest(message.message_id());
        checksum += bench::digest(message.transaction_id());
        checksum += bench::digest(message.participant_reference_number());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.instrument_type());
        checksum += bench::digest(message.quote_condition());
        checksum += bench::digest(message.security_status_indicator());
        checksum += bench::digest(message.bid_price_long().mantissa());
        checksum += bench::digest(message.bid_size_long());
        checksum += bench::digest(message.offer_price_long().mantissa());
        checksum += bench::digest(message.offer_size_long());
        checksum += bench::digest(message.retail_interest_indicator());
        checksum += bench::digest(message.settlement_condition());
        checksum += bench::digest(message.market_condition());
        checksum += bench::digest(message.finra_market_maker_id());
        checksum += bench::digest(message.finra_best_bid_quote_condition());
        checksum += bench::digest(message.finra_best_bid_price().mantissa());
        checksum += bench::digest(message.finra_best_bid_size());
        checksum += bench::digest(message.finra_best_bid_market_maker_id());
        checksum += bench::digest(message.finra_best_offer_quote_condition());
        checksum += bench::digest(message.finra_best_offer_price().mantissa());
        checksum += bench::digest(message.finra_best_offer_size());
        checksum += bench::digest(message.finra_best_offer_market_maker_id());
        checksum += bench::digest(message.timestamp_2().seconds());
        checksum += bench::digest(message.timestamp_2().nanoseconds());
        checksum += bench::digest(message.short_sale_restriction_indicator());
        checksum += bench::digest(message.primary_listing_market_participant_id());
        checksum += bench::digest(message.financial_status_indicator());
        checksum += bench::digest(message.sip_generated_message_identifier());
        checksum += bench::digest(message.finra_bbo_luld_indicator());
        checksum += bench::digest(message.national_bbo_luld_indicator());
        checksum += bench::digest(message.national_bbo_indicator());
    }
};

// The handler the reader hands each datagram's views to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        checksum += bench::digest(packet.block_header().version());
        checksum += bench::digest(packet.block_header().block_size());
        checksum += bench::digest(packet.block_header().data_feed_indicator());
        checksum += bench::digest(packet.block_header().retransmission_indicator());
        checksum += bench::digest(packet.block_header().block_sequence_number());
        checksum += bench::digest(packet.block_header().messages_in_block());
        checksum += bench::digest(packet.block_header().sip_block_timestamp().seconds());
        checksum += bench::digest(packet.block_header().sip_block_timestamp().nanoseconds());
        checksum += bench::digest(packet.block_header().block_checksum());
    }

    // a message this test prints no values of, or a code no message answers to, still takes its entry
    template <typename Message>
    void on(const Message&) {
        ++index;
    }

    template <typename Code>
    void on_unknown(Code, std::span<const std::byte>) {
        ++index;
    }

    void on(const protocol::AdministrativeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.administrative_message_type());
        AdministrativeMessagePayloadHandler selected{ checksum };
        message.administrative_message_payload(selected);
    }

    void on(const protocol::ControlMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.control_message_type());
        ControlMessagePayloadHandler selected{ checksum };
        message.control_message_payload(selected);
    }

    void on(const protocol::MarketStatusMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.market_status_message_type());
        MarketStatusMessagePayloadHandler selected{ checksum };
        message.market_status_message_payload(selected);
    }

    void on(const protocol::QuoteMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.quote_message_type());
        QuoteMessagePayloadHandler selected{ checksum };
        message.quote_message_payload(selected);
    }
};

// The values the Flyweight reader reads from one datagram, folded into a checksum. A datagram it cannot
// read is a value the model never reads, so the benchmark refuses to time it.
std::uint64_t read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::PacketReader::read(std::span<const std::byte>(frame.payload, frame.payload_len), reader);
    } catch (const protocol::DecodeError& error) {
        throw;
    }

    return reader.checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Siac.Cqs.Output.Cta.v2.10.a", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
