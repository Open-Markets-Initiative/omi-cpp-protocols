// Cboe.CfeFutures.MulticastDepthOfBook.Pitch.v1.2.22 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/definitions.hpp"

namespace protocol = ::cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22;

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

    void on(const protocol::TimeReferenceMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.midnight_reference());
        checksum += bench::digest(message.time_reference());
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.trade_date());
    }

    void on(const protocol::TimeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_reference());
        checksum += bench::digest(message.epoch_time());
    }

    void on(const protocol::UnitClearMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
    }

    void on(const protocol::FuturesInstrumentDefinitionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.unit_timestamp());
        checksum += bench::digest(message.report_symbol());
        checksum += bench::digest(message.futures_flags().variance());
        checksum += bench::digest(message.expiration_date());
        checksum += bench::digest(message.contract_size());
        checksum += bench::digest(message.listing_state());
        checksum += bench::digest(message.price_increment().mantissa());
        checksum += bench::digest(message.leg_count());
        checksum += bench::digest(message.leg_offset());
        checksum += bench::digest(message.reserved_1());
        checksum += bench::digest(message.contract_date());
    }

    void on(const protocol::FuturesVarianceSymbolMappingMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.unit_timestamp());
        checksum += bench::digest(message.feed_symbol());
        checksum += bench::digest(message.futures_symbol());
        checksum += bench::digest(message.accrued_day_variance().mantissa());
        checksum += bench::digest(message.num_final_returns());
        checksum += bench::digest(message.num_elapsed_returns());
    }

    void on(const protocol::PriceLimitsMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.upper_price_limit().mantissa());
        checksum += bench::digest(message.lower_price_limit().mantissa());
    }

    void on(const protocol::AddOrderLongMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.side_indicator());
        checksum += bench::digest(message.quantity_long());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.price_long().mantissa());
    }

    void on(const protocol::AddOrderShortMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.side_indicator());
        checksum += bench::digest(message.quantity_short());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.price_short().mantissa());
    }

    void on(const protocol::OrderExecutedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.executed_quantity());
        checksum += bench::digest(message.execution_id());
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

    void on(const protocol::TransactionBeginMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
    }

    void on(const protocol::TransactionEndMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
    }

    void on(const protocol::TradeBreakMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.execution_id());
    }

    void on(const protocol::SettlementMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.settlement_price().mantissa());
        checksum += bench::digest(message.issue());
    }

    void on(const protocol::OpenInterestMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.open_interest());
    }

    void on(const protocol::EndOfDaySummaryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.open_interest());
        checksum += bench::digest(message.high_price().mantissa());
        checksum += bench::digest(message.low_price().mantissa());
        checksum += bench::digest(message.open_price().mantissa());
        checksum += bench::digest(message.close_price().mantissa());
        checksum += bench::digest(message.total_volume());
        checksum += bench::digest(message.block_volume());
        checksum += bench::digest(message.ecrp_volume());
        checksum += bench::digest(message.summary_flags().high_price_valid());
        checksum += bench::digest(message.summary_flags().high_price_is_bid());
        checksum += bench::digest(message.summary_flags().low_price_valid());
        checksum += bench::digest(message.summary_flags().low_price_is_offer());
        checksum += bench::digest(message.summary_flags().open_close_valid());
    }

    void on(const protocol::TradingStatusMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.time_offset());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.reserved_2());
        checksum += bench::digest(message.trading_status());
        checksum += bench::digest(message.reserved_3());
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
    return bench::run("Cboe.CfeFutures.MulticastDepthOfBook.Pitch.v1.2.22", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
