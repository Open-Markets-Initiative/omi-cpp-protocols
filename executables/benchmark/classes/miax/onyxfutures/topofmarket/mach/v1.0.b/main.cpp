// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/miax/onyxfutures/topofmarket/mach/v1.0.b.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/classes/miax/onyxfutures/topofmarket/mach/v1.0.b/definitions.hpp"

namespace protocol = ::miax::onyxfutures::topofmarket::mach::v1_0_b;

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


    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.mach_packet_header().sequence_number());
        checksum += bench::digest(each.mach_packet_header().packet_length());
        checksum += bench::digest(each.mach_packet_header().packet_type());
        checksum += bench::digest(each.mach_packet_header().session_number());

        if (const auto* message = dynamic_cast<const protocol::ApplicationMessage*>(each.message())) {
            checksum += bench::digest((*message).message_type_field());
            if (const auto* message_2 = dynamic_cast<const protocol::SimpleInstrumentDefinitionMessage*>(message->data())) {
                checksum += bench::digest((*message_2).timestamp());
                checksum += bench::digest((*message_2).instrument_id());
                checksum += bench::digest((*message_2).underlying_asset_type());
                checksum += bench::digest((*message_2).underlying_asset());
                checksum += bench::digest((*message_2).product_group_code());
                checksum += bench::digest((*message_2).exchange());
                checksum += bench::digest((*message_2).instrument_id_source());
                checksum += bench::digest((*message_2).instrument_type());
                checksum += bench::digest((*message_2).maturity_month_year());
                checksum += bench::digest((*message_2).currency());
                checksum += bench::digest((*message_2).settlement_currency());
                checksum += bench::digest((*message_2).match_algorithm());
                checksum += bench::digest((*message_2).minimum_size());
                checksum += bench::digest((*message_2).maximum_size());
                checksum += bench::digest((*message_2).tick().mantissa());
                checksum += bench::digest((*message_2).unit_of_measure());
                checksum += bench::digest((*message_2).unit_of_measure_quantity());
                checksum += bench::digest((*message_2).settlement_price().mantissa());
                checksum += bench::digest((*message_2).settlement_price_type_calc_method());
                checksum += bench::digest((*message_2).total_volume());
                checksum += bench::digest((*message_2).open_interest_quantity());
                checksum += bench::digest((*message_2).high_limit_price().mantissa());
                checksum += bench::digest((*message_2).low_limit_price().mantissa());
                checksum += bench::digest((*message_2).trading_collar_variation_type());
                checksum += bench::digest((*message_2).trading_collar_variation().mantissa());
            } else if (const auto* message_2 = dynamic_cast<const protocol::ComplexInstrumentDefinitionMessage*>(message->data())) {
                checksum += bench::digest((*message_2).timestamp());
                checksum += bench::digest((*message_2).strategy_id());
                checksum += bench::digest((*message_2).underlying_asset_type());
                checksum += bench::digest((*message_2).underlying_asset());
                checksum += bench::digest((*message_2).product_group_code());
                checksum += bench::digest((*message_2).spread_type());
                checksum += bench::digest((*message_2).exchange());
                checksum += bench::digest((*message_2).instrument_id_source());
                checksum += bench::digest((*message_2).instrument_type());
                checksum += bench::digest((*message_2).currency());
                checksum += bench::digest((*message_2).settlement_currency());
                checksum += bench::digest((*message_2).match_algorithm());
                checksum += bench::digest((*message_2).minimum_size());
                checksum += bench::digest((*message_2).maximum_size());
                checksum += bench::digest((*message_2).tick().mantissa());
                checksum += bench::digest((*message_2).unit_of_measure());
                checksum += bench::digest((*message_2).unit_of_measure_quantity());
                checksum += bench::digest((*message_2).trading_collar_variation_type());
                checksum += bench::digest((*message_2).trading_collar_variation().mantissa());
                checksum += bench::digest((*message_2).number_of_legs());
            } else if (const auto* message_2 = dynamic_cast<const protocol::SystemStateMessage*>(message->data())) {
                checksum += bench::digest((*message_2).timestamp());
                checksum += bench::digest((*message_2).tom_version());
                checksum += bench::digest((*message_2).session_id());
                checksum += bench::digest((*message_2).system_status());
            } else if (const auto* message_2 = dynamic_cast<const protocol::InstrumentTradingStatusNotificationMessage*>(message->data())) {
                checksum += bench::digest((*message_2).timestamp());
                checksum += bench::digest((*message_2).instrument_id());
                checksum += bench::digest((*message_2).trading_status());
                checksum += bench::digest((*message_2).market_state());
            } else if (const auto* message_2 = dynamic_cast<const protocol::BestBidAndOfferMessage*>(message->data())) {
                checksum += bench::digest((*message_2).timestamp());
                checksum += bench::digest((*message_2).instrument_id());
                checksum += bench::digest((*message_2).mbb_price().mantissa());
                checksum += bench::digest((*message_2).mbb_size());
                checksum += bench::digest((*message_2).mbo_price().mantissa());
                checksum += bench::digest((*message_2).mbo_size());
            } else if (const auto* message_2 = dynamic_cast<const protocol::LastSaleMessage*>(message->data())) {
                checksum += bench::digest((*message_2).timestamp());
                checksum += bench::digest((*message_2).instrument_id());
                checksum += bench::digest((*message_2).trade_id());
                checksum += bench::digest((*message_2).price().mantissa());
                checksum += bench::digest((*message_2).size());
            } else if (const auto* message_2 = dynamic_cast<const protocol::TradeCancelMessage*>(message->data())) {
                checksum += bench::digest((*message_2).timestamp());
                checksum += bench::digest((*message_2).trade_date());
                checksum += bench::digest((*message_2).instrument_id());
                checksum += bench::digest((*message_2).trade_id());
                checksum += bench::digest((*message_2).correction_number());
                checksum += bench::digest((*message_2).price().mantissa());
                checksum += bench::digest((*message_2).size());
            }
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
