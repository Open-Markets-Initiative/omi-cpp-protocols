// Jpx.TseEquities.MarketByOrder.Flex.v1.1 benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/jpx/tseequities/marketbyorder/flex/v1.1.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/classes/jpx/tseequities/marketbyorder/flex/v1.1/definitions.hpp"

namespace protocol = ::jpx::tseequities::marketbyorder::flex::v1_1;

namespace {

// The values the Classes Packet decodes from one datagram, folded into a checksum. A datagram it cannot
// decode is a value the model never reads, so the benchmark refuses to time it.
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::UdpPacket packet;

    try {
        packet.decode(frame.payload, frame.payload_len);
    } catch (const protocol::DecodeError& error) {
        throw;
        return checksum;
    }

    checksum += bench::digest(packet.packet_header().multicast_group_number());
    checksum += bench::digest(packet.packet_header().number_of_system_reboots());
    checksum += bench::digest(packet.packet_header().sequence_number());
    checksum += bench::digest(packet.packet_header().issue_code());
    checksum += bench::digest(packet.packet_header().update_number());
    checksum += bench::digest(packet.packet_header().packet_number());
    checksum += bench::digest(packet.packet_header().total_number_of_packets());
    checksum += bench::digest(packet.packet_header().utility_flag());
    checksum += bench::digest(packet.packet_header().message_count());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.message_header().tag_length());
        checksum += bench::digest(each.message_header().message_type());

        if (const auto* message = dynamic_cast<const protocol::SecondsTimestampMessage*>(each.message())) {
            checksum += bench::digest((*message).time_seconds());
        } else if (const auto* message = dynamic_cast<const protocol::TradingStatusMessage*>(each.message())) {
            checksum += bench::digest((*message).time_microseconds());
            checksum += bench::digest((*message).market_status());
            checksum += bench::digest((*message).status_flag());
            checksum += bench::digest((*message).short_selling_status());
            checksum += bench::digest((*message).pricing_method());
            checksum += bench::digest((*message).book_center_price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::ExecutionSummaryMessage*>(each.message())) {
            checksum += bench::digest((*message).time_microseconds());
            checksum += bench::digest((*message).triggered_side());
            checksum += bench::digest((*message).total_volume());
            checksum += bench::digest((*message).total_invalidation());
            checksum += bench::digest((*message).last_price().mantissa());
            checksum += bench::digest((*message).match_id());
            checksum += ((*message).best_offer().has_value() ? bench::digest((*(*message).best_offer()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).best_bid().has_value() ? bench::digest((*(*message).best_bid()).mantissa()) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderMessage*>(each.message())) {
            checksum += bench::digest((*message).time_microseconds());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).quantity());
            checksum += ((*message).price().has_value() ? bench::digest((*(*message).price()).mantissa()) : std::uint64_t{0});
            checksum += bench::digest((*message).order_condition());
            checksum += bench::digest((*message).modification_flag());
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedMessage*>(each.message())) {
            checksum += bench::digest((*message).time_microseconds());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).volume());
            checksum += bench::digest((*message).match_id());
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedWithPriceMessage*>(each.message())) {
            checksum += bench::digest((*message).time_microseconds());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).volume());
            checksum += bench::digest((*message).match_id());
            checksum += bench::digest((*message).execution_price().mantissa());
            checksum += bench::digest((*message).adopted_pricing_method());
        } else if (const auto* message = dynamic_cast<const protocol::OrderDeleteMessage*>(each.message())) {
            checksum += bench::digest((*message).time_microseconds());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).modification_flag());
        } else if (const auto* message = dynamic_cast<const protocol::ResetMessage*>(each.message())) {
            checksum += bench::digest((*message).reset_start_end_flag());
        } else if (const auto* message = dynamic_cast<const protocol::CommunicationControlMessage*>(each.message())) {
            checksum += bench::digest((*message).test_mode_flag());
            checksum += bench::digest((*message).communication_start_end_flag());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Jpx.TseEquities.MarketByOrder.Flex.v1.1", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
