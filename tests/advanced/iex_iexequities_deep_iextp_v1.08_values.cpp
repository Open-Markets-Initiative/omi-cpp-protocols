// Iex.IexEquities.Deep.IexTp.v1.08 canonical values, through the Advanced session layer: every value Advanced
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
#include "cpp/advanced/iex/iexequities/deep/iextp/v1.08/messages/session.hpp"

namespace protocol = ::iex::iexequities::deep::iextp::v1_08;

namespace {

// The handler the session layer hands each datagram's values to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    protocol::seq_action on_transport_header(const protocol::iextp_header& header, const packet::Frame&) {
        values["packet.iextpheader.version"] = canonical::number(header.version.get().value());
        values["packet.iextpheader.messageprotocolid"] = canonical::number(header.message_protocol_id.get().value());
        values["packet.iextpheader.channelid"] = canonical::number(header.channel_id.get().value());
        values["packet.iextpheader.sessionid"] = canonical::number(header.session_id.get().value());
        values["packet.iextpheader.payloadlength"] = canonical::number(header.payload_length.get().value());
        values["packet.iextpheader.messagecount"] = canonical::number(header.message_count.get().value());
        values["packet.iextpheader.streamoffset"] = canonical::number(header.stream_offset.get().value());
        values["packet.iextpheader.firstmessagesequencenumber"] = canonical::number(header.first_message_sequence_number.get().value());
        values["packet.iextpheader.sendtime"] = canonical::number(header.send_time.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::iextp_header&) {
        ++index;
    }

    void on_message(const protocol::system_event_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.systemeventmessage";
        values[entry + ".messagedata.systemeventmessage.systemevent"] = canonical::text(canonical::character(message.fields.system_event.get().value()));
        values[entry + ".messagedata.systemeventmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
    }

    void on_message(const protocol::security_directory_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.securitydirectorymessage";
        values[entry + ".messagedata.securitydirectorymessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".messagedata.securitydirectorymessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), ' ', false);
        values[entry + ".messagedata.securitydirectorymessage.roundlotsize"] = canonical::number(message.fields.round_lot_size.get().value());
        values[entry + ".messagedata.securitydirectorymessage.adjustedpocprice"] = canonical::scaled(message.fields.adjusted_poc_price.get().value(), -4);
        values[entry + ".messagedata.securitydirectorymessage.luldtier"] = canonical::number(message.fields.luld_tier.get().value());
    }

