// Nyse.AmexOptions.ComplexFeed.Xdp.v1.3.a canonical values, through the Classes Packet: every value Classes decodes from
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
#include "cpp/binary/classes/nyse/amexoptions/complexfeed/xdp/v1.3.a/definitions.hpp"

namespace protocol = ::nyse::amexoptions::complexfeed::xdp::v1_3_a;

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

    values["packet.packetheader.packetsize"] = canonical::number(packet.packet_header().packet_size());
    values["packet.packetheader.deliveryflag"] = canonical::number(packet.packet_header().delivery_flag());
    values["packet.packetheader.messagecount"] = canonical::number(packet.packet_header().message_count());
    values["packet.packetheader.sequencenumber"] = canonical::number(packet.packet_header().sequence_number());
    values["packet.packetheader.sendtime.seconds"] = canonical::number(packet.packet_header().send_time().seconds());
    values["packet.packetheader.sendtime.nanoseconds"] = canonical::number(packet.packet_header().send_time().nanoseconds());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagesize"] = canonical::number(each.message_header().message_size());
        values[entry + ".messageheader.messagetype"] = canonical::number(each.message_header().message_type());

        if (const auto* message = dynamic_cast<const protocol::ComplexQuoteMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.complexquotemessage";
            values[entry + ".payload.complexquotemessage.sourcetime"] = canonical::number((*message).source_time());
            values[entry + ".payload.complexquotemessage.sourcetimens"] = canonical::number((*message).source_time_ns());
            values[entry + ".payload.complexquotemessage.complexindex"] = canonical::number((*message).complex_index());
            values[entry + ".payload.complexquotemessage.symbolseqnum"] = canonical::number((*message).symbol_seq_num());
            values[entry + ".payload.complexquotemessage.askprice"] = canonical::number((*message).ask_price());
            values[entry + ".payload.complexquotemessage.bidprice"] = canonical::number((*message).bid_price());
            values[entry + ".payload.complexquotemessage.askvolume"] = canonical::number((*message).ask_volume());
            values[entry + ".payload.complexquotemessage.bidvolume"] = canonical::number((*message).bid_volume());
            values[entry + ".payload.complexquotemessage.askcustomervolume"] = canonical::number((*message).ask_customer_volume());
            values[entry + ".payload.complexquotemessage.bidcustomervolume"] = canonical::number((*message).bid_customer_volume());
            values[entry + ".payload.complexquotemessage.quotecondition"] = canonical::text(canonical::character((*message).quote_condition()), '\0', false);
        } else if (const auto* message = dynamic_cast<const protocol::ComplexTradeMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.complextrademessage";
            values[entry + ".payload.complextrademessage.sourcetime"] = canonical::number((*message).source_time());
            values[entry + ".payload.complextrademessage.sourcetimens"] = canonical::number((*message).source_time_ns());
            values[entry + ".payload.complextrademessage.complexindex"] = canonical::number((*message).complex_index());
            values[entry + ".payload.complextrademessage.symbolseqnum"] = canonical::number((*message).symbol_seq_num());
            values[entry + ".payload.complextrademessage.tradeid"] = canonical::number((*message).trade_id());
            values[entry + ".payload.complextrademessage.price"] = canonical::number((*message).price());
            values[entry + ".payload.complextrademessage.volume4"] = canonical::number((*message).volume_4());
            values[entry + ".payload.complextrademessage.tradecond1"] = canonical::text(canonical::character((*message).trade_cond_1()), '\0', false);
            values[entry + ".payload.complextrademessage.tradecond2"] = canonical::text(canonical::character((*message).trade_cond_2()), '\0', false);
        } else if (const auto* message = dynamic_cast<const protocol::ComplexCrossingRfqMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.complexcrossingrfqmessage";
            values[entry + ".payload.complexcrossingrfqmessage.sourcetime"] = canonical::number((*message).source_time());
            values[entry + ".payload.complexcrossingrfqmessage.sourcens"] = canonical::number((*message).source_ns());
            values[entry + ".payload.complexcrossingrfqmessage.complexindex"] = canonical::number((*message).complex_index());
            values[entry + ".payload.complexcrossingrfqmessage.symbolseqnum"] = canonical::number((*message).symbol_seq_num());
            values[entry + ".payload.complexcrossingrfqmessage.side"] = canonical::text(canonical::character((*message).side()), '\0', false);
            values[entry + ".payload.complexcrossingrfqmessage.volume2"] = canonical::number((*message).volume_2());
            values[entry + ".payload.complexcrossingrfqmessage.price"] = canonical::number((*message).price());
        } else if (const auto* message = dynamic_cast<const protocol::ComplexCubeRfqMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.complexcuberfqmessage";
            values[entry + ".payload.complexcuberfqmessage.sourcetime"] = canonical::number((*message).source_time());
            values[entry + ".payload.complexcuberfqmessage.sourcens"] = canonical::number((*message).source_ns());
            values[entry + ".payload.complexcuberfqmessage.complexindex"] = canonical::number((*message).complex_index());
            values[entry + ".payload.complexcuberfqmessage.symbolseqnum"] = canonical::number((*message).symbol_seq_num());
            values[entry + ".payload.complexcuberfqmessage.side"] = canonical::text(canonical::character((*message).side()), '\0', false);
            values[entry + ".payload.complexcuberfqmessage.volume2"] = canonical::number((*message).volume_2());
            values[entry + ".payload.complexcuberfqmessage.price"] = canonical::number((*message).price());
        } else if (const auto* message = dynamic_cast<const protocol::ComplexStatusMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.complexstatusmessage";
            values[entry + ".payload.complexstatusmessage.sourcetime"] = canonical::number((*message).source_time());
            values[entry + ".payload.complexstatusmessage.sourcetimens"] = canonical::number((*message).source_time_ns());
            values[entry + ".payload.complexstatusmessage.complexindex"] = canonical::number((*message).complex_index());
            values[entry + ".payload.complexstatusmessage.symbolseqnum"] = canonical::number((*message).symbol_seq_num());
            values[entry + ".payload.complexstatusmessage.securitystatus"] = canonical::text(canonical::character((*message).security_status()), '\0', false);
            values[entry + ".payload.complexstatusmessage.haltcondition"] = canonical::text(canonical::character((*message).halt_condition()), '\0', false);
        } else if (const auto* message = dynamic_cast<const protocol::RefreshComplexQuoteMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.refreshcomplexquotemessage";
            values[entry + ".payload.refreshcomplexquotemessage.sourcetime"] = canonical::number((*message).source_time());
            values[entry + ".payload.refreshcomplexquotemessage.sourcetimens"] = canonical::number((*message).source_time_ns());
            values[entry + ".payload.refreshcomplexquotemessage.complexindex"] = canonical::number((*message).complex_index());
            values[entry + ".payload.refreshcomplexquotemessage.symbolseqnum"] = canonical::number((*message).symbol_seq_num());
            values[entry + ".payload.refreshcomplexquotemessage.askprice"] = canonical::number((*message).ask_price());
            values[entry + ".payload.refreshcomplexquotemessage.bidprice"] = canonical::number((*message).bid_price());
            values[entry + ".payload.refreshcomplexquotemessage.askvolume"] = canonical::number((*message).ask_volume());
            values[entry + ".payload.refreshcomplexquotemessage.bidvolume"] = canonical::number((*message).bid_volume());
            values[entry + ".payload.refreshcomplexquotemessage.askcustomervolume"] = canonical::number((*message).ask_customer_volume());
            values[entry + ".payload.refreshcomplexquotemessage.bidcustomervolume"] = canonical::number((*message).bid_customer_volume());
            values[entry + ".payload.refreshcomplexquotemessage.quotecondition"] = canonical::text(canonical::character((*message).quote_condition()), '\0', false);
        } else if (const auto* message = dynamic_cast<const protocol::RefreshComplexTradeMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.refreshcomplextrademessage";
            values[entry + ".payload.refreshcomplextrademessage.sourcetime"] = canonical::number((*message).source_time());
            values[entry + ".payload.refreshcomplextrademessage.sourcetimens"] = canonical::number((*message).source_time_ns());
            values[entry + ".payload.refreshcomplextrademessage.complexindex"] = canonical::number((*message).complex_index());
            values[entry + ".payload.refreshcomplextrademessage.symbolseqnum"] = canonical::number((*message).symbol_seq_num());
            values[entry + ".payload.refreshcomplextrademessage.tradeid"] = canonical::number((*message).trade_id());
            values[entry + ".payload.refreshcomplextrademessage.price"] = canonical::number((*message).price());
            values[entry + ".payload.refreshcomplextrademessage.volume4"] = canonical::number((*message).volume_4());
            values[entry + ".payload.refreshcomplextrademessage.tradecond1"] = canonical::text(canonical::character((*message).trade_cond_1()), '\0', false);
            values[entry + ".payload.refreshcomplextrademessage.tradecond2"] = canonical::text(canonical::character((*message).trade_cond_2()), '\0', false);
        } else if (const auto* message = dynamic_cast<const protocol::ComplexSymbolDefinitionMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.complexsymboldefinitionmessage";
            values[entry + ".payload.complexsymboldefinitionmessage.complexindex"] = canonical::number((*message).complex_index());
            values[entry + ".payload.complexsymboldefinitionmessage.complexsymbol"] = canonical::text(std::string((*message).complex_symbol()), '\0', false);
            values[entry + ".payload.complexsymboldefinitionmessage.channelid"] = canonical::number((*message).channel_id());
            values[entry + ".payload.complexsymboldefinitionmessage.marketid"] = canonical::number((*message).market_id());
            values[entry + ".payload.complexsymboldefinitionmessage.systemid"] = canonical::number((*message).system_id());
            values[entry + ".payload.complexsymboldefinitionmessage.streamid"] = canonical::number((*message).stream_id());
            values[entry + ".payload.complexsymboldefinitionmessage.nooflegs"] = canonical::number((*message).no_of_legs());
        } else if (const auto* message = dynamic_cast<const protocol::StreamIdMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.streamidmessage";
            values[entry + ".payload.streamidmessage.streamid"] = canonical::number((*message).stream_id());
        } else if (const auto* message = dynamic_cast<const protocol::SequenceNumberResetMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.sequencenumberresetmessage";
            values[entry + ".payload.sequencenumberresetmessage.sourcetime"] = canonical::number((*message).source_time());
            values[entry + ".payload.sequencenumberresetmessage.sourcetimens"] = canonical::number((*message).source_time_ns());
            values[entry + ".payload.sequencenumberresetmessage.productid"] = canonical::number((*message).product_id());
            values[entry + ".payload.sequencenumberresetmessage.channelid"] = canonical::number((*message).channel_id());
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
    std::printf("== Nyse.AmexOptions.ComplexFeed.Xdp.v1.3.a (classes values)\n");
    int failures = 0;
    failures += check("ComplexCrossingRfqMessage", "Nyse/AmexOptions.ComplexFeed.Xdp.v1.3.a/ComplexCrossingRfqMessage.pcap", "nyse/amexoptions/complexfeed/xdp/v1.3.a/ComplexCrossingRfqMessage.values");
    failures += check("ComplexQuoteMessage", "Nyse/AmexOptions.ComplexFeed.Xdp.v1.3.a/ComplexQuoteMessage.pcap", "nyse/amexoptions/complexfeed/xdp/v1.3.a/ComplexQuoteMessage.values");
    failures += check("ComplexStatusMessage", "Nyse/AmexOptions.ComplexFeed.Xdp.v1.3.a/ComplexStatusMessage.pcap", "nyse/amexoptions/complexfeed/xdp/v1.3.a/ComplexStatusMessage.values");
    failures += check("ComplexSymbolDefinitionMessage", "Nyse/AmexOptions.ComplexFeed.Xdp.v1.3.a/ComplexSymbolDefinitionMessage.pcap", "nyse/amexoptions/complexfeed/xdp/v1.3.a/ComplexSymbolDefinitionMessage.values");
    failures += check("ComplexTradeMessage", "Nyse/AmexOptions.ComplexFeed.Xdp.v1.3.a/ComplexTradeMessage.pcap", "nyse/amexoptions/complexfeed/xdp/v1.3.a/ComplexTradeMessage.values");
    failures += check("RefreshComplexQuoteMessage", "Nyse/AmexOptions.ComplexFeed.Xdp.v1.3.a/RefreshComplexQuoteMessage.pcap", "nyse/amexoptions/complexfeed/xdp/v1.3.a/RefreshComplexQuoteMessage.values");
    failures += check("RefreshComplexTradeMessage", "Nyse/AmexOptions.ComplexFeed.Xdp.v1.3.a/RefreshComplexTradeMessage.pcap", "nyse/amexoptions/complexfeed/xdp/v1.3.a/RefreshComplexTradeMessage.values");
    failures += check("StreamIdMessage", "Nyse/AmexOptions.ComplexFeed.Xdp.v1.3.a/StreamIdMessage.pcap", "nyse/amexoptions/complexfeed/xdp/v1.3.a/StreamIdMessage.values");
    return failures == 0 ? 0 : 1;
}
