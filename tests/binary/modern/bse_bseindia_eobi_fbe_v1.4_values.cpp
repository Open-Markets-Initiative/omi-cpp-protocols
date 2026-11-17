// Bse.BseIndia.Eobi.Fbe.v1.4 canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/binary/modern/bse/bseindia/eobi/fbe/v1.4/definitions.hpp"

namespace protocol = ::bse::bseindia::eobi::fbe::v1_4;

namespace {

// The values the Modern iterator reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    values["packet.packetheader.eobiheader.bodylen"] = canonical::number(iterator.packet_header->eobi_header.body_len.get());
    values["packet.packetheader.eobiheader.templateid"] = canonical::number(iterator.packet_header->eobi_header.template_id.get());
    values["packet.packetheader.eobiheader.msgseqnum"] = canonical::number(iterator.packet_header->eobi_header.msg_seq_num.get());
    values["packet.packetheader.applseqnum"] = canonical::number(iterator.packet_header->appl_seq_num.get());
    values["packet.packetheader.marketsegmentid"] = canonical::number(iterator.packet_header->market_segment_id.get());
    values["packet.packetheader.partitionid"] = canonical::number(iterator.packet_header->partition_id.get());
    values["packet.packetheader.completionindicator"] = canonical::number(iterator.packet_header->completion_indicator.get());
    values["packet.packetheader.applseqresetindicator"] = canonical::number(iterator.packet_header->appl_seq_reset_indicator.get());
    values["packet.packetheader.transacttime"] = canonical::number(iterator.packet_header->transact_time.get());

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.bodylen"] = canonical::number(iterator.message_header->body_len.get());
        values[entry + ".messageheader.templateid"] = canonical::number(iterator.message_header->template_id.get());
        values[entry + ".messageheader.msgseqnum"] = canonical::number(iterator.message_header->msg_seq_num.get());

