// Cboe.EdgxOptions.MulticastDepthOfBook.Pitch.v2.41.80 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/definitions.hpp"

namespace protocol = ::cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80;

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

    void on(const protocol::TransactionBeginMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
    }

    void on(const protocol::TransactionEndMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
    }

    void on(const protocol::AddOrderLongMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.side_indicator());
        checksum += bench::digest(message.quantity_long());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.price_long().mantissa());
        checksum += bench::digest(message.add_flags().aon());
    }

    void on(const protocol::AddOrderShortMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.side_indicator());
        checksum += bench::digest(message.quantity_short());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.price_short().mantissa());
        checksum += bench::digest(message.add_flags().aon());
    }

    void on(const protocol::AddOrderExpandedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.side_indicator());
        checksum += bench::digest(message.quantity_long());
        checksum += bench::digest(message.expanded_symbol());
        checksum += bench::digest(message.price_long().mantissa());
        checksum += bench::digest(message.add_flags().aon());
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.customer_indicator());
        checksum += bench::digest(message.client_id());
    }

    void on(const protocol::OrderExecutedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.executed_quantity());
        checksum += bench::digest(message.execution_id());
        checksum += bench::digest(message.trade_condition());
    }

    void on(const protocol::OrderExecutedAtPriceSizeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.executed_quantity());
        checksum += bench::digest(message.remaining_quantity());
        checksum += bench::digest(message.execution_id());
        checksum += bench::digest(message.price_long().mantissa());
        checksum += bench::digest(message.trade_condition());
    }

    void on(const protocol::ReduceSizeLongMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.canceled_quantity_long());
    }

    void on(const protocol::ReduceSizeShortMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.canceled_quantity_short());
    }

    void on(const protocol::ModifyOrderLongMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.quantity_long());
        checksum += bench::digest(message.price_long().mantissa());
        checksum += bench::digest(message.modify_flags().display());
        checksum += bench::digest(message.modify_flags().maintain_priority());
    }

    void on(const protocol::ModifyOrderShortMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.quantity_short());
        checksum += bench::digest(message.price_short().mantissa());
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
        checksum += bench::digest(message.quantity_long());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.price_long().mantissa());
        checksum += bench::digest(message.execution_id());
        checksum += bench::digest(message.trade_condition());
    }

    void on(const protocol::TradeShortMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.side_indicator());
        checksum += bench::digest(message.quantity_short());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.price_short().mantissa());
        checksum += bench::digest(message.execution_id());
        checksum += bench::digest(message.trade_condition());
    }

    void on(const protocol::TradeExpandedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.side_indicator());
        checksum += bench::digest(message.quantity_long());
        checksum += bench::digest(message.expanded_symbol());
        checksum += bench::digest(message.price_long().mantissa());
        checksum += bench::digest(message.execution_id());
        checksum += bench::digest(message.trade_condition());
    }

    void on(const protocol::TradeBreakMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.execution_id());
    }

    void on(const protocol::EndOfSessionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
    }

    void on(const protocol::SymbolMappingMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.feed_symbol());
        checksum += bench::digest(message.osi_symbol());
        checksum += bench::digest(message.symbol_condition());
        checksum += bench::digest(message.underlying());
    }

    void on(const protocol::TradingStatusMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.trading_status());
        checksum += bench::digest(message.gth_trading_status());
    }

    void on(const protocol::WidthUpdateMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.underlying());
        checksum += bench::digest(message.width_type());
        checksum += bench::digest(message.multiplier().mantissa());
    }

    void on(const protocol::OptionsAuctionUpdateMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.expanded_symbol());
        checksum += bench::digest(message.auction_type());
        checksum += bench::digest(message.reference_price().mantissa());
        checksum += bench::digest(message.buy_contracts());
        checksum += bench::digest(message.sell_contracts());
        checksum += bench::digest(message.indicative_price().mantissa());
        checksum += bench::digest(message.auction_only_price().mantissa());
        checksum += bench::digest(message.opening_condition());
        checksum += bench::digest(message.composite_market_bid_price().mantissa());
        checksum += bench::digest(message.composite_market_offer_price().mantissa());
    }

    void on(const protocol::AuctionSummaryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.stock_symbol());
        checksum += bench::digest(message.auction_type());
        checksum += bench::digest(message.price_long().mantissa());
        checksum += bench::digest(message.shares_contracts());
    }

    void on(const protocol::AuctionNotificationMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.auction_id());
        checksum += bench::digest(message.auction_type());
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.price_long().mantissa());
        checksum += bench::digest(message.contracts());
        checksum += bench::digest(message.customer_indicator());
        checksum += bench::digest(message.participant_id());
        checksum += bench::digest(message.auction_end_offset());
        checksum += bench::digest(message.client_id());
    }

    void on(const protocol::AuctionCancelMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.auction_id());
    }

    void on(const protocol::AuctionTradeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.auction_id());
        checksum += bench::digest(message.execution_id());
        checksum += bench::digest(message.price_long().mantissa());
        checksum += bench::digest(message.contracts());
    }

    void on(const protocol::SoqStrikeRangeUpdateMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.soq_identifier());
        checksum += bench::digest(message.lower_strike_price().mantissa());
        checksum += bench::digest(message.upper_strike_price().mantissa());
    }

    void on(const protocol::ConstituentSymbolMappingMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.feed_symbol());
        checksum += bench::digest(message.osi_symbol());
        checksum += bench::digest(message.symbol_condition());
        checksum += bench::digest(message.underlying());
        checksum += bench::digest(message.soq_identifier());
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
    return bench::run("Cboe.EdgxOptions.MulticastDepthOfBook.Pitch.v2.41.80", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
