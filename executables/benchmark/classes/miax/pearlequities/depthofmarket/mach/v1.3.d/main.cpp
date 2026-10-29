// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/miax/pearlequities/depthofmarket/mach/v1.3.d.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/classes/miax/pearlequities/depthofmarket/mach/v1.3.d/definitions.hpp"

namespace protocol = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

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


    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.mach_packet_header().sequence_number());
        checksum += bench::digest(each.mach_packet_header().mach_packet_length());
        checksum += bench::digest(each.mach_packet_header().mach_packet_type());
        checksum += bench::digest(each.mach_packet_header().session_number());

        if (const auto* message = dynamic_cast<const protocol::ApplicationMessage*>(each.message())) {
            checksum += bench::digest((*message).message_type_field());
            if (const auto* message_2 = dynamic_cast<const protocol::SystemTimeMessage*>(message->data())) {
                checksum += bench::digest((*message_2).seconds());
            } else if (const auto* message_2 = dynamic_cast<const protocol::SymbolUpdateMessage*>(message->data())) {
                checksum += bench::digest((*message_2).nanoseconds());
                checksum += bench::digest((*message_2).symbol_id());
                checksum += bench::digest((*message_2).ticker_symbol());
                checksum += bench::digest((*message_2).test_security_indicator());
                checksum += bench::digest((*message_2).lot_size());
                checksum += bench::digest((*message_2).opening_time());
                checksum += bench::digest((*message_2).closing_time());
                checksum += bench::digest((*message_2).primary_market_code());
            } else if (const auto* message_2 = dynamic_cast<const protocol::SystemStateMessage*>(message->data())) {
                checksum += bench::digest((*message_2).nanoseconds());
                checksum += bench::digest((*message_2).do_m_version());
                checksum += bench::digest((*message_2).session_id());
                checksum += bench::digest((*message_2).system_status());
            } else if (const auto* message_2 = dynamic_cast<const protocol::SecurityTradingStatusNotificationMessage*>(message->data())) {
                checksum += bench::digest((*message_2).nanoseconds());
                checksum += bench::digest((*message_2).symbol_id());
                checksum += bench::digest((*message_2).trading_status());
                checksum += bench::digest((*message_2).market_state());
                checksum += bench::digest((*message_2).short_sale_restriction());
            } else if (const auto* message_2 = dynamic_cast<const protocol::SymbolClearMessage*>(message->data())) {
                checksum += bench::digest((*message_2).nanoseconds());
                checksum += bench::digest((*message_2).symbol_id());
            } else if (const auto* message_2 = dynamic_cast<const protocol::AddOrderMessage*>(message->data())) {
                checksum += bench::digest((*message_2).nanoseconds());
                checksum += bench::digest((*message_2).symbol_id());
                checksum += bench::digest((*message_2).order_id());
                checksum += bench::digest((*message_2).order_side());
                checksum += bench::digest((*message_2).price().mantissa());
                checksum += bench::digest((*message_2).size());
                checksum += bench::digest((*message_2).attributable_id());
            } else if (const auto* message_2 = dynamic_cast<const protocol::ModifyOrderMessage*>(message->data())) {
                checksum += bench::digest((*message_2).nanoseconds());
                checksum += bench::digest((*message_2).symbol_id());
                checksum += bench::digest((*message_2).order_id());
                checksum += bench::digest((*message_2).price().mantissa());
                checksum += bench::digest((*message_2).size());
                checksum += bench::digest((*message_2).modify_order_flags().order_position());
            } else if (const auto* message_2 = dynamic_cast<const protocol::DeleteOrderMessage*>(message->data())) {
                checksum += bench::digest((*message_2).nanoseconds());
                checksum += bench::digest((*message_2).symbol_id());
                checksum += bench::digest((*message_2).order_id());
            } else if (const auto* message_2 = dynamic_cast<const protocol::OrderExecutionMessage*>(message->data())) {
                checksum += bench::digest((*message_2).nanoseconds());
                checksum += bench::digest((*message_2).symbol_id());
                checksum += bench::digest((*message_2).order_id());
                checksum += bench::digest((*message_2).trade_id());
                checksum += bench::digest((*message_2).price().mantissa());
                checksum += bench::digest((*message_2).size());
                checksum += bench::digest((*message_2).order_execution_flags().sip_reporting());
                checksum += bench::digest((*message_2).order_execution_flags().traded_against_retail());
            } else if (const auto* message_2 = dynamic_cast<const protocol::TradeMessage*>(message->data())) {
                checksum += bench::digest((*message_2).nanoseconds());
                checksum += bench::digest((*message_2).symbol_id());
                checksum += bench::digest((*message_2).trade_id());
                checksum += bench::digest((*message_2).correction_number());
                checksum += bench::digest((*message_2).price().mantissa());
                checksum += bench::digest((*message_2).size());
                checksum += bench::digest((*message_2).trade_flags().sip_reporting());
                checksum += bench::digest((*message_2).trade_flags().retail_trade_indicator());
            } else if (const auto* message_2 = dynamic_cast<const protocol::TradeCancelMessage*>(message->data())) {
                checksum += bench::digest((*message_2).nanoseconds());
                checksum += bench::digest((*message_2).symbol_id());
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
    return bench::run("Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
