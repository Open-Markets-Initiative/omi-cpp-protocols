// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/miax/miaxoptions/complextopofmarket/mach/v1.1.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/miax/miaxoptions/complextopofmarket/mach/v1.1/definitions.hpp"

namespace protocol = ::miax::miaxoptions::complextopofmarket::mach::v1_1;

namespace {

// The messages Data selects, their values set in the entry of the message holding it
struct DataHandler {
    std::uint64_t& checksum;

    void on(const protocol::SystemTimeMessage& message) {
        checksum += bench::digest(message.seconds());
    }

    void on(const protocol::SeriesUpdate& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.product_id());
        checksum += bench::digest(message.underlying_symbol());
        checksum += bench::digest(message.security_symbol());
        checksum += bench::digest(message.expiration_date());
        checksum += bench::digest(message.strike_price().mantissa());
        checksum += bench::digest(message.call_or_put());
        checksum += bench::digest(message.opening_time());
        checksum += bench::digest(message.closing_time());
        checksum += bench::digest(message.restricted_option());
        checksum += bench::digest(message.long_term_option());
        checksum += bench::digest(message.active_on_miax());
        checksum += bench::digest(message.miax_bbo_posting_increment_indicator());
        checksum += bench::digest(message.liquidity_acceptance_increment_indicator());
        checksum += bench::digest(message.opening_underlying_market_code());
        checksum += bench::digest(message.priority_quote_width().mantissa());
    }

    void on(const protocol::ComplexStrategyDefinitionMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.strategy_id());
        checksum += bench::digest(message.underlying_symbol());
        checksum += bench::digest(message.active_on_miax());
        checksum += bench::digest(message.update_reason());
        checksum += bench::digest(message.number_of_legs());
    }

    void on(const protocol::SystemStateMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.c_to_m_version());
        checksum += bench::digest(message.session_id());
        checksum += bench::digest(message.system_status());
    }

    void on(const protocol::CompactComplexTopOfMarketBidMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.strategy_id());
        checksum += bench::digest(message.compact_price().mantissa());
        checksum += bench::digest(message.compact_size());
        checksum += bench::digest(message.top_of_market_quote_condition());
    }

    void on(const protocol::CompactComplexTopOfMarketOfferMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.strategy_id());
        checksum += bench::digest(message.compact_price().mantissa());
        checksum += bench::digest(message.compact_size());
        checksum += bench::digest(message.top_of_market_quote_condition());
    }

    void on(const protocol::WideComplexTopOfMarketBidMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.strategy_id());
        checksum += bench::digest(message.wide_price().mantissa());
        checksum += bench::digest(message.wide_size());
        checksum += bench::digest(message.top_of_market_quote_condition());
    }

    void on(const protocol::WideComplexTopOfMarketOfferMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.strategy_id());
        checksum += bench::digest(message.wide_price().mantissa());
        checksum += bench::digest(message.wide_size());
        checksum += bench::digest(message.top_of_market_quote_condition());
    }

    void on(const protocol::CompactComplexDoubleSidedTopOfMarketMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.strategy_id());
        checksum += bench::digest(message.compact_bid().compact_bid_price().mantissa());
        checksum += bench::digest(message.compact_bid().compact_bid_size());
        checksum += bench::digest(message.compact_bid().bid_condition());
        checksum += bench::digest(message.compact_offer().compact_offer_price().mantissa());
        checksum += bench::digest(message.compact_offer().compact_offer_size());
        checksum += bench::digest(message.compact_offer().offer_condition());
    }

    void on(const protocol::WideComplexDoubleSidedTopOfMarketMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.strategy_id());
        checksum += bench::digest(message.wide_bid().wide_bid_price().mantissa());
        checksum += bench::digest(message.wide_bid().wide_bid_size());
        checksum += bench::digest(message.wide_bid().bid_condition());
        checksum += bench::digest(message.wide_offer().wide_offer_price().mantissa());
        checksum += bench::digest(message.wide_offer().wide_offer_size());
        checksum += bench::digest(message.wide_offer().offer_condition());
    }

    void on(const protocol::StrategyTradeMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.strategy_id());
        checksum += bench::digest(message.trade_id());
        checksum += bench::digest(message.net_price().mantissa());
        checksum += bench::digest(message.trade_size());
        checksum += bench::digest(message.trade_condition());
    }

    void on(const protocol::UnderlyingTradingStatusMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.underlying_symbol());
        checksum += bench::digest(message.trading_status());
        checksum += bench::digest(message.event_reason());
        checksum += bench::digest(message.seconds_part());
        checksum += bench::digest(message.expected_event_time_nano_seconds_part());
    }
};

// The handler the reader hands each datagram's views to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    void on(const protocol::Packet&) {
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
        protocol::PacketReader::read(std::span<const std::byte>(frame.payload, frame.payload_len), reader);
    } catch (const protocol::DecodeError& error) {
        throw;
    }

    return reader.checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
