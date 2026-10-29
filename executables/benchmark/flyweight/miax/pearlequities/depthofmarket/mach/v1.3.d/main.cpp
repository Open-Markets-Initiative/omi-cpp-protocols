// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/miax/pearlequities/depthofmarket/mach/v1.3.d.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/miax/pearlequities/depthofmarket/mach/v1.3.d/definitions.hpp"

namespace protocol = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

namespace {

// The messages Data selects, their values set in the entry of the message holding it
struct DataHandler {
    std::uint64_t& checksum;

    void on(const protocol::SystemTimeMessage& message) {
        checksum += bench::digest(message.seconds());
    }

    void on(const protocol::SymbolUpdateMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.symbol_id());
        checksum += bench::digest(message.ticker_symbol());
        checksum += bench::digest(message.test_security_indicator());
        checksum += bench::digest(message.lot_size());
        checksum += bench::digest(message.opening_time());
        checksum += bench::digest(message.closing_time());
        checksum += bench::digest(message.primary_market_code());
    }

    void on(const protocol::SystemStateMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.do_m_version());
        checksum += bench::digest(message.session_id());
        checksum += bench::digest(message.system_status());
    }

    void on(const protocol::SecurityTradingStatusNotificationMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.symbol_id());
        checksum += bench::digest(message.trading_status());
        checksum += bench::digest(message.market_state());
        checksum += bench::digest(message.short_sale_restriction());
    }

    void on(const protocol::SymbolClearMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.symbol_id());
    }

    void on(const protocol::AddOrderMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.symbol_id());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.order_side());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.size());
        checksum += bench::digest(message.attributable_id());
    }

    void on(const protocol::ModifyOrderMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.symbol_id());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.size());
        checksum += bench::digest(message.modify_order_flags().order_position());
    }

    void on(const protocol::DeleteOrderMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.symbol_id());
        checksum += bench::digest(message.order_id());
    }

    void on(const protocol::OrderExecutionMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.symbol_id());
        checksum += bench::digest(message.order_id());
        checksum += bench::digest(message.trade_id());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.size());
        checksum += bench::digest(message.order_execution_flags().sip_reporting());
        checksum += bench::digest(message.order_execution_flags().traded_against_retail());
    }

    void on(const protocol::TradeMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.symbol_id());
        checksum += bench::digest(message.trade_id());
        checksum += bench::digest(message.correction_number());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.size());
        checksum += bench::digest(message.trade_flags().sip_reporting());
        checksum += bench::digest(message.trade_flags().retail_trade_indicator());
    }

    void on(const protocol::TradeCancelMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.symbol_id());
        checksum += bench::digest(message.trade_id());
        checksum += bench::digest(message.correction_number());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.size());
    }
};

// The handler the reader hands each datagram's views to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    void on(const protocol::UdpPacket&) {
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

    void on(const protocol::ApplicationMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.message_type());
        DataHandler selected{ checksum };
        message.data(selected);
    }
};

// The values the Flyweight reader reads from one datagram, folded into a checksum. A datagram it cannot
// read is a value the model never reads, so the benchmark refuses to time it.
std::uint64_t read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::UdpPacketReader::read(std::span<const std::byte>(frame.payload, frame.payload_len), reader);
    } catch (const protocol::DecodeError& error) {
        throw;
    }

    return reader.checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
