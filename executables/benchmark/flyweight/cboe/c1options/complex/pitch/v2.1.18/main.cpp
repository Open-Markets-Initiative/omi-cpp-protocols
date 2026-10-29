// Cboe.C1Options.Complex.Pitch.v2.1.18 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/cboe/c1options/complex/pitch/v2.1.18.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/cboe/c1options/complex/pitch/v2.1.18/definitions.hpp"

namespace protocol = ::cboe::c1options::complex::pitch::v2_1_18;

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

    void on(const protocol::TransactionBegin& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
    }

    void on(const protocol::TransactionEndMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
    }

    void on(const protocol::ComplexInstrumentDefinitionExpandedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.complex_instrument_id());
        checksum += bench::digest(message.complex_instrument_underlying());
        checksum += bench::digest(message.complex_instrument_type());
        checksum += bench::digest(message.leg_count());
    }

    void on(const protocol::SymbolMappingMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.feed_symbol());
        checksum += bench::digest(message.osi_symbol());
        checksum += bench::digest(message.symbol_condition());
        checksum += bench::digest(message.underlying());
    }

    void on(const protocol::AddOrderLongMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.side_indicator());
        checksum += bench::digest(message.quantity());
        checksum += bench::digest(message.complex_instrument_id());
        checksum += bench::digest(message.price().mantissa());
    }

    void on(const protocol::AddOrderShortMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.side_indicator());
        checksum += bench::digest(message.quantity_short());
        checksum += bench::digest(message.complex_instrument_id());
        checksum += bench::digest(message.price_short().mantissa());
    }

    void on(const protocol::AddOrderExpandedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.side_indicator());
        checksum += bench::digest(message.quantity());
        checksum += bench::digest(message.complex_instrument_id_8());
        checksum += bench::digest(message.price().mantissa());
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
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.trade_condition());
    }

    void on(const protocol::ReduceSizeLongMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.canceled_quantity());
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
        checksum += bench::digest(message.quantity());
        checksum += bench::digest(message.price().mantissa());
    }

    void on(const protocol::ModifyOrderShortMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.quantity_short());
        checksum += bench::digest(message.price_short().mantissa());
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
        checksum += bench::digest(message.quantity());
        checksum += bench::digest(message.complex_instrument_id());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.execution_id());
        checksum += bench::digest(message.trade_condition());
    }

    void on(const protocol::TradeShortMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.side_indicator());
        checksum += bench::digest(message.quantity_short());
        checksum += bench::digest(message.complex_instrument_id());
        checksum += bench::digest(message.price_short().mantissa());
        checksum += bench::digest(message.execution_id());
        checksum += bench::digest(message.trade_condition());
    }

    void on(const protocol::AuctionNotificationMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.complex_instrument_id());
        checksum += bench::digest(message.auction_id());
        checksum += bench::digest(message.auction_type());
        checksum += bench::digest(message.side_indicator());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.quantity());
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
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.quantity());
    }

    void on(const protocol::TradingStatusMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.complex_symbol_id());
        checksum += bench::digest(message.trading_status());
        checksum += bench::digest(message.gth_trading_status());
    }

    void on(const protocol::AuctionUpdateMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.complex_instrument_id_8());
        checksum += bench::digest(message.auction_opening_type());
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
        checksum += bench::digest(message.complex_instrument_id_8());
        checksum += bench::digest(message.auction_opening_type());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.quantity());
    }

    void on(const protocol::EndOfSessionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
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
    return bench::run("Cboe.C1Options.Complex.Pitch.v2.1.18", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
