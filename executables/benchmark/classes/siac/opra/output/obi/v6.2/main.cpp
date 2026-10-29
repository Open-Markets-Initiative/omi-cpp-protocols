// Siac.Opra.Output.Obi.v6.2 benchmark, through the Classes Packet: every value it reads from every message of the simulated
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
#include "cpp/binary/classes/siac/opra/output/obi/v6.2/definitions.hpp"

namespace protocol = ::siac::opra::output::obi::v6_2;

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
    checksum += bench::digest(packet.block_header().session_indicator());
    checksum += bench::digest(packet.block_header().block_sequence_number());
    checksum += bench::digest(packet.block_header().messages_in_block());
    checksum += bench::digest(packet.block_header().block_timestamp().seconds());
    checksum += bench::digest(packet.block_header().block_timestamp().nanoseconds());
    checksum += bench::digest(packet.block_header().block_checksum());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.message_header().participant_id());
        checksum += bench::digest(each.message_header().message_category());

        if (const auto* message = dynamic_cast<const protocol::AdministrativeCategory*>(each.message())) {
            checksum += bench::digest((*message).administrative_message_type());
            if (const auto* message_2 = dynamic_cast<const protocol::AdministrativeMessage*>(message->administrative_message_payload())) {
                checksum += bench::digest((*message_2).message_indicator());
                checksum += bench::digest((*message_2).transaction_id());
                checksum += bench::digest((*message_2).participant_reference_number());
                checksum += bench::digest((*message_2).message_data_length());
            }
        } else if (const auto* message = dynamic_cast<const protocol::ControlCategory*>(each.message())) {
            checksum += bench::digest((*message).control_message_type());
            if (const auto* message_2 = dynamic_cast<const protocol::ControlMessage*>(message->control_message_payload())) {
                checksum += bench::digest((*message_2).message_indicator());
                checksum += bench::digest((*message_2).transaction_id());
                checksum += bench::digest((*message_2).participant_reference_number());
            }
        } else if (const auto* message = dynamic_cast<const protocol::EquityAndIndexLastSaleCategory*>(each.message())) {
            checksum += bench::digest((*message).equity_and_index_last_sale_message_type());
            if (const auto* message_2 = dynamic_cast<const protocol::EquityAndIndexLastSaleMessage*>(message->equity_and_index_last_sale_message_payload())) {
                checksum += bench::digest((*message_2).message_indicator());
                checksum += bench::digest((*message_2).transaction_id());
                checksum += bench::digest((*message_2).participant_reference_number());
                checksum += bench::digest((*message_2).security_symbol());
                checksum += bench::digest((*message_2).expiration_block().expiration_month());
                checksum += bench::digest((*message_2).expiration_block().expiration_day());
                checksum += bench::digest((*message_2).expiration_block().expiration_year());
                checksum += bench::digest((*message_2).strike_price_denominator_code());
                checksum += bench::digest((*message_2).strike_price().mantissa());
                checksum += bench::digest((*message_2).volume());
                checksum += bench::digest((*message_2).premium_price_denominator_code());
                checksum += bench::digest((*message_2).premium_price().mantissa());
                checksum += bench::digest((*message_2).trade_identifier());
            }
        } else if (const auto* message = dynamic_cast<const protocol::OpenInterestCategory*>(each.message())) {
            checksum += bench::digest((*message).open_interest_message_type());
            if (const auto* message_2 = dynamic_cast<const protocol::OpenInterestMessage*>(message->open_interest_message_payload())) {
                checksum += bench::digest((*message_2).message_indicator());
                checksum += bench::digest((*message_2).transaction_id());
                checksum += bench::digest((*message_2).participant_reference_number());
                checksum += bench::digest((*message_2).security_symbol());
                checksum += bench::digest((*message_2).expiration_block().expiration_month());
                checksum += bench::digest((*message_2).expiration_block().expiration_day());
                checksum += bench::digest((*message_2).expiration_block().expiration_year());
                checksum += bench::digest((*message_2).strike_price_denominator_code());
                checksum += bench::digest((*message_2).strike_price().mantissa());
                checksum += bench::digest((*message_2).open_interest_volume());
            }
        } else if (const auto* message = dynamic_cast<const protocol::EquityAndIndexEndOfDaySummaryCategory*>(each.message())) {
            checksum += bench::digest((*message).equity_and_index_end_of_day_summary_message_type());
            if (const auto* message_2 = dynamic_cast<const protocol::EquityAndIndexEndOfDaySummaryMessage*>(message->equity_and_index_end_of_day_summary_message_payload())) {
                checksum += bench::digest((*message_2).message_indicator());
                checksum += bench::digest((*message_2).transaction_id());
                checksum += bench::digest((*message_2).participant_reference_number());
                checksum += bench::digest((*message_2).security_symbol());
                checksum += bench::digest((*message_2).expiration_block().expiration_month());
                checksum += bench::digest((*message_2).expiration_block().expiration_day());
                checksum += bench::digest((*message_2).expiration_block().expiration_year());
                checksum += bench::digest((*message_2).strike_price_denominator_code());
                checksum += bench::digest((*message_2).strike_price().mantissa());
                checksum += bench::digest((*message_2).volume());
                checksum += bench::digest((*message_2).open_interest_volume());
                checksum += bench::digest((*message_2).premium_price_denominator_code());
                checksum += bench::digest((*message_2).open_price());
                checksum += bench::digest((*message_2).high_price());
                checksum += bench::digest((*message_2).low_price());
                checksum += bench::digest((*message_2).last_price());
                checksum += bench::digest((*message_2).net_change());
                checksum += bench::digest((*message_2).underlying_price_denominator_code());
                checksum += bench::digest((*message_2).underlying_price().mantissa());
                checksum += bench::digest((*message_2).bid_price());
                checksum += bench::digest((*message_2).offer_price());
            }
        } else if (const auto* message = dynamic_cast<const protocol::LongEquityAndIndexQuoteCategory*>(each.message())) {
            checksum += bench::digest((*message).long_equity_and_index_quote_message_type());
            if (const auto* message_2 = dynamic_cast<const protocol::LongEquityAndIndexQuoteMessage*>(message->long_equity_and_index_quote_message_payload())) {
                checksum += bench::digest((*message_2).bbo_indicator());
                checksum += bench::digest((*message_2).transaction_id());
                checksum += bench::digest((*message_2).participant_reference_number());
                checksum += bench::digest((*message_2).security_symbol());
                checksum += bench::digest((*message_2).expiration_block().expiration_month());
                checksum += bench::digest((*message_2).expiration_block().expiration_day());
                checksum += bench::digest((*message_2).expiration_block().expiration_year());
                checksum += bench::digest((*message_2).strike_price_denominator_code());
                checksum += bench::digest((*message_2).strike_price().mantissa());
                checksum += bench::digest((*message_2).premium_price_denominator_code());
                checksum += bench::digest((*message_2).bid_price());
                checksum += bench::digest((*message_2).bid_size());
                checksum += bench::digest((*message_2).offer_price());
                checksum += bench::digest((*message_2).offer_size());
            }
        } else if (const auto* message = dynamic_cast<const protocol::ShortEquityAndIndexQuoteCategory*>(each.message())) {
            checksum += bench::digest((*message).short_equity_and_index_quote_message_type());
            if (const auto* message_2 = dynamic_cast<const protocol::ShortEquityAndIndexQuoteMessage*>(message->short_equity_and_index_quote_message_payload())) {
                checksum += bench::digest((*message_2).bbo_indicator());
                checksum += bench::digest((*message_2).transaction_id());
                checksum += bench::digest((*message_2).participant_reference_number());
                checksum += bench::digest((*message_2).security_symbol_short());
                checksum += bench::digest((*message_2).expiration_block().expiration_month());
                checksum += bench::digest((*message_2).expiration_block().expiration_day());
                checksum += bench::digest((*message_2).expiration_block().expiration_year());
                checksum += bench::digest((*message_2).strike_price_short().mantissa());
                checksum += bench::digest((*message_2).bid_price_short().mantissa());
                checksum += bench::digest((*message_2).bid_size_short());
                checksum += bench::digest((*message_2).offer_price_short().mantissa());
                checksum += bench::digest((*message_2).offer_size_short());
            }
        } else if (const auto* message = dynamic_cast<const protocol::UnderlyingValueCategory*>(each.message())) {
            checksum += bench::digest((*message).underlying_value_message_type());
            if (const auto* message_2 = dynamic_cast<const protocol::UnderlyingValueLastSaleMessage*>(message->underlying_value_message_payload())) {
                checksum += bench::digest((*message_2).message_indicator());
                checksum += bench::digest((*message_2).transaction_id());
                checksum += bench::digest((*message_2).participant_reference_number());
                checksum += bench::digest((*message_2).security_symbol());
                checksum += bench::digest((*message_2).index_value_denominator_code());
                checksum += bench::digest((*message_2).index_value().mantissa());
            } else if (const auto* message_2 = dynamic_cast<const protocol::UnderlyingValueBidAndOfferMessage*>(message->underlying_value_message_payload())) {
                checksum += bench::digest((*message_2).message_indicator());
                checksum += bench::digest((*message_2).transaction_id());
                checksum += bench::digest((*message_2).participant_reference_number());
                checksum += bench::digest((*message_2).security_symbol());
                checksum += bench::digest((*message_2).index_value_denominator_code());
                checksum += bench::digest((*message_2).bid_index_value());
                checksum += bench::digest((*message_2).offer_index_value());
            }
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Siac.Opra.Output.Obi.v6.2", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
