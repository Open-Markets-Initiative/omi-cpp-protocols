// Nasdaq.NsmEquities.NlsPlus.Itch.v3.0 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/nsmequities/nlsplus/itch/v3.0.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <span>
#include <string>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "executables/benchmark/Benchmark.hpp"
#include "cpp/binary/flyweight/nasdaq/nsmequities/nlsplus/itch/v3.0/definitions.hpp"

namespace protocol = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        checksum += bench::digest(packet.packet_header().session());
        checksum += bench::digest(packet.packet_header().sequence_number());
        checksum += bench::digest(packet.packet_header().message_count());
    }

    // a message this test prints no values of, or a code no message answers to, still takes its entry
    template <typename Message>
    void on(const Message&) {
        ++index;
    }

    template <typename Code>
    void on_unknown(Code, std::span<const std::byte>) {
        ++index;
    }

    void on(const protocol::SystemEventMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.event_code());
    }

    void on(const protocol::TradeReportMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.originating_market_center_identifier());
        checksum += bench::digest(message.issue_symbol());
        checksum += bench::digest(message.security_class());
        checksum += bench::digest(message.trade_control_number());
        checksum += bench::digest(message.trade_price().mantissa());
        checksum += bench::digest(message.trade_size());
        checksum += bench::digest(message.sale_condition_modifier().settlement_type());
        checksum += bench::digest(message.sale_condition_modifier().trade_through_exemption());
        checksum += bench::digest(message.sale_condition_modifier().extended_hours_or_sold_code());
        checksum += bench::digest(message.sale_condition_modifier().special_sale_condition());
        checksum += bench::digest(message.consolidated_volume());
    }

    void on(const protocol::LongFormTradeReportMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.originating_market_center_identifier());
        checksum += bench::digest(message.issue_symbol());
        checksum += bench::digest(message.security_class());
        checksum += bench::digest(message.trade_control_number());
        checksum += bench::digest(message.trade_price_long().mantissa());
        checksum += bench::digest(message.trade_size());
        checksum += bench::digest(message.sale_condition_modifier().settlement_type());
        checksum += bench::digest(message.sale_condition_modifier().trade_through_exemption());
        checksum += bench::digest(message.sale_condition_modifier().extended_hours_or_sold_code());
        checksum += bench::digest(message.sale_condition_modifier().special_sale_condition());
        checksum += bench::digest(message.consolidated_volume());
    }

    void on(const protocol::NextSharesTradeReportMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.originating_market_center_identifier());
        checksum += bench::digest(message.next_shares_symbol());
        checksum += bench::digest(message.security_class());
        checksum += bench::digest(message.trade_control_number());
        checksum += bench::digest(message.proxy_price().mantissa());
        checksum += bench::digest(message.trade_size());
        checksum += bench::digest(message.nav_offset_amount().mantissa());
        checksum += bench::digest(message.sale_condition_modifier().settlement_type());
        checksum += bench::digest(message.sale_condition_modifier().trade_through_exemption());
        checksum += bench::digest(message.sale_condition_modifier().extended_hours_or_sold_code());
        checksum += bench::digest(message.sale_condition_modifier().special_sale_condition());
        checksum += bench::digest(message.consolidated_volume());
    }

    void on(const protocol::TradeCancelErrorMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.originating_market_center_identifier());
        checksum += bench::digest(message.issue_symbol());
        checksum += bench::digest(message.security_class());
        checksum += bench::digest(message.original_trade_control_number());
        checksum += bench::digest(message.original_trade_price().mantissa());
        checksum += bench::digest(message.original_trade_size());
        checksum += bench::digest(message.original_sale_condition_modifier().original_settlement_type());
        checksum += bench::digest(message.original_sale_condition_modifier().original_trade_through_exemption());
        checksum += bench::digest(message.original_sale_condition_modifier().original_extended_hours_or_sold_code());
        checksum += bench::digest(message.original_sale_condition_modifier().original_special_sale_condition());
        checksum += bench::digest(message.consolidated_volume());
    }

    void on(const protocol::LongFormTradeCancelErrorMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.originating_market_center_identifier());
        checksum += bench::digest(message.issue_symbol());
        checksum += bench::digest(message.security_class());
        checksum += bench::digest(message.original_trade_control_number());
        checksum += bench::digest(message.original_trade_price_long().mantissa());
        checksum += bench::digest(message.original_trade_size());
        checksum += bench::digest(message.original_sale_condition_modifier().original_settlement_type());
        checksum += bench::digest(message.original_sale_condition_modifier().original_trade_through_exemption());
        checksum += bench::digest(message.original_sale_condition_modifier().original_extended_hours_or_sold_code());
        checksum += bench::digest(message.original_sale_condition_modifier().original_special_sale_condition());
        checksum += bench::digest(message.consolidated_volume());
    }

    void on(const protocol::NextSharesTradeCancelErrorMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.market_center());
        checksum += bench::digest(message.issue_symbol());
        checksum += bench::digest(message.security_class());
        checksum += bench::digest(message.original_trade_control_number());
        checksum += bench::digest(message.original_proxy_price().mantissa());
        checksum += bench::digest(message.original_nav_offset_amount().mantissa());
        checksum += bench::digest(message.original_trade_size());
        checksum += bench::digest(message.original_sale_condition_modifier().original_settlement_type());
        checksum += bench::digest(message.original_sale_condition_modifier().original_trade_through_exemption());
        checksum += bench::digest(message.original_sale_condition_modifier().original_extended_hours_or_sold_code());
        checksum += bench::digest(message.original_sale_condition_modifier().original_special_sale_condition());
        checksum += bench::digest(message.consolidated_volume());
    }

    void on(const protocol::TradeCorrectionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.originating_market_center_identifier());
        checksum += bench::digest(message.issue_symbol());
        checksum += bench::digest(message.security_class());
        checksum += bench::digest(message.original_trade_control_number());
        checksum += bench::digest(message.original_trade_price().mantissa());
        checksum += bench::digest(message.original_trade_size());
        checksum += bench::digest(message.original_sale_condition_modifier().original_settlement_type());
        checksum += bench::digest(message.original_sale_condition_modifier().original_trade_through_exemption());
        checksum += bench::digest(message.original_sale_condition_modifier().original_extended_hours_or_sold_code());
        checksum += bench::digest(message.original_sale_condition_modifier().original_special_sale_condition());
        checksum += bench::digest(message.corrected_trade_control_number());
        checksum += bench::digest(message.corrected_trade_price().mantissa());
        checksum += bench::digest(message.corrected_trade_size());
        checksum += bench::digest(message.corrected_sale_condition_modifier().corrected_settlement_type());
        checksum += bench::digest(message.corrected_sale_condition_modifier().corrected_trade_through_exemption());
        checksum += bench::digest(message.corrected_sale_condition_modifier().corrected_extended_hours_or_sold_code());
        checksum += bench::digest(message.corrected_sale_condition_modifier().corrected_special_sale_condition());
        checksum += bench::digest(message.consolidated_volume());
    }

    void on(const protocol::LongFormTradeCorrectionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.originating_market_center_identifier());
        checksum += bench::digest(message.issue_symbol());
        checksum += bench::digest(message.security_class());
        checksum += bench::digest(message.original_trade_control_number());
        checksum += bench::digest(message.original_trade_price_long().mantissa());
        checksum += bench::digest(message.original_trade_size());
        checksum += bench::digest(message.original_sale_condition_modifier().original_settlement_type());
        checksum += bench::digest(message.original_sale_condition_modifier().original_trade_through_exemption());
        checksum += bench::digest(message.original_sale_condition_modifier().original_extended_hours_or_sold_code());
        checksum += bench::digest(message.original_sale_condition_modifier().original_special_sale_condition());
        checksum += bench::digest(message.corrected_trade_control_number());
        checksum += bench::digest(message.corrected_trade_price_long().mantissa());
        checksum += bench::digest(message.corrected_trade_size());
        checksum += bench::digest(message.corrected_sale_condition_modifier().corrected_settlement_type());
        checksum += bench::digest(message.corrected_sale_condition_modifier().corrected_trade_through_exemption());
        checksum += bench::digest(message.corrected_sale_condition_modifier().corrected_extended_hours_or_sold_code());
        checksum += bench::digest(message.corrected_sale_condition_modifier().corrected_special_sale_condition());
        checksum += bench::digest(message.consolidated_volume());
    }

    void on(const protocol::NextSharesTradeCorrectionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.market_center());
        checksum += bench::digest(message.issue_symbol());
        checksum += bench::digest(message.security_class());
        checksum += bench::digest(message.original_trade_control_number());
        checksum += bench::digest(message.original_proxy_price().mantissa());
        checksum += bench::digest(message.original_nav_offset_amount().mantissa());
        checksum += bench::digest(message.original_trade_size());
        checksum += bench::digest(message.original_sale_condition_modifier().original_settlement_type());
        checksum += bench::digest(message.original_sale_condition_modifier().original_trade_through_exemption());
        checksum += bench::digest(message.original_sale_condition_modifier().original_extended_hours_or_sold_code());
        checksum += bench::digest(message.original_sale_condition_modifier().original_special_sale_condition());
        checksum += bench::digest(message.corrected_trade_control_number());
        checksum += bench::digest(message.corrected_proxy_price().mantissa());
        checksum += bench::digest(message.corrected_nav_offset_amount().mantissa());
        checksum += bench::digest(message.corrected_trade_size());
        checksum += bench::digest(message.corrected_sale_condition_modifier().corrected_settlement_type());
        checksum += bench::digest(message.corrected_sale_condition_modifier().corrected_trade_through_exemption());
        checksum += bench::digest(message.corrected_sale_condition_modifier().corrected_extended_hours_or_sold_code());
        checksum += bench::digest(message.corrected_sale_condition_modifier().corrected_special_sale_condition());
        checksum += bench::digest(message.consolidated_volume());
    }

    void on(const protocol::StockTradingActionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.reserved());
        checksum += bench::digest(message.issue_symbol());
        checksum += bench::digest(message.security_class());
        checksum += bench::digest(message.current_trading_state());
        checksum += bench::digest(message.reason());
    }

    void on(const protocol::StockDirectoryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.market_category());
        checksum += bench::digest(message.financial_status_indicator());
        checksum += bench::digest(message.round_lot_size());
        checksum += bench::digest(message.round_lots_only());
        checksum += bench::digest(message.issue_classification());
        checksum += bench::digest(message.issue_sub_type());
        checksum += bench::digest(message.authenticity());
        checksum += bench::digest(message.short_sale_threshold_indicator());
        checksum += bench::digest(message.ipo_flag());
        checksum += bench::digest(message.luld_reference_price_tier());
        checksum += bench::digest(message.etp_flag());
        checksum += bench::digest(message.etp_leverage_factor());
        checksum += bench::digest(message.inverse_indicator());
        checksum += bench::digest(message.bloomberg_id());
    }

    void on(const protocol::RegShoShortSalePriceTestRestrictedIndicatorMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.issue_symbol());
        checksum += bench::digest(message.reg_sho_action());
    }

    void on(const protocol::AdjustedClosingPriceMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.issue_symbol());
        checksum += bench::digest(message.security_class());
        checksum += bench::digest(message.adjusted_closing_price().mantissa());
    }

    void on(const protocol::LongFormAdjustedClosingPriceMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.issue_symbol());
        checksum += bench::digest(message.security_class());
        checksum += bench::digest(message.adjusted_closing_price_long().mantissa());
    }

    void on(const protocol::EndOfDayTradeSummaryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.issue_symbol());
        checksum += bench::digest(message.market_category());
        checksum += bench::digest(message.consolidated_high_price().mantissa());
        checksum += bench::digest(message.consolidated_low_price().mantissa());
        checksum += bench::digest(message.consolidated_closing_price().mantissa());
        checksum += bench::digest(message.consolidated_volume());
        checksum += bench::digest(message.consolidated_open_price().mantissa());
    }

    void on(const protocol::LongFormEndOfDayTradeSummaryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.issue_symbol());
        checksum += bench::digest(message.market_category());
        checksum += bench::digest(message.consolidated_high_price_long().mantissa());
        checksum += bench::digest(message.consolidated_low_price_long().mantissa());
        checksum += bench::digest(message.consolidated_closing_price_long().mantissa());
        checksum += bench::digest(message.consolidated_volume());
        checksum += bench::digest(message.consolidated_open_price_long().mantissa());
    }

    void on(const protocol::NextSharesEndOfDayTradeSummaryMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.issue_symbol());
        checksum += bench::digest(message.market_category());
        checksum += bench::digest(message.consolidated_high_price().mantissa());
        checksum += bench::digest(message.nav_offset_amount_high().mantissa());
        checksum += bench::digest(message.consolidated_low_price().mantissa());
        checksum += bench::digest(message.nav_offset_amount_low().mantissa());
        checksum += bench::digest(message.consolidated_closing_price().mantissa());
        checksum += bench::digest(message.nav_offset_amount_closing().mantissa());
        checksum += bench::digest(message.consolidated_volume());
        checksum += bench::digest(message.consolidated_open_price().mantissa());
        checksum += bench::digest(message.nav_offset_amount_open().mantissa());
    }

    void on(const protocol::IpoInformationMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.issue_symbol());
        checksum += bench::digest(message.security_class());
        checksum += bench::digest(message.reference_for_net_change());
        checksum += bench::digest(message.reference_price().mantissa());
    }

    void on(const protocol::MwcbDeclineLevelMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.level_1().mantissa());
        checksum += bench::digest(message.level_2().mantissa());
        checksum += bench::digest(message.level_3().mantissa());
    }

    void on(const protocol::MwcbStatusMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.breached_level());
    }

    void on(const protocol::IpoQuotingPeriodUpdateMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.ipo_quotation_release_time());
        checksum += bench::digest(message.ipo_quotation_release_qualifier());
        checksum += bench::digest(message.ipo_price().mantissa());
    }

    void on(const protocol::OperationalHaltMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.stock());
        checksum += bench::digest(message.market_code());
        checksum += bench::digest(message.operational_halt_action());
    }
};

// The values the Flyweight reader reads from one datagram, folded into a checksum. A datagram it cannot
// read is a value the model never reads, so the benchmark refuses to time it.
std::uint64_t read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::PacketReader::read(std::span<const std::byte>(frame.payload, frame.payload_len), reader);
    } catch (const protocol::DecodeError& error) {
        throw;
    }

    return reader.checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Nasdaq.NsmEquities.NlsPlus.Itch.v3.0", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
