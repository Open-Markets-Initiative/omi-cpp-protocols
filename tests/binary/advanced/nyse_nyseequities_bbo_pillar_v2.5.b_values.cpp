// Nyse.NyseEquities.Bbo.Pillar.v2.5.b canonical values, through the Advanced session layer: every value Advanced
// reads from each sample, at its address, held to what the model reads.

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
#include "cpp/binary/advanced/nyse/nyseequities/bbo/pillar/v2.5.b/messages/session.hpp"

namespace protocol = ::nyse::nyseequities::bbo::pillar::v2_5_b;

namespace {

// The handler the session layer hands each datagram's values to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    protocol::seq_action on_transport_header(const protocol::packet_header& header, const packet::Frame&) {
        values["packet.packetheader.pktsize"] = canonical::number(header.pkt_size.get().value());
        values["packet.packetheader.deliveryflag"] = canonical::number(header.delivery_flag.get().value());
        values["packet.packetheader.numbermsgs"] = canonical::number(header.number_msgs.get().value());
        values["packet.packetheader.seqnum"] = canonical::number(header.seq_num.get().value());
        values["packet.packetheader.sendtime.seconds"] = canonical::number(header.send_time.seconds.get().value());
        values["packet.packetheader.sendtime.nanoseconds"] = canonical::number(header.send_time.nanoseconds.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::packet_header&) {
        ++index;
    }

    void on_message(const protocol::sequence_number_reset_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.sequencenumberresetmessage";
        values[entry + ".payload.sequencenumberresetmessage.sourcetime"] = canonical::number(message.fields.source_time.get().value());
        values[entry + ".payload.sequencenumberresetmessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.sequencenumberresetmessage.productid"] = canonical::number(message.fields.product_id.get().value());
        values[entry + ".payload.sequencenumberresetmessage.channelid"] = canonical::number(message.fields.channel_id.get().value());
    }

    void on_message(const protocol::source_time_reference_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.sourcetimereferencemessage";
        values[entry + ".payload.sourcetimereferencemessage.id"] = canonical::number(message.fields.id.get().value());
        values[entry + ".payload.sourcetimereferencemessage.symbolseqnum"] = canonical::number(message.fields.symbol_seq_num.get().value());
        values[entry + ".payload.sourcetimereferencemessage.sourcetime"] = canonical::number(message.fields.source_time.get().value());
    }

