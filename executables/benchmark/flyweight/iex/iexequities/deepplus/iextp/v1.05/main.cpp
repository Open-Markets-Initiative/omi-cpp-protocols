// Iex.IexEquities.DeepPlus.IexTp.v1.05 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/iex/iexequities/deepplus/iextp/v1.05.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/iex/iexequities/deepplus/iextp/v1.05/definitions.hpp"

namespace protocol = ::iex::iexequities::deepplus::iextp::v1_05;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        checksum += bench::digest(packet.iextp_header().version());
        checksum += bench::digest(packet.iextp_header().message_protocol_id());
        checksum += bench::digest(packet.iextp_header().channel_id());
        checksum += bench::digest(packet.iextp_header().session_id());
        checksum += bench::digest(packet.iextp_header().payload_length());
        checksum += bench::digest(packet.iextp_header().message_count());
        checksum += bench::digest(packet.iextp_header().stream_offset());
        checksum += bench::digest(packet.iextp_header().first_message_sequence_number());
        checksum += bench::digest(packet.iextp_header().send_time());
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

    void on(const protocol::SystemEventMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.system_event());
        checksum += bench::digest(message.timestamp());
    }

    void on(const protocol::SecurityDirectoryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.security_directory_flags().etp());
        checksum += bench::digest(message.security_directory_flags().when_issued());
        checksum += bench::digest(message.security_directory_flags().test_security());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.round_lot_size());
        checksum += bench::digest(message.adjusted_poc_price().mantissa());
        checksum += bench::digest(message.luld_tier());
    }

    void on(const protocol::TradingStatusMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.trading_status());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.reason());
    }

    void on(const protocol::RetailLiquidityIndicatorMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.retail_liquidity_indicator());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.symbol());
    }

    void on(const protocol::OperationalHaltStatusMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.operational_halt_status());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.symbol());
    }

    void on(const protocol::ShortSalePriceTestStatusMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.short_sale_price_test_status());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.detail());
    }

    void on(const protocol::SecurityEventMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.security_event());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.symbol());
    }

    void on(const protocol::AddOrderMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.side());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.size());
        checksum += bench::digest(message.price().mantissa());
    }

    void on(const protocol::OrderModifyMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.modify_flags().priority());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.order_id_reference());
        checksum += bench::digest(message.size());
        checksum += bench::digest(message.price().mantissa());
    }

    void on(const protocol::OrderDeleteMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.reserved_1());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.order_id_reference());
    }

    void on(const protocol::OrderExecutedMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.sale_condition_flags().single_price_cross_trade());
        checksum += bench::digest(message.sale_condition_flags().trade_through_exempt());
        checksum += bench::digest(message.sale_condition_flags().odd_lot());
        checksum += bench::digest(message.sale_condition_flags().extended_hours());
        checksum += bench::digest(message.sale_condition_flags().intermarket_sweep());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.order_id_reference());
        checksum += bench::digest(message.size());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.trade_id());
    }

    void on(const protocol::TradeMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.sale_condition_flags().single_price_cross_trade());
        checksum += bench::digest(message.sale_condition_flags().trade_through_exempt());
        checksum += bench::digest(message.sale_condition_flags().odd_lot());
        checksum += bench::digest(message.sale_condition_flags().extended_hours());
        checksum += bench::digest(message.sale_condition_flags().intermarket_sweep());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.size());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.trade_id());
    }

    void on(const protocol::TradeBreakMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.sale_condition_flags().single_price_cross_trade());
        checksum += bench::digest(message.sale_condition_flags().trade_through_exempt());
        checksum += bench::digest(message.sale_condition_flags().odd_lot());
        checksum += bench::digest(message.sale_condition_flags().extended_hours());
        checksum += bench::digest(message.sale_condition_flags().intermarket_sweep());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.size());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.trade_id());
    }

    void on(const protocol::ClearBookMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.reserved_1());
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.symbol());
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
    return bench::run("Iex.IexEquities.DeepPlus.IexTp.v1.05", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
