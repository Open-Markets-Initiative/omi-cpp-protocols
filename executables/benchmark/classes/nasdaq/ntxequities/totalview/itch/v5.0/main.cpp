// Nasdaq.NtxEquities.TotalView.Itch.v5.0 benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/ntxequities/totalview/itch/v5.0.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/classes/nasdaq/ntxequities/totalview/itch/v5.0/definitions.hpp"

namespace protocol = ::nasdaq::ntxequities::totalview::itch::v5_0;

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
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).event_code());
        } else if (const auto* message = dynamic_cast<const protocol::StockDirectoryMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).market_category());
            checksum += bench::digest((*message).financial_status_indicator());
            checksum += bench::digest((*message).round_lot_size());
            checksum += bench::digest((*message).round_lots_only());
            checksum += bench::digest((*message).issue_classification());
            checksum += bench::digest((*message).issue_sub_type());
            checksum += bench::digest((*message).authenticity());
            checksum += bench::digest((*message).short_sale_threshold_indicator());
            checksum += bench::digest((*message).ipo_flag());
            checksum += bench::digest((*message).luld_reference_price_tier());
            checksum += bench::digest((*message).etp_flag());
            checksum += bench::digest((*message).etp_leverage_factor());
            checksum += bench::digest((*message).inverse_indicator());
        } else if (const auto* message = dynamic_cast<const protocol::StockTradingActionMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).trading_state());
            checksum += bench::digest((*message).reserved());
            checksum += bench::digest((*message).trading_action_reason());
        } else if (const auto* message = dynamic_cast<const protocol::RegShoShortSalePriceTestRestrictedIndicatorMessage*>(each.message())) {
            checksum += bench::digest((*message).locate_code());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).reg_sho_action());
        } else if (const auto* message = dynamic_cast<const protocol::MarketParticipantPositionMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).mpid());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).primary_market_maker());
            checksum += bench::digest((*message).market_maker_mode());
            checksum += bench::digest((*message).market_participant_state());
        } else if (const auto* message = dynamic_cast<const protocol::MwcbDeclineLevelMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).level_1().mantissa());
            checksum += bench::digest((*message).level_2().mantissa());
            checksum += bench::digest((*message).level_3().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::MwcbStatusMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).breached_level());
        } else if (const auto* message = dynamic_cast<const protocol::LuldAuctionCollarMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).auction_collar_reference_price().mantissa());
            checksum += bench::digest((*message).upper_auction_collar_price().mantissa());
            checksum += bench::digest((*message).lower_auction_collar_price().mantissa());
            checksum += bench::digest((*message).auction_collar_extension());
        } else if (const auto* message = dynamic_cast<const protocol::OperationalHaltMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).market_code());
            checksum += bench::digest((*message).operational_halt_action());
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderNoMpidAttributionMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).order_reference_number());
            checksum += bench::digest((*message).buy_sell_indicator());
            checksum += bench::digest((*message).shares());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderMpidAttributionMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).order_reference_number());
            checksum += bench::digest((*message).buy_sell_indicator());
            checksum += bench::digest((*message).shares());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).attribution());
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).order_reference_number());
            checksum += bench::digest((*message).executed_shares());
            checksum += bench::digest((*message).match_number());
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedWithPriceMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).order_reference_number());
            checksum += bench::digest((*message).executed_shares());
            checksum += bench::digest((*message).match_number());
            checksum += bench::digest((*message).printable());
            checksum += bench::digest((*message).execution_price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::OrderCancelMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).order_reference_number());
            checksum += bench::digest((*message).cancelled_shares());
        } else if (const auto* message = dynamic_cast<const protocol::OrderDeleteMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).order_reference_number());
        } else if (const auto* message = dynamic_cast<const protocol::OrderReplaceMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).original_order_reference_number());
            checksum += bench::digest((*message).new_order_reference_number());
            checksum += bench::digest((*message).shares());
            checksum += bench::digest((*message).price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::NonCrossTradeMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).order_reference_number());
            checksum += bench::digest((*message).buy_sell_indicator());
            checksum += bench::digest((*message).shares());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).match_number());
        } else if (const auto* message = dynamic_cast<const protocol::CrossTradeMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).shares_long());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).cross_price().mantissa());
            checksum += bench::digest((*message).match_number());
            checksum += bench::digest((*message).cross_type());
        } else if (const auto* message = dynamic_cast<const protocol::BrokenTradeMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).match_number());
        } else if (const auto* message = dynamic_cast<const protocol::NetOrderImbalanceIndicatorMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).paired_shares());
            checksum += bench::digest((*message).imbalance_shares());
            checksum += bench::digest((*message).imbalance_direction());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).far_price().mantissa());
            checksum += bench::digest((*message).near_price().mantissa());
            checksum += bench::digest((*message).current_reference_price().mantissa());
            checksum += bench::digest((*message).cross_type());
            checksum += bench::digest((*message).price_variation_indicator());
        } else if (const auto* message = dynamic_cast<const protocol::RetailInterestMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).interest_flag());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nasdaq.NtxEquities.TotalView.Itch.v5.0", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