        if (iterator.template_id == protocol::HeartbeatMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.heartbeatmessage";
            [[maybe_unused]] const auto* message = protocol::HeartbeatMessage::parse(iterator.message);
            values[entry + ".payload.heartbeatmessage.lastmsgseqnumprocessed"] = canonical::number(message->last_msg_seq_num_processed.get());
        } else if (iterator.template_id == protocol::ProductSummaryMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.productsummarymessage";
            [[maybe_unused]] const auto* message = protocol::ProductSummaryMessage::parse(iterator.message);
            values[entry + ".payload.productsummarymessage.lastmsgseqnumprocessed"] = canonical::number(message->last_msg_seq_num_processed.get());
            values[entry + ".payload.productsummarymessage.tradingsessionid"] = canonical::number(message->trading_session_id.get());
            values[entry + ".payload.productsummarymessage.tradingsessionsubid"] = canonical::number(message->trading_session_sub_id.get());
            values[entry + ".payload.productsummarymessage.tradsesstatus"] = canonical::number(message->trad_ses_status.get());
            values[entry + ".payload.productsummarymessage.fastmarketindicator"] = canonical::number(message->fast_market_indicator.get());
        } else if (iterator.template_id == protocol::SnapshotOrderMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.snapshotordermessage";
            [[maybe_unused]] const auto* message = protocol::SnapshotOrderMessage::parse(iterator.message);
            values[entry + ".payload.snapshotordermessage.orderdetails.trdregtstimepriority"] = canonical::number(message->order_details.trd_reg_ts_time_priority.get());
            values[entry + ".payload.snapshotordermessage.orderdetails.displayqty"] = canonical::number(message->order_details.display_qty.get());
            values[entry + ".payload.snapshotordermessage.orderdetails.side"] = canonical::number(message->order_details.side.get());
            values[entry + ".payload.snapshotordermessage.orderdetails.price"] = canonical::scaled(message->order_details.price.integer(), -6);
        } else if (iterator.template_id == protocol::InstrumentSummaryMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.instrumentsummarymessage";
            [[maybe_unused]] const auto* message = protocol::InstrumentSummaryMessage::parse(iterator.message);
            values[entry + ".payload.instrumentsummarymessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.instrumentsummarymessage.lastupdatetime"] = canonical::number(message->last_update_time.get());
            values[entry + ".payload.instrumentsummarymessage.trdregtsexecutiontime"] = (static_cast<std::uint64_t>(message->trd_reg_ts_execution_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->trd_reg_ts_execution_time.get()) : canonical::absent());
            values[entry + ".payload.instrumentsummarymessage.totnoorders"] = canonical::number(message->tot_no_orders.get());
            values[entry + ".payload.instrumentsummarymessage.securitystatus"] = canonical::number(message->security_status.get());
            values[entry + ".payload.instrumentsummarymessage.securitytradingstatus"] = canonical::number(message->security_trading_status.get());
            values[entry + ".payload.instrumentsummarymessage.fastmarketindicator"] = canonical::number(message->fast_market_indicator.get());
            values[entry + ".payload.instrumentsummarymessage.nomdentries"] = canonical::number(message->no_md_entries.get());
            values[entry + ".payload.instrumentsummarymessage.tradevolume"] = canonical::number(message->trade_volume.get());
            values[entry + ".payload.instrumentsummarymessage.nooftrades"] = canonical::number(message->no_of_trades.get());
        } else if (iterator.template_id == protocol::AuctionBestBidOfferMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.auctionbestbidoffermessage";
            [[maybe_unused]] const auto* message = protocol::AuctionBestBidOfferMessage::parse(iterator.message);
            values[entry + ".payload.auctionbestbidoffermessage.transacttime"] = canonical::number(message->transact_time.get());
            values[entry + ".payload.auctionbestbidoffermessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.auctionbestbidoffermessage.bidpx"] = (static_cast<std::uint64_t>(message->bid_px.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->bid_px.integer(), -6) : canonical::absent());
            values[entry + ".payload.auctionbestbidoffermessage.offerpx"] = (static_cast<std::uint64_t>(message->offer_px.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->offer_px.integer(), -6) : canonical::absent());
        } else if (iterator.template_id == protocol::AuctionClearingPriceMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.auctionclearingpricemessage";
            [[maybe_unused]] const auto* message = protocol::AuctionClearingPriceMessage::parse(iterator.message);
            values[entry + ".payload.auctionclearingpricemessage.transacttime"] = canonical::number(message->transact_time.get());
            values[entry + ".payload.auctionclearingpricemessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.auctionclearingpricemessage.lastpx"] = canonical::scaled(message->last_px.integer(), -6);
            values[entry + ".payload.auctionclearingpricemessage.lastqty"] = canonical::number(message->last_qty.get());
        } else if (iterator.template_id == protocol::TopOfBookMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.topofbookmessage";
            [[maybe_unused]] const auto* message = protocol::TopOfBookMessage::parse(iterator.message);
            values[entry + ".payload.topofbookmessage.transacttime"] = canonical::number(message->transact_time.get());
            values[entry + ".payload.topofbookmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.topofbookmessage.bidpx"] = (static_cast<std::uint64_t>(message->bid_px.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->bid_px.integer(), -6) : canonical::absent());
            values[entry + ".payload.topofbookmessage.offerpx"] = (static_cast<std::uint64_t>(message->offer_px.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->offer_px.integer(), -6) : canonical::absent());
        } else if (iterator.template_id == protocol::OrderAddMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.orderaddmessage";
            [[maybe_unused]] const auto* message = protocol::OrderAddMessage::parse(iterator.message);
            values[entry + ".payload.orderaddmessage.trdregtstimein"] = (static_cast<std::uint64_t>(message->trd_reg_ts_time_in.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->trd_reg_ts_time_in.get()) : canonical::absent());
            values[entry + ".payload.orderaddmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.orderaddmessage.orderdetails.trdregtstimepriority"] = canonical::number(message->order_details.trd_reg_ts_time_priority.get());
            values[entry + ".payload.orderaddmessage.orderdetails.displayqty"] = canonical::number(message->order_details.display_qty.get());
            values[entry + ".payload.orderaddmessage.orderdetails.side"] = canonical::number(message->order_details.side.get());
            values[entry + ".payload.orderaddmessage.orderdetails.price"] = canonical::scaled(message->order_details.price.integer(), -6);
        } else if (iterator.template_id == protocol::OrderModifyMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.ordermodifymessage";
            [[maybe_unused]] const auto* message = protocol::OrderModifyMessage::parse(iterator.message);
            values[entry + ".payload.ordermodifymessage.trdregtstimein"] = (static_cast<std::uint64_t>(message->trd_reg_ts_time_in.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->trd_reg_ts_time_in.get()) : canonical::absent());
            values[entry + ".payload.ordermodifymessage.trdregtsprevtimepriority"] = canonical::number(message->trd_reg_ts_prev_time_priority.get());
            values[entry + ".payload.ordermodifymessage.prevprice"] = canonical::scaled(message->prev_price.integer(), -6);
            values[entry + ".payload.ordermodifymessage.prevdisplayqty"] = canonical::number(message->prev_display_qty.get());
            values[entry + ".payload.ordermodifymessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.ordermodifymessage.orderdetails.trdregtstimepriority"] = canonical::number(message->order_details.trd_reg_ts_time_priority.get());
            values[entry + ".payload.ordermodifymessage.orderdetails.displayqty"] = canonical::number(message->order_details.display_qty.get());
            values[entry + ".payload.ordermodifymessage.orderdetails.side"] = canonical::number(message->order_details.side.get());
            values[entry + ".payload.ordermodifymessage.orderdetails.price"] = canonical::scaled(message->order_details.price.integer(), -6);
        } else if (iterator.template_id == protocol::OrderModifySamePriorityMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.ordermodifysameprioritymessage";
            [[maybe_unused]] const auto* message = protocol::OrderModifySamePriorityMessage::parse(iterator.message);
            values[entry + ".payload.ordermodifysameprioritymessage.trdregtstimein"] = (static_cast<std::uint64_t>(message->trd_reg_ts_time_in.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->trd_reg_ts_time_in.get()) : canonical::absent());
            values[entry + ".payload.ordermodifysameprioritymessage.transacttime"] = canonical::number(message->transact_time.get());
            values[entry + ".payload.ordermodifysameprioritymessage.prevdisplayqty"] = canonical::number(message->prev_display_qty.get());
            values[entry + ".payload.ordermodifysameprioritymessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.ordermodifysameprioritymessage.orderdetails.trdregtstimepriority"] = canonical::number(message->order_details.trd_reg_ts_time_priority.get());
            values[entry + ".payload.ordermodifysameprioritymessage.orderdetails.displayqty"] = canonical::number(message->order_details.display_qty.get());
            values[entry + ".payload.ordermodifysameprioritymessage.orderdetails.side"] = canonical::number(message->order_details.side.get());
            values[entry + ".payload.ordermodifysameprioritymessage.orderdetails.price"] = canonical::scaled(message->order_details.price.integer(), -6);
        } else if (iterator.template_id == protocol::OrderDeleteMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.orderdeletemessage";
            [[maybe_unused]] const auto* message = protocol::OrderDeleteMessage::parse(iterator.message);
            values[entry + ".payload.orderdeletemessage.trdregtstimein"] = (static_cast<std::uint64_t>(message->trd_reg_ts_time_in.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->trd_reg_ts_time_in.get()) : canonical::absent());
            values[entry + ".payload.orderdeletemessage.transacttime"] = canonical::number(message->transact_time.get());
            values[entry + ".payload.orderdeletemessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.orderdeletemessage.orderdetails.trdregtstimepriority"] = canonical::number(message->order_details.trd_reg_ts_time_priority.get());
            values[entry + ".payload.orderdeletemessage.orderdetails.displayqty"] = canonical::number(message->order_details.display_qty.get());
            values[entry + ".payload.orderdeletemessage.orderdetails.side"] = canonical::number(message->order_details.side.get());
            values[entry + ".payload.orderdeletemessage.orderdetails.price"] = canonical::scaled(message->order_details.price.integer(), -6);
        } else if (iterator.template_id == protocol::OrderMassDeleteMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.ordermassdeletemessage";
            [[maybe_unused]] const auto* message = protocol::OrderMassDeleteMessage::parse(iterator.message);
            values[entry + ".payload.ordermassdeletemessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.ordermassdeletemessage.transacttime"] = canonical::number(message->transact_time.get());
        } else if (iterator.template_id == protocol::PartialOrderExecutionMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.partialorderexecutionmessage";
            [[maybe_unused]] const auto* message = protocol::PartialOrderExecutionMessage::parse(iterator.message);
            values[entry + ".payload.partialorderexecutionmessage.side"] = canonical::number(message->side.get());
            values[entry + ".payload.partialorderexecutionmessage.price"] = canonical::scaled(message->price.integer(), -6);
            values[entry + ".payload.partialorderexecutionmessage.trdregtstimepriority"] = canonical::number(message->trd_reg_ts_time_priority.get());
            values[entry + ".payload.partialorderexecutionmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.partialorderexecutionmessage.trdmatchid"] = canonical::number(message->trd_match_id.get());
            values[entry + ".payload.partialorderexecutionmessage.lastqty"] = canonical::number(message->last_qty.get());
            values[entry + ".payload.partialorderexecutionmessage.lastpx"] = canonical::scaled(message->last_px.integer(), -6);
        } else if (iterator.template_id == protocol::FullOrderExecutionMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.fullorderexecutionmessage";
            [[maybe_unused]] const auto* message = protocol::FullOrderExecutionMessage::parse(iterator.message);
            values[entry + ".payload.fullorderexecutionmessage.side"] = canonical::number(message->side.get());
            values[entry + ".payload.fullorderexecutionmessage.price"] = canonical::scaled(message->price.integer(), -6);
            values[entry + ".payload.fullorderexecutionmessage.trdregtstimepriority"] = canonical::number(message->trd_reg_ts_time_priority.get());
            values[entry + ".payload.fullorderexecutionmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.fullorderexecutionmessage.trdmatchid"] = canonical::number(message->trd_match_id.get());
            values[entry + ".payload.fullorderexecutionmessage.lastqty"] = canonical::number(message->last_qty.get());
            values[entry + ".payload.fullorderexecutionmessage.lastpx"] = canonical::scaled(message->last_px.integer(), -6);
        } else if (iterator.template_id == protocol::TradeReversalMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.tradereversalmessage";
            [[maybe_unused]] const auto* message = protocol::TradeReversalMessage::parse(iterator.message);
            values[entry + ".payload.tradereversalmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.tradereversalmessage.transacttime"] = canonical::number(message->transact_time.get());
            values[entry + ".payload.tradereversalmessage.trdmatchid"] = canonical::number(message->trd_match_id.get());
            values[entry + ".payload.tradereversalmessage.lastqty"] = canonical::number(message->last_qty.get());
            values[entry + ".payload.tradereversalmessage.lastpx"] = canonical::scaled(message->last_px.integer(), -6);
            values[entry + ".payload.tradereversalmessage.trdregtsexecutiontime"] = (static_cast<std::uint64_t>(message->trd_reg_ts_execution_time.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->trd_reg_ts_execution_time.get()) : canonical::absent());
            values[entry + ".payload.tradereversalmessage.nomdentries"] = canonical::number(message->no_md_entries.get());
        } else if (iterator.template_id == protocol::ExecutionSummaryMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.executionsummarymessage";
            [[maybe_unused]] const auto* message = protocol::ExecutionSummaryMessage::parse(iterator.message);
            values[entry + ".payload.executionsummarymessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.executionsummarymessage.aggressortimestamp"] = (static_cast<std::uint64_t>(message->aggressor_timestamp.get()) != 0x0FFFFFFFFFFFFFFFFULL ? canonical::number(message->aggressor_timestamp.get()) : canonical::absent());
            values[entry + ".payload.executionsummarymessage.execid"] = canonical::number(message->exec_id.get());
            values[entry + ".payload.executionsummarymessage.lastqty"] = canonical::number(message->last_qty.get());
            values[entry + ".payload.executionsummarymessage.aggressorside"] = canonical::number(message->aggressor_side.get());
            values[entry + ".payload.executionsummarymessage.tradecondition"] = (static_cast<std::uint8_t>(message->trade_condition.get()) != 0x0FFU ? canonical::number(message->trade_condition.get()) : canonical::absent());
            values[entry + ".payload.executionsummarymessage.lastpx"] = canonical::scaled(message->last_px.integer(), -6);
            values[entry + ".payload.executionsummarymessage.restinghiddenqty"] = (static_cast<std::uint64_t>(message->resting_hidden_qty.get()) != 0x08000000000000000ULL ? canonical::number(message->resting_hidden_qty.get()) : canonical::absent());
        } else if (iterator.template_id == protocol::InstrumentInfoMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.instrumentinfomessage";
            [[maybe_unused]] const auto* message = protocol::InstrumentInfoMessage::parse(iterator.message);
            values[entry + ".payload.instrumentinfomessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.instrumentinfomessage.closeprice"] = (static_cast<std::uint64_t>(message->close_price.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->close_price.integer(), -6) : canonical::absent());
            values[entry + ".payload.instrumentinfomessage.prevcloseprice"] = (static_cast<std::uint64_t>(message->prev_close_price.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->prev_close_price.integer(), -6) : canonical::absent());
            values[entry + ".payload.instrumentinfomessage.uppercktlimit"] = (static_cast<std::uint64_t>(message->upper_ckt_limit.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->upper_ckt_limit.integer(), -6) : canonical::absent());
            values[entry + ".payload.instrumentinfomessage.lowercktlimit"] = (static_cast<std::uint64_t>(message->lower_ckt_limit.integer()) != 0x08000000000000000ULL ? canonical::scaled(message->lower_ckt_limit.integer(), -6) : canonical::absent());
        } else if (iterator.template_id == protocol::LppRangeMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.lpprangemessage";
            [[maybe_unused]] const auto* message = protocol::LppRangeMessage::parse(iterator.message);
            values[entry + ".payload.lpprangemessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.lpprangemessage.upperexeclimit"] = canonical::scaled(message->upper_exec_limit.integer(), -6);
            values[entry + ".payload.lpprangemessage.lowerexeclimit"] = canonical::scaled(message->lower_exec_limit.integer(), -6);
        } else if (iterator.template_id == protocol::ProductStateChangeMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.productstatechangemessage";
            [[maybe_unused]] const auto* message = protocol::ProductStateChangeMessage::parse(iterator.message);
            values[entry + ".payload.productstatechangemessage.tradingsessionid"] = canonical::number(message->trading_session_id.get());
            values[entry + ".payload.productstatechangemessage.tradingsessionsubid"] = canonical::number(message->trading_session_sub_id.get());
            values[entry + ".payload.productstatechangemessage.tradsesstatus"] = canonical::number(message->trad_ses_status.get());
            values[entry + ".payload.productstatechangemessage.fastmarketindicator"] = canonical::number(message->fast_market_indicator.get());
            values[entry + ".payload.productstatechangemessage.transacttime"] = canonical::number(message->transact_time.get());
        } else if (iterator.template_id == protocol::InstrumentStateChangeMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.instrumentstatechangemessage";
            [[maybe_unused]] const auto* message = protocol::InstrumentStateChangeMessage::parse(iterator.message);
            values[entry + ".payload.instrumentstatechangemessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.instrumentstatechangemessage.securitystatus"] = canonical::number(message->security_status.get());
            values[entry + ".payload.instrumentstatechangemessage.securitytradingstatus"] = canonical::number(message->security_trading_status.get());
            values[entry + ".payload.instrumentstatechangemessage.fastmarketindicator"] = canonical::number(message->fast_market_indicator.get());
            values[entry + ".payload.instrumentstatechangemessage.transacttime"] = canonical::number(message->transact_time.get());
        } else if (iterator.template_id == protocol::AddComplexInstrumentMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.addcomplexinstrumentmessage";
            [[maybe_unused]] const auto* message = protocol::AddComplexInstrumentMessage::parse(iterator.message);
            values[entry + ".payload.addcomplexinstrumentmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.addcomplexinstrumentmessage.transacttime"] = canonical::number(message->transact_time.get());
            values[entry + ".payload.addcomplexinstrumentmessage.securitysubtype"] = (static_cast<std::uint32_t>(message->security_sub_type.get()) != 0x080000000U ? canonical::number(message->security_sub_type.get()) : canonical::absent());
            values[entry + ".payload.addcomplexinstrumentmessage.productcomplex"] = canonical::number(message->product_complex.get());
            values[entry + ".payload.addcomplexinstrumentmessage.impliedmarketindicator"] = canonical::number(message->implied_market_indicator.get());
            values[entry + ".payload.addcomplexinstrumentmessage.nolegs"] = canonical::number(message->no_legs.get());
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
    std::printf("== Bse.BseIndia.Eobi.Fbe.v1.4 (modern values)\n");
    int failures = 0;
    failures += check("ExecutionSummaryMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/ExecutionSummaryMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/ExecutionSummaryMessage.values");
    failures += check("FullOrderExecutionMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/FullOrderExecutionMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/FullOrderExecutionMessage.values");
    failures += check("HeartbeatMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/HeartbeatMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/HeartbeatMessage.values");
    failures += check("InstrumentInfoMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/InstrumentInfoMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/InstrumentInfoMessage.values");
    failures += check("InstrumentStateChangeMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/InstrumentStateChangeMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/InstrumentStateChangeMessage.values");
    failures += check("LppRangeMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/LppRangeMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/LppRangeMessage.values");
    failures += check("OrderAddMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/OrderAddMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/OrderAddMessage.values");
    failures += check("OrderDeleteMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/OrderDeleteMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/OrderDeleteMessage.values");
    failures += check("OrderModifyMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/OrderModifyMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/OrderModifyMessage.values");
    failures += check("PartialOrderExecutionMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/PartialOrderExecutionMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/PartialOrderExecutionMessage.values");
    failures += check("ProductStateChangeMessage", "Bse/BseIndia.Eobi.Fbe.v1.4/ProductStateChangeMessage.pcap", "bse/bseindia/eobi/fbe/v1.4/ProductStateChangeMessage.values");
    return failures == 0 ? 0 : 1;
}
