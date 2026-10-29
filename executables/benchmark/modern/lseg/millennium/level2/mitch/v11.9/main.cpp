// Lseg.Millennium.Level2.Mitch.v11.9 benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/lseg/millennium/level2/mitch/v11.9.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/lseg/millennium/level2/mitch/v11.9/definitions.hpp"

namespace protocol = ::lseg::millennium::level2::mitch::v11_9;

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

        if (iterator.message_type == protocol::TimeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TimeMessage::parse(iterator.message);
            checksum += bench::digest(message->seconds.get());
        } else if (iterator.message_type == protocol::SystemEventMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SystemEventMessage::parse(iterator.message);
            checksum += bench::digest(message->nanosecond.get());
            checksum += bench::digest(message->event_code.get());
        } else if (iterator.message_type == protocol::SymbolDirectoryMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SymbolDirectoryMessage::parse(iterator.message);
            checksum += bench::digest(message->nanosecond.get());
            checksum += bench::digest(message->instrument_id.get());
            checksum += bench::digest(message->symbol_status.get());
            checksum += bench::digest(message->isin.get());
            checksum += bench::digest(message->sedol.get());
            checksum += bench::digest(message->segment.get());
            checksum += bench::digest(message->underlying.get());
            checksum += bench::digest(message->currency.get());
            checksum += bench::digest(message->previous_close_price.get());
        } else if (iterator.message_type == protocol::SymbolStatusMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SymbolStatusMessage::parse(iterator.message);
            checksum += bench::digest(message->nanosecond.get());
            checksum += bench::digest(message->instrument_id.get());
            checksum += bench::digest(message->trading_status.get());
            checksum += bench::digest(message->symbol_status_flags.FirmQuote());
            checksum += bench::digest(message->reason.get());
            checksum += bench::digest(message->session_change_reason.get());
            checksum += bench::digest(message->new_end_time.get());
            checksum += bench::digest(message->book_type.get());
        } else if (iterator.message_type == protocol::AddOrderMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddOrderMessage::parse(iterator.message);
            checksum += bench::digest(message->nanosecond.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->quantity.get());
            checksum += bench::digest(message->instrument_id.get());
            checksum += bench::digest(message->price.get());
            checksum += bench::digest(message->add_order_flags.MarketOrder());
            checksum += bench::digest(message->add_order_flags.Unused1());
            checksum += bench::digest(message->add_order_flags.PrivateRfq());
            checksum += bench::digest(message->add_order_flags.SecondUnused1());
        } else if (iterator.message_type == protocol::AddAttributedOrderMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddAttributedOrderMessage::parse(iterator.message);
            checksum += bench::digest(message->nanosecond.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->quantity.get());
            checksum += bench::digest(message->instrument_id.get());
            checksum += bench::digest(message->price.get());
            checksum += bench::digest(message->attribution.get());
            checksum += bench::digest(message->add_attributed_order_flags.NamedMarketOrder());
            checksum += bench::digest(message->add_attributed_order_flags.FirmQuote());
        } else if (iterator.message_type == protocol::OrderDeletedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderDeletedMessage::parse(iterator.message);
            checksum += bench::digest(message->nanosecond.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->order_deleted_flags.FirmQuote());
            checksum += bench::digest(message->instrument_id.get());
        } else if (iterator.message_type == protocol::OrderModifiedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderModifiedMessage::parse(iterator.message);
            checksum += bench::digest(message->nanosecond.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->new_quantity.get());
            checksum += bench::digest(message->new_price.get());
            checksum += bench::digest(message->order_modified_flags.PriorityFlag());
            checksum += bench::digest(message->order_modified_flags.FirmQuote());
        } else if (iterator.message_type == protocol::OrderBookClearMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderBookClearMessage::parse(iterator.message);
            checksum += bench::digest(message->nanosecond.get());
            checksum += bench::digest(message->instrument_id.get());
            checksum += bench::digest(message->order_book_clear_flags.FirmQuote());
            checksum += bench::digest(message->order_book_clear_flags.PrivateRfq());
            checksum += bench::digest(message->order_book_clear_flags.Unused1());
        } else if (iterator.message_type == protocol::OrderExecutedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderExecutedMessage::parse(iterator.message);
            checksum += bench::digest(message->nanosecond.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->executed_quantity.get());
            checksum += bench::digest(message->trade_match_id.get());
        } else if (iterator.message_type == protocol::OrderExecutedWithPriceSizeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderExecutedWithPriceSizeMessage::parse(iterator.message);
            checksum += bench::digest(message->nanosecond.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->executed_quantity.get());
            checksum += bench::digest(message->display_quantity.get());
            checksum += bench::digest(message->trade_match_id.get());
            checksum += bench::digest(message->printable.get());
            checksum += bench::digest(message->price.get());
        } else if (iterator.message_type == protocol::TradeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeMessage::parse(iterator.message);
            checksum += bench::digest(message->nanosecond.get());
            checksum += bench::digest(message->executed_quantity.get());
            checksum += bench::digest(message->instrument_id.get());
            checksum += bench::digest(message->price.get());
            checksum += bench::digest(message->trade_match_id.get());
            checksum += (static_cast<std::uint8_t>(message->cross_type.get()) != 0x0U ? bench::digest(message->cross_type.get()) : std::uint64_t{0});
            checksum += bench::digest(message->sub_book.get());
            checksum += bench::digest(message->pt_mod_flags.Canc());
            checksum += bench::digest(message->pt_mod_flags.Amnd());
        } else if (iterator.message_type == protocol::AuctionTradeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AuctionTradeMessage::parse(iterator.message);
            checksum += bench::digest(message->nanosecond.get());
            checksum += bench::digest(message->quantity.get());
            checksum += bench::digest(message->instrument_id.get());
            checksum += bench::digest(message->price.get());
            checksum += bench::digest(message->trade_match_id.get());
            checksum += bench::digest(message->auction_type.get());
            checksum += bench::digest(message->pt_mod_flags.Canc());
            checksum += bench::digest(message->pt_mod_flags.Amnd());
        } else if (iterator.message_type == protocol::AuctionInfoMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AuctionInfoMessage::parse(iterator.message);
            checksum += bench::digest(message->nanosecond.get());
            checksum += bench::digest(message->paired_quantity.get());
            checksum += bench::digest(message->instrument_id.get());
            checksum += bench::digest(message->price.get());
            checksum += bench::digest(message->auction_type.get());
        } else if (iterator.message_type == protocol::StatisticsMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::StatisticsMessage::parse(iterator.message);
            checksum += bench::digest(message->nanosecond.get());
            checksum += bench::digest(message->instrument_id.get());
            checksum += bench::digest(message->statistic_type.get());
            checksum += bench::digest(message->price.get());
            checksum += bench::digest(message->open_close_price_indicator.get());
        } else if (iterator.message_type == protocol::TopOfBookMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TopOfBookMessage::parse(iterator.message);
            checksum += bench::digest(message->nanosecond.get());
            checksum += bench::digest(message->instrument_id.get());
            checksum += bench::digest(message->buy_limit_price.get());
            checksum += bench::digest(message->buy_limit_size.get());
            checksum += bench::digest(message->sell_limit_price.get());
            checksum += bench::digest(message->sell_limit_size.get());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Lseg.Millennium.Level2.Mitch.v11.9", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
