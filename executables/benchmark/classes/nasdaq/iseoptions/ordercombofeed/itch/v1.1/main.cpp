// Nasdaq.IseOptions.OrderComboFeed.Itch.v1.1 benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/iseoptions/ordercombofeed/itch/v1.1.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/classes/nasdaq/iseoptions/ordercombofeed/itch/v1.1/definitions.hpp"

namespace protocol = ::nasdaq::iseoptions::ordercombofeed::itch::v1_1;

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

        if (const auto* message = dynamic_cast<const protocol::SystemEventMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).event_code());
            checksum += bench::digest((*message).current_year());
            checksum += bench::digest((*message).current_month());
            checksum += bench::digest((*message).current_day());
            checksum += bench::digest((*message).version());
            checksum += bench::digest((*message).sub_version());
        } else if (const auto* message = dynamic_cast<const protocol::ComplexStrategyDirectoryMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).strategy_id());
            checksum += bench::digest((*message).strategy_type());
            checksum += bench::digest((*message).source());
            checksum += bench::digest((*message).underlying_symbol());
            checksum += bench::digest((*message).number_of_legs());
        } else if (const auto* message = dynamic_cast<const protocol::StrategyTradingActionMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).strategy_id());
            checksum += bench::digest((*message).current_trading_state());
        } else if (const auto* message = dynamic_cast<const protocol::StrategyOpenClosedMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).strategy_id());
            checksum += bench::digest((*message).open_state());
        } else if (const auto* message = dynamic_cast<const protocol::ComplexStrategyOrderOnBookMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).strategy_id());
            checksum += bench::digest((*message).order_type());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).size());
            checksum += bench::digest((*message).exec_flag());
            checksum += bench::digest((*message).order_capacity());
            checksum += bench::digest((*message).scope());
            checksum += bench::digest((*message).owner_id());
            checksum += bench::digest((*message).giveup());
            checksum += bench::digest((*message).cmta());
        } else if (const auto* message = dynamic_cast<const protocol::ComplexStrategyAuctionMessage*>(each.message())) {
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).strategy_id());
            checksum += bench::digest((*message).auction_id());
            checksum += bench::digest((*message).order_type());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).size());
            checksum += bench::digest((*message).exec_flag());
            checksum += bench::digest((*message).order_capacity());
            checksum += bench::digest((*message).scope());
            checksum += bench::digest((*message).owner_id());
            checksum += bench::digest((*message).giveup());
            checksum += bench::digest((*message).cmta());
            checksum += bench::digest((*message).auction_event());
            checksum += bench::digest((*message).auction_type());
            checksum += bench::digest((*message).number_of_responses());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nasdaq.IseOptions.OrderComboFeed.Itch.v1.1", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
