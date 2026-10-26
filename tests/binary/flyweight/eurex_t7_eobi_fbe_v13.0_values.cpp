// Eurex.T7.Eobi.Fbe.v13.0 canonical values, through the Flyweight reader: every value Flyweight reads
// from each sample, at its address, held to what the model reads.

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
#include "tests/canonical/Canonical.hpp"
#include "cpp/binary/flyweight/eurex/t7/eobi/fbe/v13.0/definitions.hpp"

namespace protocol = ::eurex::t7::eobi::fbe::v13_0;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        values["packet.packetheader.eobiheader.bodylen"] = canonical::number(packet.packet_header().eobi_header().body_len());
        values["packet.packetheader.eobiheader.templateid"] = canonical::number(packet.packet_header().eobi_header().template_id());
        values["packet.packetheader.eobiheader.msgseqnum"] = canonical::number(packet.packet_header().eobi_header().msg_seq_num());
        values["packet.packetheader.applseqnum"] = canonical::number(packet.packet_header().appl_seq_num());
        values["packet.packetheader.marketsegmentid"] = (packet.packet_header().market_segment_id().has_value() ? canonical::number((*packet.packet_header().market_segment_id())) : canonical::absent());
        values["packet.packetheader.partitionid"] = (packet.packet_header().partition_id().has_value() ? canonical::number((*packet.packet_header().partition_id())) : canonical::absent());
        values["packet.packetheader.completionindicator"] = (packet.packet_header().completion_indicator().has_value() ? canonical::number((*packet.packet_header().completion_indicator())) : canonical::absent());
        values["packet.packetheader.applseqresetindicator"] = (packet.packet_header().appl_seq_reset_indicator().has_value() ? canonical::number((*packet.packet_header().appl_seq_reset_indicator())) : canonical::absent());
        values["packet.packetheader.dscp"] = canonical::number(packet.packet_header().dscp());
        values["packet.packetheader.transacttime"] = (packet.packet_header().transact_time().has_value() ? canonical::number((*packet.packet_header().transact_time())) : canonical::absent());
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

    void on(const protocol::AddComplexInstrument& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.addcomplexinstrument";
        values[entry + ".payload.addcomplexinstrument.securityid"] = (message.security_id().has_value() ? canonical::number((*message.security_id())) : canonical::absent());
        values[entry + ".payload.addcomplexinstrument.transacttime"] = (message.transact_time().has_value() ? canonical::number((*message.transact_time())) : canonical::absent());
        values[entry + ".payload.addcomplexinstrument.securitysubtype"] = (message.security_sub_type().has_value() ? canonical::number((*message.security_sub_type())) : canonical::absent());
        values[entry + ".payload.addcomplexinstrument.productcomplex"] = (message.product_complex().has_value() ? canonical::number((*message.product_complex())) : canonical::absent());
        values[entry + ".payload.addcomplexinstrument.impliedmarketindicator"] = (message.implied_market_indicator().has_value() ? canonical::number((*message.implied_market_indicator())) : canonical::absent());
        values[entry + ".payload.addcomplexinstrument.quantityscalingfactor"] = (message.quantity_scaling_factor().has_value() ? canonical::number((*message.quantity_scaling_factor())) : canonical::absent());
        values[entry + ".payload.addcomplexinstrument.legratiomultiplier"] = (message.leg_ratio_multiplier().has_value() ? canonical::number((*message.leg_ratio_multiplier())) : canonical::absent());
        values[entry + ".payload.addcomplexinstrument.nolegs"] = (message.no_legs().has_value() ? canonical::number((*message.no_legs())) : canonical::absent());
        values[entry + ".payload.addcomplexinstrument.lastfragment"] = (message.last_fragment().has_value() ? canonical::number((*message.last_fragment())) : canonical::absent());
    }

    void on(const protocol::AddFlexibleInstrument& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.addflexibleinstrument";
        values[entry + ".payload.addflexibleinstrument.securityid"] = (message.security_id().has_value() ? canonical::number((*message.security_id())) : canonical::absent());
        values[entry + ".payload.addflexibleinstrument.transacttime"] = (message.transact_time().has_value() ? canonical::number((*message.transact_time())) : canonical::absent());
        values[entry + ".payload.addflexibleinstrument.securitytype"] = (message.security_type().has_value() ? canonical::number((*message.security_type())) : canonical::absent());
        values[entry + ".payload.addflexibleinstrument.putorcall"] = (message.put_or_call().has_value() ? canonical::number((*message.put_or_call())) : canonical::absent());
        values[entry + ".payload.addflexibleinstrument.exercisestyle"] = (message.exercise_style().has_value() ? canonical::number((*message.exercise_style())) : canonical::absent());
        values[entry + ".payload.addflexibleinstrument.settlmethod"] = (message.settl_method().has_value() ? canonical::number((*message.settl_method())) : canonical::absent());
        values[entry + ".payload.addflexibleinstrument.maturitydate"] = (message.maturity_date().has_value() ? canonical::number((*message.maturity_date())) : canonical::absent());
        values[entry + ".payload.addflexibleinstrument.strikeprice"] = (message.strike_price().has_value() ? canonical::scaled((*message.strike_price()).mantissa(), (*message.strike_price()).exponent()) : canonical::absent());
        values[entry + ".payload.addflexibleinstrument.optattribute"] = (message.opt_attribute().has_value() ? canonical::number((*message.opt_attribute())) : canonical::absent());
        values[entry + ".payload.addflexibleinstrument.contractdate"] = (message.contract_date().has_value() ? canonical::number((*message.contract_date())) : canonical::absent());
        values[entry + ".payload.addflexibleinstrument.securityreferencedatasupplement"] = (message.security_reference_data_supplement().has_value() ? canonical::number((*message.security_reference_data_supplement())) : canonical::absent());
    }

    void on(const protocol::AddScaledSimpleInstrument& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.addscaledsimpleinstrument";
        values[entry + ".payload.addscaledsimpleinstrument.securityid"] = (message.security_id().has_value() ? canonical::number((*message.security_id())) : canonical::absent());
        values[entry + ".payload.addscaledsimpleinstrument.transacttime"] = (message.transact_time().has_value() ? canonical::number((*message.transact_time())) : canonical::absent());
        values[entry + ".payload.addscaledsimpleinstrument.securitytype"] = (message.security_type().has_value() ? canonical::number((*message.security_type())) : canonical::absent());
        values[entry + ".payload.addscaledsimpleinstrument.quantityscalingfactor"] = (message.quantity_scaling_factor().has_value() ? canonical::number((*message.quantity_scaling_factor())) : canonical::absent());
        values[entry + ".payload.addscaledsimpleinstrument.relatedinstrumentgrpcomp.relatedsecurityid"] = (message.related_instrument_grp_comp().related_security_id().has_value() ? canonical::number((*message.related_instrument_grp_comp().related_security_id())) : canonical::absent());
    }

    void on(const protocol::AuctionBbo& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.auctionbbo";
        values[entry + ".payload.auctionbbo.transacttime"] = (message.transact_time().has_value() ? canonical::number((*message.transact_time())) : canonical::absent());
        values[entry + ".payload.auctionbbo.securityid"] = (message.security_id().has_value() ? canonical::number((*message.security_id())) : canonical::absent());
        values[entry + ".payload.auctionbbo.bidpx"] = (message.bid_px().has_value() ? canonical::scaled((*message.bid_px()).mantissa(), (*message.bid_px()).exponent()) : canonical::absent());
        values[entry + ".payload.auctionbbo.offerpx"] = (message.offer_px().has_value() ? canonical::scaled((*message.offer_px()).mantissa(), (*message.offer_px()).exponent()) : canonical::absent());
        values[entry + ".payload.auctionbbo.bidsize"] = (message.bid_size().has_value() ? canonical::scaled((*message.bid_size()).mantissa(), (*message.bid_size()).exponent()) : canonical::absent());
        values[entry + ".payload.auctionbbo.offersize"] = (message.offer_size().has_value() ? canonical::scaled((*message.offer_size()).mantissa(), (*message.offer_size()).exponent()) : canonical::absent());
        values[entry + ".payload.auctionbbo.potentialsecuritytradingevent"] = (message.potential_security_trading_event().has_value() ? canonical::number((*message.potential_security_trading_event())) : canonical::absent());
        values[entry + ".payload.auctionbbo.bidordtype"] = (message.bid_ord_type().has_value() ? canonical::number((*message.bid_ord_type())) : canonical::absent());
        values[entry + ".payload.auctionbbo.offerordtype"] = (message.offer_ord_type().has_value() ? canonical::number((*message.offer_ord_type())) : canonical::absent());
    }

    void on(const protocol::AuctionClearingPrice& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.auctionclearingprice";
        values[entry + ".payload.auctionclearingprice.transacttime"] = (message.transact_time().has_value() ? canonical::number((*message.transact_time())) : canonical::absent());
        values[entry + ".payload.auctionclearingprice.securityid"] = (message.security_id().has_value() ? canonical::number((*message.security_id())) : canonical::absent());
        values[entry + ".payload.auctionclearingprice.lastpx"] = (message.last_px().has_value() ? canonical::scaled((*message.last_px()).mantissa(), (*message.last_px()).exponent()) : canonical::absent());
        values[entry + ".payload.auctionclearingprice.lastqty"] = (message.last_qty().has_value() ? canonical::scaled((*message.last_qty()).mantissa(), (*message.last_qty()).exponent()) : canonical::absent());
        values[entry + ".payload.auctionclearingprice.imbalanceqty"] = (message.imbalance_qty().has_value() ? canonical::scaled((*message.imbalance_qty()).mantissa(), (*message.imbalance_qty()).exponent()) : canonical::absent());
        values[entry + ".payload.auctionclearingprice.securitytradingstatus"] = (message.security_trading_status().has_value() ? canonical::number((*message.security_trading_status())) : canonical::absent());
        values[entry + ".payload.auctionclearingprice.potentialsecuritytradingevent"] = (message.potential_security_trading_event().has_value() ? canonical::number((*message.potential_security_trading_event())) : canonical::absent());
    }

    void on(const protocol::CrossRequest& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.crossrequest";
        values[entry + ".payload.crossrequest.securityid"] = (message.security_id().has_value() ? canonical::number((*message.security_id())) : canonical::absent());
        values[entry + ".payload.crossrequest.lastpx"] = (message.last_px().has_value() ? canonical::scaled((*message.last_px()).mantissa(), (*message.last_px()).exponent()) : canonical::absent());
        values[entry + ".payload.crossrequest.lastqty"] = (message.last_qty().has_value() ? canonical::scaled((*message.last_qty()).mantissa(), (*message.last_qty()).exponent()) : canonical::absent());
        values[entry + ".payload.crossrequest.side"] = (message.side().has_value() ? canonical::number((*message.side())) : canonical::absent());
        values[entry + ".payload.crossrequest.crossrequesttype"] = (message.cross_request_type().has_value() ? canonical::number((*message.cross_request_type())) : canonical::absent());
        values[entry + ".payload.crossrequest.inputsource"] = (message.input_source().has_value() ? canonical::number((*message.input_source())) : canonical::absent());
        values[entry + ".payload.crossrequest.transacttime"] = (message.transact_time().has_value() ? canonical::number((*message.transact_time())) : canonical::absent());
    }

    void on(const protocol::ExecutionSummary& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.executionsummary";
        values[entry + ".payload.executionsummary.securityid"] = (message.security_id().has_value() ? canonical::number((*message.security_id())) : canonical::absent());
        values[entry + ".payload.executionsummary.requesttime"] = (message.request_time().has_value() ? canonical::number((*message.request_time())) : canonical::absent());
        values[entry + ".payload.executionsummary.execid"] = (message.exec_id().has_value() ? canonical::number((*message.exec_id())) : canonical::absent());
        values[entry + ".payload.executionsummary.lastqty"] = (message.last_qty().has_value() ? canonical::scaled((*message.last_qty()).mantissa(), (*message.last_qty()).exponent()) : canonical::absent());
        values[entry + ".payload.executionsummary.aggressorside"] = (message.aggressor_side().has_value() ? canonical::number((*message.aggressor_side())) : canonical::absent());
        values[entry + ".payload.executionsummary.tradecondition"] = (message.trade_condition().has_value() ? canonical::number((*message.trade_condition())) : canonical::absent());
        values[entry + ".payload.executionsummary.tradinghhiindicator"] = (message.trading_hhi_indicator().has_value() ? canonical::number((*message.trading_hhi_indicator())) : canonical::absent());
        values[entry + ".payload.executionsummary.lastpx"] = (message.last_px().has_value() ? canonical::scaled((*message.last_px()).mantissa(), (*message.last_px()).exponent()) : canonical::absent());
        values[entry + ".payload.executionsummary.remainingorderdetailscomp.trdregtsprevtimepriority"] = (message.remaining_order_details_comp().trd_reg_ts_prev_time_priority().has_value() ? canonical::number((*message.remaining_order_details_comp().trd_reg_ts_prev_time_priority())) : canonical::absent());
        values[entry + ".payload.executionsummary.remainingorderdetailscomp.displayqty"] = (message.remaining_order_details_comp().display_qty().has_value() ? canonical::scaled((*message.remaining_order_details_comp().display_qty()).mantissa(), (*message.remaining_order_details_comp().display_qty()).exponent()) : canonical::absent());
        values[entry + ".payload.executionsummary.remainingorderdetailscomp.price"] = (message.remaining_order_details_comp().price().has_value() ? canonical::scaled((*message.remaining_order_details_comp().price()).mantissa(), (*message.remaining_order_details_comp().price()).exponent()) : canonical::absent());
        values[entry + ".payload.executionsummary.restinghiddenqty"] = (message.resting_hidden_qty().has_value() ? canonical::scaled((*message.resting_hidden_qty()).mantissa(), (*message.resting_hidden_qty()).exponent()) : canonical::absent());
        values[entry + ".payload.executionsummary.restingcxlqty"] = (message.resting_cxl_qty().has_value() ? canonical::scaled((*message.resting_cxl_qty()).mantissa(), (*message.resting_cxl_qty()).exponent()) : canonical::absent());
        values[entry + ".payload.executionsummary.aggressortime"] = (message.aggressor_time().has_value() ? canonical::number((*message.aggressor_time())) : canonical::absent());
    }

    void on(const protocol::FullOrderExecution& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.fullorderexecution";
        values[entry + ".payload.fullorderexecution.side"] = (message.side().has_value() ? canonical::number((*message.side())) : canonical::absent());
        values[entry + ".payload.fullorderexecution.ordtype"] = (message.ord_type().has_value() ? canonical::number((*message.ord_type())) : canonical::absent());
        values[entry + ".payload.fullorderexecution.algorithmictradeindicator"] = (message.algorithmic_trade_indicator().has_value() ? canonical::number((*message.algorithmic_trade_indicator())) : canonical::absent());
        values[entry + ".payload.fullorderexecution.hhiindicator"] = (message.hhi_indicator().has_value() ? canonical::number((*message.hhi_indicator())) : canonical::absent());
        values[entry + ".payload.fullorderexecution.trdmatchid"] = (message.trd_match_id().has_value() ? canonical::number((*message.trd_match_id())) : canonical::absent());
        values[entry + ".payload.fullorderexecution.price"] = (message.price().has_value() ? canonical::scaled((*message.price()).mantissa(), (*message.price()).exponent()) : canonical::absent());
        values[entry + ".payload.fullorderexecution.trdregtstimepriority"] = (message.trd_reg_ts_time_priority().has_value() ? canonical::number((*message.trd_reg_ts_time_priority())) : canonical::absent());
        values[entry + ".payload.fullorderexecution.securityid"] = (message.security_id().has_value() ? canonical::number((*message.security_id())) : canonical::absent());
        values[entry + ".payload.fullorderexecution.lastqty"] = (message.last_qty().has_value() ? canonical::scaled((*message.last_qty()).mantissa(), (*message.last_qty()).exponent()) : canonical::absent());
        values[entry + ".payload.fullorderexecution.lastpx"] = (message.last_px().has_value() ? canonical::scaled((*message.last_px()).mantissa(), (*message.last_px()).exponent()) : canonical::absent());
    }

    void on(const protocol::Heartbeat& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.heartbeat";
        values[entry + ".payload.heartbeat.lastmsgseqnumprocessed"] = (message.last_msg_seq_num_processed().has_value() ? canonical::number((*message.last_msg_seq_num_processed())) : canonical::absent());
    }

    void on(const protocol::InstrumentStateChange& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.instrumentstatechange";
        values[entry + ".payload.instrumentstatechange.securityid"] = (message.security_id().has_value() ? canonical::number((*message.security_id())) : canonical::absent());
        values[entry + ".payload.instrumentstatechange.securitystatus"] = (message.security_status().has_value() ? canonical::number((*message.security_status())) : canonical::absent());
        values[entry + ".payload.instrumentstatechange.securitytradingstatus"] = (message.security_trading_status().has_value() ? canonical::number((*message.security_trading_status())) : canonical::absent());
        values[entry + ".payload.instrumentstatechange.marketcondition"] = (message.market_condition().has_value() ? canonical::number((*message.market_condition())) : canonical::absent());
        values[entry + ".payload.instrumentstatechange.fastmarketindicator"] = (message.fast_market_indicator().has_value() ? canonical::number((*message.fast_market_indicator())) : canonical::absent());
        values[entry + ".payload.instrumentstatechange.securitytradingevent"] = (message.security_trading_event().has_value() ? canonical::number((*message.security_trading_event())) : canonical::absent());
        values[entry + ".payload.instrumentstatechange.soldoutindicator"] = (message.sold_out_indicator().has_value() ? canonical::number((*message.sold_out_indicator())) : canonical::absent());
        values[entry + ".payload.instrumentstatechange.highpx"] = (message.high_px().has_value() ? canonical::scaled((*message.high_px()).mantissa(), (*message.high_px()).exponent()) : canonical::absent());
        values[entry + ".payload.instrumentstatechange.lowpx"] = (message.low_px().has_value() ? canonical::scaled((*message.low_px()).mantissa(), (*message.low_px()).exponent()) : canonical::absent());
        values[entry + ".payload.instrumentstatechange.transacttime"] = (message.transact_time().has_value() ? canonical::number((*message.transact_time())) : canonical::absent());
        values[entry + ".payload.instrumentstatechange.tessecuritystatus"] = (message.tes_security_status().has_value() ? canonical::number((*message.tes_security_status())) : canonical::absent());
    }

    void on(const protocol::InstrumentSummary& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.instrumentsummary";
        values[entry + ".payload.instrumentsummary.securityid"] = (message.security_id().has_value() ? canonical::number((*message.security_id())) : canonical::absent());
        values[entry + ".payload.instrumentsummary.lastupdatetime"] = (message.last_update_time().has_value() ? canonical::number((*message.last_update_time())) : canonical::absent());
        values[entry + ".payload.instrumentsummary.trdregtsexecutiontime"] = (message.trd_reg_ts_execution_time().has_value() ? canonical::number((*message.trd_reg_ts_execution_time())) : canonical::absent());
        values[entry + ".payload.instrumentsummary.totnoorders"] = (message.tot_no_orders().has_value() ? canonical::number((*message.tot_no_orders())) : canonical::absent());
        values[entry + ".payload.instrumentsummary.securitystatus"] = (message.security_status().has_value() ? canonical::number((*message.security_status())) : canonical::absent());
        values[entry + ".payload.instrumentsummary.securitytradingstatus"] = (message.security_trading_status().has_value() ? canonical::number((*message.security_trading_status())) : canonical::absent());
        values[entry + ".payload.instrumentsummary.marketcondition"] = (message.market_condition().has_value() ? canonical::number((*message.market_condition())) : canonical::absent());
        values[entry + ".payload.instrumentsummary.fastmarketindicator"] = (message.fast_market_indicator().has_value() ? canonical::number((*message.fast_market_indicator())) : canonical::absent());
        values[entry + ".payload.instrumentsummary.securitytradingevent"] = (message.security_trading_event().has_value() ? canonical::number((*message.security_trading_event())) : canonical::absent());
        values[entry + ".payload.instrumentsummary.soldoutindicator"] = (message.sold_out_indicator().has_value() ? canonical::number((*message.sold_out_indicator())) : canonical::absent());
        values[entry + ".payload.instrumentsummary.highpx"] = (message.high_px().has_value() ? canonical::scaled((*message.high_px()).mantissa(), (*message.high_px()).exponent()) : canonical::absent());
        values[entry + ".payload.instrumentsummary.lowpx"] = (message.low_px().has_value() ? canonical::scaled((*message.low_px()).mantissa(), (*message.low_px()).exponent()) : canonical::absent());
        values[entry + ".payload.instrumentsummary.productcomplex"] = (message.product_complex().has_value() ? canonical::number((*message.product_complex())) : canonical::absent());
        values[entry + ".payload.instrumentsummary.nomdentries"] = (message.no_md_entries().has_value() ? canonical::number((*message.no_md_entries())) : canonical::absent());
        values[entry + ".payload.instrumentsummary.tessecuritystatus"] = (message.tes_security_status().has_value() ? canonical::number((*message.tes_security_status())) : canonical::absent());
    }

    void on(const protocol::MassInstrumentStateChange& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.massinstrumentstatechange";
        values[entry + ".payload.massinstrumentstatechange.instrumentscopeproductcomplex"] = (message.instrument_scope_product_complex().has_value() ? canonical::number((*message.instrument_scope_product_complex())) : canonical::absent());
        values[entry + ".payload.massinstrumentstatechange.securitymassstatus"] = (message.security_mass_status().has_value() ? canonical::number((*message.security_mass_status())) : canonical::absent());
        values[entry + ".payload.massinstrumentstatechange.securitymasstradingstatus"] = (message.security_mass_trading_status().has_value() ? canonical::number((*message.security_mass_trading_status())) : canonical::absent());
        values[entry + ".payload.massinstrumentstatechange.massmarketcondition"] = (message.mass_market_condition().has_value() ? canonical::number((*message.mass_market_condition())) : canonical::absent());
        values[entry + ".payload.massinstrumentstatechange.fastmarketindicator"] = (message.fast_market_indicator().has_value() ? canonical::number((*message.fast_market_indicator())) : canonical::absent());
        values[entry + ".payload.massinstrumentstatechange.securitymasstradingevent"] = (message.security_mass_trading_event().has_value() ? canonical::number((*message.security_mass_trading_event())) : canonical::absent());
        values[entry + ".payload.massinstrumentstatechange.masssoldoutindicator"] = (message.mass_sold_out_indicator().has_value() ? canonical::number((*message.mass_sold_out_indicator())) : canonical::absent());
        values[entry + ".payload.massinstrumentstatechange.tessecuritymassstatus"] = (message.tes_security_mass_status().has_value() ? canonical::number((*message.tes_security_mass_status())) : canonical::absent());
        values[entry + ".payload.massinstrumentstatechange.transacttime"] = (message.transact_time().has_value() ? canonical::number((*message.transact_time())) : canonical::absent());
        values[entry + ".payload.massinstrumentstatechange.lastfragment"] = (message.last_fragment().has_value() ? canonical::number((*message.last_fragment())) : canonical::absent());
        values[entry + ".payload.massinstrumentstatechange.norelatedsym"] = (message.no_related_sym().has_value() ? canonical::number((*message.no_related_sym())) : canonical::absent());
    }

    void on(const protocol::OrderAdd& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.orderadd";
        values[entry + ".payload.orderadd.requesttime"] = (message.request_time().has_value() ? canonical::number((*message.request_time())) : canonical::absent());
        values[entry + ".payload.orderadd.securityid"] = (message.security_id().has_value() ? canonical::number((*message.security_id())) : canonical::absent());
        values[entry + ".payload.orderadd.orderdetailscomp.trdregtstimepriority"] = (message.order_details_comp().trd_reg_ts_time_priority().has_value() ? canonical::number((*message.order_details_comp().trd_reg_ts_time_priority())) : canonical::absent());
        values[entry + ".payload.orderadd.orderdetailscomp.displayqty"] = (message.order_details_comp().display_qty().has_value() ? canonical::scaled((*message.order_details_comp().display_qty()).mantissa(), (*message.order_details_comp().display_qty()).exponent()) : canonical::absent());
        values[entry + ".payload.orderadd.orderdetailscomp.side"] = (message.order_details_comp().side().has_value() ? canonical::number((*message.order_details_comp().side())) : canonical::absent());
        values[entry + ".payload.orderadd.orderdetailscomp.ordtype"] = (message.order_details_comp().ord_type().has_value() ? canonical::number((*message.order_details_comp().ord_type())) : canonical::absent());
        values[entry + ".payload.orderadd.orderdetailscomp.hhiindicator"] = (message.order_details_comp().hhi_indicator().has_value() ? canonical::number((*message.order_details_comp().hhi_indicator())) : canonical::absent());
        values[entry + ".payload.orderadd.orderdetailscomp.price"] = (message.order_details_comp().price().has_value() ? canonical::scaled((*message.order_details_comp().price()).mantissa(), (*message.order_details_comp().price()).exponent()) : canonical::absent());
    }

    void on(const protocol::OrderDelete& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.orderdelete";
        values[entry + ".payload.orderdelete.requesttime"] = (message.request_time().has_value() ? canonical::number((*message.request_time())) : canonical::absent());
        values[entry + ".payload.orderdelete.transacttime"] = (message.transact_time().has_value() ? canonical::number((*message.transact_time())) : canonical::absent());
        values[entry + ".payload.orderdelete.securityid"] = (message.security_id().has_value() ? canonical::number((*message.security_id())) : canonical::absent());
        values[entry + ".payload.orderdelete.orderdetailscomp.trdregtstimepriority"] = (message.order_details_comp().trd_reg_ts_time_priority().has_value() ? canonical::number((*message.order_details_comp().trd_reg_ts_time_priority())) : canonical::absent());
        values[entry + ".payload.orderdelete.orderdetailscomp.displayqty"] = (message.order_details_comp().display_qty().has_value() ? canonical::scaled((*message.order_details_comp().display_qty()).mantissa(), (*message.order_details_comp().display_qty()).exponent()) : canonical::absent());
        values[entry + ".payload.orderdelete.orderdetailscomp.side"] = (message.order_details_comp().side().has_value() ? canonical::number((*message.order_details_comp().side())) : canonical::absent());
        values[entry + ".payload.orderdelete.orderdetailscomp.ordtype"] = (message.order_details_comp().ord_type().has_value() ? canonical::number((*message.order_details_comp().ord_type())) : canonical::absent());
        values[entry + ".payload.orderdelete.orderdetailscomp.hhiindicator"] = (message.order_details_comp().hhi_indicator().has_value() ? canonical::number((*message.order_details_comp().hhi_indicator())) : canonical::absent());
        values[entry + ".payload.orderdelete.orderdetailscomp.price"] = (message.order_details_comp().price().has_value() ? canonical::scaled((*message.order_details_comp().price()).mantissa(), (*message.order_details_comp().price()).exponent()) : canonical::absent());
    }

    void on(const protocol::OrderMassDelete& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.ordermassdelete";
        values[entry + ".payload.ordermassdelete.securityid"] = (message.security_id().has_value() ? canonical::number((*message.security_id())) : canonical::absent());
        values[entry + ".payload.ordermassdelete.transacttime"] = (message.transact_time().has_value() ? canonical::number((*message.transact_time())) : canonical::absent());
    }

    void on(const protocol::OrderModify& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.ordermodify";
        values[entry + ".payload.ordermodify.requesttime"] = (message.request_time().has_value() ? canonical::number((*message.request_time())) : canonical::absent());
        values[entry + ".payload.ordermodify.trdregtsprevtimepriority"] = (message.trd_reg_ts_prev_time_priority().has_value() ? canonical::number((*message.trd_reg_ts_prev_time_priority())) : canonical::absent());
        values[entry + ".payload.ordermodify.prevprice"] = (message.prev_price().has_value() ? canonical::scaled((*message.prev_price()).mantissa(), (*message.prev_price()).exponent()) : canonical::absent());
        values[entry + ".payload.ordermodify.prevdisplayqty"] = (message.prev_display_qty().has_value() ? canonical::scaled((*message.prev_display_qty()).mantissa(), (*message.prev_display_qty()).exponent()) : canonical::absent());
        values[entry + ".payload.ordermodify.securityid"] = (message.security_id().has_value() ? canonical::number((*message.security_id())) : canonical::absent());
        values[entry + ".payload.ordermodify.orderdetailscomp.trdregtstimepriority"] = (message.order_details_comp().trd_reg_ts_time_priority().has_value() ? canonical::number((*message.order_details_comp().trd_reg_ts_time_priority())) : canonical::absent());
        values[entry + ".payload.ordermodify.orderdetailscomp.displayqty"] = (message.order_details_comp().display_qty().has_value() ? canonical::scaled((*message.order_details_comp().display_qty()).mantissa(), (*message.order_details_comp().display_qty()).exponent()) : canonical::absent());
        values[entry + ".payload.ordermodify.orderdetailscomp.side"] = (message.order_details_comp().side().has_value() ? canonical::number((*message.order_details_comp().side())) : canonical::absent());
        values[entry + ".payload.ordermodify.orderdetailscomp.ordtype"] = (message.order_details_comp().ord_type().has_value() ? canonical::number((*message.order_details_comp().ord_type())) : canonical::absent());
        values[entry + ".payload.ordermodify.orderdetailscomp.hhiindicator"] = (message.order_details_comp().hhi_indicator().has_value() ? canonical::number((*message.order_details_comp().hhi_indicator())) : canonical::absent());
        values[entry + ".payload.ordermodify.orderdetailscomp.price"] = (message.order_details_comp().price().has_value() ? canonical::scaled((*message.order_details_comp().price()).mantissa(), (*message.order_details_comp().price()).exponent()) : canonical::absent());
        values[entry + ".payload.ordermodify.prevpricehhiindicator"] = (message.prev_price_hhi_indicator().has_value() ? canonical::number((*message.prev_price_hhi_indicator())) : canonical::absent());
    }

    void on(const protocol::OrderModifySamePrio& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.ordermodifysameprio";
        values[entry + ".payload.ordermodifysameprio.requesttime"] = (message.request_time().has_value() ? canonical::number((*message.request_time())) : canonical::absent());
        values[entry + ".payload.ordermodifysameprio.transacttime"] = (message.transact_time().has_value() ? canonical::number((*message.transact_time())) : canonical::absent());
        values[entry + ".payload.ordermodifysameprio.prevdisplayqty"] = (message.prev_display_qty().has_value() ? canonical::scaled((*message.prev_display_qty()).mantissa(), (*message.prev_display_qty()).exponent()) : canonical::absent());
        values[entry + ".payload.ordermodifysameprio.securityid"] = (message.security_id().has_value() ? canonical::number((*message.security_id())) : canonical::absent());
        values[entry + ".payload.ordermodifysameprio.orderdetailscomp.trdregtstimepriority"] = (message.order_details_comp().trd_reg_ts_time_priority().has_value() ? canonical::number((*message.order_details_comp().trd_reg_ts_time_priority())) : canonical::absent());
        values[entry + ".payload.ordermodifysameprio.orderdetailscomp.displayqty"] = (message.order_details_comp().display_qty().has_value() ? canonical::scaled((*message.order_details_comp().display_qty()).mantissa(), (*message.order_details_comp().display_qty()).exponent()) : canonical::absent());
        values[entry + ".payload.ordermodifysameprio.orderdetailscomp.side"] = (message.order_details_comp().side().has_value() ? canonical::number((*message.order_details_comp().side())) : canonical::absent());
        values[entry + ".payload.ordermodifysameprio.orderdetailscomp.ordtype"] = (message.order_details_comp().ord_type().has_value() ? canonical::number((*message.order_details_comp().ord_type())) : canonical::absent());
        values[entry + ".payload.ordermodifysameprio.orderdetailscomp.hhiindicator"] = (message.order_details_comp().hhi_indicator().has_value() ? canonical::number((*message.order_details_comp().hhi_indicator())) : canonical::absent());
        values[entry + ".payload.ordermodifysameprio.orderdetailscomp.price"] = (message.order_details_comp().price().has_value() ? canonical::scaled((*message.order_details_comp().price()).mantissa(), (*message.order_details_comp().price()).exponent()) : canonical::absent());
    }

    void on(const protocol::PartialOrderExecution& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.partialorderexecution";
        values[entry + ".payload.partialorderexecution.side"] = (message.side().has_value() ? canonical::number((*message.side())) : canonical::absent());
        values[entry + ".payload.partialorderexecution.ordtype"] = (message.ord_type().has_value() ? canonical::number((*message.ord_type())) : canonical::absent());
        values[entry + ".payload.partialorderexecution.algorithmictradeindicator"] = (message.algorithmic_trade_indicator().has_value() ? canonical::number((*message.algorithmic_trade_indicator())) : canonical::absent());
        values[entry + ".payload.partialorderexecution.hhiindicator"] = (message.hhi_indicator().has_value() ? canonical::number((*message.hhi_indicator())) : canonical::absent());
        values[entry + ".payload.partialorderexecution.trdmatchid"] = (message.trd_match_id().has_value() ? canonical::number((*message.trd_match_id())) : canonical::absent());
        values[entry + ".payload.partialorderexecution.price"] = (message.price().has_value() ? canonical::scaled((*message.price()).mantissa(), (*message.price()).exponent()) : canonical::absent());
        values[entry + ".payload.partialorderexecution.trdregtstimepriority"] = (message.trd_reg_ts_time_priority().has_value() ? canonical::number((*message.trd_reg_ts_time_priority())) : canonical::absent());
        values[entry + ".payload.partialorderexecution.securityid"] = (message.security_id().has_value() ? canonical::number((*message.security_id())) : canonical::absent());
        values[entry + ".payload.partialorderexecution.lastqty"] = (message.last_qty().has_value() ? canonical::scaled((*message.last_qty()).mantissa(), (*message.last_qty()).exponent()) : canonical::absent());
        values[entry + ".payload.partialorderexecution.lastpx"] = (message.last_px().has_value() ? canonical::scaled((*message.last_px()).mantissa(), (*message.last_px()).exponent()) : canonical::absent());
    }

    void on(const protocol::ProductStateChange& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.productstatechange";
        values[entry + ".payload.productstatechange.tradingsessionid"] = (message.trading_session_id().has_value() ? canonical::number((*message.trading_session_id())) : canonical::absent());
        values[entry + ".payload.productstatechange.tradingsessionsubid"] = (message.trading_session_sub_id().has_value() ? canonical::number((*message.trading_session_sub_id())) : canonical::absent());
        values[entry + ".payload.productstatechange.tradsesstatus"] = (message.trad_ses_status().has_value() ? canonical::number((*message.trad_ses_status())) : canonical::absent());
        values[entry + ".payload.productstatechange.marketcondition"] = (message.market_condition().has_value() ? canonical::number((*message.market_condition())) : canonical::absent());
        values[entry + ".payload.productstatechange.fastmarketindicator"] = (message.fast_market_indicator().has_value() ? canonical::number((*message.fast_market_indicator())) : canonical::absent());
        values[entry + ".payload.productstatechange.testradsesstatus"] = (message.tes_trad_ses_status().has_value() ? canonical::number((*message.tes_trad_ses_status())) : canonical::absent());
        values[entry + ".payload.productstatechange.transacttime"] = (message.transact_time().has_value() ? canonical::number((*message.transact_time())) : canonical::absent());
    }

    void on(const protocol::ProductSummary& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.productsummary";
        values[entry + ".payload.productsummary.lastmsgseqnumprocessed"] = (message.last_msg_seq_num_processed().has_value() ? canonical::number((*message.last_msg_seq_num_processed())) : canonical::absent());
        values[entry + ".payload.productsummary.tradingsessionid"] = (message.trading_session_id().has_value() ? canonical::number((*message.trading_session_id())) : canonical::absent());
        values[entry + ".payload.productsummary.tradingsessionsubid"] = (message.trading_session_sub_id().has_value() ? canonical::number((*message.trading_session_sub_id())) : canonical::absent());
        values[entry + ".payload.productsummary.tradsesstatus"] = (message.trad_ses_status().has_value() ? canonical::number((*message.trad_ses_status())) : canonical::absent());
        values[entry + ".payload.productsummary.marketcondition"] = (message.market_condition().has_value() ? canonical::number((*message.market_condition())) : canonical::absent());
        values[entry + ".payload.productsummary.fastmarketindicator"] = (message.fast_market_indicator().has_value() ? canonical::number((*message.fast_market_indicator())) : canonical::absent());
        values[entry + ".payload.productsummary.testradsesstatus"] = (message.tes_trad_ses_status().has_value() ? canonical::number((*message.tes_trad_ses_status())) : canonical::absent());
    }

    void on(const protocol::QuoteRequest& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.quoterequest";
        values[entry + ".payload.quoterequest.securityid"] = (message.security_id().has_value() ? canonical::number((*message.security_id())) : canonical::absent());
        values[entry + ".payload.quoterequest.lastqty"] = (message.last_qty().has_value() ? canonical::scaled((*message.last_qty()).mantissa(), (*message.last_qty()).exponent()) : canonical::absent());
        values[entry + ".payload.quoterequest.side"] = (message.side().has_value() ? canonical::number((*message.side())) : canonical::absent());
        values[entry + ".payload.quoterequest.transacttime"] = (message.transact_time().has_value() ? canonical::number((*message.transact_time())) : canonical::absent());
    }

    void on(const protocol::SnapshotOrder& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.snapshotorder";
        values[entry + ".payload.snapshotorder.orderdetailscomp.trdregtstimepriority"] = (message.order_details_comp().trd_reg_ts_time_priority().has_value() ? canonical::number((*message.order_details_comp().trd_reg_ts_time_priority())) : canonical::absent());
        values[entry + ".payload.snapshotorder.orderdetailscomp.displayqty"] = (message.order_details_comp().display_qty().has_value() ? canonical::scaled((*message.order_details_comp().display_qty()).mantissa(), (*message.order_details_comp().display_qty()).exponent()) : canonical::absent());
        values[entry + ".payload.snapshotorder.orderdetailscomp.side"] = (message.order_details_comp().side().has_value() ? canonical::number((*message.order_details_comp().side())) : canonical::absent());
        values[entry + ".payload.snapshotorder.orderdetailscomp.ordtype"] = (message.order_details_comp().ord_type().has_value() ? canonical::number((*message.order_details_comp().ord_type())) : canonical::absent());
        values[entry + ".payload.snapshotorder.orderdetailscomp.hhiindicator"] = (message.order_details_comp().hhi_indicator().has_value() ? canonical::number((*message.order_details_comp().hhi_indicator())) : canonical::absent());
        values[entry + ".payload.snapshotorder.orderdetailscomp.price"] = (message.order_details_comp().price().has_value() ? canonical::scaled((*message.order_details_comp().price()).mantissa(), (*message.order_details_comp().price()).exponent()) : canonical::absent());
    }

    void on(const protocol::TesTradeReport& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.testradereport";
        values[entry + ".payload.testradereport.securityid"] = (message.security_id().has_value() ? canonical::number((*message.security_id())) : canonical::absent());
        values[entry + ".payload.testradereport.transacttime"] = (message.transact_time().has_value() ? canonical::number((*message.transact_time())) : canonical::absent());
        values[entry + ".payload.testradereport.lastqty"] = (message.last_qty().has_value() ? canonical::scaled((*message.last_qty()).mantissa(), (*message.last_qty()).exponent()) : canonical::absent());
        values[entry + ".payload.testradereport.lastpx"] = (message.last_px().has_value() ? canonical::scaled((*message.last_px()).mantissa(), (*message.last_px()).exponent()) : canonical::absent());
        values[entry + ".payload.testradereport.trdmatchid"] = (message.trd_match_id().has_value() ? canonical::number((*message.trd_match_id())) : canonical::absent());
        values[entry + ".payload.testradereport.trdtype"] = (message.trd_type().has_value() ? canonical::number((*message.trd_type())) : canonical::absent());
        values[entry + ".payload.testradereport.tradecondition"] = (message.trade_condition().has_value() ? canonical::number((*message.trade_condition())) : canonical::absent());
        values[entry + ".payload.testradereport.multilegreportingtype"] = (message.multi_leg_reporting_type().has_value() ? canonical::number((*message.multi_leg_reporting_type())) : canonical::absent());
        values[entry + ".payload.testradereport.multilegpricemodel"] = (message.multi_leg_price_model().has_value() ? canonical::number((*message.multi_leg_price_model())) : canonical::absent());
        values[entry + ".payload.testradereport.nondisclosedtradevolume"] = (message.non_disclosed_trade_volume().has_value() ? canonical::scaled((*message.non_disclosed_trade_volume()).mantissa(), (*message.non_disclosed_trade_volume()).exponent()) : canonical::absent());
        values[entry + ".payload.testradereport.transbkdtime"] = (message.trans_bkd_time().has_value() ? canonical::number((*message.trans_bkd_time())) : canonical::absent());
        values[entry + ".payload.testradereport.numberofbuysides"] = (message.number_of_buy_sides().has_value() ? canonical::number((*message.number_of_buy_sides())) : canonical::absent());
        values[entry + ".payload.testradereport.numberofsellsides"] = (message.number_of_sell_sides().has_value() ? canonical::number((*message.number_of_sell_sides())) : canonical::absent());
    }

    void on(const protocol::TopOfBook& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.topofbook";
        values[entry + ".payload.topofbook.transacttime"] = (message.transact_time().has_value() ? canonical::number((*message.transact_time())) : canonical::absent());
        values[entry + ".payload.topofbook.securityid"] = (message.security_id().has_value() ? canonical::number((*message.security_id())) : canonical::absent());
        values[entry + ".payload.topofbook.bidpx"] = (message.bid_px().has_value() ? canonical::scaled((*message.bid_px()).mantissa(), (*message.bid_px()).exponent()) : canonical::absent());
        values[entry + ".payload.topofbook.offerpx"] = (message.offer_px().has_value() ? canonical::scaled((*message.offer_px()).mantissa(), (*message.offer_px()).exponent()) : canonical::absent());
        values[entry + ".payload.topofbook.bidsize"] = (message.bid_size().has_value() ? canonical::scaled((*message.bid_size()).mantissa(), (*message.bid_size()).exponent()) : canonical::absent());
        values[entry + ".payload.topofbook.offersize"] = (message.offer_size().has_value() ? canonical::scaled((*message.offer_size()).mantissa(), (*message.offer_size()).exponent()) : canonical::absent());
        values[entry + ".payload.topofbook.numberofbuyorders"] = (message.number_of_buy_orders().has_value() ? canonical::number((*message.number_of_buy_orders())) : canonical::absent());
        values[entry + ".payload.topofbook.numberofsellorders"] = (message.number_of_sell_orders().has_value() ? canonical::number((*message.number_of_sell_orders())) : canonical::absent());
    }

    void on(const protocol::TradeReport& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.tradereport";
        values[entry + ".payload.tradereport.securityid"] = (message.security_id().has_value() ? canonical::number((*message.security_id())) : canonical::absent());
        values[entry + ".payload.tradereport.transacttime"] = (message.transact_time().has_value() ? canonical::number((*message.transact_time())) : canonical::absent());
        values[entry + ".payload.tradereport.lastqty"] = (message.last_qty().has_value() ? canonical::scaled((*message.last_qty()).mantissa(), (*message.last_qty()).exponent()) : canonical::absent());
        values[entry + ".payload.tradereport.lastpx"] = (message.last_px().has_value() ? canonical::scaled((*message.last_px()).mantissa(), (*message.last_px()).exponent()) : canonical::absent());
        values[entry + ".payload.tradereport.trdmatchid"] = (message.trd_match_id().has_value() ? canonical::number((*message.trd_match_id())) : canonical::absent());
        values[entry + ".payload.tradereport.matchtype"] = (message.match_type().has_value() ? canonical::number((*message.match_type())) : canonical::absent());
        values[entry + ".payload.tradereport.matchsubtype"] = (message.match_sub_type().has_value() ? canonical::number((*message.match_sub_type())) : canonical::absent());
        values[entry + ".payload.tradereport.algorithmictradeindicator"] = (message.algorithmic_trade_indicator().has_value() ? canonical::number((*message.algorithmic_trade_indicator())) : canonical::absent());
        values[entry + ".payload.tradereport.tradecondition"] = (message.trade_condition().has_value() ? canonical::number((*message.trade_condition())) : canonical::absent());
    }

    void on(const protocol::TradeReversal& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.tradereversal";
        values[entry + ".payload.tradereversal.securityid"] = (message.security_id().has_value() ? canonical::number((*message.security_id())) : canonical::absent());
        values[entry + ".payload.tradereversal.transacttime"] = (message.transact_time().has_value() ? canonical::number((*message.transact_time())) : canonical::absent());
        values[entry + ".payload.tradereversal.lastqty"] = (message.last_qty().has_value() ? canonical::scaled((*message.last_qty()).mantissa(), (*message.last_qty()).exponent()) : canonical::absent());
        values[entry + ".payload.tradereversal.lastpx"] = (message.last_px().has_value() ? canonical::scaled((*message.last_px()).mantissa(), (*message.last_px()).exponent()) : canonical::absent());
        values[entry + ".payload.tradereversal.trdregtsexecutiontime"] = (message.trd_reg_ts_execution_time().has_value() ? canonical::number((*message.trd_reg_ts_execution_time())) : canonical::absent());
        values[entry + ".payload.tradereversal.trdmatchid"] = (message.trd_match_id().has_value() ? canonical::number((*message.trd_match_id())) : canonical::absent());
        values[entry + ".payload.tradereversal.tradecondition"] = (message.trade_condition().has_value() ? canonical::number((*message.trade_condition())) : canonical::absent());
        values[entry + ".payload.tradereversal.mdorigintype"] = (message.md_origin_type().has_value() ? canonical::number((*message.md_origin_type())) : canonical::absent());
        values[entry + ".payload.tradereversal.nomdentries"] = (message.no_md_entries().has_value() ? canonical::number((*message.no_md_entries())) : canonical::absent());
    }
};

// The values the Flyweight reader reads from one datagram, by indexed address. A datagram it cannot
// read is a value the model never reads, so it fails rather than passing with nothing compared.
canonical::Listing read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::PacketReader::read(std::span<const std::byte>(frame.payload, frame.payload_len), reader);
    } catch (const protocol::DecodeError& error) {
        reader.values["(does not decode)"] = error.what();
    }

    return reader.values;
}

// Read each datagram of a sample with Flyweight and hold it to the model's values
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
    std::printf("== Eurex.T7.Eobi.Fbe.v13.0 (flyweight values)\n");
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
