// Nyse.ArcaEquities.Bbo.Xdp.v2.4.c canonical values, through the Flyweight reader: every value Flyweight reads
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
#include "cpp/binary/flyweight/nyse/arcaequities/bbo/xdp/v2.4.c/definitions.hpp"

namespace protocol = ::nyse::arcaequities::bbo::xdp::v2_4_c;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        values["packet.packetheader.packetsize"] = canonical::number(packet.packet_header().packet_size());
        values["packet.packetheader.deliveryflag"] = canonical::number(packet.packet_header().delivery_flag());
        values["packet.packetheader.messagecount"] = canonical::number(packet.packet_header().message_count());
        values["packet.packetheader.sequencenumber"] = canonical::number(packet.packet_header().sequence_number());
        values["packet.packetheader.sendtime.seconds"] = canonical::number(packet.packet_header().send_time().seconds());
        values["packet.packetheader.sendtime.nanoseconds"] = canonical::number(packet.packet_header().send_time().nanoseconds());
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

    void on(const protocol::SequenceNumberResetMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.sequencenumberresetmessage";
        values[entry + ".payload.sequencenumberresetmessage.sourcetime"] = canonical::number(message.source_time());
        values[entry + ".payload.sequencenumberresetmessage.sourcetimens"] = canonical::number(message.source_time_ns());
        values[entry + ".payload.sequencenumberresetmessage.productid"] = canonical::number(message.product_id());
        values[entry + ".payload.sequencenumberresetmessage.channelid"] = canonical::number(message.channel_id());
    }

    void on(const protocol::SourceTimeReferenceMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.sourcetimereferencemessage";
        values[entry + ".payload.sourcetimereferencemessage.id"] = canonical::number(message.id());
        values[entry + ".payload.sourcetimereferencemessage.symbolseqnum"] = canonical::number(message.symbol_seq_num());
        values[entry + ".payload.sourcetimereferencemessage.sourcetime"] = canonical::number(message.source_time());
    }

    void on(const protocol::SymbolIndexMappingMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.symbolindexmappingmessage";
        values[entry + ".payload.symbolindexmappingmessage.symbolindex"] = canonical::number(message.symbol_index());
        values[entry + ".payload.symbolindexmappingmessage.symbol"] = canonical::text(std::string(message.symbol()), '\0', false);
        values[entry + ".payload.symbolindexmappingmessage.marketid"] = canonical::number(message.market_id());
        values[entry + ".payload.symbolindexmappingmessage.systemid"] = canonical::number(message.system_id());
        values[entry + ".payload.symbolindexmappingmessage.exchangecode"] = canonical::text(canonical::character(message.exchange_code()), '\0', false);
        values[entry + ".payload.symbolindexmappingmessage.pricescalecode"] = canonical::number(message.price_scale_code());
        values[entry + ".payload.symbolindexmappingmessage.securitytype"] = canonical::text(canonical::character(message.security_type()), '\0', false);
        values[entry + ".payload.symbolindexmappingmessage.lotsize"] = canonical::number(message.lot_size());
        values[entry + ".payload.symbolindexmappingmessage.prevcloseprice"] = canonical::number(message.prev_close_price());
        values[entry + ".payload.symbolindexmappingmessage.prevclosevolume"] = canonical::number(message.prev_close_volume());
        values[entry + ".payload.symbolindexmappingmessage.priceresolution"] = canonical::number(message.price_resolution());
        values[entry + ".payload.symbolindexmappingmessage.roundlot"] = canonical::text(canonical::character(message.round_lot()), '\0', false);
        values[entry + ".payload.symbolindexmappingmessage.mpv"] = canonical::number(message.mpv());
        values[entry + ".payload.symbolindexmappingmessage.unitoftrade"] = canonical::number(message.unit_of_trade());
    }

    void on(const protocol::RetransmissionRequestMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.retransmissionrequestmessage";
        values[entry + ".payload.retransmissionrequestmessage.beginseqnum"] = canonical::number(message.begin_seq_num());
        values[entry + ".payload.retransmissionrequestmessage.endseqnum"] = canonical::number(message.end_seq_num());
        values[entry + ".payload.retransmissionrequestmessage.sourceid"] = canonical::text(std::string(message.source_id()), '\0', false);
        values[entry + ".payload.retransmissionrequestmessage.productid"] = canonical::number(message.product_id());
        values[entry + ".payload.retransmissionrequestmessage.channelid"] = canonical::number(message.channel_id());
    }

    void on(const protocol::RequestResponseMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.requestresponsemessage";
        values[entry + ".payload.requestresponsemessage.requestseqnum"] = canonical::number(message.request_seq_num());
        values[entry + ".payload.requestresponsemessage.beginseqnum"] = canonical::number(message.begin_seq_num());
        values[entry + ".payload.requestresponsemessage.endseqnum"] = canonical::number(message.end_seq_num());
        values[entry + ".payload.requestresponsemessage.sourceid"] = canonical::text(std::string(message.source_id()), '\0', false);
        values[entry + ".payload.requestresponsemessage.productid"] = canonical::number(message.product_id());
        values[entry + ".payload.requestresponsemessage.channelid"] = canonical::number(message.channel_id());
        values[entry + ".payload.requestresponsemessage.status"] = canonical::text(canonical::character(message.status()), '\0', false);
    }

    void on(const protocol::HeartbeatResponseMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.heartbeatresponsemessage";
        values[entry + ".payload.heartbeatresponsemessage.sourceid"] = canonical::text(std::string(message.source_id()), '\0', false);
    }

    void on(const protocol::SymbolIndexMappingRequestMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.symbolindexmappingrequestmessage";
        values[entry + ".payload.symbolindexmappingrequestmessage.symbolindex"] = canonical::number(message.symbol_index());
        values[entry + ".payload.symbolindexmappingrequestmessage.sourceid"] = canonical::text(std::string(message.source_id()), '\0', false);
        values[entry + ".payload.symbolindexmappingrequestmessage.productid"] = canonical::number(message.product_id());
        values[entry + ".payload.symbolindexmappingrequestmessage.channelid"] = canonical::number(message.channel_id());
        values[entry + ".payload.symbolindexmappingrequestmessage.retransmitmethod"] = canonical::number(message.retransmit_method());
    }

    void on(const protocol::RefreshRequestMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.refreshrequestmessage";
        values[entry + ".payload.refreshrequestmessage.symbolindex"] = canonical::number(message.symbol_index());
        values[entry + ".payload.refreshrequestmessage.sourceid"] = canonical::text(std::string(message.source_id()), '\0', false);
        values[entry + ".payload.refreshrequestmessage.productid"] = canonical::number(message.product_id());
        values[entry + ".payload.refreshrequestmessage.channelid"] = canonical::number(message.channel_id());
    }

    void on(const protocol::MessageUnavailableMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.messageunavailablemessage";
        values[entry + ".payload.messageunavailablemessage.beginseqnum"] = canonical::number(message.begin_seq_num());
        values[entry + ".payload.messageunavailablemessage.endseqnum"] = canonical::number(message.end_seq_num());
        values[entry + ".payload.messageunavailablemessage.productid"] = canonical::number(message.product_id());
        values[entry + ".payload.messageunavailablemessage.channelid"] = canonical::number(message.channel_id());
    }

    void on(const protocol::SymbolClearMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.symbolclearmessage";
        values[entry + ".payload.symbolclearmessage.sourcetime"] = canonical::number(message.source_time());
        values[entry + ".payload.symbolclearmessage.sourcetimens"] = canonical::number(message.source_time_ns());
        values[entry + ".payload.symbolclearmessage.symbolindex"] = canonical::number(message.symbol_index());
        values[entry + ".payload.symbolclearmessage.nextsourceseqnum"] = canonical::number(message.next_source_seq_num());
    }

    void on(const protocol::TradingSessionChangeMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.tradingsessionchangemessage";
        values[entry + ".payload.tradingsessionchangemessage.sourcetime"] = canonical::number(message.source_time());
        values[entry + ".payload.tradingsessionchangemessage.sourcetimens"] = canonical::number(message.source_time_ns());
        values[entry + ".payload.tradingsessionchangemessage.symbolindex"] = canonical::number(message.symbol_index());
        values[entry + ".payload.tradingsessionchangemessage.symbolseqnum"] = canonical::number(message.symbol_seq_num());
        values[entry + ".payload.tradingsessionchangemessage.tradingsession"] = canonical::number(message.trading_session());
    }

    void on(const protocol::SecurityStatusMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.securitystatusmessage";
        values[entry + ".payload.securitystatusmessage.sourcetime"] = canonical::number(message.source_time());
        values[entry + ".payload.securitystatusmessage.sourcetimens"] = canonical::number(message.source_time_ns());
        values[entry + ".payload.securitystatusmessage.symbolindex"] = canonical::number(message.symbol_index());
        values[entry + ".payload.securitystatusmessage.symbolseqnum"] = canonical::number(message.symbol_seq_num());
        values[entry + ".payload.securitystatusmessage.securitystatus"] = canonical::text(canonical::character(message.security_status()), '\0', false);
        values[entry + ".payload.securitystatusmessage.haltcondition"] = canonical::text(canonical::character(message.halt_condition()), '\0', false);
        values[entry + ".payload.securitystatusmessage.price1"] = canonical::number(message.price_1());
        values[entry + ".payload.securitystatusmessage.price2"] = canonical::number(message.price_2());
        values[entry + ".payload.securitystatusmessage.ssrtriggeringexchangeid"] = canonical::text(canonical::character(message.ssr_triggering_exchange_id()), '\0', false);
        values[entry + ".payload.securitystatusmessage.ssrtriggeringvolume"] = canonical::number(message.ssr_triggering_volume());
        values[entry + ".payload.securitystatusmessage.time"] = (message.time().has_value() ? canonical::number((*message.time())) : canonical::absent());
        values[entry + ".payload.securitystatusmessage.ssrstate"] = canonical::text(canonical::character(message.ssr_state()), '\0', false);
        values[entry + ".payload.securitystatusmessage.marketstate"] = canonical::text(canonical::character(message.market_state()), '\0', false);
        values[entry + ".payload.securitystatusmessage.sessionstate"] = canonical::text(canonical::character(message.session_state()), '\0', false);
    }

    void on(const protocol::RefreshHeaderMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.refreshheadermessage";
        values[entry + ".payload.refreshheadermessage.currentrefreshpkt"] = canonical::number(message.current_refresh_pkt());
        values[entry + ".payload.refreshheadermessage.totalrefreshpkts"] = canonical::number(message.total_refresh_pkts());
    }

    void on(const protocol::QuoteMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.quotemessage";
        values[entry + ".payload.quotemessage.sourcetimens"] = canonical::number(message.source_time_ns());
        values[entry + ".payload.quotemessage.symbolindex"] = canonical::number(message.symbol_index());
        values[entry + ".payload.quotemessage.symbolseqnum"] = canonical::number(message.symbol_seq_num());
        values[entry + ".payload.quotemessage.askprice"] = canonical::number(message.ask_price());
        values[entry + ".payload.quotemessage.askvolume"] = canonical::number(message.ask_volume());
        values[entry + ".payload.quotemessage.bidprice"] = canonical::number(message.bid_price());
        values[entry + ".payload.quotemessage.bidvolume"] = canonical::number(message.bid_volume());
        values[entry + ".payload.quotemessage.quotecondition"] = canonical::text(canonical::character(message.quote_condition()), '\0', false);
        values[entry + ".payload.quotemessage.rpiindicator"] = canonical::text(canonical::character(message.rpi_indicator()), '\0', false);
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
    std::printf("== Nyse.ArcaEquities.Bbo.Xdp.v2.4.c (flyweight values)\n");
    int failures = 0;
    failures += check("QuoteMessage", "Nyse/ArcaEquities.Bbo.Xdp.v2.4.c/QuoteMessage.pcap", "nyse/arcaequities/bbo/xdp/v2.4.c/QuoteMessage.values");
    failures += check("SequenceNumberResetMessage", "Nyse/ArcaEquities.Bbo.Xdp.v2.4.c/SequenceNumberResetMessage.pcap", "nyse/arcaequities/bbo/xdp/v2.4.c/SequenceNumberResetMessage.values");
    failures += check("SymbolIndexMappingMessage", "Nyse/ArcaEquities.Bbo.Xdp.v2.4.c/SymbolIndexMappingMessage.pcap", "nyse/arcaequities/bbo/xdp/v2.4.c/SymbolIndexMappingMessage.values");
    return failures == 0 ? 0 : 1;
}
