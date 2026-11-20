// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: main.cpp
// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10 benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/tmx/tsx/quantumfeedlevel2/xmt/v2.10.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/classes/tmx/tsx/quantumfeedlevel2/xmt/v2.10/definitions.hpp"

namespace protocol = ::tmx::tsx::quantumfeedlevel2::xmt::v2_10;

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

    checksum += bench::digest(packet.frame_header().start_of_frame());
    checksum += bench::digest(packet.frame_header().protocol_name());
    checksum += bench::digest(packet.frame_header().protocol_version());
    checksum += bench::digest(packet.frame_header().message_length());
    checksum += bench::digest(packet.frame_header().session_id());
    checksum += bench::digest(packet.frame_header().ack_required_poss_dup());
    checksum += bench::digest(packet.frame_header().num_body());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.body_header().msg_length());
        checksum += bench::digest(each.body_header().msg_type());
        checksum += bench::digest(each.business_header().msg_version());
        checksum += bench::digest(each.business_header().source_id());
        checksum += bench::digest(each.business_header().stream_id());
        checksum += bench::digest(each.business_header().sequence_0());
        checksum += bench::digest(each.business_header().sequence_1());

        if (const auto* message = dynamic_cast<const protocol::SymbolStatusMessage*>(each.message())) {
            checksum += bench::digest((*message).symbol());
            checksum += ((*message).stock_group().has_value() ? bench::digest((*(*message).stock_group())) : std::uint64_t{0});
            checksum += bench::digest((*message).cusip());
            checksum += ((*message).board_lot().has_value() ? bench::digest((*(*message).board_lot())) : std::uint64_t{0});
            checksum += bench::digest((*message).currency());
            checksum += ((*message).face_value().has_value() ? bench::digest((*(*message).face_value()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).last_sale().has_value() ? bench::digest((*(*message).last_sale()).mantissa()) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::OrderBookMessage*>(each.message())) {
            checksum += bench::digest((*message).symbol());
            checksum += ((*message).broker_number().has_value() ? bench::digest((*(*message).broker_number())) : std::uint64_t{0});
            checksum += bench::digest((*message).order_side());
            checksum += ((*message).order_id().has_value() ? bench::digest((*(*message).order_id())) : std::uint64_t{0});
            checksum += ((*message).price().has_value() ? bench::digest((*(*message).price()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).volume().has_value() ? bench::digest((*(*message).volume())) : std::uint64_t{0});
            checksum += ((*message).priority_time_stamp().has_value() ? bench::digest((*(*message).priority_time_stamp())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::OrderBookTermsMessage*>(each.message())) {
            checksum += bench::digest((*message).symbol());
            checksum += ((*message).broker_number().has_value() ? bench::digest((*(*message).broker_number())) : std::uint64_t{0});
            checksum += bench::digest((*message).order_side());
            checksum += ((*message).order_id().has_value() ? bench::digest((*(*message).order_id())) : std::uint64_t{0});
            checksum += ((*message).price().has_value() ? bench::digest((*(*message).price()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).volume().has_value() ? bench::digest((*(*message).volume())) : std::uint64_t{0});
            checksum += bench::digest((*message).non_resident());
            checksum += bench::digest((*message).settlement_terms());
            checksum += ((*message).settlement_date().has_value() ? bench::digest((*(*message).settlement_date())) : std::uint64_t{0});
            checksum += ((*message).priority_time_stamp().has_value() ? bench::digest((*(*message).priority_time_stamp())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::AssignCopOrdersMessage*>(each.message())) {
            checksum += bench::digest((*message).symbol());
            checksum += ((*message).calculated_opening_price().has_value() ? bench::digest((*(*message).calculated_opening_price()).mantissa()) : std::uint64_t{0});
            checksum += bench::digest((*message).order_side());
            checksum += ((*message).trading_system_time_stamp().has_value() ? bench::digest((*(*message).trading_system_time_stamp())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::AssignCopNoOrdersMessage*>(each.message())) {
            checksum += bench::digest((*message).symbol());
            checksum += ((*message).calculated_opening_price().has_value() ? bench::digest((*(*message).calculated_opening_price()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).trading_system_time_stamp().has_value() ? bench::digest((*(*message).trading_system_time_stamp())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::AssignLimitMessage*>(each.message())) {
            checksum += bench::digest((*message).symbol());
            checksum += ((*message).calculated_opening_price().has_value() ? bench::digest((*(*message).calculated_opening_price()).mantissa()) : std::uint64_t{0});
            checksum += bench::digest((*message).order_side());
            checksum += ((*message).trading_system_time_stamp().has_value() ? bench::digest((*(*message).trading_system_time_stamp())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::MarketStateUpdateMessage*>(each.message())) {
            checksum += bench::digest((*message).market_state());
            checksum += ((*message).stock_group().has_value() ? bench::digest((*(*message).stock_group())) : std::uint64_t{0});
            checksum += ((*message).trading_system_time_stamp().has_value() ? bench::digest((*(*message).trading_system_time_stamp())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::MocImbalanceMessage*>(each.message())) {
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).imbalance_side());
            checksum += ((*message).imbalance_volume().has_value() ? bench::digest((*(*message).imbalance_volume())) : std::uint64_t{0});
            checksum += ((*message).trading_system_time_stamp().has_value() ? bench::digest((*(*message).trading_system_time_stamp())) : std::uint64_t{0});
            checksum += ((*message).imbalance_reference_price().has_value() ? bench::digest((*(*message).imbalance_reference_price()).mantissa()) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::OrderBookedMessage*>(each.message())) {
            checksum += bench::digest((*message).symbol());
            checksum += ((*message).broker_number().has_value() ? bench::digest((*(*message).broker_number())) : std::uint64_t{0});
            checksum += bench::digest((*message).order_side());
            checksum += ((*message).order_id().has_value() ? bench::digest((*(*message).order_id())) : std::uint64_t{0});
            checksum += ((*message).price().has_value() ? bench::digest((*(*message).price()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).volume().has_value() ? bench::digest((*(*message).volume())) : std::uint64_t{0});
            checksum += ((*message).priority_time_stamp().has_value() ? bench::digest((*(*message).priority_time_stamp())) : std::uint64_t{0});
            checksum += ((*message).trading_system_time_stamp().has_value() ? bench::digest((*(*message).trading_system_time_stamp())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::OrderBookedTermsMessage*>(each.message())) {
            checksum += bench::digest((*message).symbol());
            checksum += ((*message).broker_number().has_value() ? bench::digest((*(*message).broker_number())) : std::uint64_t{0});
            checksum += bench::digest((*message).order_side());
            checksum += ((*message).order_id().has_value() ? bench::digest((*(*message).order_id())) : std::uint64_t{0});
            checksum += ((*message).price().has_value() ? bench::digest((*(*message).price()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).volume().has_value() ? bench::digest((*(*message).volume())) : std::uint64_t{0});
            checksum += bench::digest((*message).non_resident());
            checksum += bench::digest((*message).settlement_terms());
            checksum += ((*message).settlement_date().has_value() ? bench::digest((*(*message).settlement_date())) : std::uint64_t{0});
            checksum += ((*message).priority_time_stamp().has_value() ? bench::digest((*(*message).priority_time_stamp())) : std::uint64_t{0});
            checksum += ((*message).trading_system_time_stamp().has_value() ? bench::digest((*(*message).trading_system_time_stamp())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::OrderCancelledMessage*>(each.message())) {
            checksum += bench::digest((*message).symbol());
            checksum += ((*message).broker_number().has_value() ? bench::digest((*(*message).broker_number())) : std::uint64_t{0});
            checksum += bench::digest((*message).order_side());
            checksum += ((*message).order_id().has_value() ? bench::digest((*(*message).order_id())) : std::uint64_t{0});
            checksum += ((*message).trading_system_time_stamp().has_value() ? bench::digest((*(*message).trading_system_time_stamp())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::OrderCancelledTermsMessage*>(each.message())) {
            checksum += bench::digest((*message).symbol());
            checksum += ((*message).broker_number().has_value() ? bench::digest((*(*message).broker_number())) : std::uint64_t{0});
            checksum += bench::digest((*message).order_side());
            checksum += ((*message).order_id().has_value() ? bench::digest((*(*message).order_id())) : std::uint64_t{0});
            checksum += ((*message).trading_system_time_stamp().has_value() ? bench::digest((*(*message).trading_system_time_stamp())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::OrderPriceTimeAssignedMessage*>(each.message())) {
            checksum += bench::digest((*message).symbol());
            checksum += ((*message).broker_number().has_value() ? bench::digest((*(*message).broker_number())) : std::uint64_t{0});
            checksum += bench::digest((*message).order_side());
            checksum += ((*message).order_id().has_value() ? bench::digest((*(*message).order_id())) : std::uint64_t{0});
            checksum += ((*message).price().has_value() ? bench::digest((*(*message).price()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).volume().has_value() ? bench::digest((*(*message).volume())) : std::uint64_t{0});
            checksum += ((*message).priority_time_stamp().has_value() ? bench::digest((*(*message).priority_time_stamp())) : std::uint64_t{0});
            checksum += ((*message).trading_system_time_stamp().has_value() ? bench::digest((*(*message).trading_system_time_stamp())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::OrderPriceTimeAssignedTermsMessage*>(each.message())) {
            checksum += bench::digest((*message).symbol());
            checksum += ((*message).broker_number().has_value() ? bench::digest((*(*message).broker_number())) : std::uint64_t{0});
            checksum += bench::digest((*message).order_side());
            checksum += ((*message).order_id().has_value() ? bench::digest((*(*message).order_id())) : std::uint64_t{0});
            checksum += ((*message).price().has_value() ? bench::digest((*(*message).price()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).volume().has_value() ? bench::digest((*(*message).volume())) : std::uint64_t{0});
            checksum += ((*message).priority_time_stamp().has_value() ? bench::digest((*(*message).priority_time_stamp())) : std::uint64_t{0});
            checksum += ((*message).trading_system_time_stamp().has_value() ? bench::digest((*(*message).trading_system_time_stamp())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::StockStatusMessage*>(each.message())) {
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).comment());
            checksum += bench::digest((*message).stock_state());
            checksum += ((*message).trading_system_time_stamp().has_value() ? bench::digest((*(*message).trading_system_time_stamp())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::TradeReportMessage*>(each.message())) {
            checksum += bench::digest((*message).symbol());
            checksum += ((*message).trade_number().has_value() ? bench::digest((*(*message).trade_number())) : std::uint64_t{0});
            checksum += ((*message).price().has_value() ? bench::digest((*(*message).price()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).volume().has_value() ? bench::digest((*(*message).volume())) : std::uint64_t{0});
            checksum += ((*message).buy_broker_number().has_value() ? bench::digest((*(*message).buy_broker_number())) : std::uint64_t{0});
            checksum += ((*message).buy_order_id().has_value() ? bench::digest((*(*message).buy_order_id())) : std::uint64_t{0});
            checksum += ((*message).buy_display_volume().has_value() ? bench::digest((*(*message).buy_display_volume())) : std::uint64_t{0});
            checksum += ((*message).sell_broker_number().has_value() ? bench::digest((*(*message).sell_broker_number())) : std::uint64_t{0});
            checksum += ((*message).sell_order_id().has_value() ? bench::digest((*(*message).sell_order_id())) : std::uint64_t{0});
            checksum += ((*message).sell_display_volume().has_value() ? bench::digest((*(*message).sell_display_volume())) : std::uint64_t{0});
            checksum += bench::digest((*message).bypass());
            checksum += ((*message).trade_time_stamp().has_value() ? bench::digest((*(*message).trade_time_stamp())) : std::uint64_t{0});
            checksum += bench::digest((*message).cross_type());
            checksum += ((*message).trading_system_time_stamp().has_value() ? bench::digest((*(*message).trading_system_time_stamp())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::TradeReportTermsMessage*>(each.message())) {
            checksum += bench::digest((*message).symbol());
            checksum += ((*message).trade_number().has_value() ? bench::digest((*(*message).trade_number())) : std::uint64_t{0});
            checksum += ((*message).price().has_value() ? bench::digest((*(*message).price()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).volume().has_value() ? bench::digest((*(*message).volume())) : std::uint64_t{0});
            checksum += ((*message).buy_broker_number().has_value() ? bench::digest((*(*message).buy_broker_number())) : std::uint64_t{0});
            checksum += ((*message).buy_order_id().has_value() ? bench::digest((*(*message).buy_order_id())) : std::uint64_t{0});
            checksum += ((*message).buy_display_volume().has_value() ? bench::digest((*(*message).buy_display_volume())) : std::uint64_t{0});
            checksum += ((*message).sell_broker_number().has_value() ? bench::digest((*(*message).sell_broker_number())) : std::uint64_t{0});
            checksum += ((*message).sell_order_id().has_value() ? bench::digest((*(*message).sell_order_id())) : std::uint64_t{0});
            checksum += ((*message).sell_display_volume().has_value() ? bench::digest((*(*message).sell_display_volume())) : std::uint64_t{0});
            checksum += ((*message).trade_time_stamp().has_value() ? bench::digest((*(*message).trade_time_stamp())) : std::uint64_t{0});
            checksum += bench::digest((*message).non_resident());
            checksum += bench::digest((*message).settlement_terms());
            checksum += ((*message).settlement_date().has_value() ? bench::digest((*(*message).settlement_date())) : std::uint64_t{0});
            checksum += bench::digest((*message).cross_type());
            checksum += ((*message).trading_system_time_stamp().has_value() ? bench::digest((*(*message).trading_system_time_stamp())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::TradeCancelledMessage*>(each.message())) {
            checksum += bench::digest((*message).symbol());
            checksum += ((*message).trade_number().has_value() ? bench::digest((*(*message).trade_number())) : std::uint64_t{0});
            checksum += ((*message).trading_system_time_stamp().has_value() ? bench::digest((*(*message).trading_system_time_stamp())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::TradeCancelledTermsMessage*>(each.message())) {
            checksum += bench::digest((*message).symbol());
            checksum += ((*message).trade_number().has_value() ? bench::digest((*(*message).trade_number())) : std::uint64_t{0});
            checksum += ((*message).trading_system_time_stamp().has_value() ? bench::digest((*(*message).trading_system_time_stamp())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::TradeCorrectionMessage*>(each.message())) {
            checksum += bench::digest((*message).symbol());
            checksum += ((*message).trade_number().has_value() ? bench::digest((*(*message).trade_number())) : std::uint64_t{0});
            checksum += ((*message).price().has_value() ? bench::digest((*(*message).price()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).volume().has_value() ? bench::digest((*(*message).volume())) : std::uint64_t{0});
            checksum += ((*message).buy_broker_number().has_value() ? bench::digest((*(*message).buy_broker_number())) : std::uint64_t{0});
            checksum += ((*message).sell_broker_number().has_value() ? bench::digest((*(*message).sell_broker_number())) : std::uint64_t{0});
            checksum += bench::digest((*message).initiated_by());
            checksum += ((*message).orig_trade_number().has_value() ? bench::digest((*(*message).orig_trade_number())) : std::uint64_t{0});
            checksum += bench::digest((*message).bypass());
            checksum += ((*message).trade_time_stamp().has_value() ? bench::digest((*(*message).trade_time_stamp())) : std::uint64_t{0});
            checksum += bench::digest((*message).cross_type());
            checksum += ((*message).trading_system_time_stamp().has_value() ? bench::digest((*(*message).trading_system_time_stamp())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::TradeCorrectionTermsMessage*>(each.message())) {
            checksum += bench::digest((*message).symbol());
            checksum += ((*message).trade_number().has_value() ? bench::digest((*(*message).trade_number())) : std::uint64_t{0});
            checksum += ((*message).price().has_value() ? bench::digest((*(*message).price()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).volume().has_value() ? bench::digest((*(*message).volume())) : std::uint64_t{0});
            checksum += ((*message).buy_broker_number().has_value() ? bench::digest((*(*message).buy_broker_number())) : std::uint64_t{0});
            checksum += ((*message).sell_broker_number().has_value() ? bench::digest((*(*message).sell_broker_number())) : std::uint64_t{0});
            checksum += bench::digest((*message).initiated_by());
            checksum += ((*message).orig_trade_number().has_value() ? bench::digest((*(*message).orig_trade_number())) : std::uint64_t{0});
            checksum += ((*message).trade_time_stamp().has_value() ? bench::digest((*(*message).trade_time_stamp())) : std::uint64_t{0});
            checksum += bench::digest((*message).non_resident());
            checksum += bench::digest((*message).settlement_terms());
            checksum += ((*message).settlement_date().has_value() ? bench::digest((*(*message).settlement_date())) : std::uint64_t{0});
            checksum += bench::digest((*message).cross_type());
            checksum += ((*message).trading_system_time_stamp().has_value() ? bench::digest((*(*message).trading_system_time_stamp())) : std::uint64_t{0});
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
