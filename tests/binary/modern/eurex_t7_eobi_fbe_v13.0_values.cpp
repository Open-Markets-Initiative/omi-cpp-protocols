// Eurex.T7.Eobi.Fbe.v13.0 canonical values, through the Modern iterator: every value Modern reads from
// each sample, at its address, held to what the model reads.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "tests/canonical/Canonical.hpp"
#include "cpp/binary/modern/eurex/t7/eobi/fbe/v13.0/definitions.hpp"

namespace protocol = ::eurex::t7::eobi::fbe::v13_0;

namespace {

// The values the Modern iterator reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    values["packet.packetheader.eobiheader.bodylen"] = (static_cast<std::uint16_t>(iterator.packet_header->eobi_header.body_len.get()) != 0x0FFFFU ? canonical::number(iterator.packet_header->eobi_header.body_len.get()) : canonical::absent());
    values["packet.packetheader.eobiheader.templateid"] = (static_cast<std::uint16_t>(iterator.packet_header->eobi_header.template_id.get()) != 0x0FFFFU ? canonical::number(iterator.packet_header->eobi_header.template_id.get()) : canonical::absent());
    values["packet.packetheader.eobiheader.msgseqnum"] = (static_cast<std::uint32_t>(iterator.packet_header->eobi_header.msg_seq_num.get()) != 0x0FFFFFFFFU ? canonical::number(iterator.packet_header->eobi_header.msg_seq_num.get()) : canonical::absent());
    values["packet.packetheader.applseqnum"] = (static_cast<std::uint32_t>(iterator.packet_header->appl_seq_num.get()) != 0x0FFFFFFFFU ? canonical::number(iterator.packet_header->appl_seq_num.get()) : canonical::absent());
    values["packet.packetheader.marketsegmentid"] = (static_cast<std::uint32_t>(iterator.packet_header->market_segment_id.get()) != 0x080000000U ? canonical::number(iterator.packet_header->market_segment_id.get()) : canonical::absent());
    values["packet.packetheader.partitionid"] = (static_cast<std::uint8_t>(iterator.packet_header->partition_id.get()) != 0x0FFU ? canonical::number(iterator.packet_header->partition_id.get()) : canonical::absent());
    values["packet.packetheader.completionindicator"] = (static_cast<std::uint8_t>(iterator.packet_header->completion_indicator.get()) != 0x0FFU ? canonical::number(iterator.packet_header->completion_indicator.get()) : canonical::absent());
    values["packet.packetheader.applseqresetindicator"] = (static_cast<std::uint8_t>(iterator.packet_header->appl_seq_reset_indicator.get()) != 0x0FFU ? canonical::number(iterator.packet_header->appl_seq_reset_indicator.get()) : canonical::absent());
    values["packet.packetheader.dscp"] = (static_cast<std::uint8_t>(iterator.packet_header->dscp.get()) != 0x0FFU ? canonical::number(iterator.packet_header->dscp.get()) : canonical::absent());
    values["packet.packetheader.transacttime"] = (static_cast<std::uint64_t>(iterator.packet_header->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(iterator.packet_header->transact_time.get()) : canonical::absent());

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheadercomp.bodylen"] = (static_cast<std::uint16_t>(iterator.message_header_comp->body_len.get()) != 0x0FFFFU ? canonical::number(iterator.message_header_comp->body_len.get()) : canonical::absent());
        values[entry + ".messageheadercomp.templateid"] = (static_cast<std::uint16_t>(iterator.message_header_comp->template_id.get()) != 0x0FFFFU ? canonical::number(iterator.message_header_comp->template_id.get()) : canonical::absent());
        values[entry + ".messageheadercomp.msgseqnum"] = (static_cast<std::uint32_t>(iterator.message_header_comp->msg_seq_num.get()) != 0x0FFFFFFFFU ? canonical::number(iterator.message_header_comp->msg_seq_num.get()) : canonical::absent());

        if (iterator.template_id == protocol::AddComplexInstrument::message_type) {
            values[entry + ".payload"] = "packet.message.payload.addcomplexinstrument";
            [[maybe_unused]] const auto* message = protocol::AddComplexInstrument::parse(iterator.message);
            values[entry + ".payload.addcomplexinstrument.securityid"] = (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? canonical::number(message->security_id.get()) : canonical::absent());
            values[entry + ".payload.addcomplexinstrument.transacttime"] = (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->transact_time.get()) : canonical::absent());
            values[entry + ".payload.addcomplexinstrument.securitysubtype"] = (static_cast<std::uint32_t>(message->security_sub_type.get()) != 0x080000000U ? canonical::number(message->security_sub_type.get()) : canonical::absent());
            values[entry + ".payload.addcomplexinstrument.productcomplex"] = (static_cast<std::uint8_t>(message->product_complex.get()) != 0x0FFU ? canonical::number(message->product_complex.get()) : canonical::absent());
            values[entry + ".payload.addcomplexinstrument.impliedmarketindicator"] = (static_cast<std::uint8_t>(message->implied_market_indicator.get()) != 0x0FFU ? canonical::number(message->implied_market_indicator.get()) : canonical::absent());
            values[entry + ".payload.addcomplexinstrument.quantityscalingfactor"] = (static_cast<std::uint16_t>(message->quantity_scaling_factor.get()) != 0x0FFFFU ? canonical::number(message->quantity_scaling_factor.get()) : canonical::absent());
            values[entry + ".payload.addcomplexinstrument.legratiomultiplier"] = (static_cast<std::uint32_t>(message->leg_ratio_multiplier.get()) != 0x0FFFFFFFFU ? canonical::number(message->leg_ratio_multiplier.get()) : canonical::absent());
            values[entry + ".payload.addcomplexinstrument.nolegs"] = (static_cast<std::uint8_t>(message->no_legs.get()) != 0x0FFU ? canonical::number(message->no_legs.get()) : canonical::absent());
            values[entry + ".payload.addcomplexinstrument.lastfragment"] = (static_cast<std::uint8_t>(message->last_fragment.get()) != 0x0FFU ? canonical::number(message->last_fragment.get()) : canonical::absent());
        } else if (iterator.template_id == protocol::AddFlexibleInstrument::message_type) {
            values[entry + ".payload"] = "packet.message.payload.addflexibleinstrument";
            [[maybe_unused]] const auto* message = protocol::AddFlexibleInstrument::parse(iterator.message);
            values[entry + ".payload.addflexibleinstrument.securityid"] = (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? canonical::number(message->security_id.get()) : canonical::absent());
            values[entry + ".payload.addflexibleinstrument.transacttime"] = (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->transact_time.get()) : canonical::absent());
            values[entry + ".payload.addflexibleinstrument.securitytype"] = (static_cast<std::uint8_t>(message->security_type.get()) != 0x0FFU ? canonical::number(message->security_type.get()) : canonical::absent());
            values[entry + ".payload.addflexibleinstrument.putorcall"] = (static_cast<std::uint8_t>(message->put_or_call.get()) != 0x0FFU ? canonical::number(message->put_or_call.get()) : canonical::absent());
            values[entry + ".payload.addflexibleinstrument.exercisestyle"] = (static_cast<std::uint8_t>(message->exercise_style.get()) != 0x0FFU ? canonical::number(message->exercise_style.get()) : canonical::absent());
            values[entry + ".payload.addflexibleinstrument.settlmethod"] = (static_cast<std::uint8_t>(message->settl_method.get()) != 0x0FFU ? canonical::number(message->settl_method.get()) : canonical::absent());
            values[entry + ".payload.addflexibleinstrument.maturitydate"] = (static_cast<std::uint32_t>(message->maturity_date.get()) != 0x0FFFFFFFFU ? canonical::number(message->maturity_date.get()) : canonical::absent());
            values[entry + ".payload.addflexibleinstrument.strikeprice"] = (static_cast<std::uint64_t>(message->strike_price.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->strike_price.integer(), -8) : canonical::absent());
            values[entry + ".payload.addflexibleinstrument.optattribute"] = (static_cast<std::uint32_t>(message->opt_attribute.get()) != 0x0FFFFFFFFU ? canonical::number(message->opt_attribute.get()) : canonical::absent());
            values[entry + ".payload.addflexibleinstrument.contractdate"] = (static_cast<std::uint32_t>(message->contract_date.get()) != 0x0FFFFFFFFU ? canonical::number(message->contract_date.get()) : canonical::absent());
            values[entry + ".payload.addflexibleinstrument.securityreferencedatasupplement"] = (static_cast<std::uint32_t>(message->security_reference_data_supplement.get()) != 0x0FFFFFFFFU ? canonical::number(message->security_reference_data_supplement.get()) : canonical::absent());
        } else if (iterator.template_id == protocol::AddScaledSimpleInstrument::message_type) {
            values[entry + ".payload"] = "packet.message.payload.addscaledsimpleinstrument";
            [[maybe_unused]] const auto* message = protocol::AddScaledSimpleInstrument::parse(iterator.message);
            values[entry + ".payload.addscaledsimpleinstrument.securityid"] = (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? canonical::number(message->security_id.get()) : canonical::absent());
            values[entry + ".payload.addscaledsimpleinstrument.transacttime"] = (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->transact_time.get()) : canonical::absent());
            values[entry + ".payload.addscaledsimpleinstrument.securitytype"] = (static_cast<std::uint8_t>(message->security_type.get()) != 0x0FFU ? canonical::number(message->security_type.get()) : canonical::absent());
            values[entry + ".payload.addscaledsimpleinstrument.quantityscalingfactor"] = (static_cast<std::uint16_t>(message->quantity_scaling_factor.get()) != 0x0FFFFU ? canonical::number(message->quantity_scaling_factor.get()) : canonical::absent());
            values[entry + ".payload.addscaledsimpleinstrument.relatedinstrumentgrpcomp.relatedsecurityid"] = (static_cast<std::uint64_t>(message->related_instrument_grp_comp.related_security_id.get()) != 0x08000000000000000ULL ? canonical::number(message->related_instrument_grp_comp.related_security_id.get()) : canonical::absent());
        } else if (iterator.template_id == protocol::AuctionBbo::message_type) {
            values[entry + ".payload"] = "packet.message.payload.auctionbbo";
            [[maybe_unused]] const auto* message = protocol::AuctionBbo::parse(iterator.message);
            values[entry + ".payload.auctionbbo.transacttime"] = (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->transact_time.get()) : canonical::absent());
            values[entry + ".payload.auctionbbo.securityid"] = (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? canonical::number(message->security_id.get()) : canonical::absent());
            values[entry + ".payload.auctionbbo.bidpx"] = (static_cast<std::uint64_t>(message->bid_px.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->bid_px.integer(), -8) : canonical::absent());
            values[entry + ".payload.auctionbbo.offerpx"] = (static_cast<std::uint64_t>(message->offer_px.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->offer_px.integer(), -8) : canonical::absent());
            values[entry + ".payload.auctionbbo.bidsize"] = (static_cast<std::uint64_t>(message->bid_size.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->bid_size.integer(), -4) : canonical::absent());
            values[entry + ".payload.auctionbbo.offersize"] = (static_cast<std::uint64_t>(message->offer_size.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->offer_size.integer(), -4) : canonical::absent());
            values[entry + ".payload.auctionbbo.potentialsecuritytradingevent"] = (static_cast<std::uint8_t>(message->potential_security_trading_event.get()) != 0x0FFU ? canonical::number(message->potential_security_trading_event.get()) : canonical::absent());
            values[entry + ".payload.auctionbbo.bidordtype"] = (static_cast<std::uint8_t>(message->bid_ord_type.get()) != 0x0FFU ? canonical::number(message->bid_ord_type.get()) : canonical::absent());
            values[entry + ".payload.auctionbbo.offerordtype"] = (static_cast<std::uint8_t>(message->offer_ord_type.get()) != 0x0FFU ? canonical::number(message->offer_ord_type.get()) : canonical::absent());
        } else if (iterator.template_id == protocol::AuctionClearingPrice::message_type) {
            values[entry + ".payload"] = "packet.message.payload.auctionclearingprice";
            [[maybe_unused]] const auto* message = protocol::AuctionClearingPrice::parse(iterator.message);
            values[entry + ".payload.auctionclearingprice.transacttime"] = (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->transact_time.get()) : canonical::absent());
            values[entry + ".payload.auctionclearingprice.securityid"] = (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? canonical::number(message->security_id.get()) : canonical::absent());
            values[entry + ".payload.auctionclearingprice.lastpx"] = (static_cast<std::uint64_t>(message->last_px.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->last_px.integer(), -8) : canonical::absent());
            values[entry + ".payload.auctionclearingprice.lastqty"] = (static_cast<std::uint64_t>(message->last_qty.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->last_qty.integer(), -4) : canonical::absent());
            values[entry + ".payload.auctionclearingprice.imbalanceqty"] = (static_cast<std::uint64_t>(message->imbalance_qty.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->imbalance_qty.integer(), -4) : canonical::absent());
            values[entry + ".payload.auctionclearingprice.securitytradingstatus"] = (static_cast<std::uint8_t>(message->security_trading_status.get()) != 0x0FFU ? canonical::number(message->security_trading_status.get()) : canonical::absent());
            values[entry + ".payload.auctionclearingprice.potentialsecuritytradingevent"] = (static_cast<std::uint8_t>(message->potential_security_trading_event.get()) != 0x0FFU ? canonical::number(message->potential_security_trading_event.get()) : canonical::absent());
        } else if (iterator.template_id == protocol::CrossRequest::message_type) {
            values[entry + ".payload"] = "packet.message.payload.crossrequest";
            [[maybe_unused]] const auto* message = protocol::CrossRequest::parse(iterator.message);
            values[entry + ".payload.crossrequest.securityid"] = (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? canonical::number(message->security_id.get()) : canonical::absent());
            values[entry + ".payload.crossrequest.lastpx"] = (static_cast<std::uint64_t>(message->last_px.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->last_px.integer(), -8) : canonical::absent());
            values[entry + ".payload.crossrequest.lastqty"] = (static_cast<std::uint64_t>(message->last_qty.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->last_qty.integer(), -4) : canonical::absent());
            values[entry + ".payload.crossrequest.side"] = (static_cast<std::uint8_t>(message->side.get()) != 0x0FFU ? canonical::number(message->side.get()) : canonical::absent());
            values[entry + ".payload.crossrequest.crossrequesttype"] = (static_cast<std::uint8_t>(message->cross_request_type.get()) != 0x0FFU ? canonical::number(message->cross_request_type.get()) : canonical::absent());
            values[entry + ".payload.crossrequest.inputsource"] = (static_cast<std::uint8_t>(message->input_source.get()) != 0x0FFU ? canonical::number(message->input_source.get()) : canonical::absent());
            values[entry + ".payload.crossrequest.transacttime"] = (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->transact_time.get()) : canonical::absent());
        } else if (iterator.template_id == protocol::ExecutionSummary::message_type) {
            values[entry + ".payload"] = "packet.message.payload.executionsummary";
            [[maybe_unused]] const auto* message = protocol::ExecutionSummary::parse(iterator.message);
            values[entry + ".payload.executionsummary.securityid"] = (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? canonical::number(message->security_id.get()) : canonical::absent());
            values[entry + ".payload.executionsummary.requesttime"] = (static_cast<std::uint64_t>(message->request_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->request_time.get()) : canonical::absent());
            values[entry + ".payload.executionsummary.execid"] = (static_cast<std::uint64_t>(message->exec_id.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->exec_id.get()) : canonical::absent());
            values[entry + ".payload.executionsummary.lastqty"] = (static_cast<std::uint64_t>(message->last_qty.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->last_qty.integer(), -4) : canonical::absent());
            values[entry + ".payload.executionsummary.aggressorside"] = (static_cast<std::uint8_t>(message->aggressor_side.get()) != 0x0FFU ? canonical::number(message->aggressor_side.get()) : canonical::absent());
            values[entry + ".payload.executionsummary.tradecondition"] = (static_cast<std::uint16_t>(message->trade_condition.get()) != 0x0FFFFU ? canonical::number(message->trade_condition.get()) : canonical::absent());
            values[entry + ".payload.executionsummary.tradinghhiindicator"] = (static_cast<std::uint8_t>(message->trading_hhi_indicator.get()) != 0x0FFU ? canonical::number(message->trading_hhi_indicator.get()) : canonical::absent());
            values[entry + ".payload.executionsummary.lastpx"] = (static_cast<std::uint64_t>(message->last_px.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->last_px.integer(), -8) : canonical::absent());
            values[entry + ".payload.executionsummary.remainingorderdetailscomp.trdregtsprevtimepriority"] = (static_cast<std::uint64_t>(message->remaining_order_details_comp.trd_reg_ts_prev_time_priority.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->remaining_order_details_comp.trd_reg_ts_prev_time_priority.get()) : canonical::absent());
            values[entry + ".payload.executionsummary.remainingorderdetailscomp.displayqty"] = (static_cast<std::uint64_t>(message->remaining_order_details_comp.display_qty.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->remaining_order_details_comp.display_qty.integer(), -4) : canonical::absent());
            values[entry + ".payload.executionsummary.remainingorderdetailscomp.price"] = (static_cast<std::uint64_t>(message->remaining_order_details_comp.price.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->remaining_order_details_comp.price.integer(), -8) : canonical::absent());
            values[entry + ".payload.executionsummary.restinghiddenqty"] = (static_cast<std::uint64_t>(message->resting_hidden_qty.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->resting_hidden_qty.integer(), -4) : canonical::absent());
            values[entry + ".payload.executionsummary.restingcxlqty"] = (static_cast<std::uint64_t>(message->resting_cxl_qty.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->resting_cxl_qty.integer(), -4) : canonical::absent());
            values[entry + ".payload.executionsummary.aggressortime"] = (static_cast<std::uint64_t>(message->aggressor_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->aggressor_time.get()) : canonical::absent());
        } else if (iterator.template_id == protocol::FullOrderExecution::message_type) {
            values[entry + ".payload"] = "packet.message.payload.fullorderexecution";
            [[maybe_unused]] const auto* message = protocol::FullOrderExecution::parse(iterator.message);
            values[entry + ".payload.fullorderexecution.side"] = (static_cast<std::uint8_t>(message->side.get()) != 0x0FFU ? canonical::number(message->side.get()) : canonical::absent());
            values[entry + ".payload.fullorderexecution.ordtype"] = (static_cast<std::uint8_t>(message->ord_type.get()) != 0x0FFU ? canonical::number(message->ord_type.get()) : canonical::absent());
            values[entry + ".payload.fullorderexecution.algorithmictradeindicator"] = (static_cast<std::uint8_t>(message->algorithmic_trade_indicator.get()) != 0x0FFU ? canonical::number(message->algorithmic_trade_indicator.get()) : canonical::absent());
            values[entry + ".payload.fullorderexecution.hhiindicator"] = (static_cast<std::uint8_t>(message->hhi_indicator.get()) != 0x080U ? canonical::number(message->hhi_indicator.get()) : canonical::absent());
            values[entry + ".payload.fullorderexecution.trdmatchid"] = (static_cast<std::uint32_t>(message->trd_match_id.get()) != 0x0FFFFFFFFU ? canonical::number(message->trd_match_id.get()) : canonical::absent());
            values[entry + ".payload.fullorderexecution.price"] = (static_cast<std::uint64_t>(message->price.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->price.integer(), -8) : canonical::absent());
            values[entry + ".payload.fullorderexecution.trdregtstimepriority"] = (static_cast<std::uint64_t>(message->trd_reg_ts_time_priority.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->trd_reg_ts_time_priority.get()) : canonical::absent());
            values[entry + ".payload.fullorderexecution.securityid"] = (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? canonical::number(message->security_id.get()) : canonical::absent());
            values[entry + ".payload.fullorderexecution.lastqty"] = (static_cast<std::uint64_t>(message->last_qty.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->last_qty.integer(), -4) : canonical::absent());
            values[entry + ".payload.fullorderexecution.lastpx"] = (static_cast<std::uint64_t>(message->last_px.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->last_px.integer(), -8) : canonical::absent());
        } else if (iterator.template_id == protocol::Heartbeat::message_type) {
            values[entry + ".payload"] = "packet.message.payload.heartbeat";
            [[maybe_unused]] const auto* message = protocol::Heartbeat::parse(iterator.message);
            values[entry + ".payload.heartbeat.lastmsgseqnumprocessed"] = (static_cast<std::uint32_t>(message->last_msg_seq_num_processed.get()) != 0x0FFFFFFFFU ? canonical::number(message->last_msg_seq_num_processed.get()) : canonical::absent());
        } else if (iterator.template_id == protocol::InstrumentStateChange::message_type) {
            values[entry + ".payload"] = "packet.message.payload.instrumentstatechange";
            [[maybe_unused]] const auto* message = protocol::InstrumentStateChange::parse(iterator.message);
            values[entry + ".payload.instrumentstatechange.securityid"] = (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? canonical::number(message->security_id.get()) : canonical::absent());
            values[entry + ".payload.instrumentstatechange.securitystatus"] = (static_cast<std::uint8_t>(message->security_status.get()) != 0x0FFU ? canonical::number(message->security_status.get()) : canonical::absent());
            values[entry + ".payload.instrumentstatechange.securitytradingstatus"] = (static_cast<std::uint8_t>(message->security_trading_status.get()) != 0x0FFU ? canonical::number(message->security_trading_status.get()) : canonical::absent());
            values[entry + ".payload.instrumentstatechange.marketcondition"] = (static_cast<std::uint8_t>(message->market_condition.get()) != 0x0FFU ? canonical::number(message->market_condition.get()) : canonical::absent());
            values[entry + ".payload.instrumentstatechange.fastmarketindicator"] = (static_cast<std::uint8_t>(message->fast_market_indicator.get()) != 0x0FFU ? canonical::number(message->fast_market_indicator.get()) : canonical::absent());
            values[entry + ".payload.instrumentstatechange.securitytradingevent"] = (static_cast<std::uint8_t>(message->security_trading_event.get()) != 0x0FFU ? canonical::number(message->security_trading_event.get()) : canonical::absent());
            values[entry + ".payload.instrumentstatechange.soldoutindicator"] = (static_cast<std::uint8_t>(message->sold_out_indicator.get()) != 0x0FFU ? canonical::number(message->sold_out_indicator.get()) : canonical::absent());
            values[entry + ".payload.instrumentstatechange.highpx"] = (static_cast<std::uint64_t>(message->high_px.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->high_px.integer(), -8) : canonical::absent());
            values[entry + ".payload.instrumentstatechange.lowpx"] = (static_cast<std::uint64_t>(message->low_px.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->low_px.integer(), -8) : canonical::absent());
            values[entry + ".payload.instrumentstatechange.transacttime"] = (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->transact_time.get()) : canonical::absent());
            values[entry + ".payload.instrumentstatechange.tessecuritystatus"] = (static_cast<std::uint8_t>(message->tes_security_status.get()) != 0x0FFU ? canonical::number(message->tes_security_status.get()) : canonical::absent());
        } else if (iterator.template_id == protocol::InstrumentSummary::message_type) {
            values[entry + ".payload"] = "packet.message.payload.instrumentsummary";
            [[maybe_unused]] const auto* message = protocol::InstrumentSummary::parse(iterator.message);
            values[entry + ".payload.instrumentsummary.securityid"] = (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? canonical::number(message->security_id.get()) : canonical::absent());
            values[entry + ".payload.instrumentsummary.lastupdatetime"] = (static_cast<std::uint64_t>(message->last_update_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->last_update_time.get()) : canonical::absent());
            values[entry + ".payload.instrumentsummary.trdregtsexecutiontime"] = (static_cast<std::uint64_t>(message->trd_reg_ts_execution_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->trd_reg_ts_execution_time.get()) : canonical::absent());
            values[entry + ".payload.instrumentsummary.totnoorders"] = (static_cast<std::uint16_t>(message->tot_no_orders.get()) != 0x0FFFFU ? canonical::number(message->tot_no_orders.get()) : canonical::absent());
            values[entry + ".payload.instrumentsummary.securitystatus"] = (static_cast<std::uint8_t>(message->security_status.get()) != 0x0FFU ? canonical::number(message->security_status.get()) : canonical::absent());
            values[entry + ".payload.instrumentsummary.securitytradingstatus"] = (static_cast<std::uint8_t>(message->security_trading_status.get()) != 0x0FFU ? canonical::number(message->security_trading_status.get()) : canonical::absent());
            values[entry + ".payload.instrumentsummary.marketcondition"] = (static_cast<std::uint8_t>(message->market_condition.get()) != 0x0FFU ? canonical::number(message->market_condition.get()) : canonical::absent());
            values[entry + ".payload.instrumentsummary.fastmarketindicator"] = (static_cast<std::uint8_t>(message->fast_market_indicator.get()) != 0x0FFU ? canonical::number(message->fast_market_indicator.get()) : canonical::absent());
            values[entry + ".payload.instrumentsummary.securitytradingevent"] = (static_cast<std::uint8_t>(message->security_trading_event.get()) != 0x0FFU ? canonical::number(message->security_trading_event.get()) : canonical::absent());
            values[entry + ".payload.instrumentsummary.soldoutindicator"] = (static_cast<std::uint8_t>(message->sold_out_indicator.get()) != 0x0FFU ? canonical::number(message->sold_out_indicator.get()) : canonical::absent());
            values[entry + ".payload.instrumentsummary.highpx"] = (static_cast<std::uint64_t>(message->high_px.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->high_px.integer(), -8) : canonical::absent());
            values[entry + ".payload.instrumentsummary.lowpx"] = (static_cast<std::uint64_t>(message->low_px.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->low_px.integer(), -8) : canonical::absent());
            values[entry + ".payload.instrumentsummary.productcomplex"] = (static_cast<std::uint8_t>(message->product_complex.get()) != 0x0FFU ? canonical::number(message->product_complex.get()) : canonical::absent());
            values[entry + ".payload.instrumentsummary.nomdentries"] = (static_cast<std::uint8_t>(message->no_md_entries.get()) != 0x0FFU ? canonical::number(message->no_md_entries.get()) : canonical::absent());
            values[entry + ".payload.instrumentsummary.tessecuritystatus"] = (static_cast<std::uint8_t>(message->tes_security_status.get()) != 0x0FFU ? canonical::number(message->tes_security_status.get()) : canonical::absent());
        } else if (iterator.template_id == protocol::MassInstrumentStateChange::message_type) {
            values[entry + ".payload"] = "packet.message.payload.massinstrumentstatechange";
            [[maybe_unused]] const auto* message = protocol::MassInstrumentStateChange::parse(iterator.message);
            values[entry + ".payload.massinstrumentstatechange.instrumentscopeproductcomplex"] = (static_cast<std::uint8_t>(message->instrument_scope_product_complex.get()) != 0x0FFU ? canonical::number(message->instrument_scope_product_complex.get()) : canonical::absent());
            values[entry + ".payload.massinstrumentstatechange.securitymassstatus"] = (static_cast<std::uint8_t>(message->security_mass_status.get()) != 0x0FFU ? canonical::number(message->security_mass_status.get()) : canonical::absent());
            values[entry + ".payload.massinstrumentstatechange.securitymasstradingstatus"] = (static_cast<std::uint8_t>(message->security_mass_trading_status.get()) != 0x0FFU ? canonical::number(message->security_mass_trading_status.get()) : canonical::absent());
            values[entry + ".payload.massinstrumentstatechange.massmarketcondition"] = (static_cast<std::uint8_t>(message->mass_market_condition.get()) != 0x0FFU ? canonical::number(message->mass_market_condition.get()) : canonical::absent());
            values[entry + ".payload.massinstrumentstatechange.fastmarketindicator"] = (static_cast<std::uint8_t>(message->fast_market_indicator.get()) != 0x0FFU ? canonical::number(message->fast_market_indicator.get()) : canonical::absent());
            values[entry + ".payload.massinstrumentstatechange.securitymasstradingevent"] = (static_cast<std::uint8_t>(message->security_mass_trading_event.get()) != 0x0FFU ? canonical::number(message->security_mass_trading_event.get()) : canonical::absent());
            values[entry + ".payload.massinstrumentstatechange.masssoldoutindicator"] = (static_cast<std::uint8_t>(message->mass_sold_out_indicator.get()) != 0x0FFU ? canonical::number(message->mass_sold_out_indicator.get()) : canonical::absent());
            values[entry + ".payload.massinstrumentstatechange.tessecuritymassstatus"] = (static_cast<std::uint8_t>(message->tes_security_mass_status.get()) != 0x0FFU ? canonical::number(message->tes_security_mass_status.get()) : canonical::absent());
            values[entry + ".payload.massinstrumentstatechange.transacttime"] = (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->transact_time.get()) : canonical::absent());
            values[entry + ".payload.massinstrumentstatechange.lastfragment"] = (static_cast<std::uint8_t>(message->last_fragment.get()) != 0x0FFU ? canonical::number(message->last_fragment.get()) : canonical::absent());
            values[entry + ".payload.massinstrumentstatechange.norelatedsym"] = (static_cast<std::uint8_t>(message->no_related_sym.get()) != 0x0FFU ? canonical::number(message->no_related_sym.get()) : canonical::absent());
        } else if (iterator.template_id == protocol::OrderAdd::message_type) {
            values[entry + ".payload"] = "packet.message.payload.orderadd";
            [[maybe_unused]] const auto* message = protocol::OrderAdd::parse(iterator.message);
            values[entry + ".payload.orderadd.requesttime"] = (static_cast<std::uint64_t>(message->request_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->request_time.get()) : canonical::absent());
            values[entry + ".payload.orderadd.securityid"] = (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? canonical::number(message->security_id.get()) : canonical::absent());
            values[entry + ".payload.orderadd.orderdetailscomp.trdregtstimepriority"] = (static_cast<std::uint64_t>(message->order_details_comp.trd_reg_ts_time_priority.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->order_details_comp.trd_reg_ts_time_priority.get()) : canonical::absent());
            values[entry + ".payload.orderadd.orderdetailscomp.displayqty"] = (static_cast<std::uint64_t>(message->order_details_comp.display_qty.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->order_details_comp.display_qty.integer(), -4) : canonical::absent());
            values[entry + ".payload.orderadd.orderdetailscomp.side"] = (static_cast<std::uint8_t>(message->order_details_comp.side.get()) != 0x0FFU ? canonical::number(message->order_details_comp.side.get()) : canonical::absent());
            values[entry + ".payload.orderadd.orderdetailscomp.ordtype"] = (static_cast<std::uint8_t>(message->order_details_comp.ord_type.get()) != 0x0FFU ? canonical::number(message->order_details_comp.ord_type.get()) : canonical::absent());
            values[entry + ".payload.orderadd.orderdetailscomp.hhiindicator"] = (static_cast<std::uint8_t>(message->order_details_comp.hhi_indicator.get()) != 0x080U ? canonical::number(message->order_details_comp.hhi_indicator.get()) : canonical::absent());
            values[entry + ".payload.orderadd.orderdetailscomp.price"] = (static_cast<std::uint64_t>(message->order_details_comp.price.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->order_details_comp.price.integer(), -8) : canonical::absent());
        } else if (iterator.template_id == protocol::OrderDelete::message_type) {
            values[entry + ".payload"] = "packet.message.payload.orderdelete";
            [[maybe_unused]] const auto* message = protocol::OrderDelete::parse(iterator.message);
            values[entry + ".payload.orderdelete.requesttime"] = (static_cast<std::uint64_t>(message->request_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->request_time.get()) : canonical::absent());
            values[entry + ".payload.orderdelete.transacttime"] = (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->transact_time.get()) : canonical::absent());
            values[entry + ".payload.orderdelete.securityid"] = (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? canonical::number(message->security_id.get()) : canonical::absent());
            values[entry + ".payload.orderdelete.orderdetailscomp.trdregtstimepriority"] = (static_cast<std::uint64_t>(message->order_details_comp.trd_reg_ts_time_priority.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->order_details_comp.trd_reg_ts_time_priority.get()) : canonical::absent());
            values[entry + ".payload.orderdelete.orderdetailscomp.displayqty"] = (static_cast<std::uint64_t>(message->order_details_comp.display_qty.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->order_details_comp.display_qty.integer(), -4) : canonical::absent());
            values[entry + ".payload.orderdelete.orderdetailscomp.side"] = (static_cast<std::uint8_t>(message->order_details_comp.side.get()) != 0x0FFU ? canonical::number(message->order_details_comp.side.get()) : canonical::absent());
            values[entry + ".payload.orderdelete.orderdetailscomp.ordtype"] = (static_cast<std::uint8_t>(message->order_details_comp.ord_type.get()) != 0x0FFU ? canonical::number(message->order_details_comp.ord_type.get()) : canonical::absent());
            values[entry + ".payload.orderdelete.orderdetailscomp.hhiindicator"] = (static_cast<std::uint8_t>(message->order_details_comp.hhi_indicator.get()) != 0x080U ? canonical::number(message->order_details_comp.hhi_indicator.get()) : canonical::absent());
            values[entry + ".payload.orderdelete.orderdetailscomp.price"] = (static_cast<std::uint64_t>(message->order_details_comp.price.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->order_details_comp.price.integer(), -8) : canonical::absent());
        } else if (iterator.template_id == protocol::OrderMassDelete::message_type) {
            values[entry + ".payload"] = "packet.message.payload.ordermassdelete";
            [[maybe_unused]] const auto* message = protocol::OrderMassDelete::parse(iterator.message);
            values[entry + ".payload.ordermassdelete.securityid"] = (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? canonical::number(message->security_id.get()) : canonical::absent());
            values[entry + ".payload.ordermassdelete.transacttime"] = (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->transact_time.get()) : canonical::absent());
        } else if (iterator.template_id == protocol::OrderModify::message_type) {
            values[entry + ".payload"] = "packet.message.payload.ordermodify";
            [[maybe_unused]] const auto* message = protocol::OrderModify::parse(iterator.message);
            values[entry + ".payload.ordermodify.requesttime"] = (static_cast<std::uint64_t>(message->request_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->request_time.get()) : canonical::absent());
            values[entry + ".payload.ordermodify.trdregtsprevtimepriority"] = (static_cast<std::uint64_t>(message->trd_reg_ts_prev_time_priority.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->trd_reg_ts_prev_time_priority.get()) : canonical::absent());
            values[entry + ".payload.ordermodify.prevprice"] = (static_cast<std::uint64_t>(message->prev_price.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->prev_price.integer(), -8) : canonical::absent());
            values[entry + ".payload.ordermodify.prevdisplayqty"] = (static_cast<std::uint64_t>(message->prev_display_qty.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->prev_display_qty.integer(), -4) : canonical::absent());
            values[entry + ".payload.ordermodify.securityid"] = (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? canonical::number(message->security_id.get()) : canonical::absent());
            values[entry + ".payload.ordermodify.orderdetailscomp.trdregtstimepriority"] = (static_cast<std::uint64_t>(message->order_details_comp.trd_reg_ts_time_priority.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->order_details_comp.trd_reg_ts_time_priority.get()) : canonical::absent());
            values[entry + ".payload.ordermodify.orderdetailscomp.displayqty"] = (static_cast<std::uint64_t>(message->order_details_comp.display_qty.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->order_details_comp.display_qty.integer(), -4) : canonical::absent());
            values[entry + ".payload.ordermodify.orderdetailscomp.side"] = (static_cast<std::uint8_t>(message->order_details_comp.side.get()) != 0x0FFU ? canonical::number(message->order_details_comp.side.get()) : canonical::absent());
            values[entry + ".payload.ordermodify.orderdetailscomp.ordtype"] = (static_cast<std::uint8_t>(message->order_details_comp.ord_type.get()) != 0x0FFU ? canonical::number(message->order_details_comp.ord_type.get()) : canonical::absent());
            values[entry + ".payload.ordermodify.orderdetailscomp.hhiindicator"] = (static_cast<std::uint8_t>(message->order_details_comp.hhi_indicator.get()) != 0x080U ? canonical::number(message->order_details_comp.hhi_indicator.get()) : canonical::absent());
            values[entry + ".payload.ordermodify.orderdetailscomp.price"] = (static_cast<std::uint64_t>(message->order_details_comp.price.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->order_details_comp.price.integer(), -8) : canonical::absent());
            values[entry + ".payload.ordermodify.prevpricehhiindicator"] = (static_cast<std::uint8_t>(message->prev_price_hhi_indicator.get()) != 0x080U ? canonical::number(message->prev_price_hhi_indicator.get()) : canonical::absent());
        } else if (iterator.template_id == protocol::OrderModifySamePrio::message_type) {
            values[entry + ".payload"] = "packet.message.payload.ordermodifysameprio";
            [[maybe_unused]] const auto* message = protocol::OrderModifySamePrio::parse(iterator.message);
            values[entry + ".payload.ordermodifysameprio.requesttime"] = (static_cast<std::uint64_t>(message->request_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->request_time.get()) : canonical::absent());
            values[entry + ".payload.ordermodifysameprio.transacttime"] = (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->transact_time.get()) : canonical::absent());
            values[entry + ".payload.ordermodifysameprio.prevdisplayqty"] = (static_cast<std::uint64_t>(message->prev_display_qty.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->prev_display_qty.integer(), -4) : canonical::absent());
            values[entry + ".payload.ordermodifysameprio.securityid"] = (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? canonical::number(message->security_id.get()) : canonical::absent());
            values[entry + ".payload.ordermodifysameprio.orderdetailscomp.trdregtstimepriority"] = (static_cast<std::uint64_t>(message->order_details_comp.trd_reg_ts_time_priority.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->order_details_comp.trd_reg_ts_time_priority.get()) : canonical::absent());
            values[entry + ".payload.ordermodifysameprio.orderdetailscomp.displayqty"] = (static_cast<std::uint64_t>(message->order_details_comp.display_qty.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->order_details_comp.display_qty.integer(), -4) : canonical::absent());
            values[entry + ".payload.ordermodifysameprio.orderdetailscomp.side"] = (static_cast<std::uint8_t>(message->order_details_comp.side.get()) != 0x0FFU ? canonical::number(message->order_details_comp.side.get()) : canonical::absent());
            values[entry + ".payload.ordermodifysameprio.orderdetailscomp.ordtype"] = (static_cast<std::uint8_t>(message->order_details_comp.ord_type.get()) != 0x0FFU ? canonical::number(message->order_details_comp.ord_type.get()) : canonical::absent());
            values[entry + ".payload.ordermodifysameprio.orderdetailscomp.hhiindicator"] = (static_cast<std::uint8_t>(message->order_details_comp.hhi_indicator.get()) != 0x080U ? canonical::number(message->order_details_comp.hhi_indicator.get()) : canonical::absent());
            values[entry + ".payload.ordermodifysameprio.orderdetailscomp.price"] = (static_cast<std::uint64_t>(message->order_details_comp.price.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->order_details_comp.price.integer(), -8) : canonical::absent());
        } else if (iterator.template_id == protocol::PartialOrderExecution::message_type) {
            values[entry + ".payload"] = "packet.message.payload.partialorderexecution";
            [[maybe_unused]] const auto* message = protocol::PartialOrderExecution::parse(iterator.message);
            values[entry + ".payload.partialorderexecution.side"] = (static_cast<std::uint8_t>(message->side.get()) != 0x0FFU ? canonical::number(message->side.get()) : canonical::absent());
            values[entry + ".payload.partialorderexecution.ordtype"] = (static_cast<std::uint8_t>(message->ord_type.get()) != 0x0FFU ? canonical::number(message->ord_type.get()) : canonical::absent());
            values[entry + ".payload.partialorderexecution.algorithmictradeindicator"] = (static_cast<std::uint8_t>(message->algorithmic_trade_indicator.get()) != 0x0FFU ? canonical::number(message->algorithmic_trade_indicator.get()) : canonical::absent());
            values[entry + ".payload.partialorderexecution.hhiindicator"] = (static_cast<std::uint8_t>(message->hhi_indicator.get()) != 0x080U ? canonical::number(message->hhi_indicator.get()) : canonical::absent());
            values[entry + ".payload.partialorderexecution.trdmatchid"] = (static_cast<std::uint32_t>(message->trd_match_id.get()) != 0x0FFFFFFFFU ? canonical::number(message->trd_match_id.get()) : canonical::absent());
            values[entry + ".payload.partialorderexecution.price"] = (static_cast<std::uint64_t>(message->price.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->price.integer(), -8) : canonical::absent());
            values[entry + ".payload.partialorderexecution.trdregtstimepriority"] = (static_cast<std::uint64_t>(message->trd_reg_ts_time_priority.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->trd_reg_ts_time_priority.get()) : canonical::absent());
            values[entry + ".payload.partialorderexecution.securityid"] = (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? canonical::number(message->security_id.get()) : canonical::absent());
            values[entry + ".payload.partialorderexecution.lastqty"] = (static_cast<std::uint64_t>(message->last_qty.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->last_qty.integer(), -4) : canonical::absent());
            values[entry + ".payload.partialorderexecution.lastpx"] = (static_cast<std::uint64_t>(message->last_px.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->last_px.integer(), -8) : canonical::absent());
        } else if (iterator.template_id == protocol::ProductStateChange::message_type) {
            values[entry + ".payload"] = "packet.message.payload.productstatechange";
            [[maybe_unused]] const auto* message = protocol::ProductStateChange::parse(iterator.message);
            values[entry + ".payload.productstatechange.tradingsessionid"] = (static_cast<std::uint8_t>(message->trading_session_id.get()) != 0x0FFU ? canonical::number(message->trading_session_id.get()) : canonical::absent());
            values[entry + ".payload.productstatechange.tradingsessionsubid"] = (static_cast<std::uint8_t>(message->trading_session_sub_id.get()) != 0x0FFU ? canonical::number(message->trading_session_sub_id.get()) : canonical::absent());
            values[entry + ".payload.productstatechange.tradsesstatus"] = (static_cast<std::uint8_t>(message->trad_ses_status.get()) != 0x0FFU ? canonical::number(message->trad_ses_status.get()) : canonical::absent());
            values[entry + ".payload.productstatechange.marketcondition"] = (static_cast<std::uint8_t>(message->market_condition.get()) != 0x0FFU ? canonical::number(message->market_condition.get()) : canonical::absent());
            values[entry + ".payload.productstatechange.fastmarketindicator"] = (static_cast<std::uint8_t>(message->fast_market_indicator.get()) != 0x0FFU ? canonical::number(message->fast_market_indicator.get()) : canonical::absent());
            values[entry + ".payload.productstatechange.testradsesstatus"] = (static_cast<std::uint8_t>(message->tes_trad_ses_status.get()) != 0x0FFU ? canonical::number(message->tes_trad_ses_status.get()) : canonical::absent());
            values[entry + ".payload.productstatechange.transacttime"] = (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->transact_time.get()) : canonical::absent());
        } else if (iterator.template_id == protocol::ProductSummary::message_type) {
            values[entry + ".payload"] = "packet.message.payload.productsummary";
            [[maybe_unused]] const auto* message = protocol::ProductSummary::parse(iterator.message);
            values[entry + ".payload.productsummary.lastmsgseqnumprocessed"] = (static_cast<std::uint32_t>(message->last_msg_seq_num_processed.get()) != 0x0FFFFFFFFU ? canonical::number(message->last_msg_seq_num_processed.get()) : canonical::absent());
            values[entry + ".payload.productsummary.tradingsessionid"] = (static_cast<std::uint8_t>(message->trading_session_id.get()) != 0x0FFU ? canonical::number(message->trading_session_id.get()) : canonical::absent());
            values[entry + ".payload.productsummary.tradingsessionsubid"] = (static_cast<std::uint8_t>(message->trading_session_sub_id.get()) != 0x0FFU ? canonical::number(message->trading_session_sub_id.get()) : canonical::absent());
            values[entry + ".payload.productsummary.tradsesstatus"] = (static_cast<std::uint8_t>(message->trad_ses_status.get()) != 0x0FFU ? canonical::number(message->trad_ses_status.get()) : canonical::absent());
            values[entry + ".payload.productsummary.marketcondition"] = (static_cast<std::uint8_t>(message->market_condition.get()) != 0x0FFU ? canonical::number(message->market_condition.get()) : canonical::absent());
            values[entry + ".payload.productsummary.fastmarketindicator"] = (static_cast<std::uint8_t>(message->fast_market_indicator.get()) != 0x0FFU ? canonical::number(message->fast_market_indicator.get()) : canonical::absent());
            values[entry + ".payload.productsummary.testradsesstatus"] = (static_cast<std::uint8_t>(message->tes_trad_ses_status.get()) != 0x0FFU ? canonical::number(message->tes_trad_ses_status.get()) : canonical::absent());
        } else if (iterator.template_id == protocol::QuoteRequest::message_type) {
            values[entry + ".payload"] = "packet.message.payload.quoterequest";
            [[maybe_unused]] const auto* message = protocol::QuoteRequest::parse(iterator.message);
            values[entry + ".payload.quoterequest.securityid"] = (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? canonical::number(message->security_id.get()) : canonical::absent());
            values[entry + ".payload.quoterequest.lastqty"] = (static_cast<std::uint64_t>(message->last_qty.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->last_qty.integer(), -4) : canonical::absent());
            values[entry + ".payload.quoterequest.side"] = (static_cast<std::uint8_t>(message->side.get()) != 0x0FFU ? canonical::number(message->side.get()) : canonical::absent());
            values[entry + ".payload.quoterequest.transacttime"] = (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->transact_time.get()) : canonical::absent());
        } else if (iterator.template_id == protocol::SnapshotOrder::message_type) {
            values[entry + ".payload"] = "packet.message.payload.snapshotorder";
            [[maybe_unused]] const auto* message = protocol::SnapshotOrder::parse(iterator.message);
            values[entry + ".payload.snapshotorder.orderdetailscomp.trdregtstimepriority"] = (static_cast<std::uint64_t>(message->order_details_comp.trd_reg_ts_time_priority.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->order_details_comp.trd_reg_ts_time_priority.get()) : canonical::absent());
            values[entry + ".payload.snapshotorder.orderdetailscomp.displayqty"] = (static_cast<std::uint64_t>(message->order_details_comp.display_qty.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->order_details_comp.display_qty.integer(), -4) : canonical::absent());
            values[entry + ".payload.snapshotorder.orderdetailscomp.side"] = (static_cast<std::uint8_t>(message->order_details_comp.side.get()) != 0x0FFU ? canonical::number(message->order_details_comp.side.get()) : canonical::absent());
            values[entry + ".payload.snapshotorder.orderdetailscomp.ordtype"] = (static_cast<std::uint8_t>(message->order_details_comp.ord_type.get()) != 0x0FFU ? canonical::number(message->order_details_comp.ord_type.get()) : canonical::absent());
            values[entry + ".payload.snapshotorder.orderdetailscomp.hhiindicator"] = (static_cast<std::uint8_t>(message->order_details_comp.hhi_indicator.get()) != 0x080U ? canonical::number(message->order_details_comp.hhi_indicator.get()) : canonical::absent());
            values[entry + ".payload.snapshotorder.orderdetailscomp.price"] = (static_cast<std::uint64_t>(message->order_details_comp.price.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->order_details_comp.price.integer(), -8) : canonical::absent());
        } else if (iterator.template_id == protocol::TesTradeReport::message_type) {
            values[entry + ".payload"] = "packet.message.payload.testradereport";
            [[maybe_unused]] const auto* message = protocol::TesTradeReport::parse(iterator.message);
            values[entry + ".payload.testradereport.securityid"] = (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? canonical::number(message->security_id.get()) : canonical::absent());
            values[entry + ".payload.testradereport.transacttime"] = (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->transact_time.get()) : canonical::absent());
            values[entry + ".payload.testradereport.lastqty"] = (static_cast<std::uint64_t>(message->last_qty.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->last_qty.integer(), -4) : canonical::absent());
            values[entry + ".payload.testradereport.lastpx"] = (static_cast<std::uint64_t>(message->last_px.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->last_px.integer(), -8) : canonical::absent());
            values[entry + ".payload.testradereport.trdmatchid"] = (static_cast<std::uint32_t>(message->trd_match_id.get()) != 0x0FFFFFFFFU ? canonical::number(message->trd_match_id.get()) : canonical::absent());
            values[entry + ".payload.testradereport.trdtype"] = (static_cast<std::uint16_t>(message->trd_type.get()) != 0x0FFFFU ? canonical::number(message->trd_type.get()) : canonical::absent());
            values[entry + ".payload.testradereport.tradecondition"] = (static_cast<std::uint16_t>(message->trade_condition.get()) != 0x0FFFFU ? canonical::number(message->trade_condition.get()) : canonical::absent());
            values[entry + ".payload.testradereport.multilegreportingtype"] = (static_cast<std::uint8_t>(message->multi_leg_reporting_type.get()) != 0x0FFU ? canonical::number(message->multi_leg_reporting_type.get()) : canonical::absent());
            values[entry + ".payload.testradereport.multilegpricemodel"] = (static_cast<std::uint8_t>(message->multi_leg_price_model.get()) != 0x0FFU ? canonical::number(message->multi_leg_price_model.get()) : canonical::absent());
            values[entry + ".payload.testradereport.nondisclosedtradevolume"] = (static_cast<std::uint64_t>(message->non_disclosed_trade_volume.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->non_disclosed_trade_volume.integer(), -4) : canonical::absent());
            values[entry + ".payload.testradereport.transbkdtime"] = (static_cast<std::uint64_t>(message->trans_bkd_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->trans_bkd_time.get()) : canonical::absent());
            values[entry + ".payload.testradereport.numberofbuysides"] = (static_cast<std::uint16_t>(message->number_of_buy_sides.get()) != 0x0FFFFU ? canonical::number(message->number_of_buy_sides.get()) : canonical::absent());
            values[entry + ".payload.testradereport.numberofsellsides"] = (static_cast<std::uint16_t>(message->number_of_sell_sides.get()) != 0x0FFFFU ? canonical::number(message->number_of_sell_sides.get()) : canonical::absent());
        } else if (iterator.template_id == protocol::TopOfBook::message_type) {
            values[entry + ".payload"] = "packet.message.payload.topofbook";
            [[maybe_unused]] const auto* message = protocol::TopOfBook::parse(iterator.message);
            values[entry + ".payload.topofbook.transacttime"] = (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->transact_time.get()) : canonical::absent());
            values[entry + ".payload.topofbook.securityid"] = (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? canonical::number(message->security_id.get()) : canonical::absent());
            values[entry + ".payload.topofbook.bidpx"] = (static_cast<std::uint64_t>(message->bid_px.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->bid_px.integer(), -8) : canonical::absent());
            values[entry + ".payload.topofbook.offerpx"] = (static_cast<std::uint64_t>(message->offer_px.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->offer_px.integer(), -8) : canonical::absent());
            values[entry + ".payload.topofbook.bidsize"] = (static_cast<std::uint64_t>(message->bid_size.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->bid_size.integer(), -4) : canonical::absent());
            values[entry + ".payload.topofbook.offersize"] = (static_cast<std::uint64_t>(message->offer_size.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->offer_size.integer(), -4) : canonical::absent());
            values[entry + ".payload.topofbook.numberofbuyorders"] = (static_cast<std::uint16_t>(message->number_of_buy_orders.get()) != 0x0FFFFU ? canonical::number(message->number_of_buy_orders.get()) : canonical::absent());
            values[entry + ".payload.topofbook.numberofsellorders"] = (static_cast<std::uint16_t>(message->number_of_sell_orders.get()) != 0x0FFFFU ? canonical::number(message->number_of_sell_orders.get()) : canonical::absent());
        } else if (iterator.template_id == protocol::TradeReport::message_type) {
            values[entry + ".payload"] = "packet.message.payload.tradereport";
            [[maybe_unused]] const auto* message = protocol::TradeReport::parse(iterator.message);
            values[entry + ".payload.tradereport.securityid"] = (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? canonical::number(message->security_id.get()) : canonical::absent());
            values[entry + ".payload.tradereport.transacttime"] = (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->transact_time.get()) : canonical::absent());
            values[entry + ".payload.tradereport.lastqty"] = (static_cast<std::uint64_t>(message->last_qty.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->last_qty.integer(), -4) : canonical::absent());
            values[entry + ".payload.tradereport.lastpx"] = (static_cast<std::uint64_t>(message->last_px.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->last_px.integer(), -8) : canonical::absent());
            values[entry + ".payload.tradereport.trdmatchid"] = (static_cast<std::uint32_t>(message->trd_match_id.get()) != 0x0FFFFFFFFU ? canonical::number(message->trd_match_id.get()) : canonical::absent());
            values[entry + ".payload.tradereport.matchtype"] = (static_cast<std::uint8_t>(message->match_type.get()) != 0x0FFU ? canonical::number(message->match_type.get()) : canonical::absent());
            values[entry + ".payload.tradereport.matchsubtype"] = (static_cast<std::uint8_t>(message->match_sub_type.get()) != 0x0FFU ? canonical::number(message->match_sub_type.get()) : canonical::absent());
            values[entry + ".payload.tradereport.algorithmictradeindicator"] = (static_cast<std::uint8_t>(message->algorithmic_trade_indicator.get()) != 0x0FFU ? canonical::number(message->algorithmic_trade_indicator.get()) : canonical::absent());
            values[entry + ".payload.tradereport.tradecondition"] = (static_cast<std::uint16_t>(message->trade_condition.get()) != 0x0FFFFU ? canonical::number(message->trade_condition.get()) : canonical::absent());
        } else if (iterator.template_id == protocol::TradeReversal::message_type) {
            values[entry + ".payload"] = "packet.message.payload.tradereversal";
            [[maybe_unused]] const auto* message = protocol::TradeReversal::parse(iterator.message);
            values[entry + ".payload.tradereversal.securityid"] = (static_cast<std::uint64_t>(message->security_id.get()) != 0x08000000000000000ULL ? canonical::number(message->security_id.get()) : canonical::absent());
            values[entry + ".payload.tradereversal.transacttime"] = (static_cast<std::uint64_t>(message->transact_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->transact_time.get()) : canonical::absent());
            values[entry + ".payload.tradereversal.lastqty"] = (static_cast<std::uint64_t>(message->last_qty.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->last_qty.integer(), -4) : canonical::absent());
            values[entry + ".payload.tradereversal.lastpx"] = (static_cast<std::uint64_t>(message->last_px.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->last_px.integer(), -8) : canonical::absent());
            values[entry + ".payload.tradereversal.trdregtsexecutiontime"] = (static_cast<std::uint64_t>(message->trd_reg_ts_execution_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->trd_reg_ts_execution_time.get()) : canonical::absent());
            values[entry + ".payload.tradereversal.trdmatchid"] = (static_cast<std::uint32_t>(message->trd_match_id.get()) != 0x0FFFFFFFFU ? canonical::number(message->trd_match_id.get()) : canonical::absent());
            values[entry + ".payload.tradereversal.tradecondition"] = (static_cast<std::uint16_t>(message->trade_condition.get()) != 0x0FFFFU ? canonical::number(message->trade_condition.get()) : canonical::absent());
            values[entry + ".payload.tradereversal.mdorigintype"] = (static_cast<std::uint8_t>(message->md_origin_type.get()) != 0x0FFU ? canonical::number(message->md_origin_type.get()) : canonical::absent());
            values[entry + ".payload.tradereversal.nomdentries"] = (static_cast<std::uint8_t>(message->no_md_entries.get()) != 0x0FFU ? canonical::number(message->no_md_entries.get()) : canonical::absent());
        }
    }

    return values;
}

