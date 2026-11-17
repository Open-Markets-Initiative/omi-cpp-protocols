// Lseg.Lse.Level2Mbo.Gtp.v26.2: main.cpp
// Lseg.Lse.Level2Mbo.Gtp.v26.2 benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/lseg/lse/level2mbo/gtp/v26.2.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/classes/lseg/lse/level2mbo/gtp/v26.2/definitions.hpp"

namespace protocol = ::lseg::lse::level2mbo::gtp::v26_2;

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

    checksum += bench::digest(packet.unit_header().length());
    checksum += bench::digest(packet.unit_header().message_count());
    checksum += bench::digest(packet.unit_header().market_data_group());
    checksum += bench::digest(packet.unit_header().sequence_number());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.message_header().message_length());
        checksum += bench::digest(each.message_header().message_type());

        if (const auto* message = dynamic_cast<const protocol::SystemEventMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).source_venue());
        } else if (const auto* message = dynamic_cast<const protocol::InstrumentDirectoryMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).instrument());
            checksum += bench::digest((*message).allowed_book_types().firm_quote_book());
            checksum += bench::digest((*message).allowed_book_types().off_book());
            checksum += bench::digest((*message).allowed_book_types().electronic_order_book());
            checksum += bench::digest((*message).allowed_book_types().private_rfq());
            checksum += bench::digest((*message).source_venue());
            checksum += bench::digest((*message).dynamic_circuit_breaker_tolerances().mantissa());
            checksum += bench::digest((*message).static_circuit_breaker_tolerances().mantissa());
            checksum += bench::digest((*message).average_daily_turnover_adt().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::InstrumentStatusMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).instrument());
            checksum += bench::digest((*message).source_venue());
            checksum += bench::digest((*message).session_change_reason());
            checksum += bench::digest((*message).order_book_type());
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderMboMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).size().mantissa());
            checksum += bench::digest((*message).instrument());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).source_venue());
            checksum += bench::digest((*message).order_book_type());
            checksum += bench::digest((*message).depth());
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderShortMboMessage*>(each.message())) {
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).size().mantissa());
            checksum += bench::digest((*message).price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::OrderBookClearMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).source_venue());
            checksum += bench::digest((*message).instrument());
            checksum += bench::digest((*message).order_book_type());
        } else if (const auto* message = dynamic_cast<const protocol::TradeMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).transaction_time());
            checksum += bench::digest((*message).source_venue());
            checksum += bench::digest((*message).executed_size().mantissa());
            checksum += bench::digest((*message).instrument());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).trade_id());
            checksum += bench::digest((*message).trade_type());
            checksum += bench::digest((*message).trade_flags().trade_cancellation());
            checksum += bench::digest((*message).trade_flags().trade_correction());
            checksum += bench::digest((*message).hidden_execution_indicator());
        } else if (const auto* message = dynamic_cast<const protocol::StatisticsMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).instrument());
            checksum += bench::digest((*message).source_venue());
            checksum += bench::digest((*message).volume().mantissa());
            checksum += bench::digest((*message).volume_on_book_only().mantissa());
            checksum += bench::digest((*message).vwap().mantissa());
            checksum += bench::digest((*message).vwap_on_book_only().mantissa());
            checksum += bench::digest((*message).number_of_trades());
            checksum += bench::digest((*message).number_of_trades_on_book_only());
            checksum += bench::digest((*message).turnover().mantissa());
            checksum += bench::digest((*message).turnover_on_book_only().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::StatisticsUpdateMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).instrument());
            checksum += bench::digest((*message).source_venue());
            checksum += bench::digest((*message).statistic_type());
            checksum += bench::digest((*message).statistic_price().mantissa());
            checksum += bench::digest((*message).statistic_size().mantissa());
            checksum += bench::digest((*message).imbalance_quantity().mantissa());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Lseg.Lse.Level2Mbo.Gtp.v26.2", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
