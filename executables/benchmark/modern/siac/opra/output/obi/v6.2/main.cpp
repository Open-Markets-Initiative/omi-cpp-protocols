// Siac.Opra.Output.Obi.v6.2: main.cpp
// Siac.Opra.Output.Obi.v6.2 benchmark, through the Modern iterator: every value it reads from every message of the simulated
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
#include "cpp/binary/modern/siac/opra/output/obi/v6.2/definitions.hpp"

namespace protocol = ::siac::opra::output::obi::v6_2;

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
    checksum += bench::digest(iterator.block_header->session_indicator.get());
    checksum += bench::digest(iterator.block_header->block_sequence_number.get());
    checksum += bench::digest(iterator.block_header->messages_in_block.get());
    checksum += bench::digest(iterator.block_header->block_timestamp.seconds.get());
    checksum += bench::digest(iterator.block_header->block_timestamp.nanoseconds.get());
    checksum += bench::digest(iterator.block_header->block_checksum.get());

    std::size_t index = 0;

    while (iterator.next()) {
        checksum += index++;
        checksum += bench::digest(iterator.message_header->participant_id.get());
        checksum += bench::digest(iterator.message_header->message_category.get());

        if (iterator.message_category == 'C') {
            [[maybe_unused]] const auto* message = protocol::AdministrativeCategory::parse(iterator.message);
            checksum += bench::digest(message->administrative_message_type.get());
            if (message->administrative_message_type.get() == ' ') {
                [[maybe_unused]] const auto* message_2 = protocol::AdministrativeMessage::parse(iterator.message + sizeof(protocol::AdministrativeCategory));
                checksum += bench::digest(message_2->message_indicator.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->message_data_length.get());
            }
        } else if (iterator.message_category == 'H') {
            [[maybe_unused]] const auto* message = protocol::ControlCategory::parse(iterator.message);
            checksum += bench::digest(message->control_message_type.get());
            if (message->control_message_type.get() == 'C' || message->control_message_type.get() == 'E' || message->control_message_type.get() == 'F' || message->control_message_type.get() == 'J' || message->control_message_type.get() == 'K' || message->control_message_type.get() == 'L' || message->control_message_type.get() == 'M' || message->control_message_type.get() == 'N' || message->control_message_type.get() == 'P') {
                [[maybe_unused]] const auto* message_2 = protocol::ControlMessage::parse(iterator.message + sizeof(protocol::ControlCategory));
                checksum += bench::digest(message_2->message_indicator.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
            }
        } else if (iterator.message_category == 'a') {
            [[maybe_unused]] const auto* message = protocol::EquityAndIndexLastSaleCategory::parse(iterator.message);
            checksum += bench::digest(message->equity_and_index_last_sale_message_type.get());
            if (message->equity_and_index_last_sale_message_type.get() == 'A' || message->equity_and_index_last_sale_message_type.get() == 'B' || message->equity_and_index_last_sale_message_type.get() == 'C' || message->equity_and_index_last_sale_message_type.get() == 'D' || message->equity_and_index_last_sale_message_type.get() == 'E' || message->equity_and_index_last_sale_message_type.get() == 'F' || message->equity_and_index_last_sale_message_type.get() == 'G' || message->equity_and_index_last_sale_message_type.get() == 'H' || message->equity_and_index_last_sale_message_type.get() == 'I' || message->equity_and_index_last_sale_message_type.get() == 'J' || message->equity_and_index_last_sale_message_type.get() == 'K' || message->equity_and_index_last_sale_message_type.get() == 'L' || message->equity_and_index_last_sale_message_type.get() == 'M' || message->equity_and_index_last_sale_message_type.get() == 'N' || message->equity_and_index_last_sale_message_type.get() == 'O' || message->equity_and_index_last_sale_message_type.get() == 'P' || message->equity_and_index_last_sale_message_type.get() == 'Q' || message->equity_and_index_last_sale_message_type.get() == 'R' || message->equity_and_index_last_sale_message_type.get() == 'S' || message->equity_and_index_last_sale_message_type.get() == 'T' || message->equity_and_index_last_sale_message_type.get() == 'X') {
                [[maybe_unused]] const auto* message_2 = protocol::EquityAndIndexLastSaleMessage::parse(iterator.message + sizeof(protocol::EquityAndIndexLastSaleCategory));
                checksum += bench::digest(message_2->message_indicator.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->security_symbol.get());
                checksum += bench::digest(message_2->expiration_block.expiration_month.get());
                checksum += bench::digest(message_2->expiration_block.expiration_day.get());
                checksum += bench::digest(message_2->expiration_block.expiration_year.get());
                checksum += bench::digest(message_2->strike_price_denominator_code.get());
                checksum += bench::digest(message_2->strike_price.integer());
                checksum += bench::digest(message_2->volume.get());
                checksum += bench::digest(message_2->premium_price_denominator_code.get());
                checksum += bench::digest(message_2->premium_price.integer());
                checksum += bench::digest(message_2->trade_identifier.get());
            }
        } else if (iterator.message_category == 'd') {
            [[maybe_unused]] const auto* message = protocol::OpenInterestCategory::parse(iterator.message);
            checksum += bench::digest(message->open_interest_message_type.get());
            if (message->open_interest_message_type.get() == ' ') {
                [[maybe_unused]] const auto* message_2 = protocol::OpenInterestMessage::parse(iterator.message + sizeof(protocol::OpenInterestCategory));
                checksum += bench::digest(message_2->message_indicator.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->security_symbol.get());
                checksum += bench::digest(message_2->expiration_block.expiration_month.get());
                checksum += bench::digest(message_2->expiration_block.expiration_day.get());
                checksum += bench::digest(message_2->expiration_block.expiration_year.get());
                checksum += bench::digest(message_2->strike_price_denominator_code.get());
                checksum += bench::digest(message_2->strike_price.integer());
                checksum += bench::digest(message_2->open_interest_volume.get());
            }
        } else if (iterator.message_category == 'f') {
            [[maybe_unused]] const auto* message = protocol::EquityAndIndexEndOfDaySummaryCategory::parse(iterator.message);
            checksum += bench::digest(message->equity_and_index_end_of_day_summary_message_type.get());
            if (message->equity_and_index_end_of_day_summary_message_type.get() == ' ') {
                [[maybe_unused]] const auto* message_2 = protocol::EquityAndIndexEndOfDaySummaryMessage::parse(iterator.message + sizeof(protocol::EquityAndIndexEndOfDaySummaryCategory));
                checksum += bench::digest(message_2->message_indicator.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->security_symbol.get());
                checksum += bench::digest(message_2->expiration_block.expiration_month.get());
                checksum += bench::digest(message_2->expiration_block.expiration_day.get());
                checksum += bench::digest(message_2->expiration_block.expiration_year.get());
                checksum += bench::digest(message_2->strike_price_denominator_code.get());
                checksum += bench::digest(message_2->strike_price.integer());
                checksum += bench::digest(message_2->volume.get());
                checksum += bench::digest(message_2->open_interest_volume.get());
                checksum += bench::digest(message_2->premium_price_denominator_code.get());
                checksum += bench::digest(message_2->open_price.get());
                checksum += bench::digest(message_2->high_price.get());
                checksum += bench::digest(message_2->low_price.get());
                checksum += bench::digest(message_2->last_price.get());
                checksum += bench::digest(message_2->net_change.get());
                checksum += bench::digest(message_2->underlying_price_denominator_code.get());
                checksum += bench::digest(message_2->underlying_price.integer());
                checksum += bench::digest(message_2->bid_price.get());
                checksum += bench::digest(message_2->offer_price.get());
            }
        } else if (iterator.message_category == 'k') {
            [[maybe_unused]] const auto* message = protocol::LongEquityAndIndexQuoteCategory::parse(iterator.message);
            checksum += bench::digest(message->long_equity_and_index_quote_message_type.get());
            if (message->long_equity_and_index_quote_message_type.get() == ' ' || message->long_equity_and_index_quote_message_type.get() == 'F' || message->long_equity_and_index_quote_message_type.get() == 'I' || message->long_equity_and_index_quote_message_type.get() == 'R' || message->long_equity_and_index_quote_message_type.get() == 'T' || message->long_equity_and_index_quote_message_type.get() == 'A' || message->long_equity_and_index_quote_message_type.get() == 'B' || message->long_equity_and_index_quote_message_type.get() == 'O' || message->long_equity_and_index_quote_message_type.get() == 'C' || message->long_equity_and_index_quote_message_type.get() == 'X' || message->long_equity_and_index_quote_message_type.get() == 'Y') {
                [[maybe_unused]] const auto* message_2 = protocol::LongEquityAndIndexQuoteMessage::parse(iterator.message + sizeof(protocol::LongEquityAndIndexQuoteCategory));
                checksum += bench::digest(message_2->bbo_indicator.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->security_symbol.get());
                checksum += bench::digest(message_2->expiration_block.expiration_month.get());
                checksum += bench::digest(message_2->expiration_block.expiration_day.get());
                checksum += bench::digest(message_2->expiration_block.expiration_year.get());
                checksum += bench::digest(message_2->strike_price_denominator_code.get());
                checksum += bench::digest(message_2->strike_price.integer());
                checksum += bench::digest(message_2->premium_price_denominator_code.get());
                checksum += bench::digest(message_2->bid_price.get());
                checksum += bench::digest(message_2->bid_size.get());
                checksum += bench::digest(message_2->offer_price.get());
                checksum += bench::digest(message_2->offer_size.get());
            }
        } else if (iterator.message_category == 'q') {
            [[maybe_unused]] const auto* message = protocol::ShortEquityAndIndexQuoteCategory::parse(iterator.message);
            checksum += bench::digest(message->short_equity_and_index_quote_message_type.get());
            if (message->short_equity_and_index_quote_message_type.get() == ' ' || message->short_equity_and_index_quote_message_type.get() == 'F' || message->short_equity_and_index_quote_message_type.get() == 'I' || message->short_equity_and_index_quote_message_type.get() == 'R' || message->short_equity_and_index_quote_message_type.get() == 'T' || message->short_equity_and_index_quote_message_type.get() == 'A' || message->short_equity_and_index_quote_message_type.get() == 'B' || message->short_equity_and_index_quote_message_type.get() == 'O' || message->short_equity_and_index_quote_message_type.get() == 'C' || message->short_equity_and_index_quote_message_type.get() == 'X' || message->short_equity_and_index_quote_message_type.get() == 'Y') {
                [[maybe_unused]] const auto* message_2 = protocol::ShortEquityAndIndexQuoteMessage::parse(iterator.message + sizeof(protocol::ShortEquityAndIndexQuoteCategory));
                checksum += bench::digest(message_2->bbo_indicator.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->security_symbol_short.get());
                checksum += bench::digest(message_2->expiration_block.expiration_month.get());
                checksum += bench::digest(message_2->expiration_block.expiration_day.get());
                checksum += bench::digest(message_2->expiration_block.expiration_year.get());
                checksum += bench::digest(message_2->strike_price_short.integer());
                checksum += bench::digest(message_2->bid_price_short.integer());
                checksum += bench::digest(message_2->bid_size_short.get());
                checksum += bench::digest(message_2->offer_price_short.integer());
                checksum += bench::digest(message_2->offer_size_short.get());
            }
        } else if (iterator.message_category == 'Y') {
            [[maybe_unused]] const auto* message = protocol::UnderlyingValueCategory::parse(iterator.message);
            checksum += bench::digest(message->underlying_value_message_type.get());
            if (message->underlying_value_message_type.get() == ' ') {
                [[maybe_unused]] const auto* message_2 = protocol::UnderlyingValueLastSaleMessage::parse(iterator.message + sizeof(protocol::UnderlyingValueCategory));
                checksum += bench::digest(message_2->message_indicator.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->security_symbol.get());
                checksum += bench::digest(message_2->index_value_denominator_code.get());
                checksum += bench::digest(message_2->index_value.integer());
            } else if (message->underlying_value_message_type.get() == 'I') {
                [[maybe_unused]] const auto* message_2 = protocol::UnderlyingValueBidAndOfferMessage::parse(iterator.message + sizeof(protocol::UnderlyingValueCategory));
                checksum += bench::digest(message_2->message_indicator.get());
                checksum += bench::digest(message_2->transaction_id.get());
                checksum += bench::digest(message_2->participant_reference_number.get());
                checksum += bench::digest(message_2->security_symbol.get());
                checksum += bench::digest(message_2->index_value_denominator_code.get());
                checksum += bench::digest(message_2->bid_index_value.get());
                checksum += bench::digest(message_2->offer_index_value.get());
            }
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Siac.Opra.Output.Obi.v6.2", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
