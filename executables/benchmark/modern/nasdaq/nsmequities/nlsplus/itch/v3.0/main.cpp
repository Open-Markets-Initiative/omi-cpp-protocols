// Nasdaq.NsmEquities.NlsPlus.Itch.v3.0 benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/nsmequities/nlsplus/itch/v3.0.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/nasdaq/nsmequities/nlsplus/itch/v3.0/definitions.hpp"

namespace protocol = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

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
        checksum += bench::digest(iterator.message_header->tracking_number.get());
        checksum += bench::digest(iterator.message_header->timestamp.get());
        checksum += bench::digest(iterator.message_header->message_type.get());

        if (iterator.message_type == protocol::SystemEventMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SystemEventMessage::parse(iterator.message);
            checksum += bench::digest(message->event_code.get());
        } else if (iterator.message_type == protocol::TradeReportMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeReportMessage::parse(iterator.message);
            checksum += bench::digest(message->originating_market_center_identifier.get());
            checksum += bench::digest(message->issue_symbol.get());
            checksum += bench::digest(message->security_class.get());
            checksum += bench::digest(message->trade_control_number.get());
            checksum += bench::digest(message->trade_price.integer());
            checksum += bench::digest(message->trade_size.get());
            checksum += bench::digest(message->sale_condition_modifier.settlement_type.get());
            checksum += bench::digest(message->sale_condition_modifier.trade_through_exemption.get());
            checksum += bench::digest(message->sale_condition_modifier.extended_hours_or_sold_code.get());
            checksum += bench::digest(message->sale_condition_modifier.special_sale_condition.get());
            checksum += bench::digest(message->consolidated_volume.get());
        } else if (iterator.message_type == protocol::LongFormTradeReportMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::LongFormTradeReportMessage::parse(iterator.message);
            checksum += bench::digest(message->originating_market_center_identifier.get());
            checksum += bench::digest(message->issue_symbol.get());
            checksum += bench::digest(message->security_class.get());
            checksum += bench::digest(message->trade_control_number.get());
            checksum += bench::digest(message->trade_price_long.integer());
            checksum += bench::digest(message->trade_size.get());
            checksum += bench::digest(message->sale_condition_modifier.settlement_type.get());
            checksum += bench::digest(message->sale_condition_modifier.trade_through_exemption.get());
            checksum += bench::digest(message->sale_condition_modifier.extended_hours_or_sold_code.get());
            checksum += bench::digest(message->sale_condition_modifier.special_sale_condition.get());
            checksum += bench::digest(message->consolidated_volume.get());
        } else if (iterator.message_type == protocol::NextSharesTradeReportMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::NextSharesTradeReportMessage::parse(iterator.message);
            checksum += bench::digest(message->originating_market_center_identifier.get());
            checksum += bench::digest(message->next_shares_symbol.get());
            checksum += bench::digest(message->security_class.get());
            checksum += bench::digest(message->trade_control_number.get());
            checksum += bench::digest(message->proxy_price.integer());
            checksum += bench::digest(message->trade_size.get());
            checksum += bench::digest(message->nav_offset_amount.integer());
            checksum += bench::digest(message->sale_condition_modifier.settlement_type.get());
            checksum += bench::digest(message->sale_condition_modifier.trade_through_exemption.get());
            checksum += bench::digest(message->sale_condition_modifier.extended_hours_or_sold_code.get());
            checksum += bench::digest(message->sale_condition_modifier.special_sale_condition.get());
            checksum += bench::digest(message->consolidated_volume.get());
        } else if (iterator.message_type == protocol::TradeCancelErrorMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeCancelErrorMessage::parse(iterator.message);
            checksum += bench::digest(message->originating_market_center_identifier.get());
            checksum += bench::digest(message->issue_symbol.get());
            checksum += bench::digest(message->security_class.get());
            checksum += bench::digest(message->original_trade_control_number.get());
            checksum += bench::digest(message->original_trade_price.integer());
            checksum += bench::digest(message->original_trade_size.get());
            checksum += bench::digest(message->original_sale_condition_modifier.original_settlement_type.get());
            checksum += bench::digest(message->original_sale_condition_modifier.original_trade_through_exemption.get());
            checksum += bench::digest(message->original_sale_condition_modifier.original_extended_hours_or_sold_code.get());
            checksum += bench::digest(message->original_sale_condition_modifier.original_special_sale_condition.get());
            checksum += bench::digest(message->consolidated_volume.get());
        } else if (iterator.message_type == protocol::LongFormTradeCancelErrorMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::LongFormTradeCancelErrorMessage::parse(iterator.message);
            checksum += bench::digest(message->originating_market_center_identifier.get());
            checksum += bench::digest(message->issue_symbol.get());
            checksum += bench::digest(message->security_class.get());
            checksum += bench::digest(message->original_trade_control_number.get());
            checksum += bench::digest(message->original_trade_price_long.integer());
            checksum += bench::digest(message->original_trade_size.get());
            checksum += bench::digest(message->original_sale_condition_modifier.original_settlement_type.get());
            checksum += bench::digest(message->original_sale_condition_modifier.original_trade_through_exemption.get());
            checksum += bench::digest(message->original_sale_condition_modifier.original_extended_hours_or_sold_code.get());
            checksum += bench::digest(message->original_sale_condition_modifier.original_special_sale_condition.get());
            checksum += bench::digest(message->consolidated_volume.get());
        } else if (iterator.message_type == protocol::NextSharesTradeCancelErrorMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::NextSharesTradeCancelErrorMessage::parse(iterator.message);
            checksum += bench::digest(message->market_center.get());
            checksum += bench::digest(message->issue_symbol.get());
            checksum += bench::digest(message->security_class.get());
            checksum += bench::digest(message->original_trade_control_number.get());
            checksum += bench::digest(message->original_proxy_price.integer());
            checksum += bench::digest(message->original_nav_offset_amount.integer());
            checksum += bench::digest(message->original_trade_size.get());
            checksum += bench::digest(message->original_sale_condition_modifier.original_settlement_type.get());
            checksum += bench::digest(message->original_sale_condition_modifier.original_trade_through_exemption.get());
            checksum += bench::digest(message->original_sale_condition_modifier.original_extended_hours_or_sold_code.get());
            checksum += bench::digest(message->original_sale_condition_modifier.original_special_sale_condition.get());
            checksum += bench::digest(message->consolidated_volume.get());
        } else if (iterator.message_type == protocol::TradeCorrectionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeCorrectionMessage::parse(iterator.message);
            checksum += bench::digest(message->originating_market_center_identifier.get());
            checksum += bench::digest(message->issue_symbol.get());
            checksum += bench::digest(message->security_class.get());
            checksum += bench::digest(message->original_trade_control_number.get());
            checksum += bench::digest(message->original_trade_price.integer());
            checksum += bench::digest(message->original_trade_size.get());
            checksum += bench::digest(message->original_sale_condition_modifier.original_settlement_type.get());
            checksum += bench::digest(message->original_sale_condition_modifier.original_trade_through_exemption.get());
            checksum += bench::digest(message->original_sale_condition_modifier.original_extended_hours_or_sold_code.get());
            checksum += bench::digest(message->original_sale_condition_modifier.original_special_sale_condition.get());
            checksum += bench::digest(message->corrected_trade_control_number.get());
            checksum += bench::digest(message->corrected_trade_price.integer());
            checksum += bench::digest(message->corrected_trade_size.get());
            checksum += bench::digest(message->corrected_sale_condition_modifier.corrected_settlement_type.get());
            checksum += bench::digest(message->corrected_sale_condition_modifier.corrected_trade_through_exemption.get());
            checksum += bench::digest(message->corrected_sale_condition_modifier.corrected_extended_hours_or_sold_code.get());
            checksum += bench::digest(message->corrected_sale_condition_modifier.corrected_special_sale_condition.get());
            checksum += bench::digest(message->consolidated_volume.get());
        } else if (iterator.message_type == protocol::LongFormTradeCorrectionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::LongFormTradeCorrectionMessage::parse(iterator.message);
            checksum += bench::digest(message->originating_market_center_identifier.get());
            checksum += bench::digest(message->issue_symbol.get());
            checksum += bench::digest(message->security_class.get());
            checksum += bench::digest(message->original_trade_control_number.get());
            checksum += bench::digest(message->original_trade_price_long.integer());
            checksum += bench::digest(message->original_trade_size.get());
            checksum += bench::digest(message->original_sale_condition_modifier.original_settlement_type.get());
            checksum += bench::digest(message->original_sale_condition_modifier.original_trade_through_exemption.get());
            checksum += bench::digest(message->original_sale_condition_modifier.original_extended_hours_or_sold_code.get());
            checksum += bench::digest(message->original_sale_condition_modifier.original_special_sale_condition.get());
            checksum += bench::digest(message->corrected_trade_control_number.get());
            checksum += bench::digest(message->corrected_trade_price_long.integer());
            checksum += bench::digest(message->corrected_trade_size.get());
            checksum += bench::digest(message->corrected_sale_condition_modifier.corrected_settlement_type.get());
            checksum += bench::digest(message->corrected_sale_condition_modifier.corrected_trade_through_exemption.get());
            checksum += bench::digest(message->corrected_sale_condition_modifier.corrected_extended_hours_or_sold_code.get());
            checksum += bench::digest(message->corrected_sale_condition_modifier.corrected_special_sale_condition.get());
            checksum += bench::digest(message->consolidated_volume.get());
        } else if (iterator.message_type == protocol::NextSharesTradeCorrectionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::NextSharesTradeCorrectionMessage::parse(iterator.message);
            checksum += bench::digest(message->market_center.get());
            checksum += bench::digest(message->issue_symbol.get());
            checksum += bench::digest(message->security_class.get());
            checksum += bench::digest(message->original_trade_control_number.get());
            checksum += bench::digest(message->original_proxy_price.integer());
            checksum += bench::digest(message->original_nav_offset_amount.integer());
            checksum += bench::digest(message->original_trade_size.get());
            checksum += bench::digest(message->original_sale_condition_modifier.original_settlement_type.get());
            checksum += bench::digest(message->original_sale_condition_modifier.original_trade_through_exemption.get());
            checksum += bench::digest(message->original_sale_condition_modifier.original_extended_hours_or_sold_code.get());
            checksum += bench::digest(message->original_sale_condition_modifier.original_special_sale_condition.get());
            checksum += bench::digest(message->corrected_trade_control_number.get());
            checksum += bench::digest(message->corrected_proxy_price.integer());
            checksum += bench::digest(message->corrected_nav_offset_amount.integer());
            checksum += bench::digest(message->corrected_trade_size.get());
            checksum += bench::digest(message->corrected_sale_condition_modifier.corrected_settlement_type.get());
            checksum += bench::digest(message->corrected_sale_condition_modifier.corrected_trade_through_exemption.get());
            checksum += bench::digest(message->corrected_sale_condition_modifier.corrected_extended_hours_or_sold_code.get());
            checksum += bench::digest(message->corrected_sale_condition_modifier.corrected_special_sale_condition.get());
            checksum += bench::digest(message->consolidated_volume.get());
        } else if (iterator.message_type == protocol::StockTradingActionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::StockTradingActionMessage::parse(iterator.message);
            checksum += bench::digest(message->reserved.get());
            checksum += bench::digest(message->issue_symbol.get());
            checksum += bench::digest(message->security_class.get());
            checksum += bench::digest(message->current_trading_state.get());
            checksum += bench::digest(message->reason.get());
        } else if (iterator.message_type == protocol::StockDirectoryMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::StockDirectoryMessage::parse(iterator.message);
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
            checksum += bench::digest(message->bloomberg_id.get());
        } else if (iterator.message_type == protocol::RegShoShortSalePriceTestRestrictedIndicatorMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::RegShoShortSalePriceTestRestrictedIndicatorMessage::parse(iterator.message);
            checksum += bench::digest(message->issue_symbol.get());
            checksum += bench::digest(message->reg_sho_action.get());
        } else if (iterator.message_type == protocol::AdjustedClosingPriceMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AdjustedClosingPriceMessage::parse(iterator.message);
            checksum += bench::digest(message->issue_symbol.get());
            checksum += bench::digest(message->security_class.get());
            checksum += bench::digest(message->adjusted_closing_price.integer());
        } else if (iterator.message_type == protocol::LongFormAdjustedClosingPriceMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::LongFormAdjustedClosingPriceMessage::parse(iterator.message);
            checksum += bench::digest(message->issue_symbol.get());
            checksum += bench::digest(message->security_class.get());
            checksum += bench::digest(message->adjusted_closing_price_long.integer());
        } else if (iterator.message_type == protocol::EndOfDayTradeSummaryMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::EndOfDayTradeSummaryMessage::parse(iterator.message);
            checksum += bench::digest(message->issue_symbol.get());
            checksum += bench::digest(message->market_category.get());
            checksum += bench::digest(message->consolidated_high_price.integer());
            checksum += bench::digest(message->consolidated_low_price.integer());
            checksum += bench::digest(message->consolidated_closing_price.integer());
            checksum += bench::digest(message->consolidated_volume.get());
            checksum += bench::digest(message->consolidated_open_price.integer());
        } else if (iterator.message_type == protocol::LongFormEndOfDayTradeSummaryMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::LongFormEndOfDayTradeSummaryMessage::parse(iterator.message);
            checksum += bench::digest(message->issue_symbol.get());
            checksum += bench::digest(message->market_category.get());
            checksum += bench::digest(message->consolidated_high_price_long.integer());
            checksum += bench::digest(message->consolidated_low_price_long.integer());
            checksum += bench::digest(message->consolidated_closing_price_long.integer());
            checksum += bench::digest(message->consolidated_volume.get());
            checksum += bench::digest(message->consolidated_open_price_long.integer());
        } else if (iterator.message_type == protocol::NextSharesEndOfDayTradeSummaryMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::NextSharesEndOfDayTradeSummaryMessage::parse(iterator.message);
            checksum += bench::digest(message->issue_symbol.get());
            checksum += bench::digest(message->market_category.get());
            checksum += bench::digest(message->consolidated_high_price.integer());
            checksum += bench::digest(message->nav_offset_amount_high.integer());
            checksum += bench::digest(message->consolidated_low_price.integer());
            checksum += bench::digest(message->nav_offset_amount_low.integer());
            checksum += bench::digest(message->consolidated_closing_price.integer());
            checksum += bench::digest(message->nav_offset_amount_closing.integer());
            checksum += bench::digest(message->consolidated_volume.get());
            checksum += bench::digest(message->consolidated_open_price.integer());
            checksum += bench::digest(message->nav_offset_amount_open.integer());
        } else if (iterator.message_type == protocol::IpoInformationMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::IpoInformationMessage::parse(iterator.message);
            checksum += bench::digest(message->issue_symbol.get());
            checksum += bench::digest(message->security_class.get());
            checksum += bench::digest(message->reference_for_net_change.get());
            checksum += bench::digest(message->reference_price.integer());
        } else if (iterator.message_type == protocol::MwcbDeclineLevelMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::MwcbDeclineLevelMessage::parse(iterator.message);
            checksum += bench::digest(message->level_1.integer());
            checksum += bench::digest(message->level_2.integer());
            checksum += bench::digest(message->level_3.integer());
        } else if (iterator.message_type == protocol::MwcbStatusMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::MwcbStatusMessage::parse(iterator.message);
            checksum += bench::digest(message->breached_level.get());
        } else if (iterator.message_type == protocol::IpoQuotingPeriodUpdateMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::IpoQuotingPeriodUpdateMessage::parse(iterator.message);
            checksum += bench::digest(message->stock.get());
            checksum += bench::digest(message->ipo_quotation_release_time.get());
            checksum += bench::digest(message->ipo_quotation_release_qualifier.get());
            checksum += bench::digest(message->ipo_price.integer());
        } else if (iterator.message_type == protocol::OperationalHaltMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OperationalHaltMessage::parse(iterator.message);
            checksum += bench::digest(message->stock.get());
            checksum += bench::digest(message->market_code.get());
            checksum += bench::digest(message->operational_halt_action.get());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nasdaq.NsmEquities.NlsPlus.Itch.v3.0", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
