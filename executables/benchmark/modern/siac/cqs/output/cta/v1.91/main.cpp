// Siac.Cqs.Output.Cta.v1.91 benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/siac/cqs/output/cta/v1.91.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/siac/cqs/output/cta/v1.91/definitions.hpp"

namespace protocol = ::siac::cqs::output::cta::v1_91;

namespace {

// The values the Modern iterator reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    checksum += bench::digest(iterator.block_header->version.get());
    checksum += bench::digest(iterator.block_header->block_size.get());
    checksum += bench::digest(iterator.block_header->data_feed_indicator.get());
    checksum += bench::digest(iterator.block_header->retransmission_indicator.get());
    checksum += bench::digest(iterator.block_header->block_sequence_number.get());
    checksum += bench::digest(iterator.block_header->messages_in_block.get());
    checksum += bench::digest(iterator.block_header->sip_block_timestamp.seconds.get());
    checksum += bench::digest(iterator.block_header->sip_block_timestamp.nanoseconds.get());
    checksum += bench::digest(iterator.block_header->block_checksum.get());

    std::size_t index = 0;

    while (iterator.next()) {
        checksum += index++;
        checksum += bench::digest(iterator.message_header->message_length.get());
        checksum += bench::digest(iterator.message_header->message_category.get());

        if (iterator.message_category == 'A') {
            [[maybe_unused]] const auto* message = protocol::AdministrativeMessage::parse(iterator.message);
            checksum += bench::digest(message->administrative_message_type.get());
            if (message->administrative_message_type.get() == 'H') {
                [[maybe_unused]] const auto* message_2 = protocol::AdministrativeUnformattedMessage::parse(iterator.message + sizeof(protocol::AdministrativeMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->participant_timestamp.seconds.get());
                checksum += bench::digest(message_2->participant_timestamp.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->text.get());
            }
        } else if (iterator.message_category == 'C') {
            [[maybe_unused]] const auto* message = protocol::ControlMessage::parse(iterator.message);
            checksum += bench::digest(message->control_message_type.get());
            if (message->control_message_type.get() == 'A') {
                [[maybe_unused]] const auto* message_2 = protocol::StartOfDayMessage::parse(iterator.message + sizeof(protocol::ControlMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->participant_timestamp.seconds.get());
                checksum += bench::digest(message_2->participant_timestamp.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
            } else if (message->control_message_type.get() == 'C') {
                [[maybe_unused]] const auto* message_2 = protocol::FinraCloseMessage::parse(iterator.message + sizeof(protocol::ControlMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->participant_timestamp.seconds.get());
                checksum += bench::digest(message_2->participant_timestamp.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
            } else if (message->control_message_type.get() == 'L') {
                [[maybe_unused]] const auto* message_2 = protocol::ResetBlockSequenceNumberMessage::parse(iterator.message + sizeof(protocol::ControlMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->participant_timestamp.seconds.get());
                checksum += bench::digest(message_2->participant_timestamp.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
            } else if (message->control_message_type.get() == 'M') {
                [[maybe_unused]] const auto* message_2 = protocol::StartOfTestCycleMessage::parse(iterator.message + sizeof(protocol::ControlMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->participant_timestamp.seconds.get());
                checksum += bench::digest(message_2->participant_timestamp.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
            } else if (message->control_message_type.get() == 'N') {
                [[maybe_unused]] const auto* message_2 = protocol::EndOfTestCycleMessage::parse(iterator.message + sizeof(protocol::ControlMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->participant_timestamp.seconds.get());
                checksum += bench::digest(message_2->participant_timestamp.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
            } else if (message->control_message_type.get() == 'O') {
                [[maybe_unused]] const auto* message_2 = protocol::FinraOpenMessage::parse(iterator.message + sizeof(protocol::ControlMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->participant_timestamp.seconds.get());
                checksum += bench::digest(message_2->participant_timestamp.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
            } else if (message->control_message_type.get() == 'P') {
                [[maybe_unused]] const auto* message_2 = protocol::DisasterRecoveryDataCenterActivationMessage::parse(iterator.message + sizeof(protocol::ControlMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->participant_timestamp.seconds.get());
                checksum += bench::digest(message_2->participant_timestamp.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
            } else if (message->control_message_type.get() == 'T') {
                [[maybe_unused]] const auto* message_2 = protocol::LineIntegrityMessage::parse(iterator.message + sizeof(protocol::ControlMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->participant_timestamp.seconds.get());
                checksum += bench::digest(message_2->participant_timestamp.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
            } else if (message->control_message_type.get() == 'Z') {
                [[maybe_unused]] const auto* message_2 = protocol::EndOfDayMessage::parse(iterator.message + sizeof(protocol::ControlMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->participant_timestamp.seconds.get());
                checksum += bench::digest(message_2->participant_timestamp.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
            }
        } else if (iterator.message_category == 'M') {
            [[maybe_unused]] const auto* message = protocol::MarketStatusMessage::parse(iterator.message);
            checksum += bench::digest(message->market_status_message_type.get());
            if (message->market_status_message_type.get() == 'K') {
                [[maybe_unused]] const auto* message_2 = protocol::MarketWideCircuitBreakerDeclineLevelStatusMessage::parse(iterator.message + sizeof(protocol::MarketStatusMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->participant_timestamp.seconds.get());
                checksum += bench::digest(message_2->participant_timestamp.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->mwcb_level_1.integer());
                checksum += bench::digest(message_2->mwcb_level_2.integer());
                checksum += bench::digest(message_2->mwcb_level_3.integer());
                checksum += bench::digest(message_2->reserved.get());
            } else if (message->market_status_message_type.get() == 'L') {
                [[maybe_unused]] const auto* message_2 = protocol::MarketWideCircuitBreakerStatusMessage::parse(iterator.message + sizeof(protocol::MarketStatusMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->participant_timestamp.seconds.get());
                checksum += bench::digest(message_2->participant_timestamp.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->market_wide_circuit_breaker_level_indicator.get());
                checksum += bench::digest(message_2->reserved.get());
            }
        } else if (iterator.message_category == 'Q') {
            [[maybe_unused]] const auto* message = protocol::QuoteMessage::parse(iterator.message);
            checksum += bench::digest(message->quote_message_type.get());
            if (message->quote_message_type.get() == 'A') {
                [[maybe_unused]] const auto* message_2 = protocol::AuctionStatusMessage::parse(iterator.message + sizeof(protocol::QuoteMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->participant_timestamp.seconds.get());
                checksum += bench::digest(message_2->participant_timestamp.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->security_symbol_long.get());
                checksum += bench::digest(message_2->instrument_type.get());
                checksum += (static_cast<std::uint64_t>(message_2->auction_collar_reference_price.integer()) != 0x0ULL ? bench::digest(message_2->auction_collar_reference_price.integer()) : std::uint64_t{0});
                checksum += (static_cast<std::uint64_t>(message_2->auction_collar_upper_threshold_price.integer()) != 0x0ULL ? bench::digest(message_2->auction_collar_upper_threshold_price.integer()) : std::uint64_t{0});
                checksum += (static_cast<std::uint64_t>(message_2->auction_collar_lower_threshold_price.integer()) != 0x0ULL ? bench::digest(message_2->auction_collar_lower_threshold_price.integer()) : std::uint64_t{0});
                checksum += bench::digest(message_2->number_of_extensions.get());
                checksum += bench::digest(message_2->short_sale_restriction_indicator.get());
                checksum += bench::digest(message_2->primary_listing_market_participant_id.get());
                checksum += bench::digest(message_2->financial_status_indicator.get());
                checksum += bench::digest(message_2->future.get());
            } else if (message->quote_message_type.get() == 'L') {
                [[maybe_unused]] const auto* message_2 = protocol::LongQuoteMessage::parse(iterator.message + sizeof(protocol::QuoteMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->participant_timestamp.seconds.get());
                checksum += bench::digest(message_2->participant_timestamp.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->security_symbol_long.get());
                checksum += bench::digest(message_2->instrument_type.get());
                checksum += bench::digest(message_2->quote_condition.get());
                checksum += bench::digest(message_2->security_status_indicator.get());
                checksum += bench::digest(message_2->bid_price_lower_limit_price_band.integer());
                checksum += bench::digest(message_2->bid_size_long.get());
                checksum += bench::digest(message_2->offer_price_upper_limit_price_band.integer());
                checksum += bench::digest(message_2->offer_size_long.get());
                checksum += bench::digest(message_2->retail_interest_indicator.get());
                checksum += bench::digest(message_2->settlement_condition.get());
                checksum += bench::digest(message_2->market_condition.get());
                checksum += bench::digest(message_2->finra_market_maker_id.get());
                checksum += bench::digest(message_2->finra_bbo_indicator.get());
                checksum += bench::digest(message_2->adf_timestamp.seconds.get());
                checksum += bench::digest(message_2->adf_timestamp.nanoseconds.get());
                checksum += bench::digest(message_2->short_sale_restriction_indicator.get());
                checksum += bench::digest(message_2->primary_listing_market_participant_id.get());
                checksum += bench::digest(message_2->financial_status_indicator.get());
                checksum += bench::digest(message_2->sip_generated_message_identifier.get());
                checksum += bench::digest(message_2->luld_indicator.get());
                checksum += bench::digest(message_2->national_bbo_luld_indicator.get());
                checksum += bench::digest(message_2->national_bbo_indicator.get());
            } else if (message->quote_message_type.get() == 'Q') {
                [[maybe_unused]] const auto* message_2 = protocol::ShortQuoteMessage::parse(iterator.message + sizeof(protocol::QuoteMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->participant_timestamp.seconds.get());
                checksum += bench::digest(message_2->participant_timestamp.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->security_symbol_short.get());
                checksum += bench::digest(message_2->bid_price_short.integer());
                checksum += bench::digest(message_2->bid_size_short.get());
                checksum += bench::digest(message_2->offer_price_short.integer());
                checksum += bench::digest(message_2->offer_size_short.get());
                checksum += bench::digest(message_2->primary_listing_market_participant_id.get());
                checksum += bench::digest(message_2->national_bbo_indicator.get());
            } else if (message->quote_message_type.get() == 'S') {
                [[maybe_unused]] const auto* message_2 = protocol::SpecialLongQuoteMessage::parse(iterator.message + sizeof(protocol::QuoteMessage));
                checksum += bench::digest(message_2->participant_id.get());
                checksum += bench::digest(message_2->participant_timestamp.seconds.get());
                checksum += bench::digest(message_2->participant_timestamp.nanoseconds.get());
                checksum += bench::digest(message_2->message_id.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->security_symbol_long.get());
                checksum += bench::digest(message_2->instrument_type.get());
                checksum += bench::digest(message_2->quote_condition.get());
                checksum += bench::digest(message_2->security_status_indicator.get());
                checksum += bench::digest(message_2->bid_price_long.integer());
                checksum += bench::digest(message_2->bid_size_long.get());
                checksum += bench::digest(message_2->offer_price_long.integer());
                checksum += bench::digest(message_2->offer_size_long.get());
                checksum += bench::digest(message_2->retail_interest_indicator.get());
                checksum += bench::digest(message_2->settlement_condition.get());
                checksum += bench::digest(message_2->market_condition.get());
                checksum += bench::digest(message_2->finra_market_maker_id.get());
                checksum += bench::digest(message_2->finra_best_bid_quote_condition.get());
                checksum += bench::digest(message_2->finra_best_bid_price.integer());
                checksum += bench::digest(message_2->finra_best_bid_size.get());
                checksum += bench::digest(message_2->finra_best_bid_market_maker_id.get());
                checksum += bench::digest(message_2->finra_best_offer_quote_condition.get());
                checksum += bench::digest(message_2->finra_best_offer_price.integer());
                checksum += bench::digest(message_2->finra_best_offer_size.get());
                checksum += bench::digest(message_2->finra_best_offer_market_maker_id.get());
                checksum += bench::digest(message_2->adf_timestamp.seconds.get());
                checksum += bench::digest(message_2->adf_timestamp.nanoseconds.get());
                checksum += bench::digest(message_2->short_sale_restriction_indicator.get());
                checksum += bench::digest(message_2->primary_listing_market_participant_id.get());
                checksum += bench::digest(message_2->financial_status_indicator.get());
                checksum += bench::digest(message_2->sip_generated_message_identifier.get());
                checksum += bench::digest(message_2->finra_bbo_luld_indicator.get());
                checksum += bench::digest(message_2->national_bbo_luld_indicator.get());
                checksum += bench::digest(message_2->national_bbo_indicator.get());
            }
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Siac.Cqs.Output.Cta.v1.91", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
