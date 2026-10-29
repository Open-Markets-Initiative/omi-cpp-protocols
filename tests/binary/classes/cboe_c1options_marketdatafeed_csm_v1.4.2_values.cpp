// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2 canonical values, through the Classes Packet: every value Classes decodes from
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
#include "cpp/binary/classes/cboe/c1options/marketdatafeed/csm/v1.4.2/definitions.hpp"

namespace protocol = ::cboe::c1options::marketdatafeed::csm::v1_4_2;

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

    values["packet.packetheader.version"] = canonical::number(packet.packet_header().version());
    values["packet.packetheader.packetlength"] = canonical::number(packet.packet_header().packet_length());
    values["packet.packetheader.sendingtime"] = canonical::number(packet.packet_header().sending_time());
    values["packet.packetheader.messagecount"] = canonical::number(packet.packet_header().message_count());
    values["packet.packetheader.firstmsgseqnum"] = canonical::number(packet.packet_header().first_msg_seq_num());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(each.message_header().message_length());
        values[entry + ".messageheader.templateid"] = canonical::number(each.message_header().template_id());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(each.message_header().message_type()));
        values[entry + ".messageheader.msgseqnum"] = canonical::number(each.message_header().msg_seq_num());

        if (dynamic_cast<const protocol::SecurityDefinitionMessage*>(each.message()) != nullptr) {
            values[entry + ".payload"] = "packet.message.payload.securitydefinitionmessage";
        } else if (const auto* message = dynamic_cast<const protocol::CurrentMarketRefreshMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.currentmarketrefreshmessage";
            values[entry + ".payload.currentmarketrefreshmessage.classkey"] = canonical::number((*message).class_key());
            values[entry + ".payload.currentmarketrefreshmessage.securityid"] = canonical::number((*message).security_id());
            values[entry + ".payload.currentmarketrefreshmessage.securitytradingstatus"] = canonical::number((*message).security_trading_status());
            values[entry + ".payload.currentmarketrefreshmessage.pricetype"] = canonical::number((*message).price_type());
            values[entry + ".payload.currentmarketrefreshmessage.applseqnum"] = canonical::number((*message).appl_seq_num());
            values[entry + ".payload.currentmarketrefreshmessage.noentries"] = canonical::number((*message).no_entries());
        } else if (const auto* message = dynamic_cast<const protocol::MarketDataRefreshMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.marketdatarefreshmessage";
            values[entry + ".payload.marketdatarefreshmessage.classkey"] = canonical::number((*message).class_key());
            values[entry + ".payload.marketdatarefreshmessage.securityid"] = canonical::number((*message).security_id());
            values[entry + ".payload.marketdatarefreshmessage.securitytradingstatus"] = canonical::number((*message).security_trading_status());
            values[entry + ".payload.marketdatarefreshmessage.pricetype"] = canonical::number((*message).price_type());
            values[entry + ".payload.marketdatarefreshmessage.applseqnum"] = canonical::number((*message).appl_seq_num());
            values[entry + ".payload.marketdatarefreshmessage.prevclosepx.prevclosepxexponent"] = canonical::number((*message).prev_close_px().prev_close_px_exponent());
            values[entry + ".payload.marketdatarefreshmessage.prevclosepx.prevclosepxmantissa"] = canonical::number((*message).prev_close_px().prev_close_px_mantissa());
            values[entry + ".payload.marketdatarefreshmessage.tradevolume"] = canonical::number((*message).trade_volume());
            values[entry + ".payload.marketdatarefreshmessage.noentries"] = canonical::number((*message).no_entries());
        } else if (const auto* message = dynamic_cast<const protocol::CurrentMarketUpdateMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.currentmarketupdatemessage";
            values[entry + ".payload.currentmarketupdatemessage.classkey"] = canonical::number((*message).class_key());
            values[entry + ".payload.currentmarketupdatemessage.securityid"] = canonical::number((*message).security_id());
            values[entry + ".payload.currentmarketupdatemessage.securitytradingstatus"] = canonical::number((*message).security_trading_status());
            values[entry + ".payload.currentmarketupdatemessage.pricetype"] = canonical::number((*message).price_type());
            values[entry + ".payload.currentmarketupdatemessage.noentries"] = canonical::number((*message).no_entries());
        } else if (const auto* message = dynamic_cast<const protocol::RecapUpdateMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.recapupdatemessage";
            values[entry + ".payload.recapupdatemessage.classkey"] = canonical::number((*message).class_key());
            values[entry + ".payload.recapupdatemessage.securityid"] = canonical::number((*message).security_id());
            values[entry + ".payload.recapupdatemessage.pricetype"] = canonical::number((*message).price_type());
            values[entry + ".payload.recapupdatemessage.prevclosepx.prevclosepxexponent"] = canonical::number((*message).prev_close_px().prev_close_px_exponent());
            values[entry + ".payload.recapupdatemessage.prevclosepx.prevclosepxmantissa"] = canonical::number((*message).prev_close_px().prev_close_px_mantissa());
            values[entry + ".payload.recapupdatemessage.tradevolume"] = canonical::number((*message).trade_volume());
            values[entry + ".payload.recapupdatemessage.noentries"] = canonical::number((*message).no_entries());
        } else if (const auto* message = dynamic_cast<const protocol::TickerMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.tickermessage";
            values[entry + ".payload.tickermessage.classkey"] = canonical::number((*message).class_key());
            values[entry + ".payload.tickermessage.securityid"] = canonical::number((*message).security_id());
            values[entry + ".payload.tickermessage.pricetype"] = canonical::number((*message).price_type());
            values[entry + ".payload.tickermessage.noentries"] = canonical::number((*message).no_entries());
        } else if (const auto* message = dynamic_cast<const protocol::ExpectedOpeningPriceAndSizeMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.expectedopeningpriceandsizemessage";
            values[entry + ".payload.expectedopeningpriceandsizemessage.classkey"] = canonical::number((*message).class_key());
            values[entry + ".payload.expectedopeningpriceandsizemessage.securityid"] = canonical::number((*message).security_id());
            values[entry + ".payload.expectedopeningpriceandsizemessage.eop.eopexponent"] = canonical::number((*message).eop().eop_exponent());
            values[entry + ".payload.expectedopeningpriceandsizemessage.eop.eopmantissa"] = canonical::number((*message).eop().eop_mantissa());
            values[entry + ".payload.expectedopeningpriceandsizemessage.eos"] = canonical::number((*message).eos());
            values[entry + ".payload.expectedopeningpriceandsizemessage.eoptype"] = canonical::number((*message).eop_type());
            values[entry + ".payload.expectedopeningpriceandsizemessage.legalmarket"] = canonical::number((*message).legal_market());
        } else if (dynamic_cast<const protocol::IndexValueMessage*>(each.message()) != nullptr) {
            values[entry + ".payload"] = "packet.message.payload.indexvaluemessage";
        } else if (const auto* message = dynamic_cast<const protocol::SettlementValueMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.settlementvaluemessage";
            values[entry + ".payload.settlementvaluemessage.classkey"] = canonical::number((*message).class_key());
            values[entry + ".payload.settlementvaluemessage.securityid"] = canonical::number((*message).security_id());
            values[entry + ".payload.settlementvaluemessage.pricetype"] = canonical::number((*message).price_type());
            values[entry + ".payload.settlementvaluemessage.noentries"] = canonical::number((*message).no_entries());
        } else if (const auto* message = dynamic_cast<const protocol::SummaryMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.summarymessage";
            values[entry + ".payload.summarymessage.classkey"] = canonical::number((*message).class_key());
            values[entry + ".payload.summarymessage.securityid"] = canonical::number((*message).security_id());
            values[entry + ".payload.summarymessage.pricetype"] = canonical::number((*message).price_type());
            values[entry + ".payload.summarymessage.tradevolume"] = canonical::number((*message).trade_volume());
            values[entry + ".payload.summarymessage.openinterest"] = canonical::number((*message).open_interest());
            values[entry + ".payload.summarymessage.netchgprevday.netchgprevdayexponent"] = canonical::number((*message).net_chg_prev_day().net_chg_prev_day_exponent());
            values[entry + ".payload.summarymessage.netchgprevday.netchgprevdaymantissa"] = canonical::number((*message).net_chg_prev_day().net_chg_prev_day_mantissa());
            values[entry + ".payload.summarymessage.underlyingpx.underlyingpxexponent"] = canonical::number((*message).underlying_px().underlying_px_exponent());
            values[entry + ".payload.summarymessage.underlyingpx.underlyingpxmantissa"] = canonical::number((*message).underlying_px().underlying_px_mantissa());
            values[entry + ".payload.summarymessage.noentries"] = canonical::number((*message).no_entries());
        } else if (const auto* message = dynamic_cast<const protocol::MarketDataControlMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.message.payload.marketdatacontrolmessage";
            values[entry + ".payload.marketdatacontrolmessage.mdcontroltype"] = canonical::number((*message).md_control_type());
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
    std::printf("== Cboe.C1Options.MarketDataFeed.Csm.v1.4.2 (classes values)\n");
    int failures = 0;
    failures += check("CurrentMarketRefreshMessage", "Cboe/C1Options.MarketDataFeed.Csm.v1.4.2/CurrentMarketRefreshMessage.pcap", "cboe/c1options/marketdatafeed/csm/v1.4.2/CurrentMarketRefreshMessage.values");
    failures += check("CurrentMarketUpdateMessage", "Cboe/C1Options.MarketDataFeed.Csm.v1.4.2/CurrentMarketUpdateMessage.pcap", "cboe/c1options/marketdatafeed/csm/v1.4.2/CurrentMarketUpdateMessage.values");
    failures += check("HeartbeatMessage", "Cboe/C1Options.MarketDataFeed.Csm.v1.4.2/HeartbeatMessage.pcap", "cboe/c1options/marketdatafeed/csm/v1.4.2/HeartbeatMessage.values");
    failures += check("MarketDataRefreshMessage", "Cboe/C1Options.MarketDataFeed.Csm.v1.4.2/MarketDataRefreshMessage.pcap", "cboe/c1options/marketdatafeed/csm/v1.4.2/MarketDataRefreshMessage.values");
    failures += check("RecapUpdateMessage", "Cboe/C1Options.MarketDataFeed.Csm.v1.4.2/RecapUpdateMessage.pcap", "cboe/c1options/marketdatafeed/csm/v1.4.2/RecapUpdateMessage.values");
    failures += check("SecurityDefinitionMessage", "Cboe/C1Options.MarketDataFeed.Csm.v1.4.2/SecurityDefinitionMessage.pcap", "cboe/c1options/marketdatafeed/csm/v1.4.2/SecurityDefinitionMessage.values");
    failures += check("TickerMessage", "Cboe/C1Options.MarketDataFeed.Csm.v1.4.2/TickerMessage.pcap", "cboe/c1options/marketdatafeed/csm/v1.4.2/TickerMessage.values");
    return failures == 0 ? 0 : 1;
}
