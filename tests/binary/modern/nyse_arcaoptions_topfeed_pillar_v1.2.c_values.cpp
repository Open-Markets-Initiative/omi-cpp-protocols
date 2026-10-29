// Nyse.ArcaOptions.TopFeed.Pillar.v1.2.c canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/binary/modern/nyse/arcaoptions/topfeed/pillar/v1.2.c/definitions.hpp"

namespace protocol = ::nyse::arcaoptions::topfeed::pillar::v1_2_c;

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
        } else if (iterator.message_type == protocol::TimeReferenceMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.timereferencemessage";
            [[maybe_unused]] const auto* message = protocol::TimeReferenceMessage::parse(iterator.message);
            values[entry + ".payload.timereferencemessage.id"] = canonical::number(message->id.get());
            values[entry + ".payload.timereferencemessage.sourcetime"] = canonical::number(message->source_time.get());
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
        } else if (iterator.message_type == protocol::RetransmissionRequestMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.retransmissionrequestmessage";
            [[maybe_unused]] const auto* message = protocol::RetransmissionRequestMessage::parse(iterator.message);
            values[entry + ".payload.retransmissionrequestmessage.beginseqnum"] = canonical::number(message->begin_seq_num.get());
            values[entry + ".payload.retransmissionrequestmessage.endseqnum"] = canonical::number(message->end_seq_num.get());
            values[entry + ".payload.retransmissionrequestmessage.sourceid"] = canonical::text(std::string(message->source_id.get()), '\0', false);
            values[entry + ".payload.retransmissionrequestmessage.productid"] = canonical::number(message->product_id.get());
            values[entry + ".payload.retransmissionrequestmessage.channelid"] = canonical::number(message->channel_id.get());
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
        } else if (iterator.message_type == protocol::SymbolIndexMappingRequestMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.symbolindexmappingrequestmessage";
            [[maybe_unused]] const auto* message = protocol::SymbolIndexMappingRequestMessage::parse(iterator.message);
            values[entry + ".payload.symbolindexmappingrequestmessage.symbolindex"] = canonical::number(message->symbol_index.get());
            values[entry + ".payload.symbolindexmappingrequestmessage.sourceid"] = canonical::text(std::string(message->source_id.get()), '\0', false);
            values[entry + ".payload.symbolindexmappingrequestmessage.productid"] = canonical::number(message->product_id.get());
            values[entry + ".payload.symbolindexmappingrequestmessage.channelid"] = canonical::number(message->channel_id.get());
            values[entry + ".payload.symbolindexmappingrequestmessage.retransmitmethod"] = canonical::number(message->retransmit_method.get());
        } else if (iterator.message_type == protocol::RefreshRequestMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.refreshrequestmessage";
            [[maybe_unused]] const auto* message = protocol::RefreshRequestMessage::parse(iterator.message);
            values[entry + ".payload.refreshrequestmessage.symbolindex"] = canonical::number(message->symbol_index.get());
            values[entry + ".payload.refreshrequestmessage.sourceid"] = canonical::text(std::string(message->source_id.get()), '\0', false);
            values[entry + ".payload.refreshrequestmessage.productid"] = canonical::number(message->product_id.get());
            values[entry + ".payload.refreshrequestmessage.channelid"] = canonical::number(message->channel_id.get());
        } else if (iterator.message_type == protocol::MessageUnavailableMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.messageunavailablemessage";
            [[maybe_unused]] const auto* message = protocol::MessageUnavailableMessage::parse(iterator.message);
            values[entry + ".payload.messageunavailablemessage.beginseqnum"] = canonical::number(message->begin_seq_num.get());
            values[entry + ".payload.messageunavailablemessage.endseqnum"] = canonical::number(message->end_seq_num.get());
            values[entry + ".payload.messageunavailablemessage.productid"] = canonical::number(message->product_id.get());
            values[entry + ".payload.messageunavailablemessage.channelid"] = canonical::number(message->channel_id.get());
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
            values[entry + ".payload.securitystatusmessage.sessionstate"] = canonical::number(message->session_state.get());
        } else if (iterator.message_type == protocol::RefreshHeaderMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.refreshheadermessage";
            [[maybe_unused]] const auto* message = protocol::RefreshHeaderMessage::parse(iterator.message);
            values[entry + ".payload.refreshheadermessage.currentrefreshpkt"] = canonical::number(message->current_refresh_pkt.get());
            values[entry + ".payload.refreshheadermessage.totalrefreshpkts"] = canonical::number(message->total_refresh_pkts.get());
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
            values[entry + ".payload.optionsstatusmessage.haltcondition"] = canonical::text(canonical::character(message->halt_condition.get()), '\0', false);
        } else if (iterator.message_type == protocol::OptionsQuoteMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.optionsquotemessage";
            [[maybe_unused]] const auto* message = protocol::OptionsQuoteMessage::parse(iterator.message);
            values[entry + ".payload.optionsquotemessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.optionsquotemessage.seriesindex"] = canonical::number(message->series_index.get());
            values[entry + ".payload.optionsquotemessage.seriesseqnum"] = canonical::number(message->series_seq_num.get());
            values[entry + ".payload.optionsquotemessage.askprice"] = canonical::number(message->ask_price.get());
            values[entry + ".payload.optionsquotemessage.askvolume"] = canonical::number(message->ask_volume.get());
            values[entry + ".payload.optionsquotemessage.bidprice"] = canonical::number(message->bid_price.get());
            values[entry + ".payload.optionsquotemessage.bidvolume"] = canonical::number(message->bid_volume.get());
            values[entry + ".payload.optionsquotemessage.quotecondition"] = canonical::text(canonical::character(message->quote_condition.get()), '\0', false);
            values[entry + ".payload.optionsquotemessage.askcustomervolume"] = canonical::number(message->ask_customer_volume.get());
            values[entry + ".payload.optionsquotemessage.bidcustomervolume"] = canonical::number(message->bid_customer_volume.get());
        } else if (iterator.message_type == protocol::OptionsTradeMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.optionstrademessage";
            [[maybe_unused]] const auto* message = protocol::OptionsTradeMessage::parse(iterator.message);
            values[entry + ".payload.optionstrademessage.sourcetime"] = canonical::number(message->source_time.get());
            values[entry + ".payload.optionstrademessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.optionstrademessage.seriesindex"] = canonical::number(message->series_index.get());
            values[entry + ".payload.optionstrademessage.seriesseqnum"] = canonical::number(message->series_seq_num.get());
            values[entry + ".payload.optionstrademessage.tradeid"] = canonical::number(message->trade_id.get());
            values[entry + ".payload.optionstrademessage.price"] = canonical::number(message->price.get());
            values[entry + ".payload.optionstrademessage.volume"] = canonical::number(message->volume.get());
            values[entry + ".payload.optionstrademessage.tradecondition.series"] = canonical::text(canonical::character(message->trade_condition.series.get()), '\0', false);
            values[entry + ".payload.optionstrademessage.tradecondition.opening"] = canonical::text(canonical::character(message->trade_condition.opening.get()), '\0', false);
            values[entry + ".payload.optionstrademessage.tradecondition.offical"] = canonical::text(canonical::character(message->trade_condition.offical.get()), '\0', false);
        } else if (iterator.message_type == protocol::OptionsTradeCancelMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.optionstradecancelmessage";
            [[maybe_unused]] const auto* message = protocol::OptionsTradeCancelMessage::parse(iterator.message);
            values[entry + ".payload.optionstradecancelmessage.sourcetime"] = canonical::number(message->source_time.get());
            values[entry + ".payload.optionstradecancelmessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.optionstradecancelmessage.seriesindex"] = canonical::number(message->series_index.get());
            values[entry + ".payload.optionstradecancelmessage.seriesseqnum"] = canonical::number(message->series_seq_num.get());
            values[entry + ".payload.optionstradecancelmessage.originaltradeid"] = canonical::number(message->original_trade_id.get());
        } else if (iterator.message_type == protocol::OptionsTradeCorrectionMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.optionstradecorrectionmessage";
            [[maybe_unused]] const auto* message = protocol::OptionsTradeCorrectionMessage::parse(iterator.message);
            values[entry + ".payload.optionstradecorrectionmessage.sourcetime"] = canonical::number(message->source_time.get());
            values[entry + ".payload.optionstradecorrectionmessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.optionstradecorrectionmessage.seriesindex"] = canonical::number(message->series_index.get());
            values[entry + ".payload.optionstradecorrectionmessage.seriesseqnum"] = canonical::number(message->series_seq_num.get());
            values[entry + ".payload.optionstradecorrectionmessage.originaltradeid"] = canonical::number(message->original_trade_id.get());
            values[entry + ".payload.optionstradecorrectionmessage.tradeid"] = canonical::number(message->trade_id.get());
            values[entry + ".payload.optionstradecorrectionmessage.price"] = canonical::number(message->price.get());
            values[entry + ".payload.optionstradecorrectionmessage.volume"] = canonical::number(message->volume.get());
            values[entry + ".payload.optionstradecorrectionmessage.correctioncondition.transaction"] = canonical::text(canonical::character(message->correction_condition.transaction.get()), '\0', false);
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
        } else if (iterator.message_type == protocol::SeriesRfqMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.seriesrfqmessage";
            [[maybe_unused]] const auto* message = protocol::SeriesRfqMessage::parse(iterator.message);
            values[entry + ".payload.seriesrfqmessage.sourcetime"] = canonical::number(message->source_time.get());
            values[entry + ".payload.seriesrfqmessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.seriesrfqmessage.seriesindex"] = canonical::number(message->series_index.get());
            values[entry + ".payload.seriesrfqmessage.seriesseqnum"] = canonical::number(message->series_seq_num.get());
            values[entry + ".payload.seriesrfqmessage.side"] = canonical::text(canonical::character(message->side.get()), '\0', false);
            values[entry + ".payload.seriesrfqmessage.type"] = canonical::text(canonical::character(message->type.get()), '\0', false);
            values[entry + ".payload.seriesrfqmessage.capacity"] = canonical::text(canonical::character(message->capacity.get()), '\0', false);
            values[entry + ".payload.seriesrfqmessage.totalquantity"] = canonical::number(message->total_quantity.get());
            values[entry + ".payload.seriesrfqmessage.workingprice"] = canonical::number(message->working_price.get());
            values[entry + ".payload.seriesrfqmessage.participant"] = canonical::number(message->participant.get());
            values[entry + ".payload.seriesrfqmessage.auctionid"] = canonical::number(message->auction_id.get());
            values[entry + ".payload.seriesrfqmessage.rfqstatus"] = canonical::text(canonical::character(message->rfq_status.get()), '\0', false);
        } else if (iterator.message_type == protocol::OutrightSeriesSummaryMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.outrightseriessummarymessage";
            [[maybe_unused]] const auto* message = protocol::OutrightSeriesSummaryMessage::parse(iterator.message);
            values[entry + ".payload.outrightseriessummarymessage.sourcetime"] = canonical::number(message->source_time.get());
            values[entry + ".payload.outrightseriessummarymessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.outrightseriessummarymessage.seriesindex"] = canonical::number(message->series_index.get());
            values[entry + ".payload.outrightseriessummarymessage.highprice"] = canonical::number(message->high_price.get());
            values[entry + ".payload.outrightseriessummarymessage.lowprice"] = canonical::number(message->low_price.get());
            values[entry + ".payload.outrightseriessummarymessage.open"] = canonical::number(message->open.get());
            values[entry + ".payload.outrightseriessummarymessage.close"] = canonical::number(message->close.get());
            values[entry + ".payload.outrightseriessummarymessage.totalvolume"] = canonical::number(message->total_volume.get());
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
    std::printf("== Nyse.ArcaOptions.TopFeed.Pillar.v1.2.c (modern values)\n");
    int failures = 0;
    failures += check("HeartBeat", "Nyse/ArcaOptions.TopFeed.Pillar.v1.2.c/HeartBeat.pcap", "nyse/arcaoptions/topfeed/pillar/v1.2.c/HeartBeat.values");
    failures += check("OptionsQuoteMessage", "Nyse/ArcaOptions.TopFeed.Pillar.v1.2.c/OptionsQuoteMessage.pcap", "nyse/arcaoptions/topfeed/pillar/v1.2.c/OptionsQuoteMessage.values");
    failures += check("SequenceNumberResetMessage", "Nyse/ArcaOptions.TopFeed.Pillar.v1.2.c/SequenceNumberResetMessage.pcap", "nyse/arcaoptions/topfeed/pillar/v1.2.c/SequenceNumberResetMessage.values");
    return failures == 0 ? 0 : 1;
}
