// Miax.MiaxOptions.TopOfMarket.Mach.v2.5 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/miax/miaxoptions/topofmarket/mach/v2.5.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/miax/miaxoptions/topofmarket/mach/v2.5/definitions.hpp"

namespace protocol = ::miax::miaxoptions::topofmarket::mach::v2_5;

namespace {

// The messages Data selects, their values set in the entry of the message holding it
struct DataHandler {
    std::uint64_t& checksum;

    void on(const protocol::SystemTimeMessage& message) {
        checksum += bench::digest(message.seconds());
    }

    void on(const protocol::SimpleSeriesUpdateMessage& message) {
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

    void on(const protocol::SystemStateMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.to_m_version());
        checksum += bench::digest(message.session_id());
        checksum += bench::digest(message.system_status());
    }

    void on(const protocol::SimpleTopOfMarketBestBidOrOfferCompactBidMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.product_id());
        checksum += bench::digest(message.mbbo_price_short().mantissa());
        checksum += bench::digest(message.mbbo_size_short());
        checksum += bench::digest(message.mbbo_priority_customer_size_short());
        checksum += bench::digest(message.mbbo_condition());
    }

    void on(const protocol::SimpleTopOfMarketBestBidOrOfferCompactOfferMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.product_id());
        checksum += bench::digest(message.mbbo_price_short().mantissa());
        checksum += bench::digest(message.mbbo_size_short());
        checksum += bench::digest(message.mbbo_priority_customer_size_short());
        checksum += bench::digest(message.mbbo_condition());
    }

    void on(const protocol::SimpleTopOfMarketBestBidOrOfferWideBidMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.product_id());
        checksum += bench::digest(message.mbbo_price_long().mantissa());
        checksum += bench::digest(message.mbbo_size_long());
        checksum += bench::digest(message.mbbo_priority_customer_size_long());
        checksum += bench::digest(message.mbbo_condition());
    }

    void on(const protocol::SimpleTopOfMarketBestBidOrOfferWideOfferMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.product_id());
        checksum += bench::digest(message.mbbo_price_long().mantissa());
        checksum += bench::digest(message.mbbo_size_long());
        checksum += bench::digest(message.mbbo_priority_customer_size_long());
        checksum += bench::digest(message.mbbo_condition());
    }

    void on(const protocol::SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.product_id());
        checksum += bench::digest(message.bid_price_short().mantissa());
        checksum += bench::digest(message.bid_size_short());
        checksum += bench::digest(message.bid_priority_customer_size_short());
        checksum += bench::digest(message.bid_condition());
        checksum += bench::digest(message.offer_price_short().mantissa());
        checksum += bench::digest(message.offer_size_short());
        checksum += bench::digest(message.offer_priority_customer_size_short());
        checksum += bench::digest(message.offer_condition());
    }

    void on(const protocol::SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.product_id());
        checksum += bench::digest(message.bid_price_long().mantissa());
        checksum += bench::digest(message.bid_size_long());
        checksum += bench::digest(message.bid_priority_customer_size_long());
        checksum += bench::digest(message.bid_condition());
        checksum += bench::digest(message.offer_price_long().mantissa());
        checksum += bench::digest(message.offer_size_long());
        checksum += bench::digest(message.offer_priority_customer_size_long());
        checksum += bench::digest(message.offer_condition());
    }

    void on(const protocol::LastSaleMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.product_id());
        checksum += bench::digest(message.trade_id());
        checksum += bench::digest(message.correction_number());
        checksum += bench::digest(message.reference_trade_id());
        checksum += bench::digest(message.reference_correction_number());
        checksum += bench::digest(message.trade_price().mantissa());
        checksum += bench::digest(message.trade_size());
        checksum += bench::digest(message.trade_condition());
    }

    void on(const protocol::TradeCancelMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.product_id());
        checksum += bench::digest(message.trade_id());
        checksum += bench::digest(message.correction_number());
        checksum += bench::digest(message.trade_price().mantissa());
        checksum += bench::digest(message.trade_size());
        checksum += bench::digest(message.trade_condition());
    }

    void on(const protocol::UnderlyingTradingStatusNotificationMessage& message) {
        checksum += bench::digest(message.nanoseconds());
        checksum += bench::digest(message.underlying_symbol());
        checksum += bench::digest(message.trading_status());
        checksum += bench::digest(message.event_reason());
        checksum += bench::digest(message.expected_event_time_seconds_part());
        checksum += bench::digest(message.expected_event_time_nano_seconds_part());
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
    return bench::run("Miax.MiaxOptions.TopOfMarket.Mach.v2.5", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
