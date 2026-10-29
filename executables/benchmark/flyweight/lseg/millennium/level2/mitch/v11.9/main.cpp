// Lseg.Millennium.Level2.Mitch.v11.9 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/lseg/millennium/level2/mitch/v11.9.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/lseg/millennium/level2/mitch/v11.9/definitions.hpp"

namespace protocol = ::lseg::millennium::level2::mitch::v11_9;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        checksum += bench::digest(packet.unit_header().length());
        checksum += bench::digest(packet.unit_header().message_count());
        checksum += bench::digest(packet.unit_header().market_data_group());
        checksum += bench::digest(packet.unit_header().sequence_number());
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

    void on(const protocol::TimeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.seconds());
    }

    void on(const protocol::SystemEventMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanosecond());
        checksum += bench::digest(message.event_code());
    }

    void on(const protocol::SymbolDirectoryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanosecond());
        checksum += bench::digest(message.instrument_id());
        checksum += bench::digest(message.symbol_status());
        checksum += bench::digest(message.isin());
        checksum += bench::digest(message.sedol());
        checksum += bench::digest(message.segment());
        checksum += bench::digest(message.underlying());
        checksum += bench::digest(message.currency());
        checksum += bench::digest(message.previous_close_price());
    }

    void on(const protocol::SymbolStatusMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanosecond());
        checksum += bench::digest(message.instrument_id());
        checksum += bench::digest(message.trading_status());
        checksum += bench::digest(message.symbol_status_flags().unused_5());
        checksum += bench::digest(message.symbol_status_flags().firm_quote());
        checksum += bench::digest(message.symbol_status_flags().unused_2());
        checksum += bench::digest(message.reason());
        checksum += bench::digest(message.session_change_reason());
        checksum += bench::digest(message.new_end_time());
        checksum += bench::digest(message.book_type());
    }

    void on(const protocol::AddOrderMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanosecond());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.quantity());
        checksum += bench::digest(message.instrument_id());
        checksum += bench::digest(message.price());
        checksum += bench::digest(message.add_order_flags().unused_4());
        checksum += bench::digest(message.add_order_flags().market_order());
        checksum += bench::digest(message.add_order_flags().unused_1());
        checksum += bench::digest(message.add_order_flags().private_rfq());
        checksum += bench::digest(message.add_order_flags().second_unused_1());
    }

    void on(const protocol::AddAttributedOrderMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanosecond());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.quantity());
        checksum += bench::digest(message.instrument_id());
        checksum += bench::digest(message.price());
        checksum += bench::digest(message.attribution());
        checksum += bench::digest(message.add_attributed_order_flags().unused_4());
        checksum += bench::digest(message.add_attributed_order_flags().named_market_order());
        checksum += bench::digest(message.add_attributed_order_flags().firm_quote());
        checksum += bench::digest(message.add_attributed_order_flags().unused_2());
    }

    void on(const protocol::OrderDeletedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanosecond());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.order_deleted_flags().unused_5());
        checksum += bench::digest(message.order_deleted_flags().firm_quote());
        checksum += bench::digest(message.order_deleted_flags().unused_2());
        checksum += bench::digest(message.instrument_id());
    }

    void on(const protocol::OrderModifiedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanosecond());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.new_quantity());
        checksum += bench::digest(message.new_price());
        checksum += bench::digest(message.order_modified_flags().priority_flag());
        checksum += bench::digest(message.order_modified_flags().unused_4());
        checksum += bench::digest(message.order_modified_flags().firm_quote());
        checksum += bench::digest(message.order_modified_flags().unused_2());
    }

    void on(const protocol::OrderBookClearMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanosecond());
        checksum += bench::digest(message.instrument_id());
        checksum += bench::digest(message.order_book_clear_flags().unused_5());
        checksum += bench::digest(message.order_book_clear_flags().firm_quote());
        checksum += bench::digest(message.order_book_clear_flags().private_rfq());
        checksum += bench::digest(message.order_book_clear_flags().unused_1());
    }

    void on(const protocol::OrderExecutedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanosecond());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.executed_quantity());
        checksum += bench::digest(message.trade_match_id());
    }

    void on(const protocol::OrderExecutedWithPriceSizeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanosecond());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.executed_quantity());
        checksum += bench::digest(message.display_quantity());
        checksum += bench::digest(message.trade_match_id());
        checksum += bench::digest(message.printable());
        checksum += bench::digest(message.price());
    }

    void on(const protocol::TradeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanosecond());
        checksum += bench::digest(message.executed_quantity());
        checksum += bench::digest(message.instrument_id());
        checksum += bench::digest(message.price());
        checksum += bench::digest(message.trade_match_id());
        checksum += (message.cross_type().has_value() ? bench::digest((*message.cross_type())) : std::uint64_t{0});
        checksum += bench::digest(message.sub_book());
        checksum += bench::digest(message.pt_mod_flags().canc());
        checksum += bench::digest(message.pt_mod_flags().amnd());
        checksum += bench::digest(message.pt_mod_flags().unused_6());
    }

    void on(const protocol::AuctionTradeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanosecond());
        checksum += bench::digest(message.quantity());
        checksum += bench::digest(message.instrument_id());
        checksum += bench::digest(message.price());
        checksum += bench::digest(message.trade_match_id());
        checksum += bench::digest(message.auction_type());
        checksum += bench::digest(message.pt_mod_flags().canc());
        checksum += bench::digest(message.pt_mod_flags().amnd());
        checksum += bench::digest(message.pt_mod_flags().unused_6());
    }

    void on(const protocol::AuctionInfoMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanosecond());
        checksum += bench::digest(message.paired_quantity());
        checksum += bench::digest(message.instrument_id());
        checksum += bench::digest(message.price());
        checksum += bench::digest(message.auction_type());
    }

    void on(const protocol::StatisticsMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanosecond());
        checksum += bench::digest(message.instrument_id());
        checksum += bench::digest(message.statistic_type());
        checksum += bench::digest(message.price());
        checksum += bench::digest(message.open_close_price_indicator());
        checksum += bench::digest(message.statistics_reserved().unused_8());
    }

    void on(const protocol::TopOfBookMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.nanosecond());
        checksum += bench::digest(message.instrument_id());
        checksum += bench::digest(message.buy_limit_price());
        checksum += bench::digest(message.buy_limit_size());
        checksum += bench::digest(message.sell_limit_price());
        checksum += bench::digest(message.sell_limit_size());
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
    return bench::run("Lseg.Millennium.Level2.Mitch.v11.9", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
