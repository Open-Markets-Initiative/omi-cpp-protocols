// Nyse.ArcaOptions.DeepFeed.Pillar.v1.2.m canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/binary/modern/nyse/arcaoptions/deepfeed/pillar/v1.2.m/definitions.hpp"

namespace protocol = ::nyse::arcaoptions::deepfeed::pillar::v1_2_m;

namespace {

// The values the Modern iterator reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    values["packet.packetheader.pktsize"] = canonical::number(iterator.packet_header->pkt_size.get());
    values["packet.packetheader.deliveryflag"] = canonical::number(iterator.packet_header->delivery_flag.get());
    values["packet.packetheader.numbermsgs"] = canonical::number(iterator.packet_header->number_msgs.get());
    values["packet.packetheader.seqnum"] = canonical::number(iterator.packet_header->seq_num.get());
    values["packet.packetheader.sendtime.seconds"] = canonical::number(iterator.packet_header->send_time.seconds.get());
    values["packet.packetheader.sendtime.nanoseconds"] = canonical::number(iterator.packet_header->send_time.nanoseconds.get());

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(iterator.message_header->message_size.get());
        values[entry + ".messageheader.messagetype"] = canonical::number(iterator.message_header->message_type.get());

        if (iterator.message_type == protocol::SequenceNumberResetMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.sequencenumberresetmessage";
            [[maybe_unused]] const auto* message = protocol::SequenceNumberResetMessage::parse(iterator.message);
            values[entry + ".payload.sequencenumberresetmessage.sourcetime"] = canonical::number(message->source_time.get());
            values[entry + ".payload.sequencenumberresetmessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.sequencenumberresetmessage.productid"] = canonical::number(message->product_id.get());
            values[entry + ".payload.sequencenumberresetmessage.channelid"] = canonical::number(message->channel_id.get());
        } else if (iterator.message_type == protocol::SourceTimeReferenceMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.sourcetimereferencemessage";
            [[maybe_unused]] const auto* message = protocol::SourceTimeReferenceMessage::parse(iterator.message);
            values[entry + ".payload.sourcetimereferencemessage.id"] = canonical::number(message->id.get());
            values[entry + ".payload.sourcetimereferencemessage.symbolseqnum"] = canonical::number(message->symbol_seq_num.get());
            values[entry + ".payload.sourcetimereferencemessage.sourcetime"] = canonical::number(message->source_time.get());
        } else if (iterator.message_type == protocol::SymbolIndexMappingMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.symbolindexmappingmessage";
            [[maybe_unused]] const auto* message = protocol::SymbolIndexMappingMessage::parse(iterator.message);
            values[entry + ".payload.symbolindexmappingmessage.symbolindex"] = canonical::number(message->symbol_index.get());
            values[entry + ".payload.symbolindexmappingmessage.symbol"] = canonical::text(std::string(message->symbol.get()), '\0', false);
            values[entry + ".payload.symbolindexmappingmessage.marketid"] = canonical::number(message->market_id.get());
            values[entry + ".payload.symbolindexmappingmessage.systemid"] = canonical::number(message->system_id.get());
            values[entry + ".payload.symbolindexmappingmessage.exchangecode"] = canonical::text(canonical::character(message->exchange_code.get()), '\0', false);
            values[entry + ".payload.symbolindexmappingmessage.pricescalecode"] = canonical::number(message->price_scale_code.get());
            values[entry + ".payload.symbolindexmappingmessage.securitytype"] = canonical::text(canonical::character(message->security_type.get()), '\0', false);
            values[entry + ".payload.symbolindexmappingmessage.lotsize"] = canonical::number(message->lot_size.get());
            values[entry + ".payload.symbolindexmappingmessage.prevcloseprice"] = canonical::number(message->prev_close_price.get());
            values[entry + ".payload.symbolindexmappingmessage.prevclosevolume"] = canonical::number(message->prev_close_volume.get());
            values[entry + ".payload.symbolindexmappingmessage.priceresolution"] = canonical::number(message->price_resolution.get());
            values[entry + ".payload.symbolindexmappingmessage.roundlot"] = canonical::text(canonical::character(message->round_lot.get()), '\0', false);
        } else if (iterator.message_type == protocol::SymbolClearMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.symbolclearmessage";
            [[maybe_unused]] const auto* message = protocol::SymbolClearMessage::parse(iterator.message);
            values[entry + ".payload.symbolclearmessage.sourcetime"] = canonical::number(message->source_time.get());
            values[entry + ".payload.symbolclearmessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.symbolclearmessage.symbolindex"] = canonical::number(message->symbol_index.get());
            values[entry + ".payload.symbolclearmessage.nextsourceseqnum"] = canonical::number(message->next_source_seq_num.get());
        } else if (iterator.message_type == protocol::SecurityStatusMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.securitystatusmessage";
            [[maybe_unused]] const auto* message = protocol::SecurityStatusMessage::parse(iterator.message);
            values[entry + ".payload.securitystatusmessage.sourcetime"] = canonical::number(message->source_time.get());
            values[entry + ".payload.securitystatusmessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.securitystatusmessage.symbolindex"] = canonical::number(message->symbol_index.get());
            values[entry + ".payload.securitystatusmessage.symbolseqnum"] = canonical::number(message->symbol_seq_num.get());
            values[entry + ".payload.securitystatusmessage.securitystatus"] = canonical::text(canonical::character(message->security_status.get()), '\0', false);
            values[entry + ".payload.securitystatusmessage.haltcondition"] = canonical::text(canonical::character(message->halt_condition.get()), '\0', false);
            values[entry + ".payload.securitystatusmessage.price1"] = canonical::number(message->price_1.get());
            values[entry + ".payload.securitystatusmessage.price2"] = canonical::number(message->price_2.get());
            values[entry + ".payload.securitystatusmessage.ssrtriggeringexchangeid"] = canonical::text(canonical::character(message->ssr_triggering_exchange_id.get()), '\0', false);
            values[entry + ".payload.securitystatusmessage.ssrtriggeringvolume"] = canonical::number(message->ssr_triggering_volume.get());
            values[entry + ".payload.securitystatusmessage.time"] = (static_cast<std::uint32_t>(message->time.get()) != 0x0U ? canonical::number(message->time.get()) : canonical::absent());
            values[entry + ".payload.securitystatusmessage.ssrstate"] = canonical::text(canonical::character(message->ssr_state.get()), '\0', false);
            values[entry + ".payload.securitystatusmessage.marketstate"] = canonical::text(canonical::character(message->market_state.get()), '\0', false);
            values[entry + ".payload.securitystatusmessage.sessionstate"] = canonical::text(canonical::character(message->session_state.get()), '\0', false);
        } else if (iterator.message_type == protocol::OutrightSeriesIndexMappingMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.outrightseriesindexmappingmessage";
            [[maybe_unused]] const auto* message = protocol::OutrightSeriesIndexMappingMessage::parse(iterator.message);
            values[entry + ".payload.outrightseriesindexmappingmessage.seriesindex"] = canonical::number(message->series_index.get());
            values[entry + ".payload.outrightseriesindexmappingmessage.seriestype"] = canonical::number(message->series_type.get());
            values[entry + ".payload.outrightseriesindexmappingmessage.marketid"] = canonical::number(message->market_id.get());
            values[entry + ".payload.outrightseriesindexmappingmessage.systemid"] = canonical::number(message->system_id.get());
            values[entry + ".payload.outrightseriesindexmappingmessage.optionsymbolroot"] = canonical::text(std::string(message->option_symbol_root.get()), '\0', false);
            values[entry + ".payload.outrightseriesindexmappingmessage.underlyingsymbol"] = canonical::text(std::string(message->underlying_symbol.get()), '\0', false);
            values[entry + ".payload.outrightseriesindexmappingmessage.underlyingindex"] = canonical::number(message->underlying_index.get());
            values[entry + ".payload.outrightseriesindexmappingmessage.pricescalecode"] = canonical::number(message->price_scale_code.get());
            values[entry + ".payload.outrightseriesindexmappingmessage.contractmultiplier"] = canonical::number(message->contract_multiplier.get());
            values[entry + ".payload.outrightseriesindexmappingmessage.maturitydate"] = canonical::text(std::string(message->maturity_date.get()), '\0', false);
            values[entry + ".payload.outrightseriesindexmappingmessage.putorcall"] = canonical::number(message->put_or_call.get());
            values[entry + ".payload.outrightseriesindexmappingmessage.strikeprice"] = canonical::text(std::string(message->strike_price.get()), '\0', false);
            values[entry + ".payload.outrightseriesindexmappingmessage.closingonlyindicator"] = canonical::text(canonical::character(message->closing_only_indicator.get()), '\0', false);
        } else if (iterator.message_type == protocol::OptionsStatusMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.optionsstatusmessage";
            [[maybe_unused]] const auto* message = protocol::OptionsStatusMessage::parse(iterator.message);
            values[entry + ".payload.optionsstatusmessage.sourcetime"] = canonical::number(message->source_time.get());
            values[entry + ".payload.optionsstatusmessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.optionsstatusmessage.seriesindex"] = canonical::number(message->series_index.get());
            values[entry + ".payload.optionsstatusmessage.seriesseqnum"] = canonical::number(message->series_seq_num.get());
            values[entry + ".payload.optionsstatusmessage.seriesstatus"] = canonical::text(canonical::character(message->series_status.get()), '\0', false);
            values[entry + ".payload.optionsstatusmessage.marketstate"] = canonical::text(canonical::character(message->market_state.get()), '\0', false);
            values[entry + ".payload.optionsstatusmessage.optionsstatushaltcondition"] = canonical::text(canonical::character(message->options_status_halt_condition.get()), '\0', false);
        } else if (iterator.message_type == protocol::ComplexSeriesIndexMappingMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.complexseriesindexmappingmessage";
            [[maybe_unused]] const auto* message = protocol::ComplexSeriesIndexMappingMessage::parse(iterator.message);
            values[entry + ".payload.complexseriesindexmappingmessage.seriesindex"] = canonical::number(message->series_index.get());
            values[entry + ".payload.complexseriesindexmappingmessage.marketid"] = canonical::number(message->market_id.get());
            values[entry + ".payload.complexseriesindexmappingmessage.systemid"] = canonical::number(message->system_id.get());
            values[entry + ".payload.complexseriesindexmappingmessage.nooflegs"] = canonical::number(message->no_of_legs.get());
        } else if (iterator.message_type == protocol::RetransmissionRequestMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.retransmissionrequestmessage";
            [[maybe_unused]] const auto* message = protocol::RetransmissionRequestMessage::parse(iterator.message);
            values[entry + ".payload.retransmissionrequestmessage.beginseqnum"] = canonical::number(message->begin_seq_num.get());
            values[entry + ".payload.retransmissionrequestmessage.endseqnum"] = canonical::number(message->end_seq_num.get());
            values[entry + ".payload.retransmissionrequestmessage.sourceid"] = canonical::text(std::string(message->source_id.get()), '\0', false);
            values[entry + ".payload.retransmissionrequestmessage.productid"] = canonical::number(message->product_id.get());
            values[entry + ".payload.retransmissionrequestmessage.channelid"] = canonical::number(message->channel_id.get());
        } else if (iterator.message_type == protocol::RefreshHeaderMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.refreshheadermessage";
            [[maybe_unused]] const auto* message = protocol::RefreshHeaderMessage::parse(iterator.message);
            values[entry + ".payload.refreshheadermessage.currentrefreshpkt"] = canonical::number(message->current_refresh_pkt.get());
            values[entry + ".payload.refreshheadermessage.totalrefreshpkts"] = canonical::number(message->total_refresh_pkts.get());
        } else if (iterator.message_type == protocol::RefreshRequestMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.refreshrequestmessage";
            [[maybe_unused]] const auto* message = protocol::RefreshRequestMessage::parse(iterator.message);
            values[entry + ".payload.refreshrequestmessage.symbolindex"] = canonical::number(message->symbol_index.get());
            values[entry + ".payload.refreshrequestmessage.sourceid"] = canonical::text(std::string(message->source_id.get()), '\0', false);
            values[entry + ".payload.refreshrequestmessage.productid"] = canonical::number(message->product_id.get());
            values[entry + ".payload.refreshrequestmessage.channelid"] = canonical::number(message->channel_id.get());
        } else if (iterator.message_type == protocol::SymbolIndexMappingRequestMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.symbolindexmappingrequestmessage";
            [[maybe_unused]] const auto* message = protocol::SymbolIndexMappingRequestMessage::parse(iterator.message);
            values[entry + ".payload.symbolindexmappingrequestmessage.symbolindex"] = canonical::number(message->symbol_index.get());
            values[entry + ".payload.symbolindexmappingrequestmessage.sourceid"] = canonical::text(std::string(message->source_id.get()), '\0', false);
            values[entry + ".payload.symbolindexmappingrequestmessage.productid"] = canonical::number(message->product_id.get());
            values[entry + ".payload.symbolindexmappingrequestmessage.channelid"] = canonical::number(message->channel_id.get());
            values[entry + ".payload.symbolindexmappingrequestmessage.retransmitmethod"] = canonical::number(message->retransmit_method.get());
        } else if (iterator.message_type == protocol::MessageUnavailableMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.messageunavailablemessage";
            [[maybe_unused]] const auto* message = protocol::MessageUnavailableMessage::parse(iterator.message);
            values[entry + ".payload.messageunavailablemessage.beginseqnum"] = canonical::number(message->begin_seq_num.get());
            values[entry + ".payload.messageunavailablemessage.endseqnum"] = canonical::number(message->end_seq_num.get());
            values[entry + ".payload.messageunavailablemessage.productid"] = canonical::number(message->product_id.get());
            values[entry + ".payload.messageunavailablemessage.channelid"] = canonical::number(message->channel_id.get());
        } else if (iterator.message_type == protocol::RequestResponseMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.requestresponsemessage";
            [[maybe_unused]] const auto* message = protocol::RequestResponseMessage::parse(iterator.message);
            values[entry + ".payload.requestresponsemessage.requestseqnum"] = canonical::number(message->request_seq_num.get());
            values[entry + ".payload.requestresponsemessage.beginseqnum"] = canonical::number(message->begin_seq_num.get());
            values[entry + ".payload.requestresponsemessage.endseqnum"] = canonical::number(message->end_seq_num.get());
            values[entry + ".payload.requestresponsemessage.sourceid"] = canonical::text(std::string(message->source_id.get()), '\0', false);
            values[entry + ".payload.requestresponsemessage.productid"] = canonical::number(message->product_id.get());
            values[entry + ".payload.requestresponsemessage.channelid"] = canonical::number(message->channel_id.get());
            values[entry + ".payload.requestresponsemessage.status"] = canonical::text(canonical::character(message->status.get()), '\0', false);
        } else if (iterator.message_type == protocol::HeartbeatResponseMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.heartbeatresponsemessage";
            [[maybe_unused]] const auto* message = protocol::HeartbeatResponseMessage::parse(iterator.message);
            values[entry + ".payload.heartbeatresponsemessage.sourceid"] = canonical::text(std::string(message->source_id.get()), '\0', false);
        } else if (iterator.message_type == protocol::OptionsAddOrderMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.optionsaddordermessage";
            [[maybe_unused]] const auto* message = protocol::OptionsAddOrderMessage::parse(iterator.message);
            values[entry + ".payload.optionsaddordermessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.optionsaddordermessage.seriesindex"] = canonical::number(message->series_index.get());
            values[entry + ".payload.optionsaddordermessage.seriesseqnum"] = canonical::number(message->series_seq_num.get());
            values[entry + ".payload.optionsaddordermessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.optionsaddordermessage.price"] = canonical::number(message->price.get());
            values[entry + ".payload.optionsaddordermessage.volume"] = canonical::number(message->volume.get());
            values[entry + ".payload.optionsaddordermessage.side"] = canonical::text(canonical::character(message->side.get()), '\0', false);
            values[entry + ".payload.optionsaddordermessage.firmid"] = canonical::text(std::string(message->firm_id.get()), ' ', false);
            values[entry + ".payload.optionsaddordermessage.custindicator"] = canonical::text(canonical::character(message->cust_indicator.get()), '\0', false);
        } else if (iterator.message_type == protocol::OptionsModifyOrderMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.optionsmodifyordermessage";
            [[maybe_unused]] const auto* message = protocol::OptionsModifyOrderMessage::parse(iterator.message);
            values[entry + ".payload.optionsmodifyordermessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.optionsmodifyordermessage.seriesindex"] = canonical::number(message->series_index.get());
            values[entry + ".payload.optionsmodifyordermessage.seriesseqnum"] = canonical::number(message->series_seq_num.get());
            values[entry + ".payload.optionsmodifyordermessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.optionsmodifyordermessage.price"] = canonical::number(message->price.get());
            values[entry + ".payload.optionsmodifyordermessage.volume"] = canonical::number(message->volume.get());
            values[entry + ".payload.optionsmodifyordermessage.positionchange"] = canonical::number(message->position_change.get());
            values[entry + ".payload.optionsmodifyordermessage.side"] = canonical::text(canonical::character(message->side.get()), '\0', false);
            values[entry + ".payload.optionsmodifyordermessage.custindicator"] = canonical::text(canonical::character(message->cust_indicator.get()), '\0', false);
        } else if (iterator.message_type == protocol::OptionsDeleteOrderMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.optionsdeleteordermessage";
            [[maybe_unused]] const auto* message = protocol::OptionsDeleteOrderMessage::parse(iterator.message);
            values[entry + ".payload.optionsdeleteordermessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.optionsdeleteordermessage.seriesindex"] = canonical::number(message->series_index.get());
            values[entry + ".payload.optionsdeleteordermessage.seriesseqnum"] = canonical::number(message->series_seq_num.get());
            values[entry + ".payload.optionsdeleteordermessage.orderid"] = canonical::number(message->order_id.get());
        } else if (iterator.message_type == protocol::OptionsOrderExecutionMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.optionsorderexecutionmessage";
            [[maybe_unused]] const auto* message = protocol::OptionsOrderExecutionMessage::parse(iterator.message);
            values[entry + ".payload.optionsorderexecutionmessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.optionsorderexecutionmessage.seriesindex"] = canonical::number(message->series_index.get());
            values[entry + ".payload.optionsorderexecutionmessage.seriesseqnum"] = canonical::number(message->series_seq_num.get());
            values[entry + ".payload.optionsorderexecutionmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.optionsorderexecutionmessage.tradeid"] = canonical::number(message->trade_id.get());
            values[entry + ".payload.optionsorderexecutionmessage.price"] = canonical::number(message->price.get());
            values[entry + ".payload.optionsorderexecutionmessage.volume"] = canonical::number(message->volume.get());
            values[entry + ".payload.optionsorderexecutionmessage.printableflag"] = canonical::number(message->printable_flag.get());
            values[entry + ".payload.optionsorderexecutionmessage.tradecond1"] = canonical::text(canonical::character(message->trade_cond_1.get()), '\0', false);
        } else if (iterator.message_type == protocol::OptionsReplaceOrderMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.optionsreplaceordermessage";
            [[maybe_unused]] const auto* message = protocol::OptionsReplaceOrderMessage::parse(iterator.message);
            values[entry + ".payload.optionsreplaceordermessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.optionsreplaceordermessage.seriesindex"] = canonical::number(message->series_index.get());
            values[entry + ".payload.optionsreplaceordermessage.seriesseqnum"] = canonical::number(message->series_seq_num.get());
            values[entry + ".payload.optionsreplaceordermessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.optionsreplaceordermessage.neworderid"] = canonical::number(message->new_order_id.get());
            values[entry + ".payload.optionsreplaceordermessage.price"] = canonical::number(message->price.get());
            values[entry + ".payload.optionsreplaceordermessage.volume"] = canonical::number(message->volume.get());
            values[entry + ".payload.optionsreplaceordermessage.side"] = canonical::text(canonical::character(message->side.get()), '\0', false);
            values[entry + ".payload.optionsreplaceordermessage.custindicator"] = canonical::text(canonical::character(message->cust_indicator.get()), '\0', false);
        } else if (iterator.message_type == protocol::OptionsImbalanceMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.optionsimbalancemessage";
            [[maybe_unused]] const auto* message = protocol::OptionsImbalanceMessage::parse(iterator.message);
            values[entry + ".payload.optionsimbalancemessage.sourcetime"] = canonical::number(message->source_time.get());
            values[entry + ".payload.optionsimbalancemessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.optionsimbalancemessage.seriesindex"] = canonical::number(message->series_index.get());
            values[entry + ".payload.optionsimbalancemessage.seriesseqnum"] = canonical::number(message->series_seq_num.get());
            values[entry + ".payload.optionsimbalancemessage.pairedqty"] = canonical::number(message->paired_qty.get());
            values[entry + ".payload.optionsimbalancemessage.totalimbalanceqty"] = canonical::number(message->total_imbalance_qty.get());
            values[entry + ".payload.optionsimbalancemessage.marketimbalanceqty"] = canonical::number(message->market_imbalance_qty.get());
            values[entry + ".payload.optionsimbalancemessage.auctiontype"] = canonical::text(canonical::character(message->auction_type.get()), '\0', false);
            values[entry + ".payload.optionsimbalancemessage.imbalanceside"] = canonical::text(canonical::character(message->imbalance_side.get()), '\0', false);
            values[entry + ".payload.optionsimbalancemessage.continuousbookclearingprice"] = canonical::number(message->continuous_book_clearing_price.get());
            values[entry + ".payload.optionsimbalancemessage.auctioninterestclearingprice"] = canonical::number(message->auction_interest_clearing_price.get());
            values[entry + ".payload.optionsimbalancemessage.indicativematchprice"] = canonical::number(message->indicative_match_price.get());
            values[entry + ".payload.optionsimbalancemessage.uppercollar"] = canonical::number(message->upper_collar.get());
            values[entry + ".payload.optionsimbalancemessage.lowercollar"] = canonical::number(message->lower_collar.get());
            values[entry + ".payload.optionsimbalancemessage.auctionstatus"] = canonical::number(message->auction_status.get());
        } else if (iterator.message_type == protocol::OptionsAddOrderRefreshMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.optionsaddorderrefreshmessage";
            [[maybe_unused]] const auto* message = protocol::OptionsAddOrderRefreshMessage::parse(iterator.message);
            values[entry + ".payload.optionsaddorderrefreshmessage.sourcetime"] = canonical::number(message->source_time.get());
            values[entry + ".payload.optionsaddorderrefreshmessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.optionsaddorderrefreshmessage.seriesindex"] = canonical::number(message->series_index.get());
            values[entry + ".payload.optionsaddorderrefreshmessage.seriesseqnum"] = canonical::number(message->series_seq_num.get());
            values[entry + ".payload.optionsaddorderrefreshmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.optionsaddorderrefreshmessage.price"] = canonical::number(message->price.get());
            values[entry + ".payload.optionsaddorderrefreshmessage.volume"] = canonical::number(message->volume.get());
            values[entry + ".payload.optionsaddorderrefreshmessage.side"] = canonical::text(canonical::character(message->side.get()), '\0', false);
            values[entry + ".payload.optionsaddorderrefreshmessage.firmid"] = canonical::text(std::string(message->firm_id.get()), ' ', false);
            values[entry + ".payload.optionsaddorderrefreshmessage.custindicator"] = canonical::text(canonical::character(message->cust_indicator.get()), '\0', false);
        } else if (iterator.message_type == protocol::OptionsSeriesRfqMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.optionsseriesrfqmessage";
            [[maybe_unused]] const auto* message = protocol::OptionsSeriesRfqMessage::parse(iterator.message);
            values[entry + ".payload.optionsseriesrfqmessage.sourcetime"] = canonical::number(message->source_time.get());
            values[entry + ".payload.optionsseriesrfqmessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.optionsseriesrfqmessage.seriesindex"] = canonical::number(message->series_index.get());
            values[entry + ".payload.optionsseriesrfqmessage.seriesseqnum"] = canonical::number(message->series_seq_num.get());
            values[entry + ".payload.optionsseriesrfqmessage.rfqside"] = canonical::text(canonical::character(message->rfq_side.get()), '\0', false);
            values[entry + ".payload.optionsseriesrfqmessage.type"] = canonical::text(canonical::character(message->type.get()), '\0', false);
            values[entry + ".payload.optionsseriesrfqmessage.capacity"] = canonical::text(canonical::character(message->capacity.get()), '\0', false);
            values[entry + ".payload.optionsseriesrfqmessage.totalquantity"] = canonical::number(message->total_quantity.get());
            values[entry + ".payload.optionsseriesrfqmessage.workingprice"] = canonical::number(message->working_price.get());
            values[entry + ".payload.optionsseriesrfqmessage.participant"] = canonical::number(message->participant.get());
            values[entry + ".payload.optionsseriesrfqmessage.auctionid"] = canonical::number(message->auction_id.get());
            values[entry + ".payload.optionsseriesrfqmessage.rfqstatus"] = canonical::text(canonical::character(message->rfq_status.get()), '\0', false);
        } else if (iterator.message_type == protocol::OptionsNonDisplayedTradeMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.optionsnondisplayedtrademessage";
            [[maybe_unused]] const auto* message = protocol::OptionsNonDisplayedTradeMessage::parse(iterator.message);
            values[entry + ".payload.optionsnondisplayedtrademessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.optionsnondisplayedtrademessage.seriesindex"] = canonical::number(message->series_index.get());
            values[entry + ".payload.optionsnondisplayedtrademessage.seriesseqnum"] = canonical::number(message->series_seq_num.get());
            values[entry + ".payload.optionsnondisplayedtrademessage.tradeid"] = canonical::number(message->trade_id.get());
            values[entry + ".payload.optionsnondisplayedtrademessage.price"] = canonical::number(message->price.get());
            values[entry + ".payload.optionsnondisplayedtrademessage.volume"] = canonical::number(message->volume.get());
            values[entry + ".payload.optionsnondisplayedtrademessage.printableflag"] = canonical::number(message->printable_flag.get());
            values[entry + ".payload.optionsnondisplayedtrademessage.nondisplayedtradetradecond1"] = canonical::text(canonical::character(message->non_displayed_trade_trade_cond_1.get()), '\0', false);
            values[entry + ".payload.optionsnondisplayedtrademessage.pricetype"] = canonical::number(message->price_type.get());
        } else if (iterator.message_type == protocol::OptionsCrossTradeMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.optionscrosstrademessage";
            [[maybe_unused]] const auto* message = protocol::OptionsCrossTradeMessage::parse(iterator.message);
            values[entry + ".payload.optionscrosstrademessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.optionscrosstrademessage.seriesindex"] = canonical::number(message->series_index.get());
            values[entry + ".payload.optionscrosstrademessage.seriesseqnum"] = canonical::number(message->series_seq_num.get());
            values[entry + ".payload.optionscrosstrademessage.crossid"] = canonical::number(message->cross_id.get());
            values[entry + ".payload.optionscrosstrademessage.price"] = canonical::number(message->price.get());
            values[entry + ".payload.optionscrosstrademessage.volume"] = canonical::number(message->volume.get());
            values[entry + ".payload.optionscrosstrademessage.crosstype"] = canonical::text(canonical::character(message->cross_type.get()), '\0', false);
        } else if (iterator.message_type == protocol::OptionsTradeCancelMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.optionstradecancelmessage";
            [[maybe_unused]] const auto* message = protocol::OptionsTradeCancelMessage::parse(iterator.message);
            values[entry + ".payload.optionstradecancelmessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.optionstradecancelmessage.seriesindex"] = canonical::number(message->series_index.get());
            values[entry + ".payload.optionstradecancelmessage.seriesseqnum"] = canonical::number(message->series_seq_num.get());
            values[entry + ".payload.optionstradecancelmessage.tradeid"] = canonical::number(message->trade_id.get());
        } else if (iterator.message_type == protocol::OptionsOutrightSeriesSummaryMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.optionsoutrightseriessummarymessage";
            [[maybe_unused]] const auto* message = protocol::OptionsOutrightSeriesSummaryMessage::parse(iterator.message);
            values[entry + ".payload.optionsoutrightseriessummarymessage.sourcetime"] = canonical::number(message->source_time.get());
            values[entry + ".payload.optionsoutrightseriessummarymessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.optionsoutrightseriessummarymessage.seriesindex"] = canonical::number(message->series_index.get());
            values[entry + ".payload.optionsoutrightseriessummarymessage.highprice"] = canonical::number(message->high_price.get());
            values[entry + ".payload.optionsoutrightseriessummarymessage.lowprice"] = canonical::number(message->low_price.get());
            values[entry + ".payload.optionsoutrightseriessummarymessage.open"] = canonical::number(message->open.get());
            values[entry + ".payload.optionsoutrightseriessummarymessage.close"] = canonical::number(message->close.get());
            values[entry + ".payload.optionsoutrightseriessummarymessage.totalvolume"] = canonical::number(message->total_volume.get());
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
    std::printf("== Nyse.ArcaOptions.DeepFeed.Pillar.v1.2.m (modern values)\n");
    int failures = 0;
    failures += check("OptionsAddOrderMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/OptionsAddOrderMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/OptionsAddOrderMessage.values");
    failures += check("OptionsCrossTradeMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/OptionsCrossTradeMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/OptionsCrossTradeMessage.values");
    failures += check("OptionsDeleteOrderMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/OptionsDeleteOrderMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/OptionsDeleteOrderMessage.values");
    failures += check("OptionsImbalanceMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/OptionsImbalanceMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/OptionsImbalanceMessage.values");
    failures += check("OptionsModifyOrderMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/OptionsModifyOrderMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/OptionsModifyOrderMessage.values");
    failures += check("OptionsNonDisplayedTradeMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/OptionsNonDisplayedTradeMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/OptionsNonDisplayedTradeMessage.values");
    failures += check("OptionsOrderExecutionMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/OptionsOrderExecutionMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/OptionsOrderExecutionMessage.values");
    failures += check("OptionsReplaceOrderMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/OptionsReplaceOrderMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/OptionsReplaceOrderMessage.values");
    failures += check("OptionsStatusMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/OptionsStatusMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/OptionsStatusMessage.values");
    failures += check("OutrightSeriesIndexMappingMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/OutrightSeriesIndexMappingMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/OutrightSeriesIndexMappingMessage.values");
    failures += check("SecurityStatusMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/SecurityStatusMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/SecurityStatusMessage.values");
    failures += check("SequenceNumberResetMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/SequenceNumberResetMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/SequenceNumberResetMessage.values");
    failures += check("SourceTimeReferenceMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/SourceTimeReferenceMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/SourceTimeReferenceMessage.values");
    failures += check("SymbolClearMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/SymbolClearMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/SymbolClearMessage.values");
    failures += check("SymbolIndexMappingMessage", "Nyse/ArcaOptions.DeepFeed.Pillar.v1.2.m/SymbolIndexMappingMessage.pcap", "nyse/arcaoptions/deepfeed/pillar/v1.2.m/SymbolIndexMappingMessage.values");
    return failures == 0 ? 0 : 1;
}
