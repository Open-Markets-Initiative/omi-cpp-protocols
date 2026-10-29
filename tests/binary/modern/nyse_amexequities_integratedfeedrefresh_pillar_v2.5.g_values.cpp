// Nyse.AmexEquities.IntegratedFeedRefresh.Pillar.v2.5.g canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/binary/modern/nyse/amexequities/integratedfeedrefresh/pillar/v2.5.g/definitions.hpp"

namespace protocol = ::nyse::amexequities::integratedfeedrefresh::pillar::v2_5_g;

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
            values[entry + ".payload.symbolindexmappingmessage.mpv"] = canonical::number(message->mpv.get());
            values[entry + ".payload.symbolindexmappingmessage.unitoftrade"] = canonical::number(message->unit_of_trade.get());
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
        } else if (iterator.message_type == protocol::RefreshHeaderMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.refreshheadermessage";
            [[maybe_unused]] const auto* message = protocol::RefreshHeaderMessage::parse(iterator.message);
            values[entry + ".payload.refreshheadermessage.currentrefreshpkt"] = canonical::number(message->current_refresh_pkt.get());
            values[entry + ".payload.refreshheadermessage.totalrefreshpkts"] = canonical::number(message->total_refresh_pkts.get());
        } else if (iterator.message_type == protocol::ImbalanceMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.imbalancemessage";
            [[maybe_unused]] const auto* message = protocol::ImbalanceMessage::parse(iterator.message);
            values[entry + ".payload.imbalancemessage.sourcetime"] = canonical::number(message->source_time.get());
            values[entry + ".payload.imbalancemessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.imbalancemessage.symbolindex"] = canonical::number(message->symbol_index.get());
            values[entry + ".payload.imbalancemessage.symbolseqnum"] = canonical::number(message->symbol_seq_num.get());
            values[entry + ".payload.imbalancemessage.referenceprice"] = canonical::number(message->reference_price.get());
            values[entry + ".payload.imbalancemessage.pairedqty"] = canonical::number(message->paired_qty.get());
            values[entry + ".payload.imbalancemessage.totalimbalanceqty"] = canonical::number(message->total_imbalance_qty.get());
            values[entry + ".payload.imbalancemessage.marketimbalanceqty"] = canonical::number(message->market_imbalance_qty.get());
            values[entry + ".payload.imbalancemessage.auctiontime"] = canonical::number(message->auction_time.get());
            values[entry + ".payload.imbalancemessage.auctiontype"] = canonical::text(canonical::character(message->auction_type.get()), '\0', false);
            values[entry + ".payload.imbalancemessage.imbalanceside"] = canonical::text(canonical::character(message->imbalance_side.get()), '\0', false);
            values[entry + ".payload.imbalancemessage.continuousbookclearingprice"] = canonical::number(message->continuous_book_clearing_price.get());
            values[entry + ".payload.imbalancemessage.auctioninterestclearingprice"] = canonical::number(message->auction_interest_clearing_price.get());
            values[entry + ".payload.imbalancemessage.ssrfilingprice"] = canonical::number(message->ssr_filing_price.get());
            values[entry + ".payload.imbalancemessage.indicativematchprice"] = canonical::number(message->indicative_match_price.get());
            values[entry + ".payload.imbalancemessage.uppercollar"] = canonical::number(message->upper_collar.get());
            values[entry + ".payload.imbalancemessage.lowercollar"] = canonical::number(message->lower_collar.get());
            values[entry + ".payload.imbalancemessage.auctionstatus"] = canonical::number(message->auction_status.get());
            values[entry + ".payload.imbalancemessage.freezestatus"] = canonical::number(message->freeze_status.get());
            values[entry + ".payload.imbalancemessage.numextensions"] = canonical::number(message->num_extensions.get());
            values[entry + ".payload.imbalancemessage.unpairedqty"] = canonical::number(message->unpaired_qty.get());
            values[entry + ".payload.imbalancemessage.unpairedside"] = canonical::text(canonical::character(message->unpaired_side.get()), '\0', false);
        } else if (iterator.message_type == protocol::AddOrderRefreshMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.addorderrefreshmessage";
            [[maybe_unused]] const auto* message = protocol::AddOrderRefreshMessage::parse(iterator.message);
            values[entry + ".payload.addorderrefreshmessage.sourcetime"] = canonical::number(message->source_time.get());
            values[entry + ".payload.addorderrefreshmessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.addorderrefreshmessage.symbolindex"] = canonical::number(message->symbol_index.get());
            values[entry + ".payload.addorderrefreshmessage.symbolseqnum"] = canonical::number(message->symbol_seq_num.get());
            values[entry + ".payload.addorderrefreshmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.addorderrefreshmessage.price"] = canonical::number(message->price.get());
            values[entry + ".payload.addorderrefreshmessage.volume"] = canonical::number(message->volume.get());
            values[entry + ".payload.addorderrefreshmessage.side"] = canonical::text(canonical::character(message->side.get()), '\0', false);
            values[entry + ".payload.addorderrefreshmessage.firmid"] = canonical::text(std::string(message->firm_id.get()), ' ', false);
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
    std::printf("== Nyse.AmexEquities.IntegratedFeedRefresh.Pillar.v2.5.g (modern values)\n");
    int failures = 0;
    failures += check("AddOrderRefreshMessage", "Nyse/AmexEquities.IntegratedFeedRefresh.Pillar.v2.5.g/AddOrderRefreshMessage.pcap", "nyse/amexequities/integratedfeedrefresh/pillar/v2.5.g/AddOrderRefreshMessage.values");
    failures += check("ImbalanceMessage", "Nyse/AmexEquities.IntegratedFeedRefresh.Pillar.v2.5.g/ImbalanceMessage.pcap", "nyse/amexequities/integratedfeedrefresh/pillar/v2.5.g/ImbalanceMessage.values");
    failures += check("RefreshHeaderMessage", "Nyse/AmexEquities.IntegratedFeedRefresh.Pillar.v2.5.g/RefreshHeaderMessage.pcap", "nyse/amexequities/integratedfeedrefresh/pillar/v2.5.g/RefreshHeaderMessage.values");
    failures += check("SecurityStatusMessage", "Nyse/AmexEquities.IntegratedFeedRefresh.Pillar.v2.5.g/SecurityStatusMessage.pcap", "nyse/amexequities/integratedfeedrefresh/pillar/v2.5.g/SecurityStatusMessage.values");
    failures += check("SymbolIndexMappingMessage", "Nyse/AmexEquities.IntegratedFeedRefresh.Pillar.v2.5.g/SymbolIndexMappingMessage.pcap", "nyse/amexequities/integratedfeedrefresh/pillar/v2.5.g/SymbolIndexMappingMessage.values");
    return failures == 0 ? 0 : 1;
}
