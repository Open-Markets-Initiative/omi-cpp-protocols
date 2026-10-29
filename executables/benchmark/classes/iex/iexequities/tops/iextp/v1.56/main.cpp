// Iex.IexEquities.Tops.IexTp.v1.56 benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/iex/iexequities/tops/iextp/v1.56.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/classes/iex/iexequities/tops/iextp/v1.56/definitions.hpp"

namespace protocol = ::iex::iexequities::tops::iextp::v1_56;

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

    checksum += bench::digest(packet.iextp_header().version());
    checksum += bench::digest(packet.iextp_header().message_protocol_id());
    checksum += bench::digest(packet.iextp_header().channel_id());
    checksum += bench::digest(packet.iextp_header().session_id());
    checksum += bench::digest(packet.iextp_header().payload_length());
    checksum += bench::digest(packet.iextp_header().message_count());
    checksum += bench::digest(packet.iextp_header().stream_offset());
    checksum += bench::digest(packet.iextp_header().first_message_sequence_number());
    checksum += bench::digest(packet.iextp_header().send_time());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.message_header().message_length());
        checksum += bench::digest(each.message_header().message_type());

        if (const auto* message = dynamic_cast<const protocol::QuoteUpdateMessage*>(each.message())) {
            checksum += bench::digest((*message).quote_update_flags().market_session());
            checksum += bench::digest((*message).quote_update_flags().symbol_availability());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).bid_size());
            checksum += bench::digest((*message).bid_price().mantissa());
            checksum += bench::digest((*message).ask_price().mantissa());
            checksum += bench::digest((*message).ask_size());
        } else if (const auto* message = dynamic_cast<const protocol::TradeReportMessage*>(each.message())) {
            checksum += bench::digest((*message).sale_condition_flags().trade_through_exempt());
            checksum += bench::digest((*message).sale_condition_flags().odd_lot());
            checksum += bench::digest((*message).sale_condition_flags().extended_hours());
            checksum += bench::digest((*message).sale_condition_flags().intermarket_sweep());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).size());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).trade_id());
            checksum += bench::digest((*message).reserved_4());
        } else if (const auto* message = dynamic_cast<const protocol::TradeBreakMessage*>(each.message())) {
            checksum += bench::digest((*message).sale_condition_flags().trade_through_exempt());
            checksum += bench::digest((*message).sale_condition_flags().odd_lot());
            checksum += bench::digest((*message).sale_condition_flags().extended_hours());
            checksum += bench::digest((*message).sale_condition_flags().intermarket_sweep());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).size());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).trade_id());
            checksum += bench::digest((*message).reserved_4());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Iex.IexEquities.Tops.IexTp.v1.56", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
