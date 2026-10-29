// Iex.IexEquities.Tops.IexTp.v1.56 benchmark, through the Modern iterator: every value it reads from every message of the simulated
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
#include "cpp/binary/modern/iex/iexequities/tops/iextp/v1.56/definitions.hpp"

namespace protocol = ::iex::iexequities::tops::iextp::v1_56;

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

        if (iterator.message_type == protocol::QuoteUpdateMessage::message_type) {
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
            checksum += bench::digest(message->sale_condition_flags.TradeThroughExempt());
            checksum += bench::digest(message->sale_condition_flags.OddLot());
            checksum += bench::digest(message->sale_condition_flags.ExtendedHours());
            checksum += bench::digest(message->sale_condition_flags.IntermarketSweep());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->size.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->trade_id.get());
            checksum += bench::digest(message->reserved_4.get());
        } else if (iterator.message_type == protocol::TradeBreakMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeBreakMessage::parse(iterator.message);
            checksum += bench::digest(message->sale_condition_flags.TradeThroughExempt());
            checksum += bench::digest(message->sale_condition_flags.OddLot());
            checksum += bench::digest(message->sale_condition_flags.ExtendedHours());
            checksum += bench::digest(message->sale_condition_flags.IntermarketSweep());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->size.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->trade_id.get());
            checksum += bench::digest(message->reserved_4.get());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Iex.IexEquities.Tops.IexTp.v1.56", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
