// Siac.Cqs.Output.Cta.v1.91 benchmark, through the Classes Packet: every value it reads from every message of the simulated
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
#include "cpp/binary/classes/siac/cqs/output/cta/v1.91/definitions.hpp"

namespace protocol = ::siac::cqs::output::cta::v1_91;

namespace {

// The values the Classes Packet decodes from one datagram, folded into a checksum. A datagram it cannot
// decode is a value the model never reads, so the benchmark refuses to time it.
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::Packet packet;

    try {
        packet.decode(frame.payload, frame.payload_len);
    } catch (const protocol::DecodeError& error) {
        throw;
        return checksum;
    }

    checksum += bench::digest(packet.block_header().version());
    checksum += bench::digest(packet.block_header().block_size());
    checksum += bench::digest(packet.block_header().data_feed_indicator());
    checksum += bench::digest(packet.block_header().retransmission_indicator());
    checksum += bench::digest(packet.block_header().block_sequence_number());
    checksum += bench::digest(packet.block_header().messages_in_block());
    checksum += bench::digest(packet.block_header().sip_block_timestamp().seconds());
    checksum += bench::digest(packet.block_header().sip_block_timestamp().nanoseconds());
    checksum += bench::digest(packet.block_header().block_checksum());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.message_length());
        checksum += bench::digest(each.message_category());

        if (const auto* message = dynamic_cast<const protocol::AdministrativeMessage*>(each.message())) {
            checksum += bench::digest((*message).administrative_message_type());
            if (const auto* message_2 = dynamic_cast<const protocol::AdministrativeUnformattedMessage*>(message->administrative_message_payload())) {
                checksum += bench::digest((*message_2).participant_id());
                checksum += bench::digest((*message_2).participant_timestamp().seconds());
                checksum += bench::digest((*message_2).participant_timestamp().nanoseconds());
                checksum += bench::digest((*message_2).message_id());
                checksum += bench::digest((*message_2).transaction_id());
                checksum += bench::digest((*message_2).participant_reference_number());
                checksum += bench::digest((*message_2).text());
            }
        } else if (const auto* message = dynamic_cast<const protocol::ControlMessage*>(each.message())) {
            checksum += bench::digest((*message).control_message_type());
            if (const auto* message_2 = dynamic_cast<const protocol::StartOfDayMessage*>(message->control_message_payload())) {
                checksum += bench::digest((*message_2).participant_id());
                checksum += bench::digest((*message_2).participant_timestamp().seconds());
                checksum += bench::digest((*message_2).participant_timestamp().nanoseconds());
                checksum += bench::digest((*message_2).message_id());
                checksum += bench::digest((*message_2).transaction_id());
                checksum += bench::digest((*message_2).participant_reference_number());
            } else if (const auto* message_2 = dynamic_cast<const protocol::FinraCloseMessage*>(message->control_message_payload())) {
                checksum += bench::digest((*message_2).participant_id());
                checksum += bench::digest((*message_2).participant_timestamp().seconds());
                checksum += bench::digest((*message_2).participant_timestamp().nanoseconds());
                checksum += bench::digest((*message_2).message_id());
                checksum += bench::digest((*message_2).transaction_id());
                checksum += bench::digest((*message_2).participant_reference_number());
            } else if (const auto* message_2 = dynamic_cast<const protocol::ResetBlockSequenceNumberMessage*>(message->control_message_payload())) {
                checksum += bench::digest((*message_2).participant_id());
                checksum += bench::digest((*message_2).participant_timestamp().seconds());
                checksum += bench::digest((*message_2).participant_timestamp().nanoseconds());
                checksum += bench::digest((*message_2).message_id());
                checksum += bench::digest((*message_2).transaction_id());
                checksum += bench::digest((*message_2).participant_reference_number());
            } else if (const auto* message_2 = dynamic_cast<const protocol::StartOfTestCycleMessage*>(message->control_message_payload())) {
                checksum += bench::digest((*message_2).participant_id());
                checksum += bench::digest((*message_2).participant_timestamp().seconds());
                checksum += bench::digest((*message_2).participant_timestamp().nanoseconds());
                checksum += bench::digest((*message_2).message_id());
                checksum += bench::digest((*message_2).transaction_id());
                checksum += bench::digest((*message_2).participant_reference_number());
            } else if (const auto* message_2 = dynamic_cast<const protocol::EndOfTestCycleMessage*>(message->control_message_payload())) {
                checksum += bench::digest((*message_2).participant_id());
                checksum += bench::digest((*message_2).participant_timestamp().seconds());
                checksum += bench::digest((*message_2).participant_timestamp().nanoseconds());
                checksum += bench::digest((*message_2).message_id());
                checksum += bench::digest((*message_2).transaction_id());
                checksum += bench::digest((*message_2).participant_reference_number());
            } else if (const auto* message_2 = dynamic_cast<const protocol::FinraOpenMessage*>(message->control_message_payload())) {
                checksum += bench::digest((*message_2).participant_id());
                checksum += bench::digest((*message_2).participant_timestamp().seconds());
                checksum += bench::digest((*message_2).participant_timestamp().nanoseconds());
                checksum += bench::digest((*message_2).message_id());
                checksum += bench::digest((*message_2).transaction_id());
                checksum += bench::digest((*message_2).participant_reference_number());
            } else if (const auto* message_2 = dynamic_cast<const protocol::DisasterRecoveryDataCenterActivationMessage*>(message->control_message_payload())) {
                checksum += bench::digest((*message_2).participant_id());
                checksum += bench::digest((*message_2).participant_timestamp().seconds());
                checksum += bench::digest((*message_2).participant_timestamp().nanoseconds());
                checksum += bench::digest((*message_2).message_id());
                checksum += bench::digest((*message_2).transaction_id());
                checksum += bench::digest((*message_2).participant_reference_number());
            } else if (const auto* message_2 = dynamic_cast<const protocol::LineIntegrityMessage*>(message->control_message_payload())) {
                checksum += bench::digest((*message_2).participant_id());
                checksum += bench::digest((*message_2).participant_timestamp().seconds());
                checksum += bench::digest((*message_2).participant_timestamp().nanoseconds());
                checksum += bench::digest((*message_2).message_id());
                checksum += bench::digest((*message_2).transaction_id());
                checksum += bench::digest((*message_2).participant_reference_number());
            } else if (const auto* message_2 = dynamic_cast<const protocol::EndOfDayMessage*>(message->control_message_payload())) {
                checksum += bench::digest((*message_2).participant_id());
                checksum += bench::digest((*message_2).participant_timestamp().seconds());
                checksum += bench::digest((*message_2).participant_timestamp().nanoseconds());
                checksum += bench::digest((*message_2).message_id());
                checksum += bench::digest((*message_2).transaction_id());
                checksum += bench::digest((*message_2).participant_reference_number());
            }
        } else if (const auto* message = dynamic_cast<const protocol::MarketStatusMessage*>(each.message())) {
            checksum += bench::digest((*message).market_status_message_type());
            if (const auto* message_2 = dynamic_cast<const protocol::MarketWideCircuitBreakerDeclineLevelStatusMessage*>(message->market_status_message_payload())) {
                checksum += bench::digest((*message_2).participant_id());
                checksum += bench::digest((*message_2).participant_timestamp().seconds());
                checksum += bench::digest((*message_2).participant_timestamp().nanoseconds());
                checksum += bench::digest((*message_2).message_id());
                checksum += bench::digest((*message_2).transaction_id());
                checksum += bench::digest((*message_2).participant_reference_number());
                checksum += bench::digest((*message_2).mwcb_level_1().mantissa());
                checksum += bench::digest((*message_2).mwcb_level_2().mantissa());
                checksum += bench::digest((*message_2).mwcb_level_3().mantissa());
                checksum += bench::digest((*message_2).reserved());
            } else if (const auto* message_2 = dynamic_cast<const protocol::MarketWideCircuitBreakerStatusMessage*>(message->market_status_message_payload())) {
                checksum += bench::digest((*message_2).participant_id());
                checksum += bench::digest((*message_2).participant_timestamp().seconds());
                checksum += bench::digest((*message_2).participant_timestamp().nanoseconds());
                checksum += bench::digest((*message_2).message_id());
                checksum += bench::digest((*message_2).transaction_id());
                checksum += bench::digest((*message_2).participant_reference_number());
                checksum += bench::digest((*message_2).market_wide_circuit_breaker_level_indicator());
                checksum += bench::digest((*message_2).reserved());
            }
        } else if (const auto* message = dynamic_cast<const protocol::QuoteMessage*>(each.message())) {
            checksum += bench::digest((*message).quote_message_type());
            if (const auto* message_2 = dynamic_cast<const protocol::AuctionStatusMessage*>(message->quote_message_payload())) {
                checksum += bench::digest((*message_2).participant_id());
                checksum += bench::digest((*message_2).participant_timestamp().seconds());
                checksum += bench::digest((*message_2).participant_timestamp().nanoseconds());
                checksum += bench::digest((*message_2).message_id());
                checksum += bench::digest((*message_2).transaction_id());
                checksum += bench::digest((*message_2).participant_reference_number());
                checksum += bench::digest((*message_2).security_symbol_long());
                checksum += bench::digest((*message_2).instrument_type());
                checksum += ((*message_2).auction_collar_reference_price().has_value() ? bench::digest((*(*message_2).auction_collar_reference_price()).mantissa()) : std::uint64_t{0});
                checksum += ((*message_2).auction_collar_upper_threshold_price().has_value() ? bench::digest((*(*message_2).auction_collar_upper_threshold_price()).mantissa()) : std::uint64_t{0});
                checksum += ((*message_2).auction_collar_lower_threshold_price().has_value() ? bench::digest((*(*message_2).auction_collar_lower_threshold_price()).mantissa()) : std::uint64_t{0});
                checksum += bench::digest((*message_2).number_of_extensions());
                checksum += bench::digest((*message_2).short_sale_restriction_indicator());
                checksum += bench::digest((*message_2).primary_listing_market_participant_id());
                checksum += bench::digest((*message_2).financial_status_indicator());
                checksum += bench::digest((*message_2).future());
            } else if (const auto* message_2 = dynamic_cast<const protocol::LongQuoteMessage*>(message->quote_message_payload())) {
                checksum += bench::digest((*message_2).participant_id());
                checksum += bench::digest((*message_2).participant_timestamp().seconds());
                checksum += bench::digest((*message_2).participant_timestamp().nanoseconds());
                checksum += bench::digest((*message_2).message_id());
                checksum += bench::digest((*message_2).transaction_id());
                checksum += bench::digest((*message_2).participant_reference_number());
                checksum += bench::digest((*message_2).security_symbol_long());
                checksum += bench::digest((*message_2).instrument_type());
                checksum += bench::digest((*message_2).quote_condition());
                checksum += bench::digest((*message_2).security_status_indicator());
                checksum += bench::digest((*message_2).bid_price_lower_limit_price_band().mantissa());
                checksum += bench::digest((*message_2).bid_size_long());
                checksum += bench::digest((*message_2).offer_price_upper_limit_price_band().mantissa());
                checksum += bench::digest((*message_2).offer_size_long());
                checksum += bench::digest((*message_2).retail_interest_indicator());
                checksum += bench::digest((*message_2).settlement_condition());
                checksum += bench::digest((*message_2).market_condition());
                checksum += bench::digest((*message_2).finra_market_maker_id());
                checksum += bench::digest((*message_2).finra_bbo_indicator());
                checksum += bench::digest((*message_2).adf_timestamp().seconds());
                checksum += bench::digest((*message_2).adf_timestamp().nanoseconds());
                checksum += bench::digest((*message_2).short_sale_restriction_indicator());
                checksum += bench::digest((*message_2).primary_listing_market_participant_id());
                checksum += bench::digest((*message_2).financial_status_indicator());
                checksum += bench::digest((*message_2).sip_generated_message_identifier());
                checksum += bench::digest((*message_2).luld_indicator());
                checksum += bench::digest((*message_2).national_bbo_luld_indicator());
                checksum += bench::digest((*message_2).national_bbo_indicator());
            } else if (const auto* message_2 = dynamic_cast<const protocol::ShortQuoteMessage*>(message->quote_message_payload())) {
                checksum += bench::digest((*message_2).participant_id());
                checksum += bench::digest((*message_2).participant_timestamp().seconds());
                checksum += bench::digest((*message_2).participant_timestamp().nanoseconds());
                checksum += bench::digest((*message_2).message_id());
                checksum += bench::digest((*message_2).transaction_id());
                checksum += bench::digest((*message_2).participant_reference_number());
                checksum += bench::digest((*message_2).security_symbol_short());
                checksum += bench::digest((*message_2).bid_price_short().mantissa());
                checksum += bench::digest((*message_2).bid_size_short());
                checksum += bench::digest((*message_2).offer_price_short().mantissa());
                checksum += bench::digest((*message_2).offer_size_short());
                checksum += bench::digest((*message_2).primary_listing_market_participant_id());
                checksum += bench::digest((*message_2).national_bbo_indicator());
            } else if (const auto* message_2 = dynamic_cast<const protocol::SpecialLongQuoteMessage*>(message->quote_message_payload())) {
                checksum += bench::digest((*message_2).participant_id());
                checksum += bench::digest((*message_2).participant_timestamp().seconds());
                checksum += bench::digest((*message_2).participant_timestamp().nanoseconds());
                checksum += bench::digest((*message_2).message_id());
                checksum += bench::digest((*message_2).transaction_id());
                checksum += bench::digest((*message_2).participant_reference_number());
                checksum += bench::digest((*message_2).security_symbol_long());
                checksum += bench::digest((*message_2).instrument_type());
                checksum += bench::digest((*message_2).quote_condition());
                checksum += bench::digest((*message_2).security_status_indicator());
                checksum += bench::digest((*message_2).bid_price_long().mantissa());
                checksum += bench::digest((*message_2).bid_size_long());
                checksum += bench::digest((*message_2).offer_price_long().mantissa());
                checksum += bench::digest((*message_2).offer_size_long());
                checksum += bench::digest((*message_2).retail_interest_indicator());
                checksum += bench::digest((*message_2).settlement_condition());
                checksum += bench::digest((*message_2).market_condition());
                checksum += bench::digest((*message_2).finra_market_maker_id());
                checksum += bench::digest((*message_2).finra_best_bid_quote_condition());
                checksum += bench::digest((*message_2).finra_best_bid_price().mantissa());
                checksum += bench::digest((*message_2).finra_best_bid_size());
                checksum += bench::digest((*message_2).finra_best_bid_market_maker_id());
                checksum += bench::digest((*message_2).finra_best_offer_quote_condition());
                checksum += bench::digest((*message_2).finra_best_offer_price().mantissa());
                checksum += bench::digest((*message_2).finra_best_offer_size());
                checksum += bench::digest((*message_2).finra_best_offer_market_maker_id());
                checksum += bench::digest((*message_2).adf_timestamp().seconds());
                checksum += bench::digest((*message_2).adf_timestamp().nanoseconds());
                checksum += bench::digest((*message_2).short_sale_restriction_indicator());
                checksum += bench::digest((*message_2).primary_listing_market_participant_id());
                checksum += bench::digest((*message_2).financial_status_indicator());
                checksum += bench::digest((*message_2).sip_generated_message_identifier());
                checksum += bench::digest((*message_2).finra_bbo_luld_indicator());
                checksum += bench::digest((*message_2).national_bbo_luld_indicator());
                checksum += bench::digest((*message_2).national_bbo_indicator());
            }
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Siac.Cqs.Output.Cta.v1.91", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
