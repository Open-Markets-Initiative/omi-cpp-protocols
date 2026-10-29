// Iex.IexEquities.Tops.IexTp.v1.64 benchmark, through the Modern iterator: every value it reads from every message of the simulated
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
#include "cpp/binary/modern/iex/iexequities/tops/iextp/v1.64/definitions.hpp"

namespace protocol = ::iex::iexequities::tops::iextp::v1_64;

namespace {

// The values the Modern iterator reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    checksum += bench::digest(iterator.iextp_header->version.get());
    checksum += bench::digest(iterator.iextp_header->message_protocol_id.get());
    checksum += bench::digest(iterator.iextp_header->channel_id.get());
    checksum += bench::digest(iterator.iextp_header->session_id.get());
    checksum += bench::digest(iterator.iextp_header->payload_length.get());
    checksum += bench::digest(iterator.iextp_header->message_count.get());
    checksum += bench::digest(iterator.iextp_header->stream_offset.get());
    checksum += bench::digest(iterator.iextp_header->first_message_sequence_number.get());
    checksum += bench::digest(iterator.iextp_header->send_time.get());

    std::size_t index = 0;

    while (iterator.next()) {
        checksum += index++;
        checksum += bench::digest(iterator.message_header->message_length.get());
        checksum += bench::digest(iterator.message_header->message_type.get());

        if (iterator.message_type == protocol::SystemEventMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SystemEventMessage::parse(iterator.message);
            checksum += bench::digest(message->system_event.get());
            checksum += bench::digest(message->timestamp.get());
        } else if (iterator.message_type == protocol::SecurityDirectoryMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SecurityDirectoryMessage::parse(iterator.message);
            checksum += bench::digest(message->security_directory_flags.Etp());
            checksum += bench::digest(message->security_directory_flags.WhenIssued());
            checksum += bench::digest(message->security_directory_flags.TestSecurity());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->round_lot_size.get());
            checksum += bench::digest(message->adjusted_poc_price.integer());
            checksum += bench::digest(message->luld_tier.get());
        } else if (iterator.message_type == protocol::TradingStatusMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradingStatusMessage::parse(iterator.message);
            checksum += bench::digest(message->trading_status.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->reason.get());
        } else if (iterator.message_type == protocol::OperationalHaltStatusMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OperationalHaltStatusMessage::parse(iterator.message);
            checksum += bench::digest(message->operational_halt_status.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->symbol.get());
        } else if (iterator.message_type == protocol::ShortSalePriceTestStatusMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ShortSalePriceTestStatusMessage::parse(iterator.message);
            checksum += bench::digest(message->short_sale_price_test_status.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->detail.get());
        } else if (iterator.message_type == protocol::SecurityEventMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SecurityEventMessage::parse(iterator.message);
            checksum += bench::digest(message->security_event.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->symbol.get());
        } else if (iterator.message_type == protocol::QuoteUpdateMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::QuoteUpdateMessage::parse(iterator.message);
            checksum += bench::digest(message->quote_update_flags.MarketSession());
            checksum += bench::digest(message->quote_update_flags.SymbolAvailability());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->bid_size.get());
            checksum += bench::digest(message->bid_price.integer());
            checksum += bench::digest(message->ask_price.integer());
            checksum += bench::digest(message->ask_size.get());
        } else if (iterator.message_type == protocol::TradeReportMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeReportMessage::parse(iterator.message);
            checksum += bench::digest(message->sale_condition_flags.SinglePriceCrossTrade());
            checksum += bench::digest(message->sale_condition_flags.TradeThroughExempt());
            checksum += bench::digest(message->sale_condition_flags.OddLot());
            checksum += bench::digest(message->sale_condition_flags.ExtendedHours());
            checksum += bench::digest(message->sale_condition_flags.IntermarketSweep());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->size.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->trade_id.get());
        } else if (iterator.message_type == protocol::OfficialPriceMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OfficialPriceMessage::parse(iterator.message);
            checksum += bench::digest(message->price_type.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->official_price.integer());
        } else if (iterator.message_type == protocol::TradeBreakMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeBreakMessage::parse(iterator.message);
            checksum += bench::digest(message->sale_condition_flags.SinglePriceCrossTrade());
            checksum += bench::digest(message->sale_condition_flags.TradeThroughExempt());
            checksum += bench::digest(message->sale_condition_flags.OddLot());
            checksum += bench::digest(message->sale_condition_flags.ExtendedHours());
            checksum += bench::digest(message->sale_condition_flags.IntermarketSweep());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->size.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->trade_id.get());
        } else if (iterator.message_type == protocol::AuctionInformationMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AuctionInformationMessage::parse(iterator.message);
            checksum += bench::digest(message->auction_type.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->paired_shares.get());
            checksum += bench::digest(message->reference_price.integer());
            checksum += bench::digest(message->indicative_clearing_price.integer());
            checksum += bench::digest(message->imbalance_shares.get());
            checksum += bench::digest(message->imbalance_side.get());
            checksum += bench::digest(message->extension_number.get());
            checksum += bench::digest(message->scheduled_auction_time.get());
            checksum += bench::digest(message->auction_book_clearing_price.integer());
            checksum += bench::digest(message->collar_reference_price.integer());
            checksum += bench::digest(message->lower_auction_collar.integer());
            checksum += bench::digest(message->upper_auction_collar.integer());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Iex.IexEquities.Tops.IexTp.v1.64", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
