// Nyse.ArcaEquities.IntegratedFeedRefresh.Pillar.v2.5.g canonical values, through the Flyweight reader: every value Flyweight reads
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
#include "cpp/binary/flyweight/nyse/arcaequities/integratedfeedrefresh/pillar/v2.5.g/definitions.hpp"

namespace protocol = ::nyse::arcaequities::integratedfeedrefresh::pillar::v2_5_g;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        values["packet.packetheader.pktsize"] = canonical::number(packet.packet_header().pkt_size());
        values["packet.packetheader.deliveryflag"] = canonical::number(packet.packet_header().delivery_flag());
        values["packet.packetheader.numbermsgs"] = canonical::number(packet.packet_header().number_msgs());
        values["packet.packetheader.seqnum"] = canonical::number(packet.packet_header().seq_num());
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
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.sequencenumberresetmessage";
        values[entry + ".payload.sequencenumberresetmessage.sourcetime"] = canonical::number(message.source_time());
        values[entry + ".payload.sequencenumberresetmessage.sourcetimens"] = canonical::number(message.source_time_ns());
        values[entry + ".payload.sequencenumberresetmessage.productid"] = canonical::number(message.product_id());
        values[entry + ".payload.sequencenumberresetmessage.channelid"] = canonical::number(message.channel_id());
    }

    void on(const protocol::SourceTimeReferenceMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.sourcetimereferencemessage";
        values[entry + ".payload.sourcetimereferencemessage.id"] = canonical::number(message.id());
        values[entry + ".payload.sourcetimereferencemessage.symbolseqnum"] = canonical::number(message.symbol_seq_num());
        values[entry + ".payload.sourcetimereferencemessage.sourcetime"] = canonical::number(message.source_time());
    }

    void on(const protocol::SymbolIndexMappingMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.symbolindexmappingmessage";
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

    void on(const protocol::SecurityStatusMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.securitystatusmessage";
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
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.refreshheadermessage";
        values[entry + ".payload.refreshheadermessage.currentrefreshpkt"] = canonical::number(message.current_refresh_pkt());
        values[entry + ".payload.refreshheadermessage.totalrefreshpkts"] = canonical::number(message.total_refresh_pkts());
    }

    void on(const protocol::ImbalanceMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.imbalancemessage";
        values[entry + ".payload.imbalancemessage.sourcetime"] = canonical::number(message.source_time());
        values[entry + ".payload.imbalancemessage.sourcetimens"] = canonical::number(message.source_time_ns());
        values[entry + ".payload.imbalancemessage.symbolindex"] = canonical::number(message.symbol_index());
        values[entry + ".payload.imbalancemessage.symbolseqnum"] = canonical::number(message.symbol_seq_num());
        values[entry + ".payload.imbalancemessage.referenceprice"] = canonical::number(message.reference_price());
        values[entry + ".payload.imbalancemessage.pairedqty"] = canonical::number(message.paired_qty());
        values[entry + ".payload.imbalancemessage.totalimbalanceqty"] = canonical::number(message.total_imbalance_qty());
        values[entry + ".payload.imbalancemessage.marketimbalanceqty"] = canonical::number(message.market_imbalance_qty());
        values[entry + ".payload.imbalancemessage.auctiontime"] = canonical::number(message.auction_time());
        values[entry + ".payload.imbalancemessage.auctiontype"] = canonical::text(canonical::character(message.auction_type()), '\0', false);
        values[entry + ".payload.imbalancemessage.imbalanceside"] = canonical::text(canonical::character(message.imbalance_side()), '\0', false);
        values[entry + ".payload.imbalancemessage.continuousbookclearingprice"] = canonical::number(message.continuous_book_clearing_price());
        values[entry + ".payload.imbalancemessage.auctioninterestclearingprice"] = canonical::number(message.auction_interest_clearing_price());
        values[entry + ".payload.imbalancemessage.ssrfilingprice"] = canonical::number(message.ssr_filing_price());
        values[entry + ".payload.imbalancemessage.indicativematchprice"] = canonical::number(message.indicative_match_price());
        values[entry + ".payload.imbalancemessage.uppercollar"] = canonical::number(message.upper_collar());
        values[entry + ".payload.imbalancemessage.lowercollar"] = canonical::number(message.lower_collar());
        values[entry + ".payload.imbalancemessage.auctionstatus"] = canonical::number(message.auction_status());
        values[entry + ".payload.imbalancemessage.freezestatus"] = canonical::number(message.freeze_status());
        values[entry + ".payload.imbalancemessage.numextensions"] = canonical::number(message.num_extensions());
        values[entry + ".payload.imbalancemessage.unpairedqty"] = canonical::number(message.unpaired_qty());
        values[entry + ".payload.imbalancemessage.unpairedside"] = canonical::text(canonical::character(message.unpaired_side()), '\0', false);
    }

    void on(const protocol::AddOrderRefreshMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.addorderrefreshmessage";
        values[entry + ".payload.addorderrefreshmessage.sourcetime"] = canonical::number(message.source_time());
        values[entry + ".payload.addorderrefreshmessage.sourcetimens"] = canonical::number(message.source_time_ns());
        values[entry + ".payload.addorderrefreshmessage.symbolindex"] = canonical::number(message.symbol_index());
        values[entry + ".payload.addorderrefreshmessage.symbolseqnum"] = canonical::number(message.symbol_seq_num());
        values[entry + ".payload.addorderrefreshmessage.orderid"] = canonical::number(message.order_id());
        values[entry + ".payload.addorderrefreshmessage.price"] = canonical::number(message.price());
        values[entry + ".payload.addorderrefreshmessage.volume"] = canonical::number(message.volume());
        values[entry + ".payload.addorderrefreshmessage.side"] = canonical::text(canonical::character(message.side()), '\0', false);
        values[entry + ".payload.addorderrefreshmessage.firmid"] = canonical::text(std::string(message.firm_id()), ' ', false);
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
    std::printf("== Nyse.ArcaEquities.IntegratedFeedRefresh.Pillar.v2.5.g (flyweight values)\n");
    int failures = 0;
    failures += check("AddOrderRefreshMessage", "Nyse/ArcaEquities.IntegratedFeedRefresh.Pillar.v2.5.g/AddOrderRefreshMessage.pcap", "nyse/arcaequities/integratedfeedrefresh/pillar/v2.5.g/AddOrderRefreshMessage.values");
    failures += check("ImbalanceMessage", "Nyse/ArcaEquities.IntegratedFeedRefresh.Pillar.v2.5.g/ImbalanceMessage.pcap", "nyse/arcaequities/integratedfeedrefresh/pillar/v2.5.g/ImbalanceMessage.values");
    failures += check("RefreshHeaderMessage", "Nyse/ArcaEquities.IntegratedFeedRefresh.Pillar.v2.5.g/RefreshHeaderMessage.pcap", "nyse/arcaequities/integratedfeedrefresh/pillar/v2.5.g/RefreshHeaderMessage.values");
    failures += check("SecurityStatusMessage", "Nyse/ArcaEquities.IntegratedFeedRefresh.Pillar.v2.5.g/SecurityStatusMessage.pcap", "nyse/arcaequities/integratedfeedrefresh/pillar/v2.5.g/SecurityStatusMessage.values");
    failures += check("SymbolIndexMappingMessage", "Nyse/ArcaEquities.IntegratedFeedRefresh.Pillar.v2.5.g/SymbolIndexMappingMessage.pcap", "nyse/arcaequities/integratedfeedrefresh/pillar/v2.5.g/SymbolIndexMappingMessage.values");
    return failures == 0 ? 0 : 1;
}
