// Eurex.T7.Eobi.Fbe.v3.0 canonical values, through the Classes Packet: every value Classes decodes from
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
#include "cpp/binary/classes/eurex/t7/eobi/fbe/v3.0/definitions.hpp"

namespace protocol = ::eurex::t7::eobi::fbe::v3_0;

namespace {

// The values the Classes Packet decodes from one datagram, by indexed address. A datagram it cannot
// decode is a value the model never reads, so it fails rather than passing with nothing compared.
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::Packet packet;

    try {
        packet.decode(frame.payload, frame.payload_len);
    } catch (const protocol::DecodeError& error) {
        values["(does not decode)"] = error.what();
        return values;
    }

    values["packet.packetheader.eobiheader.bodylen"] = canonical::number(packet.packet_header().eobi_header().body_len());
    values["packet.packetheader.eobiheader.templateid"] = canonical::number(packet.packet_header().eobi_header().template_id());
    values["packet.packetheader.eobiheader.msgseqnum"] = canonical::number(packet.packet_header().eobi_header().msg_seq_num());
    values["packet.packetheader.applseqnum"] = canonical::number(packet.packet_header().appl_seq_num());
    values["packet.packetheader.marketsegmentid"] = (packet.packet_header().market_segment_id().has_value() ? canonical::number((*packet.packet_header().market_segment_id())) : canonical::absent());
    values["packet.packetheader.partitionid"] = (packet.packet_header().partition_id().has_value() ? canonical::number((*packet.packet_header().partition_id())) : canonical::absent());
    values["packet.packetheader.completionindicator"] = (packet.packet_header().completion_indicator().has_value() ? canonical::number((*packet.packet_header().completion_indicator())) : canonical::absent());
    values["packet.packetheader.applseqresetindicator"] = (packet.packet_header().appl_seq_reset_indicator().has_value() ? canonical::number((*packet.packet_header().appl_seq_reset_indicator())) : canonical::absent());
    values["packet.packetheader.transacttime"] = (packet.packet_header().transact_time().has_value() ? canonical::number((*packet.packet_header().transact_time())) : canonical::absent());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheadercomp.bodylen"] = canonical::number(each.message_header_comp().body_len());
        values[entry + ".messageheadercomp.templateid"] = canonical::number(each.message_header_comp().template_id());
        values[entry + ".messageheadercomp.msgseqnum"] = canonical::number(each.message_header_comp().msg_seq_num());

