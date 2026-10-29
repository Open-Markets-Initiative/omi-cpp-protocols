// Jnx.JnxEquities.Pts.Itch.v1.7 benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/jnx/jnxequities/pts/itch/v1.7.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/classes/jnx/jnxequities/pts/itch/v1.7/definitions.hpp"

namespace protocol = ::jnx::jnxequities::pts::itch::v1_7;

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

        if (const auto* message = dynamic_cast<const protocol::UdpPayloadSecondsMessage*>(each.message())) {
            checksum += bench::digest((*message).seconds());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadSystemEventMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).group());
            checksum += bench::digest((*message).system_event());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadPriceTickSizeMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).price_tick_size_table_id());
            checksum += bench::digest((*message).price_tick_size().mantissa());
            checksum += bench::digest((*message).price_start().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadOrderbookDirectoryMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).orderbook_id());
            checksum += bench::digest((*message).orderbook_code());
            checksum += bench::digest((*message).group());
            checksum += bench::digest((*message).round_lot_size());
            checksum += bench::digest((*message).price_tick_size_table_id());
            checksum += bench::digest((*message).price_decimals());
            checksum += bench::digest((*message).upper_price_limit().mantissa());
            checksum += bench::digest((*message).lower_price_limit().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadTradingStateMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).orderbook_id());
            checksum += bench::digest((*message).group());
            checksum += bench::digest((*message).trading_state());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadShortSellingPriceRestrictionStateMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).orderbook_id());
            checksum += bench::digest((*message).group());
            checksum += bench::digest((*message).short_selling_state());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadOrderAddedWithoutAttributesMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).order_number());
            checksum += bench::digest((*message).buy_sell_indicator());
            checksum += bench::digest((*message).quantity());
            checksum += bench::digest((*message).orderbook_id());
            checksum += bench::digest((*message).group());
            checksum += bench::digest((*message).price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadOrderAddedWithAttributesMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).order_number());
            checksum += bench::digest((*message).buy_sell_indicator());
            checksum += bench::digest((*message).quantity());
            checksum += bench::digest((*message).orderbook_id());
            checksum += bench::digest((*message).group());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).attribution());
            checksum += bench::digest((*message).order_type());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadOrderExecutedMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).order_number());
            checksum += bench::digest((*message).executed_quantity());
            checksum += bench::digest((*message).match_number());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadOrderDeletedMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).order_number());
        } else if (const auto* message = dynamic_cast<const protocol::UdpPayloadOrderReplacedMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).original_order_number());
            checksum += bench::digest((*message).new_order_number());
            checksum += bench::digest((*message).quantity());
            checksum += bench::digest((*message).price().mantissa());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Jnx.JnxEquities.Pts.Itch.v1.7", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
