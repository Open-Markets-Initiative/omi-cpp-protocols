// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2 canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/binary/modern/cboe/c1options/marketdatafeed/csm/v1.4.2/definitions.hpp"

namespace protocol = ::cboe::c1options::marketdatafeed::csm::v1_4_2;

namespace {

// The values the Modern iterator reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    values["packet.packetheader.version"] = canonical::number(iterator.packet_header->version.get());
    values["packet.packetheader.packetlength"] = canonical::number(iterator.packet_header->packet_length.get());
    values["packet.packetheader.sendingtime"] = canonical::number(iterator.packet_header->sending_time.get());
    values["packet.packetheader.messagecount"] = canonical::number(iterator.packet_header->message_count.get());
    values["packet.packetheader.firstmsgseqnum"] = canonical::number(iterator.packet_header->first_msg_seq_num.get());

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(iterator.message_header->message_length.get());
        values[entry + ".messageheader.templateid"] = canonical::number(iterator.message_header->template_id.get());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(iterator.message_header->message_type.get()));
        values[entry + ".messageheader.msgseqnum"] = canonical::number(iterator.message_header->msg_seq_num.get());

        if (iterator.template_id == protocol::SecurityDefinitionMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.securitydefinitionmessage";
            [[maybe_unused]] const auto* message = protocol::SecurityDefinitionMessage::parse(iterator.message);
        } else if (iterator.template_id == protocol::CurrentMarketRefreshMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.currentmarketrefreshmessage";
            [[maybe_unused]] const auto* message = protocol::CurrentMarketRefreshMessage::parse(iterator.message);
            values[entry + ".payload.currentmarketrefreshmessage.classkey"] = canonical::number(message->class_key.get());
            values[entry + ".payload.currentmarketrefreshmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.currentmarketrefreshmessage.securitytradingstatus"] = canonical::number(message->security_trading_status.get());
            values[entry + ".payload.currentmarketrefreshmessage.pricetype"] = canonical::number(message->price_type.get());
            values[entry + ".payload.currentmarketrefreshmessage.applseqnum"] = canonical::number(message->appl_seq_num.get());
            values[entry + ".payload.currentmarketrefreshmessage.noentries"] = canonical::number(message->no_entries.get());
        } else if (iterator.template_id == protocol::MarketDataRefreshMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.marketdatarefreshmessage";
            [[maybe_unused]] const auto* message = protocol::MarketDataRefreshMessage::parse(iterator.message);
            values[entry + ".payload.marketdatarefreshmessage.classkey"] = canonical::number(message->class_key.get());
            values[entry + ".payload.marketdatarefreshmessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.marketdatarefreshmessage.securitytradingstatus"] = canonical::number(message->security_trading_status.get());
            values[entry + ".payload.marketdatarefreshmessage.pricetype"] = canonical::number(message->price_type.get());
            values[entry + ".payload.marketdatarefreshmessage.applseqnum"] = canonical::number(message->appl_seq_num.get());
            values[entry + ".payload.marketdatarefreshmessage.prevclosepx.prevclosepxexponent"] = canonical::number(message->prev_close_px.prev_close_px_exponent.get());
            values[entry + ".payload.marketdatarefreshmessage.prevclosepx.prevclosepxmantissa"] = canonical::number(message->prev_close_px.prev_close_px_mantissa.get());
            values[entry + ".payload.marketdatarefreshmessage.tradevolume"] = canonical::number(message->trade_volume.get());
            values[entry + ".payload.marketdatarefreshmessage.noentries"] = canonical::number(message->no_entries.get());
        } else if (iterator.template_id == protocol::CurrentMarketUpdateMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.currentmarketupdatemessage";
            [[maybe_unused]] const auto* message = protocol::CurrentMarketUpdateMessage::parse(iterator.message);
            values[entry + ".payload.currentmarketupdatemessage.classkey"] = canonical::number(message->class_key.get());
            values[entry + ".payload.currentmarketupdatemessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.currentmarketupdatemessage.securitytradingstatus"] = canonical::number(message->security_trading_status.get());
            values[entry + ".payload.currentmarketupdatemessage.pricetype"] = canonical::number(message->price_type.get());
            values[entry + ".payload.currentmarketupdatemessage.noentries"] = canonical::number(message->no_entries.get());
        } else if (iterator.template_id == protocol::RecapUpdateMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.recapupdatemessage";
            [[maybe_unused]] const auto* message = protocol::RecapUpdateMessage::parse(iterator.message);
            values[entry + ".payload.recapupdatemessage.classkey"] = canonical::number(message->class_key.get());
            values[entry + ".payload.recapupdatemessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.recapupdatemessage.pricetype"] = canonical::number(message->price_type.get());
            values[entry + ".payload.recapupdatemessage.prevclosepx.prevclosepxexponent"] = canonical::number(message->prev_close_px.prev_close_px_exponent.get());
            values[entry + ".payload.recapupdatemessage.prevclosepx.prevclosepxmantissa"] = canonical::number(message->prev_close_px.prev_close_px_mantissa.get());
            values[entry + ".payload.recapupdatemessage.tradevolume"] = canonical::number(message->trade_volume.get());
            values[entry + ".payload.recapupdatemessage.noentries"] = canonical::number(message->no_entries.get());
        } else if (iterator.template_id == protocol::TickerMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.tickermessage";
            [[maybe_unused]] const auto* message = protocol::TickerMessage::parse(iterator.message);
            values[entry + ".payload.tickermessage.classkey"] = canonical::number(message->class_key.get());
            values[entry + ".payload.tickermessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.tickermessage.pricetype"] = canonical::number(message->price_type.get());
            values[entry + ".payload.tickermessage.noentries"] = canonical::number(message->no_entries.get());
        } else if (iterator.template_id == protocol::ExpectedOpeningPriceAndSizeMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.expectedopeningpriceandsizemessage";
            [[maybe_unused]] const auto* message = protocol::ExpectedOpeningPriceAndSizeMessage::parse(iterator.message);
            values[entry + ".payload.expectedopeningpriceandsizemessage.classkey"] = canonical::number(message->class_key.get());
            values[entry + ".payload.expectedopeningpriceandsizemessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.expectedopeningpriceandsizemessage.eop.eopexponent"] = canonical::number(message->eop.eop_exponent.get());
            values[entry + ".payload.expectedopeningpriceandsizemessage.eop.eopmantissa"] = canonical::number(message->eop.eop_mantissa.get());
            values[entry + ".payload.expectedopeningpriceandsizemessage.eos"] = canonical::number(message->eos.get());
            values[entry + ".payload.expectedopeningpriceandsizemessage.eoptype"] = canonical::number(message->eop_type.get());
            values[entry + ".payload.expectedopeningpriceandsizemessage.legalmarket"] = canonical::number(message->legal_market.get());
        } else if (iterator.template_id == protocol::IndexValueMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.indexvaluemessage";
            [[maybe_unused]] const auto* message = protocol::IndexValueMessage::parse(iterator.message);
        } else if (iterator.template_id == protocol::SettlementValueMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.settlementvaluemessage";
            [[maybe_unused]] const auto* message = protocol::SettlementValueMessage::parse(iterator.message);
            values[entry + ".payload.settlementvaluemessage.classkey"] = canonical::number(message->class_key.get());
            values[entry + ".payload.settlementvaluemessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.settlementvaluemessage.pricetype"] = canonical::number(message->price_type.get());
            values[entry + ".payload.settlementvaluemessage.noentries"] = canonical::number(message->no_entries.get());
        } else if (iterator.template_id == protocol::SummaryMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.summarymessage";
            [[maybe_unused]] const auto* message = protocol::SummaryMessage::parse(iterator.message);
            values[entry + ".payload.summarymessage.classkey"] = canonical::number(message->class_key.get());
            values[entry + ".payload.summarymessage.securityid"] = canonical::number(message->security_id.get());
            values[entry + ".payload.summarymessage.pricetype"] = canonical::number(message->price_type.get());
            values[entry + ".payload.summarymessage.tradevolume"] = canonical::number(message->trade_volume.get());
            values[entry + ".payload.summarymessage.openinterest"] = canonical::number(message->open_interest.get());
            values[entry + ".payload.summarymessage.netchgprevday.netchgprevdayexponent"] = canonical::number(message->net_chg_prev_day.net_chg_prev_day_exponent.get());
            values[entry + ".payload.summarymessage.netchgprevday.netchgprevdaymantissa"] = canonical::number(message->net_chg_prev_day.net_chg_prev_day_mantissa.get());
            values[entry + ".payload.summarymessage.underlyingpx.underlyingpxexponent"] = canonical::number(message->underlying_px.underlying_px_exponent.get());
            values[entry + ".payload.summarymessage.underlyingpx.underlyingpxmantissa"] = canonical::number(message->underlying_px.underlying_px_mantissa.get());
            values[entry + ".payload.summarymessage.noentries"] = canonical::number(message->no_entries.get());
        } else if (iterator.template_id == protocol::MarketDataControlMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.marketdatacontrolmessage";
            [[maybe_unused]] const auto* message = protocol::MarketDataControlMessage::parse(iterator.message);
            values[entry + ".payload.marketdatacontrolmessage.mdcontroltype"] = canonical::number(message->md_control_type.get());
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
    std::printf("== Cboe.C1Options.MarketDataFeed.Csm.v1.4.2 (modern values)\n");
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
