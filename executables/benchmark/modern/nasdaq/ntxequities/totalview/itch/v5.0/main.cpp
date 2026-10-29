// Nasdaq.NtxEquities.TotalView.Itch.v5.0 benchmark, through the Modern iterator: every value it reads from every message of the simulated
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
#include "cpp/binary/modern/nasdaq/ntxequities/totalview/itch/v5.0/definitions.hpp"

namespace protocol = ::nasdaq::ntxequities::totalview::itch::v5_0;

namespace {

// The values the Modern iterator reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    checksum += bench::digest(iterator.packet_header->session.get());
    checksum += bench::digest(iterator.packet_header->sequence_number.get());
    checksum += bench::digest(iterator.packet_header->message_count.get());

    std::size_t index = 0;

    while (iterator.next()) {
        checksum += index++;
        checksum += bench::digest(iterator.message_header->message_length.get());
        checksum += bench::digest(iterator.message_header->message_type.get());

        if (iterator.message_type == protocol::SystemEventMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SystemEventMessage::parse(iterator.message);
            checksum += bench::digest(message->stock_locate.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->event_code.get());
        } else if (iterator.message_type == protocol::StockDirectoryMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::StockDirectoryMessage::parse(iterator.message);
            checksum += bench::digest(message->stock_locate.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->stock.get());
            checksum += bench::digest(message->market_category.get());
            checksum += bench::digest(message->financial_status_indicator.get());
            checksum += bench::digest(message->round_lot_size.get());
            checksum += bench::digest(message->round_lots_only.get());
            checksum += bench::digest(message->issue_classification.get());
            checksum += bench::digest(message->issue_sub_type.get());
            checksum += bench::digest(message->authenticity.get());
            checksum += bench::digest(message->short_sale_threshold_indicator.get());
            checksum += bench::digest(message->ipo_flag.get());
            checksum += bench::digest(message->luld_reference_price_tier.get());
            checksum += bench::digest(message->etp_flag.get());
            checksum += bench::digest(message->etp_leverage_factor.get());
            checksum += bench::digest(message->inverse_indicator.get());
        } else if (iterator.message_type == protocol::StockTradingActionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::StockTradingActionMessage::parse(iterator.message);
            checksum += bench::digest(message->stock_locate.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->stock.get());
            checksum += bench::digest(message->trading_state.get());
            checksum += bench::digest(message->reserved.get());
            checksum += bench::digest(message->trading_action_reason.get());
        } else if (iterator.message_type == protocol::RegShoShortSalePriceTestRestrictedIndicatorMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::RegShoShortSalePriceTestRestrictedIndicatorMessage::parse(iterator.message);
            checksum += bench::digest(message->locate_code.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->stock.get());
            checksum += bench::digest(message->reg_sho_action.get());
        } else if (iterator.message_type == protocol::MarketParticipantPositionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::MarketParticipantPositionMessage::parse(iterator.message);
            checksum += bench::digest(message->stock_locate.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->mpid.get());
            checksum += bench::digest(message->stock.get());
            checksum += bench::digest(message->primary_market_maker.get());
            checksum += bench::digest(message->market_maker_mode.get());
            checksum += bench::digest(message->market_participant_state.get());
        } else if (iterator.message_type == protocol::MwcbDeclineLevelMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::MwcbDeclineLevelMessage::parse(iterator.message);
            checksum += bench::digest(message->stock_locate.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->level_1.integer());
            checksum += bench::digest(message->level_2.integer());
            checksum += bench::digest(message->level_3.integer());
        } else if (iterator.message_type == protocol::MwcbStatusMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::MwcbStatusMessage::parse(iterator.message);
            checksum += bench::digest(message->stock_locate.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->breached_level.get());
        } else if (iterator.message_type == protocol::LuldAuctionCollarMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::LuldAuctionCollarMessage::parse(iterator.message);
            checksum += bench::digest(message->stock_locate.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->stock.get());
            checksum += bench::digest(message->auction_collar_reference_price.integer());
            checksum += bench::digest(message->upper_auction_collar_price.integer());
            checksum += bench::digest(message->lower_auction_collar_price.integer());
            checksum += bench::digest(message->auction_collar_extension.get());
        } else if (iterator.message_type == protocol::OperationalHaltMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OperationalHaltMessage::parse(iterator.message);
            checksum += bench::digest(message->stock_locate.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->stock.get());
            checksum += bench::digest(message->market_code.get());
            checksum += bench::digest(message->operational_halt_action.get());
        } else if (iterator.message_type == protocol::AddOrderNoMpidAttributionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddOrderNoMpidAttributionMessage::parse(iterator.message);
            checksum += bench::digest(message->stock_locate.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->order_reference_number.get());
            checksum += bench::digest(message->buy_sell_indicator.get());
            checksum += bench::digest(message->shares.get());
            checksum += bench::digest(message->stock.get());
            checksum += bench::digest(message->price.integer());
        } else if (iterator.message_type == protocol::AddOrderMpidAttributionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddOrderMpidAttributionMessage::parse(iterator.message);
            checksum += bench::digest(message->stock_locate.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->order_reference_number.get());
            checksum += bench::digest(message->buy_sell_indicator.get());
            checksum += bench::digest(message->shares.get());
            checksum += bench::digest(message->stock.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->attribution.get());
        } else if (iterator.message_type == protocol::OrderExecutedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderExecutedMessage::parse(iterator.message);
            checksum += bench::digest(message->stock_locate.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->order_reference_number.get());
            checksum += bench::digest(message->executed_shares.get());
            checksum += bench::digest(message->match_number.get());
        } else if (iterator.message_type == protocol::OrderExecutedWithPriceMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderExecutedWithPriceMessage::parse(iterator.message);
            checksum += bench::digest(message->stock_locate.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->order_reference_number.get());
            checksum += bench::digest(message->executed_shares.get());
            checksum += bench::digest(message->match_number.get());
            checksum += bench::digest(message->printable.get());
            checksum += bench::digest(message->execution_price.integer());
        } else if (iterator.message_type == protocol::OrderCancelMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderCancelMessage::parse(iterator.message);
            checksum += bench::digest(message->stock_locate.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->order_reference_number.get());
            checksum += bench::digest(message->cancelled_shares.get());
        } else if (iterator.message_type == protocol::OrderDeleteMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderDeleteMessage::parse(iterator.message);
            checksum += bench::digest(message->stock_locate.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->order_reference_number.get());
        } else if (iterator.message_type == protocol::OrderReplaceMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderReplaceMessage::parse(iterator.message);
            checksum += bench::digest(message->stock_locate.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->original_order_reference_number.get());
            checksum += bench::digest(message->new_order_reference_number.get());
            checksum += bench::digest(message->shares.get());
            checksum += bench::digest(message->price.integer());
        } else if (iterator.message_type == protocol::NonCrossTradeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::NonCrossTradeMessage::parse(iterator.message);
            checksum += bench::digest(message->stock_locate.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->order_reference_number.get());
            checksum += bench::digest(message->buy_sell_indicator.get());
            checksum += bench::digest(message->shares.get());
            checksum += bench::digest(message->stock.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->match_number.get());
        } else if (iterator.message_type == protocol::CrossTradeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::CrossTradeMessage::parse(iterator.message);
            checksum += bench::digest(message->stock_locate.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->shares_long.get());
            checksum += bench::digest(message->stock.get());
            checksum += bench::digest(message->cross_price.integer());
            checksum += bench::digest(message->match_number.get());
            checksum += bench::digest(message->cross_type.get());
        } else if (iterator.message_type == protocol::BrokenTradeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::BrokenTradeMessage::parse(iterator.message);
            checksum += bench::digest(message->stock_locate.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->match_number.get());
        } else if (iterator.message_type == protocol::NetOrderImbalanceIndicatorMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::NetOrderImbalanceIndicatorMessage::parse(iterator.message);
            checksum += bench::digest(message->stock_locate.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->paired_shares.get());
            checksum += bench::digest(message->imbalance_shares.get());
            checksum += bench::digest(message->imbalance_direction.get());
            checksum += bench::digest(message->stock.get());
            checksum += bench::digest(message->far_price.integer());
            checksum += bench::digest(message->near_price.integer());
            checksum += bench::digest(message->current_reference_price.integer());
            checksum += bench::digest(message->cross_type.get());
            checksum += bench::digest(message->price_variation_indicator.get());
        } else if (iterator.message_type == protocol::RetailInterestMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::RetailInterestMessage::parse(iterator.message);
            checksum += bench::digest(message->stock_locate.get());
            checksum += bench::digest(message->tracking_number.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->stock.get());
            checksum += bench::digest(message->interest_flag.get());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nasdaq.NtxEquities.TotalView.Itch.v5.0", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
