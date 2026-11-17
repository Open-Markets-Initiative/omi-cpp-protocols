// Eurex.T7.Eobi.Fbe.v15.0: main.cpp
// Eurex.T7.Eobi.Fbe.v15.0 benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/eurex/t7/eobi/fbe/v15.0.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/eurex/t7/eobi/fbe/v15.0/definitions.hpp"

namespace protocol = ::eurex::t7::eobi::fbe::v15_0;

namespace {

// The values the Modern iterator reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    checksum += (static_cast<std::uint16_t>(iterator.packet_header->eobi_header.body_len.get()) != 0x0FFFFU ? bench::digest(iterator.packet_header->eobi_header.body_len.get()) : std::uint64_t{0});
    checksum += (static_cast<std::uint16_t>(iterator.packet_header->eobi_header.template_id.get()) != 0x0FFFFU ? bench::digest(iterator.packet_header->eobi_header.template_id.get()) : std::uint64_t{0});
    checksum += (static_cast<std::uint32_t>(iterator.packet_header->eobi_header.msg_seq_num.get()) != 0x0FFFFFFFFU ? bench::digest(iterator.packet_header->eobi_header.msg_seq_num.get()) : std::uint64_t{0});
    checksum += (static_cast<std::uint32_t>(iterator.packet_header->appl_seq_num.get()) != 0x0FFFFFFFFU ? bench::digest(iterator.packet_header->appl_seq_num.get()) : std::uint64_t{0});
    checksum += (static_cast<std::uint32_t>(iterator.packet_header->market_segment_id.get()) != 0x080000000U ? bench::digest(iterator.packet_header->market_segment_id.get()) : std::uint64_t{0});
    checksum += (static_cast<std::uint8_t>(iterator.packet_header->partition_id.get()) != 0x0FFU ? bench::digest(iterator.packet_header->partition_id.get()) : std::uint64_t{0});
    checksum += (static_cast<std::uint8_t>(iterator.packet_header->completion_indicator.get()) != 0x0FFU ? bench::digest(iterator.packet_header->completion_indicator.get()) : std::uint64_t{0});
    checksum += (static_cast<std::uint8_t>(iterator.packet_header->appl_seq_reset_indicator.get()) != 0x0FFU ? bench::digest(iterator.packet_header->appl_seq_reset_indicator.get()) : std::uint64_t{0});
    checksum += (static_cast<std::uint8_t>(iterator.packet_header->dscp.get()) != 0x0FFU ? bench::digest(iterator.packet_header->dscp.get()) : std::uint64_t{0});
    checksum += (static_cast<std::uint64_t>(iterator.packet_header->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(iterator.packet_header->transact_time.get()) : std::uint64_t{0});

    std::size_t index = 0;

    while (iterator.next()) {
        checksum += index++;
        checksum += (static_cast<std::uint16_t>(iterator.message_header_comp->body_len.get()) != 0x0FFFFU ? bench::digest(iterator.message_header_comp->body_len.get()) : std::uint64_t{0});
        checksum += (static_cast<std::uint16_t>(iterator.message_header_comp->template_id.get()) != 0x0FFFFU ? bench::digest(iterator.message_header_comp->template_id.get()) : std::uint64_t{0});
        checksum += (static_cast<std::uint32_t>(iterator.message_header_comp->msg_seq_num.get()) != 0x0FFFFFFFFU ? bench::digest(iterator.message_header_comp->msg_seq_num.get()) : std::uint64_t{0});

        if (iterator.template_id == protocol::AddComplexInstrument::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddComplexInstrument::parse(iterator.message);
            checksum += (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? bench::digest(message->security_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->transact_time.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->security_sub_type.get()) != 0x080000000U ? bench::digest(message->security_sub_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->product_complex.get()) != 0x0FFU ? bench::digest(message->product_complex.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->implied_market_indicator.get()) != 0x0FFU ? bench::digest(message->implied_market_indicator.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint16_t>(message->quantity_scaling_factor.get()) != 0x0FFFFU ? bench::digest(message->quantity_scaling_factor.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->leg_ratio_multiplier.get()) != 0x0FFFFFFFFU ? bench::digest(message->leg_ratio_multiplier.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->no_legs.get()) != 0x0FFU ? bench::digest(message->no_legs.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->last_fragment.get()) != 0x0FFU ? bench::digest(message->last_fragment.get()) : std::uint64_t{0});
        } else if (iterator.template_id == protocol::AddFlexibleInstrument::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddFlexibleInstrument::parse(iterator.message);
            checksum += (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? bench::digest(message->security_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->transact_time.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->security_type.get()) != 0x0FFU ? bench::digest(message->security_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->put_or_call.get()) != 0x0FFU ? bench::digest(message->put_or_call.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->exercise_style.get()) != 0x0FFU ? bench::digest(message->exercise_style.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->settl_method.get()) != 0x0FFU ? bench::digest(message->settl_method.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->maturity_date.get()) != 0x0FFFFFFFFU ? bench::digest(message->maturity_date.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->strike_price.integer()) != 0x08000000000000000ULL ? bench::digest(message->strike_price.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->opt_attribute.get()) != 0x0FFFFFFFFU ? bench::digest(message->opt_attribute.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->contract_date.get()) != 0x0FFFFFFFFU ? bench::digest(message->contract_date.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->security_reference_data_supplement.get()) != 0x0FFFFFFFFU ? bench::digest(message->security_reference_data_supplement.get()) : std::uint64_t{0});
        } else if (iterator.template_id == protocol::AddScaledSimpleInstrument::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddScaledSimpleInstrument::parse(iterator.message);
            checksum += (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? bench::digest(message->security_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->transact_time.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->security_type.get()) != 0x0FFU ? bench::digest(message->security_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint16_t>(message->quantity_scaling_factor.get()) != 0x0FFFFU ? bench::digest(message->quantity_scaling_factor.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->related_instrument_grp_comp.related_security_id.get()) != 0x08000000000000000ULL ? bench::digest(message->related_instrument_grp_comp.related_security_id.get()) : std::uint64_t{0});
        } else if (iterator.template_id == protocol::AuctionBbo::message_type) {
            [[maybe_unused]] const auto* message = protocol::AuctionBbo::parse(iterator.message);
            checksum += (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->transact_time.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? bench::digest(message->security_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->bid_px.integer()) != 0x08000000000000000ULL ? bench::digest(message->bid_px.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->offer_px.integer()) != 0x08000000000000000ULL ? bench::digest(message->offer_px.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->bid_size.integer()) != 0x08000000000000000ULL ? bench::digest(message->bid_size.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->offer_size.integer()) != 0x08000000000000000ULL ? bench::digest(message->offer_size.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->potential_security_trading_event.get()) != 0x0FFU ? bench::digest(message->potential_security_trading_event.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->bid_ord_type.get()) != 0x0FFU ? bench::digest(message->bid_ord_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->offer_ord_type.get()) != 0x0FFU ? bench::digest(message->offer_ord_type.get()) : std::uint64_t{0});
        } else if (iterator.template_id == protocol::AuctionClearingPrice::message_type) {
            [[maybe_unused]] const auto* message = protocol::AuctionClearingPrice::parse(iterator.message);
            checksum += (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->transact_time.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? bench::digest(message->security_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->last_px.integer()) != 0x08000000000000000ULL ? bench::digest(message->last_px.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->last_qty.integer()) != 0x08000000000000000ULL ? bench::digest(message->last_qty.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->imbalance_qty.integer()) != 0x08000000000000000ULL ? bench::digest(message->imbalance_qty.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->security_trading_status.get()) != 0x0FFU ? bench::digest(message->security_trading_status.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->potential_security_trading_event.get()) != 0x0FFU ? bench::digest(message->potential_security_trading_event.get()) : std::uint64_t{0});
        } else if (iterator.template_id == protocol::CrossRequest::message_type) {
            [[maybe_unused]] const auto* message = protocol::CrossRequest::parse(iterator.message);
            checksum += (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? bench::digest(message->security_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->last_px.integer()) != 0x08000000000000000ULL ? bench::digest(message->last_px.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->last_qty.integer()) != 0x08000000000000000ULL ? bench::digest(message->last_qty.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->side.get()) != 0x0FFU ? bench::digest(message->side.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->cross_request_type.get()) != 0x0FFU ? bench::digest(message->cross_request_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->input_source.get()) != 0x0FFU ? bench::digest(message->input_source.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->transact_time.get()) : std::uint64_t{0});
        } else if (iterator.template_id == protocol::ExecutionSummary::message_type) {
            [[maybe_unused]] const auto* message = protocol::ExecutionSummary::parse(iterator.message);
            checksum += (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? bench::digest(message->security_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->request_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->request_time.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->exec_id.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->exec_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->last_qty.integer()) != 0x08000000000000000ULL ? bench::digest(message->last_qty.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->aggressor_side.get()) != 0x0FFU ? bench::digest(message->aggressor_side.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint16_t>(message->trade_condition.get()) != 0x0FFFFU ? bench::digest(message->trade_condition.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->trading_hhi_indicator.get()) != 0x0FFU ? bench::digest(message->trading_hhi_indicator.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->last_px.integer()) != 0x08000000000000000ULL ? bench::digest(message->last_px.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->remaining_order_details_comp.trd_reg_ts_prev_time_priority.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->remaining_order_details_comp.trd_reg_ts_prev_time_priority.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->remaining_order_details_comp.display_qty.integer()) != 0x08000000000000000ULL ? bench::digest(message->remaining_order_details_comp.display_qty.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->remaining_order_details_comp.price.integer()) != 0x08000000000000000ULL ? bench::digest(message->remaining_order_details_comp.price.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->resting_hidden_qty.integer()) != 0x08000000000000000ULL ? bench::digest(message->resting_hidden_qty.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->resting_cxl_qty.integer()) != 0x08000000000000000ULL ? bench::digest(message->resting_cxl_qty.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->aggressor_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->aggressor_time.get()) : std::uint64_t{0});
        } else if (iterator.template_id == protocol::FullOrderExecution::message_type) {
            [[maybe_unused]] const auto* message = protocol::FullOrderExecution::parse(iterator.message);
            checksum += (static_cast<std::uint8_t>(message->side.get()) != 0x0FFU ? bench::digest(message->side.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->ord_type.get()) != 0x0FFU ? bench::digest(message->ord_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->algorithmic_trade_indicator.get()) != 0x0FFU ? bench::digest(message->algorithmic_trade_indicator.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->hhi_indicator.get()) != 0x080U ? bench::digest(message->hhi_indicator.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->trd_match_id.get()) != 0x0FFFFFFFFU ? bench::digest(message->trd_match_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->price.integer()) != 0x08000000000000000ULL ? bench::digest(message->price.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->trd_reg_ts_time_priority.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->trd_reg_ts_time_priority.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? bench::digest(message->security_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->last_qty.integer()) != 0x08000000000000000ULL ? bench::digest(message->last_qty.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->last_px.integer()) != 0x08000000000000000ULL ? bench::digest(message->last_px.integer()) : std::uint64_t{0});
        } else if (iterator.template_id == protocol::Heartbeat::message_type) {
            [[maybe_unused]] const auto* message = protocol::Heartbeat::parse(iterator.message);
            checksum += (static_cast<std::uint32_t>(message->last_msg_seq_num_processed.get()) != 0x0FFFFFFFFU ? bench::digest(message->last_msg_seq_num_processed.get()) : std::uint64_t{0});
        } else if (iterator.template_id == protocol::InstrumentStateChange::message_type) {
            [[maybe_unused]] const auto* message = protocol::InstrumentStateChange::parse(iterator.message);
            checksum += (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? bench::digest(message->security_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->security_status.get()) != 0x0FFU ? bench::digest(message->security_status.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->security_trading_status.get()) != 0x0FFU ? bench::digest(message->security_trading_status.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->market_condition.get()) != 0x0FFU ? bench::digest(message->market_condition.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->fast_market_indicator.get()) != 0x0FFU ? bench::digest(message->fast_market_indicator.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->security_trading_event.get()) != 0x0FFU ? bench::digest(message->security_trading_event.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->sold_out_indicator.get()) != 0x0FFU ? bench::digest(message->sold_out_indicator.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->high_px.integer()) != 0x08000000000000000ULL ? bench::digest(message->high_px.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->low_px.integer()) != 0x08000000000000000ULL ? bench::digest(message->low_px.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->transact_time.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->tes_security_status.get()) != 0x0FFU ? bench::digest(message->tes_security_status.get()) : std::uint64_t{0});
        } else if (iterator.template_id == protocol::InstrumentSummary::message_type) {
            [[maybe_unused]] const auto* message = protocol::InstrumentSummary::parse(iterator.message);
            checksum += (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? bench::digest(message->security_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->last_update_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->last_update_time.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->trd_reg_ts_execution_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->trd_reg_ts_execution_time.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint16_t>(message->tot_no_orders.get()) != 0x0FFFFU ? bench::digest(message->tot_no_orders.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->security_status.get()) != 0x0FFU ? bench::digest(message->security_status.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->security_trading_status.get()) != 0x0FFU ? bench::digest(message->security_trading_status.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->market_condition.get()) != 0x0FFU ? bench::digest(message->market_condition.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->fast_market_indicator.get()) != 0x0FFU ? bench::digest(message->fast_market_indicator.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->security_trading_event.get()) != 0x0FFU ? bench::digest(message->security_trading_event.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->sold_out_indicator.get()) != 0x0FFU ? bench::digest(message->sold_out_indicator.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->high_px.integer()) != 0x08000000000000000ULL ? bench::digest(message->high_px.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->low_px.integer()) != 0x08000000000000000ULL ? bench::digest(message->low_px.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->product_complex.get()) != 0x0FFU ? bench::digest(message->product_complex.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->no_md_entries.get()) != 0x0FFU ? bench::digest(message->no_md_entries.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->tes_security_status.get()) != 0x0FFU ? bench::digest(message->tes_security_status.get()) : std::uint64_t{0});
        } else if (iterator.template_id == protocol::MassInstrumentStateChange::message_type) {
            [[maybe_unused]] const auto* message = protocol::MassInstrumentStateChange::parse(iterator.message);
            checksum += (static_cast<std::uint8_t>(message->instrument_scope_product_complex.get()) != 0x0FFU ? bench::digest(message->instrument_scope_product_complex.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->security_mass_status.get()) != 0x0FFU ? bench::digest(message->security_mass_status.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->security_mass_trading_status.get()) != 0x0FFU ? bench::digest(message->security_mass_trading_status.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->mass_market_condition.get()) != 0x0FFU ? bench::digest(message->mass_market_condition.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->fast_market_indicator.get()) != 0x0FFU ? bench::digest(message->fast_market_indicator.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->security_mass_trading_event.get()) != 0x0FFU ? bench::digest(message->security_mass_trading_event.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->mass_sold_out_indicator.get()) != 0x0FFU ? bench::digest(message->mass_sold_out_indicator.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->tes_security_mass_status.get()) != 0x0FFU ? bench::digest(message->tes_security_mass_status.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->transact_time.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->last_fragment.get()) != 0x0FFU ? bench::digest(message->last_fragment.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->no_related_sym.get()) != 0x0FFU ? bench::digest(message->no_related_sym.get()) : std::uint64_t{0});
        } else if (iterator.template_id == protocol::OrderAdd::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderAdd::parse(iterator.message);
            checksum += (static_cast<std::uint64_t>(message->request_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->request_time.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? bench::digest(message->security_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->order_details_comp.trd_reg_ts_time_priority.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->order_details_comp.trd_reg_ts_time_priority.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->order_details_comp.display_qty.integer()) != 0x08000000000000000ULL ? bench::digest(message->order_details_comp.display_qty.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->order_details_comp.side.get()) != 0x0FFU ? bench::digest(message->order_details_comp.side.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->order_details_comp.ord_type.get()) != 0x0FFU ? bench::digest(message->order_details_comp.ord_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->order_details_comp.hhi_indicator.get()) != 0x080U ? bench::digest(message->order_details_comp.hhi_indicator.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->order_details_comp.price.integer()) != 0x08000000000000000ULL ? bench::digest(message->order_details_comp.price.integer()) : std::uint64_t{0});
        } else if (iterator.template_id == protocol::OrderDelete::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderDelete::parse(iterator.message);
            checksum += (static_cast<std::uint64_t>(message->request_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->request_time.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->transact_time.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? bench::digest(message->security_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->order_details_comp.trd_reg_ts_time_priority.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->order_details_comp.trd_reg_ts_time_priority.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->order_details_comp.display_qty.integer()) != 0x08000000000000000ULL ? bench::digest(message->order_details_comp.display_qty.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->order_details_comp.side.get()) != 0x0FFU ? bench::digest(message->order_details_comp.side.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->order_details_comp.ord_type.get()) != 0x0FFU ? bench::digest(message->order_details_comp.ord_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->order_details_comp.hhi_indicator.get()) != 0x080U ? bench::digest(message->order_details_comp.hhi_indicator.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->order_details_comp.price.integer()) != 0x08000000000000000ULL ? bench::digest(message->order_details_comp.price.integer()) : std::uint64_t{0});
        } else if (iterator.template_id == protocol::OrderMassDelete::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderMassDelete::parse(iterator.message);
            checksum += (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? bench::digest(message->security_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->transact_time.get()) : std::uint64_t{0});
        } else if (iterator.template_id == protocol::OrderModify::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderModify::parse(iterator.message);
            checksum += (static_cast<std::uint64_t>(message->request_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->request_time.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->trd_reg_ts_prev_time_priority.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->trd_reg_ts_prev_time_priority.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->prev_price.integer()) != 0x08000000000000000ULL ? bench::digest(message->prev_price.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->prev_display_qty.integer()) != 0x08000000000000000ULL ? bench::digest(message->prev_display_qty.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? bench::digest(message->security_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->order_details_comp.trd_reg_ts_time_priority.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->order_details_comp.trd_reg_ts_time_priority.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->order_details_comp.display_qty.integer()) != 0x08000000000000000ULL ? bench::digest(message->order_details_comp.display_qty.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->order_details_comp.side.get()) != 0x0FFU ? bench::digest(message->order_details_comp.side.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->order_details_comp.ord_type.get()) != 0x0FFU ? bench::digest(message->order_details_comp.ord_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->order_details_comp.hhi_indicator.get()) != 0x080U ? bench::digest(message->order_details_comp.hhi_indicator.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->order_details_comp.price.integer()) != 0x08000000000000000ULL ? bench::digest(message->order_details_comp.price.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->prev_price_hhi_indicator.get()) != 0x080U ? bench::digest(message->prev_price_hhi_indicator.get()) : std::uint64_t{0});
        } else if (iterator.template_id == protocol::OrderModifySamePrio::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderModifySamePrio::parse(iterator.message);
            checksum += (static_cast<std::uint64_t>(message->request_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->request_time.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->transact_time.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->prev_display_qty.integer()) != 0x08000000000000000ULL ? bench::digest(message->prev_display_qty.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? bench::digest(message->security_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->order_details_comp.trd_reg_ts_time_priority.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->order_details_comp.trd_reg_ts_time_priority.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->order_details_comp.display_qty.integer()) != 0x08000000000000000ULL ? bench::digest(message->order_details_comp.display_qty.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->order_details_comp.side.get()) != 0x0FFU ? bench::digest(message->order_details_comp.side.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->order_details_comp.ord_type.get()) != 0x0FFU ? bench::digest(message->order_details_comp.ord_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->order_details_comp.hhi_indicator.get()) != 0x080U ? bench::digest(message->order_details_comp.hhi_indicator.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->order_details_comp.price.integer()) != 0x08000000000000000ULL ? bench::digest(message->order_details_comp.price.integer()) : std::uint64_t{0});
        } else if (iterator.template_id == protocol::PartialOrderExecution::message_type) {
            [[maybe_unused]] const auto* message = protocol::PartialOrderExecution::parse(iterator.message);
            checksum += (static_cast<std::uint8_t>(message->side.get()) != 0x0FFU ? bench::digest(message->side.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->ord_type.get()) != 0x0FFU ? bench::digest(message->ord_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->algorithmic_trade_indicator.get()) != 0x0FFU ? bench::digest(message->algorithmic_trade_indicator.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->hhi_indicator.get()) != 0x080U ? bench::digest(message->hhi_indicator.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->trd_match_id.get()) != 0x0FFFFFFFFU ? bench::digest(message->trd_match_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->price.integer()) != 0x08000000000000000ULL ? bench::digest(message->price.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->trd_reg_ts_time_priority.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->trd_reg_ts_time_priority.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? bench::digest(message->security_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->last_qty.integer()) != 0x08000000000000000ULL ? bench::digest(message->last_qty.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->last_px.integer()) != 0x08000000000000000ULL ? bench::digest(message->last_px.integer()) : std::uint64_t{0});
        } else if (iterator.template_id == protocol::ProductStateChange::message_type) {
            [[maybe_unused]] const auto* message = protocol::ProductStateChange::parse(iterator.message);
            checksum += (static_cast<std::uint8_t>(message->trading_session_id.get()) != 0x0FFU ? bench::digest(message->trading_session_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->trading_session_sub_id.get()) != 0x0FFU ? bench::digest(message->trading_session_sub_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->trad_ses_status.get()) != 0x0FFU ? bench::digest(message->trad_ses_status.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->market_condition.get()) != 0x0FFU ? bench::digest(message->market_condition.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->fast_market_indicator.get()) != 0x0FFU ? bench::digest(message->fast_market_indicator.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->tes_trad_ses_status.get()) != 0x0FFU ? bench::digest(message->tes_trad_ses_status.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->transact_time.get()) : std::uint64_t{0});
        } else if (iterator.template_id == protocol::ProductSummary::message_type) {
            [[maybe_unused]] const auto* message = protocol::ProductSummary::parse(iterator.message);
            checksum += (static_cast<std::uint32_t>(message->last_msg_seq_num_processed.get()) != 0x0FFFFFFFFU ? bench::digest(message->last_msg_seq_num_processed.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->trading_session_id.get()) != 0x0FFU ? bench::digest(message->trading_session_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->trading_session_sub_id.get()) != 0x0FFU ? bench::digest(message->trading_session_sub_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->trad_ses_status.get()) != 0x0FFU ? bench::digest(message->trad_ses_status.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->market_condition.get()) != 0x0FFU ? bench::digest(message->market_condition.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->fast_market_indicator.get()) != 0x0FFU ? bench::digest(message->fast_market_indicator.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->tes_trad_ses_status.get()) != 0x0FFU ? bench::digest(message->tes_trad_ses_status.get()) : std::uint64_t{0});
        } else if (iterator.template_id == protocol::QuoteRequest::message_type) {
            [[maybe_unused]] const auto* message = protocol::QuoteRequest::parse(iterator.message);
            checksum += (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? bench::digest(message->security_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->last_qty.integer()) != 0x08000000000000000ULL ? bench::digest(message->last_qty.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->side.get()) != 0x0FFU ? bench::digest(message->side.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->transact_time.get()) : std::uint64_t{0});
        } else if (iterator.template_id == protocol::SnapshotOrder::message_type) {
            [[maybe_unused]] const auto* message = protocol::SnapshotOrder::parse(iterator.message);
            checksum += (static_cast<std::uint64_t>(message->order_details_comp.trd_reg_ts_time_priority.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->order_details_comp.trd_reg_ts_time_priority.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->order_details_comp.display_qty.integer()) != 0x08000000000000000ULL ? bench::digest(message->order_details_comp.display_qty.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->order_details_comp.side.get()) != 0x0FFU ? bench::digest(message->order_details_comp.side.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->order_details_comp.ord_type.get()) != 0x0FFU ? bench::digest(message->order_details_comp.ord_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->order_details_comp.hhi_indicator.get()) != 0x080U ? bench::digest(message->order_details_comp.hhi_indicator.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->order_details_comp.price.integer()) != 0x08000000000000000ULL ? bench::digest(message->order_details_comp.price.integer()) : std::uint64_t{0});
        } else if (iterator.template_id == protocol::TesTradeReport::message_type) {
            [[maybe_unused]] const auto* message = protocol::TesTradeReport::parse(iterator.message);
            checksum += (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? bench::digest(message->security_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->transact_time.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->last_qty.integer()) != 0x08000000000000000ULL ? bench::digest(message->last_qty.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->last_px.integer()) != 0x08000000000000000ULL ? bench::digest(message->last_px.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->trd_match_id.get()) != 0x0FFFFFFFFU ? bench::digest(message->trd_match_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint16_t>(message->trd_type.get()) != 0x0FFFFU ? bench::digest(message->trd_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint16_t>(message->trade_condition.get()) != 0x0FFFFU ? bench::digest(message->trade_condition.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->multi_leg_reporting_type.get()) != 0x0FFU ? bench::digest(message->multi_leg_reporting_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->multi_leg_price_model.get()) != 0x0FFU ? bench::digest(message->multi_leg_price_model.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->non_disclosed_trade_volume.integer()) != 0x08000000000000000ULL ? bench::digest(message->non_disclosed_trade_volume.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->trans_bkd_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->trans_bkd_time.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint16_t>(message->number_of_buy_sides.get()) != 0x0FFFFU ? bench::digest(message->number_of_buy_sides.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint16_t>(message->number_of_sell_sides.get()) != 0x0FFFFU ? bench::digest(message->number_of_sell_sides.get()) : std::uint64_t{0});
        } else if (iterator.template_id == protocol::TopOfBook::message_type) {
            [[maybe_unused]] const auto* message = protocol::TopOfBook::parse(iterator.message);
            checksum += (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->transact_time.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? bench::digest(message->security_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->bid_px.integer()) != 0x08000000000000000ULL ? bench::digest(message->bid_px.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->offer_px.integer()) != 0x08000000000000000ULL ? bench::digest(message->offer_px.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->bid_size.integer()) != 0x08000000000000000ULL ? bench::digest(message->bid_size.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->offer_size.integer()) != 0x08000000000000000ULL ? bench::digest(message->offer_size.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint16_t>(message->number_of_buy_orders.get()) != 0x0FFFFU ? bench::digest(message->number_of_buy_orders.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint16_t>(message->number_of_sell_orders.get()) != 0x0FFFFU ? bench::digest(message->number_of_sell_orders.get()) : std::uint64_t{0});
        } else if (iterator.template_id == protocol::TradeReport::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeReport::parse(iterator.message);
            checksum += (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? bench::digest(message->security_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->transact_time.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->last_qty.integer()) != 0x08000000000000000ULL ? bench::digest(message->last_qty.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->last_px.integer()) != 0x08000000000000000ULL ? bench::digest(message->last_px.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->trd_match_id.get()) != 0x0FFFFFFFFU ? bench::digest(message->trd_match_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->match_type.get()) != 0x0FFU ? bench::digest(message->match_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->match_sub_type.get()) != 0x0FFU ? bench::digest(message->match_sub_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->algorithmic_trade_indicator.get()) != 0x0FFU ? bench::digest(message->algorithmic_trade_indicator.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint16_t>(message->trade_condition.get()) != 0x0FFFFU ? bench::digest(message->trade_condition.get()) : std::uint64_t{0});
        } else if (iterator.template_id == protocol::TradeReversal::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeReversal::parse(iterator.message);
            checksum += (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? bench::digest(message->security_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->transact_time.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->last_qty.integer()) != 0x08000000000000000ULL ? bench::digest(message->last_qty.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->last_px.integer()) != 0x08000000000000000ULL ? bench::digest(message->last_px.integer()) : std::uint64_t{0});
            checksum += (static_cast<std::uint64_t>(message->trd_reg_ts_execution_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? bench::digest(message->trd_reg_ts_execution_time.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint32_t>(message->trd_match_id.get()) != 0x0FFFFFFFFU ? bench::digest(message->trd_match_id.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint16_t>(message->trade_condition.get()) != 0x0FFFFU ? bench::digest(message->trade_condition.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->md_origin_type.get()) != 0x0FFU ? bench::digest(message->md_origin_type.get()) : std::uint64_t{0});
            checksum += (static_cast<std::uint8_t>(message->no_md_entries.get()) != 0x0FFU ? bench::digest(message->no_md_entries.get()) : std::uint64_t{0});
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Eurex.T7.Eobi.Fbe.v15.0", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