        if (const auto* message = dynamic_cast<const protocol::AddComplexInstrument*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.addcomplexinstrument";
            values[entry + ".payload.addcomplexinstrument.securityid"] = ((*message).security_id().has_value() ? canonical::number((*(*message).security_id())) : canonical::absent());
            values[entry + ".payload.addcomplexinstrument.transacttime"] = ((*message).transact_time().has_value() ? canonical::number((*(*message).transact_time())) : canonical::absent());
            values[entry + ".payload.addcomplexinstrument.securitysubtype"] = ((*message).security_sub_type().has_value() ? canonical::number((*(*message).security_sub_type())) : canonical::absent());
            values[entry + ".payload.addcomplexinstrument.productcomplex"] = ((*message).product_complex().has_value() ? canonical::number((*(*message).product_complex())) : canonical::absent());
            values[entry + ".payload.addcomplexinstrument.impliedmarketindicator"] = ((*message).implied_market_indicator().has_value() ? canonical::number((*(*message).implied_market_indicator())) : canonical::absent());
            values[entry + ".payload.addcomplexinstrument.nolegs"] = ((*message).no_legs().has_value() ? canonical::number((*(*message).no_legs())) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::AuctionBbo*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.auctionbbo";
            values[entry + ".payload.auctionbbo.transacttime"] = ((*message).transact_time().has_value() ? canonical::number((*(*message).transact_time())) : canonical::absent());
            values[entry + ".payload.auctionbbo.securityid"] = ((*message).security_id().has_value() ? canonical::number((*(*message).security_id())) : canonical::absent());
            values[entry + ".payload.auctionbbo.bidpx"] = ((*message).bid_px().has_value() ? canonical::scaled((*(*message).bid_px()).mantissa(), (*(*message).bid_px()).exponent()) : canonical::absent());
            values[entry + ".payload.auctionbbo.offerpx"] = ((*message).offer_px().has_value() ? canonical::scaled((*(*message).offer_px()).mantissa(), (*(*message).offer_px()).exponent()) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::AuctionClearingPrice*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.auctionclearingprice";
            values[entry + ".payload.auctionclearingprice.transacttime"] = ((*message).transact_time().has_value() ? canonical::number((*(*message).transact_time())) : canonical::absent());
            values[entry + ".payload.auctionclearingprice.securityid"] = ((*message).security_id().has_value() ? canonical::number((*(*message).security_id())) : canonical::absent());
            values[entry + ".payload.auctionclearingprice.lastpx"] = ((*message).last_px().has_value() ? canonical::scaled((*(*message).last_px()).mantissa(), (*(*message).last_px()).exponent()) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::CrossRequest*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.crossrequest";
            values[entry + ".payload.crossrequest.securityid"] = ((*message).security_id().has_value() ? canonical::number((*(*message).security_id())) : canonical::absent());
            values[entry + ".payload.crossrequest.lastqty"] = ((*message).last_qty().has_value() ? canonical::number((*(*message).last_qty())) : canonical::absent());
            values[entry + ".payload.crossrequest.transacttime"] = ((*message).transact_time().has_value() ? canonical::number((*(*message).transact_time())) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::ExecutionSummary*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.executionsummary";
            values[entry + ".payload.executionsummary.securityid"] = ((*message).security_id().has_value() ? canonical::number((*(*message).security_id())) : canonical::absent());
            values[entry + ".payload.executionsummary.aggressortimestamp"] = ((*message).aggressor_timestamp().has_value() ? canonical::number((*(*message).aggressor_timestamp())) : canonical::absent());
            values[entry + ".payload.executionsummary.requesttime"] = ((*message).request_time().has_value() ? canonical::number((*(*message).request_time())) : canonical::absent());
            values[entry + ".payload.executionsummary.execid"] = ((*message).exec_id().has_value() ? canonical::number((*(*message).exec_id())) : canonical::absent());
            values[entry + ".payload.executionsummary.lastqty"] = ((*message).last_qty().has_value() ? canonical::number((*(*message).last_qty())) : canonical::absent());
            values[entry + ".payload.executionsummary.aggressorside"] = ((*message).aggressor_side().has_value() ? canonical::number((*(*message).aggressor_side())) : canonical::absent());
            values[entry + ".payload.executionsummary.tradecondition"] = ((*message).trade_condition().has_value() ? canonical::number((*(*message).trade_condition())) : canonical::absent());
            values[entry + ".payload.executionsummary.lastpx"] = ((*message).last_px().has_value() ? canonical::scaled((*(*message).last_px()).mantissa(), (*(*message).last_px()).exponent()) : canonical::absent());
            values[entry + ".payload.executionsummary.restinghiddenqty"] = ((*message).resting_hidden_qty().has_value() ? canonical::number((*(*message).resting_hidden_qty())) : canonical::absent());
            values[entry + ".payload.executionsummary.restingcxlqty"] = ((*message).resting_cxl_qty().has_value() ? canonical::number((*(*message).resting_cxl_qty())) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::FullOrderExecution*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.fullorderexecution";
            values[entry + ".payload.fullorderexecution.side"] = ((*message).side().has_value() ? canonical::number((*(*message).side())) : canonical::absent());
            values[entry + ".payload.fullorderexecution.price"] = ((*message).price().has_value() ? canonical::scaled((*(*message).price()).mantissa(), (*(*message).price()).exponent()) : canonical::absent());
            values[entry + ".payload.fullorderexecution.trdregtstimepriority"] = ((*message).trd_reg_ts_time_priority().has_value() ? canonical::number((*(*message).trd_reg_ts_time_priority())) : canonical::absent());
            values[entry + ".payload.fullorderexecution.securityid"] = ((*message).security_id().has_value() ? canonical::number((*(*message).security_id())) : canonical::absent());
            values[entry + ".payload.fullorderexecution.trdmatchid"] = ((*message).trd_match_id().has_value() ? canonical::number((*(*message).trd_match_id())) : canonical::absent());
            values[entry + ".payload.fullorderexecution.lastqty"] = ((*message).last_qty().has_value() ? canonical::number((*(*message).last_qty())) : canonical::absent());
            values[entry + ".payload.fullorderexecution.lastpx"] = ((*message).last_px().has_value() ? canonical::scaled((*(*message).last_px()).mantissa(), (*(*message).last_px()).exponent()) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::Heartbeat*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.heartbeat";
            values[entry + ".payload.heartbeat.lastmsgseqnumprocessed"] = ((*message).last_msg_seq_num_processed().has_value() ? canonical::number((*(*message).last_msg_seq_num_processed())) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::InstrumentStateChange*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.instrumentstatechange";
            values[entry + ".payload.instrumentstatechange.securityid"] = ((*message).security_id().has_value() ? canonical::number((*(*message).security_id())) : canonical::absent());
            values[entry + ".payload.instrumentstatechange.securitystatus"] = ((*message).security_status().has_value() ? canonical::number((*(*message).security_status())) : canonical::absent());
            values[entry + ".payload.instrumentstatechange.securitytradingstatus"] = ((*message).security_trading_status().has_value() ? canonical::number((*(*message).security_trading_status())) : canonical::absent());
            values[entry + ".payload.instrumentstatechange.fastmarketindicator"] = ((*message).fast_market_indicator().has_value() ? canonical::number((*(*message).fast_market_indicator())) : canonical::absent());
            values[entry + ".payload.instrumentstatechange.transacttime"] = ((*message).transact_time().has_value() ? canonical::number((*(*message).transact_time())) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::InstrumentSummary*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.instrumentsummary";
            values[entry + ".payload.instrumentsummary.securityid"] = ((*message).security_id().has_value() ? canonical::number((*(*message).security_id())) : canonical::absent());
            values[entry + ".payload.instrumentsummary.lastupdatetime"] = ((*message).last_update_time().has_value() ? canonical::number((*(*message).last_update_time())) : canonical::absent());
            values[entry + ".payload.instrumentsummary.trdregtsexecutiontime"] = ((*message).trd_reg_ts_execution_time().has_value() ? canonical::number((*(*message).trd_reg_ts_execution_time())) : canonical::absent());
            values[entry + ".payload.instrumentsummary.totnoorders"] = ((*message).tot_no_orders().has_value() ? canonical::number((*(*message).tot_no_orders())) : canonical::absent());
            values[entry + ".payload.instrumentsummary.securitystatus"] = ((*message).security_status().has_value() ? canonical::number((*(*message).security_status())) : canonical::absent());
            values[entry + ".payload.instrumentsummary.securitytradingstatus"] = ((*message).security_trading_status().has_value() ? canonical::number((*(*message).security_trading_status())) : canonical::absent());
            values[entry + ".payload.instrumentsummary.fastmarketindicator"] = ((*message).fast_market_indicator().has_value() ? canonical::number((*(*message).fast_market_indicator())) : canonical::absent());
            values[entry + ".payload.instrumentsummary.nomdentries"] = ((*message).no_md_entries().has_value() ? canonical::number((*(*message).no_md_entries())) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::OrderAdd*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.orderadd";
            values[entry + ".payload.orderadd.trdregtstimein"] = ((*message).trd_reg_ts_time_in().has_value() ? canonical::number((*(*message).trd_reg_ts_time_in())) : canonical::absent());
            values[entry + ".payload.orderadd.securityid"] = ((*message).security_id().has_value() ? canonical::number((*(*message).security_id())) : canonical::absent());
            values[entry + ".payload.orderadd.orderdetailscomp.trdregtstimepriority"] = ((*message).order_details_comp().trd_reg_ts_time_priority().has_value() ? canonical::number((*(*message).order_details_comp().trd_reg_ts_time_priority())) : canonical::absent());
            values[entry + ".payload.orderadd.orderdetailscomp.displayqty"] = ((*message).order_details_comp().display_qty().has_value() ? canonical::number((*(*message).order_details_comp().display_qty())) : canonical::absent());
            values[entry + ".payload.orderadd.orderdetailscomp.side"] = ((*message).order_details_comp().side().has_value() ? canonical::number((*(*message).order_details_comp().side())) : canonical::absent());
            values[entry + ".payload.orderadd.orderdetailscomp.price"] = ((*message).order_details_comp().price().has_value() ? canonical::scaled((*(*message).order_details_comp().price()).mantissa(), (*(*message).order_details_comp().price()).exponent()) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::OrderDelete*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.orderdelete";
            values[entry + ".payload.orderdelete.trdregtstimein"] = ((*message).trd_reg_ts_time_in().has_value() ? canonical::number((*(*message).trd_reg_ts_time_in())) : canonical::absent());
            values[entry + ".payload.orderdelete.transacttime"] = ((*message).transact_time().has_value() ? canonical::number((*(*message).transact_time())) : canonical::absent());
            values[entry + ".payload.orderdelete.securityid"] = ((*message).security_id().has_value() ? canonical::number((*(*message).security_id())) : canonical::absent());
            values[entry + ".payload.orderdelete.orderdetailscomp.trdregtstimepriority"] = ((*message).order_details_comp().trd_reg_ts_time_priority().has_value() ? canonical::number((*(*message).order_details_comp().trd_reg_ts_time_priority())) : canonical::absent());
            values[entry + ".payload.orderdelete.orderdetailscomp.displayqty"] = ((*message).order_details_comp().display_qty().has_value() ? canonical::number((*(*message).order_details_comp().display_qty())) : canonical::absent());
            values[entry + ".payload.orderdelete.orderdetailscomp.side"] = ((*message).order_details_comp().side().has_value() ? canonical::number((*(*message).order_details_comp().side())) : canonical::absent());
            values[entry + ".payload.orderdelete.orderdetailscomp.price"] = ((*message).order_details_comp().price().has_value() ? canonical::scaled((*(*message).order_details_comp().price()).mantissa(), (*(*message).order_details_comp().price()).exponent()) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::OrderMassDelete*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.ordermassdelete";
            values[entry + ".payload.ordermassdelete.securityid"] = ((*message).security_id().has_value() ? canonical::number((*(*message).security_id())) : canonical::absent());
            values[entry + ".payload.ordermassdelete.transacttime"] = ((*message).transact_time().has_value() ? canonical::number((*(*message).transact_time())) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::OrderModify*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.ordermodify";
            values[entry + ".payload.ordermodify.trdregtstimein"] = ((*message).trd_reg_ts_time_in().has_value() ? canonical::number((*(*message).trd_reg_ts_time_in())) : canonical::absent());
            values[entry + ".payload.ordermodify.trdregtsprevtimepriority"] = ((*message).trd_reg_ts_prev_time_priority().has_value() ? canonical::number((*(*message).trd_reg_ts_prev_time_priority())) : canonical::absent());
            values[entry + ".payload.ordermodify.prevprice"] = ((*message).prev_price().has_value() ? canonical::scaled((*(*message).prev_price()).mantissa(), (*(*message).prev_price()).exponent()) : canonical::absent());
            values[entry + ".payload.ordermodify.prevdisplayqty"] = ((*message).prev_display_qty().has_value() ? canonical::number((*(*message).prev_display_qty())) : canonical::absent());
            values[entry + ".payload.ordermodify.securityid"] = ((*message).security_id().has_value() ? canonical::number((*(*message).security_id())) : canonical::absent());
            values[entry + ".payload.ordermodify.orderdetailscomp.trdregtstimepriority"] = ((*message).order_details_comp().trd_reg_ts_time_priority().has_value() ? canonical::number((*(*message).order_details_comp().trd_reg_ts_time_priority())) : canonical::absent());
            values[entry + ".payload.ordermodify.orderdetailscomp.displayqty"] = ((*message).order_details_comp().display_qty().has_value() ? canonical::number((*(*message).order_details_comp().display_qty())) : canonical::absent());
            values[entry + ".payload.ordermodify.orderdetailscomp.side"] = ((*message).order_details_comp().side().has_value() ? canonical::number((*(*message).order_details_comp().side())) : canonical::absent());
            values[entry + ".payload.ordermodify.orderdetailscomp.price"] = ((*message).order_details_comp().price().has_value() ? canonical::scaled((*(*message).order_details_comp().price()).mantissa(), (*(*message).order_details_comp().price()).exponent()) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::OrderModifySamePrio*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.ordermodifysameprio";
            values[entry + ".payload.ordermodifysameprio.trdregtstimein"] = ((*message).trd_reg_ts_time_in().has_value() ? canonical::number((*(*message).trd_reg_ts_time_in())) : canonical::absent());
            values[entry + ".payload.ordermodifysameprio.transacttime"] = ((*message).transact_time().has_value() ? canonical::number((*(*message).transact_time())) : canonical::absent());
            values[entry + ".payload.ordermodifysameprio.prevdisplayqty"] = ((*message).prev_display_qty().has_value() ? canonical::number((*(*message).prev_display_qty())) : canonical::absent());
            values[entry + ".payload.ordermodifysameprio.securityid"] = ((*message).security_id().has_value() ? canonical::number((*(*message).security_id())) : canonical::absent());
            values[entry + ".payload.ordermodifysameprio.orderdetailscomp.trdregtstimepriority"] = ((*message).order_details_comp().trd_reg_ts_time_priority().has_value() ? canonical::number((*(*message).order_details_comp().trd_reg_ts_time_priority())) : canonical::absent());
            values[entry + ".payload.ordermodifysameprio.orderdetailscomp.displayqty"] = ((*message).order_details_comp().display_qty().has_value() ? canonical::number((*(*message).order_details_comp().display_qty())) : canonical::absent());
            values[entry + ".payload.ordermodifysameprio.orderdetailscomp.side"] = ((*message).order_details_comp().side().has_value() ? canonical::number((*(*message).order_details_comp().side())) : canonical::absent());
            values[entry + ".payload.ordermodifysameprio.orderdetailscomp.price"] = ((*message).order_details_comp().price().has_value() ? canonical::scaled((*(*message).order_details_comp().price()).mantissa(), (*(*message).order_details_comp().price()).exponent()) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::PartialOrderExecution*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.partialorderexecution";
            values[entry + ".payload.partialorderexecution.side"] = ((*message).side().has_value() ? canonical::number((*(*message).side())) : canonical::absent());
            values[entry + ".payload.partialorderexecution.price"] = ((*message).price().has_value() ? canonical::scaled((*(*message).price()).mantissa(), (*(*message).price()).exponent()) : canonical::absent());
            values[entry + ".payload.partialorderexecution.trdregtstimepriority"] = ((*message).trd_reg_ts_time_priority().has_value() ? canonical::number((*(*message).trd_reg_ts_time_priority())) : canonical::absent());
            values[entry + ".payload.partialorderexecution.securityid"] = ((*message).security_id().has_value() ? canonical::number((*(*message).security_id())) : canonical::absent());
            values[entry + ".payload.partialorderexecution.trdmatchid"] = ((*message).trd_match_id().has_value() ? canonical::number((*(*message).trd_match_id())) : canonical::absent());
            values[entry + ".payload.partialorderexecution.lastqty"] = ((*message).last_qty().has_value() ? canonical::number((*(*message).last_qty())) : canonical::absent());
            values[entry + ".payload.partialorderexecution.lastpx"] = ((*message).last_px().has_value() ? canonical::scaled((*(*message).last_px()).mantissa(), (*(*message).last_px()).exponent()) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::ProductStateChange*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.productstatechange";
            values[entry + ".payload.productstatechange.tradingsessionid"] = ((*message).trading_session_id().has_value() ? canonical::number((*(*message).trading_session_id())) : canonical::absent());
            values[entry + ".payload.productstatechange.tradingsessionsubid"] = ((*message).trading_session_sub_id().has_value() ? canonical::number((*(*message).trading_session_sub_id())) : canonical::absent());
            values[entry + ".payload.productstatechange.tradsesstatus"] = ((*message).trad_ses_status().has_value() ? canonical::number((*(*message).trad_ses_status())) : canonical::absent());
            values[entry + ".payload.productstatechange.fastmarketindicator"] = ((*message).fast_market_indicator().has_value() ? canonical::number((*(*message).fast_market_indicator())) : canonical::absent());
            values[entry + ".payload.productstatechange.transacttime"] = ((*message).transact_time().has_value() ? canonical::number((*(*message).transact_time())) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::ProductSummary*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.productsummary";
            values[entry + ".payload.productsummary.lastmsgseqnumprocessed"] = ((*message).last_msg_seq_num_processed().has_value() ? canonical::number((*(*message).last_msg_seq_num_processed())) : canonical::absent());
            values[entry + ".payload.productsummary.tradingsessionid"] = ((*message).trading_session_id().has_value() ? canonical::number((*(*message).trading_session_id())) : canonical::absent());
            values[entry + ".payload.productsummary.tradingsessionsubid"] = ((*message).trading_session_sub_id().has_value() ? canonical::number((*(*message).trading_session_sub_id())) : canonical::absent());
            values[entry + ".payload.productsummary.tradsesstatus"] = ((*message).trad_ses_status().has_value() ? canonical::number((*(*message).trad_ses_status())) : canonical::absent());
            values[entry + ".payload.productsummary.fastmarketindicator"] = ((*message).fast_market_indicator().has_value() ? canonical::number((*(*message).fast_market_indicator())) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::QuoteRequest*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.quoterequest";
            values[entry + ".payload.quoterequest.securityid"] = ((*message).security_id().has_value() ? canonical::number((*(*message).security_id())) : canonical::absent());
            values[entry + ".payload.quoterequest.lastqty"] = ((*message).last_qty().has_value() ? canonical::number((*(*message).last_qty())) : canonical::absent());
            values[entry + ".payload.quoterequest.side"] = ((*message).side().has_value() ? canonical::number((*(*message).side())) : canonical::absent());
            values[entry + ".payload.quoterequest.transacttime"] = ((*message).transact_time().has_value() ? canonical::number((*(*message).transact_time())) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::SnapshotOrder*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.snapshotorder";
            values[entry + ".payload.snapshotorder.orderdetailscomp.trdregtstimepriority"] = ((*message).order_details_comp().trd_reg_ts_time_priority().has_value() ? canonical::number((*(*message).order_details_comp().trd_reg_ts_time_priority())) : canonical::absent());
            values[entry + ".payload.snapshotorder.orderdetailscomp.displayqty"] = ((*message).order_details_comp().display_qty().has_value() ? canonical::number((*(*message).order_details_comp().display_qty())) : canonical::absent());
            values[entry + ".payload.snapshotorder.orderdetailscomp.side"] = ((*message).order_details_comp().side().has_value() ? canonical::number((*(*message).order_details_comp().side())) : canonical::absent());
            values[entry + ".payload.snapshotorder.orderdetailscomp.price"] = ((*message).order_details_comp().price().has_value() ? canonical::scaled((*(*message).order_details_comp().price()).mantissa(), (*(*message).order_details_comp().price()).exponent()) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::TopOfBook*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.topofbook";
            values[entry + ".payload.topofbook.transacttime"] = ((*message).transact_time().has_value() ? canonical::number((*(*message).transact_time())) : canonical::absent());
            values[entry + ".payload.topofbook.securityid"] = ((*message).security_id().has_value() ? canonical::number((*(*message).security_id())) : canonical::absent());
            values[entry + ".payload.topofbook.bidpx"] = ((*message).bid_px().has_value() ? canonical::scaled((*(*message).bid_px()).mantissa(), (*(*message).bid_px()).exponent()) : canonical::absent());
            values[entry + ".payload.topofbook.offerpx"] = ((*message).offer_px().has_value() ? canonical::scaled((*(*message).offer_px()).mantissa(), (*(*message).offer_px()).exponent()) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::TradeReport*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.tradereport";
            values[entry + ".payload.tradereport.securityid"] = ((*message).security_id().has_value() ? canonical::number((*(*message).security_id())) : canonical::absent());
            values[entry + ".payload.tradereport.transacttime"] = ((*message).transact_time().has_value() ? canonical::number((*(*message).transact_time())) : canonical::absent());
            values[entry + ".payload.tradereport.trdmatchid"] = ((*message).trd_match_id().has_value() ? canonical::number((*(*message).trd_match_id())) : canonical::absent());
            values[entry + ".payload.tradereport.lastqty"] = ((*message).last_qty().has_value() ? canonical::number((*(*message).last_qty())) : canonical::absent());
            values[entry + ".payload.tradereport.lastpx"] = ((*message).last_px().has_value() ? canonical::scaled((*(*message).last_px()).mantissa(), (*(*message).last_px()).exponent()) : canonical::absent());
            values[entry + ".payload.tradereport.matchtype"] = ((*message).match_type().has_value() ? canonical::number((*(*message).match_type())) : canonical::absent());
            values[entry + ".payload.tradereport.matchsubtype"] = ((*message).match_sub_type().has_value() ? canonical::number((*(*message).match_sub_type())) : canonical::absent());
        } else if (const auto* message = dynamic_cast<const protocol::TradeReversal*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.tradereversal";
            values[entry + ".payload.tradereversal.securityid"] = ((*message).security_id().has_value() ? canonical::number((*(*message).security_id())) : canonical::absent());
            values[entry + ".payload.tradereversal.transacttime"] = ((*message).transact_time().has_value() ? canonical::number((*(*message).transact_time())) : canonical::absent());
            values[entry + ".payload.tradereversal.trdmatchid"] = ((*message).trd_match_id().has_value() ? canonical::number((*(*message).trd_match_id())) : canonical::absent());
            values[entry + ".payload.tradereversal.lastqty"] = ((*message).last_qty().has_value() ? canonical::number((*(*message).last_qty())) : canonical::absent());
            values[entry + ".payload.tradereversal.lastpx"] = ((*message).last_px().has_value() ? canonical::scaled((*(*message).last_px()).mantissa(), (*(*message).last_px()).exponent()) : canonical::absent());
            values[entry + ".payload.tradereversal.trdregtsexecutiontime"] = ((*message).trd_reg_ts_execution_time().has_value() ? canonical::number((*(*message).trd_reg_ts_execution_time())) : canonical::absent());
            values[entry + ".payload.tradereversal.nomdentries"] = ((*message).no_md_entries().has_value() ? canonical::number((*(*message).no_md_entries())) : canonical::absent());
        }
    }

    return values;
}

// Read each datagram of a sample with Classes and hold it to the model's values
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
    std::printf("== Eurex.T7.Eobi.Fbe.v3.0 (classes values)\n");
    int failures = 0;
    failures += check("Heartbeat", "Eurex/T7.Eobi.Fbe.v3.0/Heartbeat.pcap", "eurex/t7/eobi/fbe/v3.0/Heartbeat.values");
    failures += check("OrderAdd", "Eurex/T7.Eobi.Fbe.v3.0/OrderAdd.pcap", "eurex/t7/eobi/fbe/v3.0/OrderAdd.values");
    failures += check("SnapshotOrder", "Eurex/T7.Eobi.Fbe.v3.0/SnapshotOrder.pcap", "eurex/t7/eobi/fbe/v3.0/SnapshotOrder.values");
    return failures == 0 ? 0 : 1;
}
