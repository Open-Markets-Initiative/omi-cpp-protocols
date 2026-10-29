// Cboe.CfeFutures.MulticastDepthOfBook.Pitch.v1.2.22 benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/classes/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/definitions.hpp"

namespace protocol = ::cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22;

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

    checksum += bench::digest(packet.packet_header().length());
    checksum += bench::digest(packet.packet_header().message_count());
    checksum += bench::digest(packet.packet_header().unit());
    checksum += bench::digest(packet.packet_header().sequence());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.message_header().message_length());
        checksum += bench::digest(each.message_header().message_type());

        if (const auto* message = dynamic_cast<const protocol::TimeReferenceMessage*>(each.message())) {
            checksum += bench::digest((*message).midnight_reference());
            checksum += bench::digest((*message).time_reference());
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).trade_date());
        } else if (const auto* message = dynamic_cast<const protocol::TimeMessage*>(each.message())) {
            checksum += bench::digest((*message).time_reference());
            checksum += bench::digest((*message).epoch_time());
        } else if (const auto* message = dynamic_cast<const protocol::UnitClearMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
        } else if (const auto* message = dynamic_cast<const protocol::FuturesInstrumentDefinitionMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).unit_timestamp());
            checksum += bench::digest((*message).report_symbol());
            checksum += bench::digest((*message).futures_flags().variance());
            checksum += bench::digest((*message).expiration_date());
            checksum += bench::digest((*message).contract_size());
            checksum += bench::digest((*message).listing_state());
            checksum += bench::digest((*message).price_increment().mantissa());
            checksum += bench::digest((*message).leg_count());
            checksum += bench::digest((*message).leg_offset());
            checksum += bench::digest((*message).reserved_1());
            checksum += bench::digest((*message).contract_date());
        } else if (const auto* message = dynamic_cast<const protocol::FuturesVarianceSymbolMappingMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).unit_timestamp());
            checksum += bench::digest((*message).feed_symbol());
            checksum += bench::digest((*message).futures_symbol());
            checksum += bench::digest((*message).accrued_day_variance().mantissa());
            checksum += bench::digest((*message).num_final_returns());
            checksum += bench::digest((*message).num_elapsed_returns());
        } else if (const auto* message = dynamic_cast<const protocol::PriceLimitsMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).upper_price_limit().mantissa());
            checksum += bench::digest((*message).lower_price_limit().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderLongMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).side_indicator());
            checksum += bench::digest((*message).quantity_long());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).price_long().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderShortMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).side_indicator());
            checksum += bench::digest((*message).quantity_short());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).price_short().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).executed_quantity());
            checksum += bench::digest((*message).execution_id());
            checksum += bench::digest((*message).trade_condition());
        } else if (const auto* message = dynamic_cast<const protocol::ReduceSizeLongMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).canceled_quantity_long());
        } else if (const auto* message = dynamic_cast<const protocol::ReduceSizeShortMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).canceled_quantity_short());
        } else if (const auto* message = dynamic_cast<const protocol::ModifyOrderLongMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).quantity_long());
            checksum += bench::digest((*message).price_long().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::ModifyOrderShortMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).quantity_short());
            checksum += bench::digest((*message).price_short().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::DeleteOrderMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
        } else if (const auto* message = dynamic_cast<const protocol::TradeLongMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).side_indicator());
            checksum += bench::digest((*message).quantity_long());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).price_long().mantissa());
            checksum += bench::digest((*message).execution_id());
            checksum += bench::digest((*message).trade_condition());
        } else if (const auto* message = dynamic_cast<const protocol::TradeShortMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).side_indicator());
            checksum += bench::digest((*message).quantity_short());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).price_short().mantissa());
            checksum += bench::digest((*message).execution_id());
            checksum += bench::digest((*message).trade_condition());
        } else if (const auto* message = dynamic_cast<const protocol::TransactionBeginMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
        } else if (const auto* message = dynamic_cast<const protocol::TransactionEndMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
        } else if (const auto* message = dynamic_cast<const protocol::TradeBreakMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).execution_id());
        } else if (const auto* message = dynamic_cast<const protocol::SettlementMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).trade_date());
            checksum += bench::digest((*message).settlement_price().mantissa());
            checksum += bench::digest((*message).issue());
        } else if (const auto* message = dynamic_cast<const protocol::OpenInterestMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).trade_date());
            checksum += bench::digest((*message).open_interest());
        } else if (const auto* message = dynamic_cast<const protocol::EndOfDaySummaryMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).trade_date());
            checksum += bench::digest((*message).open_interest());
            checksum += bench::digest((*message).high_price().mantissa());
            checksum += bench::digest((*message).low_price().mantissa());
            checksum += bench::digest((*message).open_price().mantissa());
            checksum += bench::digest((*message).close_price().mantissa());
            checksum += bench::digest((*message).total_volume());
            checksum += bench::digest((*message).block_volume());
            checksum += bench::digest((*message).ecrp_volume());
            checksum += bench::digest((*message).summary_flags().high_price_valid());
            checksum += bench::digest((*message).summary_flags().high_price_is_bid());
            checksum += bench::digest((*message).summary_flags().low_price_valid());
            checksum += bench::digest((*message).summary_flags().low_price_is_offer());
            checksum += bench::digest((*message).summary_flags().open_close_valid());
        } else if (const auto* message = dynamic_cast<const protocol::TradingStatusMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
            checksum += bench::digest((*message).symbol());
            checksum += bench::digest((*message).reserved_2());
            checksum += bench::digest((*message).trading_status());
            checksum += bench::digest((*message).reserved_3());
        } else if (const auto* message = dynamic_cast<const protocol::EndOfSessionMessage*>(each.message())) {
            checksum += bench::digest((*message).time_offset());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Cboe.CfeFutures.MulticastDepthOfBook.Pitch.v1.2.22", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
