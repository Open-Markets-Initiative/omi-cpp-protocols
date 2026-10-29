// Iex.IexEquities.DeepPlus.IexTp.v1.05 benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/iex/iexequities/deepplus/iextp/v1.05.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/classes/iex/iexequities/deepplus/iextp/v1.05/definitions.hpp"

namespace protocol = ::iex::iexequities::deepplus::iextp::v1_05;

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

        if (const auto* message = dynamic_cast<const protocol::SystemEventMessage*>(each.message())) {
            checksum += bench::digest((*message).system_event());
            checksum += bench::digest((*message).timestamp());
        } else if (const auto* message = dynamic_cast<const protocol::SecurityDirectoryMessage*>(each.message())) {
            checksum += bench::digest((*message).security_directory_flags().etp());
            checksum += bench::digest((*message).security_directory_flags().when_issued());
            checksum += bench::digest((*message).security_directory_flags().test_security());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).round_lot_size());
            checksum += bench::digest((*message).adjusted_poc_price().mantissa());
            checksum += bench::digest((*message).luld_tier());
        } else if (const auto* message = dynamic_cast<const protocol::TradingStatusMessage*>(each.message())) {
            checksum += bench::digest((*message).trading_status());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).reason());
        } else if (const auto* message = dynamic_cast<const protocol::RetailLiquidityIndicatorMessage*>(each.message())) {
            checksum += bench::digest((*message).retail_liquidity_indicator());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).symbol());
        } else if (const auto* message = dynamic_cast<const protocol::OperationalHaltStatusMessage*>(each.message())) {
            checksum += bench::digest((*message).operational_halt_status());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).symbol());
        } else if (const auto* message = dynamic_cast<const protocol::ShortSalePriceTestStatusMessage*>(each.message())) {
            checksum += bench::digest((*message).short_sale_price_test_status());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).detail());
        } else if (const auto* message = dynamic_cast<const protocol::SecurityEventMessage*>(each.message())) {
            checksum += bench::digest((*message).security_event());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).symbol());
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderMessage*>(each.message())) {
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).size());
            checksum += bench::digest((*message).price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::OrderModifyMessage*>(each.message())) {
            checksum += bench::digest((*message).modify_flags().priority());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).order_id_reference());
            checksum += bench::digest((*message).size());
            checksum += bench::digest((*message).price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::OrderDeleteMessage*>(each.message())) {
            checksum += bench::digest((*message).reserved_1());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).order_id_reference());
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedMessage*>(each.message())) {
            checksum += bench::digest((*message).sale_condition_flags().single_price_cross_trade());
            checksum += bench::digest((*message).sale_condition_flags().trade_through_exempt());
            checksum += bench::digest((*message).sale_condition_flags().odd_lot());
            checksum += bench::digest((*message).sale_condition_flags().extended_hours());
            checksum += bench::digest((*message).sale_condition_flags().intermarket_sweep());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).order_id_reference());
            checksum += bench::digest((*message).size());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).trade_id());
        } else if (const auto* message = dynamic_cast<const protocol::TradeMessage*>(each.message())) {
            checksum += bench::digest((*message).sale_condition_flags().single_price_cross_trade());
            checksum += bench::digest((*message).sale_condition_flags().trade_through_exempt());
            checksum += bench::digest((*message).sale_condition_flags().odd_lot());
            checksum += bench::digest((*message).sale_condition_flags().extended_hours());
            checksum += bench::digest((*message).sale_condition_flags().intermarket_sweep());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).size());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).trade_id());
        } else if (const auto* message = dynamic_cast<const protocol::TradeBreakMessage*>(each.message())) {
            checksum += bench::digest((*message).sale_condition_flags().single_price_cross_trade());
            checksum += bench::digest((*message).sale_condition_flags().trade_through_exempt());
            checksum += bench::digest((*message).sale_condition_flags().odd_lot());
            checksum += bench::digest((*message).sale_condition_flags().extended_hours());
            checksum += bench::digest((*message).sale_condition_flags().intermarket_sweep());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).size());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).trade_id());
        } else if (const auto* message = dynamic_cast<const protocol::ClearBookMessage*>(each.message())) {
            checksum += bench::digest((*message).reserved_1());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).symbol());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Iex.IexEquities.DeepPlus.IexTp.v1.05", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
