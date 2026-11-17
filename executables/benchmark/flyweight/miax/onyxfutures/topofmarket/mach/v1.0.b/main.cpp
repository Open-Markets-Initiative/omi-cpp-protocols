// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: main.cpp
// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/miax/onyxfutures/topofmarket/mach/v1.0.b.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/miax/onyxfutures/topofmarket/mach/v1.0.b/definitions.hpp"

namespace protocol = ::miax::onyxfutures::topofmarket::mach::v1_0_b;

namespace {

// The messages Data selects, their values set in the entry of the message holding it
struct DataHandler {
    std::uint64_t& checksum;

    void on(const protocol::SimpleInstrumentDefinitionMessage& message) {
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.instrument_id());
        checksum += bench::digest(message.underlying_asset_type());
        checksum += bench::digest(message.underlying_asset());
        checksum += bench::digest(message.product_group_code());
        checksum += bench::digest(message.exchange());
        checksum += bench::digest(message.instrument_id_source());
        checksum += bench::digest(message.instrument_type());
        checksum += bench::digest(message.maturity_month_year());
        checksum += bench::digest(message.currency());
        checksum += bench::digest(message.settlement_currency());
        checksum += bench::digest(message.match_algorithm());
        checksum += bench::digest(message.minimum_size_field());
        checksum += bench::digest(message.maximum_size());
        checksum += bench::digest(message.tick().mantissa());
        checksum += bench::digest(message.unit_of_measure());
        checksum += bench::digest(message.unit_of_measure_quantity());
        checksum += bench::digest(message.settlement_price().mantissa());
        checksum += bench::digest(message.settlement_price_type_calc_method());
        checksum += bench::digest(message.total_volume());
        checksum += bench::digest(message.open_interest_quantity());
        checksum += bench::digest(message.high_limit_price().mantissa());
        checksum += bench::digest(message.low_limit_price().mantissa());
        checksum += bench::digest(message.trading_collar_variation_type());
        checksum += bench::digest(message.trading_collar_variation().mantissa());
    }

    void on(const protocol::ComplexInstrumentDefinitionMessage& message) {
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.strategy_id());
        checksum += bench::digest(message.underlying_asset_type());
        checksum += bench::digest(message.underlying_asset());
        checksum += bench::digest(message.product_group_code());
        checksum += bench::digest(message.spread_type());
        checksum += bench::digest(message.exchange());
        checksum += bench::digest(message.instrument_id_source());
        checksum += bench::digest(message.instrument_type());
        checksum += bench::digest(message.currency());
        checksum += bench::digest(message.settlement_currency());
        checksum += bench::digest(message.match_algorithm());
        checksum += bench::digest(message.minimum_size_field());
        checksum += bench::digest(message.maximum_size());
        checksum += bench::digest(message.tick().mantissa());
        checksum += bench::digest(message.unit_of_measure());
        checksum += bench::digest(message.unit_of_measure_quantity());
        checksum += bench::digest(message.trading_collar_variation_type());
        checksum += bench::digest(message.trading_collar_variation().mantissa());
        checksum += bench::digest(message.number_of_legs());
    }

    void on(const protocol::SystemStateMessage& message) {
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.tom_version());
        checksum += bench::digest(message.session_id());
        checksum += bench::digest(message.system_status());
    }

    void on(const protocol::InstrumentTradingStatusNotificationMessage& message) {
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.instrument_id());
        checksum += bench::digest(message.trading_status());
        checksum += bench::digest(message.market_state());
    }

    void on(const protocol::BestBidAndOfferMessage& message) {
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.instrument_id());
        checksum += (message.mbb_price().has_value() ? bench::digest((*message.mbb_price()).mantissa()) : std::uint64_t{0});
        checksum += bench::digest(message.mbb_size());
        checksum += (message.mbo_price().has_value() ? bench::digest((*message.mbo_price()).mantissa()) : std::uint64_t{0});
        checksum += bench::digest(message.mbo_size());
    }

    void on(const protocol::LastSaleMessage& message) {
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.instrument_id());
        checksum += bench::digest(message.trade_id());
        checksum += bench::digest(message.price().mantissa());
        checksum += bench::digest(message.size());
    }

    void on(const protocol::TradeCancelMessage& message) {
        checksum += bench::digest(message.timestamp());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.instrument_id());
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
    return bench::run("Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
