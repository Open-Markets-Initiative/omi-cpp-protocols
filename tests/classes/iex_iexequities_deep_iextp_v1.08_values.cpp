// Iex.IexEquities.Deep.IexTp.v1.08 canonical values, through the Classes Packet: every value Classes decodes from
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
#include "cpp/classes/iex/iexequities/deep/iextp/v1.08/definitions.hpp"

namespace protocol = ::iex::iexequities::deep::iextp::v1_08;

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

    values["packet.iextpheader.version"] = canonical::number(packet.iextp_header().version());
    values["packet.iextpheader.messageprotocolid"] = canonical::number(packet.iextp_header().message_protocol_id());
    values["packet.iextpheader.channelid"] = canonical::number(packet.iextp_header().channel_id());
    values["packet.iextpheader.sessionid"] = canonical::number(packet.iextp_header().session_id());
    values["packet.iextpheader.payloadlength"] = canonical::number(packet.iextp_header().payload_length());
    values["packet.iextpheader.messagecount"] = canonical::number(packet.iextp_header().message_count());
    values["packet.iextpheader.streamoffset"] = canonical::number(packet.iextp_header().stream_offset());
    values["packet.iextpheader.firstmessagesequencenumber"] = canonical::number(packet.iextp_header().first_message_sequence_number());
    values["packet.iextpheader.sendtime"] = canonical::number(packet.iextp_header().send_time());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(each.message_header().message_length());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(each.message_header().message_type()));

        if (const auto* message = dynamic_cast<const protocol::SystemEventMessage*>(each.message())) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.systemeventmessage";
            values[entry + ".messagedata.systemeventmessage.systemevent"] = canonical::text(canonical::character((*message).system_event()));
            values[entry + ".messagedata.systemeventmessage.timestamp"] = canonical::number((*message).timestamp());
        } else if (const auto* message = dynamic_cast<const protocol::SecurityDirectoryMessage*>(each.message())) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.securitydirectorymessage";
            values[entry + ".messagedata.securitydirectorymessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".messagedata.securitydirectorymessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".messagedata.securitydirectorymessage.roundlotsize"] = canonical::number((*message).round_lot_size());
            values[entry + ".messagedata.securitydirectorymessage.adjustedpocprice"] = canonical::scaled((*message).adjusted_poc_price().mantissa(), (*message).adjusted_poc_price().exponent());
            values[entry + ".messagedata.securitydirectorymessage.luldtier"] = canonical::number((*message).luld_tier());
        } else if (const auto* message = dynamic_cast<const protocol::TradingStatusMessage*>(each.message())) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.tradingstatusmessage";
            values[entry + ".messagedata.tradingstatusmessage.tradingstatus"] = canonical::text(canonical::character((*message).trading_status()));
            values[entry + ".messagedata.tradingstatusmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".messagedata.tradingstatusmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".messagedata.tradingstatusmessage.reason"] = canonical::text(std::string((*message).reason()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::RetailLiquidityIndicatorMessage*>(each.message())) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.retailliquidityindicatormessage";
            values[entry + ".messagedata.retailliquidityindicatormessage.retailliquidityindicator"] = canonical::text(canonical::character((*message).retail_liquidity_indicator()));
            values[entry + ".messagedata.retailliquidityindicatormessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".messagedata.retailliquidityindicatormessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::OperationalHaltStatusMessage*>(each.message())) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.operationalhaltstatusmessage";
            values[entry + ".messagedata.operationalhaltstatusmessage.operationalhaltstatus"] = canonical::text(canonical::character((*message).operational_halt_status()));
            values[entry + ".messagedata.operationalhaltstatusmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".messagedata.operationalhaltstatusmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::ShortSalePriceTestStatusMessage*>(each.message())) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.shortsalepriceteststatusmessage";
            values[entry + ".messagedata.shortsalepriceteststatusmessage.shortsalepriceteststatus"] = canonical::number((*message).short_sale_price_test_status());
            values[entry + ".messagedata.shortsalepriceteststatusmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".messagedata.shortsalepriceteststatusmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".messagedata.shortsalepriceteststatusmessage.detail"] = canonical::text(canonical::character((*message).detail()));
        } else if (const auto* message = dynamic_cast<const protocol::SecurityEventMessage*>(each.message())) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.securityeventmessage";
            values[entry + ".messagedata.securityeventmessage.securityevent"] = canonical::text(canonical::character((*message).security_event()));
            values[entry + ".messagedata.securityeventmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".messagedata.securityeventmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::PriceLevelBuyUpdateMessage*>(each.message())) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.pricelevelbuyupdatemessage";
            values[entry + ".messagedata.pricelevelbuyupdatemessage.eventflags"] = canonical::number((*message).event_flags());
            values[entry + ".messagedata.pricelevelbuyupdatemessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".messagedata.pricelevelbuyupdatemessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".messagedata.pricelevelbuyupdatemessage.size"] = canonical::number((*message).size());
            values[entry + ".messagedata.pricelevelbuyupdatemessage.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
        } else if (const auto* message = dynamic_cast<const protocol::PriceLevelSellUpdateMessage*>(each.message())) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.pricelevelsellupdatemessage";
            values[entry + ".messagedata.pricelevelsellupdatemessage.eventflags"] = canonical::number((*message).event_flags());
            values[entry + ".messagedata.pricelevelsellupdatemessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".messagedata.pricelevelsellupdatemessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".messagedata.pricelevelsellupdatemessage.size"] = canonical::number((*message).size());
            values[entry + ".messagedata.pricelevelsellupdatemessage.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
        } else if (const auto* message = dynamic_cast<const protocol::TradeReportMessage*>(each.message())) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.tradereportmessage";
            values[entry + ".messagedata.tradereportmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".messagedata.tradereportmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".messagedata.tradereportmessage.size"] = canonical::number((*message).size());
            values[entry + ".messagedata.tradereportmessage.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
            values[entry + ".messagedata.tradereportmessage.tradeid"] = canonical::number((*message).trade_id());
        } else if (const auto* message = dynamic_cast<const protocol::OfficialPriceMessage*>(each.message())) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.officialpricemessage";
            values[entry + ".messagedata.officialpricemessage.pricetype"] = canonical::text(canonical::character((*message).price_type()));
            values[entry + ".messagedata.officialpricemessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".messagedata.officialpricemessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".messagedata.officialpricemessage.officialprice"] = canonical::scaled((*message).official_price().mantissa(), (*message).official_price().exponent());
        } else if (const auto* message = dynamic_cast<const protocol::TradeBreakMessage*>(each.message())) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.tradebreakmessage";
            values[entry + ".messagedata.tradebreakmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".messagedata.tradebreakmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".messagedata.tradebreakmessage.size"] = canonical::number((*message).size());
            values[entry + ".messagedata.tradebreakmessage.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
            values[entry + ".messagedata.tradebreakmessage.tradeid"] = canonical::number((*message).trade_id());
        } else if (const auto* message = dynamic_cast<const protocol::AuctionInformationMessage*>(each.message())) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.auctioninformationmessage";
            values[entry + ".messagedata.auctioninformationmessage.auctiontype"] = canonical::text(canonical::character((*message).auction_type()));
            values[entry + ".messagedata.auctioninformationmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".messagedata.auctioninformationmessage.symbol"] = canonical::text(std::string((*message).symbol()), ' ', false);
            values[entry + ".messagedata.auctioninformationmessage.pairedshares"] = canonical::number((*message).paired_shares());
            values[entry + ".messagedata.auctioninformationmessage.referenceprice"] = canonical::scaled((*message).reference_price().mantissa(), (*message).reference_price().exponent());
            values[entry + ".messagedata.auctioninformationmessage.indicativeclearingprice"] = canonical::scaled((*message).indicative_clearing_price().mantissa(), (*message).indicative_clearing_price().exponent());
            values[entry + ".messagedata.auctioninformationmessage.imbalanceshares"] = canonical::number((*message).imbalance_shares());
            values[entry + ".messagedata.auctioninformationmessage.imbalanceside"] = canonical::text(canonical::character((*message).imbalance_side()));
            values[entry + ".messagedata.auctioninformationmessage.extensionnumber"] = canonical::text(canonical::character((*message).extension_number()));
            values[entry + ".messagedata.auctioninformationmessage.scheduledauctiontime"] = canonical::number((*message).scheduled_auction_time());
            values[entry + ".messagedata.auctioninformationmessage.auctionbookclearingprice"] = canonical::scaled((*message).auction_book_clearing_price().mantissa(), (*message).auction_book_clearing_price().exponent());
            values[entry + ".messagedata.auctioninformationmessage.collarreferenceprice"] = canonical::scaled((*message).collar_reference_price().mantissa(), (*message).collar_reference_price().exponent());
            values[entry + ".messagedata.auctioninformationmessage.lowerauctioncollar"] = canonical::scaled((*message).lower_auction_collar().mantissa(), (*message).lower_auction_collar().exponent());
            values[entry + ".messagedata.auctioninformationmessage.upperauctioncollar"] = canonical::scaled((*message).upper_auction_collar().mantissa(), (*message).upper_auction_collar().exponent());
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
    std::printf("== Iex.IexEquities.Deep.IexTp.v1.08 (classes values)\n");
    int failures = 0;
    failures += check("AuctionInformationMessage", "Iex/IexEquities.Deep.IexTp.v1.08/AuctionInformationMessage.pcap", "iex/iexequities/deep/iextp/v1.08/AuctionInformationMessage.values");
    failures += check("OperationalHaltStatusMessage", "Iex/IexEquities.Deep.IexTp.v1.08/OperationalHaltStatusMessage.pcap", "iex/iexequities/deep/iextp/v1.08/OperationalHaltStatusMessage.values");
    failures += check("PriceLevelBuyUpdateMessage", "Iex/IexEquities.Deep.IexTp.v1.08/PriceLevelBuyUpdateMessage.pcap", "iex/iexequities/deep/iextp/v1.08/PriceLevelBuyUpdateMessage.values");
    failures += check("PriceLevelSellUpdateMessage", "Iex/IexEquities.Deep.IexTp.v1.08/PriceLevelSellUpdateMessage.pcap", "iex/iexequities/deep/iextp/v1.08/PriceLevelSellUpdateMessage.values");
    failures += check("RetailLiquidityIndicatorMessage", "Iex/IexEquities.Deep.IexTp.v1.08/RetailLiquidityIndicatorMessage.pcap", "iex/iexequities/deep/iextp/v1.08/RetailLiquidityIndicatorMessage.values");
    failures += check("SecurityEventMessage", "Iex/IexEquities.Deep.IexTp.v1.08/SecurityEventMessage.pcap", "iex/iexequities/deep/iextp/v1.08/SecurityEventMessage.values");
    failures += check("ShortSalePriceTestStatusMessage", "Iex/IexEquities.Deep.IexTp.v1.08/ShortSalePriceTestStatusMessage.pcap", "iex/iexequities/deep/iextp/v1.08/ShortSalePriceTestStatusMessage.values");
    failures += check("SystemEventMessage", "Iex/IexEquities.Deep.IexTp.v1.08/SystemEventMessage.pcap", "iex/iexequities/deep/iextp/v1.08/SystemEventMessage.values");
    failures += check("TradeReportMessage", "Iex/IexEquities.Deep.IexTp.v1.08/TradeReportMessage.pcap", "iex/iexequities/deep/iextp/v1.08/TradeReportMessage.values");
    failures += check("TradingStatusMessage", "Iex/IexEquities.Deep.IexTp.v1.08/TradingStatusMessage.pcap", "iex/iexequities/deep/iextp/v1.08/TradingStatusMessage.values");
    return failures == 0 ? 0 : 1;
}