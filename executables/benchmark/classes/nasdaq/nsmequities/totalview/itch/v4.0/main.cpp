// Nasdaq.NsmEquities.TotalView.Itch.v4.0 benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/nsmequities/totalview/itch/v4.0.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/classes/nasdaq/nsmequities/totalview/itch/v4.0/definitions.hpp"

namespace protocol = ::nasdaq::nsmequities::totalview::itch::v4_0;

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

    checksum += bench::digest(packet.packet_header().session());
    checksum += bench::digest(packet.packet_header().sequence_number());
    checksum += bench::digest(packet.packet_header().message_count());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.message_header().message_length());
        checksum += bench::digest(each.message_header().message_type());

        if (const auto* message = dynamic_cast<const protocol::PayloadTimestampMessage*>(each.message())) {
            checksum += bench::digest((*message).second());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadSystemEventMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).event_code());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadStockDirectoryMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).market_category());
            checksum += bench::digest((*message).financial_status_indicator());
            checksum += bench::digest((*message).round_lot_size());
            checksum += bench::digest((*message).round_lots_only());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadStockTradingActionMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).trading_state());
            checksum += bench::digest((*message).reserved());
            checksum += bench::digest((*message).reason());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadMarketParticipantPositionMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).mpid());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).primary_market_maker());
            checksum += bench::digest((*message).market_maker_mode());
            checksum += bench::digest((*message).market_participant_state());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadAddOrderMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).order_reference_number());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).shares());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadAddOrderWithMpidMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).order_reference_number());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).shares());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).attribution());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadOrderExecutedMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).order_reference_number());
            checksum += bench::digest((*message).executed_shares());
            checksum += bench::digest((*message).match_number());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadOrderExecutedWithPriceMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).order_reference_number());
            checksum += bench::digest((*message).executed_shares());
            checksum += bench::digest((*message).match_number());
            checksum += bench::digest((*message).printable());
            checksum += bench::digest((*message).execution_price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadOrderCancelMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).order_reference_number());
            checksum += bench::digest((*message).canceled_shares());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadOrderDeleteMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).order_reference_number());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadOrderReplaceMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).original_order_reference_number());
            checksum += bench::digest((*message).new_order_reference_number());
            checksum += bench::digest((*message).shares());
            checksum += bench::digest((*message).price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadTradeMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).order_reference_number());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).shares());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).match_number());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadCrossTradeMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).cross_shares());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).cross_price().mantissa());
            checksum += bench::digest((*message).match_number());
            checksum += bench::digest((*message).cross_type());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadBrokenTradeMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).match_number());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadNetOrderImbalanceIndicatorMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).paired_shares());
            checksum += bench::digest((*message).imbalance_shares());
            checksum += bench::digest((*message).imbalance_direction());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).far_price().mantissa());
            checksum += bench::digest((*message).near_price().mantissa());
            checksum += bench::digest((*message).current_reference_price().mantissa());
            checksum += bench::digest((*message).cross_type());
            checksum += bench::digest((*message).price_variation_indicator());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nasdaq.NsmEquities.TotalView.Itch.v4.0", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
