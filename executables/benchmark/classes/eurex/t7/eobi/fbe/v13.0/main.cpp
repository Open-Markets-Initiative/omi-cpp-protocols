// Eurex.T7.Eobi.Fbe.v13.0 benchmark, through the Classes Packet: every value it reads from every message of the simulated
// sequence (tests/simulated/eurex/t7/eobi/fbe/v13.0.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/classes/eurex/t7/eobi/fbe/v13.0/definitions.hpp"

namespace protocol = ::eurex::t7::eobi::fbe::v13_0;

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

    checksum += bench::digest(packet.packet_header().eobi_header().body_len());
    checksum += bench::digest(packet.packet_header().eobi_header().template_id());
    checksum += bench::digest(packet.packet_header().eobi_header().msg_seq_num());
    checksum += bench::digest(packet.packet_header().appl_seq_num());
    checksum += (packet.packet_header().market_segment_id().has_value() ? bench::digest((*packet.packet_header().market_segment_id())) : std::uint64_t{0});
    checksum += (packet.packet_header().partition_id().has_value() ? bench::digest((*packet.packet_header().partition_id())) : std::uint64_t{0});
    checksum += (packet.packet_header().completion_indicator().has_value() ? bench::digest((*packet.packet_header().completion_indicator())) : std::uint64_t{0});
    checksum += (packet.packet_header().appl_seq_reset_indicator().has_value() ? bench::digest((*packet.packet_header().appl_seq_reset_indicator())) : std::uint64_t{0});
    checksum += bench::digest(packet.packet_header().dscp());
    checksum += (packet.packet_header().transact_time().has_value() ? bench::digest((*packet.packet_header().transact_time())) : std::uint64_t{0});

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.message_header_comp().body_len());
        checksum += bench::digest(each.message_header_comp().template_id());
        checksum += bench::digest(each.message_header_comp().msg_seq_num());

        if (const auto* message = dynamic_cast<const protocol::AddComplexInstrument*>(each.message())) {
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
            checksum += ((*message).security_sub_type().has_value() ? bench::digest((*(*message).security_sub_type())) : std::uint64_t{0});
            checksum += ((*message).product_complex().has_value() ? bench::digest((*(*message).product_complex())) : std::uint64_t{0});
            checksum += ((*message).implied_market_indicator().has_value() ? bench::digest((*(*message).implied_market_indicator())) : std::uint64_t{0});
            checksum += ((*message).quantity_scaling_factor().has_value() ? bench::digest((*(*message).quantity_scaling_factor())) : std::uint64_t{0});
            checksum += ((*message).leg_ratio_multiplier().has_value() ? bench::digest((*(*message).leg_ratio_multiplier())) : std::uint64_t{0});
            checksum += ((*message).no_legs().has_value() ? bench::digest((*(*message).no_legs())) : std::uint64_t{0});
            checksum += ((*message).last_fragment().has_value() ? bench::digest((*(*message).last_fragment())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::AddFlexibleInstrument*>(each.message())) {
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
            checksum += ((*message).security_type().has_value() ? bench::digest((*(*message).security_type())) : std::uint64_t{0});
            checksum += ((*message).put_or_call().has_value() ? bench::digest((*(*message).put_or_call())) : std::uint64_t{0});
            checksum += ((*message).exercise_style().has_value() ? bench::digest((*(*message).exercise_style())) : std::uint64_t{0});
            checksum += ((*message).settl_method().has_value() ? bench::digest((*(*message).settl_method())) : std::uint64_t{0});
            checksum += ((*message).maturity_date().has_value() ? bench::digest((*(*message).maturity_date())) : std::uint64_t{0});
            checksum += ((*message).strike_price().has_value() ? bench::digest((*(*message).strike_price()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).opt_attribute().has_value() ? bench::digest((*(*message).opt_attribute())) : std::uint64_t{0});
            checksum += ((*message).contract_date().has_value() ? bench::digest((*(*message).contract_date())) : std::uint64_t{0});
            checksum += ((*message).security_reference_data_supplement().has_value() ? bench::digest((*(*message).security_reference_data_supplement())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::AddScaledSimpleInstrument*>(each.message())) {
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
            checksum += ((*message).security_type().has_value() ? bench::digest((*(*message).security_type())) : std::uint64_t{0});
            checksum += ((*message).quantity_scaling_factor().has_value() ? bench::digest((*(*message).quantity_scaling_factor())) : std::uint64_t{0});
            checksum += ((*message).related_instrument_grp_comp().related_security_id().has_value() ? bench::digest((*(*message).related_instrument_grp_comp().related_security_id())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::AuctionBbo*>(each.message())) {
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).bid_px().has_value() ? bench::digest((*(*message).bid_px()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).offer_px().has_value() ? bench::digest((*(*message).offer_px()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).bid_size().has_value() ? bench::digest((*(*message).bid_size()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).offer_size().has_value() ? bench::digest((*(*message).offer_size()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).potential_security_trading_event().has_value() ? bench::digest((*(*message).potential_security_trading_event())) : std::uint64_t{0});
            checksum += ((*message).bid_ord_type().has_value() ? bench::digest((*(*message).bid_ord_type())) : std::uint64_t{0});
            checksum += ((*message).offer_ord_type().has_value() ? bench::digest((*(*message).offer_ord_type())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::AuctionClearingPrice*>(each.message())) {
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).last_px().has_value() ? bench::digest((*(*message).last_px()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).last_qty().has_value() ? bench::digest((*(*message).last_qty()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).imbalance_qty().has_value() ? bench::digest((*(*message).imbalance_qty()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).security_trading_status().has_value() ? bench::digest((*(*message).security_trading_status())) : std::uint64_t{0});
            checksum += ((*message).potential_security_trading_event().has_value() ? bench::digest((*(*message).potential_security_trading_event())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::CrossRequest*>(each.message())) {
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).last_px().has_value() ? bench::digest((*(*message).last_px()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).last_qty().has_value() ? bench::digest((*(*message).last_qty()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).side().has_value() ? bench::digest((*(*message).side())) : std::uint64_t{0});
            checksum += ((*message).cross_request_type().has_value() ? bench::digest((*(*message).cross_request_type())) : std::uint64_t{0});
            checksum += ((*message).input_source().has_value() ? bench::digest((*(*message).input_source())) : std::uint64_t{0});
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::ExecutionSummary*>(each.message())) {
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).request_time().has_value() ? bench::digest((*(*message).request_time())) : std::uint64_t{0});
            checksum += ((*message).exec_id().has_value() ? bench::digest((*(*message).exec_id())) : std::uint64_t{0});
            checksum += ((*message).last_qty().has_value() ? bench::digest((*(*message).last_qty()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).aggressor_side().has_value() ? bench::digest((*(*message).aggressor_side())) : std::uint64_t{0});
            checksum += ((*message).trade_condition().has_value() ? bench::digest((*(*message).trade_condition())) : std::uint64_t{0});
            checksum += ((*message).trading_hhi_indicator().has_value() ? bench::digest((*(*message).trading_hhi_indicator())) : std::uint64_t{0});
            checksum += ((*message).last_px().has_value() ? bench::digest((*(*message).last_px()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).remaining_order_details_comp().trd_reg_ts_prev_time_priority().has_value() ? bench::digest((*(*message).remaining_order_details_comp().trd_reg_ts_prev_time_priority())) : std::uint64_t{0});
            checksum += ((*message).remaining_order_details_comp().display_qty().has_value() ? bench::digest((*(*message).remaining_order_details_comp().display_qty()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).remaining_order_details_comp().price().has_value() ? bench::digest((*(*message).remaining_order_details_comp().price()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).resting_hidden_qty().has_value() ? bench::digest((*(*message).resting_hidden_qty()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).resting_cxl_qty().has_value() ? bench::digest((*(*message).resting_cxl_qty()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).aggressor_time().has_value() ? bench::digest((*(*message).aggressor_time())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::FullOrderExecution*>(each.message())) {
            checksum += ((*message).side().has_value() ? bench::digest((*(*message).side())) : std::uint64_t{0});
            checksum += ((*message).ord_type().has_value() ? bench::digest((*(*message).ord_type())) : std::uint64_t{0});
            checksum += ((*message).algorithmic_trade_indicator().has_value() ? bench::digest((*(*message).algorithmic_trade_indicator())) : std::uint64_t{0});
            checksum += ((*message).hhi_indicator().has_value() ? bench::digest((*(*message).hhi_indicator())) : std::uint64_t{0});
            checksum += ((*message).trd_match_id().has_value() ? bench::digest((*(*message).trd_match_id())) : std::uint64_t{0});
            checksum += ((*message).price().has_value() ? bench::digest((*(*message).price()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).trd_reg_ts_time_priority().has_value() ? bench::digest((*(*message).trd_reg_ts_time_priority())) : std::uint64_t{0});
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).last_qty().has_value() ? bench::digest((*(*message).last_qty()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).last_px().has_value() ? bench::digest((*(*message).last_px()).mantissa()) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::Heartbeat*>(each.message())) {
            checksum += ((*message).last_msg_seq_num_processed().has_value() ? bench::digest((*(*message).last_msg_seq_num_processed())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::InstrumentStateChange*>(each.message())) {
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).security_status().has_value() ? bench::digest((*(*message).security_status())) : std::uint64_t{0});
            checksum += ((*message).security_trading_status().has_value() ? bench::digest((*(*message).security_trading_status())) : std::uint64_t{0});
            checksum += ((*message).market_condition().has_value() ? bench::digest((*(*message).market_condition())) : std::uint64_t{0});
            checksum += ((*message).fast_market_indicator().has_value() ? bench::digest((*(*message).fast_market_indicator())) : std::uint64_t{0});
            checksum += ((*message).security_trading_event().has_value() ? bench::digest((*(*message).security_trading_event())) : std::uint64_t{0});
            checksum += ((*message).sold_out_indicator().has_value() ? bench::digest((*(*message).sold_out_indicator())) : std::uint64_t{0});
            checksum += ((*message).high_px().has_value() ? bench::digest((*(*message).high_px()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).low_px().has_value() ? bench::digest((*(*message).low_px()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
            checksum += ((*message).tes_security_status().has_value() ? bench::digest((*(*message).tes_security_status())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::InstrumentSummary*>(each.message())) {
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).last_update_time().has_value() ? bench::digest((*(*message).last_update_time())) : std::uint64_t{0});
            checksum += ((*message).trd_reg_ts_execution_time().has_value() ? bench::digest((*(*message).trd_reg_ts_execution_time())) : std::uint64_t{0});
            checksum += ((*message).tot_no_orders().has_value() ? bench::digest((*(*message).tot_no_orders())) : std::uint64_t{0});
            checksum += ((*message).security_status().has_value() ? bench::digest((*(*message).security_status())) : std::uint64_t{0});
            checksum += ((*message).security_trading_status().has_value() ? bench::digest((*(*message).security_trading_status())) : std::uint64_t{0});
            checksum += ((*message).market_condition().has_value() ? bench::digest((*(*message).market_condition())) : std::uint64_t{0});
            checksum += ((*message).fast_market_indicator().has_value() ? bench::digest((*(*message).fast_market_indicator())) : std::uint64_t{0});
            checksum += ((*message).security_trading_event().has_value() ? bench::digest((*(*message).security_trading_event())) : std::uint64_t{0});
            checksum += ((*message).sold_out_indicator().has_value() ? bench::digest((*(*message).sold_out_indicator())) : std::uint64_t{0});
            checksum += ((*message).high_px().has_value() ? bench::digest((*(*message).high_px()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).low_px().has_value() ? bench::digest((*(*message).low_px()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).product_complex().has_value() ? bench::digest((*(*message).product_complex())) : std::uint64_t{0});
            checksum += ((*message).no_md_entries().has_value() ? bench::digest((*(*message).no_md_entries())) : std::uint64_t{0});
            checksum += ((*message).tes_security_status().has_value() ? bench::digest((*(*message).tes_security_status())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::MassInstrumentStateChange*>(each.message())) {
            checksum += ((*message).instrument_scope_product_complex().has_value() ? bench::digest((*(*message).instrument_scope_product_complex())) : std::uint64_t{0});
            checksum += ((*message).security_mass_status().has_value() ? bench::digest((*(*message).security_mass_status())) : std::uint64_t{0});
            checksum += ((*message).security_mass_trading_status().has_value() ? bench::digest((*(*message).security_mass_trading_status())) : std::uint64_t{0});
            checksum += ((*message).mass_market_condition().has_value() ? bench::digest((*(*message).mass_market_condition())) : std::uint64_t{0});
            checksum += ((*message).fast_market_indicator().has_value() ? bench::digest((*(*message).fast_market_indicator())) : std::uint64_t{0});
            checksum += ((*message).security_mass_trading_event().has_value() ? bench::digest((*(*message).security_mass_trading_event())) : std::uint64_t{0});
            checksum += ((*message).mass_sold_out_indicator().has_value() ? bench::digest((*(*message).mass_sold_out_indicator())) : std::uint64_t{0});
            checksum += ((*message).tes_security_mass_status().has_value() ? bench::digest((*(*message).tes_security_mass_status())) : std::uint64_t{0});
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
            checksum += ((*message).last_fragment().has_value() ? bench::digest((*(*message).last_fragment())) : std::uint64_t{0});
            checksum += ((*message).no_related_sym().has_value() ? bench::digest((*(*message).no_related_sym())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::OrderAdd*>(each.message())) {
            checksum += ((*message).request_time().has_value() ? bench::digest((*(*message).request_time())) : std::uint64_t{0});
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().trd_reg_ts_time_priority().has_value() ? bench::digest((*(*message).order_details_comp().trd_reg_ts_time_priority())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().display_qty().has_value() ? bench::digest((*(*message).order_details_comp().display_qty()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().side().has_value() ? bench::digest((*(*message).order_details_comp().side())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().ord_type().has_value() ? bench::digest((*(*message).order_details_comp().ord_type())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().hhi_indicator().has_value() ? bench::digest((*(*message).order_details_comp().hhi_indicator())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().price().has_value() ? bench::digest((*(*message).order_details_comp().price()).mantissa()) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::OrderDelete*>(each.message())) {
            checksum += ((*message).request_time().has_value() ? bench::digest((*(*message).request_time())) : std::uint64_t{0});
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().trd_reg_ts_time_priority().has_value() ? bench::digest((*(*message).order_details_comp().trd_reg_ts_time_priority())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().display_qty().has_value() ? bench::digest((*(*message).order_details_comp().display_qty()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().side().has_value() ? bench::digest((*(*message).order_details_comp().side())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().ord_type().has_value() ? bench::digest((*(*message).order_details_comp().ord_type())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().hhi_indicator().has_value() ? bench::digest((*(*message).order_details_comp().hhi_indicator())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().price().has_value() ? bench::digest((*(*message).order_details_comp().price()).mantissa()) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::OrderMassDelete*>(each.message())) {
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::OrderModify*>(each.message())) {
            checksum += ((*message).request_time().has_value() ? bench::digest((*(*message).request_time())) : std::uint64_t{0});
            checksum += ((*message).trd_reg_ts_prev_time_priority().has_value() ? bench::digest((*(*message).trd_reg_ts_prev_time_priority())) : std::uint64_t{0});
            checksum += ((*message).prev_price().has_value() ? bench::digest((*(*message).prev_price()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).prev_display_qty().has_value() ? bench::digest((*(*message).prev_display_qty()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().trd_reg_ts_time_priority().has_value() ? bench::digest((*(*message).order_details_comp().trd_reg_ts_time_priority())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().display_qty().has_value() ? bench::digest((*(*message).order_details_comp().display_qty()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().side().has_value() ? bench::digest((*(*message).order_details_comp().side())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().ord_type().has_value() ? bench::digest((*(*message).order_details_comp().ord_type())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().hhi_indicator().has_value() ? bench::digest((*(*message).order_details_comp().hhi_indicator())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().price().has_value() ? bench::digest((*(*message).order_details_comp().price()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).prev_price_hhi_indicator().has_value() ? bench::digest((*(*message).prev_price_hhi_indicator())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::OrderModifySamePrio*>(each.message())) {
            checksum += ((*message).request_time().has_value() ? bench::digest((*(*message).request_time())) : std::uint64_t{0});
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
            checksum += ((*message).prev_display_qty().has_value() ? bench::digest((*(*message).prev_display_qty()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().trd_reg_ts_time_priority().has_value() ? bench::digest((*(*message).order_details_comp().trd_reg_ts_time_priority())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().display_qty().has_value() ? bench::digest((*(*message).order_details_comp().display_qty()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().side().has_value() ? bench::digest((*(*message).order_details_comp().side())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().ord_type().has_value() ? bench::digest((*(*message).order_details_comp().ord_type())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().hhi_indicator().has_value() ? bench::digest((*(*message).order_details_comp().hhi_indicator())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().price().has_value() ? bench::digest((*(*message).order_details_comp().price()).mantissa()) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::PartialOrderExecution*>(each.message())) {
            checksum += ((*message).side().has_value() ? bench::digest((*(*message).side())) : std::uint64_t{0});
            checksum += ((*message).ord_type().has_value() ? bench::digest((*(*message).ord_type())) : std::uint64_t{0});
            checksum += ((*message).algorithmic_trade_indicator().has_value() ? bench::digest((*(*message).algorithmic_trade_indicator())) : std::uint64_t{0});
            checksum += ((*message).hhi_indicator().has_value() ? bench::digest((*(*message).hhi_indicator())) : std::uint64_t{0});
            checksum += ((*message).trd_match_id().has_value() ? bench::digest((*(*message).trd_match_id())) : std::uint64_t{0});
            checksum += ((*message).price().has_value() ? bench::digest((*(*message).price()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).trd_reg_ts_time_priority().has_value() ? bench::digest((*(*message).trd_reg_ts_time_priority())) : std::uint64_t{0});
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).last_qty().has_value() ? bench::digest((*(*message).last_qty()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).last_px().has_value() ? bench::digest((*(*message).last_px()).mantissa()) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::ProductStateChange*>(each.message())) {
            checksum += ((*message).trading_session_id().has_value() ? bench::digest((*(*message).trading_session_id())) : std::uint64_t{0});
            checksum += ((*message).trading_session_sub_id().has_value() ? bench::digest((*(*message).trading_session_sub_id())) : std::uint64_t{0});
            checksum += ((*message).trad_ses_status().has_value() ? bench::digest((*(*message).trad_ses_status())) : std::uint64_t{0});
            checksum += ((*message).market_condition().has_value() ? bench::digest((*(*message).market_condition())) : std::uint64_t{0});
            checksum += ((*message).fast_market_indicator().has_value() ? bench::digest((*(*message).fast_market_indicator())) : std::uint64_t{0});
            checksum += ((*message).tes_trad_ses_status().has_value() ? bench::digest((*(*message).tes_trad_ses_status())) : std::uint64_t{0});
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::ProductSummary*>(each.message())) {
            checksum += ((*message).last_msg_seq_num_processed().has_value() ? bench::digest((*(*message).last_msg_seq_num_processed())) : std::uint64_t{0});
            checksum += ((*message).trading_session_id().has_value() ? bench::digest((*(*message).trading_session_id())) : std::uint64_t{0});
            checksum += ((*message).trading_session_sub_id().has_value() ? bench::digest((*(*message).trading_session_sub_id())) : std::uint64_t{0});
            checksum += ((*message).trad_ses_status().has_value() ? bench::digest((*(*message).trad_ses_status())) : std::uint64_t{0});
            checksum += ((*message).market_condition().has_value() ? bench::digest((*(*message).market_condition())) : std::uint64_t{0});
            checksum += ((*message).fast_market_indicator().has_value() ? bench::digest((*(*message).fast_market_indicator())) : std::uint64_t{0});
            checksum += ((*message).tes_trad_ses_status().has_value() ? bench::digest((*(*message).tes_trad_ses_status())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::QuoteRequest*>(each.message())) {
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).last_qty().has_value() ? bench::digest((*(*message).last_qty()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).side().has_value() ? bench::digest((*(*message).side())) : std::uint64_t{0});
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::SnapshotOrder*>(each.message())) {
            checksum += ((*message).order_details_comp().trd_reg_ts_time_priority().has_value() ? bench::digest((*(*message).order_details_comp().trd_reg_ts_time_priority())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().display_qty().has_value() ? bench::digest((*(*message).order_details_comp().display_qty()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().side().has_value() ? bench::digest((*(*message).order_details_comp().side())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().ord_type().has_value() ? bench::digest((*(*message).order_details_comp().ord_type())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().hhi_indicator().has_value() ? bench::digest((*(*message).order_details_comp().hhi_indicator())) : std::uint64_t{0});
            checksum += ((*message).order_details_comp().price().has_value() ? bench::digest((*(*message).order_details_comp().price()).mantissa()) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::TesTradeReport*>(each.message())) {
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
            checksum += ((*message).last_qty().has_value() ? bench::digest((*(*message).last_qty()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).last_px().has_value() ? bench::digest((*(*message).last_px()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).trd_match_id().has_value() ? bench::digest((*(*message).trd_match_id())) : std::uint64_t{0});
            checksum += ((*message).trd_type().has_value() ? bench::digest((*(*message).trd_type())) : std::uint64_t{0});
            checksum += ((*message).trade_condition().has_value() ? bench::digest((*(*message).trade_condition())) : std::uint64_t{0});
            checksum += ((*message).multi_leg_reporting_type().has_value() ? bench::digest((*(*message).multi_leg_reporting_type())) : std::uint64_t{0});
            checksum += ((*message).multi_leg_price_model().has_value() ? bench::digest((*(*message).multi_leg_price_model())) : std::uint64_t{0});
            checksum += ((*message).non_disclosed_trade_volume().has_value() ? bench::digest((*(*message).non_disclosed_trade_volume()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).trans_bkd_time().has_value() ? bench::digest((*(*message).trans_bkd_time())) : std::uint64_t{0});
            checksum += ((*message).number_of_buy_sides().has_value() ? bench::digest((*(*message).number_of_buy_sides())) : std::uint64_t{0});
            checksum += ((*message).number_of_sell_sides().has_value() ? bench::digest((*(*message).number_of_sell_sides())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::TopOfBook*>(each.message())) {
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).bid_px().has_value() ? bench::digest((*(*message).bid_px()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).offer_px().has_value() ? bench::digest((*(*message).offer_px()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).bid_size().has_value() ? bench::digest((*(*message).bid_size()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).offer_size().has_value() ? bench::digest((*(*message).offer_size()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).number_of_buy_orders().has_value() ? bench::digest((*(*message).number_of_buy_orders())) : std::uint64_t{0});
            checksum += ((*message).number_of_sell_orders().has_value() ? bench::digest((*(*message).number_of_sell_orders())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::TradeReport*>(each.message())) {
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
            checksum += ((*message).last_qty().has_value() ? bench::digest((*(*message).last_qty()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).last_px().has_value() ? bench::digest((*(*message).last_px()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).trd_match_id().has_value() ? bench::digest((*(*message).trd_match_id())) : std::uint64_t{0});
            checksum += ((*message).match_type().has_value() ? bench::digest((*(*message).match_type())) : std::uint64_t{0});
            checksum += ((*message).match_sub_type().has_value() ? bench::digest((*(*message).match_sub_type())) : std::uint64_t{0});
            checksum += ((*message).algorithmic_trade_indicator().has_value() ? bench::digest((*(*message).algorithmic_trade_indicator())) : std::uint64_t{0});
            checksum += ((*message).trade_condition().has_value() ? bench::digest((*(*message).trade_condition())) : std::uint64_t{0});
        } else if (const auto* message = dynamic_cast<const protocol::TradeReversal*>(each.message())) {
            checksum += ((*message).security_id().has_value() ? bench::digest((*(*message).security_id())) : std::uint64_t{0});
            checksum += ((*message).transact_time().has_value() ? bench::digest((*(*message).transact_time())) : std::uint64_t{0});
            checksum += ((*message).last_qty().has_value() ? bench::digest((*(*message).last_qty()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).last_px().has_value() ? bench::digest((*(*message).last_px()).mantissa()) : std::uint64_t{0});
            checksum += ((*message).trd_reg_ts_execution_time().has_value() ? bench::digest((*(*message).trd_reg_ts_execution_time())) : std::uint64_t{0});
            checksum += ((*message).trd_match_id().has_value() ? bench::digest((*(*message).trd_match_id())) : std::uint64_t{0});
            checksum += ((*message).trade_condition().has_value() ? bench::digest((*(*message).trade_condition())) : std::uint64_t{0});
            checksum += ((*message).md_origin_type().has_value() ? bench::digest((*(*message).md_origin_type())) : std::uint64_t{0});
            checksum += ((*message).no_md_entries().has_value() ? bench::digest((*(*message).no_md_entries())) : std::uint64_t{0});
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Eurex.T7.Eobi.Fbe.v13.0", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