    void on_message(const protocol::symbol_index_mapping_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.symbolindexmappingmessage";
        values[entry + ".payload.symbolindexmappingmessage.symbolindex"] = canonical::number(message.fields.symbol_index.get().value());
        values[entry + ".payload.symbolindexmappingmessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), '\0', false);
        values[entry + ".payload.symbolindexmappingmessage.marketid"] = canonical::number(message.fields.market_id.get().value());
        values[entry + ".payload.symbolindexmappingmessage.systemid"] = canonical::number(message.fields.system_id.get().value());
        values[entry + ".payload.symbolindexmappingmessage.exchangecode"] = canonical::text(canonical::character(message.fields.exchange_code.get().value()), '\0', false);
        values[entry + ".payload.symbolindexmappingmessage.pricescalecode"] = canonical::number(message.fields.price_scale_code.get().value());
        values[entry + ".payload.symbolindexmappingmessage.securitytype"] = canonical::text(canonical::character(message.fields.security_type.get().value()), '\0', false);
        values[entry + ".payload.symbolindexmappingmessage.lotsize"] = canonical::number(message.fields.lot_size.get().value());
        values[entry + ".payload.symbolindexmappingmessage.prevcloseprice"] = canonical::number(message.fields.prev_close_price.get().value());
        values[entry + ".payload.symbolindexmappingmessage.prevclosevolume"] = canonical::number(message.fields.prev_close_volume.get().value());
        values[entry + ".payload.symbolindexmappingmessage.priceresolution"] = canonical::number(message.fields.price_resolution.get().value());
        values[entry + ".payload.symbolindexmappingmessage.roundlot"] = canonical::text(canonical::character(message.fields.round_lot.get().value()), '\0', false);
        values[entry + ".payload.symbolindexmappingmessage.mpv"] = canonical::number(message.fields.mpv.get().value());
        values[entry + ".payload.symbolindexmappingmessage.unitoftrade"] = canonical::number(message.fields.unit_of_trade.get().value());
    }

    void on_message(const protocol::retransmission_request_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.retransmissionrequestmessage";
        values[entry + ".payload.retransmissionrequestmessage.beginseqnum"] = canonical::number(message.fields.begin_seq_num.get().value());
        values[entry + ".payload.retransmissionrequestmessage.endseqnum"] = canonical::number(message.fields.end_seq_num.get().value());
        values[entry + ".payload.retransmissionrequestmessage.sourceid"] = canonical::text(std::string(message.fields.source_id.get().value()), '\0', false);
        values[entry + ".payload.retransmissionrequestmessage.productid"] = canonical::number(message.fields.product_id.get().value());
        values[entry + ".payload.retransmissionrequestmessage.channelid"] = canonical::number(message.fields.channel_id.get().value());
    }

    void on_message(const protocol::request_response_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.requestresponsemessage";
        values[entry + ".payload.requestresponsemessage.requestseqnum"] = canonical::number(message.fields.request_seq_num.get().value());
        values[entry + ".payload.requestresponsemessage.beginseqnum"] = canonical::number(message.fields.begin_seq_num.get().value());
        values[entry + ".payload.requestresponsemessage.endseqnum"] = canonical::number(message.fields.end_seq_num.get().value());
        values[entry + ".payload.requestresponsemessage.sourceid"] = canonical::text(std::string(message.fields.source_id.get().value()), '\0', false);
        values[entry + ".payload.requestresponsemessage.productid"] = canonical::number(message.fields.product_id.get().value());
        values[entry + ".payload.requestresponsemessage.channelid"] = canonical::number(message.fields.channel_id.get().value());
        values[entry + ".payload.requestresponsemessage.status"] = canonical::text(canonical::character(message.fields.status.get().value()), '\0', false);
    }

    void on_message(const protocol::heartbeat_response_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.heartbeatresponsemessage";
        values[entry + ".payload.heartbeatresponsemessage.sourceid"] = canonical::text(std::string(message.fields.source_id.get().value()), '\0', false);
    }

    void on_message(const protocol::symbol_index_mapping_request_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.symbolindexmappingrequestmessage";
        values[entry + ".payload.symbolindexmappingrequestmessage.symbolindex"] = canonical::number(message.fields.symbol_index.get().value());
        values[entry + ".payload.symbolindexmappingrequestmessage.sourceid"] = canonical::text(std::string(message.fields.source_id.get().value()), '\0', false);
        values[entry + ".payload.symbolindexmappingrequestmessage.productid"] = canonical::number(message.fields.product_id.get().value());
        values[entry + ".payload.symbolindexmappingrequestmessage.channelid"] = canonical::number(message.fields.channel_id.get().value());
        values[entry + ".payload.symbolindexmappingrequestmessage.retransmitmethod"] = canonical::number(message.fields.retransmit_method.get().value());
    }

    void on_message(const protocol::refresh_request_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.refreshrequestmessage";
        values[entry + ".payload.refreshrequestmessage.symbolindex"] = canonical::number(message.fields.symbol_index.get().value());
        values[entry + ".payload.refreshrequestmessage.sourceid"] = canonical::text(std::string(message.fields.source_id.get().value()), '\0', false);
        values[entry + ".payload.refreshrequestmessage.productid"] = canonical::number(message.fields.product_id.get().value());
        values[entry + ".payload.refreshrequestmessage.channelid"] = canonical::number(message.fields.channel_id.get().value());
    }

    void on_message(const protocol::message_unavailable_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.messageunavailablemessage";
        values[entry + ".payload.messageunavailablemessage.beginseqnum"] = canonical::number(message.fields.begin_seq_num.get().value());
        values[entry + ".payload.messageunavailablemessage.endseqnum"] = canonical::number(message.fields.end_seq_num.get().value());
        values[entry + ".payload.messageunavailablemessage.productid"] = canonical::number(message.fields.product_id.get().value());
        values[entry + ".payload.messageunavailablemessage.channelid"] = canonical::number(message.fields.channel_id.get().value());
    }

    void on_message(const protocol::symbol_clear_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.symbolclearmessage";
        values[entry + ".payload.symbolclearmessage.sourcetime"] = canonical::number(message.fields.source_time.get().value());
        values[entry + ".payload.symbolclearmessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.symbolclearmessage.symbolindex"] = canonical::number(message.fields.symbol_index.get().value());
        values[entry + ".payload.symbolclearmessage.nextsourceseqnum"] = canonical::number(message.fields.next_source_seq_num.get().value());
    }

    void on_message(const protocol::security_status_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.securitystatusmessage";
        values[entry + ".payload.securitystatusmessage.sourcetime"] = canonical::number(message.fields.source_time.get().value());
        values[entry + ".payload.securitystatusmessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.securitystatusmessage.symbolindex"] = canonical::number(message.fields.symbol_index.get().value());
        values[entry + ".payload.securitystatusmessage.symbolseqnum"] = canonical::number(message.fields.symbol_seq_num.get().value());
        values[entry + ".payload.securitystatusmessage.securitystatus"] = canonical::text(canonical::character(message.fields.security_status.get().value()), '\0', false);
        values[entry + ".payload.securitystatusmessage.haltcondition"] = canonical::text(canonical::character(message.fields.halt_condition.get().value()), '\0', false);
        values[entry + ".payload.securitystatusmessage.price1"] = canonical::number(message.fields.price_1.get().value());
        values[entry + ".payload.securitystatusmessage.price2"] = canonical::number(message.fields.price_2.get().value());
        values[entry + ".payload.securitystatusmessage.ssrtriggeringexchangeid"] = canonical::text(canonical::character(message.fields.ssr_triggering_exchange_id.get().value()), '\0', false);
        values[entry + ".payload.securitystatusmessage.ssrtriggeringvolume"] = canonical::number(message.fields.ssr_triggering_volume.get().value());
        values[entry + ".payload.securitystatusmessage.time"] = (message.fields.time.get().has_value() ? canonical::number(message.fields.time.get().value()) : canonical::absent());
        values[entry + ".payload.securitystatusmessage.ssrstate"] = canonical::text(canonical::character(message.fields.ssr_state.get().value()), '\0', false);
        values[entry + ".payload.securitystatusmessage.marketstate"] = canonical::text(canonical::character(message.fields.market_state.get().value()), '\0', false);
        values[entry + ".payload.securitystatusmessage.sessionstate"] = canonical::text(canonical::character(message.fields.session_state.get().value()), '\0', false);
    }

    void on_message(const protocol::refresh_header_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.refreshheadermessage";
        values[entry + ".payload.refreshheadermessage.currentrefreshpkt"] = canonical::number(message.fields.current_refresh_pkt.get().value());
        values[entry + ".payload.refreshheadermessage.totalrefreshpkts"] = canonical::number(message.fields.total_refresh_pkts.get().value());
    }

    void on_message(const protocol::quote_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(message.header.message_size.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::number(message.header.message_type.get().value());
        values[entry + ".payload"] = "packet.messages.message.payload.quotemessage";
        values[entry + ".payload.quotemessage.sourcetimens"] = canonical::number(message.fields.source_time_ns.get().value());
        values[entry + ".payload.quotemessage.symbolindex"] = canonical::number(message.fields.symbol_index.get().value());
        values[entry + ".payload.quotemessage.symbolseqnum"] = canonical::number(message.fields.symbol_seq_num.get().value());
        values[entry + ".payload.quotemessage.askprice"] = canonical::number(message.fields.ask_price.get().value());
        values[entry + ".payload.quotemessage.askvolume"] = canonical::number(message.fields.ask_volume.get().value());
        values[entry + ".payload.quotemessage.bidprice"] = canonical::number(message.fields.bid_price.get().value());
        values[entry + ".payload.quotemessage.bidvolume"] = canonical::number(message.fields.bid_volume.get().value());
        values[entry + ".payload.quotemessage.quotecondition"] = canonical::text(canonical::character(message.fields.quote_condition.get().value()), '\0', false);
        values[entry + ".payload.quotemessage.rpiindicator"] = canonical::text(canonical::character(message.fields.rpi_indicator.get().value()), '\0', false);
    }
};

// The values Advanced reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    Reader reader;
    protocol::process_segment(reader, frame.payload, frame.payload_len, 0, frame);
    return reader.values;
}

// Read each datagram of a sample with Advanced and hold it to the model's values
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
    std::printf("== Nyse.NyseEquities.Bbo.Pillar.v2.5.b (advanced values)\n");
    int failures = 0;
    failures += check("QuoteMessage", "Nyse/NyseEquities.Bbo.Pillar.v2.5.b/QuoteMessage.pcap", "nyse/nyseequities/bbo/pillar/v2.5.b/QuoteMessage.values");
    failures += check("RefreshHeaderMessage", "Nyse/NyseEquities.Bbo.Pillar.v2.5.b/RefreshHeaderMessage.pcap", "nyse/nyseequities/bbo/pillar/v2.5.b/RefreshHeaderMessage.values");
    failures += check("SecurityStatusMessage", "Nyse/NyseEquities.Bbo.Pillar.v2.5.b/SecurityStatusMessage.pcap", "nyse/nyseequities/bbo/pillar/v2.5.b/SecurityStatusMessage.values");
    failures += check("SourceTimeReferenceMessage", "Nyse/NyseEquities.Bbo.Pillar.v2.5.b/SourceTimeReferenceMessage.pcap", "nyse/nyseequities/bbo/pillar/v2.5.b/SourceTimeReferenceMessage.values");
    return failures == 0 ? 0 : 1;
}
