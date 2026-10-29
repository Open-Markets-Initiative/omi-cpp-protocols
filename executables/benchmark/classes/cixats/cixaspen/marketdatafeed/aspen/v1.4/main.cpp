// CixAts.CixAspen.MarketDataFeed.Aspen.v1.4 benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/cixats/cixaspen/marketdatafeed/aspen/v1.4.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "executables/benchmark/Benchmark.hpp"
#include "cpp/binary/classes/cixats/cixaspen/marketdatafeed/aspen/v1.4/definitions.hpp"

namespace protocol = ::cixats::cixaspen::marketdatafeed::aspen::v1_4;

namespace {

// The values the Classes Packet decodes from one datagram, folded into a checksum. A datagram it cannot
// decode is a value the model never reads, so the benchmark refuses to time it.
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::Packet packet;

    try {
        packet.decode(frame.payload, frame.payload_len);
    } catch (const protocol::DecodeError& error) {
        throw;
        return checksum;
    }

    checksum += bench::digest(packet.packet_header().market_day_identifier());
    checksum += bench::digest(packet.packet_header().feed_identifier());
    checksum += bench::digest(packet.packet_header().sequence());
    checksum += bench::digest(packet.packet_header().count());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.message_header().length());
        checksum += bench::digest(each.message_header().message_type());

        if (const auto* message = dynamic_cast<const protocol::MarketEventMessage*>(each.message())) {
            checksum += bench::digest((*message).reserved_2());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).event());
        } else if (const auto* message = dynamic_cast<const protocol::SymbolInformationMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).symbol_id());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).listing_market());
            checksum += bench::digest((*message).board_lot_size());
        } else if (const auto* message = dynamic_cast<const protocol::SymbolStateMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).symbol_id());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).state());
            checksum += bench::digest((*message).reserved_1());
            checksum += bench::digest((*message).info());
        } else if (const auto* message = dynamic_cast<const protocol::NewOrderAddMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).symbol_id());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).quantity().mantissa());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).broker());
            checksum += bench::digest((*message).reserved_1());
        } else if (const auto* message = dynamic_cast<const protocol::OrderPartialCancelMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).quantity_canceled().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::OrderCancelAllMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).order_id());
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).quantity().mantissa());
            checksum += bench::digest((*message).execution_id());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).broker());
            checksum += bench::digest((*message).contra_broker());
        } else if (const auto* message = dynamic_cast<const protocol::TradeMessage*>(each.message())) {
            checksum += bench::digest((*message).symbol_id());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).reserved_8());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).shares().mantissa());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).execution_id());
            checksum += bench::digest((*message).broker());
            checksum += bench::digest((*message).contra_broker());
        } else if (const auto* message = dynamic_cast<const protocol::TradeCancelMessage*>(each.message())) {
            checksum += bench::digest((*message).symbol_id());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).reserved_8());
            checksum += bench::digest((*message).reserved_1());
            checksum += bench::digest((*message).shares().mantissa());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).execution_id());
            checksum += bench::digest((*message).broker());
            checksum += bench::digest((*message).contra_broker());
        } else if (const auto* message = dynamic_cast<const protocol::TradeCorrectMessage*>(each.message())) {
            checksum += bench::digest((*message).symbol_id());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).reserved_8());
            checksum += bench::digest((*message).reserved_1());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).execution_id());
            checksum += bench::digest((*message).broker());
            checksum += bench::digest((*message).contra_broker());
            checksum += bench::digest((*message).original_execution_id());
            checksum += bench::digest((*message).original_trade_price().mantissa());
            checksum += bench::digest((*message).original_trade_quantity().mantissa());
            checksum += bench::digest((*message).corrected_trade_price().mantissa());
            checksum += bench::digest((*message).corrected_trade_quantity().mantissa());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("CixAts.CixAspen.MarketDataFeed.Aspen.v1.4", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
