// Lseg.Lse.Level2Mbo.Gtp.v26.2: main.cpp
// Lseg.Lse.Level2Mbo.Gtp.v26.2 benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/lseg/lse/level2mbo/gtp/v26.2.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/lseg/lse/level2mbo/gtp/v26.2/definitions.hpp"

namespace protocol = ::lseg::lse::level2mbo::gtp::v26_2;

namespace {

// The values the Modern iterator reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    checksum += bench::digest(iterator.unit_header->length.get());
    checksum += bench::digest(iterator.unit_header->message_count.get());
    checksum += bench::digest(iterator.unit_header->market_data_group.get());
    checksum += bench::digest(iterator.unit_header->sequence_number.get());

    std::size_t index = 0;

    while (iterator.next()) {
        checksum += index++;
        checksum += bench::digest(iterator.message_header->message_length.get());
        checksum += bench::digest(iterator.message_header->message_type.get());

        if (iterator.message_type == protocol::SystemEventMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SystemEventMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->source_venue.get());
        } else if (iterator.message_type == protocol::InstrumentDirectoryMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::InstrumentDirectoryMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->instrument.get());
            checksum += bench::digest(message->allowed_book_types.FirmQuoteBook());
            checksum += bench::digest(message->allowed_book_types.OffBook());
            checksum += bench::digest(message->allowed_book_types.ElectronicOrderBook());
            checksum += bench::digest(message->allowed_book_types.PrivateRfq());
            checksum += bench::digest(message->source_venue.get());
            checksum += bench::digest(message->dynamic_circuit_breaker_tolerances.integer());
            checksum += bench::digest(message->static_circuit_breaker_tolerances.integer());
            checksum += bench::digest(message->average_daily_turnover_adt.integer());
        } else if (iterator.message_type == protocol::InstrumentStatusMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::InstrumentStatusMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->instrument.get());
            checksum += bench::digest(message->source_venue.get());
            checksum += bench::digest(message->session_change_reason.get());
            checksum += bench::digest(message->order_book_type.get());
        } else if (iterator.message_type == protocol::AddOrderMboMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddOrderMboMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->size.integer());
            checksum += bench::digest(message->instrument.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->source_venue.get());
            checksum += bench::digest(message->order_book_type.get());
            checksum += bench::digest(message->depth.get());
        } else if (iterator.message_type == protocol::AddOrderShortMboMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddOrderShortMboMessage::parse(iterator.message);
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->size.integer());
            checksum += bench::digest(message->price.integer());
        } else if (iterator.message_type == protocol::OrderBookClearMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderBookClearMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->source_venue.get());
            checksum += bench::digest(message->instrument.get());
            checksum += bench::digest(message->order_book_type.get());
        } else if (iterator.message_type == protocol::TradeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->transaction_time.get());
            checksum += bench::digest(message->source_venue.get());
            checksum += bench::digest(message->executed_size.integer());
            checksum += bench::digest(message->instrument.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->trade_id.get());
            checksum += bench::digest(message->trade_type.get());
            checksum += bench::digest(message->trade_flags.TradeCancellation());
            checksum += bench::digest(message->trade_flags.TradeCorrection());
            checksum += bench::digest(message->hidden_execution_indicator.get());
        } else if (iterator.message_type == protocol::StatisticsMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::StatisticsMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->instrument.get());
            checksum += bench::digest(message->source_venue.get());
            checksum += bench::digest(message->volume.integer());
            checksum += bench::digest(message->volume_on_book_only.integer());
            checksum += bench::digest(message->vwap.integer());
            checksum += bench::digest(message->vwap_on_book_only.integer());
            checksum += bench::digest(message->number_of_trades.get());
            checksum += bench::digest(message->number_of_trades_on_book_only.get());
            checksum += bench::digest(message->turnover.integer());
            checksum += bench::digest(message->turnover_on_book_only.integer());
        } else if (iterator.message_type == protocol::StatisticsUpdateMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::StatisticsUpdateMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->instrument.get());
            checksum += bench::digest(message->source_venue.get());
            checksum += bench::digest(message->statistic_type.get());
            checksum += bench::digest(message->statistic_price.integer());
            checksum += bench::digest(message->statistic_size.integer());
            checksum += bench::digest(message->imbalance_quantity.integer());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Lseg.Lse.Level2Mbo.Gtp.v26.2", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
