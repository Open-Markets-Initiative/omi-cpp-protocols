// Cme.Globex.Mdp3.Sbe.v1.8 benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/cme/globex/mdp3/sbe/v1.8.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/classes/cme/globex/mdp3/sbe/v1.8/definitions.hpp"

namespace protocol = ::cme::globex::mdp3::sbe::v1_8;

namespace {

// The values the Classes Packet decodes from one datagram, folded into a checksum. A datagram it cannot
// decode is a value the model never reads, so the benchmark refuses to time it.
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::UdpPacket packet;

    try {
        packet.decode(frame.payload, frame.payload_len);
    } catch (const protocol::DecodeError& error) {
        throw;
        return checksum;
    }

    checksum += bench::digest(packet.binary_packet_header().packet_sequence_number());
    checksum += bench::digest(packet.binary_packet_header().sending_time());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.message_header().message_size());
        checksum += bench::digest(each.message_header().simple_binary_header().block_length());
        checksum += bench::digest(each.message_header().simple_binary_header().template_id());
        checksum += bench::digest(each.message_header().simple_binary_header().schema_id());
        checksum += bench::digest(each.message_header().simple_binary_header().version());

        if (const auto* message = dynamic_cast<const protocol::MktdataMessage*>(each.message())) {
            if (const auto* message_2 = dynamic_cast<const protocol::ChannelReset*>(message->mktdata_payload())) {
                checksum += bench::digest((*message_2).transact_time());
                checksum += bench::digest((*message_2).match_event_indicator().last_trade_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_volume_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_quote_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_stats_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_implied_msg());
                checksum += bench::digest((*message_2).match_event_indicator().recovery_msg());
                checksum += bench::digest((*message_2).match_event_indicator().reserved());
                checksum += bench::digest((*message_2).match_event_indicator().end_of_event());
            } else if (const auto* message_2 = dynamic_cast<const protocol::AdminLogin*>(message->mktdata_payload())) {
                checksum += bench::digest((*message_2).heart_bt_int());
            } else if (const auto* message_2 = dynamic_cast<const protocol::AdminLogout*>(message->mktdata_payload())) {
                checksum += bench::digest((*message_2).text());
            } else if (const auto* message_2 = dynamic_cast<const protocol::MdInstrumentDefinitionFuture*>(message->mktdata_payload())) {
                checksum += bench::digest((*message_2).match_event_indicator().last_trade_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_volume_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_quote_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_stats_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_implied_msg());
                checksum += bench::digest((*message_2).match_event_indicator().recovery_msg());
                checksum += bench::digest((*message_2).match_event_indicator().reserved());
                checksum += bench::digest((*message_2).match_event_indicator().end_of_event());
                checksum += ((*message_2).tot_num_reports_optional().has_value() ? bench::digest((*(*message_2).tot_num_reports_optional())) : std::uint64_t{0});
                checksum += bench::digest((*message_2).security_update_action());
                checksum += bench::digest((*message_2).last_update_time());
                checksum += ((*message_2).md_security_trading_status().has_value() ? bench::digest((*(*message_2).md_security_trading_status())) : std::uint64_t{0});
                checksum += bench::digest((*message_2).appl_id());
                checksum += bench::digest((*message_2).market_segment_id());
                checksum += bench::digest((*message_2).underlying_product());
                checksum += bench::digest((*message_2).security_exchange());
                checksum += bench::digest((*message_2).security_group());
                checksum += bench::digest((*message_2).asset());
                checksum += bench::digest((*message_2).symbol());
                checksum += bench::digest((*message_2).security_id());
                checksum += bench::digest((*message_2).security_type());
                checksum += bench::digest((*message_2).cfi_code());
                checksum += ((*message_2).maturity_month_year().year().has_value() ? bench::digest((*(*message_2).maturity_month_year().year())) : std::uint64_t{0});
                checksum += ((*message_2).maturity_month_year().month().has_value() ? bench::digest((*(*message_2).maturity_month_year().month())) : std::uint64_t{0});
                checksum += ((*message_2).maturity_month_year().day().has_value() ? bench::digest((*(*message_2).maturity_month_year().day())) : std::uint64_t{0});
                checksum += ((*message_2).maturity_month_year().week().has_value() ? bench::digest((*(*message_2).maturity_month_year().week())) : std::uint64_t{0});
                checksum += bench::digest((*message_2).currency());
                checksum += bench::digest((*message_2).settl_currency());
                checksum += bench::digest((*message_2).match_algorithm());
                checksum += bench::digest((*message_2).min_trade_vol());
                checksum += bench::digest((*message_2).max_trade_vol());
                checksum += bench::digest((*message_2).min_price_increment().mantissa());
                checksum += bench::digest((*message_2).display_factor().mantissa());
                checksum += ((*message_2).main_fraction().has_value() ? bench::digest((*(*message_2).main_fraction())) : std::uint64_t{0});
                checksum += ((*message_2).sub_fraction().has_value() ? bench::digest((*(*message_2).sub_fraction())) : std::uint64_t{0});
                checksum += ((*message_2).price_display_format().has_value() ? bench::digest((*(*message_2).price_display_format())) : std::uint64_t{0});
                checksum += bench::digest((*message_2).unit_of_measure());
                checksum += ((*message_2).unit_of_measure_qty().has_value() ? bench::digest((*(*message_2).unit_of_measure_qty()).mantissa()) : std::uint64_t{0});
                checksum += ((*message_2).trading_reference_price().has_value() ? bench::digest((*(*message_2).trading_reference_price()).mantissa()) : std::uint64_t{0});
                checksum += bench::digest((*message_2).settl_price_type().final());
                checksum += bench::digest((*message_2).settl_price_type().actual());
                checksum += bench::digest((*message_2).settl_price_type().rounded());
                checksum += bench::digest((*message_2).settl_price_type().intraday());
                checksum += bench::digest((*message_2).settl_price_type().reserved_bits());
                checksum += bench::digest((*message_2).settl_price_type().unused_settl_price_type_5());
                checksum += bench::digest((*message_2).settl_price_type().unused_settl_price_type_6());
                checksum += bench::digest((*message_2).settl_price_type().null_value());
                checksum += ((*message_2).open_interest_qty().has_value() ? bench::digest((*(*message_2).open_interest_qty())) : std::uint64_t{0});
                checksum += ((*message_2).cleared_volume().has_value() ? bench::digest((*(*message_2).cleared_volume())) : std::uint64_t{0});
                checksum += ((*message_2).high_limit_price().has_value() ? bench::digest((*(*message_2).high_limit_price()).mantissa()) : std::uint64_t{0});
                checksum += ((*message_2).low_limit_price().has_value() ? bench::digest((*(*message_2).low_limit_price()).mantissa()) : std::uint64_t{0});
                checksum += ((*message_2).max_price_variation().has_value() ? bench::digest((*(*message_2).max_price_variation()).mantissa()) : std::uint64_t{0});
                checksum += ((*message_2).decay_quantity().has_value() ? bench::digest((*(*message_2).decay_quantity())) : std::uint64_t{0});
                checksum += ((*message_2).decay_start_date().has_value() ? bench::digest((*(*message_2).decay_start_date())) : std::uint64_t{0});
                checksum += ((*message_2).original_contract_size().has_value() ? bench::digest((*(*message_2).original_contract_size())) : std::uint64_t{0});
                checksum += ((*message_2).contract_multiplier().has_value() ? bench::digest((*(*message_2).contract_multiplier())) : std::uint64_t{0});
                checksum += ((*message_2).contract_multiplier_unit().has_value() ? bench::digest((*(*message_2).contract_multiplier_unit())) : std::uint64_t{0});
                checksum += ((*message_2).flow_schedule_type().has_value() ? bench::digest((*(*message_2).flow_schedule_type())) : std::uint64_t{0});
                checksum += ((*message_2).min_price_increment_amount().has_value() ? bench::digest((*(*message_2).min_price_increment_amount()).mantissa()) : std::uint64_t{0});
                checksum += bench::digest((*message_2).user_defined_instrument());
                checksum += ((*message_2).trading_reference_date().has_value() ? bench::digest((*(*message_2).trading_reference_date())) : std::uint64_t{0});
            } else if (const auto* message_2 = dynamic_cast<const protocol::MdInstrumentDefinitionSpread*>(message->mktdata_payload())) {
                checksum += bench::digest((*message_2).match_event_indicator().last_trade_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_volume_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_quote_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_stats_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_implied_msg());
                checksum += bench::digest((*message_2).match_event_indicator().recovery_msg());
                checksum += bench::digest((*message_2).match_event_indicator().reserved());
                checksum += bench::digest((*message_2).match_event_indicator().end_of_event());
                checksum += ((*message_2).tot_num_reports_optional().has_value() ? bench::digest((*(*message_2).tot_num_reports_optional())) : std::uint64_t{0});
                checksum += bench::digest((*message_2).security_update_action());
                checksum += bench::digest((*message_2).last_update_time());
                checksum += ((*message_2).md_security_trading_status().has_value() ? bench::digest((*(*message_2).md_security_trading_status())) : std::uint64_t{0});
                checksum += bench::digest((*message_2).appl_id());
                checksum += bench::digest((*message_2).market_segment_id());
                checksum += ((*message_2).underlying_product_optional().has_value() ? bench::digest((*(*message_2).underlying_product_optional())) : std::uint64_t{0});
                checksum += bench::digest((*message_2).security_exchange());
                checksum += bench::digest((*message_2).security_group());
                checksum += bench::digest((*message_2).asset());
                checksum += bench::digest((*message_2).symbol());
                checksum += bench::digest((*message_2).security_id());
                checksum += bench::digest((*message_2).security_type());
                checksum += bench::digest((*message_2).cfi_code());
                checksum += ((*message_2).maturity_month_year().year().has_value() ? bench::digest((*(*message_2).maturity_month_year().year())) : std::uint64_t{0});
                checksum += ((*message_2).maturity_month_year().month().has_value() ? bench::digest((*(*message_2).maturity_month_year().month())) : std::uint64_t{0});
                checksum += ((*message_2).maturity_month_year().day().has_value() ? bench::digest((*(*message_2).maturity_month_year().day())) : std::uint64_t{0});
                checksum += ((*message_2).maturity_month_year().week().has_value() ? bench::digest((*(*message_2).maturity_month_year().week())) : std::uint64_t{0});
                checksum += bench::digest((*message_2).currency());
                checksum += bench::digest((*message_2).security_sub_type());
                checksum += bench::digest((*message_2).user_defined_instrument());
                checksum += bench::digest((*message_2).match_algorithm());
                checksum += bench::digest((*message_2).min_trade_vol());
                checksum += bench::digest((*message_2).max_trade_vol());
                checksum += bench::digest((*message_2).min_price_increment().mantissa());
                checksum += bench::digest((*message_2).display_factor().mantissa());
                checksum += ((*message_2).price_display_format().has_value() ? bench::digest((*(*message_2).price_display_format())) : std::uint64_t{0});
                checksum += ((*message_2).price_ratio().has_value() ? bench::digest((*(*message_2).price_ratio()).mantissa()) : std::uint64_t{0});
                checksum += ((*message_2).tick_rule().has_value() ? bench::digest((*(*message_2).tick_rule())) : std::uint64_t{0});
                checksum += bench::digest((*message_2).unit_of_measure());
                checksum += ((*message_2).trading_reference_price().has_value() ? bench::digest((*(*message_2).trading_reference_price()).mantissa()) : std::uint64_t{0});
                checksum += bench::digest((*message_2).settl_price_type().final());
                checksum += bench::digest((*message_2).settl_price_type().actual());
                checksum += bench::digest((*message_2).settl_price_type().rounded());
                checksum += bench::digest((*message_2).settl_price_type().intraday());
                checksum += bench::digest((*message_2).settl_price_type().reserved_bits());
                checksum += bench::digest((*message_2).settl_price_type().unused_settl_price_type_5());
                checksum += bench::digest((*message_2).settl_price_type().unused_settl_price_type_6());
                checksum += bench::digest((*message_2).settl_price_type().null_value());
                checksum += ((*message_2).open_interest_qty().has_value() ? bench::digest((*(*message_2).open_interest_qty())) : std::uint64_t{0});
                checksum += ((*message_2).cleared_volume().has_value() ? bench::digest((*(*message_2).cleared_volume())) : std::uint64_t{0});
                checksum += ((*message_2).high_limit_price().has_value() ? bench::digest((*(*message_2).high_limit_price()).mantissa()) : std::uint64_t{0});
                checksum += ((*message_2).low_limit_price().has_value() ? bench::digest((*(*message_2).low_limit_price()).mantissa()) : std::uint64_t{0});
                checksum += ((*message_2).max_price_variation().has_value() ? bench::digest((*(*message_2).max_price_variation()).mantissa()) : std::uint64_t{0});
                checksum += ((*message_2).main_fraction().has_value() ? bench::digest((*(*message_2).main_fraction())) : std::uint64_t{0});
                checksum += ((*message_2).sub_fraction().has_value() ? bench::digest((*(*message_2).sub_fraction())) : std::uint64_t{0});
                checksum += ((*message_2).trading_reference_date().has_value() ? bench::digest((*(*message_2).trading_reference_date())) : std::uint64_t{0});
            } else if (const auto* message_2 = dynamic_cast<const protocol::SecurityStatus*>(message->mktdata_payload())) {
                checksum += bench::digest((*message_2).transact_time());
                checksum += bench::digest((*message_2).security_group());
                checksum += bench::digest((*message_2).asset());
                checksum += ((*message_2).security_id_optional().has_value() ? bench::digest((*(*message_2).security_id_optional())) : std::uint64_t{0});
                checksum += ((*message_2).trade_date().has_value() ? bench::digest((*(*message_2).trade_date())) : std::uint64_t{0});
                checksum += bench::digest((*message_2).match_event_indicator().last_trade_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_volume_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_quote_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_stats_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_implied_msg());
                checksum += bench::digest((*message_2).match_event_indicator().recovery_msg());
                checksum += bench::digest((*message_2).match_event_indicator().reserved());
                checksum += bench::digest((*message_2).match_event_indicator().end_of_event());
                checksum += ((*message_2).security_trading_status().has_value() ? bench::digest((*(*message_2).security_trading_status())) : std::uint64_t{0});
                checksum += bench::digest((*message_2).halt_reason());
                checksum += bench::digest((*message_2).security_trading_event());
            } else if (const auto* message_2 = dynamic_cast<const protocol::MdIncrementalRefreshBook*>(message->mktdata_payload())) {
                checksum += bench::digest((*message_2).transact_time());
                checksum += bench::digest((*message_2).match_event_indicator().last_trade_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_volume_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_quote_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_stats_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_implied_msg());
                checksum += bench::digest((*message_2).match_event_indicator().recovery_msg());
                checksum += bench::digest((*message_2).match_event_indicator().reserved());
                checksum += bench::digest((*message_2).match_event_indicator().end_of_event());
            } else if (const auto* message_2 = dynamic_cast<const protocol::MdIncrementalRefreshDailyStatistics*>(message->mktdata_payload())) {
                checksum += bench::digest((*message_2).transact_time());
                checksum += bench::digest((*message_2).match_event_indicator().last_trade_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_volume_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_quote_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_stats_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_implied_msg());
                checksum += bench::digest((*message_2).match_event_indicator().recovery_msg());
                checksum += bench::digest((*message_2).match_event_indicator().reserved());
                checksum += bench::digest((*message_2).match_event_indicator().end_of_event());
            } else if (const auto* message_2 = dynamic_cast<const protocol::MdIncrementalRefreshLimitsBanding*>(message->mktdata_payload())) {
                checksum += bench::digest((*message_2).transact_time());
                checksum += bench::digest((*message_2).match_event_indicator().last_trade_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_volume_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_quote_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_stats_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_implied_msg());
                checksum += bench::digest((*message_2).match_event_indicator().recovery_msg());
                checksum += bench::digest((*message_2).match_event_indicator().reserved());
                checksum += bench::digest((*message_2).match_event_indicator().end_of_event());
            } else if (const auto* message_2 = dynamic_cast<const protocol::MdIncrementalRefreshSessionStatistics*>(message->mktdata_payload())) {
                checksum += bench::digest((*message_2).transact_time());
                checksum += bench::digest((*message_2).match_event_indicator().last_trade_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_volume_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_quote_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_stats_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_implied_msg());
                checksum += bench::digest((*message_2).match_event_indicator().recovery_msg());
                checksum += bench::digest((*message_2).match_event_indicator().reserved());
                checksum += bench::digest((*message_2).match_event_indicator().end_of_event());
            } else if (const auto* message_2 = dynamic_cast<const protocol::MdIncrementalRefreshTrade*>(message->mktdata_payload())) {
                checksum += bench::digest((*message_2).transact_time());
                checksum += bench::digest((*message_2).match_event_indicator().last_trade_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_volume_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_quote_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_stats_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_implied_msg());
                checksum += bench::digest((*message_2).match_event_indicator().recovery_msg());
                checksum += bench::digest((*message_2).match_event_indicator().reserved());
                checksum += bench::digest((*message_2).match_event_indicator().end_of_event());
            } else if (const auto* message_2 = dynamic_cast<const protocol::MdIncrementalRefreshVolume*>(message->mktdata_payload())) {
                checksum += bench::digest((*message_2).transact_time());
                checksum += bench::digest((*message_2).match_event_indicator().last_trade_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_volume_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_quote_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_stats_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_implied_msg());
                checksum += bench::digest((*message_2).match_event_indicator().recovery_msg());
                checksum += bench::digest((*message_2).match_event_indicator().reserved());
                checksum += bench::digest((*message_2).match_event_indicator().end_of_event());
            } else if (const auto* message_2 = dynamic_cast<const protocol::SnapshotFullRefresh*>(message->mktdata_payload())) {
                checksum += bench::digest((*message_2).last_msg_seq_num_processed());
                checksum += bench::digest((*message_2).tot_num_reports());
                checksum += bench::digest((*message_2).security_id());
                checksum += bench::digest((*message_2).rpt_seq());
                checksum += bench::digest((*message_2).transact_time());
                checksum += bench::digest((*message_2).last_update_time());
                checksum += ((*message_2).trade_date().has_value() ? bench::digest((*(*message_2).trade_date())) : std::uint64_t{0});
                checksum += ((*message_2).md_security_trading_status().has_value() ? bench::digest((*(*message_2).md_security_trading_status())) : std::uint64_t{0});
                checksum += ((*message_2).high_limit_price().has_value() ? bench::digest((*(*message_2).high_limit_price()).mantissa()) : std::uint64_t{0});
                checksum += ((*message_2).low_limit_price().has_value() ? bench::digest((*(*message_2).low_limit_price()).mantissa()) : std::uint64_t{0});
                checksum += ((*message_2).max_price_variation().has_value() ? bench::digest((*(*message_2).max_price_variation()).mantissa()) : std::uint64_t{0});
            } else if (const auto* message_2 = dynamic_cast<const protocol::QuoteRequest*>(message->mktdata_payload())) {
                checksum += bench::digest((*message_2).transact_time());
                checksum += bench::digest((*message_2).quote_req_id());
                checksum += bench::digest((*message_2).match_event_indicator().last_trade_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_volume_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_quote_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_stats_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_implied_msg());
                checksum += bench::digest((*message_2).match_event_indicator().recovery_msg());
                checksum += bench::digest((*message_2).match_event_indicator().reserved());
                checksum += bench::digest((*message_2).match_event_indicator().end_of_event());
            } else if (const auto* message_2 = dynamic_cast<const protocol::MdInstrumentDefinitionOption*>(message->mktdata_payload())) {
                checksum += bench::digest((*message_2).match_event_indicator().last_trade_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_volume_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_quote_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_stats_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_implied_msg());
                checksum += bench::digest((*message_2).match_event_indicator().recovery_msg());
                checksum += bench::digest((*message_2).match_event_indicator().reserved());
                checksum += bench::digest((*message_2).match_event_indicator().end_of_event());
                checksum += ((*message_2).tot_num_reports_optional().has_value() ? bench::digest((*(*message_2).tot_num_reports_optional())) : std::uint64_t{0});
                checksum += bench::digest((*message_2).security_update_action());
                checksum += bench::digest((*message_2).last_update_time());
                checksum += ((*message_2).md_security_trading_status().has_value() ? bench::digest((*(*message_2).md_security_trading_status())) : std::uint64_t{0});
                checksum += bench::digest((*message_2).appl_id());
                checksum += bench::digest((*message_2).market_segment_id());
                checksum += bench::digest((*message_2).underlying_product());
                checksum += bench::digest((*message_2).security_exchange());
                checksum += bench::digest((*message_2).security_group());
                checksum += bench::digest((*message_2).asset());
                checksum += bench::digest((*message_2).symbol());
                checksum += bench::digest((*message_2).security_id());
                checksum += bench::digest((*message_2).security_type());
                checksum += bench::digest((*message_2).cfi_code());
                checksum += bench::digest((*message_2).put_or_call());
                checksum += ((*message_2).maturity_month_year().year().has_value() ? bench::digest((*(*message_2).maturity_month_year().year())) : std::uint64_t{0});
                checksum += ((*message_2).maturity_month_year().month().has_value() ? bench::digest((*(*message_2).maturity_month_year().month())) : std::uint64_t{0});
                checksum += ((*message_2).maturity_month_year().day().has_value() ? bench::digest((*(*message_2).maturity_month_year().day())) : std::uint64_t{0});
                checksum += ((*message_2).maturity_month_year().week().has_value() ? bench::digest((*(*message_2).maturity_month_year().week())) : std::uint64_t{0});
                checksum += bench::digest((*message_2).currency());
                checksum += ((*message_2).strike_price().has_value() ? bench::digest((*(*message_2).strike_price()).mantissa()) : std::uint64_t{0});
                checksum += bench::digest((*message_2).strike_currency());
                checksum += bench::digest((*message_2).settl_currency());
                checksum += ((*message_2).min_cab_price().has_value() ? bench::digest((*(*message_2).min_cab_price()).mantissa()) : std::uint64_t{0});
                checksum += bench::digest((*message_2).match_algorithm());
                checksum += bench::digest((*message_2).min_trade_vol());
                checksum += bench::digest((*message_2).max_trade_vol());
                checksum += ((*message_2).min_price_increment_optional().has_value() ? bench::digest((*(*message_2).min_price_increment_optional()).mantissa()) : std::uint64_t{0});
                checksum += ((*message_2).min_price_increment_amount().has_value() ? bench::digest((*(*message_2).min_price_increment_amount()).mantissa()) : std::uint64_t{0});
                checksum += bench::digest((*message_2).display_factor().mantissa());
                checksum += ((*message_2).tick_rule().has_value() ? bench::digest((*(*message_2).tick_rule())) : std::uint64_t{0});
                checksum += ((*message_2).main_fraction().has_value() ? bench::digest((*(*message_2).main_fraction())) : std::uint64_t{0});
                checksum += ((*message_2).sub_fraction().has_value() ? bench::digest((*(*message_2).sub_fraction())) : std::uint64_t{0});
                checksum += ((*message_2).price_display_format().has_value() ? bench::digest((*(*message_2).price_display_format())) : std::uint64_t{0});
                checksum += bench::digest((*message_2).unit_of_measure());
                checksum += ((*message_2).unit_of_measure_qty().has_value() ? bench::digest((*(*message_2).unit_of_measure_qty()).mantissa()) : std::uint64_t{0});
                checksum += ((*message_2).trading_reference_price().has_value() ? bench::digest((*(*message_2).trading_reference_price()).mantissa()) : std::uint64_t{0});
                checksum += bench::digest((*message_2).settl_price_type().final());
                checksum += bench::digest((*message_2).settl_price_type().actual());
                checksum += bench::digest((*message_2).settl_price_type().rounded());
                checksum += bench::digest((*message_2).settl_price_type().intraday());
                checksum += bench::digest((*message_2).settl_price_type().reserved_bits());
                checksum += bench::digest((*message_2).settl_price_type().unused_settl_price_type_5());
                checksum += bench::digest((*message_2).settl_price_type().unused_settl_price_type_6());
                checksum += bench::digest((*message_2).settl_price_type().null_value());
                checksum += ((*message_2).cleared_volume().has_value() ? bench::digest((*(*message_2).cleared_volume())) : std::uint64_t{0});
                checksum += ((*message_2).open_interest_qty().has_value() ? bench::digest((*(*message_2).open_interest_qty())) : std::uint64_t{0});
                checksum += ((*message_2).low_limit_price().has_value() ? bench::digest((*(*message_2).low_limit_price()).mantissa()) : std::uint64_t{0});
                checksum += ((*message_2).high_limit_price().has_value() ? bench::digest((*(*message_2).high_limit_price()).mantissa()) : std::uint64_t{0});
                checksum += bench::digest((*message_2).user_defined_instrument());
                checksum += ((*message_2).trading_reference_date().has_value() ? bench::digest((*(*message_2).trading_reference_date())) : std::uint64_t{0});
            } else if (const auto* message_2 = dynamic_cast<const protocol::MdIncrementalRefreshTradeSummary*>(message->mktdata_payload())) {
                checksum += bench::digest((*message_2).transact_time());
                checksum += bench::digest((*message_2).match_event_indicator().last_trade_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_volume_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_quote_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_stats_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_implied_msg());
                checksum += bench::digest((*message_2).match_event_indicator().recovery_msg());
                checksum += bench::digest((*message_2).match_event_indicator().reserved());
                checksum += bench::digest((*message_2).match_event_indicator().end_of_event());
            } else if (const auto* message_2 = dynamic_cast<const protocol::MdIncrementalRefreshOrderBook*>(message->mktdata_payload())) {
                checksum += bench::digest((*message_2).transact_time());
                checksum += bench::digest((*message_2).match_event_indicator().last_trade_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_volume_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_quote_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_stats_msg());
                checksum += bench::digest((*message_2).match_event_indicator().last_implied_msg());
                checksum += bench::digest((*message_2).match_event_indicator().recovery_msg());
                checksum += bench::digest((*message_2).match_event_indicator().reserved());
                checksum += bench::digest((*message_2).match_event_indicator().end_of_event());
            } else if (const auto* message_2 = dynamic_cast<const protocol::SnapshotFullRefreshOrderBook*>(message->mktdata_payload())) {
                checksum += bench::digest((*message_2).last_msg_seq_num_processed());
                checksum += bench::digest((*message_2).tot_num_reports());
                checksum += bench::digest((*message_2).security_id());
                checksum += bench::digest((*message_2).no_chunks());
                checksum += bench::digest((*message_2).current_chunk());
                checksum += bench::digest((*message_2).transact_time());
            }
        } else if (const auto* message = dynamic_cast<const protocol::MdpsessionmgmtMessage*>(each.message())) {
            if (const auto* message_2 = dynamic_cast<const protocol::Negotiate*>(message->mdpsessionmgmt_payload())) {
                checksum += bench::digest((*message_2).hmac_signature());
                checksum += bench::digest((*message_2).access_key_id());
                checksum += bench::digest((*message_2).uuid());
                checksum += bench::digest((*message_2).request_timestamp());
                checksum += bench::digest((*message_2).session());
                checksum += bench::digest((*message_2).firm());
            } else if (const auto* message_2 = dynamic_cast<const protocol::NegotiationReject*>(message->mdpsessionmgmt_payload())) {
                checksum += bench::digest((*message_2).reason());
                checksum += bench::digest((*message_2).uuid());
                checksum += bench::digest((*message_2).request_timestamp());
                checksum += bench::digest((*message_2).error_codes());
            } else if (const auto* message_2 = dynamic_cast<const protocol::NegotiationResponse*>(message->mdpsessionmgmt_payload())) {
                checksum += bench::digest((*message_2).uuid());
                checksum += bench::digest((*message_2).request_timestamp());
                checksum += ((*message_2).secret_key_secure_id_expiration().has_value() ? bench::digest((*(*message_2).secret_key_secure_id_expiration())) : std::uint64_t{0});
            } else if (const auto* message_2 = dynamic_cast<const protocol::Terminate*>(message->mdpsessionmgmt_payload())) {
                checksum += bench::digest((*message_2).reason());
                checksum += bench::digest((*message_2).uuid());
                checksum += bench::digest((*message_2).request_timestamp());
                checksum += bench::digest((*message_2).error_codes());
            } else if (const auto* message_2 = dynamic_cast<const protocol::MarketDataRequest*>(message->mdpsessionmgmt_payload())) {
                checksum += bench::digest((*message_2).md_req_id());
                checksum += bench::digest((*message_2).subscription_req_type());
            } else if (const auto* message_2 = dynamic_cast<const protocol::RequestAck*>(message->mdpsessionmgmt_payload())) {
                checksum += bench::digest((*message_2).md_req_id());
                checksum += bench::digest((*message_2).subscription_req_type());
                checksum += bench::digest((*message_2).md_req_id_status());
            } else if (const auto* message_2 = dynamic_cast<const protocol::RequestReject*>(message->mdpsessionmgmt_payload())) {
                checksum += ((*message_2).md_req_id_optional().has_value() ? bench::digest((*(*message_2).md_req_id_optional())) : std::uint64_t{0});
                checksum += bench::digest((*message_2).md_req_rej_reason());
                checksum += bench::digest((*message_2).text());
            } else if (const auto* message_2 = dynamic_cast<const protocol::SecurityListRequest*>(message->mdpsessionmgmt_payload())) {
                checksum += bench::digest((*message_2).md_req_id());
                checksum += bench::digest((*message_2).subscription_req_type());
            } else if (const auto* message_2 = dynamic_cast<const protocol::SecurityStatusRequest*>(message->mdpsessionmgmt_payload())) {
                checksum += bench::digest((*message_2).md_req_id());
                checksum += bench::digest((*message_2).subscription_req_type());
            }
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Cme.Globex.Mdp3.Sbe.v1.8", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
