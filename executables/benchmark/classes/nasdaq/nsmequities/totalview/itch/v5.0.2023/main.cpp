// Nasdaq.NsmEquities.TotalView.Itch.v5.0.2023 benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/nsmequities/totalview/itch/v5.0.2023.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/definitions.hpp"

namespace protocol = ::nasdaq::nsmequities::totalview::itch::v5_0_2023;

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

        if (const auto* message = dynamic_cast<const protocol::PayloadSystemEventMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).event_code());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadStockDirectoryMessage*>(each.message())) {
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
        } else if (const auto* message = dynamic_cast<const protocol::PayloadStockTradingActionMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).trading_state());
            checksum += bench::digest((*message).reserved());
            checksum += bench::digest((*message).reason_code());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadRegShoShortSalePriceTestRestrictedIndicatorMessage*>(each.message())) {
            checksum += bench::digest((*message).locate_code());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).reg_sho_action());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadMarketParticipantPositionMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).mpid());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).primary_market_maker());
            checksum += bench::digest((*message).market_maker_mode());
            checksum += bench::digest((*message).market_participant_state());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadMwcbDeclineLevelMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).level_1().mantissa());
            checksum += bench::digest((*message).level_2().mantissa());
            checksum += bench::digest((*message).level_3().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadMwcbStatusLevelMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).breached_level());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadIpoQuotingPeriodUpdate*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).ipo_quotation_release_time());
            checksum += bench::digest((*message).ipo_quotation_release_qualifier());
            checksum += bench::digest((*message).ipo_price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadLuldAuctionCollarMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).auction_collar_reference_price().mantissa());
            checksum += bench::digest((*message).upper_auction_collar_price().mantissa());
            checksum += bench::digest((*message).lower_auction_collar_price().mantissa());
            checksum += bench::digest((*message).auction_collar_extension());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadOperationalHaltMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).market_code());
            checksum += bench::digest((*message).operational_halt_action());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadAddOrderNoMpidAttributionMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).order_reference_number());
            checksum += bench::digest((*message).buy_sell_indicator());
            checksum += bench::digest((*message).shares());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadAddOrderWithMpidAttributionMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).order_reference_number());
            checksum += bench::digest((*message).buy_sell_indicator());
            checksum += bench::digest((*message).shares());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).attribution());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadOrderExecutedMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).order_reference_number());
            checksum += bench::digest((*message).executed_shares());
            checksum += bench::digest((*message).match_number());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadOrderExecutedWithPriceMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).order_reference_number());
            checksum += bench::digest((*message).executed_shares());
            checksum += bench::digest((*message).match_number());
            checksum += bench::digest((*message).printable());
            checksum += bench::digest((*message).execution_price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadOrderCancelMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).order_reference_number());
            checksum += bench::digest((*message).canceled_shares());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadOrderDeleteMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).order_reference_number());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadOrderReplaceMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).original_order_reference_number());
            checksum += bench::digest((*message).new_order_reference_number());
            checksum += bench::digest((*message).shares());
            checksum += bench::digest((*message).price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadNonCrossTradeMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).order_reference_number());
            checksum += bench::digest((*message).buy_sell_indicator());
            checksum += bench::digest((*message).shares());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).price().mantissa());
            checksum += bench::digest((*message).match_number());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadCrossTradeMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).cross_shares());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).cross_price().mantissa());
            checksum += bench::digest((*message).match_number());
            checksum += bench::digest((*message).cross_type());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadBrokenTradeMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).match_number());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadNetOrderImbalanceIndicatorMessage*>(each.message())) {
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
        } else if (const auto* message = dynamic_cast<const protocol::PayloadRetailPriceImprovementIndicatorMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).interest_flag());
        } else if (const auto* message = dynamic_cast<const protocol::PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage*>(each.message())) {
            checksum += bench::digest((*message).stock_locate());
            checksum += bench::digest((*message).tracking_number());
            checksum += bench::digest((*message).timestamp());
            checksum += bench::digest((*message).stock());
            checksum += bench::digest((*message).open_eligibility_status());
            checksum += bench::digest((*message).minimum_allowable_price().mantissa());
            checksum += bench::digest((*message).maximum_allowable_price().mantissa());
            checksum += bench::digest((*message).near_execution_price().mantissa());
            checksum += bench::digest((*message).near_execution_time());
            checksum += bench::digest((*message).lower_price_range_collar().mantissa());
            checksum += bench::digest((*message).upper_price_range_collar().mantissa());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nasdaq.NsmEquities.TotalView.Itch.v5.0.2023", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
