// B3.B3Derivatives.BinaryUmdf.Sbe.v1.6 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/b3/b3derivatives/binaryumdf/sbe/v1.6.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/b3/b3derivatives/binaryumdf/sbe/v1.6/definitions.hpp"

namespace protocol = ::b3::b3derivatives::binaryumdf::sbe::v1_6;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        checksum += bench::digest(packet.packet_header().channel_id());
        checksum += bench::digest(packet.packet_header().packet_reserved());
        checksum += bench::digest(packet.packet_header().sequence_version());
        checksum += bench::digest(packet.packet_header().sequence_number());
        checksum += bench::digest(packet.packet_header().sending_time());
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

    void on(const protocol::SequenceMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.next_seq_no());
    }

    void on(const protocol::SecurityStatus3Message& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().unused());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += bench::digest(message.trading_session_id());
        checksum += bench::digest(message.security_trading_status());
        checksum += (message.security_trading_event().has_value() ? bench::digest((*message.security_trading_event())) : std::uint64_t{0});
        checksum += bench::digest(message.trade_date());
        checksum += (message.trad_ses_open_time().has_value() ? bench::digest((*message.trad_ses_open_time())) : std::uint64_t{0});
        checksum += (message.transact_time().has_value() ? bench::digest((*message.transact_time())) : std::uint64_t{0});
        checksum += (message.rpt_seq().has_value() ? bench::digest((*message.rpt_seq())) : std::uint64_t{0});
    }

    void on(const protocol::SecurityGroupPhase10Message& message) {
        checksum += index++;
        checksum += bench::digest(message.security_group());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().unused());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += bench::digest(message.trading_session_id());
        checksum += bench::digest(message.trading_session_sub_id());
        checksum += (message.security_trading_event().has_value() ? bench::digest((*message.security_trading_event())) : std::uint64_t{0});
        checksum += bench::digest(message.trade_date());
        checksum += (message.trad_ses_open_time().has_value() ? bench::digest((*message.trad_ses_open_time())) : std::uint64_t{0});
        checksum += (message.transact_time().has_value() ? bench::digest((*message.transact_time())) : std::uint64_t{0});
    }

    void on(const protocol::DeprecatedSecurityDefinitionMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.security_exchange());
        checksum += bench::digest(message.security_id_source());
        checksum += bench::digest(message.security_group());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.security_update_action());
        checksum += bench::digest(message.security_type());
        checksum += bench::digest(message.security_sub_type());
        checksum += bench::digest(message.tot_no_related_sym());
        checksum += (message.min_price_increment().has_value() ? bench::digest((*message.min_price_increment()).mantissa()) : std::uint64_t{0});
        checksum += (message.strike_price().has_value() ? bench::digest((*message.strike_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.contract_multiplier().has_value() ? bench::digest((*message.contract_multiplier()).mantissa()) : std::uint64_t{0});
        checksum += (message.price_divisor().has_value() ? bench::digest((*message.price_divisor()).mantissa()) : std::uint64_t{0});
        checksum += (message.security_validity_timestamp().has_value() ? bench::digest((*message.security_validity_timestamp())) : std::uint64_t{0});
        checksum += (message.no_shares_issued().has_value() ? bench::digest((*message.no_shares_issued())) : std::uint64_t{0});
        checksum += (message.clearing_house_id().has_value() ? bench::digest((*message.clearing_house_id())) : std::uint64_t{0});
        checksum += (message.min_order_qty().has_value() ? bench::digest((*message.min_order_qty())) : std::uint64_t{0});
        checksum += (message.max_order_qty().has_value() ? bench::digest((*message.max_order_qty())) : std::uint64_t{0});
        checksum += (message.min_lot_size().has_value() ? bench::digest((*message.min_lot_size())) : std::uint64_t{0});
        checksum += (message.min_trade_vol().has_value() ? bench::digest((*message.min_trade_vol())) : std::uint64_t{0});
        checksum += (message.corporate_action_event_id().has_value() ? bench::digest((*message.corporate_action_event_id())) : std::uint64_t{0});
        checksum += bench::digest(message.issue_date());
        checksum += (message.maturity_date().has_value() ? bench::digest((*message.maturity_date())) : std::uint64_t{0});
        checksum += (message.start_date().has_value() ? bench::digest((*message.start_date())) : std::uint64_t{0});
        checksum += (message.end_date().has_value() ? bench::digest((*message.end_date())) : std::uint64_t{0});
        checksum += (message.settl_type().has_value() ? bench::digest((*message.settl_type())) : std::uint64_t{0});
        checksum += (message.settl_date().has_value() ? bench::digest((*message.settl_date())) : std::uint64_t{0});
        checksum += (message.dated_date().has_value() ? bench::digest((*message.dated_date())) : std::uint64_t{0});
        checksum += bench::digest(message.asset());
        checksum += bench::digest(message.cfi_code());
        checksum += bench::digest(message.maturity_month_year().year());
        checksum += bench::digest(message.maturity_month_year().month());
        checksum += bench::digest(message.maturity_month_year().day());
        checksum += bench::digest(message.maturity_month_year().week());
        checksum += bench::digest(message.contract_settl_month().year());
        checksum += bench::digest(message.contract_settl_month().month());
        checksum += bench::digest(message.contract_settl_month().day());
        checksum += bench::digest(message.contract_settl_month().week());
        checksum += bench::digest(message.currency());
        checksum += (message.lot_type().has_value() ? bench::digest((*message.lot_type())) : std::uint64_t{0});
        checksum += (message.tick_size_denominator().has_value() ? bench::digest((*message.tick_size_denominator())) : std::uint64_t{0});
        checksum += bench::digest(message.product());
        checksum += (message.exercise_style().has_value() ? bench::digest((*message.exercise_style())) : std::uint64_t{0});
        checksum += (message.put_or_call().has_value() ? bench::digest((*message.put_or_call())) : std::uint64_t{0});
        checksum += (message.price_type().has_value() ? bench::digest((*message.price_type())) : std::uint64_t{0});
        checksum += (message.market_segment_id().has_value() ? bench::digest((*message.market_segment_id())) : std::uint64_t{0});
        checksum += (message.governance_indicator().has_value() ? bench::digest((*message.governance_indicator())) : std::uint64_t{0});
        checksum += (message.security_match_type().has_value() ? bench::digest((*message.security_match_type())) : std::uint64_t{0});
        checksum += (message.last_fragment().has_value() ? bench::digest((*message.last_fragment())) : std::uint64_t{0});
        checksum += (message.multi_leg_model().has_value() ? bench::digest((*message.multi_leg_model())) : std::uint64_t{0});
        checksum += (message.multi_leg_price_method().has_value() ? bench::digest((*message.multi_leg_price_method())) : std::uint64_t{0});
        checksum += (message.min_cross_qty().has_value() ? bench::digest((*message.min_cross_qty())) : std::uint64_t{0});
    }

    void on(const protocol::News5Message& message) {
        checksum += index++;
        checksum += (message.security_id_optional().has_value() ? bench::digest((*message.security_id_optional())) : std::uint64_t{0});
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().unused());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += bench::digest(message.news_source());
        checksum += bench::digest(message.part_count());
        checksum += bench::digest(message.part_number());
        checksum += (message.news_id().has_value() ? bench::digest((*message.news_id())) : std::uint64_t{0});
        checksum += (message.orig_time().has_value() ? bench::digest((*message.orig_time())) : std::uint64_t{0});
        checksum += bench::digest(message.total_text_length());
    }

    void on(const protocol::EmptyBookMessage& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().unused());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += (message.md_entry_timestamp().has_value() ? bench::digest((*message.md_entry_timestamp())) : std::uint64_t{0});
    }

    void on(const protocol::ChannelReset11Message& message) {
        checksum += index++;
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().unused());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += (message.md_entry_timestamp().has_value() ? bench::digest((*message.md_entry_timestamp())) : std::uint64_t{0});
    }

    void on(const protocol::OpeningPrice15Message& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().unused());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += bench::digest(message.md_update_action());
        checksum += bench::digest(message.open_close_settl_flag());
        checksum += bench::digest(message.md_future_price().mantissa());
        checksum += (message.net_chg_prev_day().has_value() ? bench::digest((*message.net_chg_prev_day()).mantissa()) : std::uint64_t{0});
        checksum += bench::digest(message.trade_date());
        checksum += (message.md_entry_timestamp().has_value() ? bench::digest((*message.md_entry_timestamp())) : std::uint64_t{0});
        checksum += (message.rpt_seq().has_value() ? bench::digest((*message.rpt_seq())) : std::uint64_t{0});
    }

    void on(const protocol::TheoreticalOpeningPrice16Message& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().unused());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += bench::digest(message.md_update_action());
        checksum += bench::digest(message.trade_date());
        checksum += (message.md_corporate_offset_price_optional().has_value() ? bench::digest((*message.md_corporate_offset_price_optional()).mantissa()) : std::uint64_t{0});
        checksum += (message.md_entry_size_quantity_optional().has_value() ? bench::digest((*message.md_entry_size_quantity_optional())) : std::uint64_t{0});
        checksum += (message.md_entry_timestamp().has_value() ? bench::digest((*message.md_entry_timestamp())) : std::uint64_t{0});
        checksum += (message.rpt_seq().has_value() ? bench::digest((*message.rpt_seq())) : std::uint64_t{0});
    }

    void on(const protocol::ClosingPrice17Message& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().unused());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += bench::digest(message.open_close_settl_flag());
        checksum += bench::digest(message.md_corporate_price().mantissa());
        checksum += (message.last_trade_date().has_value() ? bench::digest((*message.last_trade_date())) : std::uint64_t{0});
        checksum += bench::digest(message.trade_date());
        checksum += (message.md_entry_timestamp().has_value() ? bench::digest((*message.md_entry_timestamp())) : std::uint64_t{0});
        checksum += (message.rpt_seq().has_value() ? bench::digest((*message.rpt_seq())) : std::uint64_t{0});
    }

    void on(const protocol::AuctionImbalance19Message& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().unused());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += bench::digest(message.md_update_action());
        checksum += bench::digest(message.imbalance_condition().unused_imbalance_condition_0());
        checksum += bench::digest(message.imbalance_condition().unused_imbalance_condition_1());
        checksum += bench::digest(message.imbalance_condition().unused_imbalance_condition_2());
        checksum += bench::digest(message.imbalance_condition().unused_imbalance_condition_3());
        checksum += bench::digest(message.imbalance_condition().unused_imbalance_condition_4());
        checksum += bench::digest(message.imbalance_condition().unused_imbalance_condition_5());
        checksum += bench::digest(message.imbalance_condition().unused_imbalance_condition_6());
        checksum += bench::digest(message.imbalance_condition().unused_imbalance_condition_7());
        checksum += bench::digest(message.imbalance_condition().imbalance_more_buyers());
        checksum += bench::digest(message.imbalance_condition().imbalance_more_sellers());
        checksum += bench::digest(message.imbalance_condition().reserved_6());
        checksum += (message.md_entry_size_quantity_optional().has_value() ? bench::digest((*message.md_entry_size_quantity_optional())) : std::uint64_t{0});
        checksum += (message.md_entry_timestamp().has_value() ? bench::digest((*message.md_entry_timestamp())) : std::uint64_t{0});
        checksum += (message.rpt_seq().has_value() ? bench::digest((*message.rpt_seq())) : std::uint64_t{0});
    }

    void on(const protocol::PriceBand20Message& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().unused());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += (message.price_band_type().has_value() ? bench::digest((*message.price_band_type())) : std::uint64_t{0});
        checksum += (message.price_limit_type().has_value() ? bench::digest((*message.price_limit_type())) : std::uint64_t{0});
        checksum += (message.price_band_midpoint_price_type().has_value() ? bench::digest((*message.price_band_midpoint_price_type())) : std::uint64_t{0});
        checksum += (message.low_limit_price().has_value() ? bench::digest((*message.low_limit_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.high_limit_price().has_value() ? bench::digest((*message.high_limit_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.trading_reference_price().has_value() ? bench::digest((*message.trading_reference_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.md_entry_timestamp().has_value() ? bench::digest((*message.md_entry_timestamp())) : std::uint64_t{0});
        checksum += (message.rpt_seq().has_value() ? bench::digest((*message.rpt_seq())) : std::uint64_t{0});
    }

    void on(const protocol::QuantityBand21Message& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().unused());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += (message.avg_daily_traded_qty().has_value() ? bench::digest((*message.avg_daily_traded_qty())) : std::uint64_t{0});
        checksum += (message.max_trade_vol().has_value() ? bench::digest((*message.max_trade_vol())) : std::uint64_t{0});
        checksum += (message.md_entry_timestamp().has_value() ? bench::digest((*message.md_entry_timestamp())) : std::uint64_t{0});
        checksum += (message.rpt_seq().has_value() ? bench::digest((*message.rpt_seq())) : std::uint64_t{0});
    }

    void on(const protocol::HighPrice24Message& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().unused());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += bench::digest(message.md_update_action());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.md_future_price().mantissa());
        checksum += (message.md_entry_timestamp().has_value() ? bench::digest((*message.md_entry_timestamp())) : std::uint64_t{0});
        checksum += (message.rpt_seq().has_value() ? bench::digest((*message.rpt_seq())) : std::uint64_t{0});
    }

    void on(const protocol::LowPrice25Message& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().unused());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += bench::digest(message.md_update_action());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.md_future_price().mantissa());
        checksum += (message.md_entry_timestamp().has_value() ? bench::digest((*message.md_entry_timestamp())) : std::uint64_t{0});
        checksum += (message.rpt_seq().has_value() ? bench::digest((*message.rpt_seq())) : std::uint64_t{0});
    }

    void on(const protocol::LastTradePrice27Message& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().unused());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += bench::digest(message.trading_session_id());
        checksum += bench::digest(message.trade_condition().opening_price());
        checksum += bench::digest(message.trade_condition().crossed());
        checksum += bench::digest(message.trade_condition().last_trade_at_the_same_price());
        checksum += bench::digest(message.trade_condition().out_of_sequence());
        checksum += bench::digest(message.trade_condition().unused_trade_condition_4());
        checksum += bench::digest(message.trade_condition().unused_trade_condition_5());
        checksum += bench::digest(message.trade_condition().trade_on_behalf());
        checksum += bench::digest(message.trade_condition().unused_trade_condition_7());
        checksum += bench::digest(message.trade_condition().unused_trade_condition_8());
        checksum += bench::digest(message.trade_condition().unused_trade_condition_9());
        checksum += bench::digest(message.trade_condition().unused_trade_condition_10());
        checksum += bench::digest(message.trade_condition().unused_trade_condition_11());
        checksum += bench::digest(message.trade_condition().unused_trade_condition_12());
        checksum += bench::digest(message.trade_condition().regular_trade());
        checksum += bench::digest(message.trade_condition().block_trade());
        checksum += bench::digest(message.trade_condition().unused_trade_condition_15());
        checksum += bench::digest(message.md_future_price().mantissa());
        checksum += bench::digest(message.md_entry_size_quantity());
        checksum += bench::digest(message.trade_id());
        checksum += (message.md_entry_buyer().has_value() ? bench::digest((*message.md_entry_buyer())) : std::uint64_t{0});
        checksum += (message.md_entry_seller().has_value() ? bench::digest((*message.md_entry_seller())) : std::uint64_t{0});
        checksum += bench::digest(message.trade_date());
        checksum += (message.md_entry_timestamp().has_value() ? bench::digest((*message.md_entry_timestamp())) : std::uint64_t{0});
        checksum += (message.rpt_seq().has_value() ? bench::digest((*message.rpt_seq())) : std::uint64_t{0});
        checksum += (message.seller_days().has_value() ? bench::digest((*message.seller_days())) : std::uint64_t{0});
        checksum += (message.md_entry_interest_rate().has_value() ? bench::digest((*message.md_entry_interest_rate()).mantissa()) : std::uint64_t{0});
        checksum += (message.trd_sub_type().has_value() ? bench::digest((*message.trd_sub_type())) : std::uint64_t{0});
    }

    void on(const protocol::SnapshotFullRefreshHeader30Message& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.last_msg_seq_num_processed());
        checksum += bench::digest(message.tot_num_reports());
        checksum += bench::digest(message.tot_num_bids());
        checksum += bench::digest(message.tot_num_offers());
        checksum += bench::digest(message.tot_num_stats());
        checksum += (message.last_rpt_seq().has_value() ? bench::digest((*message.last_rpt_seq())) : std::uint64_t{0});
    }

    void on(const protocol::OrderMbO50Message& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().unused());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += bench::digest(message.md_update_action());
        checksum += bench::digest(message.md_entry_type());
        checksum += (message.md_corporate_offset_price_optional().has_value() ? bench::digest((*message.md_corporate_offset_price_optional()).mantissa()) : std::uint64_t{0});
        checksum += bench::digest(message.md_entry_size_quantity());
        checksum += bench::digest(message.md_entry_position_no());
        checksum += (message.entering_firm().has_value() ? bench::digest((*message.entering_firm())) : std::uint64_t{0});
        checksum += (message.md_insert_timestamp().has_value() ? bench::digest((*message.md_insert_timestamp())) : std::uint64_t{0});
        checksum += bench::digest(message.secondary_order_id());
        checksum += (message.rpt_seq().has_value() ? bench::digest((*message.rpt_seq())) : std::uint64_t{0});
        checksum += (message.md_entry_timestamp().has_value() ? bench::digest((*message.md_entry_timestamp())) : std::uint64_t{0});
    }

    void on(const protocol::DeleteOrderMbO51Message& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().unused());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += bench::digest(message.md_entry_type());
        checksum += bench::digest(message.md_entry_position_no());
        checksum += (message.md_entry_size_quantity_optional().has_value() ? bench::digest((*message.md_entry_size_quantity_optional())) : std::uint64_t{0});
        checksum += bench::digest(message.secondary_order_id());
        checksum += (message.md_entry_timestamp().has_value() ? bench::digest((*message.md_entry_timestamp())) : std::uint64_t{0});
        checksum += (message.rpt_seq().has_value() ? bench::digest((*message.rpt_seq())) : std::uint64_t{0});
    }

    void on(const protocol::MassDeleteOrdersMbO52Message& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().unused());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += bench::digest(message.md_update_action());
        checksum += bench::digest(message.md_entry_type());
        checksum += bench::digest(message.md_entry_position_no());
        checksum += (message.md_entry_timestamp().has_value() ? bench::digest((*message.md_entry_timestamp())) : std::uint64_t{0});
        checksum += (message.rpt_seq().has_value() ? bench::digest((*message.rpt_seq())) : std::uint64_t{0});
    }

    void on(const protocol::Trade53Message& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().unused());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += bench::digest(message.trading_session_id());
        checksum += bench::digest(message.trade_condition().opening_price());
        checksum += bench::digest(message.trade_condition().crossed());
        checksum += bench::digest(message.trade_condition().last_trade_at_the_same_price());
        checksum += bench::digest(message.trade_condition().out_of_sequence());
        checksum += bench::digest(message.trade_condition().unused_trade_condition_4());
        checksum += bench::digest(message.trade_condition().unused_trade_condition_5());
        checksum += bench::digest(message.trade_condition().trade_on_behalf());
        checksum += bench::digest(message.trade_condition().unused_trade_condition_7());
        checksum += bench::digest(message.trade_condition().unused_trade_condition_8());
        checksum += bench::digest(message.trade_condition().unused_trade_condition_9());
        checksum += bench::digest(message.trade_condition().unused_trade_condition_10());
        checksum += bench::digest(message.trade_condition().unused_trade_condition_11());
        checksum += bench::digest(message.trade_condition().unused_trade_condition_12());
        checksum += bench::digest(message.trade_condition().regular_trade());
        checksum += bench::digest(message.trade_condition().block_trade());
        checksum += bench::digest(message.trade_condition().unused_trade_condition_15());
        checksum += bench::digest(message.md_future_price().mantissa());
        checksum += bench::digest(message.md_entry_size_quantity());
        checksum += bench::digest(message.trade_id());
        checksum += (message.md_entry_buyer().has_value() ? bench::digest((*message.md_entry_buyer())) : std::uint64_t{0});
        checksum += (message.md_entry_seller().has_value() ? bench::digest((*message.md_entry_seller())) : std::uint64_t{0});
        checksum += bench::digest(message.trade_date());
        checksum += (message.trd_sub_type().has_value() ? bench::digest((*message.trd_sub_type())) : std::uint64_t{0});
        checksum += (message.md_entry_timestamp().has_value() ? bench::digest((*message.md_entry_timestamp())) : std::uint64_t{0});
        checksum += (message.rpt_seq().has_value() ? bench::digest((*message.rpt_seq())) : std::uint64_t{0});
    }

    void on(const protocol::ForwardTrade54Message& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().unused());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += bench::digest(message.trading_session_id());
        checksum += bench::digest(message.trade_condition().opening_price());
        checksum += bench::digest(message.trade_condition().crossed());
        checksum += bench::digest(message.trade_condition().last_trade_at_the_same_price());
        checksum += bench::digest(message.trade_condition().out_of_sequence());
        checksum += bench::digest(message.trade_condition().unused_trade_condition_4());
        checksum += bench::digest(message.trade_condition().unused_trade_condition_5());
        checksum += bench::digest(message.trade_condition().trade_on_behalf());
        checksum += bench::digest(message.trade_condition().unused_trade_condition_7());
        checksum += bench::digest(message.trade_condition().unused_trade_condition_8());
        checksum += bench::digest(message.trade_condition().unused_trade_condition_9());
        checksum += bench::digest(message.trade_condition().unused_trade_condition_10());
        checksum += bench::digest(message.trade_condition().unused_trade_condition_11());
        checksum += bench::digest(message.trade_condition().unused_trade_condition_12());
        checksum += bench::digest(message.trade_condition().regular_trade());
        checksum += bench::digest(message.trade_condition().block_trade());
        checksum += bench::digest(message.trade_condition().unused_trade_condition_15());
        checksum += bench::digest(message.md_future_price().mantissa());
        checksum += bench::digest(message.md_entry_size_quantity());
        checksum += bench::digest(message.trade_id());
        checksum += (message.md_entry_buyer().has_value() ? bench::digest((*message.md_entry_buyer())) : std::uint64_t{0});
        checksum += (message.md_entry_seller().has_value() ? bench::digest((*message.md_entry_seller())) : std::uint64_t{0});
        checksum += bench::digest(message.trade_date());
        checksum += (message.md_entry_timestamp().has_value() ? bench::digest((*message.md_entry_timestamp())) : std::uint64_t{0});
        checksum += (message.rpt_seq().has_value() ? bench::digest((*message.rpt_seq())) : std::uint64_t{0});
        checksum += (message.seller_days().has_value() ? bench::digest((*message.seller_days())) : std::uint64_t{0});
        checksum += (message.md_entry_interest_rate().has_value() ? bench::digest((*message.md_entry_interest_rate()).mantissa()) : std::uint64_t{0});
        checksum += (message.trd_sub_type().has_value() ? bench::digest((*message.trd_sub_type())) : std::uint64_t{0});
    }

    void on(const protocol::ExecutionSummary55Message& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.aggressor_side());
        checksum += bench::digest(message.last_px().mantissa());
        checksum += bench::digest(message.fill_qty());
        checksum += (message.traded_hidden_qty().has_value() ? bench::digest((*message.traded_hidden_qty())) : std::uint64_t{0});
        checksum += (message.cxl_qty().has_value() ? bench::digest((*message.cxl_qty())) : std::uint64_t{0});
        checksum += (message.aggressor_time().has_value() ? bench::digest((*message.aggressor_time())) : std::uint64_t{0});
        checksum += (message.rpt_seq().has_value() ? bench::digest((*message.rpt_seq())) : std::uint64_t{0});
        checksum += (message.md_entry_timestamp().has_value() ? bench::digest((*message.md_entry_timestamp())) : std::uint64_t{0});
    }

    void on(const protocol::ExecutionStatistics56Message& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().unused());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += bench::digest(message.trading_session_id());
        checksum += bench::digest(message.trade_date());
        checksum += bench::digest(message.trade_volume());
        checksum += (message.vwap_px().has_value() ? bench::digest((*message.vwap_px()).mantissa()) : std::uint64_t{0});
        checksum += (message.net_chg_prev_day().has_value() ? bench::digest((*message.net_chg_prev_day()).mantissa()) : std::uint64_t{0});
        checksum += bench::digest(message.number_of_trades());
        checksum += (message.md_entry_timestamp().has_value() ? bench::digest((*message.md_entry_timestamp())) : std::uint64_t{0});
        checksum += (message.rpt_seq().has_value() ? bench::digest((*message.rpt_seq())) : std::uint64_t{0});
    }

    void on(const protocol::TradeBust57Message& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().unused());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += bench::digest(message.trading_session_id());
        checksum += bench::digest(message.md_future_price().mantissa());
        checksum += bench::digest(message.md_entry_size_quantity());
        checksum += bench::digest(message.trade_id());
        checksum += bench::digest(message.trade_date());
        checksum += (message.md_entry_timestamp().has_value() ? bench::digest((*message.md_entry_timestamp())) : std::uint64_t{0});
        checksum += (message.rpt_seq().has_value() ? bench::digest((*message.rpt_seq())) : std::uint64_t{0});
    }

    void on(const protocol::SnapshotFullRefreshOrdersMbO71Message& message) {
        checksum += index++;
        checksum += bench::digest(message.security_id());
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
    return bench::run("B3.B3Derivatives.BinaryUmdf.Sbe.v1.6", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
