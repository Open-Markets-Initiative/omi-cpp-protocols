// Cme.Globex.Mdp3.Sbe.v1.13 benchmark, through the Flyweight reader: every value it reads from every message of the simulated
// sequence (tests/simulated/cme/globex/mdp3/sbe/v1.13.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/flyweight/cme/globex/mdp3/sbe/v1.13/definitions.hpp"

namespace protocol = ::cme::globex::mdp3::sbe::v1_13;

namespace {

// The messages Mktdata Payload selects, their values set in the entry of the message holding it
struct MktdataPayloadHandler {
    std::uint64_t& checksum;

    void on(const protocol::ChannelReset& message) {
        checksum += bench::digest(message.transact_time());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().reserved());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
    }

    void on(const protocol::AdminLogin& message) {
        checksum += bench::digest(message.heart_bt_int());
    }

    void on(const protocol::AdminLogout& message) {
        checksum += bench::digest(message.logout_text());
    }

    void on(const protocol::SecurityStatus& message) {
        checksum += bench::digest(message.transact_time());
        checksum += bench::digest(message.security_group());
        checksum += bench::digest(message.asset());
        checksum += (message.security_id_optional().has_value() ? bench::digest((*message.security_id_optional())) : std::uint64_t{0});
        checksum += (message.trade_date().has_value() ? bench::digest((*message.trade_date())) : std::uint64_t{0});
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().reserved());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += (message.security_trading_status().has_value() ? bench::digest((*message.security_trading_status())) : std::uint64_t{0});
        checksum += bench::digest(message.halt_reason());
        checksum += bench::digest(message.security_trading_event());
    }

    void on(const protocol::MdIncrementalRefreshVolume& message) {
        checksum += bench::digest(message.transact_time());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().reserved());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
    }

    void on(const protocol::QuoteRequest& message) {
        checksum += bench::digest(message.transact_time());
        checksum += bench::digest(message.quote_req_id());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().reserved());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
    }

    void on(const protocol::MdIncrementalRefreshBook& message) {
        checksum += bench::digest(message.transact_time());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().reserved());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
    }

    void on(const protocol::MdIncrementalRefreshOrderBook& message) {
        checksum += bench::digest(message.transact_time());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().reserved());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
    }

    void on(const protocol::MdIncrementalRefreshTradeSummary& message) {
        checksum += bench::digest(message.transact_time());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().reserved());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
    }

    void on(const protocol::MdIncrementalRefreshDailyStatistics& message) {
        checksum += bench::digest(message.transact_time());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().reserved());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
    }

    void on(const protocol::MdIncrementalRefreshLimitsBanding& message) {
        checksum += bench::digest(message.transact_time());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().reserved());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
    }

    void on(const protocol::MdIncrementalRefreshSessionStatistics& message) {
        checksum += bench::digest(message.transact_time());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().reserved());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
    }

    void on(const protocol::SnapshotFullRefresh& message) {
        checksum += bench::digest(message.last_msg_seq_num_processed());
        checksum += bench::digest(message.tot_num_reports());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.rpt_seq());
        checksum += bench::digest(message.transact_time());
        checksum += bench::digest(message.last_update_time());
        checksum += (message.trade_date().has_value() ? bench::digest((*message.trade_date())) : std::uint64_t{0});
        checksum += (message.md_security_trading_status().has_value() ? bench::digest((*message.md_security_trading_status())) : std::uint64_t{0});
        checksum += (message.high_limit_price().has_value() ? bench::digest((*message.high_limit_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.low_limit_price().has_value() ? bench::digest((*message.low_limit_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.max_price_variation().has_value() ? bench::digest((*message.max_price_variation()).mantissa()) : std::uint64_t{0});
    }

    void on(const protocol::SnapshotFullRefreshOrderBook& message) {
        checksum += bench::digest(message.last_msg_seq_num_processed());
        checksum += bench::digest(message.tot_num_reports());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.no_chunks());
        checksum += bench::digest(message.current_chunk());
        checksum += bench::digest(message.transact_time());
    }

    void on(const protocol::MdInstrumentDefinitionFuture& message) {
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().reserved());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += (message.tot_num_reports_optional().has_value() ? bench::digest((*message.tot_num_reports_optional())) : std::uint64_t{0});
        checksum += bench::digest(message.security_update_action());
        checksum += bench::digest(message.last_update_time());
        checksum += (message.md_security_trading_status().has_value() ? bench::digest((*message.md_security_trading_status())) : std::uint64_t{0});
        checksum += bench::digest(message.appl_id());
        checksum += bench::digest(message.market_segment_id());
        checksum += bench::digest(message.underlying_product());
        checksum += bench::digest(message.security_exchange());
        checksum += bench::digest(message.security_group());
        checksum += bench::digest(message.asset());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.security_type());
        checksum += bench::digest(message.cfi_code());
        checksum += (message.maturity_month_year().year().has_value() ? bench::digest((*message.maturity_month_year().year())) : std::uint64_t{0});
        checksum += (message.maturity_month_year().month().has_value() ? bench::digest((*message.maturity_month_year().month())) : std::uint64_t{0});
        checksum += (message.maturity_month_year().day().has_value() ? bench::digest((*message.maturity_month_year().day())) : std::uint64_t{0});
        checksum += (message.maturity_month_year().week().has_value() ? bench::digest((*message.maturity_month_year().week())) : std::uint64_t{0});
        checksum += bench::digest(message.currency());
        checksum += bench::digest(message.settl_currency());
        checksum += bench::digest(message.match_algorithm());
        checksum += bench::digest(message.min_trade_vol());
        checksum += bench::digest(message.max_trade_vol());
        checksum += bench::digest(message.min_price_increment_ex().mantissa());
        checksum += bench::digest(message.display_factor().mantissa());
        checksum += (message.main_fraction().has_value() ? bench::digest((*message.main_fraction())) : std::uint64_t{0});
        checksum += (message.sub_fraction().has_value() ? bench::digest((*message.sub_fraction())) : std::uint64_t{0});
        checksum += (message.price_display_format().has_value() ? bench::digest((*message.price_display_format())) : std::uint64_t{0});
        checksum += bench::digest(message.unit_of_measure());
        checksum += (message.unit_of_measure_qty().has_value() ? bench::digest((*message.unit_of_measure_qty()).mantissa()) : std::uint64_t{0});
        checksum += (message.trading_reference_price().has_value() ? bench::digest((*message.trading_reference_price()).mantissa()) : std::uint64_t{0});
        checksum += bench::digest(message.settl_price_type().final_daily());
        checksum += bench::digest(message.settl_price_type().actual());
        checksum += bench::digest(message.settl_price_type().rounded());
        checksum += bench::digest(message.settl_price_type().intraday());
        checksum += bench::digest(message.settl_price_type().reserved_bits());
        checksum += bench::digest(message.settl_price_type().unused_settl_price_type_5());
        checksum += bench::digest(message.settl_price_type().unused_settl_price_type_6());
        checksum += bench::digest(message.settl_price_type().null_value());
        checksum += (message.open_interest_qty().has_value() ? bench::digest((*message.open_interest_qty())) : std::uint64_t{0});
        checksum += (message.cleared_volume().has_value() ? bench::digest((*message.cleared_volume())) : std::uint64_t{0});
        checksum += (message.high_limit_price().has_value() ? bench::digest((*message.high_limit_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.low_limit_price().has_value() ? bench::digest((*message.low_limit_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.max_price_variation().has_value() ? bench::digest((*message.max_price_variation()).mantissa()) : std::uint64_t{0});
        checksum += (message.decay_quantity().has_value() ? bench::digest((*message.decay_quantity())) : std::uint64_t{0});
        checksum += (message.decay_start_date().has_value() ? bench::digest((*message.decay_start_date())) : std::uint64_t{0});
        checksum += (message.original_contract_size().has_value() ? bench::digest((*message.original_contract_size())) : std::uint64_t{0});
        checksum += (message.contract_multiplier().has_value() ? bench::digest((*message.contract_multiplier())) : std::uint64_t{0});
        checksum += (message.contract_multiplier_unit().has_value() ? bench::digest((*message.contract_multiplier_unit())) : std::uint64_t{0});
        checksum += (message.flow_schedule_type().has_value() ? bench::digest((*message.flow_schedule_type())) : std::uint64_t{0});
        checksum += (message.min_price_increment_amount().has_value() ? bench::digest((*message.min_price_increment_amount()).mantissa()) : std::uint64_t{0});
        checksum += bench::digest(message.user_defined_instrument());
        checksum += (message.trading_reference_date().has_value() ? bench::digest((*message.trading_reference_date())) : std::uint64_t{0});
        checksum += (message.instrument_guid().has_value() ? bench::digest((*message.instrument_guid())) : std::uint64_t{0});
    }

    void on(const protocol::MdInstrumentDefinitionOption& message) {
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().reserved());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += (message.tot_num_reports_optional().has_value() ? bench::digest((*message.tot_num_reports_optional())) : std::uint64_t{0});
        checksum += bench::digest(message.security_update_action());
        checksum += bench::digest(message.last_update_time());
        checksum += (message.md_security_trading_status().has_value() ? bench::digest((*message.md_security_trading_status())) : std::uint64_t{0});
        checksum += bench::digest(message.appl_id());
        checksum += bench::digest(message.market_segment_id());
        checksum += bench::digest(message.underlying_product());
        checksum += bench::digest(message.security_exchange());
        checksum += bench::digest(message.security_group());
        checksum += bench::digest(message.asset());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.security_type());
        checksum += bench::digest(message.cfi_code());
        checksum += bench::digest(message.put_or_call());
        checksum += (message.maturity_month_year().year().has_value() ? bench::digest((*message.maturity_month_year().year())) : std::uint64_t{0});
        checksum += (message.maturity_month_year().month().has_value() ? bench::digest((*message.maturity_month_year().month())) : std::uint64_t{0});
        checksum += (message.maturity_month_year().day().has_value() ? bench::digest((*message.maturity_month_year().day())) : std::uint64_t{0});
        checksum += (message.maturity_month_year().week().has_value() ? bench::digest((*message.maturity_month_year().week())) : std::uint64_t{0});
        checksum += bench::digest(message.currency());
        checksum += (message.strike_price().has_value() ? bench::digest((*message.strike_price()).mantissa()) : std::uint64_t{0});
        checksum += bench::digest(message.strike_currency());
        checksum += bench::digest(message.settl_currency());
        checksum += (message.min_cab_price().has_value() ? bench::digest((*message.min_cab_price()).mantissa()) : std::uint64_t{0});
        checksum += bench::digest(message.match_algorithm());
        checksum += bench::digest(message.min_trade_vol());
        checksum += bench::digest(message.max_trade_vol());
        checksum += (message.min_price_increment_optional_ex().has_value() ? bench::digest((*message.min_price_increment_optional_ex()).mantissa()) : std::uint64_t{0});
        checksum += (message.min_price_increment_amount().has_value() ? bench::digest((*message.min_price_increment_amount()).mantissa()) : std::uint64_t{0});
        checksum += bench::digest(message.display_factor().mantissa());
        checksum += (message.tick_rule().has_value() ? bench::digest((*message.tick_rule())) : std::uint64_t{0});
        checksum += (message.main_fraction().has_value() ? bench::digest((*message.main_fraction())) : std::uint64_t{0});
        checksum += (message.sub_fraction().has_value() ? bench::digest((*message.sub_fraction())) : std::uint64_t{0});
        checksum += (message.price_display_format().has_value() ? bench::digest((*message.price_display_format())) : std::uint64_t{0});
        checksum += bench::digest(message.unit_of_measure());
        checksum += (message.unit_of_measure_qty().has_value() ? bench::digest((*message.unit_of_measure_qty()).mantissa()) : std::uint64_t{0});
        checksum += (message.trading_reference_price().has_value() ? bench::digest((*message.trading_reference_price()).mantissa()) : std::uint64_t{0});
        checksum += bench::digest(message.settl_price_type().final_daily());
        checksum += bench::digest(message.settl_price_type().actual());
        checksum += bench::digest(message.settl_price_type().rounded());
        checksum += bench::digest(message.settl_price_type().intraday());
        checksum += bench::digest(message.settl_price_type().reserved_bits());
        checksum += bench::digest(message.settl_price_type().unused_settl_price_type_5());
        checksum += bench::digest(message.settl_price_type().unused_settl_price_type_6());
        checksum += bench::digest(message.settl_price_type().null_value());
        checksum += (message.cleared_volume().has_value() ? bench::digest((*message.cleared_volume())) : std::uint64_t{0});
        checksum += (message.open_interest_qty().has_value() ? bench::digest((*message.open_interest_qty())) : std::uint64_t{0});
        checksum += (message.low_limit_price().has_value() ? bench::digest((*message.low_limit_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.high_limit_price().has_value() ? bench::digest((*message.high_limit_price()).mantissa()) : std::uint64_t{0});
        checksum += bench::digest(message.user_defined_instrument());
        checksum += (message.trading_reference_date().has_value() ? bench::digest((*message.trading_reference_date())) : std::uint64_t{0});
        checksum += (message.instrument_guid().has_value() ? bench::digest((*message.instrument_guid())) : std::uint64_t{0});
    }

    void on(const protocol::MdInstrumentDefinitionSpread& message) {
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().reserved());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += (message.tot_num_reports_optional().has_value() ? bench::digest((*message.tot_num_reports_optional())) : std::uint64_t{0});
        checksum += bench::digest(message.security_update_action());
        checksum += bench::digest(message.last_update_time());
        checksum += (message.md_security_trading_status().has_value() ? bench::digest((*message.md_security_trading_status())) : std::uint64_t{0});
        checksum += bench::digest(message.appl_id());
        checksum += bench::digest(message.market_segment_id());
        checksum += (message.underlying_product_optional().has_value() ? bench::digest((*message.underlying_product_optional())) : std::uint64_t{0});
        checksum += bench::digest(message.security_exchange());
        checksum += bench::digest(message.security_group());
        checksum += bench::digest(message.asset());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.security_type());
        checksum += bench::digest(message.cfi_code());
        checksum += (message.maturity_month_year().year().has_value() ? bench::digest((*message.maturity_month_year().year())) : std::uint64_t{0});
        checksum += (message.maturity_month_year().month().has_value() ? bench::digest((*message.maturity_month_year().month())) : std::uint64_t{0});
        checksum += (message.maturity_month_year().day().has_value() ? bench::digest((*message.maturity_month_year().day())) : std::uint64_t{0});
        checksum += (message.maturity_month_year().week().has_value() ? bench::digest((*message.maturity_month_year().week())) : std::uint64_t{0});
        checksum += bench::digest(message.currency());
        checksum += bench::digest(message.security_sub_type());
        checksum += bench::digest(message.user_defined_instrument());
        checksum += bench::digest(message.match_algorithm());
        checksum += bench::digest(message.min_trade_vol());
        checksum += bench::digest(message.max_trade_vol());
        checksum += (message.min_price_increment_optional_ex().has_value() ? bench::digest((*message.min_price_increment_optional_ex()).mantissa()) : std::uint64_t{0});
        checksum += bench::digest(message.display_factor().mantissa());
        checksum += (message.price_display_format().has_value() ? bench::digest((*message.price_display_format())) : std::uint64_t{0});
        checksum += (message.price_ratio().has_value() ? bench::digest((*message.price_ratio()).mantissa()) : std::uint64_t{0});
        checksum += (message.tick_rule().has_value() ? bench::digest((*message.tick_rule())) : std::uint64_t{0});
        checksum += bench::digest(message.unit_of_measure());
        checksum += (message.trading_reference_price().has_value() ? bench::digest((*message.trading_reference_price()).mantissa()) : std::uint64_t{0});
        checksum += bench::digest(message.settl_price_type().final_daily());
        checksum += bench::digest(message.settl_price_type().actual());
        checksum += bench::digest(message.settl_price_type().rounded());
        checksum += bench::digest(message.settl_price_type().intraday());
        checksum += bench::digest(message.settl_price_type().reserved_bits());
        checksum += bench::digest(message.settl_price_type().unused_settl_price_type_5());
        checksum += bench::digest(message.settl_price_type().unused_settl_price_type_6());
        checksum += bench::digest(message.settl_price_type().null_value());
        checksum += (message.open_interest_qty().has_value() ? bench::digest((*message.open_interest_qty())) : std::uint64_t{0});
        checksum += (message.cleared_volume().has_value() ? bench::digest((*message.cleared_volume())) : std::uint64_t{0});
        checksum += (message.high_limit_price().has_value() ? bench::digest((*message.high_limit_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.low_limit_price().has_value() ? bench::digest((*message.low_limit_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.max_price_variation().has_value() ? bench::digest((*message.max_price_variation()).mantissa()) : std::uint64_t{0});
        checksum += (message.main_fraction().has_value() ? bench::digest((*message.main_fraction())) : std::uint64_t{0});
        checksum += (message.sub_fraction().has_value() ? bench::digest((*message.sub_fraction())) : std::uint64_t{0});
        checksum += (message.trading_reference_date().has_value() ? bench::digest((*message.trading_reference_date())) : std::uint64_t{0});
        checksum += bench::digest(message.price_quote_method());
        checksum += bench::digest(message.risk_set());
        checksum += bench::digest(message.market_set());
        checksum += (message.instrument_guid().has_value() ? bench::digest((*message.instrument_guid())) : std::uint64_t{0});
        checksum += bench::digest(message.financial_instrument_full_name());
    }

    void on(const protocol::MdInstrumentDefinitionFixedIncome& message) {
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().reserved());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += (message.tot_num_reports_optional().has_value() ? bench::digest((*message.tot_num_reports_optional())) : std::uint64_t{0});
        checksum += bench::digest(message.security_update_action());
        checksum += bench::digest(message.last_update_time());
        checksum += (message.md_security_trading_status().has_value() ? bench::digest((*message.md_security_trading_status())) : std::uint64_t{0});
        checksum += bench::digest(message.appl_id());
        checksum += bench::digest(message.market_segment_id());
        checksum += bench::digest(message.underlying_product());
        checksum += bench::digest(message.security_exchange());
        checksum += bench::digest(message.security_group());
        checksum += bench::digest(message.asset());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.security_type());
        checksum += bench::digest(message.cfi_code());
        checksum += bench::digest(message.currency());
        checksum += bench::digest(message.settl_currency());
        checksum += bench::digest(message.match_algorithm());
        checksum += bench::digest(message.min_trade_vol());
        checksum += bench::digest(message.max_trade_vol());
        checksum += (message.min_price_increment_optional_ex().has_value() ? bench::digest((*message.min_price_increment_optional_ex()).mantissa()) : std::uint64_t{0});
        checksum += bench::digest(message.display_factor().mantissa());
        checksum += (message.main_fraction().has_value() ? bench::digest((*message.main_fraction())) : std::uint64_t{0});
        checksum += (message.sub_fraction().has_value() ? bench::digest((*message.sub_fraction())) : std::uint64_t{0});
        checksum += (message.price_display_format().has_value() ? bench::digest((*message.price_display_format())) : std::uint64_t{0});
        checksum += bench::digest(message.unit_of_measure());
        checksum += (message.unit_of_measure_qty().has_value() ? bench::digest((*message.unit_of_measure_qty()).mantissa()) : std::uint64_t{0});
        checksum += (message.trading_reference_price().has_value() ? bench::digest((*message.trading_reference_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.trading_reference_date().has_value() ? bench::digest((*message.trading_reference_date())) : std::uint64_t{0});
        checksum += (message.high_limit_price().has_value() ? bench::digest((*message.high_limit_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.low_limit_price().has_value() ? bench::digest((*message.low_limit_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.max_price_variation().has_value() ? bench::digest((*message.max_price_variation()).mantissa()) : std::uint64_t{0});
        checksum += (message.min_price_increment_amount().has_value() ? bench::digest((*message.min_price_increment_amount()).mantissa()) : std::uint64_t{0});
        checksum += (message.issue_date().has_value() ? bench::digest((*message.issue_date())) : std::uint64_t{0});
        checksum += (message.dated_date().has_value() ? bench::digest((*message.dated_date())) : std::uint64_t{0});
        checksum += (message.maturity_date().has_value() ? bench::digest((*message.maturity_date())) : std::uint64_t{0});
        checksum += (message.coupon_rate().has_value() ? bench::digest((*message.coupon_rate()).mantissa()) : std::uint64_t{0});
        checksum += (message.par_value().has_value() ? bench::digest((*message.par_value()).mantissa()) : std::uint64_t{0});
        checksum += bench::digest(message.coupon_frequency_unit());
        checksum += (message.coupon_frequency_period().has_value() ? bench::digest((*message.coupon_frequency_period())) : std::uint64_t{0});
        checksum += bench::digest(message.coupon_day_count());
        checksum += bench::digest(message.country_of_issue());
        checksum += bench::digest(message.issuer());
        checksum += bench::digest(message.financial_instrument_full_name());
        checksum += bench::digest(message.security_alt_id());
        checksum += (message.security_alt_id_source().has_value() ? bench::digest((*message.security_alt_id_source())) : std::uint64_t{0});
        checksum += bench::digest(message.price_quote_method());
        checksum += bench::digest(message.party_role_clearing_org());
        checksum += bench::digest(message.user_defined_instrument());
        checksum += bench::digest(message.risk_set());
        checksum += bench::digest(message.market_set());
        checksum += (message.instrument_guid().has_value() ? bench::digest((*message.instrument_guid())) : std::uint64_t{0});
    }

    void on(const protocol::MdInstrumentDefinitionRepo& message) {
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().reserved());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += (message.tot_num_reports_optional().has_value() ? bench::digest((*message.tot_num_reports_optional())) : std::uint64_t{0});
        checksum += bench::digest(message.security_update_action());
        checksum += bench::digest(message.last_update_time());
        checksum += (message.md_security_trading_status().has_value() ? bench::digest((*message.md_security_trading_status())) : std::uint64_t{0});
        checksum += bench::digest(message.appl_id());
        checksum += bench::digest(message.market_segment_id());
        checksum += bench::digest(message.underlying_product());
        checksum += bench::digest(message.security_exchange());
        checksum += bench::digest(message.security_group());
        checksum += bench::digest(message.asset());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.security_type());
        checksum += bench::digest(message.cfi_code());
        checksum += bench::digest(message.currency());
        checksum += bench::digest(message.settl_currency());
        checksum += bench::digest(message.match_algorithm());
        checksum += bench::digest(message.min_trade_vol());
        checksum += bench::digest(message.max_trade_vol());
        checksum += bench::digest(message.min_price_increment_ex().mantissa());
        checksum += bench::digest(message.display_factor().mantissa());
        checksum += bench::digest(message.unit_of_measure());
        checksum += (message.unit_of_measure_qty().has_value() ? bench::digest((*message.unit_of_measure_qty()).mantissa()) : std::uint64_t{0});
        checksum += (message.trading_reference_price().has_value() ? bench::digest((*message.trading_reference_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.trading_reference_date().has_value() ? bench::digest((*message.trading_reference_date())) : std::uint64_t{0});
        checksum += (message.high_limit_price().has_value() ? bench::digest((*message.high_limit_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.low_limit_price().has_value() ? bench::digest((*message.low_limit_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.max_price_variation().has_value() ? bench::digest((*message.max_price_variation()).mantissa()) : std::uint64_t{0});
        checksum += bench::digest(message.financial_instrument_full_name());
        checksum += bench::digest(message.party_role_clearing_org());
        checksum += (message.start_date().has_value() ? bench::digest((*message.start_date())) : std::uint64_t{0});
        checksum += (message.end_date().has_value() ? bench::digest((*message.end_date())) : std::uint64_t{0});
        checksum += bench::digest(message.termination_type());
        checksum += bench::digest(message.repo_sub_type());
        checksum += (message.money_or_par().has_value() ? bench::digest((*message.money_or_par())) : std::uint64_t{0});
        checksum += bench::digest(message.max_no_of_substitutions());
        checksum += bench::digest(message.price_quote_method());
        checksum += bench::digest(message.user_defined_instrument());
        checksum += bench::digest(message.risk_set());
        checksum += bench::digest(message.market_set());
        checksum += (message.instrument_guid().has_value() ? bench::digest((*message.instrument_guid())) : std::uint64_t{0});
        checksum += bench::digest(message.term_code());
        checksum += (message.broken_date_term_type().has_value() ? bench::digest((*message.broken_date_term_type())) : std::uint64_t{0});
    }

    void on(const protocol::SnapshotRefreshTopOrders& message) {
        checksum += bench::digest(message.transact_time());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().reserved());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += bench::digest(message.security_id());
    }

    void on(const protocol::SecurityStatusWorkup& message) {
        checksum += bench::digest(message.transact_time());
        checksum += (message.md_entry_px_optional_ex().has_value() ? bench::digest((*message.md_entry_px_optional_ex()).mantissa()) : std::uint64_t{0});
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().reserved());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += (message.trade_date().has_value() ? bench::digest((*message.trade_date())) : std::uint64_t{0});
        checksum += bench::digest(message.trade_link_id());
        checksum += bench::digest(message.workup_trading_status());
        checksum += bench::digest(message.halt_reason());
        checksum += bench::digest(message.security_trading_event());
    }

    void on(const protocol::SnapshotFullRefreshTcp& message) {
        checksum += bench::digest(message.transact_time());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().reserved());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += bench::digest(message.security_id());
        checksum += (message.high_limit_price().has_value() ? bench::digest((*message.high_limit_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.low_limit_price().has_value() ? bench::digest((*message.low_limit_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.max_price_variation().has_value() ? bench::digest((*message.max_price_variation()).mantissa()) : std::uint64_t{0});
    }

    void on(const protocol::CollateralMarketValue& message) {
        checksum += bench::digest(message.transact_time());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().reserved());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
    }

    void on(const protocol::MdInstrumentDefinitionFx& message) {
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().reserved());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += (message.tot_num_reports_optional().has_value() ? bench::digest((*message.tot_num_reports_optional())) : std::uint64_t{0});
        checksum += bench::digest(message.security_update_action());
        checksum += bench::digest(message.last_update_time());
        checksum += (message.md_security_trading_status().has_value() ? bench::digest((*message.md_security_trading_status())) : std::uint64_t{0});
        checksum += bench::digest(message.appl_id());
        checksum += bench::digest(message.market_segment_id());
        checksum += bench::digest(message.underlying_product());
        checksum += bench::digest(message.security_exchange());
        checksum += bench::digest(message.security_group());
        checksum += bench::digest(message.asset());
        checksum += bench::digest(message.symbol());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.security_type());
        checksum += bench::digest(message.cfi_code());
        checksum += bench::digest(message.currency());
        checksum += bench::digest(message.settl_currency());
        checksum += bench::digest(message.price_quote_currency());
        checksum += bench::digest(message.match_algorithm());
        checksum += bench::digest(message.min_trade_vol());
        checksum += bench::digest(message.max_trade_vol());
        checksum += bench::digest(message.min_price_increment_ex().mantissa());
        checksum += bench::digest(message.display_factor().mantissa());
        checksum += bench::digest(message.price_precision());
        checksum += bench::digest(message.unit_of_measure());
        checksum += (message.unit_of_measure_qty().has_value() ? bench::digest((*message.unit_of_measure_qty()).mantissa()) : std::uint64_t{0});
        checksum += (message.high_limit_price().has_value() ? bench::digest((*message.high_limit_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.low_limit_price().has_value() ? bench::digest((*message.low_limit_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.max_price_variation().has_value() ? bench::digest((*message.max_price_variation()).mantissa()) : std::uint64_t{0});
        checksum += bench::digest(message.user_defined_instrument());
        checksum += bench::digest(message.financial_instrument_full_name());
        checksum += bench::digest(message.fx_currency_symbol());
        checksum += bench::digest(message.settl_type());
        checksum += bench::digest(message.intervening_days());
        checksum += bench::digest(message.fx_benchmark_rate_fix());
        checksum += bench::digest(message.rate_source());
        checksum += bench::digest(message.fix_rate_local_time());
        checksum += bench::digest(message.fix_rate_local_time_zone());
        checksum += bench::digest(message.min_quote_life());
        checksum += bench::digest(message.max_price_discretion_offset().mantissa());
        checksum += (message.instrument_guid().has_value() ? bench::digest((*message.instrument_guid())) : std::uint64_t{0});
        checksum += (message.maturity_month_year().year().has_value() ? bench::digest((*message.maturity_month_year().year())) : std::uint64_t{0});
        checksum += (message.maturity_month_year().month().has_value() ? bench::digest((*message.maturity_month_year().month())) : std::uint64_t{0});
        checksum += (message.maturity_month_year().day().has_value() ? bench::digest((*message.maturity_month_year().day())) : std::uint64_t{0});
        checksum += (message.maturity_month_year().week().has_value() ? bench::digest((*message.maturity_month_year().week())) : std::uint64_t{0});
        checksum += bench::digest(message.settlement_locale());
        checksum += (message.alt_min_price_increment().has_value() ? bench::digest((*message.alt_min_price_increment()).mantissa()) : std::uint64_t{0});
        checksum += (message.alt_min_quote_life().has_value() ? bench::digest((*message.alt_min_quote_life())) : std::uint64_t{0});
        checksum += (message.alt_price_increment_constraint().has_value() ? bench::digest((*message.alt_price_increment_constraint()).mantissa()) : std::uint64_t{0});
        checksum += (message.max_bid_ask_constraint().has_value() ? bench::digest((*message.max_bid_ask_constraint()).mantissa()) : std::uint64_t{0});
    }

    void on(const protocol::MdIncrementalRefreshBookLongQty& message) {
        checksum += bench::digest(message.transact_time());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().reserved());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
    }

    void on(const protocol::MdIncrementalRefreshTradeSummaryLongQty& message) {
        checksum += bench::digest(message.transact_time());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().reserved());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
    }

    void on(const protocol::MdIncrementalRefreshVolumeLongQty& message) {
        checksum += bench::digest(message.transact_time());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().reserved());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
    }

    void on(const protocol::MdIncrementalRefreshSessionStatisticsLongQty& message) {
        checksum += bench::digest(message.transact_time());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().reserved());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
    }

    void on(const protocol::SnapshotFullRefreshTcpLongQty& message) {
        checksum += bench::digest(message.transact_time());
        checksum += bench::digest(message.match_event_indicator().last_trade_msg());
        checksum += bench::digest(message.match_event_indicator().last_volume_msg());
        checksum += bench::digest(message.match_event_indicator().last_quote_msg());
        checksum += bench::digest(message.match_event_indicator().last_stats_msg());
        checksum += bench::digest(message.match_event_indicator().last_implied_msg());
        checksum += bench::digest(message.match_event_indicator().recovery_msg());
        checksum += bench::digest(message.match_event_indicator().reserved());
        checksum += bench::digest(message.match_event_indicator().end_of_event());
        checksum += bench::digest(message.security_id());
        checksum += (message.high_limit_price().has_value() ? bench::digest((*message.high_limit_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.low_limit_price().has_value() ? bench::digest((*message.low_limit_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.max_price_variation().has_value() ? bench::digest((*message.max_price_variation()).mantissa()) : std::uint64_t{0});
    }

    void on(const protocol::SnapshotFullRefreshLongQty& message) {
        checksum += bench::digest(message.last_msg_seq_num_processed());
        checksum += bench::digest(message.tot_num_reports());
        checksum += bench::digest(message.security_id());
        checksum += bench::digest(message.rpt_seq());
        checksum += bench::digest(message.transact_time());
        checksum += bench::digest(message.last_update_time());
        checksum += (message.trade_date().has_value() ? bench::digest((*message.trade_date())) : std::uint64_t{0});
        checksum += (message.md_security_trading_status().has_value() ? bench::digest((*message.md_security_trading_status())) : std::uint64_t{0});
        checksum += (message.high_limit_price().has_value() ? bench::digest((*message.high_limit_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.low_limit_price().has_value() ? bench::digest((*message.low_limit_price()).mantissa()) : std::uint64_t{0});
        checksum += (message.max_price_variation().has_value() ? bench::digest((*message.max_price_variation()).mantissa()) : std::uint64_t{0});
    }
};

// The messages Mdpsessionmgmt Payload selects, their values set in the entry of the message holding it
struct MdpsessionmgmtPayloadHandler {
    std::uint64_t& checksum;

    void on(const protocol::Negotiate& message) {
        checksum += bench::digest(message.hmac_signature());
        checksum += bench::digest(message.access_key_id());
        checksum += bench::digest(message.uuid());
        checksum += bench::digest(message.request_timestamp());
        checksum += bench::digest(message.session());
        checksum += bench::digest(message.firm());
    }

    void on(const protocol::NegotiationReject& message) {
        checksum += bench::digest(message.reason());
        checksum += bench::digest(message.uuid());
        checksum += bench::digest(message.request_timestamp());
        checksum += bench::digest(message.error_codes());
    }

    void on(const protocol::NegotiationResponse& message) {
        checksum += bench::digest(message.uuid());
        checksum += bench::digest(message.request_timestamp());
        checksum += (message.secret_key_secure_id_expiration().has_value() ? bench::digest((*message.secret_key_secure_id_expiration())) : std::uint64_t{0});
    }

    void on(const protocol::Terminate& message) {
        checksum += bench::digest(message.reason());
        checksum += bench::digest(message.uuid());
        checksum += bench::digest(message.request_timestamp());
        checksum += bench::digest(message.error_codes());
    }

    void on(const protocol::MarketDataRequest& message) {
        checksum += bench::digest(message.md_req_id());
        checksum += bench::digest(message.subscription_req_type());
    }

    void on(const protocol::RequestAck& message) {
        checksum += bench::digest(message.md_req_id());
        checksum += bench::digest(message.subscription_req_type());
        checksum += bench::digest(message.md_req_id_status());
    }

    void on(const protocol::RequestReject& message) {
        checksum += (message.md_req_id_optional().has_value() ? bench::digest((*message.md_req_id_optional())) : std::uint64_t{0});
        checksum += bench::digest(message.md_req_rej_reason());
        checksum += bench::digest(message.text());
    }

    void on(const protocol::SecurityListRequest& message) {
        checksum += bench::digest(message.md_req_id());
        checksum += bench::digest(message.subscription_req_type());
    }

    void on(const protocol::SecurityStatusRequest& message) {
        checksum += bench::digest(message.md_req_id());
        checksum += bench::digest(message.subscription_req_type());
    }
};

// The handler the reader hands each datagram's views to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    void on(const protocol::UdpPacket& packet) {
        checksum += bench::digest(packet.binary_packet_header().packet_sequence_number());
        checksum += bench::digest(packet.binary_packet_header().sending_time());
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

    void on(const protocol::MktdataMessage& message) {
        checksum += index++;
        MktdataPayloadHandler selected{ checksum };
        message.mktdata_payload(selected);
    }

    void on(const protocol::MdpsessionmgmtMessage& message) {
        checksum += index++;
        MdpsessionmgmtPayloadHandler selected{ checksum };
        message.mdpsessionmgmt_payload(selected);
    }
};

// The values the Flyweight reader reads from one datagram, folded into a checksum. A datagram it cannot
// read is a value the model never reads, so the benchmark refuses to time it.
std::uint64_t read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::UdpPacketReader::read(std::span<const std::byte>(frame.payload, frame.payload_len), reader);
    } catch (const protocol::DecodeError& error) {
        throw;
    }

    return reader.checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Cme.Globex.Mdp3.Sbe.v1.13", "flyweight", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