// Read each datagram of a sample with Modern and hold it to the model's values
int check(const char* name, const char* capture, const char* expected) {
    const char* packets = std::getenv("OMI_PACKETS_DIR");

    if (packets == nullptr) {
        std::printf("FAIL: OMI_PACKETS_DIR is not set\n");
        return 1;
    }

    const auto model = canonical::load(canonical::root() + "/" + expected);
    std::vector<std::pair<std::string, std::int64_t>> sources;
    sources.emplace_back(std::string{packets} + "/" + capture, 0);

    packet::PcapIterator captures(sources);
    std::size_t datagram = 0;
    int differences = 0;

    while (captures.advance()) {
        const packet::Frame frame(captures.data(), captures.length());

        if (!frame.valid() || !frame.is_udp()) { continue; }

        if (datagram >= model.size()) {
            std::printf("FAIL %s: more datagrams than the model read\n", name);
            return 1;
        }

        differences += canonical::compare(name, datagram, model[datagram], read(frame));
        ++datagram;
    }

    if (datagram != model.size()) {
        std::printf("FAIL %s: %zu datagrams, the model read %zu\n", name, datagram, model.size());
        return 1;
    }

    if (differences == 0) {
        std::printf("ok   %s: %zu datagrams\n", name, datagram);
    }

    return differences == 0 ? 0 : 1;
}

}

