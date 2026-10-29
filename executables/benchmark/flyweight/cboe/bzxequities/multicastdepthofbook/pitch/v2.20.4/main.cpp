// Cboe.BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/cboe/bzxequities/multicastdepthofbook/pitch/v2.20.4.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/cboe/bzxequities/multicastdepthofbook/pitch/v2.20.4/definitions.hpp"

namespace protocol = ::cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        checksum += bench::digest(packet.packet_header().length());
        checksum += bench::digest(packet.packet_header().message_count());
        checksum += bench::digest(packet.packet_header().unit());
        checksum += bench::digest(packet.packet_header().sequence());
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
        checksum += bench::digest(message.time());
    }

    void on(const protocol::UnitClearMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
    }

    void on(const protocol::AddOrderLongMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.side_indicator());
        checksum += bench::digest(message.quantity_binary_4());
        checksum += bench::digest(message.symbol_short());
        checksum += bench::digest(message.price_binary_long_price_8().mantissa());
        checksum += bench::digest(message.add_flags().display());
    }

    void on(const protocol::AddOrderShortMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.side_indicator());
        checksum += bench::digest(message.quantity_binary_2());
        checksum += bench::digest(message.symbol_short());
        checksum += bench::digest(message.price_binary_short_price_2().mantissa());
        checksum += bench::digest(message.add_flags().display());
    }

    void on(const protocol::AddOrderExpandedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.side_indicator());
        checksum += bench::digest(message.quantity_binary_4());
        checksum += bench::digest(message.symbol_long());
        checksum += bench::digest(message.price_binary_long_price_8().mantissa());
        checksum += bench::digest(message.add_flags().display());
        checksum += bench::digest(message.participant_id());
    }

    void on(const protocol::OrderExecutedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.executed_quantity());
        checksum += bench::digest(message.execution_id());
    }

    void on(const protocol::OrderExecutedAtPriceSizeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.executed_quantity());
        checksum += bench::digest(message.remaining_quantity());
        checksum += bench::digest(message.execution_id());
        checksum += bench::digest(message.price_binary_long_price_8().mantissa());
    }

    void on(const protocol::ReduceSizeLongMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.canceled_quantity_binary_4());
    }

    void on(const protocol::ReduceSizeShortMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.canceled_quantity_binary_2());
    }

    void on(const protocol::ModifyOrderLongMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.quantity_binary_4());
        checksum += bench::digest(message.price_binary_long_price_8().mantissa());
        checksum += bench::digest(message.modify_flags().display());
        checksum += bench::digest(message.modify_flags().maintain_priority());
    }

    void on(const protocol::ModifyOrderShortMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.quantity_binary_2());
        checksum += bench::digest(message.price_binary_short_price_2().mantissa());
        checksum += bench::digest(message.modify_flags().display());
        checksum += bench::digest(message.modify_flags().maintain_priority());
    }

    void on(const protocol::DeleteOrderMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
    }

    void on(const protocol::TradeLongMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.side_indicator());
        checksum += bench::digest(message.quantity_binary_4());
        checksum += bench::digest(message.symbol_short());
        checksum += bench::digest(message.price_binary_long_price_8().mantissa());
        checksum += bench::digest(message.execution_id());
    }

    void on(const protocol::TradeShortMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.side_indicator());
        checksum += bench::digest(message.quantity_binary_2());
        checksum += bench::digest(message.symbol_short());
        checksum += bench::digest(message.price_binary_short_price_2().mantissa());
        checksum += bench::digest(message.execution_id());
    }

    void on(const protocol::TradeExpandedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.side_indicator());
        checksum += bench::digest(message.quantity_binary_4());
        checksum += bench::digest(message.symbol_long());
        checksum += bench::digest(message.price_binary_long_price_8().mantissa());
        checksum += bench::digest(message.execution_id());
    }

    void on(const protocol::TradeBreakMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.execution_id());
    }

    void on(const protocol::EndOfSessionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.timestamp());
    }

    void on(const protocol::SymbolMappingMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.feed_symbol());
        checksum += bench::digest(message.osi_symbol());
        checksum += bench::digest(message.symbol_condition());
    }

    void on(const protocol::TradingStatusMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.symbol_long());
        checksum += bench::digest(message.trading_status());
        checksum += bench::digest(message.reg_sho_action());
        checksum += bench::digest(message.reserved_1());
        checksum += bench::digest(message.second_reserved_1());
    }

    void on(const protocol::AuctionUpdateMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.stock_symbol());
        checksum += bench::digest(message.auction_type());
        checksum += bench::digest(message.reference_price());
        checksum += bench::digest(message.buy_shares());
        checksum += bench::digest(message.sell_shares());
        checksum += bench::digest(message.indicative_price());
        checksum += bench::digest(message.auction_only_price());
    }

    void on(const protocol::AuctionSummaryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.stock_symbol());
        checksum += bench::digest(message.auction_type());
        checksum += bench::digest(message.price_binary_8());
        checksum += bench::digest(message.shares());
    }

    void on(const protocol::RetailPriceImprovementMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.symbol_long());
        checksum += bench::digest(message.retail_price_improvement());
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
    return bench::run("Cboe.BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
