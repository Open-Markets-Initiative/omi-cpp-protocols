// Iex.IexEquities.Deep.IexTp.v1.08 canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/modern/iex/iexequities/deep/iextp/v1.08/definitions.hpp"

namespace protocol = ::iex::iexequities::deep::iextp::v1_08;

namespace {

// The values the Modern iterator reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    values["packet.iextpheader.version"] = canonical::number(iterator.iextp_header->version.get());
    values["packet.iextpheader.messageprotocolid"] = canonical::number(iterator.iextp_header->message_protocol_id.get());
    values["packet.iextpheader.channelid"] = canonical::number(iterator.iextp_header->channel_id.get());
    values["packet.iextpheader.sessionid"] = canonical::number(iterator.iextp_header->session_id.get());
    values["packet.iextpheader.payloadlength"] = canonical::number(iterator.iextp_header->payload_length.get());
    values["packet.iextpheader.messagecount"] = canonical::number(iterator.iextp_header->message_count.get());
    values["packet.iextpheader.streamoffset"] = canonical::number(iterator.iextp_header->stream_offset.get());
    values["packet.iextpheader.firstmessagesequencenumber"] = canonical::number(iterator.iextp_header->first_message_sequence_number.get());
    values["packet.iextpheader.sendtime"] = canonical::number(iterator.iextp_header->send_time.get());

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(iterator.message_header->message_length.get());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(iterator.message_header->message_type.get()));

        if (iterator.message_type == protocol::SystemEventMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.systemeventmessage";
            [[maybe_unused]] const auto* message = protocol::SystemEventMessage::parse(iterator.message);
            values[entry + ".messagedata.systemeventmessage.systemevent"] = canonical::text(canonical::character(message->system_event.get()));
            values[entry + ".messagedata.systemeventmessage.timestamp"] = canonical::number(message->timestamp.get());
        } else if (iterator.message_type == protocol::SecurityDirectoryMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.securitydirectorymessage";
            [[maybe_unused]] const auto* message = protocol::SecurityDirectoryMessage::parse(iterator.message);
            values[entry + ".messagedata.securitydirectorymessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".messagedata.securitydirectorymessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".messagedata.securitydirectorymessage.roundlotsize"] = canonical::number(message->round_lot_size.get());
            values[entry + ".messagedata.securitydirectorymessage.adjustedpocprice"] = canonical::scaled(message->adjusted_poc_price.integer(), -4);
            values[entry + ".messagedata.securitydirectorymessage.luldtier"] = canonical::number(message->luld_tier.get());
        } else if (iterator.message_type == protocol::TradingStatusMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.tradingstatusmessage";
            [[maybe_unused]] const auto* message = protocol::TradingStatusMessage::parse(iterator.message);
            values[entry + ".messagedata.tradingstatusmessage.tradingstatus"] = canonical::text(canonical::character(message->trading_status.get()));
            values[entry + ".messagedata.tradingstatusmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".messagedata.tradingstatusmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".messagedata.tradingstatusmessage.reason"] = canonical::text(std::string(message->reason.get()), ' ', false);
        } else if (iterator.message_type == protocol::RetailLiquidityIndicatorMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.retailliquidityindicatormessage";
            [[maybe_unused]] const auto* message = protocol::RetailLiquidityIndicatorMessage::parse(iterator.message);
            values[entry + ".messagedata.retailliquidityindicatormessage.retailliquidityindicator"] = canonical::text(canonical::character(message->retail_liquidity_indicator.get()));
            values[entry + ".messagedata.retailliquidityindicatormessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".messagedata.retailliquidityindicatormessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
        } else if (iterator.message_type == protocol::OperationalHaltStatusMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.operationalhaltstatusmessage";
            [[maybe_unused]] const auto* message = protocol::OperationalHaltStatusMessage::parse(iterator.message);
            values[entry + ".messagedata.operationalhaltstatusmessage.operationalhaltstatus"] = canonical::text(canonical::character(message->operational_halt_status.get()));
            values[entry + ".messagedata.operationalhaltstatusmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".messagedata.operationalhaltstatusmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
        } else if (iterator.message_type == protocol::ShortSalePriceTestStatusMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.shortsalepriceteststatusmessage";
            [[maybe_unused]] const auto* message = protocol::ShortSalePriceTestStatusMessage::parse(iterator.message);
            values[entry + ".messagedata.shortsalepriceteststatusmessage.shortsalepriceteststatus"] = canonical::number(message->short_sale_price_test_status.get());
            values[entry + ".messagedata.shortsalepriceteststatusmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".messagedata.shortsalepriceteststatusmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".messagedata.shortsalepriceteststatusmessage.detail"] = canonical::text(canonical::character(message->detail.get()));
        } else if (iterator.message_type == protocol::SecurityEventMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.securityeventmessage";
            [[maybe_unused]] const auto* message = protocol::SecurityEventMessage::parse(iterator.message);
            values[entry + ".messagedata.securityeventmessage.securityevent"] = canonical::text(canonical::character(message->security_event.get()));
            values[entry + ".messagedata.securityeventmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".messagedata.securityeventmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
        } else if (iterator.message_type == protocol::PriceLevelBuyUpdateMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.pricelevelbuyupdatemessage";
            [[maybe_unused]] const auto* message = protocol::PriceLevelBuyUpdateMessage::parse(iterator.message);
            values[entry + ".messagedata.pricelevelbuyupdatemessage.eventflags"] = canonical::number(message->event_flags.get());
            values[entry + ".messagedata.pricelevelbuyupdatemessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".messagedata.pricelevelbuyupdatemessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".messagedata.pricelevelbuyupdatemessage.size"] = canonical::number(message->size.get());
            values[entry + ".messagedata.pricelevelbuyupdatemessage.price"] = canonical::scaled(message->price.integer(), -4);
        } else if (iterator.message_type == protocol::PriceLevelSellUpdateMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.pricelevelsellupdatemessage";
            [[maybe_unused]] const auto* message = protocol::PriceLevelSellUpdateMessage::parse(iterator.message);
            values[entry + ".messagedata.pricelevelsellupdatemessage.eventflags"] = canonical::number(message->event_flags.get());
            values[entry + ".messagedata.pricelevelsellupdatemessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".messagedata.pricelevelsellupdatemessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".messagedata.pricelevelsellupdatemessage.size"] = canonical::number(message->size.get());
            values[entry + ".messagedata.pricelevelsellupdatemessage.price"] = canonical::scaled(message->price.integer(), -4);
        } else if (iterator.message_type == protocol::TradeReportMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.tradereportmessage";
            [[maybe_unused]] const auto* message = protocol::TradeReportMessage::parse(iterator.message);
            values[entry + ".messagedata.tradereportmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".messagedata.tradereportmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".messagedata.tradereportmessage.size"] = canonical::number(message->size.get());
            values[entry + ".messagedata.tradereportmessage.price"] = canonical::scaled(message->price.integer(), -4);
            values[entry + ".messagedata.tradereportmessage.tradeid"] = canonical::number(message->trade_id.get());
        } else if (iterator.message_type == protocol::OfficialPriceMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.officialpricemessage";
            [[maybe_unused]] const auto* message = protocol::OfficialPriceMessage::parse(iterator.message);
            values[entry + ".messagedata.officialpricemessage.pricetype"] = canonical::text(canonical::character(message->price_type.get()));
            values[entry + ".messagedata.officialpricemessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".messagedata.officialpricemessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".messagedata.officialpricemessage.officialprice"] = canonical::scaled(message->official_price.integer(), -4);
        } else if (iterator.message_type == protocol::TradeBreakMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.tradebreakmessage";
            [[maybe_unused]] const auto* message = protocol::TradeBreakMessage::parse(iterator.message);
            values[entry + ".messagedata.tradebreakmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".messagedata.tradebreakmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".messagedata.tradebreakmessage.size"] = canonical::number(message->size.get());
            values[entry + ".messagedata.tradebreakmessage.price"] = canonical::scaled(message->price.integer(), -4);
            values[entry + ".messagedata.tradebreakmessage.tradeid"] = canonical::number(message->trade_id.get());
        } else if (iterator.message_type == protocol::AuctionInformationMessage::message_type) {
            values[entry + ".messagedata"] = "packet.messages.message.messagedata.auctioninformationmessage";
            [[maybe_unused]] const auto* message = protocol::AuctionInformationMessage::parse(iterator.message);
            values[entry + ".messagedata.auctioninformationmessage.auctiontype"] = canonical::text(canonical::character(message->auction_type.get()));
            values[entry + ".messagedata.auctioninformationmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".messagedata.auctioninformationmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".messagedata.auctioninformationmessage.pairedshares"] = canonical::number(message->paired_shares.get());
            values[entry + ".messagedata.auctioninformationmessage.referenceprice"] = canonical::scaled(message->reference_price.integer(), -4);
            values[entry + ".messagedata.auctioninformationmessage.indicativeclearingprice"] = canonical::scaled(message->indicative_clearing_price.integer(), -4);
            values[entry + ".messagedata.auctioninformationmessage.imbalanceshares"] = canonical::number(message->imbalance_shares.get());
            values[entry + ".messagedata.auctioninformationmessage.imbalanceside"] = canonical::text(canonical::character(message->imbalance_side.get()));
            values[entry + ".messagedata.auctioninformationmessage.extensionnumber"] = canonical::text(canonical::character(message->extension_number.get()));
            values[entry + ".messagedata.auctioninformationmessage.scheduledauctiontime"] = canonical::number(message->scheduled_auction_time.get());
            values[entry + ".messagedata.auctioninformationmessage.auctionbookclearingprice"] = canonical::scaled(message->auction_book_clearing_price.integer(), -4);
            values[entry + ".messagedata.auctioninformationmessage.collarreferenceprice"] = canonical::scaled(message->collar_reference_price.integer(), -4);
            values[entry + ".messagedata.auctioninformationmessage.lowerauctioncollar"] = canonical::scaled(message->lower_auction_collar.integer(), -4);
            values[entry + ".messagedata.auctioninformationmessage.upperauctioncollar"] = canonical::scaled(message->upper_auction_collar.integer(), -4);
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
    std::printf("== Iex.IexEquities.Deep.IexTp.v1.08 (modern values)\n");
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