int main() {
    std::printf("== Eurex.T7.Eobi.Fbe.v13.0 (modern values)\n");
    int failures = 0;
    failures += check("AddComplexInstrument", "Eurex/T7.Eobi.Fbe.v13.0/AddComplexInstrument.pcap", "eurex/t7/eobi/fbe/v13.0/AddComplexInstrument.values");
    failures += check("AddFlexibleInstrument", "Eurex/T7.Eobi.Fbe.v13.0/AddFlexibleInstrument.pcap", "eurex/t7/eobi/fbe/v13.0/AddFlexibleInstrument.values");
    failures += check("AuctionBbo", "Eurex/T7.Eobi.Fbe.v13.0/AuctionBbo.pcap", "eurex/t7/eobi/fbe/v13.0/AuctionBbo.values");
    failures += check("AuctionClearingPrice", "Eurex/T7.Eobi.Fbe.v13.0/AuctionClearingPrice.pcap", "eurex/t7/eobi/fbe/v13.0/AuctionClearingPrice.values");
    failures += check("CrossRequest", "Eurex/T7.Eobi.Fbe.v13.0/CrossRequest.pcap", "eurex/t7/eobi/fbe/v13.0/CrossRequest.values");
    failures += check("ExecutionSummary", "Eurex/T7.Eobi.Fbe.v13.0/ExecutionSummary.pcap", "eurex/t7/eobi/fbe/v13.0/ExecutionSummary.values");
    failures += check("FullOrderExecution", "Eurex/T7.Eobi.Fbe.v13.0/FullOrderExecution.pcap", "eurex/t7/eobi/fbe/v13.0/FullOrderExecution.values");
    failures += check("Heartbeat", "Eurex/T7.Eobi.Fbe.v13.0/Heartbeat.pcap", "eurex/t7/eobi/fbe/v13.0/Heartbeat.values");
    failures += check("InstrumentStateChange", "Eurex/T7.Eobi.Fbe.v13.0/InstrumentStateChange.pcap", "eurex/t7/eobi/fbe/v13.0/InstrumentStateChange.values");
    failures += check("InstrumentSummary", "Eurex/T7.Eobi.Fbe.v13.0/InstrumentSummary.pcap", "eurex/t7/eobi/fbe/v13.0/InstrumentSummary.values");
    failures += check("MassInstrumentStateChange", "Eurex/T7.Eobi.Fbe.v13.0/MassInstrumentStateChange.pcap", "eurex/t7/eobi/fbe/v13.0/MassInstrumentStateChange.values");
    failures += check("OrderAdd", "Eurex/T7.Eobi.Fbe.v13.0/OrderAdd.pcap", "eurex/t7/eobi/fbe/v13.0/OrderAdd.values");
    failures += check("OrderDelete", "Eurex/T7.Eobi.Fbe.v13.0/OrderDelete.pcap", "eurex/t7/eobi/fbe/v13.0/OrderDelete.values");
    failures += check("OrderMassDelete", "Eurex/T7.Eobi.Fbe.v13.0/OrderMassDelete.pcap", "eurex/t7/eobi/fbe/v13.0/OrderMassDelete.values");
    failures += check("OrderModify", "Eurex/T7.Eobi.Fbe.v13.0/OrderModify.pcap", "eurex/t7/eobi/fbe/v13.0/OrderModify.values");
    failures += check("OrderModifySamePrio", "Eurex/T7.Eobi.Fbe.v13.0/OrderModifySamePrio.pcap", "eurex/t7/eobi/fbe/v13.0/OrderModifySamePrio.values");
    failures += check("PartialOrderExecution", "Eurex/T7.Eobi.Fbe.v13.0/PartialOrderExecution.pcap", "eurex/t7/eobi/fbe/v13.0/PartialOrderExecution.values");
    failures += check("ProductStateChange", "Eurex/T7.Eobi.Fbe.v13.0/ProductStateChange.pcap", "eurex/t7/eobi/fbe/v13.0/ProductStateChange.values");
    failures += check("ProductSummary", "Eurex/T7.Eobi.Fbe.v13.0/ProductSummary.pcap", "eurex/t7/eobi/fbe/v13.0/ProductSummary.values");
    failures += check("QuoteRequest", "Eurex/T7.Eobi.Fbe.v13.0/QuoteRequest.pcap", "eurex/t7/eobi/fbe/v13.0/QuoteRequest.values");
    failures += check("SnapshotOrder", "Eurex/T7.Eobi.Fbe.v13.0/SnapshotOrder.pcap", "eurex/t7/eobi/fbe/v13.0/SnapshotOrder.values");
    failures += check("TesTradeReport", "Eurex/T7.Eobi.Fbe.v13.0/TesTradeReport.pcap", "eurex/t7/eobi/fbe/v13.0/TesTradeReport.values");
    failures += check("TopOfBook", "Eurex/T7.Eobi.Fbe.v13.0/TopOfBook.pcap", "eurex/t7/eobi/fbe/v13.0/TopOfBook.values");
    failures += check("TradeReport", "Eurex/T7.Eobi.Fbe.v13.0/TradeReport.pcap", "eurex/t7/eobi/fbe/v13.0/TradeReport.values");
    failures += check("TradeReversal", "Eurex/T7.Eobi.Fbe.v13.0/TradeReversal.pcap", "eurex/t7/eobi/fbe/v13.0/TradeReversal.values");
    return failures == 0 ? 0 : 1;
}