    void on_message(const protocol::trading_status_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.tradingstatusmessage";
        values[entry + ".messagedata.tradingstatusmessage.tradingstatus"] = canonical::text(canonical::character(message.fields.trading_status.get().value()));
        values[entry + ".messagedata.tradingstatusmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".messagedata.tradingstatusmessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), ' ', false);
        values[entry + ".messagedata.tradingstatusmessage.reason"] = canonical::text(std::string(message.fields.reason.get().value()), ' ', false);
    }

    void on_message(const protocol::retail_liquidity_indicator_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.retailliquidityindicatormessage";
        values[entry + ".messagedata.retailliquidityindicatormessage.retailliquidityindicator"] = canonical::text(canonical::character(message.fields.retail_liquidity_indicator.get().value()));
        values[entry + ".messagedata.retailliquidityindicatormessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".messagedata.retailliquidityindicatormessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), ' ', false);
    }

    void on_message(const protocol::operational_halt_status_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.operationalhaltstatusmessage";
        values[entry + ".messagedata.operationalhaltstatusmessage.operationalhaltstatus"] = canonical::text(canonical::character(message.fields.operational_halt_status.get().value()));
        values[entry + ".messagedata.operationalhaltstatusmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".messagedata.operationalhaltstatusmessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), ' ', false);
    }

    void on_message(const protocol::short_sale_price_test_status_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.shortsalepriceteststatusmessage";
        values[entry + ".messagedata.shortsalepriceteststatusmessage.shortsalepriceteststatus"] = canonical::number(message.fields.short_sale_price_test_status.get().value());
        values[entry + ".messagedata.shortsalepriceteststatusmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".messagedata.shortsalepriceteststatusmessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), ' ', false);
        values[entry + ".messagedata.shortsalepriceteststatusmessage.detail"] = canonical::text(canonical::character(message.fields.detail.get().value()));
    }

    void on_message(const protocol::security_event_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.securityeventmessage";
        values[entry + ".messagedata.securityeventmessage.securityevent"] = canonical::text(canonical::character(message.fields.security_event.get().value()));
        values[entry + ".messagedata.securityeventmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".messagedata.securityeventmessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), ' ', false);
    }

    void on_message(const protocol::price_level_buy_update_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.pricelevelbuyupdatemessage";
        values[entry + ".messagedata.pricelevelbuyupdatemessage.eventflags"] = canonical::number(message.fields.event_flags.get().value());
        values[entry + ".messagedata.pricelevelbuyupdatemessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".messagedata.pricelevelbuyupdatemessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), ' ', false);
        values[entry + ".messagedata.pricelevelbuyupdatemessage.size"] = canonical::number(message.fields.size.get().value());
        values[entry + ".messagedata.pricelevelbuyupdatemessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
    }

    void on_message(const protocol::price_level_sell_update_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.pricelevelsellupdatemessage";
        values[entry + ".messagedata.pricelevelsellupdatemessage.eventflags"] = canonical::number(message.fields.event_flags.get().value());
        values[entry + ".messagedata.pricelevelsellupdatemessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".messagedata.pricelevelsellupdatemessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), ' ', false);
        values[entry + ".messagedata.pricelevelsellupdatemessage.size"] = canonical::number(message.fields.size.get().value());
        values[entry + ".messagedata.pricelevelsellupdatemessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
    }

    void on_message(const protocol::trade_report_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.tradereportmessage";
        values[entry + ".messagedata.tradereportmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".messagedata.tradereportmessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), ' ', false);
        values[entry + ".messagedata.tradereportmessage.size"] = canonical::number(message.fields.size.get().value());
        values[entry + ".messagedata.tradereportmessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
        values[entry + ".messagedata.tradereportmessage.tradeid"] = canonical::number(message.fields.trade_id.get().value());
    }

    void on_message(const protocol::official_price_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.officialpricemessage";
        values[entry + ".messagedata.officialpricemessage.pricetype"] = canonical::text(canonical::character(message.fields.price_type.get().value()));
        values[entry + ".messagedata.officialpricemessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".messagedata.officialpricemessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), ' ', false);
        values[entry + ".messagedata.officialpricemessage.officialprice"] = canonical::scaled(message.fields.official_price.get().value(), -4);
    }

    void on_message(const protocol::trade_break_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.tradebreakmessage";
        values[entry + ".messagedata.tradebreakmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".messagedata.tradebreakmessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), ' ', false);
        values[entry + ".messagedata.tradebreakmessage.size"] = canonical::number(message.fields.size.get().value());
        values[entry + ".messagedata.tradebreakmessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
        values[entry + ".messagedata.tradebreakmessage.tradeid"] = canonical::number(message.fields.trade_id.get().value());
    }

    void on_message(const protocol::auction_information_message& message, std::uint64_t, const protocol::iextp_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".messagedata"] = "packet.messages.message.messagedata.auctioninformationmessage";
        values[entry + ".messagedata.auctioninformationmessage.auctiontype"] = canonical::text(canonical::character(message.fields.auction_type.get().value()));
        values[entry + ".messagedata.auctioninformationmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".messagedata.auctioninformationmessage.symbol"] = canonical::text(std::string(message.fields.symbol.get().value()), ' ', false);
        values[entry + ".messagedata.auctioninformationmessage.pairedshares"] = canonical::number(message.fields.paired_shares.get().value());
        values[entry + ".messagedata.auctioninformationmessage.referenceprice"] = canonical::scaled(message.fields.reference_price.get().value(), -4);
        values[entry + ".messagedata.auctioninformationmessage.indicativeclearingprice"] = canonical::scaled(message.fields.indicative_clearing_price.get().value(), -4);
        values[entry + ".messagedata.auctioninformationmessage.imbalanceshares"] = canonical::number(message.fields.imbalance_shares.get().value());
        values[entry + ".messagedata.auctioninformationmessage.imbalanceside"] = canonical::text(canonical::character(message.fields.imbalance_side.get().value()));
        values[entry + ".messagedata.auctioninformationmessage.extensionnumber"] = canonical::text(canonical::character(message.fields.extension_number.get().value()));
        values[entry + ".messagedata.auctioninformationmessage.scheduledauctiontime"] = canonical::number(message.fields.scheduled_auction_time.get().value());
        values[entry + ".messagedata.auctioninformationmessage.auctionbookclearingprice"] = canonical::scaled(message.fields.auction_book_clearing_price.get().value(), -4);
        values[entry + ".messagedata.auctioninformationmessage.collarreferenceprice"] = canonical::scaled(message.fields.collar_reference_price.get().value(), -4);
        values[entry + ".messagedata.auctioninformationmessage.lowerauctioncollar"] = canonical::scaled(message.fields.lower_auction_collar.get().value(), -4);
        values[entry + ".messagedata.auctioninformationmessage.upperauctioncollar"] = canonical::scaled(message.fields.upper_auction_collar.get().value(), -4);
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
    std::printf("== Iex.IexEquities.Deep.IexTp.v1.08 (advanced values)\n");
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