// Nyse.NyseEquities.Bbo.Xdp.v2.4.g canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/binary/modern/nyse/nyseequities/bbo/xdp/v2.4.g/definitions.hpp"

namespace protocol = ::nyse::nyseequities::bbo::xdp::v2_4_g;

namespace {

// The values the Modern iterator reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    values["packet.packetheader.packetsize"] = canonical::number(iterator.packet_header->packet_size.get());
    values["packet.packetheader.deliveryflag"] = canonical::number(iterator.packet_header->delivery_flag.get());
    values["packet.packetheader.messagecount"] = canonical::number(iterator.packet_header->message_count.get());
    values["packet.packetheader.sequencenumber"] = canonical::number(iterator.packet_header->sequence_number.get());
    values["packet.packetheader.sendtime.seconds"] = canonical::number(iterator.packet_header->send_time.seconds.get());
    values["packet.packetheader.sendtime.nanoseconds"] = canonical::number(iterator.packet_header->send_time.nanoseconds.get());

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(iterator.message_header->message_size.get());
        values[entry + ".messageheader.messagetype"] = canonical::number(iterator.message_header->message_type.get());

        if (iterator.message_type == protocol::SequenceNumberResetMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.sequencenumberresetmessage";
            [[maybe_unused]] const auto* message = protocol::SequenceNumberResetMessage::parse(iterator.message);
            values[entry + ".payload.sequencenumberresetmessage.sourcetime"] = canonical::number(message->source_time.get());
            values[entry + ".payload.sequencenumberresetmessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.sequencenumberresetmessage.productid"] = canonical::number(message->product_id.get());
            values[entry + ".payload.sequencenumberresetmessage.channelid"] = canonical::number(message->channel_id.get());
        } else if (iterator.message_type == protocol::SourceTimeReferenceMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.sourcetimereferencemessage";
            [[maybe_unused]] const auto* message = protocol::SourceTimeReferenceMessage::parse(iterator.message);
            values[entry + ".payload.sourcetimereferencemessage.id"] = canonical::number(message->id.get());
            values[entry + ".payload.sourcetimereferencemessage.symbolseqnum"] = canonical::number(message->symbol_seq_num.get());
            values[entry + ".payload.sourcetimereferencemessage.sourcetime"] = canonical::number(message->source_time.get());
        } else if (iterator.message_type == protocol::SymbolIndexMappingMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.symbolindexmappingmessage";
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
        } else if (iterator.message_type == protocol::RetransmissionRequestMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.retransmissionrequestmessage";
            [[maybe_unused]] const auto* message = protocol::RetransmissionRequestMessage::parse(iterator.message);
            values[entry + ".payload.retransmissionrequestmessage.beginseqnum"] = canonical::number(message->begin_seq_num.get());
            values[entry + ".payload.retransmissionrequestmessage.endseqnum"] = canonical::number(message->end_seq_num.get());
            values[entry + ".payload.retransmissionrequestmessage.sourceid"] = canonical::text(std::string(message->source_id.get()), '\0', false);
            values[entry + ".payload.retransmissionrequestmessage.productid"] = canonical::number(message->product_id.get());
            values[entry + ".payload.retransmissionrequestmessage.channelid"] = canonical::number(message->channel_id.get());
        } else if (iterator.message_type == protocol::RequestResponseMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.requestresponsemessage";
            [[maybe_unused]] const auto* message = protocol::RequestResponseMessage::parse(iterator.message);
            values[entry + ".payload.requestresponsemessage.requestseqnum"] = canonical::number(message->request_seq_num.get());
            values[entry + ".payload.requestresponsemessage.beginseqnum"] = canonical::number(message->begin_seq_num.get());
            values[entry + ".payload.requestresponsemessage.endseqnum"] = canonical::number(message->end_seq_num.get());
            values[entry + ".payload.requestresponsemessage.sourceid"] = canonical::text(std::string(message->source_id.get()), '\0', false);
            values[entry + ".payload.requestresponsemessage.productid"] = canonical::number(message->product_id.get());
            values[entry + ".payload.requestresponsemessage.channelid"] = canonical::number(message->channel_id.get());
            values[entry + ".payload.requestresponsemessage.status"] = canonical::text(canonical::character(message->status.get()), '\0', false);
        } else if (iterator.message_type == protocol::HeartbeatResponseMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.heartbeatresponsemessage";
            [[maybe_unused]] const auto* message = protocol::HeartbeatResponseMessage::parse(iterator.message);
            values[entry + ".payload.heartbeatresponsemessage.sourceid"] = canonical::text(std::string(message->source_id.get()), '\0', false);
        } else if (iterator.message_type == protocol::SymbolIndexMappingRequestMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.symbolindexmappingrequestmessage";
            [[maybe_unused]] const auto* message = protocol::SymbolIndexMappingRequestMessage::parse(iterator.message);
            values[entry + ".payload.symbolindexmappingrequestmessage.symbolindex"] = canonical::number(message->symbol_index.get());
            values[entry + ".payload.symbolindexmappingrequestmessage.sourceid"] = canonical::text(std::string(message->source_id.get()), '\0', false);
            values[entry + ".payload.symbolindexmappingrequestmessage.productid"] = canonical::number(message->product_id.get());
            values[entry + ".payload.symbolindexmappingrequestmessage.channelid"] = canonical::number(message->channel_id.get());
            values[entry + ".payload.symbolindexmappingrequestmessage.retransmitmethod"] = canonical::number(message->retransmit_method.get());
        } else if (iterator.message_type == protocol::RefreshRequestMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.refreshrequestmessage";
            [[maybe_unused]] const auto* message = protocol::RefreshRequestMessage::parse(iterator.message);
            values[entry + ".payload.refreshrequestmessage.symbolindex"] = canonical::number(message->symbol_index.get());
            values[entry + ".payload.refreshrequestmessage.sourceid"] = canonical::text(std::string(message->source_id.get()), '\0', false);
            values[entry + ".payload.refreshrequestmessage.productid"] = canonical::number(message->product_id.get());
            values[entry + ".payload.refreshrequestmessage.channelid"] = canonical::number(message->channel_id.get());
        } else if (iterator.message_type == protocol::MessageUnavailableMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.messageunavailablemessage";
            [[maybe_unused]] const auto* message = protocol::MessageUnavailableMessage::parse(iterator.message);
            values[entry + ".payload.messageunavailablemessage.beginseqnum"] = canonical::number(message->begin_seq_num.get());
            values[entry + ".payload.messageunavailablemessage.endseqnum"] = canonical::number(message->end_seq_num.get());
            values[entry + ".payload.messageunavailablemessage.productid"] = canonical::number(message->product_id.get());
            values[entry + ".payload.messageunavailablemessage.channelid"] = canonical::number(message->channel_id.get());
        } else if (iterator.message_type == protocol::SymbolClearMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.symbolclearmessage";
            [[maybe_unused]] const auto* message = protocol::SymbolClearMessage::parse(iterator.message);
            values[entry + ".payload.symbolclearmessage.sourcetime"] = canonical::number(message->source_time.get());
            values[entry + ".payload.symbolclearmessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.symbolclearmessage.symbolindex"] = canonical::number(message->symbol_index.get());
            values[entry + ".payload.symbolclearmessage.nextsourceseqnum"] = canonical::number(message->next_source_seq_num.get());
        } else if (iterator.message_type == protocol::TradingSessionChangeMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.tradingsessionchangemessage";
            [[maybe_unused]] const auto* message = protocol::TradingSessionChangeMessage::parse(iterator.message);
            values[entry + ".payload.tradingsessionchangemessage.sourcetime"] = canonical::number(message->source_time.get());
            values[entry + ".payload.tradingsessionchangemessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.tradingsessionchangemessage.symbolindex"] = canonical::number(message->symbol_index.get());
            values[entry + ".payload.tradingsessionchangemessage.symbolseqnum"] = canonical::number(message->symbol_seq_num.get());
            values[entry + ".payload.tradingsessionchangemessage.tradingsession"] = canonical::number(message->trading_session.get());
        } else if (iterator.message_type == protocol::SecurityStatusMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.securitystatusmessage";
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
            values[entry + ".payload"] = "packet.message.payload.refreshheadermessage";
            [[maybe_unused]] const auto* message = protocol::RefreshHeaderMessage::parse(iterator.message);
            values[entry + ".payload.refreshheadermessage.currentrefreshpkt"] = canonical::number(message->current_refresh_pkt.get());
            values[entry + ".payload.refreshheadermessage.totalrefreshpkts"] = canonical::number(message->total_refresh_pkts.get());
        } else if (iterator.message_type == protocol::QuoteMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.quotemessage";
            [[maybe_unused]] const auto* message = protocol::QuoteMessage::parse(iterator.message);
            values[entry + ".payload.quotemessage.sourcetimens"] = canonical::number(message->source_time_ns.get());
            values[entry + ".payload.quotemessage.symbolindex"] = canonical::number(message->symbol_index.get());
            values[entry + ".payload.quotemessage.symbolseqnum"] = canonical::number(message->symbol_seq_num.get());
            values[entry + ".payload.quotemessage.askprice"] = canonical::number(message->ask_price.get());
            values[entry + ".payload.quotemessage.askvolume"] = canonical::number(message->ask_volume.get());
            values[entry + ".payload.quotemessage.bidprice"] = canonical::number(message->bid_price.get());
            values[entry + ".payload.quotemessage.bidvolume"] = canonical::number(message->bid_volume.get());
            values[entry + ".payload.quotemessage.quotecondition"] = canonical::text(canonical::character(message->quote_condition.get()), '\0', false);
            values[entry + ".payload.quotemessage.rpiindicator"] = canonical::text(canonical::character(message->rpi_indicator.get()), '\0', false);
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
    std::printf("== Nyse.NyseEquities.Bbo.Xdp.v2.4.g (modern values)\n");
    int failures = 0;
    failures += check("QuoteMessage", "Nyse/NyseEquities.Bbo.Xdp.v2.4.g/QuoteMessage.pcap", "nyse/nyseequities/bbo/xdp/v2.4.g/QuoteMessage.values");
    failures += check("SecurityStatusMessage", "Nyse/NyseEquities.Bbo.Xdp.v2.4.g/SecurityStatusMessage.pcap", "nyse/nyseequities/bbo/xdp/v2.4.g/SecurityStatusMessage.values");
    failures += check("SequenceNumberResetMessage", "Nyse/NyseEquities.Bbo.Xdp.v2.4.g/SequenceNumberResetMessage.pcap", "nyse/nyseequities/bbo/xdp/v2.4.g/SequenceNumberResetMessage.values");
    failures += check("SymbolIndexMappingMessage", "Nyse/NyseEquities.Bbo.Xdp.v2.4.g/SymbolIndexMappingMessage.pcap", "nyse/nyseequities/bbo/xdp/v2.4.g/SymbolIndexMappingMessage.values");
    failures += check("TradingSessionChangeMessage", "Nyse/NyseEquities.Bbo.Xdp.v2.4.g/TradingSessionChangeMessage.pcap", "nyse/nyseequities/bbo/xdp/v2.4.g/TradingSessionChangeMessage.values");
    return failures == 0 ? 0 : 1;
}
