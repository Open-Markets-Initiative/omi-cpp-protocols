// Nasdaq.PhlxOptions.TopOfMarket.Itch.v3.4 benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/phlxoptions/topofmarket/itch/v3.4.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/classes/nasdaq/phlxoptions/topofmarket/itch/v3.4/definitions.hpp"

namespace protocol = ::nasdaq::phlxoptions::topofmarket::itch::v3_4;

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
            checksum += bench::digest((*message).version());
            checksum += bench::digest((*message).sub_version());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadOptionsDirectoryMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).option_id());
            checksum += bench::digest((*message).security_symbol());
            checksum += bench::digest((*message).expiration_year());
            checksum += bench::digest((*message).expiration_month());
            checksum += bench::digest((*message).expiration_day());
            checksum += bench::digest((*message).strike_price().mantissa());
            checksum += bench::digest((*message).option_type());
            checksum += bench::digest((*message).source());
            checksum += bench::digest((*message).underlying_symbol());
            checksum += bench::digest((*message).option_closing_type());
            checksum += bench::digest((*message).tradable());
            checksum += bench::digest((*message).mpv());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadTradingActionMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).option_id());
            checksum += bench::digest((*message).current_trading_state());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadSecurityOpenClosedMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).option_id());
            checksum += bench::digest((*message).open_state());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadShortBestBidAndAskUpdateMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).option_id());
            checksum += bench::digest((*message).quote_condition());
            checksum += bench::digest((*message).bid_price_2().mantissa());
            checksum += bench::digest((*message).bid_size_2());
            checksum += bench::digest((*message).ask_price_2().mantissa());
            checksum += bench::digest((*message).ask_size_2());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadLongBestBidAndAskUpdateMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).option_id());
            checksum += bench::digest((*message).quote_condition());
            checksum += bench::digest((*message).bid_price_4().mantissa());
            checksum += bench::digest((*message).bid_size_4());
            checksum += bench::digest((*message).ask_price_4().mantissa());
            checksum += bench::digest((*message).ask_size_4());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadShortBestAskUpdateMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).option_id());
            checksum += bench::digest((*message).quote_condition());
            checksum += bench::digest((*message).price_2().mantissa());
            checksum += bench::digest((*message).size_2());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadShortBestBidUpdateMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).option_id());
            checksum += bench::digest((*message).quote_condition());
            checksum += bench::digest((*message).price_2().mantissa());
            checksum += bench::digest((*message).size_2());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadLongBestAskUpdateMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).option_id());
            checksum += bench::digest((*message).quote_condition());
            checksum += bench::digest((*message).price_4().mantissa());
            checksum += bench::digest((*message).size_4());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadLongBestBidUpdateMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).option_id());
            checksum += bench::digest((*message).quote_condition());
            checksum += bench::digest((*message).price_4().mantissa());
            checksum += bench::digest((*message).size_4());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadTradeReportMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).option_id());
            checksum += bench::digest((*message).cross_id());
            checksum += bench::digest((*message).trade_condition());
            checksum += bench::digest((*message).price_4().mantissa());
            checksum += bench::digest((*message).volume());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadBrokenTradeReportMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).option_id());
            checksum += bench::digest((*message).original_cross_id());
            checksum += bench::digest((*message).original_price().mantissa());
            checksum += bench::digest((*message).original_volume());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nasdaq.PhlxOptions.TopOfMarket.Itch.v3.4", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
